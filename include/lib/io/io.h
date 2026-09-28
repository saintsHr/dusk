#ifndef DUSK_LIB_IO_IO_H
#define DUSK_LIB_IO_IO_H

#include "lib/std/stdint.h"

typedef uint8_t io_value_t;
typedef uint16_t io_port_t;

io_value_t io_inb(io_port_t port);
void io_outb(io_port_t port, io_value_t value);

#endif
