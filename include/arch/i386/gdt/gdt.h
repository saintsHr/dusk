#ifndef DUSK_ARCH_I386_GDT_GDT_H
#define DUSK_ARCH_I386_GDT_GDT_H

#include "lib/std/stdint.h"

#define GDT_ENTRIES 5

typedef struct {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t flags_limit_high;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct {
    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) gdt_register_t;

extern void gdt_flush(void);

gdt_entry_t gdt_create_entry(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
gdt_register_t gdt_create_register(gdt_entry_t* table, usize_t size);

void gdt_set_entry(gdt_entry_t entry, usize_t num);
void gdt_set_register(gdt_register_t reg);

void gdt_init(void);

#endif
