#include "kernel/main.h"
#include "kernel/console/console.h"
#include "drivers/vga/vga.h"
#include "lib/std/stddef.h"

__attribute__((noreturn))
static void kernel_hang() {
    while (true) __asm__ __volatile__ ("hlt");
}

void kernel_init(void) {
    vga_init();
    console_init();

    console_move(0, 0);
    console_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    console_write_string("Welcome to ");
    console_set_color(VGA_COLOR_MAGENTA, VGA_COLOR_BLACK);
    console_write_string("Dusk");
    console_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    console_write_string("!");
    console_move(0, 2);
}

__attribute__((noreturn))
void kernel_panic(const char* msg) {
    console_clear();
    console_move(0, 0);
    vga_set_cursor(false);

    console_set_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
    console_write_string("Kernel Panic!");

    console_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    console_write_string("\n\nMessage: ");
    console_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    if (msg != NULL) {
        console_write_string(msg);
    } else {
        console_write_string("N/A");
    }

    kernel_hang();
}

__attribute__((noreturn))
void kernel_main(void) {
    kernel_init();

    while (true) {

    }

    kernel_panic("Kernel returned.");
}
