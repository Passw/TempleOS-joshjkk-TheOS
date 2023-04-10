#include "include/stdlib.h"
#include "include/stdio.h"
#include "include/stdint.h"
#include "include/string.h"
#include <stdarg.h>

#define HEAP_SIZ 1024

static char heap[HEAP_SIZ];

typedef struct MemBlock {
    size_t size;
    int free;
} memblock_t;

static memblock_t *heap_start = (memblock_t *) heap;


#define ITOA_BUF 32
#define ITOA_PALLETE "0123456789abcdef"

char *itoa(int val) {
    static char buf[ITOA_BUF] = { 0 };
    int base = 10;
    int i = 30;
    for (; val && i; --i, val /= base)
        buf[i] = ITOA_PALLETE[val % base];
    return &buf[i + 1];
}

char *itoa_base(int val, int base) {
    static char buf[ITOA_BUF] = { 0 };
    int i = 30;
    for (; val && i; --i, val /= base)
        buf[i] = ITOA_PALLETE[val % base];
    return &buf[i + 1];
}

char *itoa_val(int value, char *str, int base) {
    if (value == 0) {
        *str++ = '0';
        *str = '\0';
        return str;
    }

    int is_negative = 0;
    if (value < 0) {
        is_negative = 1;
        value = -value;
    }

    int num_digits = 0;
    while (value != 0) {
        int digit = value % base;
        char c = digit < 10 ? '0' + digit : 'A' + digit - 10;
        *str++ = c;
        value /= base;
        num_digits++;
    }

    if (is_negative) {
        *str++ = '-';
        num_digits++;
    }

    char *start = str - num_digits;
    char *end = str - 1;
    while (start < end) {
        char temp = *start;
        *start++ = *end;
        *end-- = temp;
    }

    *str = '\0';
    return str;
}

unsigned char inb(unsigned short port) {
    unsigned char value;
    __asm__ __volatile__("inb %1, %0" : "=a" (value) : "dN" (port));
    return value;
}

void outb(unsigned short port, unsigned char data) {
    __asm__ __volatile__("outb %0, %1" : : "a" (data), "dN" (port));
}

void reg_int_handler(int_handler_t *int_handlers, unsigned int n, int_handler_t handler) {
    int_handlers[n] = handler;
}

void *memset(void *ptr, int value, size_t size) {
    unsigned char *p = ptr;
    while (size--)
        *p++ = (unsigned char)value;
    return ptr;
}

static void split_block(memblock_t *block, size_t size) {
    memblock_t *new_block = (memblock_t *)((char *)block + sizeof(memblock_t) + size);
    new_block->size = block->size - sizeof(memblock_t) - size;
    new_block->free = 1;
    block->size = size;
    block->free = 0;
}

void *malloc(size_t size) {
    memblock_t *block = heap_start;

    while (block->size != 0) {
        if (block->free && block->size >= size) {
            if (block->size > size + sizeof(memblock_t))
                split_block(block, size);
            block->free = 0;
            return (void *)(block + 1);
        }
        block = (memblock_t *)((char *)block + sizeof(memblock_t) + block->size);
    }
    return NULL;
}

void *realloc(void *ptr, size_t size) {
    if (ptr == NULL)
        return malloc(size);

    if (size == 0) {
        free(ptr);
        return NULL;
    }

    memblock_t *block = (memblock_t *)ptr - 1;
    size_t original_size = block->size;
    if (original_size == size)
        return ptr;

    if (original_size > size) {
        if (original_size - size >= sizeof(memblock_t) + 1) {
            split_block(block, size);
        }
        return ptr;
    }

    memblock_t *next_block = (memblock_t *)((char *)block + sizeof(memblock_t) + block->size);
    if (next_block->free && block->size + sizeof(memblock_t) + next_block->size >= size) {
        block->size += sizeof(memblock_t) + next_block->size;
        return ptr;
    }

    void *new_ptr = malloc(size);
    if (new_ptr == NULL) {
        return NULL;
    }
    memcpy(new_ptr, ptr, original_size);
    free(ptr);
    return new_ptr;
}

void free(void *ptr) {
    if (ptr == NULL)
        return;

    memblock_t *block = (memblock_t *)ptr - 1;
    block->free = 1;

    memblock_t *prev_block = heap_start;
    while (prev_block->size != 0) {
        memblock_t *next_block = (memblock_t *)((char *)prev_block + sizeof(memblock_t) + prev_block->size);
        if (prev_block->free && next_block->free) {
            prev_block->size += sizeof(memblock_t) + next_block->size;
            block = prev_block;
        } else
            prev_block = next_block;
    }
}

void *memcpy(void *dest, const void *src, size_t size) {
    const char *s = src;
    char *d = dest;
    for (size_t i = 0; i < size; i++)
        d[i] = s[i];
    return dest;
}

void sprintf(char *buffer, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    char c;
    int d;
    char *s;

    while (*format) {
        if (*format != '%') {
            *buffer++ = *format++;
            continue;
        }

        format++;
        switch (*format) {
            case 'c':
                c = va_arg(args, int);
                *buffer++ = c;
                break;
            case 'd':
                d = va_arg(args, int);
                itoa_val(d, buffer, 10); // Custom implementation of itoa
                buffer += strlen(buffer);
                break;
            case 's':
                s = va_arg(args, char*);
                strcpy(buffer, s);
                buffer += strlen(buffer);
                break;
            default:
                *buffer++ = *format;
                break;
        }

        format++;
    }

    va_end(args);
    *buffer = '\0';
}

void system(char *cmd) {
    (void)cmd;
    mvlog(1, 1, "SYSTEM", "NOT IMPLEMENTED", "Commands are not implemented yet", COLOR_RED);
}

void mvsystem(uint8_t row, uint8_t col, char *cmd) {
    (void)cmd;
    mvlog(row, col, "SYSTEM", "NOT IMPLEMENTED", "Commands are not implemented yet", COLOR_RED);
}    
