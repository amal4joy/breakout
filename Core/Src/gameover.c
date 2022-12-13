#include "state.h"
#include "types.h"
#include <stdio.h>
#include "gfx.h"
#include "ft6206.h"

static i32 acc;

void gameover_init()
{
  // printf("gameover_init\r\n");
  gfx_fill_screen(gfx_color(0, 0, 0));
  
  if (victory)
  {
    gfx_draw_font("Well done. You Won!", 190, 70, gfx_color(255, 255, 255));
  }
  else
  {
    gfx_draw_font("Game Over. You Lost", 190, 70, gfx_color(255, 0, 0));
  }
  
  gfx_update_screen();
  
  // draw to bottom screen
  gfx_fill_screen(gfx_color(0, 0, 0));
  gfx_update_bottom_screen();
  
  // get the current time
  acc = HAL_GetTick();
}

void gameover_loop()
{
  // printf("gameover_loop\r\n");
  
  // wait 3 seconds and move to intro
  if (HAL_GetTick() - acc > 3000)
  {
    next = &intro;
  }
}

state gameover = { gameover_init, gameover_loop };