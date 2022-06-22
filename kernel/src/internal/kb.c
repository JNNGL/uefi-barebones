#include "kb.h"
#include "kb_scancode.h"
#include "tty.h"
#include <stdbool.h>

bool is_left_shift_pr;
bool is_right_shift_pr;

void kb_input(uint8_t scancode) {
    switch (scancode) {
        case KB_LEFT_SHIFT:
            is_left_shift_pr = true;
            break;

        case KB_LEFT_SHIFT + 0x80:
            is_left_shift_pr = false;
            break;

        case KB_RIGHT_SHIFT:
            is_right_shift_pr = true;
            break;

        case KB_RIGHT_SHIFT + 0x80:
            is_right_shift_pr = false;
            break;

        case KB_ENTER: 
            tty_print("\n");
            break;

        case KB_BACKSPACE:
            tty_print("\b");
            break;

        case KB_SPACE:
            tty_putchar(' ');
            break;

        default: {
            char a = kbtoa(scancode, is_left_shift_pr | is_right_shift_pr);
            if(a) {
                tty_putchar(a);
            }
            break;
        }
    }
}