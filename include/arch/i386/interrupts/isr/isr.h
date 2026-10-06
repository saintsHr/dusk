#ifndef DUSK_ARCH_I386_ISR_ISR_H
#define DUSK_ARCH_I386_ISR_ISR_H

#include "lib/std/stdint.h"

typedef struct {
    uint32_t gs;
    uint32_t fs;
    uint32_t es;
    uint32_t ds;

    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;

    uint32_t int_no;
    uint32_t err_code;

    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
} __attribute__((packed)) interrupt_context_t;

typedef void (*isr_routine_t)(interrupt_context_t *ctx);

void isr_init(void);

void isr_install_routine(usize_t index, isr_routine_t routine);
void isr_uninstall_routine(usize_t index);

void isr_handler(interrupt_context_t *ctx);

#endif
