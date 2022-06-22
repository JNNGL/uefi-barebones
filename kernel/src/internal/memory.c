#include "memory.h"

uint64_t get_memory_size(efi_memory_descriptor_t* memory_map, uint64_t map_entries, uint64_t map_desc_size) {
    static uint64_t memory_size = 0;
    if(memory_size > 0) return memory_size;
    for(int i = 0; i < map_entries; i++) {
        efi_memory_descriptor_t* desc = (efi_memory_descriptor_t*)((uint64_t)memory_map + i * map_desc_size);
        memory_size += desc->num_pages * 4096;
    }
    return memory_size;
}

void memory_set(void* start, uint8_t value, uint64_t num) {
    for(uint64_t i = 0; i < num; i++) {
        *(uint8_t*)((uint64_t)start + i) = value;
    }
}