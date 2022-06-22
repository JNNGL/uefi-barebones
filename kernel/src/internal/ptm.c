#include <stdint.h>
#include "ptm.h"
#include "pmi.h"
#include "pfa.h"
#include "memory.h"

void ptm_init(ptm_t* ptm, page_table_t* pml4_addr) {
    ptm->pml4_addr = pml4_addr;
}

void ptm_map_memory(ptm_t* ptm, void* virt_mem, void* phys_mem) {
    pmi_t indexer;
    pmi_init(&indexer, (uint64_t)virt_mem);
    page_dir_entry_t pde;
    
    pde = ptm->pml4_addr->entries[indexer.pdp_i];
    page_table_t* pdp;
    if(!pde.present) {
        pdp = (page_table_t*)pfa_request_page(&global_allocator);
        memory_set(pdp, 0, 0x1000);
        pde.addr = (uint64_t)pdp >> 12;
        pde.present = true;
        pde.rw = true;
        ptm->pml4_addr->entries[indexer.pdp_i] = pde;
    } else {
        pdp = (page_table_t*)((uint64_t)pde.addr << 12);
    }

    pde = pdp->entries[indexer.pd_i];
    page_table_t* pd;
    if(!pde.present) {
        pd = (page_table_t*)pfa_request_page(&global_allocator);
        memory_set(pd, 0, 0x1000);
        pde.addr = (uint64_t)pd >> 12;
        pde.present = true;
        pde.rw = true;
        pdp->entries[indexer.pd_i] = pde;
    } else {
        pd = (page_table_t*)((uint64_t)pde.addr << 12);
    }

    pde = pd->entries[indexer.pt_i];
    page_table_t* pt;
    if(!pde.present) {
        pt = (page_table_t*)pfa_request_page(&global_allocator);
        memory_set(pt, 0, 0x1000);
        pde.addr = (uint64_t)pt >> 12;
        pde.present = true;
        pde.rw = true;
        pd->entries[indexer.pt_i] = pde;
    } else {
        pt = (page_table_t*)((uint64_t)pde.addr << 12);
    }

    pde = pt->entries[indexer.p_i];
    pde.addr = (uint64_t)phys_mem >> 12;
    pde.present = true;
    pde.rw = true;
    pt->entries[indexer.p_i] = pde;

}