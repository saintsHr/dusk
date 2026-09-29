#include "kernel/main.h"
#include "drivers/vga/vga.h"
#include "kernel/console/console.h"

__attribute__((noreturn))
static void kernel_hang() {
    __asm__ __volatile__ ("cli");
    while (true) __asm__ __volatile__ ("hlt");
}

void kernel_init(void) {
    vga_init();
    console_init();
}

__attribute__((noreturn))
void kernel_panic(const char* msg) {
    console_clear();
    console_move(0, 0);
    vga_set_cursor(false);

    console_move(0, 0);
    console_set_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
    console_write_string("Kernel Panic!");

    if (!(msg[0] == '\0')) {
        console_move(0, 2);
        console_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
        console_write_string("Message: ");

        console_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        console_write_string(msg);
    }

    kernel_hang();
}

__attribute__((noreturn))
void kernel_main(void) {
    kernel_init();
    kernel_panic("Kernel returned.");
}
