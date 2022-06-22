#ifndef KERNEL_INTERNAL_IDT_H
#define KERNEL_INTERNAL_IDT_H

#include <stdint.h>

#define IDT_TA_INTERRUPT_GATE 0b10001110
#define IDT_TA_CALL_GATE      0b10001100
#define IDT_TA_TRAP_GATE      0b10001111

typedef struct idt_desc_entry_s {
    uint16_t offset0;
    uint16_t selector;
    uint8_t ist;
    uint8_t type_attr;
    uint16_t offset1;
    uint32_t offset2;
    uint32_t ignore;
} idt_desc_entry_t;

void idt_desc_entry_set_offset(idt_desc_entry_t*, uint64_t offset);
uint64_t idt_desc_entry_get_offset(idt_desc_entry_t*);

typedef struct idtr_s {
    uint16_t limit;
    uint64_t offset;
} __attribute__((packed)) idtr_t;

#endif