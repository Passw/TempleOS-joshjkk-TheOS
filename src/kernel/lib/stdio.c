#include "include/stdio.h"
#include "include/stdint.h"
#include "include/string.h"

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
    if (c == '\n') {
        g_row++;
        return;
    } else if (c == '\0')
        return;

    vgachar_t vgac = { (uint8_t)c, g_color };
    vgabuf[g_col + COLS * g_row] = vgac; 
    g_col++;
}

void puts(char *str) {
    while (*str) {
        putc(*str);
        str++;
    }
    g_row++;
}

void mvputc(uint8_t row, uint8_t col, char c) {
    vgachar_t vgac = { (uint8_t)c, g_color };
    vgabuf[col + COLS * row] = vgac; 
    g_col++;
}

void mvputs(uint8_t row, uint8_t col, char *str) {
    uint8_t i = 0;
    while (*str) {
        mvputc(row, col + i, *str);
        i++;
        str++;
    }
}

void mvlog(uint8_t row, uint8_t col, const char *sender, const char *status, char *msg, uint8_t fore) {
    size_t send_len = strlen((char *)sender);
    size_t act_len = strlen((char *)status);

    set_color(COLOR_WHITE, COLOR_BLACK);
    mvputs(row, col, "[ ");
    set_color(fore, COLOR_BLACK);
    mvputs(row, col + 2, (char *)sender);
    set_color(COLOR_WHITE, COLOR_BLACK);
    mvputs(row, col + 2 + send_len, " ] ");
    set_color(COLOR_LIGHT_GRAY, COLOR_BLACK);
    mvputs(row, col + 5 + send_len, (char *)status);
    set_color(COLOR_WHITE, COLOR_BLACK);
    mvputc(row, col + 5 + send_len + act_len, ' ');
    mvputs(row, col + 6 + send_len + act_len, msg);
    g_row++;
}
