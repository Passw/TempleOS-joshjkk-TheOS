#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "stdint.h"

typedef struct Box {
	char *title;
	uint8_t beg_row;
	uint8_t beg_col;
	uint8_t rows;
	uint8_t cols;
	uint8_t colorscheme[8];
	int title_menu;
} box_t;

box_t *init_box(char *title, uint8_t beg_row, uint8_t beg_col, uint8_t rows, uint8_t cols, uint8_t colorscheme[8], int title_menu);

void outline(uint8_t beg_row, uint8_t beg_col, uint8_t rows, uint8_t cols);

void refresh_box(box_t *box);

void box_addstr(box_t *box, uint8_t row, uint8_t col, char *str);

#endif /* GRAPHICS_H */
