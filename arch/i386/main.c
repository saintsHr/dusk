#include "arch/i386/interrupts/idt/idt.h"
#include "arch/i386/interrupts/irq/irq.h"
#include "arch/i386/interrupts/isr/isr.h"
#include "arch/i386/interrupts/pic/pic.h"
#include "arch/i386/gdt/gdt.h"
#include "kernel/main.h"

void i386_init(void) {
    __asm__ __volatile__ ("cli");

    gdt_init();
    isr_init();
    irq_init();
    idt_init();
    pic_init();

    __asm__ __volatile__ ("sti");
}

__attribute__((noreturn))
void i386_main(void) {
    i386_init();
    kernel_main();
}
