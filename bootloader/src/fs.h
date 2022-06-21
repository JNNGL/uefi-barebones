#ifndef BOOTLOADER_FS_H
#define BOOTLOADER_FS_H

#include <efi.h>
#include <efilib.h>

EFI_FILE* load_file(EFI_FILE* Directory, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable);

#endif