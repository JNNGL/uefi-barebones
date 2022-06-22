#include "idt.h"

void idt_desc_entry_set_offset(idt_desc_entry_t* e, uint64_t offset) {
    e->offset0 = (uint16_t)((offset & 0x000000000000FFFF));
    e->offset1 = (uint16_t)((offset & 0x00000000FFFF0000) >> 16);
    e->offset2 = (uint32_t)((offset & 0xFFFFFFFF00000000) >> 32);
}

uint64_t idt_desc_entry_get_offset(idt_desc_entry_t* e) {
    uint64_t offset = 0;
    offset |= (uint64_t)e->offset0;
    offset |= (uint64_t)e->offset1 << 16;
    offset |= (uint64_t)e->offset2 << 32;
    return offset;
}