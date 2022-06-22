#include "pmi.h"

void pmi_init(pmi_t* pmi, uint64_t virt_addr) {
    virt_addr >>= 12;
    pmi->p_i = virt_addr & 0x1FF;
    virt_addr >>= 9;
    pmi->pt_i = virt_addr & 0x1FF;
    virt_addr >>= 9;
    pmi->pd_i = virt_addr & 0x1FF;
    virt_addr >>= 9;
    pmi->pdp_i = virt_addr & 0x1FF;

}