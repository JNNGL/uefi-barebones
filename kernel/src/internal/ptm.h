#ifndef KERNEL_INTERNAL_PTM_H
#define KERNEL_INTERNAL_PTM_H

#include "paging.h"

typedef struct ptm_s {
    page_table_t* pml4_addr;
} ptm_t;

void ptm_init(ptm_t* ptm, page_table_t* pml4_addr);
void ptm_map_memory(ptm_t* ptm, void* virt_mem, void* phys_mem);

#endif