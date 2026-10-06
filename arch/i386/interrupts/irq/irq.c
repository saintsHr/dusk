#include "arch/i386/interrupts/irq/irq.h"
#include "arch/i386/interrupts/pic/pic.h"
#include "arch/i386/interrupts/idt/idt.h"
#include "lib/io/io.h"
#include "lib/std/stddef.h"

#define IRQ_INTERRUPT_COUNT 16
#define IRQ_BASE_VECTOR 32

extern void irq_0(void);
extern void irq_1(void);
extern void irq_2(void);
extern void irq_3(void);
extern void irq_4(void);
extern void irq_5(void);
extern void irq_6(void);
extern void irq_7(void);
extern void irq_8(void);
extern void irq_9(void);
extern void irq_10(void);
extern void irq_11(void);
extern void irq_12(void);
extern void irq_13(void);
extern void irq_14(void);
extern void irq_15(void);

static irq_routine_t irq_routines[IRQ_INTERRUPT_COUNT];

static void (*irq_stubs[IRQ_INTERRUPT_COUNT])(void) = {
    irq_0, irq_1, irq_2, irq_3, irq_4, irq_5, irq_6, irq_7,
    irq_8, irq_9, irq_10, irq_11, irq_12, irq_13, irq_14, irq_15
};

void irq_init(void) {
    for (int i = 0; i < IRQ_INTERRUPT_COUNT; i++) {
        idt_entry_t entry = idt_create_entry(
            (uintptr_t)irq_stubs[i],
            0x08, 0xE, 0x1, 0x0
        );

        idt_set_entry(entry, IRQ_BASE_VECTOR + i);
    }
}

void irq_install_routine(usize_t irq, irq_routine_t handler) {
    if (irq < IRQ_INTERRUPT_COUNT) irq_routines[irq] = handler;
}

void irq_uninstall_routine(usize_t irq) {
    if (irq < IRQ_INTERRUPT_COUNT) irq_routines[irq] = NULL;
}

void irq_handler(interrupt_context_t *ctx) {
    uint8_t irq = ctx->int_no - IRQ_BASE_VECTOR;

    if (irq == 7 || irq == 15) {
        if (!(pic_read_isr() & (1 << irq))) {
            if (irq == 15) io_outb(PIC1_CMD, PIC_EOI);
            return;
        }
    }

    if (irq < IRQ_INTERRUPT_COUNT && irq_routines[irq]) irq_routines[irq](ctx);

    pic_send_eoi(irq);
}
