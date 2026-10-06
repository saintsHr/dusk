#include "arch/i386/interrupts/isr/isr.h"
#include "arch/i386/interrupts/idt/idt.h"
#include "arch/i386/gdt/gdt.h"
#include "kernel/main.h"
#include "lib/std/stddef.h"

#define ISR_INTERRUPT_COUNT 32
#define ISR_ROUTINES_COUNT 256

extern void isr_0(void);
extern void isr_1(void);
extern void isr_2(void);
extern void isr_3(void);
extern void isr_4(void);
extern void isr_5(void);
extern void isr_6(void);
extern void isr_7(void);
extern void isr_8(void);
extern void isr_9(void);
extern void isr_10(void);
extern void isr_11(void);
extern void isr_12(void);
extern void isr_13(void);
extern void isr_14(void);
extern void isr_15(void);
extern void isr_16(void);
extern void isr_17(void);
extern void isr_18(void);
extern void isr_19(void);
extern void isr_20(void);
extern void isr_21(void);
extern void isr_22(void);
extern void isr_23(void);
extern void isr_24(void);
extern void isr_25(void);
extern void isr_26(void);
extern void isr_27(void);
extern void isr_28(void);
extern void isr_29(void);
extern void isr_30(void);
extern void isr_31(void);

static const char* isr_msg[ISR_INTERRUPT_COUNT] = {
    "[DE] Division Error.", "[DB] Debug Exception.", "[NMI] NMI Interrupt.",
    "[BP] Breakpoint.", "[OF] Overflow.", "[BR] BOUND Range Exceeded.",
    "[UD] Invalid Opcode.", "[NM] Device Not Available.", "[DF] Double Fault.",
    "[N/A] Reserved.", "[TS] Invalid TSS.", "[NP] Segment Not Present.",
    "[SS] Stack-Segment Fault.", "[GP] General Protection.", "[PF] Page Fault.",
    "[N/A] Reserved.", "[MF] x87 FPU Floating-Point Error.", "[AC] Alignment Check.",
    "[MC] Machine Check.", "[XM] SIMD Floating-Point Exception.",
    "[VE] Virtualization Exception.", "[CP] Control Protection Exception.",
    "[N/A] Reserved.", "[N/A] Reserved.", "[N/A] Reserved.", "[N/A] Reserved.",
    "[N/A] Reserved.", "[N/A] Reserved.", "[N/A] Reserved.", "[N/A] Reserved.",
    "[N/A] Reserved.", "[N/A] Reserved.",
};

static isr_routine_t isr_routines[ISR_ROUTINES_COUNT] = {NULL};

static void (*isr_stubs[ISR_INTERRUPT_COUNT])(void) = {
    isr_0, isr_1, isr_2, isr_3, isr_4, isr_5, isr_6, isr_7, isr_8, isr_9,
    isr_10, isr_11, isr_12, isr_13, isr_14, isr_15, isr_16, isr_17, isr_18,
    isr_19, isr_20, isr_21, isr_22, isr_23, isr_24, isr_25, isr_26, isr_27,
    isr_28, isr_29, isr_30, isr_31,
};

__attribute__((noreturn))
static void isr_panic(interrupt_context_t *ctx) {
    if (ctx->int_no < ISR_INTERRUPT_COUNT) {
        kernel_panic(isr_msg[ctx->int_no]);
    } else {
        kernel_panic("[N/A] Unknown.");
    }
}

void isr_init(void) {
    for (usize_t i = 0; i < ISR_INTERRUPT_COUNT; i++) {
        idt_entry_t entry = idt_create_entry(
            (uintptr_t)isr_stubs[i],
            GDT_KERNEL_CODE_INDEX * 8,
            0xE, 0x1, 0x0
        );

        idt_set_entry(entry, i);
    }
}

void isr_install_routine(usize_t index, isr_routine_t routine) {
    if (index < ISR_ROUTINES_COUNT) isr_routines[index] = routine;
}

void isr_uninstall_routine(usize_t index) {
    if (index < ISR_ROUTINES_COUNT) isr_routines[index] = NULL;
}

void isr_handler(interrupt_context_t *ctx) {
    if (ctx->int_no < ISR_ROUTINES_COUNT && isr_routines[ctx->int_no] != NULL) {
        isr_routines[ctx->int_no](ctx);
    } else {
        isr_panic(ctx);
    }
}
