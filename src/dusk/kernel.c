#include "dusk/interrupts/idt.h"
#include "dusk/interrupts/pic.h"
#include "dusk/vga.h"
#include "dusk/serial.h"

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

void kinit(void) {
    __asm__ volatile ("cli");
    serial_init();
    idt_init();
    pic_remap(0x20, 0x28);
    __asm__ volatile ("sti");
}

void kmain(void) {
    kinit();

    vga_move(31, 11);
    vga_set_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);

    vga_print("Hello, Kernel!");
    serial_print("Hello, Kernel!");

    while (1);
}