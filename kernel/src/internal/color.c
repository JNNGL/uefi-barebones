#include "color.h"

color_argb_t color_argb(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
    color_argb_t color;
    color.a = a;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}

color_argb_t color_argb32(uint32_t argb) {
    color_argb_t color;
    color.argb = argb;
    return color;
}