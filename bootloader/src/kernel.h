#ifndef BOOTLOADER_KERNEL_H
#define BOOTLOADER_KERNEL_H

#include <elf.h>
#include <efi.h>
#include <efilib.h>

uint8_t load_kernel(EFI_FILE* file, Elf64_Ehdr* dst);

#endif