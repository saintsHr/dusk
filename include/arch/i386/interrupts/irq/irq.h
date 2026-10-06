#ifndef DUSK_ARCH_I386_IRQ_IRQ_H
#define DUSK_ARCH_I386_IRQ_IRQ_H

#include "arch/i386/interrupts/isr/isr.h"
#include "lib/std/stdint.h"

typedef void (*irq_routine_t)(interrupt_context_t *ctx);

void irq_init(void);

void irq_install_routine(usize_t index, irq_routine_t handler);
void irq_uninstall_routine(usize_t index);

void irq_handler(interrupt_context_t *ctx);

#endif
