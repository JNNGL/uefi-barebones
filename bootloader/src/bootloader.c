#include <efi.h>
#include <efilib.h>

#include "gop.h"

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {
    InitializeLib(ImageHandle, SystemTable);
    
    EFI_GRAPHICS_OUTPUT_PROTOCOL* gop = locate_gop();
    if(!gop) { 
        Print(L"Unable to locate Graphics Output Protocol\n\r");
        return -1;
    }

    framebuffer_t* framebuffer = get_framebuffer(gop);
    if(!framebuffer) {
        Print(L"Unable to create framebuffer\n\r");
        return -1;
    }

    for(uint32_t y = 0; y < framebuffer->height; y++) {
        for(uint32_t x = 0; x < framebuffer->width; x++) {
            *(uint32_t*)(framebuffer->buf_addr + (y * framebuffer->bpp * framebuffer->scanline) + x * framebuffer->bpp) = 
                0xff000000 | ((uint8_t)(((float)x / framebuffer->width) * 0xff)) << 16 | ((uint8_t)(((float)y / framebuffer->height) * 0xff)) << 8;
        }
    }

    return EFI_SUCCESS;
}