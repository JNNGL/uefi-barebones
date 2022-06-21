#include "graphics.h"

void kernel_main(framebuffer_t* screen) {
    for(uint32_t y = 50; y < 200; y++) {
        for(uint32_t x = 50; x < 200; x++) {
            *(uint32_t*)(screen->buf_addr + (y * screen->bpp * screen->scanline) + x * screen->bpp) = 
                (uint32_t)(x*screen->scanline+y);
        }
    }
    while(1);
}

