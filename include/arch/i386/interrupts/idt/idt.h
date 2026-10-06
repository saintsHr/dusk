#ifndef DUSK_ARCH_I386_IDT_IDT_H
#define DUSK_ARCH_I386_IDT_IDT_H

#include "lib/std/stdint.h"

typedef struct {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t reserved;
    uint8_t p_dpl_type;
    uint16_t offset_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) idt_register_t;

idt_entry_t idt_create_entry(uintptr_t offset, uint16_t selector, uint8_t type, uint8_t present, uint8_t dpl);
idt_register_t idt_create_register(idt_entry_t *table, usize_t count);

void idt_set_entry(idt_entry_t entry, usize_t num);
void idt_set_register(idt_register_t reg);

void idt_init(void);

#endif
