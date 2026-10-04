bits 32

section .text

%macro ISR_NO_ERR 1
    global isr_%1
    isr_%1:
        push dword 0
        push dword %1
        jmp isr_common
%endmacro

%macro ISR_ERR 1
    global isr_%1
    isr_%1:
        push dword %1
        jmp isr_common
%endmacro

%define KERNEL_DATA_SELECTOR 16

extern isr_handler

isr_common:
    pusha

    push ds
    push es
    push fs
    push gs

    mov ax, KERNEL_DATA_SELECTOR
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp
    call isr_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds

    popa
    add esp, 8
    iret

; used
ISR_NO_ERR 0
ISR_NO_ERR 1
ISR_NO_ERR 2
ISR_NO_ERR 3
ISR_NO_ERR 4
ISR_NO_ERR 5
ISR_NO_ERR 6
ISR_NO_ERR 7
ISR_ERR 8
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR_NO_ERR 16
ISR_ERR 17
ISR_NO_ERR 18
ISR_NO_ERR 19
ISR_NO_ERR 20
ISR_ERR 21

; reserved
ISR_NO_ERR 9
ISR_NO_ERR 15
ISR_NO_ERR 22
ISR_NO_ERR 23
ISR_NO_ERR 24
ISR_NO_ERR 25
ISR_NO_ERR 26
ISR_NO_ERR 27
ISR_NO_ERR 28
ISR_NO_ERR 29
ISR_NO_ERR 30
ISR_NO_ERR 31
