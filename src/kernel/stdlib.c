#include "include/stdlib.h"
#include "include/stdint.h"

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
