#include "internal/graphics.h"
#include "internal/tty.h"
#include "internal/color.h"
#include "internal/string.h"
#include "internal/gdt.h"
#include "internal/efimem.h"
#include "internal/memory.h"
#include "internal/bitmap.h"
#include "internal/pfa.h"
#include "internal/paging.h"
#include "internal/pmi.h"
#include "internal/ptm.h"

extern uint64_t _kernel_start;
extern uint64_t _kernel_end;

typedef struct boot_info_s {
    efi_memory_descriptor_t* memory_map;
    uint64_t memory_map_size;
    uint64_t memory_map_desc_size;
    framebuffer_t* framebuffer;
    struct psf1_font* font;
} boot_info_t;

typedef struct kernel_info_s {
    ptm_t* ptm;
} kernel_info_t;



ptm_t global_ptm;
kernel_info_t kernel_init(boot_info_t* info) {
    kernel_info_t output;

    gdt_descriptor_t descriptor;
    descriptor.size = sizeof(struct gdt_s) - 1;
    descriptor.offset = (uint64_t)&default_gdt;
    gdt_load(&descriptor);

    {
        uint64_t memmap_entries = info->memory_map_size / info->memory_map_desc_size;

        pfa_read_efi_memory_map(&global_allocator, info->memory_map, info->memory_map_size, info->memory_map_desc_size);
        
        uint64_t kernel_size = (uint64_t)&_kernel_end - (uint64_t)&_kernel_start;
        uint64_t kernel_pages = (uint64_t)kernel_size / 4096 + 1;

        pfa_lock_pages(&global_allocator, &_kernel_start, kernel_pages);

        page_table_t* pml4 = (page_table_t*)pfa_request_page(&global_allocator);
        memory_set(pml4, 0, 0x1000);

        ptm_init(&global_ptm, pml4);

        for(uint64_t i = 0; i < get_memory_size(info->memory_map, memmap_entries, info->memory_map_desc_size); i += 0x1000) {
            ptm_map_memory(&global_ptm, (void*)i, (void*)i);
        }

        uint64_t fb_base = (uint64_t)info->framebuffer->buf_addr;
        uint64_t fb_size = (uint64_t)info->framebuffer->buf_size + 0x1000;
        pfa_lock_pages(&global_allocator, (void*)fb_base, fb_size / 0x10000 + 1);
        for(uint64_t i = fb_base; i < fb_base + fb_size; i += 4096) {
            ptm_map_memory(&global_ptm, (void*)i, (void*)i);
        }

        asm("mov %0, %%cr3" : : "r" (pml4));
        memory_set(info->framebuffer->buf_addr, 0, info->framebuffer->buf_size);

        output.ptm = &global_ptm;
    }

    return output;
}




void fill_block(int x, int y, int cid) {
    color_argb_t color;
    switch (cid)
    {
    case 1:  { color = VGA_BLUE; break; }
    case 2:  { color = VGA_GREEN; break; }
    case 3:  { color = VGA_CYAN; break; }
    case 4:  { color = VGA_RED; break; }
    case 5:  { color = VGA_VIOLET; break; }
    case 6:  { color = VGA_YELLOW; break; }
    case 7:  { color = VGA_WHITE; break; }
    case 8:  { color = VGA_GREY; break; }
    case 9:  { color = VGA_LIGHT_BLUE; break; }
    case 10: { color = VGA_LIGHT_GREEN; break; }
    case 11: { color = VGA_LIGHT_CYAN; break; }
    case 12: { color = VGA_LIGHT_RED; break; }
    case 13: { color = VGA_LIGHT_VIOLET; break; }
    case 14: { color = VGA_LIGHT_YELLOW; break; }
    case 15: { color = VGA_BRIGHT_WHITE; break; }
    case 0:
    default: { color = VGA_BLACK; break; }
    }
    for(int dx = x; dx < x+50; dx++) {
        for(int dy = y; dy < y+25; dy++) {
            fb_set_pixel(dx, dy, color.argb);
        }
    }
}

uint8_t buffer[20];
void kernel_main(boot_info_t* info) {
    fb_set_framebuffer(info->framebuffer);
    tty_set_font(info->font);

    kernel_info_t kernel = kernel_init(info);

    for(int x = 0; x < 8; x++) {
        for(int y = 0; y < 2; y++) {
            int cid = y * 8 + x;
            fill_block(x*50+300, y*25, cid);
        }
    }

    while(1);
}

