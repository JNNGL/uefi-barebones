#include "gdt.h"

__attribute__((aligned(0x1000)))
gdt_t default_gdt = {
    { 0, 0, 0, 0x00, 0x00, 0 },
    { 0, 0, 0, 0x9A, 0xA0, 0 },
    { 0, 0, 0, 0x92, 0xA0, 0 },
    { 0, 0, 0, 0x00, 0x00, 0 },
    { 0, 0, 0, 0x9A, 0xA0, 0 },
    { 0, 0, 0, 0x92, 0xA0, 0 }
};