#include <stdlib.h>
#include "gfx.h"
#include "ili9341.h"
#include "font.h"

u8 frame[76800];

void gfx_init(SPI_HandleTypeDef *sh)
{
  ili9341_init(sh);
}

void gfx_finl()
{
  /* pass */
}

void gfx_draw_rect(u32 xs, u32 xe, u32 ys, u32 ye, u16 color)
{
  for (u32 i = xs; i <= xe; ++i)
  {
    for (u32 j = ys; j <= ye; ++j)
    {
      frame[2*(240 * j + i) + 0] = color >> 8;
      frame[2*(240 * j + i) + 1] = color & 0xFF;
    }
  }
}

void gfx_draw_font(const char *txt, u32 xs, u32 ys, u16 color)
{
  while (*txt != '\0')
  {
    for (i32 i = xs; (i > xs - 8) && (i > -1); --i)
      for (i32 j = ys; (j < ys + 8) && (j < 160); ++j)
        if (FONT[*txt][j - ys] & (0x1 << (xs - i)))
        {
          frame[2*(240 * j + i) + 0] = color >> 8;
          frame[2*(240 * j + i) + 1] = color & 0xFF;
        }
      
    xs  -= 8;
    txt += 1;
  }
}

void gfx_draw_font_large(const char *txt, i32 xs, i32 ys, u16 color)
{
  while (*txt != '\0')
  {
    for (i32 i = xs; (i > xs - 64) && (i > -1); --i)
      for (i32 j = ys; (j < ys + 64) && (j < 160); ++j)
        if (FONT[*txt][(j - ys)/8] & (0x1 << ((xs - i)/8)))
        {
          frame[2*(240 * j + i) + 0] = color >> 8;
          frame[2*(240 * j + i) + 1] = color & 0xFF;
        }
      
    xs  -= 64;
    txt += 1;
  }
}

void gfx_fill_screen(u16 color)
{
  for (u32 i = 0; i < 76800; i+=2)
  {
    frame[ i ] = color >> 8;
    frame[i+1] = color & 0xFF;
  }
}

u16 gfx_color(u8 red, u8 green, u8 blue)
{
  double mr, mg, mb;
  u16 r, g, b;
  
  mr = (double)0x1F / 255.0;
  mg = (double)0x3F / 255.0;
  mb = (double)0x1F / 255.0;
  
  r = (u16)(mr * (double)red);
  g = (u16)(mg * (double)green);
  b = (u16)(mb * (double)blue);
  
  return (b << 11) | (g << 5) | r;
}

void gfx_update_screen()
{
  ili9341_write(frame);
}

void gfx_update_bottom_screen()
{
  ili9341_write_bottom(frame);
}