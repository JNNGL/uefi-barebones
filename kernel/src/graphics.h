#pragma once

#include <stdint.h>

typedef struct framebuffer_s {
    void* buf_addr;
    uint64_t buf_size;
    uint32_t width;
    uint32_t height;
    uint32_t scanline;
    uint8_t bpp;
} framebuffer_t;