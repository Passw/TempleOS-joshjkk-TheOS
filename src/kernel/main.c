#include "lib/include/stdio.h"
#include "lib/include/stdlib.h"
#include "lib/include/string.h"
#include "lib/include/stdint.h"
#include "lib/include/input.h"
#include "lib/include/time.h"
#include "lib/include/graphics.h"

extern int shift_pressed;
extern int ctrl_pressed;

void kernel_main() {
    clear();

    uint8_t colorscheme[8] = {
        COLOR_WHITE, COLOR_BLACK,
        COLOR_WHITE, COLOR_BLUE,
        COLOR_BLACK, COLOR_LIGHT_GRAY,
        COLOR_BLACK, COLOR_LIGHT_GRAY
    };
    box_t *kernel = init_box("KERNEL", 0, 0, ROWS, COLS, colorscheme, TRUE);
    refresh_box(kernel);

    char ver[] = "TheOS v0.2.0-prerelease1";
    set_color(COLOR_MAGENTA, COLOR_LIGHT_GRAY);
    box_addstr(kernel, 2, (kernel->cols / 2) - (strlen(ver) / 2), ver);

    box_t *welcome = init_box("WELCOME", (kernel->rows / 2) - (10 / 2), (kernel->cols / 2) - (40 / 2), 10, 40, colorscheme, FALSE);
    char welcome_msg[] = "Welcome to the 64-bit Theos Operating System. It is still in very early stages of development, so there isn't much to do right now. Despite that, I hope you're impressed, and you choose to stick around.";

    refresh_box(welcome);

    set_color(colorscheme[6], colorscheme[7]); // content color
    box_addstr(welcome, 0, 0, welcome_msg);

    free(welcome);

    while (TRUE) {
        sleep(INPUT_DELAY);
        getchar();
    }

    free(kernel); // should never happen
}
