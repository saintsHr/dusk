#include "kernel/main.h"
#include "drivers/vga/vga.h"
#include "kernel/console/console.h"

void kernel_init(void) {
    vga_init();
    console_init();
}

__attribute__((noreturn))
void kernel_main(void) {
    kernel_init();
    while (true) __asm__ __volatile__ ("hlt");
}
