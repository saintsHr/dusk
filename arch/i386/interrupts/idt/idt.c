#include "arch/i386/interrupts/idt/idt.h"
#include "arch/i386/interrupts/isr/isr.h"
#include "arch/i386/gdt/gdt.h"
#include "lib/std/stdint.h"

static idt_entry_t idt[IDT_ENTRIES] = {0};

idt_entry_t idt_create_entry(uintptr_t offset, uint16_t selector, uint8_t type, uint8_t present, uint8_t dpl) {
    idt_entry_t entry = {0};

    entry.offset_low = (uint16_t)(offset & 0x0000FFFF);
    entry.offset_high = (uint16_t)((offset & 0xFFFF0000) >> 16);
    entry.selector = selector;
    entry.reserved = 0x00;
    entry.p_dpl_type = (uint8_t)((type & 0xF) | ((dpl & 0x3) << 5) | ((present & 0x1) << 7));

    return entry;
}

idt_register_t idt_create_register(idt_entry_t *table, usize_t count) {
    idt_register_t reg = {0};

    reg.size = (uint16_t)(count * sizeof(idt_entry_t) - 1);
    reg.offset = (uint32_t)(uintptr_t)table;

    return reg;
}

void idt_set_entry(idt_entry_t entry, usize_t num) {
    if (num >= IDT_ENTRIES) return;
    idt[num] = entry;
}

void idt_set_register(idt_register_t reg) {
    __asm__ __volatile__ ("lidt %0" : : "m"(reg) : "memory");
}

void idt_init(void) {
    for (usize_t i = 0; i < ISR_EXCEPTIONS_COUNT; i++) {
        idt_entry_t entry = idt_create_entry(
            (uintptr_t)isr_stubs[i],
            GDT_KERNEL_CODE_INDEX * 8,
            0xE, 0x1, 0x0
        );

        idt_set_entry(entry, i);
    }

    idt_register_t reg = idt_create_register(idt, IDT_ENTRIES);
    idt_set_register(reg);
}
