#ifndef KERNEL_INTERNAL_EFIMEM_H
#define KERNEL_INTERNAL_EFIMEM_H

#include <stdint.h>

typedef struct efi_memory_descriptor_s {
    uint32_t type;
    void* physical_addr;
    void* virtual_addr;
    uint64_t num_pages;
    uint64_t attribs;
} efi_memory_descriptor_t;

extern const char* efi_mem_type[];

#endif