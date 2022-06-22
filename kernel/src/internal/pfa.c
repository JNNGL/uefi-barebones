#include "pfa.h"

static void pfa_unreserve_page(pfa_t* pfa, void* addr);
static void pfa_unreserve_pages(pfa_t* pfa, void* addr, uint64_t count);
static void pfa_reserve_page(pfa_t* pfa, void* addr);
static void pfa_reserve_pages(pfa_t* pfa, void* addr, uint64_t count);

uint64_t free_memory;
uint64_t reserved_memory;
uint64_t used_memory;
bool initialized = false;

static void pfa_init_bitmap(pfa_t* pfa, size_t bitmap_size, void* addr) {
    pfa->page_bitmap.size = bitmap_size;
    pfa->page_bitmap.buf = (uint8_t*)addr;
    for(int i = 0; i < bitmap_size; i++) {
        *(uint8_t*)(pfa->page_bitmap.buf + i) = 0; 
    }
}

void pfa_read_efi_memory_map(pfa_t* pfa, efi_memory_descriptor_t* memory_map, size_t map_size, size_t map_desc_size) {
    if(initialized) return;
    initialized = true;

    uint64_t map_entries = map_size / map_desc_size;
    void*  largest_free_mem_seg = NULL;
    size_t largest_free_mem_seg_size = 0;
    for(int i = 0; i < map_entries; i++) {
        efi_memory_descriptor_t* desc = (efi_memory_descriptor_t*)((uint64_t)memory_map + i * map_desc_size);
        if(desc->type == 7) {
            if(desc->num_pages * 4096 > largest_free_mem_seg_size) {
                largest_free_mem_seg = desc->physical_addr;
                largest_free_mem_seg_size = desc->num_pages * 4096;
            }
        }
    }
    uint64_t memory_size = get_memory_size(memory_map, map_entries, map_desc_size);
    free_memory = memory_size;
    uint64_t bitmap_size = memory_size / 4096 / 8 + 1;
    pfa_init_bitmap(pfa, bitmap_size, largest_free_mem_seg);
    pfa_lock_pages(pfa, &pfa->page_bitmap, pfa->page_bitmap.size / 4096 + 1);
    for(int i = 0; i < map_entries; i++) {
        efi_memory_descriptor_t* desc = (efi_memory_descriptor_t*)((uint64_t)memory_map + i * map_desc_size);
        if(desc->type != 7) {
            pfa_reserve_pages(pfa, desc->physical_addr, desc->num_pages);
        }
    }
}

uint64_t page_bitmap_idx;

void* pfa_request_page(pfa_t* pfa) {
    for(; page_bitmap_idx < pfa->page_bitmap.size * 8; page_bitmap_idx++) {
        if(bitmap_get(&pfa->page_bitmap, page_bitmap_idx)) continue;
        pfa_lock_page(pfa, (void*)(page_bitmap_idx * 4096));
        return (void*)(page_bitmap_idx * 4096);
    }
    return NULL;
}

void pfa_free_page(pfa_t* pfa, void* addr) {
    uint64_t idx = (uint64_t)addr / 4096;
    if(!bitmap_get(&pfa->page_bitmap, idx)) return;
    if(bitmap_set(&pfa->page_bitmap, idx, false)) {
        free_memory += 4096;
        used_memory -= 4096;
        if(page_bitmap_idx > idx) page_bitmap_idx = idx;
    }
}

void pfa_free_pages(pfa_t* pfa, void* addr, uint64_t count) {
    for(int i = 0; i < count; i++) {
        pfa_free_page(pfa, (void*)((uint64_t)addr + i * 4096));
    }
}

void pfa_lock_page(pfa_t* pfa, void* addr) {
    uint64_t idx = (uint64_t)addr / 4096;
    if(bitmap_get(&pfa->page_bitmap, idx)) return;
    if(bitmap_set(&pfa->page_bitmap, idx, true)) {
        free_memory -= 4096;
        used_memory += 4096;
    }
}

void pfa_lock_pages(pfa_t* pfa, void* addr, uint64_t count) {
    for(int i = 0; i < count; i++) {
        pfa_lock_page(pfa, (void*)((uint64_t)addr + i * 4096));
    }
}

static void pfa_unreserve_page(pfa_t* pfa, void* addr) {
    uint64_t idx = (uint64_t)addr / 4096;
    if(!bitmap_get(&pfa->page_bitmap, idx)) return;
    if(bitmap_set(&pfa->page_bitmap, idx, false)) {
        free_memory += 4096;
        reserved_memory -= 4096;
        if(page_bitmap_idx > idx) page_bitmap_idx = idx;
    }
}

static void pfa_unreserve_pages(pfa_t* pfa, void* addr, uint64_t count) {
    for(int i = 0; i < count; i++) {
        pfa_unreserve_page(pfa, (void*)((uint64_t)addr + i * 4096));
    }
}

static void pfa_reserve_page(pfa_t* pfa, void* addr) {
    uint64_t idx = (uint64_t)addr / 4096;
    if(bitmap_get(&pfa->page_bitmap, idx)) return;
    if(bitmap_set(&pfa->page_bitmap, idx, true)) {
        free_memory -= 4096;
        reserved_memory += 4096;
    }
}

static void pfa_reserve_pages(pfa_t* pfa, void* addr, uint64_t count) {
    for(int i = 0; i < count; i++) {
        pfa_reserve_page(pfa, (void*)((uint64_t)addr + i * 4096));
    }
}

uint64_t pfa_get_free_ram() {
    return free_memory;
}

uint64_t pfa_get_used_ram() {
    return used_memory;
}

uint64_t pfa_get_reserved_ram() {
    return reserved_memory;
}

pfa_t global_allocator;