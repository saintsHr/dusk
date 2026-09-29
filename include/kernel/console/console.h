#ifndef DUSK_KERNEL_CONSOLE_CONSOLE_H
#define DUSK_KERNEL_CONSOLE_CONSOLE_H

#include "drivers/vga/vga.h"

void console_move(vga_coord_t x, vga_coord_t y);
void console_set_color(vga_color_t fg, vga_color_t bg);

void console_write_char(char c);
void console_write_string(char* str);

void console_clear(void);

void console_init(void);

#endif
