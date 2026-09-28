#include "kernel/main.h"
#include "drivers/vga/vga.h"

void kernel_init(void) {
    vga_enable_cursor();
    vga_move_cursor(vga_make_index(0, 0));
}

__attribute__((noreturn))
void kernel_main(void) {
    kernel_init();
    while (1) __asm__ __volatile__ ("hlt");
}
