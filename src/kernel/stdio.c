#include "include/stdio.h"
#include "include/stdint.h"

typedef struct VGAChar {
    uint8_t c;
    uint8_t color;
} vgachar_t;

vgachar_t *vgabuf = (vgachar_t *)0xB8000;

uint8_t g_row = 0;
uint8_t g_col = 0;
uint8_t g_color = COLOR_WHITE | (COLOR_BLACK << 4);

void putc(char c) {
    vgachar_t vgac = { (uint8_t)c, g_color };
    vgabuf[g_col + COLS * g_row] = vgac; 
    g_col++;
}

void puts(char *str) {
    while (*str) {
        putc(*str);
        str++;
    }
}

void clear() {
    for (uint16_t i = 0; i < ROWS * COLS; i++) {
        vgachar_t empty = { (uint8_t)' ', g_color };
        vgabuf[i] = empty;
    }
}
