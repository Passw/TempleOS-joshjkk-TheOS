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

void clear() {
    for (uint16_t i = 0; i < ROWS * COLS; i++) {
        vgachar_t empty = { (uint8_t)' ', g_color };
        vgabuf[i] = empty;
    }
}

void set_color(uint8_t fore, uint8_t back) {
    g_color = fore | (back << 4);
}

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

void mvputc(uint8_t row, uint8_t col, char c) {
    vgachar_t vgac = { (uint8_t)c, g_color };
    vgabuf[col + COLS * row] = vgac; 
}

void mvputs(uint8_t row, uint8_t col, char *str) {
    uint8_t i = 0;
    while (*str) {
        mvputc(row, col + i, *str);
        i++;
        str++;
    }
}
