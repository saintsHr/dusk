#include "dusk/interrupts/idt.h"
#include "dusk/interrupts/pic.h"
#include "dusk/multiboot.h"
#include "dusk/memory/pmm.h"
#include "dusk/vga.h"
#include "dusk/serial.h"

#include <stddef.h>
#include <stdint.h>

void kpanic(const char* msg) {
    vga_cursor_disable();
    vga_clear();

    vga_set_color(VGA_COLOR_RED, VGA_COLOR_BLACK);
    vga_move(0, 0);
    vga_print("KERNEL PANIC");

    vga_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    vga_move(0, 2);
    vga_print("Reason: ");
    vga_print(msg);

    __asm__ volatile ("cli" ::: "memory");

    while (1) {
        __asm__ volatile ("hlt");
    }
}

void kinit(const struct multiboot_info* mbi) {
    __asm__ volatile ("cli");
    serial_init();
    idt_init();
    pic_remap(0x20, 0x28);
    pmm_init(mbi);
    __asm__ volatile ("sti");
}

void kmain(struct multiboot_info* mbi, uint32_t magic) {
    if (magic != 0x2BADB002) {
        kpanic("[Boot]: Invalid magic number.");
    }

    if (mbi == NULL || (uint32_t)mbi < 0x500) {
        kpanic("[Boot]: Invalid MBI provided.");
    }

    kinit(mbi);

    vga_move(31, 11);
    vga_set_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);

    vga_print("Hello, Kernel!");
    serial_print("Hello, Kernel!");

    while (1);
}