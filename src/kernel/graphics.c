#include "include/graphics.h"
#include "include/stdio.h"
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

void box(size_t beg_row, size_t beg_col, size_t rows, size_t cols) {
    size_t last_row = beg_row + rows - 1;
    size_t last_col = beg_col + cols - 1;

    mvputc(beg_row, beg_col, (char)BOX_TOP_LEFT_CORNER);

    for (size_t col = 1; col < cols - 1; col++)
        mvputc(beg_row, beg_col + col, (char)BOX_TOP_BOTTOM_BORDER);

    mvputc(beg_row, last_col, (char)BOX_TOP_RIGHT_CORNER);

    for (size_t row = 1; row < rows - 1; row++) {
        mvputc(beg_row + row, beg_col, (char)BOX_SIDE_BORDER);
        mvputc(beg_row + row, last_col, (char)BOX_SIDE_BORDER);
    }

    mvputc(last_row, beg_col, (char)BOX_BOTTOM_LEFT_CORNER);

    for (size_t col = 1; col < cols - 1; col++)
        mvputc(last_row, beg_col + col, (char)BOX_TOP_BOTTOM_BORDER);

    mvputc(last_row, last_col, (char)BOX_BOTTOM_RIGHT_CORNER);
}
