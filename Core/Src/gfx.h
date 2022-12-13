#ifndef __GFX_H__
#define __GFX_H__

#include "types.h"
#include "main.h"

extern u8 frame[];

void gfx_init(SPI_HandleTypeDef *sh);

void gfx_finl();

void gfx_draw_rect(u32 xs, u32 xe, u32 ys, u32 ye, u16 color);

void gfx_draw_font(const char *txt, u32 xs, u32 ys, u16 color);

void gfx_draw_font_large(const char *txt, i32 xs, i32 ys, u16 color);

void gfx_fill_screen(u16 color);

u16 gfx_color(u8 red, u8 green, u8 blue);

void gfx_update_screen();

void gfx_update_bottom_screen();

#endif