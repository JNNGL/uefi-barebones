#ifndef KERNEL_INTERNAL_GDT_H
#define KERNEL_INTERNAL_GDT_H

#include <stdint.h>

typedef struct gdt_descriptor_s {
    uint16_t size;
    uint64_t offset;
} __attribute__((packed)) gdt_descriptor_t;

typedef struct gdt_entry_s {
    uint16_t limit0;
    uint16_t base0;
    uint8_t base1;
    uint8_t access_byte;
    uint8_t limit1_flags;
    uint8_t base2;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_s {
    gdt_entry_t null_descriptor;
    gdt_entry_t kernel_mode_code_segment;
    gdt_entry_t kernel_mode_data_segment;
    gdt_entry_t user_null;
    gdt_entry_t user_mode_code_segment;
    gdt_entry_t user_mode_data_segment;
} __attribute__((packed)) __attribute__((aligned(0x1000))) gdt_t;

extern gdt_t default_gdt;

void gdt_load(gdt_descriptor_t* gdt_descriptor);

#endif