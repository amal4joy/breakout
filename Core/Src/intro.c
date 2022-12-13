#include "state.h"
#include "types.h"
#include <stdio.h>
#include "gfx.h"
#include "ft6206.h"

static u8 touched, prev_touched = 0;
static u16 touchdata[2];

void intro_init()
{
  // printf("intro_init\r\n");
  gfx_fill_screen(gfx_color(0, 0, 0));
  gfx_draw_font("--- Breakout ---", 180, 70, gfx_color(255, 0, 0));
  gfx_draw_font("Tap here to start", 185, 90, gfx_color(255, 255, 255));
  gfx_update_screen();
  
  // draw to bottom screen
  gfx_fill_screen(gfx_color(0, 0, 0));
  gfx_update_bottom_screen();
}

void intro_loop()
{
  // printf("intro_loop\r\n");
  
  // handle input
  touched = ft6206_touched();
    
  if (touched && !prev_touched)
  {
    ft6206_touch_data(touchdata);
    
    if (touchdata[1] > 160)
    {
      next = &game;
    }
  }
  
  prev_touched = touched;
  
  // update
  
  // draw to screen
  
}

state intro = { intro_init, intro_loop };