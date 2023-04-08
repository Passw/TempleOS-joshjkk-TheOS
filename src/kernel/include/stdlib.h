#ifndef STDLIB_H
#define STDLIB_H

#include "stdint.h"

#define INT_HNDLR_CNT 256

typedef struct InterruptFrame {
    int ip;
    int cs;
    int flags;
    int sp;
    int ss;
} int_frame;

typedef void (*int_handler_t)(int_frame *);


char *itoa(int val);

char *itoa_base(int val, int base);

unsigned char inb(unsigned short port);

void outb(unsigned short port, unsigned char data);

void reg_int_handler(int_handler_t *int_handlers, unsigned int n, int_handler_t handler);

void *memset(void *ptr, int value, size_t size);

#endif /* STDLIB_H */
