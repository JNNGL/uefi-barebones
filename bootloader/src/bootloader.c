#include <efi.h>
#include <efilib.h>

#include "gop.h"
#include "kernel.h"
#include "fs.h"
#include "font.h"

typedef struct boot_info_s {
    EFI_MEMORY_DESCRIPTOR* memory_map;
    UINTN memory_map_size;
    UINTN memory_map_desc_size;
    framebuffer_t* framebuffer;
    struct psf1_font* font;
} boot_info_t;

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {
    InitializeLib(ImageHandle, SystemTable);

    Elf64_Ehdr header;
    if(!load_kernel(load_file(NULL, L"kernel.elf", ImageHandle, SystemTable), &header)) {
        Print(L"Unable to load kernel");
        return -1;
    }

    void(*kernel_main)(boot_info_t*) = ((__attribute__((sysv_abi))void(*)(boot_info_t*))header.e_entry);

    EFI_GRAPHICS_OUTPUT_PROTOCOL* gop = locate_gop();
    if(!gop) { 
        Print(L"Unable to locate Graphics Output Protocol\n\r");
        return -1;
    }

    framebuffer_t* screen = get_framebuffer(gop);
    if(!screen) {
        Print(L"Unable to create framebuffer\n\r");
        return -1;
    }

    EFI_FILE* font_file = load_file(NULL, L"zap-ext-vga16.psf", ImageHandle, SystemTable);
    if(!font_file) {
        Print(L"Unable to load font\n\r");
        return -1;
    }

    struct psf1_font* font = load_font(font_file);
    if(!font) {
        Print(L"Invalid font file\n\r");
        return -1;
    }

    EFI_MEMORY_DESCRIPTOR* map;
    UINTN map_size;
    UINTN map_key;
    UINTN descriptor_size;
    UINT32 descriptor_version;
    ST->BootServices->GetMemoryMap(&map_size, map, &map_key, &descriptor_size, &descriptor_version);
    ST->BootServices->AllocatePool(EfiLoaderData, map_size, (void**)&map);
    ST->BootServices->GetMemoryMap(&map_size, map, &map_key, &descriptor_size, &descriptor_version);

    boot_info_t boot_info;
    boot_info.memory_map = map;
    boot_info.memory_map_size = map_size;
    boot_info.memory_map_desc_size = descriptor_size;
    boot_info.framebuffer = screen;
    boot_info.font = font;

    ST->BootServices->ExitBootServices(ImageHandle, map_key);
    
    kernel_main(&boot_info);

    return EFI_SUCCESS;
}