#include "lib/include/stdio.h"
#include "lib/include/stdlib.h"
#include "lib/include/string.h"
#include "lib/include/input.h"
#include "lib/include/graphics.h"

void refresh_console() {
    box(0, 0, ROWS, COLS);
    set_color(COLOR_BLACK, COLOR_LIGHT_GRAY);
    mvputs(0, (COLS / 2) - (strlen("KERNEL") / 2), "KERNEL");
    set_color(COLOR_WHITE, COLOR_BLACK);
}

void kernel_main() {
    set_color(COLOR_WHITE, COLOR_BLACK);
    clear();
    refresh_console();
    mvlog(1, 1, "KERNEL", "Welcome", "Hello from the 64-bit TheOS kernel!", COLOR_MAGENTA);

    char buffer[32];
    char hello[] = "hello";
    sprintf(buffer, "%s", hello);
    mvputs(4, 1, buffer);
}
