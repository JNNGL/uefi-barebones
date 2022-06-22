#ifndef KERNEL_INTERNAL_PAGING_H
#define KERNEL_INTERNAL_PAGING_H

#include <stdint.h>
#include <stdbool.h>

typedef struct page_dir_entry_s {
    bool present : 1;
    bool rw : 1;
    bool user_super : 1;
    bool write_through : 1;
    bool cache_disabled : 1;
    bool accessed : 1;
    bool ignore0 : 1;
    bool larger_pages : 1;
    bool ignore1 : 1;
    uint8_t available : 3;
    uint64_t addr : 40;
    uint64_t unused : 12;
} page_dir_entry_t;

typedef struct page_table_s {
    page_dir_entry_t entries[512];
} __attribute__((aligned(0x1000))) page_table_t;

#endif