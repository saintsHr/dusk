#include "kernel/console/console.h"
#include "drivers/vga/vga.h"
#include "lib/std/stdint.h"

static vga_coord_t console_x = 0;
static vga_coord_t console_y = 0;

static vga_color_t console_fg = VGA_COLOR_LIGHT_GREY;
static vga_color_t console_bg = VGA_COLOR_BLACK;

void console_move(vga_coord_t x, vga_coord_t y) {
    vga_move_cursor(vga_make_index(x, y));

    console_x = x;
    console_y = y;
}

void console_set_color(vga_color_t fg, vga_color_t bg) {
    console_fg = fg;
    console_bg = bg;
}

void console_write_char(char c) {
    vga_set_cell(
        vga_make_cell(
            vga_make_attr(console_fg, console_bg),
            (vga_char_t)c
        ),
        vga_make_index(console_x, console_y)
    );

    if (console_x >= VGA_WIDTH) {
        console_x = 0;
        console_y++;
    } else {
        console_x++;
    }

    console_move(console_x, console_y);
}

void console_write_string(char* str) {
    usize_t i = 0;

    while (str[i] != '\0') {
        char c = str[i++];
        console_write_char(c);
    }
}

void console_clear(void) {
    for (vga_coord_t y = 0; y <= VGA_HEIGHT; y++) {
        for (vga_coord_t x = 0; x <= VGA_WIDTH; x++) {
            vga_set_cell(
                vga_make_cell(
                    vga_make_attr(console_fg, console_bg),
                    (vga_char_t)' '
                ),
                vga_make_index(x, y)
            );
        }
    }
}

void console_init(void) {
    console_clear();
    console_move(0, 0);
}
