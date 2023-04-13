#include "lib/include/stdio.h"
#include "lib/include/stdlib.h"
#include "lib/include/stdint.h"
#include "lib/include/string.h"
#include "lib/include/input.h"
#include "lib/include/time.h"
#include "lib/include/graphics.h"

#define VERSION "0.2.1-prerelease1"

void welcome() {
    const uint8_t rows = 12;
    const uint8_t cols = 40;

    box_t *wel_box = init_box("Welcome", (ROWS / 2) - (rows / 2), (COLS / 2) - (cols / 2), rows, cols);
    refresh_box(wel_box);

    char msg[] = "Welcome TheOS, an open source 64-bit operating system built by joshjkk@github. Use arrow keys for navigation, and the enter key for selecting entries.";

    set_color(wel_box->colorscheme.content.fore, wel_box->colorscheme.content.back);
    box_addstr(wel_box, 0, 0, msg);

    set_color(COLOR_WHITE, COLOR_RED);
    mvputs(LAST_ROW(wel_box), wel_box->beg_col + ((wel_box->cols / 2) - (strlen("<OK>") / 2)), "<OK>");

    while (TRUE) {
        sleep(INPUT_DELAY);
        char c = getchar();
        switch (c) {
            case CH_ENTER: goto stop; free(wel_box); return;
            default: break;
        }
    }
stop:
    /* how come this works but fill() doesn't???? */
    set_color(wel_box->colorscheme.content.fore, wel_box->colorscheme.content.back);
    for (uint8_t row = 0; row < wel_box->rows; row++) {
        for (uint8_t col = 0; col < wel_box->cols; col++)
            mvputc(wel_box->beg_row + row, wel_box->beg_col + col, ' ');
    }
}

void kernel_main() {
    clear();

    box_t *immortal = init_box("Immortal", 0, 0, ROWS, COLS);
    refresh_box(immortal);
    set_color(immortal->colorscheme.title_border.fore, immortal->colorscheme.title_border.back);
    mvputs(immortal->beg_row, LAST_COL(immortal) - 2, "   "); /* remove [x] */

    char title[32];
    sprintf(title, "TheOS v%s", VERSION);

    set_color(COLOR_MAGENTA, immortal->colorscheme.content.back);
    box_addstr(immortal, 0, (immortal->cols / 2) - (strlen(title) / 2), title);

    char msg[] = "Not much here at the moment :/";

    int welcomed = FALSE;

    while (TRUE) {
        if (!welcomed) {
            welcome();
            welcomed = TRUE;
        }

        set_color(immortal->colorscheme.content.fore, immortal->colorscheme.content.back);
        box_addstr(immortal, immortal->rows / 2, (immortal->cols / 2) - (strlen(msg) / 2), msg);

        sleep(INPUT_DELAY);
        getchar();
    }
}
