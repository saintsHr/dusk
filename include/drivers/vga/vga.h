#ifndef DUSK_DRIVERS_VGA_VGA_H
#define DUSK_DRIVERS_VGA_VGA_H

#include "lib/std/stdint.h"
#include "lib/std/stdbool.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define VGA_CRTC_INDEX 0x3D4
#define VGA_CRTC_DATA  0x3D5

#define VGA_CURSOR_START 0x0A
#define VGA_CURSOR_END   0x0B
#define VGA_CURSOR_LOW   0x0F
#define VGA_CURSOR_HIGH  0x0E
#define VGA_CURSOR_DISABLE 0x20

#define VGA_AC_INDEX 0x3C0
#define VGA_AC_READ 0x3C1
#define VGA_AC_MODE_CONTROL 0x10
#define VGA_AC_ENABLE 0x20

typedef enum {
	VGA_COLOR_BLACK         = 0x0,
	VGA_COLOR_BLUE          = 0x1,
	VGA_COLOR_GREEN         = 0x2,
	VGA_COLOR_CYAN          = 0x3,
	VGA_COLOR_RED           = 0x4,
	VGA_COLOR_MAGENTA       = 0x5,
	VGA_COLOR_BROWN         = 0x6,
	VGA_COLOR_LIGHT_GREY    = 0x7,
	VGA_COLOR_DARK_GREY     = 0x8,
	VGA_COLOR_LIGHT_BLUE    = 0x9,
	VGA_COLOR_LIGHT_GREEN   = 0xA,
	VGA_COLOR_LIGHT_CYAN    = 0xB,
	VGA_COLOR_LIGHT_RED     = 0xC,
	VGA_COLOR_LIGHT_MAGENTA = 0xD,
	VGA_COLOR_LIGHT_BROWN   = 0xE,
	VGA_COLOR_WHITE         = 0xF,
} vga_color_t;

typedef uint8_t vga_char_t;
typedef uint8_t vga_attr_t;
typedef uint16_t vga_cell_t;

typedef uint8_t vga_coord_t;
typedef uint16_t vga_index_t;

vga_attr_t vga_make_attr(vga_color_t fg, vga_color_t bg);
vga_cell_t vga_make_cell(vga_attr_t attr, vga_char_t c);
vga_index_t vga_make_index(vga_coord_t x, vga_coord_t y);

void vga_set_cursor(bool state);
void vga_move_cursor(vga_index_t index);

void vga_set_blink(bool state);

void vga_init(void);

void vga_set_cell(vga_cell_t cell, vga_index_t index);

#endif
