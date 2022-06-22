#include "tty.h"
#include "graphics.h"

struct psf1_font* global_font;
int global_x = 0, global_y = 0;
uint32_t global_color = 0xffffffff;
uint32_t clear_color = 0;

void tty_set_font(struct psf1_font* font) {
    global_font = font;
}

struct psf1_font* tty_get_font() {
    return global_font;
}

void tty_set_color(uint32_t color) {
    global_color = color;
}

uint32_t tty_get_color() {
    return global_color;
}

void tty_set_clear_color(uint32_t color) {
    clear_color = color;
}

uint32_t tty_get_clear_color() {
    return clear_color;
}

void tty_set_position(uint32_t char_x, uint32_t char_y) {
    if(!global_font) return;
    global_x = char_x * 8;
    global_y = char_y * global_font->header->charsize;
}

void tty_set_position_pixel(uint32_t x, uint32_t y) {
    global_x = x;
    global_y = y;
}

void tty_putchar(char c) {
    if(!global_font) return;
    if(!fb_get_framebuffer()) return;
    char* font = (char*)global_font->buf + ((unsigned char)c * global_font->header->charsize);
    for(uint32_t y = global_y; y < global_y + global_font->header->charsize; y++) {
        for(uint32_t x = global_x; x < global_x + 8; x++) {
            if((*font & (128 >> (x - global_x))) > 0)
                fb_set_pixel(x, y, global_color);
        }
        font++;
    }
    global_x += 8;
    if(global_x + 8 > fb_get_framebuffer()->width) {
        global_x = 0;
        global_y += global_font->header->charsize;
    }
}

void tty_print(const char* str) {
    if(!str) return;
    if(!fb_get_framebuffer()) return;
    if(!global_font) return;
    char* ptr = (char*)str;
    while(*ptr != 0) {
        const char c = *ptr;
        if(c == '\n') {
            global_y += global_font->header->charsize;
            global_x = 0;
        } else if(c == '\r') {
            global_x = 0;
        } else if(c == '\v') {
            global_y += global_font->header->charsize;
        } else if(c == '\t') {
            for(int i = 0; i < 4; i++)
                tty_putchar(' ');
        } else if(c == '\b') {
            if(global_x <= 0 && global_y <= 0) {
                global_x = 0;
                global_y = 0;
            } else {
                if(global_x == 0) {
                    global_x = fb_get_framebuffer()->width;
                    global_y -= 16;
                }
                global_x -= 8;
            }
            
            fb_fill_rect(global_x, global_y, 8, global_font->header->charsize, clear_color);
        } else tty_putchar(*ptr);
        ptr++;
    }
}