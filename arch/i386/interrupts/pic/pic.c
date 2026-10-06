#include "arch/i386/interrupts/pic/pic.h"
#include "lib/io/io.h"

#define PIC_READ_ISR 0x0B

void pic_init(void) {
    io_outb(PIC1_CMD, 0x11); io_wait();
    io_outb(PIC2_CMD, 0x11); io_wait();
    io_outb(PIC1_DATA, 0x20); io_wait();
    io_outb(PIC2_DATA, 0x28); io_wait();
    io_outb(PIC1_DATA, 0x04); io_wait();
    io_outb(PIC2_DATA, 0x02); io_wait();
    io_outb(PIC1_DATA, 0x01); io_wait();
    io_outb(PIC2_DATA, 0x01); io_wait();

    pic_mask_all();
}

void pic_mask(uint8_t irq) {
    uint16_t port;

    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }

    io_outb(port, io_inb(port) | (1 << irq));
}

void pic_unmask(uint8_t irq) {
    uint16_t port;

    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
        io_outb(PIC1_DATA, io_inb(PIC1_DATA) & ~(1 << 2));
    }

    io_outb(port, io_inb(port) & ~(1 << irq));
}

void pic_mask_all(void) {
    io_outb(PIC1_DATA, 0xFF);
    io_outb(PIC2_DATA, 0xFF);
}

void pic_unmask_all(void) {
    io_outb(PIC1_DATA, 0x00);
    io_outb(PIC2_DATA, 0x00);
}

uint16_t pic_read_isr(void) {
    io_outb(PIC1_CMD, PIC_READ_ISR);
    io_outb(PIC2_CMD, PIC_READ_ISR);
    return ((uint16_t)io_inb(PIC2_CMD) << 8) | io_inb(PIC1_CMD);
}

void pic_send_eoi(uint8_t irq) {
    if (irq >= 8) io_outb(PIC2_CMD, PIC_EOI);
    io_outb(PIC1_CMD, PIC_EOI);
}
