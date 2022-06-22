#ifndef KERNEL_INTERNAL_MEMORY_H
#define KERNEL_INTERNAL_MEMORY_H

#include <stdint.h>
#include "efimem.h"

uint64_t get_memory_size(efi_memory_descriptor_t* memory_map, uint64_t map_entries, uint64_t map_desc_size);

void memory_set(void* start, uint8_t value, uint64_t num);

#endif