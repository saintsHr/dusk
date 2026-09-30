#include "arch/i386/gdt/gdt.h"

static gdt_entry_t gdt[GDT_ENTRIES];

gdt_entry_t gdt_create_entry(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    gdt_entry_t entry = {0};

    entry.base_low = (uint16_t)base;
    entry.base_mid = (uint8_t)(base >> 16);
    entry.base_high = (uint8_t)(base >> 24);

    entry.limit_low = (uint16_t)limit;

    uint8_t flags_nibble = (uint8_t)((flags & 0x0F) << 4);
    uint8_t limit_nibble = (uint8_t)(limit >> 16) & 0x0F;
    entry.flags_limit_high = (uint8_t)(flags_nibble | limit_nibble);

    entry.access = access;

    return entry;
}

gdt_register_t gdt_create_register(gdt_entry_t *table, usize_t size) {
    gdt_register_t reg = {0};

    reg.size = (uint16_t)(size * sizeof(gdt_entry_t) - 1);
    reg.offset = (uint32_t)table;

    return reg;
}

void gdt_set_entry(gdt_entry_t entry, usize_t num) {
    if (num >= GDT_ENTRIES) return;
    gdt[num] = entry;
}

void gdt_set_register(gdt_register_t reg) {
    __asm__ __volatile__ ("lgdt %0" : : "m"(reg) : "memory");
    gdt_flush();
}

void gdt_init(void) {
    gdt_entry_t null = gdt_create_entry(0x00000000, 0x00000000, 0x00, 0x00);
    gdt_entry_t kernel_code = gdt_create_entry(0x00000000, 0xFFFFF, 0x9B, 0xC);
    gdt_entry_t kernel_data = gdt_create_entry(0x00000000, 0xFFFFF, 0x93, 0xC);
    gdt_entry_t user_code = gdt_create_entry(0x00000000, 0xFFFFF, 0xFB, 0xC);
    gdt_entry_t user_data = gdt_create_entry(0x00000000, 0xFFFFF, 0xF3, 0xC);

    gdt_set_entry(null, 0);
    gdt_set_entry(kernel_code, 1);
    gdt_set_entry(kernel_data, 2);
    gdt_set_entry(user_code, 3);
    gdt_set_entry(user_data, 4);

    gdt_register_t reg = gdt_create_register(gdt, GDT_ENTRIES);

    gdt_set_register(reg);
}
