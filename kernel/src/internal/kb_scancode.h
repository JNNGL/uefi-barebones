#ifndef KERNEL_INTERNAL_KB_SCANCODE_H
#define KERNEL_INTERNAL_KB_SCANCODE_H

#include <stdint.h>
#include <stdbool.h>

extern const char ascii_table[];

#define KB_LEFT_SHIFT 0x2A
#define KB_RIGHT_SHIFT 0x36
#define KB_ENTER 0x1C
#define KB_BACKSPACE 0x0E
#define KB_SPACE 0x39

char kbtoa(uint8_t scancode, bool uppercase);

#endif