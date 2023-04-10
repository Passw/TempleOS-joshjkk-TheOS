#include "lib/include/stdio.h"
#include "lib/include/stdlib.h"
#include "lib/include/string.h"
#include "lib/include/stdint.h"
#include "lib/include/input.h"
#include "lib/include/time.h"
#include "lib/include/graphics.h"

#define CMD_BUF 128

uint8_t g_krow = 1;
uint8_t g_kcol = 1;

void refresh_console() {
    box(0, 0, ROWS, COLS);
    set_color(COLOR_BLACK, COLOR_LIGHT_GRAY);
    mvputs(0, (COLS / 2) - (strlen("KERNEL") / 2), "KERNEL");
    set_color(COLOR_WHITE, COLOR_BLACK);
}

void welcome() {
    clear();
    refresh_console();
    mvlog(g_krow++, g_kcol, "KERNEL", "Welcome", "Welcome to the 64-bit TheOS kernel!", COLOR_MAGENTA);
}

void kernel_main() {
    welcome();
    set_color(COLOR_WHITE, COLOR_BLACK);

    while (TRUE) {
        if (g_krow >= ROWS) {
            clear();
            refresh_console();
            g_krow = 1;
            g_kcol = 1;
        }

        sleep(INPUT_DELAY);
        g_kcol = 1;
        mvputc(g_krow, g_kcol++, '>');

        char *cmd = (char *)malloc(CMD_BUF * sizeof(char));
        size_t input_ticks = INPUT_BUF_TICKS;
        int i = 0;
        while (TRUE) {
            sleep(INPUT_DELAY / 3);
            char c = getchar();

            if (c == '\t' || c == '\b' || (int)c == 15 || (int)c == 14)
                continue;

            if (i > 0 && c == cmd[i - 1]) {
                if (input_ticks > 0) {
                    input_ticks--;
                    continue;
                }
                else
                    input_ticks = INPUT_BUF_TICKS;
            } else
                input_ticks = INPUT_BUF_TICKS;

            if (c == '\n') {
                g_krow++;
                break;
            } else {
                cmd[i++] = c;
                mvputc(g_krow, g_kcol++, c);
            }
        }
        mvsystem(g_krow++, 1, cmd);
        free(cmd);
    }
}
