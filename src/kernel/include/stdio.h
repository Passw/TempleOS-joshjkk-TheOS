#ifndef STDIO_H
#define STDIO_H

#include "stdint.h"

#define ROWS 25
#define COLS 80

enum Colors {
    COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GRAY = 7,
	COLOR_DARK_GRAY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_PINK = 13,
	COLOR_YELLOW = 14,
	COLOR_WHITE = 15
};

void clear();

void set_color(uint8_t fore, uint8_t back);

void putc(char c);

void puts(char *str);

void mvputc(uint8_t row, uint8_t col, char c);

void mvputs(uint8_t row, uint8_t col, char *str);

#endif /* STDIO_H */
