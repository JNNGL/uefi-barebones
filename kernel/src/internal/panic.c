#include "panic.h"
#include "graphics.h"
#include "color.h"
#include "tty.h"

void panic(const char* str) {
    fb_clear(VGA_BLACK.argb);
    tty_set_position(0, 0);
    tty_print("kernel: panic: ");
    tty_print(str);
}