#include "lib/io/io.h"

io_value_t io_inb(io_port_t port) {
    io_value_t value;
    asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

void io_outb(io_port_t port, io_value_t value) {
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

void io_wait(void) {
    io_outb(0x80, 0);
}
