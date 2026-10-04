bits 32

global flush_seg_regs

section .text

flush_seg_regs:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:.flush

    .flush:
        ret
