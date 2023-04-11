#include "include/graphics.h"
#include "include/stdio.h"
#include "include/stdlib.h"
#include "include/string.h"
#include "include/stdint.h"

enum BoxChars
{
	BOX_TOP_LEFT_CORNER = 201,
	BOX_TOP_RIGHT_CORNER = 187,
	BOX_TOP_BOTTOM_BORDER = 205,
	BOX_BOTTOM_LEFT_CORNER = 200,
	BOX_BOTTOM_RIGHT_CORNER = 188,
	BOX_SIDE_BORDER = 186
};

box_t *init_box(char *title, uint8_t beg_row, uint8_t beg_col, uint8_t rows, uint8_t cols, uint8_t colorscheme[8], int title_menu) {
    box_t *box = (box_t *)malloc(sizeof(box_t));
    box->title = title;
    box->beg_row = beg_row;
    box->beg_col = beg_col;
    box->rows = rows;
    box->cols = cols;
    memcpy(box->colorscheme, colorscheme, (8 * sizeof(uint8_t)));
    box->title_menu = title_menu;
    return box;
}

void outline(uint8_t beg_row, uint8_t beg_col, uint8_t rows, uint8_t cols) {
    uint8_t last_row = beg_row + rows - 1;
    uint8_t last_col = beg_col + cols - 1;

    mvputc(beg_row, beg_col, (char)BOX_TOP_LEFT_CORNER);

    for (uint8_t col = 1; col < cols - 1; col++)
        mvputc(beg_row, beg_col + col, (char)BOX_TOP_BOTTOM_BORDER);

    mvputc(beg_row, last_col, (char)BOX_TOP_RIGHT_CORNER);

    for (uint8_t row = 1; row < rows - 1; row++) {
        mvputc(beg_row + row, beg_col, (char)BOX_SIDE_BORDER);
        mvputc(beg_row + row, last_col, (char)BOX_SIDE_BORDER);
    }

    mvputc(last_row, beg_col, (char)BOX_BOTTOM_LEFT_CORNER);

    for (uint8_t col = 1; col < cols - 1; col++)
        mvputc(last_row, beg_col + col, (char)BOX_TOP_BOTTOM_BORDER);

    mvputc(last_row, last_col, (char)BOX_BOTTOM_RIGHT_CORNER);
}

void fill(uint8_t beg_row, uint8_t beg_col, uint8_t rows, uint8_t cols) {
    for (uint8_t row = 0; row < rows; row++) {
        for (uint8_t col = 0; col < cols; col++)
            mvputc(beg_row + row, beg_col + col, ' ');
    }
}

void refresh_box(box_t *box) {
    set_color(box->colorscheme[4], box->colorscheme[5]);
    outline(box->beg_row, box->beg_col, box->rows, box->cols);

    set_color(box->colorscheme[6], box->colorscheme[7]);
    fill(box->beg_row + 1, box->beg_col + 1, box->rows - 2, box->cols - 2);

    set_color(box->colorscheme[2], box->colorscheme[3]);
    for (uint8_t i = 0; i < box->cols; i++)
        mvputc(box->beg_row, box->beg_col + i, ' ');

    if (box->title_menu == TRUE) {
        char title_menu[] = "File  Edit  View";
        mvputs(box->beg_row, box->beg_col + 1, title_menu);
    }

    mvputs(box->beg_row, box->beg_col + box->cols - 3, "[X]");

    set_color(box->colorscheme[0], box->colorscheme[1]);
    mvputs(box->beg_row, box->beg_col + ((box->cols / 2) - (strlen(box->title) / 2)), box->title);
}

void box_addstr(box_t *box, uint8_t row, uint8_t col, char *str) {
    const uint8_t right_border = box->beg_col + box->cols - 1;
    const uint8_t start_row = box->beg_row + row + 1; // 1 = border offset
    const uint8_t start_col = box->beg_col + col + 1; // 1 = border offset
    
    uint8_t cur_row = start_row;
    uint8_t cur_col = start_col;

    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '\n' || cur_col == right_border) {
            cur_col = start_col;
            cur_row++;
        }
        mvputc(cur_row, cur_col++, str[i]);
    }
}
