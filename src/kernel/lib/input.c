#include "include/input.h"
#include "include/stdio.h"
#include "include/stdlib.h"
#include "include/stdint.h"

#define KBD_DATA 0x60
#define KBD_STATUS 0x64 
#define KBD_IRQ 1

#define KBD_BUF_SIZ 256

#define LSHIFT 0x2A
#define RSHIFT 0x36

#define LCTRL 0x1D
#define RCTRL 0x9D

int_handler_t int_handlers[INT_HNDLR_CNT];

char kbd_buf[KBD_BUF_SIZ];
size_t kbd_index = 0;

unsigned char kbd_map[128] = {
    0, CH_ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', CH_BACKSPACE,
    CH_TAB, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', CH_ENTER,
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, CH_SPACE, 0, 
    // Remaining elements are set to 0
};

int g_shift_press = 0;
int g_ctrl_press = 0;
int g_key_held = 0;

int kbd_enabled = FALSE;

void kbd_handler() {
    unsigned char scancode = inb(KBD_DATA);
    if (scancode & 0x80) {
        g_key_held = 0;

        if (scancode == 0xAA || scancode == 0xB6)
            g_shift_press = 0;
        else if (scancode == 0x9D || scancode == 0xB8)
            g_ctrl_press = 0;
    } else {
        g_key_held = 1;

        if (scancode == LSHIFT || scancode == RSHIFT)
            g_shift_press = 1;
        else if (scancode == LCTRL || scancode == RCTRL)
            g_ctrl_press = 1;

        kbd_buf[kbd_index++] = kbd_map[scancode];
    }
    outb(0x20, 0x20);
}

void init_keyboard() {
    while (inb(KBD_STATUS) & 0x02)
        outb(0xAD, KBD_STATUS);

    while (inb(KBD_STATUS) & 0x02)
        outb(0xAE, KBD_STATUS);

    outb(0x64, 0x60);
    outb(0xF4, KBD_DATA);
    reg_int_handler(int_handlers, KBD_IRQ, kbd_handler);
    kbd_enabled = TRUE;
}

char getchar() {
    while (1) {
        kbd_handler();
        if (kbd_index > 0) {
            char input = kbd_buf[0];
            memset(kbd_buf, 0, KBD_BUF_SIZ);
            kbd_index = 0;
            return input;
        }
    }
    return '\0';
}
