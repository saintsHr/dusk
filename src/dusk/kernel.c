#include "dusk/vga.h"
#include "dusk/serial.h"

void kinit(void) {
    serial_init();
}

void kmain(void) {
    kinit();

    vga_move(31, 11);
    vga_set_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);

    vga_print("Hello, Kernel!");
    serial_print("Hello, Kernel!");

    while (1);
}