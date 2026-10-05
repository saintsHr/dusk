#ifndef DUSK_ARCH_I386_ISR_ISR_H
#define DUSK_ARCH_I386_ISR_ISR_H

#include "lib/std/stdint.h"

#define ISR_EXCEPTIONS_COUNT 32
#define ISR_ROUTINES_COUNT 256

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
} __attribute__((packed)) isr_context_t;

typedef void (*isr_routine_t)(isr_context_t *ctx);

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

extern void (*isr_stubs[ISR_EXCEPTIONS_COUNT])(void);

void isr_register_routine(isr_routine_t routine, usize_t index);
void isr_handler(isr_context_t *ctx);

#endif
