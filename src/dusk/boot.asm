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

multiboot_ptr: resd 1
magic_number:  resd 1

section .data
    %include "src/dusk/gdt.asm"

section .text

global _start

extern kmain

extern _bss_start
extern _bss_end

_start:
    ; zeroes/resets the .bss section
    mov esi, ebx
    mov edx, eax

    xor eax, eax
    mov edi, _bss_start
    mov ecx, _bss_end
    sub ecx, edi
    shr ecx, 2
    rep stosd

    ; saves multiboot header & magic number
    mov [magic_number],  edx
    mov [multiboot_ptr], esi

    mov esp, stack_top    ; inits stack
    lgdt [gdt_descriptor] ; inits GDT

    ; calls the kernel
    jmp 0x08:call_kernel

call_kernel:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    push dword [magic_number]
    push dword [multiboot_ptr]

    call kmain

    cli
.hang:
    hlt
    jmp .hang