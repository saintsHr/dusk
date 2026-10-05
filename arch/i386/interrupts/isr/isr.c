#include "arch/i386/interrupts/isr/isr.h"
#include "kernel/main.h"
#include "lib/std/stddef.h"

void (*isr_stubs[32])(void) = {
    isr_0, isr_1, isr_2, isr_3, isr_4, isr_5, isr_6, isr_7, isr_8, isr_9,
    isr_10, isr_11, isr_12, isr_13, isr_14, isr_15, isr_16, isr_17, isr_18,
    isr_19, isr_20, isr_21, isr_22, isr_23, isr_24, isr_25, isr_26, isr_27,
    isr_28, isr_29, isr_30, isr_31,
};

static const char* isr_msg[ISR_EXCEPTIONS_COUNT] = {
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

__attribute__((noreturn))
static void isr_panic(isr_context_t *ctx) {
    if (ctx->int_no < ISR_EXCEPTIONS_COUNT) {
        kernel_panic(isr_msg[ctx->int_no]);
    } else {
        kernel_panic("[N/A] Unknown.");
    }
}

void isr_register_routine(isr_routine_t routine, usize_t index) {
    if (index >= ISR_ROUTINES_COUNT) return;
    isr_routines[index] = routine;
}

void isr_handler(isr_context_t *ctx) {
    if (ctx->int_no < ISR_ROUTINES_COUNT && isr_routines[ctx->int_no] != NULL) {
        isr_routines[ctx->int_no](ctx);
    } else {
        isr_panic(ctx);
    }
}
