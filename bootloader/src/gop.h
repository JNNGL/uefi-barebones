#ifndef BOOTLOADER_GOP_H
#define BOOTLOADER_GOP_H

#include <efi.h>
#include <efilib.h>

typedef struct framebuffer_s {
    void* buf_addr;
    uint64_t buf_size;
    uint32_t width;
    uint32_t height;
    uint32_t scanline;
    uint8_t bpp;
} framebuffer_t;

EFI_GRAPHICS_OUTPUT_PROTOCOL* locate_gop();
framebuffer_t* get_framebuffer(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop);

#endif