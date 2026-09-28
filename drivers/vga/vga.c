#include "drivers/vga/vga.h"

static volatile vga_cell_t *const framebuffer = (volatile vga_cell_t *)0xB8000;

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
    framebuffer[index] = cell;
}
