[bits 64]

gdt_load:
    lgdt [rdi]
    mov ax, 0x10 ; kernel mode data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    pop rdi
    mov rax, 0x08 ; kernel mode code segment
    push rax
    push rdi
    retfq
    
GLOBAL gdt_load