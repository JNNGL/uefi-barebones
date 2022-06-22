#include "graphics.h"

framebuffer_t* global_framebuffer;

void fb_set_framebuffer(framebuffer_t* framebuffer) {
    global_framebuffer = framebuffer;
}

framebuffer_t* fb_get_framebuffer() {
    return global_framebuffer;
}

void fb_set_pixel(uint32_t x, uint32_t y, uint32_t color) {
    if(!global_framebuffer) return;
    if(x < 0 || y < 0) return;
    if(x >= global_framebuffer->width 
    || y >= global_framebuffer->height) return;
    *(uint32_t*)(((y * global_framebuffer->scanline) + x) * global_framebuffer->bpp + global_framebuffer->buf_addr) = color;
}

void fb_fill_rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color) {
    for(uint32_t dy = y; dy < y + h; dy++) {
        for(uint32_t dx = x; dx < x + w; dx++) {
            fb_set_pixel(dx, dy, color);
        }
    }
}

void fb_clear(uint32_t color) {
    if(!global_framebuffer) return;
    fb_fill_rect(0, 0, global_framebuffer->width, global_framebuffer->height, color);
}