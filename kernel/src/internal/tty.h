#ifndef KERNEL_INTERNAL_TTY_H
#define KERNEL_INTERNAL_TTY_H

#include <stdint.h>
#include "font.h"

void tty_set_font(struct psf1_font* font);
struct psf1_font* tty_get_font();

void tty_set_color(uint32_t color);
uint32_t tty_get_color();

void tty_set_position(uint32_t char_x, uint32_t char_y);
void tty_set_position_pixel(uint32_t x, uint32_t y);

void tty_putchar(char c);
void tty_print(const char* str);

#endif