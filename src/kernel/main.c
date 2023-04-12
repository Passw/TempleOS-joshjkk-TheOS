#include "lib/include/stdio.h"
#include "lib/include/stdlib.h"
#include "lib/include/string.h"
#include "lib/include/stdint.h"
#include "lib/include/input.h"
#include "lib/include/time.h"
#include "lib/include/graphics.h"

#define VERSION "0.2.1-prerelease1"

extern int shift_pressed;
extern int ctrl_pressed;

uint8_t colorscheme[10] = {
    COLOR_WHITE, COLOR_BLACK,
    COLOR_WHITE, COLOR_BLUE,
    COLOR_BLACK, COLOR_LIGHT_GRAY,
    COLOR_BLACK, COLOR_LIGHT_GRAY,
    COLOR_WHITE, COLOR_BLUE
};

char title[32];

box_t *init_immortal() {

    box_t *immortal = init_box("Immortal", 0, 0, ROWS, COLS, colorscheme, TRUE);
    refresh_box(immortal);

    /* get rid of [x] */
    set_color(colorscheme[2], colorscheme[3]);
    mvputs(immortal->beg_row, immortal->beg_col + immortal->cols - 3, "   ");

    return immortal;
}

void update_immortal(box_t *immortal) {
    set_color(COLOR_MAGENTA, colorscheme[7]);
    box_addstr(immortal, 0, (immortal->cols / 2) - (strlen(title) / 2), title);

    /*
    box_t *status = init_box("Status", 2, 2, 10, COLS - 4, colorscheme, FALSE);
    refresh_box(status);
    char msg[] = "This is the status box.";
    box_addstr(status, 0, 0, msg);

    free(status);
    */
}

box_t *init_welcome(uint8_t beg_row, uint8_t beg_col, uint8_t rows, uint8_t cols) {
    box_t *welcome = init_box("Welcome", beg_row, beg_col, rows, cols, colorscheme, FALSE);
    char welcome_msg[] = "Welcome to the 64-bit Theos Operating System. It is still in very early stages of development, so there isn't much to do right now. Despite that, I hope you're still impressed, and I hope you choose to stick around.";

    refresh_box(welcome);

    set_color(colorscheme[6], colorscheme[7]);
    box_addstr(welcome, 0, 0, welcome_msg);

    set_color(COLOR_WHITE, COLOR_RED);
    mvputs(welcome->beg_row + welcome->rows - 1, welcome->beg_col + ((welcome->cols / 2) - (strlen("<OK>") / 2)), "<OK>");

    return welcome;
}

void kernel_main() {
    clear();

    sprintf(title, "TheOS v%s", VERSION);

    box_t *immortal = init_immortal();
    update_immortal(immortal);

    int welcoming = TRUE;

    while (TRUE) {
        if (welcoming == TRUE) {
            box_t *welcome = init_welcome((ROWS / 2) - (10 / 2), (COLS / 2) - (40 / 2), ROWS / 2, COLS / 2);
            while (TRUE) {
                sleep(INPUT_DELAY);
                int key = getchar();
                switch (key) {
                    case CH_ENTER: welcoming = FALSE; set_color(colorscheme[6], colorscheme[7]);  del_box(welcome); break;
                    default: break;
                }
            }
        }


        sleep(INPUT_DELAY);
        char key = getchar();
        switch (key) {
            default: break;
        }
    }
}
