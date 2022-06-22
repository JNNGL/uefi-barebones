#include "bitmap.h"

bool bitmap_get(bitmap_t* bitmap, uint64_t index) {
    if(index > bitmap->size * 8) return false;
    return bitmap->buf[index / 8] & (128 >> (index % 8));
}

bool bitmap_set(bitmap_t* bitmap, uint64_t index, bool value) {
    if(index > bitmap->size * 8) return false;
    if(value) bitmap->buf[index / 8] |= (128 >> (index % 8));
    else bitmap->buf[index / 8] &= ~(128 >> (index % 8));
    return true;
}