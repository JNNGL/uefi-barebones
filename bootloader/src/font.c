#include "font.h"

struct psf1_font* load_font(EFI_FILE* file) {
    if(!file) return NULL;
    struct psf1_header* header;
    UINTN size = sizeof(struct psf1_header);
    ST->BootServices->AllocatePool(EfiLoaderData, size, (void**)&header);
    file->Read(file, &size, header);
    if(header->magic[0] != PSF1_MAGIC0 
    || header->magic[1] != PSF1_MAGIC1) return NULL;
    UINTN buf_size = header->charsize * 256;
    if(header->mode == PSF1_MODE512) buf_size *= 2;
    void* buf;
    file->SetPosition(file, sizeof(struct psf1_header));
    ST->BootServices->AllocatePool(EfiLoaderData, buf_size, (void**)&buf);
    file->Read(file, &buf_size, buf);
    struct psf1_font* font;
    ST->BootServices->AllocatePool(EfiLoaderData, sizeof(struct psf1_font), (void**)&font);
    font->header = header;
    font->buf = buf;
    return font;
}