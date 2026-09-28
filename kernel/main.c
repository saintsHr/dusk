#include "kernel/main.h"
#include "drivers/vga/vga.h"

__attribute__((noreturn))
void kernel_main() {
    vga_set_cell(
        vga_make_cell(
            vga_make_attr(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK), 'A'
        ),
        vga_make_index(0, 0)
    );

    while (1) __asm__ __volatile__ ("hlt");
}
