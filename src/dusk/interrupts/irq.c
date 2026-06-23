#include "dusk/interrupts/irq.h"
#include "dusk/interrupts/pic.h"
#include <stdint.h>

void irq_handler(uint8_t irq) {
    switch (irq) {
        default: break;
    }

    pic_send_eoi(irq);
}