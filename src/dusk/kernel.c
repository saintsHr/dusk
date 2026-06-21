#include "dusk/vga.h"

void kmain(void) {
    vga_move(32, 11);
    vga_set_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);

    vga_print("Hello, Kernel!");

    while (1);
}