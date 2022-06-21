#include <efi.h>
#include <efilib.h>

#include "gop.h"
#include "kernel.h"
#include "fs.h"

EFI_FILE* LoadFile(EFI_FILE* Directory, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {
	EFI_FILE* LoadedFile;
	EFI_LOADED_IMAGE_PROTOCOL* LoadedImage;
	SystemTable->BootServices->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, (void**)&LoadedImage);
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileSystem;
	SystemTable->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (void**)&FileSystem);
	if(Directory == NULL) {
		FileSystem->OpenVolume(FileSystem, &Directory);
	}
	EFI_STATUS s = Directory->Open(Directory, &LoadedFile, Path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
	if(s != EFI_SUCCESS) return NULL;
	return LoadedFile;
}

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

    Elf64_Ehdr header;
    if(!load_kernel(LoadFile(NULL, L"kernel.elf", ImageHandle, SystemTable), &header)) {
        Print(L"Unable to load kernel");
        return -1;
    }

    void(*kernel_main)(framebuffer_t*) = ((__attribute__((sysv_abi))void(*)(framebuffer_t*))header.e_entry);
    kernel_main(framebuffer);

    return EFI_SUCCESS;
}