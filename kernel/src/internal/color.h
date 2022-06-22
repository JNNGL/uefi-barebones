#ifndef KERNEL_INTERNAL_COLOR_H
#define KERNEL_INTERNAL_COLOR_H

#include <stdint.h>

typedef union color_argb_s {
    struct {
        uint32_t b : 8;
        uint32_t g : 8;
        uint32_t r : 8;
        uint32_t a : 8;
    };
    uint32_t argb;
} color_argb_t;

color_argb_t color_argb(uint8_t a, uint8_t r, uint8_t g, uint8_t b);
#define color_rgb(r, g, b) color_argb(0xff, r, g, b)

color_argb_t color_argb32(uint32_t argb);
#define color_rgb32(rgb) color_argb32(rgb & 0x00FFFFFF)

#define VGA_BLACK        (color_rgb(0x00, 0x00, 0x00))
#define VGA_BLUE         (color_rgb(0x00, 0x00, 0xff))
#define VGA_GREEN        (color_rgb(0x00, 0xff, 0x00))
#define VGA_CYAN         (color_rgb(0x00, 0xff, 0xff))
#define VGA_RED          (color_rgb(0xff, 0x00, 0x00))
#define VGA_VIOLET       (color_rgb(0xff, 0x00, 0xff))
#define VGA_YELLOW       (color_rgb(0xff, 0xff, 0x00))
#define VGA_WHITE        (color_rgb(0xff, 0xff, 0xff))
#define VGA_GREY         (color_rgb(0x80, 0x80, 0x80))
#define VGA_LIGHT_BLUE   (color_rgb(0x80, 0x80, 0xff))
#define VGA_LIGHT_GREEN  (color_rgb(0x80, 0xff, 0x80))
#define VGA_LIGHT_CYAN   (color_rgb(0x80, 0xff, 0xff))
#define VGA_LIGHT_RED    (color_rgb(0xff, 0x80, 0x80))
#define VGA_LIGHT_VIOLET (color_rgb(0xff, 0x80, 0xff))
#define VGA_LIGHT_YELLOW (color_rgb(0xff, 0xff, 0x80))
#define VGA_BRIGHT_WHITE (color_rgb(0xff, 0xff, 0xff))

#endif