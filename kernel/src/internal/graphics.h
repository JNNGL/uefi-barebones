#ifndef KERNEL_INTERNAL_GRAPHICS_H
#define KERNEL_INTERNAL_GRAPHICS_H

#include <stdint.h>

typedef struct framebuffer_s {
    void* buf_addr;
    uint64_t buf_size;
    uint32_t width;
    uint32_t height;
    uint32_t scanline;
    uint8_t bpp;
} framebuffer_t;

void fb_set_framebuffer(framebuffer_t* framebuffer);
framebuffer_t* fb_get_framebuffer();

void fb_set_pixel(uint32_t x, uint32_t y, uint32_t color);

#endif