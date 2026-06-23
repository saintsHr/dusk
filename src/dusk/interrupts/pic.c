#include "dusk/interrupts/pic.h"
#include "dusk/io.h"

#define PIC1 0x20
#define PIC2 0xA0

#define PIC1_COMMAND PIC1
#define PIC1_DATA    (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA    (PIC2 + 1)

void pic_remap(uint8_t offset1, uint8_t offset2) {
    uint8_t a1 = io_inb(PIC1_DATA);
    uint8_t a2 = io_inb(PIC2_DATA);

    io_outb(PIC1_COMMAND, 0x11);
    io_outb(PIC2_COMMAND, 0x11);

    io_outb(PIC1_DATA, offset1);
    io_outb(PIC2_DATA, offset2);

    io_outb(PIC1_DATA, 0x04);
    io_outb(PIC2_DATA, 0x02);

    io_outb(PIC1_DATA, 0x01);
    io_outb(PIC2_DATA, 0x01);

    io_outb(PIC1_DATA, a1);
    io_outb(PIC2_DATA, a2);
}

void pic_send_eoi(uint8_t irq) {
    if (irq >= 8) io_outb(0xA0, 0x20);
    io_outb(0x20, 0x20);
}