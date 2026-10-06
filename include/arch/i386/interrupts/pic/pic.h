#ifndef DUSK_ARCH_I386_PIC_PIC_H
#define DUSK_ARCH_I386_PIC_PIC_H

#include "lib/std/stdint.h"

#define PIC1_CMD 0x20
#define PIC1_DATA 0x21
#define PIC2_CMD 0xA0
#define PIC2_DATA 0xA1

#define PIC_EOI 0x20

void pic_init(void);

void pic_send_eoi(uint8_t irq);

void pic_mask(uint8_t irq);
void pic_unmask(uint8_t irq);

void pic_mask_all(void);
void pic_unmask_all(void);

uint16_t pic_read_isr(void);

#endif
