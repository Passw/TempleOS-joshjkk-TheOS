#ifndef FAT_H
#define FAT_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct BootSector {
    uint8_t boot_jmp_instr[3];
    uint8_t oem_identifier[8];
    uint16_t bytes_per_sect;
    uint8_t sects_per_clust;
    uint16_t reserved_sects;
    uint8_t fat_count;
    uint16_t dir_entry_count;
    uint16_t total_sects;
    uint8_t media_descript_type;
    uint16_t sects_per_fat;
    uint16_t sects_per_track;
    uint16_t heads;
    uint32_t hidden_sects;
    uint32_t large_sect_count;

    // extended boot record
    uint8_t drive_num;
    uint8_t _reserved;
    uint8_t signature;
    uint32_t volume_id;
    uint8_t volume_label[11];
    uint8_t system_id[8];
} __attribute__((packed)) bootsector_t;

typedef struct DirectoryEntry {
    uint8_t name[11];
    uint8_t attrs;
    uint8_t _reserved;
    uint8_t creation_time_tenths;
    uint16_t creation_time;
    uint16_t creation_date;
    uint16_t accessed_date;
    uint16_t first_clust_high;
    uint16_t modified_time;
    uint16_t modified_date;
    uint16_t first_clust_low;
    uint32_t size;
} __attribute__((packed)) dir_entry_t;

bool read_bootsector(FILE *disk);

bool read_sectors(FILE *disk, uint32_t lba, uint32_t count, void *buffer);

bool read_fat(FILE *disk);

bool read_root_dir(FILE *disk);

dir_entry_t *find_file(const char *name);

bool read_file(dir_entry_t *file_entry, FILE *disk, uint8_t *buffer);

#endif // FAT_H
