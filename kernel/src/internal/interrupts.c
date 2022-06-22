#include "interrupts.h"
#include "tty.h"
#include "panic.h"
#include "io.h"
#include "kb_scancode.h"
#include "kb.h"

__attribute__((interrupt)) void page_fault_handler(struct interrupt_frame* frame) {
    panic("page fault\n");
    while(1);
}

__attribute__((interrupt)) void double_fault_handler(struct interrupt_frame* frame) {
    panic("double fault\n");
    while(1);
}

__attribute__((interrupt)) void gp_fault_handler(struct interrupt_frame* frame) {
    panic("general protection fault\n");
    while(1);
}

__attribute__((interrupt)) void kb_interrupt_handler(struct interrupt_frame* frame) {
    uint8_t scancode = inb(0x60);
    kb_input(scancode);
    pic_end_master();
}

void pic_end_master() {
    outb(PIC1_COMMAND, PIC_EOI);
}

void pic_end_slave() {
    outb(PIC2_COMMAND, PIC_EOI);
    outb(PIC1_COMMAND, PIC_EOI);
}

void remap_pic() {
    uint8_t a1, a2;

    a1 = inb(PIC1_DATA);
    io_wait();
    a2 = inb(PIC2_DATA);
    io_wait();

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    outb(PIC1_DATA, 0x20);
    io_wait();
    outb(PIC2_DATA, 0x28);
    io_wait();

    outb(PIC1_DATA, 4);
    io_wait();
    outb(PIC2_DATA, 2);
    io_wait();

    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, a1);
    io_wait();
    outb(PIC2_DATA, a2);
    io_wait();
}