#include "gop.h"

EFI_GRAPHICS_OUTPUT_PROTOCOL* locate_gop() {
    EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;
    EFI_GUID guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_STATUS status = uefi_call_wrapper(BS->LocateProtocol, 3, &guid, NULL, (void**)&gop);
    if(EFI_ERROR(status)) return NULL;
    return gop;
}

framebuffer_t tmp_fb;
framebuffer_t* get_framebuffer(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop) {
    if(!gop) return NULL;
    tmp_fb.buf_addr = (void*)gop->Mode->FrameBufferBase;
    tmp_fb.buf_size = gop->Mode->FrameBufferSize;
    tmp_fb.width = gop->Mode->Info->HorizontalResolution;
    tmp_fb.height = gop->Mode->Info->VerticalResolution;
    tmp_fb.scanline = gop->Mode->Info->PixelsPerScanLine;
    tmp_fb.bpp = 4;
    return &tmp_fb;
}