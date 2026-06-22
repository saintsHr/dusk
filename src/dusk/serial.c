#include "dusk/serial.h"
#include "dusk/io.h"

#define COM1 0x3F8

static inline void serial_put_char(char c) {
    io_outb(COM1, c);
}

void serial_init(void) {
    io_outb(COM1 + 1, 0x00);
    io_outb(COM1 + 3, 0x80);
    io_outb(COM1 + 0, 0x03);
    io_outb(COM1 + 1, 0x00);
    io_outb(COM1 + 3, 0x03);
    io_outb(COM1 + 2, 0xC7);
    io_outb(COM1 + 4, 0x0B);
}

void serial_print(const char* string) {
	while (*string) {
        serial_put_char(*string++);
    }
}