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

void fill_block(int x, int y, int cid) {
    color_argb_t color;
    switch (cid)
    {
    case 1:  { color = VGA_BLUE; break; }
    case 2:  { color = VGA_GREEN; break; }
    case 3:  { color = VGA_CYAN; break; }
    case 4:  { color = VGA_RED; break; }
    case 5:  { color = VGA_VIOLET; break; }
    case 6:  { color = VGA_YELLOW; break; }
    case 7:  { color = VGA_WHITE; break; }
    case 8:  { color = VGA_GREY; break; }
    case 9:  { color = VGA_LIGHT_BLUE; break; }
    case 10: { color = VGA_LIGHT_GREEN; break; }
    case 11: { color = VGA_LIGHT_CYAN; break; }
    case 12: { color = VGA_LIGHT_RED; break; }
    case 13: { color = VGA_LIGHT_VIOLET; break; }
    case 14: { color = VGA_LIGHT_YELLOW; break; }
    case 15: { color = VGA_BRIGHT_WHITE; break; }
    case 0:
    default: { color = VGA_BLACK; break; }
    }
    for(int dx = x; dx < x+50; dx++) {
        for(int dy = y; dy < y+25; dy++) {
            fb_set_pixel(dx, dy, color.argb);
        }
    }
}

void kernel_main(boot_info_t* info) {
    fb_set_framebuffer(info->framebuffer);
    tty_set_font(info->font);

    for(int x = 0; x < 8; x++) {
        for(int y = 0; y < 2; y++) {
            int cid = y * 8 + x;
            fill_block(x*50, y*25, cid);
        }
    }

    tty_set_color(VGA_LIGHT_GREEN.argb);
    tty_set_position(0, 4);
    tty_print("int_to_str (12345, radix: 10): ");
    tty_print(int_to_str(12345, 10));
    tty_print("\nint_to_str (12345, radix: 2): ");
    tty_print(int_to_str(12345, 2));
    tty_print("\nint_to_str (12345, radix: 16): ");
    tty_print(int_to_str(12345, 16));
    tty_print("\nint_to_str (12345, radix: 8): ");
    tty_print(int_to_str(12345, 8));
    tty_set_color(VGA_LIGHT_BLUE.argb);
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

