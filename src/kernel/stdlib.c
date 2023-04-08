#include "include/stdlib.h"

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
