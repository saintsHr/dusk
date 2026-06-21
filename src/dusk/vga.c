#include "dusk/vga.h"
#include "dusk/io.h"

#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH  80
#define VGA_HEIGHT 25

static volatile uint16_t* const vga_memory = (volatile uint16_t*)0xb8000;

static uint16_t vga_x;
static uint16_t vga_y;

static uint16_t vga_color = 0x07;

static void vga_put_char(char c, uint16_t x, uint16_t y) {
    if (x >= VGA_WIDTH)  return;
    if (y >= VGA_HEIGHT) return;

	uint16_t index = y * VGA_WIDTH + x;
    vga_memory[index] = (uint16_t)c | (vga_color << 8);
}

void vga_set_color(enum vga_color fg, enum vga_color bg) {
    vga_color = ((uint8_t)bg << 4) | ((uint8_t)fg);
}

void vga_move(uint8_t x, uint8_t y) {
    uint16_t pos = y * 80 + x;

    io_outb(0x3D4, 0x0F);
    io_outb(0x3D5, (uint8_t)(pos & 0xFF));

    io_outb(0x3D4, 0x0E);
    io_outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));

    vga_x = x;
    vga_y = y;
}

void vga_print(const char* string) {
    for (uint16_t i = 0; string[i] != '\0'; i++) {
        char c = string[i];

        if (c == '\n') {
            vga_x = 0;
            vga_y++;
        }

        if (vga_x >= VGA_WIDTH) {
            vga_x = 0;
            vga_y++;
        }

        if (vga_y >= VGA_HEIGHT) {
            vga_y = 0;
        }

        vga_put_char(c, vga_x, vga_y);
        vga_x++;

        vga_move(vga_x, vga_y);
    }
}