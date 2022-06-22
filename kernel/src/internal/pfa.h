#ifndef KERNEL_INTERNAL_PFA_H
#define KERNEL_INTERNAL_PFA_H

#include <stdint.h>
#include "efimem.h"
#include "memory.h"
#include "bitmap.h"

typedef struct pfa_s {
    bitmap_t page_bitmap;
} pfa_t;

void pfa_read_efi_memory_map(pfa_t* pfa, efi_memory_descriptor_t* memory_map, size_t map_size, size_t map_desc_size);
void pfa_free_page(pfa_t* pfa, void* addr);
void pfa_lock_page(pfa_t* pfa, void* addr);
void* pfa_request_page(pfa_t* pfa);

void pfa_free_pages(pfa_t* pfa, void* addr, uint64_t count);
void pfa_lock_pages(pfa_t* pfa, void* addr, uint64_t count);

uint64_t pfa_get_free_ram();
uint64_t pfa_get_used_ram();
uint64_t pfa_get_reserved_ram();

extern pfa_t global_allocator;

#endif