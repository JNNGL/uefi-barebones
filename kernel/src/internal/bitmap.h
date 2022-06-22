#ifndef KERNEL_INTERNAL_BITMAP_H
#define KERNEL_INTERNAL_BITMAP_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct bitmap_s {
    size_t size;
    uint8_t* buf;
} bitmap_t;

bool bitmap_get(bitmap_t* bitmap, uint64_t index);
bool bitmap_set(bitmap_t* bitmap, uint64_t index, bool value);

#endif