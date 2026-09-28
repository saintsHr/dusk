#include "main.h"

__attribute__((noreturn))
void kernel_main() {
    while (1) __asm__ __volatile__ ("hlt");
}
