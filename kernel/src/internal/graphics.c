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