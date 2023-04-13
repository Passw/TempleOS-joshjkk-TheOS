#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "stdint.h"

#define LAST_ROW(box) (box->beg_row + box->rows - 1)
#define LAST_COL(box) (box->beg_col + box->cols - 1)

typedef struct Color {
	uint8_t fore;
	uint8_t back;
} color_t;

typedef struct Colorscheme {
	color_t title;
	color_t title_border;
	color_t border;
	color_t content;
} colorscheme_t;

typedef struct Box {
	char *title;
	uint8_t beg_row;
	uint8_t beg_col;
	uint8_t rows;
	uint8_t cols;
	colorscheme_t colorscheme;
} box_t;

box_t *init_box(char *title, uint8_t beg_row, uint8_t beg_col, uint8_t rows, uint8_t cols);

void outline(uint8_t beg_row, uint8_t beg_col, uint8_t rows, uint8_t cols);

void fill(uint8_t beg_row, uint8_t beg_col, uint8_t rows, uint8_t cols, color_t color);

void refresh_box(box_t *box);

void box_addstr(box_t *box, uint8_t row, uint8_t col, char *str);

void del_box(box_t *box);

#endif /* GRAPHICS_H */
