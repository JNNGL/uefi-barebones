#include "internal/graphics.h"
#include "internal/tty.h"
#include "internal/color.h"
#include "internal/string.h"

typedef struct boot_info_s {
    framebuffer_t* framebuffer;
    struct psf1_font* font;
} boot_info_t;

void debug_err() {
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < 100; j++) {
            fb_set_pixel(i, j, 0xffffffff);
        }
    } 
}

void kernel_main(boot_info_t* info) {
    fb_set_framebuffer(info->framebuffer);
    tty_set_font(info->font);
    tty_set_color(VGA_LIGHT_CYAN.argb);
    tty_print("int_to_str (10): ");
    tty_print(int_to_str(12345, 10));
    tty_print("\nint_to_str (2): ");
    tty_print(int_to_str(12345, 2));
    tty_print("\nint_to_str (16): ");
    tty_print(int_to_str(12345, 16));
    tty_print("\nint_to_str (8): ");
    tty_print(int_to_str(12345, 8));
    tty_print("\n");
    tty_print("\nstr_to_int (12345): ");
    tty_print(int_to_str(str_to_int("12345", 10), 10));
    tty_print("\nstr_to_long (DEADBEEF): ");
    tty_print(long_to_str(str_to_long("DEADBEEF", 16), 16));
    tty_print("\nstr_to_int (baaaad): ");
    tty_print(long_to_str(str_to_long("baaaad", 16), 16));
    tty_print("\nstr_to_int (110111001): ");
    tty_print(int_to_str(str_to_int("110111001", 2), 2));
}

