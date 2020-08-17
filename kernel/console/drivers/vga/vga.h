/*****************************************************************
 * This file is part of CosmOS                                   *
 * Copyright (C) 2020 Kurt M. Weber                              *
 * Released under the stated terms in the file LICENSE           *
 * See the file "LICENSE" in the source distribution for details *
 *****************************************************************/

#ifndef _VGA_CONSOLE_H
#define _VGA_CONSOLE_H

#define VGA_CONSOLE_ENABLED

#ifndef _VGA_CONSOLE_C
extern uint16_t vga_console_x_width;
extern uint16_t vga_console_y_height;
extern uint8_t vga_console_xpos;
extern uint8_t vga_console_ypos;

void vga_console_register();
#else
uint16_t vga_console_x_width;
uint16_t vga_console_y_height;
uint8_t vga_console_xpos;
uint8_t vga_console_ypos;

void vga_console_init();
uint8_t vga_console_setpos(uint8_t x, uint8_t y);
uint8_t vga_console_write(const char *c);
#endif

#endif