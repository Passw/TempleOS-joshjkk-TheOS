#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "fat.h"

bootsector_t g_bootsector;
uint8_t *g_fat = NULL;
dir_entry_t *g_root_dir = NULL;
uint32_t g_root_dir_end;

bool read_bootsector(FILE *disk) {
    return fread(&g_bootsector, sizeof(g_bootsector), 1, disk);
}

bool read_sectors(FILE *disk, uint32_t lba, uint32_t count, void *buffer) {
    bool ok = true;
    ok = ok && (fseek(disk, lba * g_bootsector.bytes_per_sect, SEEK_SET) == 0);
    ok = ok && (fread(buffer, g_bootsector.bytes_per_sect, count, disk) == count);
    return ok;
}

bool read_fat(FILE *disk) {
    g_fat = (uint8_t *)calloc(g_bootsector.sects_per_fat, g_bootsector.bytes_per_sect);
    return read_sectors(disk, g_bootsector.reserved_sects, g_bootsector.sects_per_fat, g_fat);
}

bool read_root_dir(FILE *disk) {
    uint32_t lba = g_bootsector.reserved_sects + g_bootsector.sects_per_fat * g_bootsector.fat_count;
    uint32_t size = sizeof(dir_entry_t) * g_bootsector.dir_entry_count;
    uint32_t sectors = (size / g_bootsector.bytes_per_sect);
    if (size % g_bootsector.bytes_per_sect > 0)
        sectors++;

    g_root_dir_end = lba + sectors;
    g_root_dir = (dir_entry_t *)calloc(sectors, g_bootsector.bytes_per_sect);
    return read_sectors(disk, lba, sectors, g_root_dir);
}

dir_entry_t *find_file(const char *name) {
    for (uint32_t i = 0; i < g_bootsector.dir_entry_count; i++) {
        if (memcmp(name, g_root_dir[i].name, 11) == 0)
            return &g_root_dir[i];
    }
    return NULL;
}

bool read_file(dir_entry_t *file_entry, FILE *disk, uint8_t *buffer) {
    bool ok = true;
    uint16_t cur_clust = file_entry->first_clust_low;

    do {
        uint32_t lba = g_root_dir_end + (cur_clust - 2) * g_bootsector.sects_per_clust;
        ok = ok && read_sectors(disk, lba, g_bootsector.sects_per_clust, buffer);
        buffer += g_bootsector.sects_per_clust * g_bootsector.bytes_per_sect;

        uint32_t fat_i = cur_clust * 3 / 2;
        if (cur_clust % 2 == 0)
            cur_clust = (*(uint16_t *)(g_fat + fat_i)) & 0x0FFF;
        else
            cur_clust = (*(uint16_t *)(g_fat + fat_i)) >> 4;
    } while (ok && cur_clust < 0x0FF8);
    return ok;
}

int main(int argc, const char **argv) {
    if (argc < 3) {
        printf("Usage: %s [disk image] [filename]\n", argv[0]);
        return 1;
    }

    const char *img_name = argv[1];
    FILE *disk = fopen(img_name, "rb");
    if (disk == NULL) {
        fprintf(stderr, "Could not open disk image '%s'\n", img_name);
        return 1;
    }

    if (!read_bootsector(disk)) {
        fprintf(stderr, "Could not read boot sector!\n");
        fclose(disk);
        return 1;
    }

    if (!read_fat(disk)) {
        fprintf(stderr, "Could not read FAT!\n");
        fclose(disk);
        free(g_fat);
        return 1;
    }

    if (!read_root_dir(disk)) {
        fprintf(stderr, "Could not read root directory of FAT!\n");
        fclose(disk);
        free(g_fat);
        free(g_root_dir);
        return 1;
    }

    dir_entry_t *file_entry = find_file(argv[2]);
    if (file_entry == NULL) {
        fprintf(stderr, "Could not read file entry for '%s'\n", argv[2]);
        fclose(disk);
        free(g_fat);
        free(g_root_dir);
        return 1;
    }

    uint8_t *buffer = (uint8_t *)malloc(file_entry->size + g_bootsector.bytes_per_sect);
    if (!read_file(file_entry, disk, buffer)) {
        fprintf(stderr, "Could not read file '%s'\n", argv[2]);
        fclose(disk);
        free(g_fat);
        free(g_root_dir);
        free(buffer);
        return 1;
    }

    for (size_t i = 0; i < file_entry->size; i++) {
        if (isprint(buffer[i]))
            fputc(buffer[i], stdout);
        else
            printf("<%02x>", buffer[i]);
    }
    printf("\n");

    fclose(disk);
    free(g_fat);
    free(g_root_dir);
    return 0;
}
