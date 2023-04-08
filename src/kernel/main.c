#include "include/stdio.h"
#include "include/stdlib.h"
#include "include/string.h"

void kernel_main() {
    set_color(COLOR_WHITE, COLOR_BLACK);
    clear();

    puts("Hello from the 64-bit TheOS kernel!");
}
