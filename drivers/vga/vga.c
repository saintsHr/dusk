#include "drivers/vga/vga.h"
#include "lib/io/io.h"
#include "lib/std/stdint.h"

static volatile vga_cell_t *const framebuffer = (volatile vga_cell_t *)0xB8000;

static uint8_t vga_read_mode_control(void) {
    uint8_t mode;

    io_inb(0x3DA);
    io_outb(VGA_AC_INDEX, VGA_AC_MODE_CONTROL);
    mode = io_inb(VGA_AC_READ);

    return mode;
}

static void vga_write_mode_control(uint8_t mode) {
    io_inb(0x3DA);
    io_outb(VGA_AC_INDEX, VGA_AC_MODE_CONTROL);
    io_outb(VGA_AC_INDEX, mode);
    io_outb(VGA_AC_INDEX, VGA_AC_ENABLE);
}

vga_attr_t vga_make_attr(vga_color_t fg, vga_color_t bg) {
    return (vga_attr_t)((bg << 4) | fg);
}

vga_cell_t vga_make_cell(vga_attr_t attr, vga_char_t c) {
    return (vga_cell_t)((attr << 8) | c);
}

vga_index_t vga_make_index(vga_coord_t x, vga_coord_t y) {
    return (vga_index_t)(y * VGA_WIDTH + x);
}

void vga_set_cell(vga_cell_t cell, vga_index_t index) {
    if (index >= VGA_WIDTH * VGA_HEIGHT) return;
    framebuffer[index] = cell;
}

vga_cell_t vga_get_cell(vga_index_t index) {
    if (index >= VGA_WIDTH * VGA_HEIGHT) return 0;
    return framebuffer[index];
}

void vga_set_cursor(bool state) {
    if (state == true) {
        uint8_t cursor_start;
        uint8_t cursor_end;

        io_outb(VGA_CRTC_INDEX, VGA_CURSOR_START);
        cursor_start = io_inb(VGA_CRTC_DATA);
        cursor_start &= ~(1 << 5);

        io_outb(VGA_CRTC_INDEX, VGA_CURSOR_END);
        cursor_end = io_inb(VGA_CRTC_DATA);
        cursor_end &= 0x1F;

        io_outb(VGA_CRTC_INDEX, VGA_CURSOR_START);
        io_outb(VGA_CRTC_DATA, cursor_start);

        io_outb(VGA_CRTC_INDEX, VGA_CURSOR_END);
        io_outb(VGA_CRTC_DATA, cursor_end);
    } else {
        io_outb(VGA_CRTC_INDEX, VGA_CURSOR_START);
        io_outb(VGA_CRTC_DATA, VGA_CURSOR_DISABLE);
    }
}

void vga_move_cursor(vga_index_t index) {
    io_outb(VGA_CRTC_INDEX, VGA_CURSOR_LOW);
	io_outb(VGA_CRTC_DATA, (uint8_t)(index & 0xFF));

	io_outb(VGA_CRTC_INDEX, VGA_CURSOR_HIGH);
	io_outb(VGA_CRTC_DATA, (uint8_t)((index >> 8) & 0xFF));
}

void vga_set_blink(bool state) {
    uint8_t mode = vga_read_mode_control();

    if (state == true) {
        mode |= (1 << 3);
    } else {
        mode &= ~(1 << 3);
    }

    vga_write_mode_control(mode);
}

void vga_init(void) {
    vga_set_blink(false);
    vga_set_cursor(true);
}
