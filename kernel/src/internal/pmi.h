#ifndef KERNEL_INTERNAL_PMI_H
#define KERNEL_INTERNAL_PMI_H

#include <stdint.h>

typedef struct pmi_s {
    uint64_t pdp_i;
    uint64_t pd_i;
    uint64_t pt_i;
    uint64_t p_i;
} pmi_t;

void pmi_init(pmi_t* pmi, uint64_t virt_addr);

#endif