section .multiboot
align 4

dd 0x1BADB002
dd (1<<0 | 1<<1)
dd -(0x1BADB002 + (1<<0 | 1<<1))

section .bss
align 16

stack_bottom:
resb 32768 ; 32 KB
stack_top:

section .text

global _start
extern kmain

data:
    %include "src/dusk/gdt.asm"

call_kernel:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    call kmain

_start:
    mov esp, stack_top    ; inits stack
    lgdt [gdt_descriptor] ; inits GDT

    jmp 0x08:call_kernel

    cli
hang:
    hlt
    jmp hang