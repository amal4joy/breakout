#include "state.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include "gfx.h"
#include "ft6206.h"
#include "game_object.h"

static u8 touched;
static u16 touchdata[2];

static go paddle;
i32 paddle_vel = 0;

static go ball;
static i32 ball_vel[2];

int victory = 0;

#define NUM_BRICK_ROWS 3
#define NUM_BRICK_COLS 7

static go bricks[NUM_BRICK_ROWS][NUM_BRICK_COLS];

void game_init()
{
  // printf("game_init\r\n");
  
  // draw the bottom screen
  gfx_fill_screen(gfx_color(0, 0, 0));
  gfx_draw_font_large("<", 200, 70, gfx_color(255, 0, 0));
  gfx_draw_font_large(">", 86, 70, gfx_color(255, 0, 0));
  gfx_update_bottom_screen();
  
  // clear top screen
  gfx_fill_screen(gfx_color(0, 0, 0));
  gfx_update_screen();
  
  // init paddle
  paddle.width  = 40;
  paddle.height = 5;
  paddle.left   = 140;
  paddle.top    = 140;
  paddle.hidden = 0;
  paddle.color  = gfx_color(255, 0, 0);

  // init ball
  ball.width  = 5;
  ball.height = 5;
  ball.left   = 239;
  ball.top    = 80;
  ball.hidden = 0;
  ball.color  = gfx_color(0, 255, 255);
  ball_vel[0] = -5;
  ball_vel[1] = 4;
  
  // init bricks
  srand(HAL_GetTick());
  
  int x0 = 219, y0 = 10;
  
  for (int i = 0; i < NUM_BRICK_ROWS; ++i)
  {
    for (int j = 0; j < NUM_BRICK_COLS; ++j)
    {
      bricks[i][j].width  = 20;
      bricks[i][j].height = 10;
      bricks[i][j].left   = x0;
      bricks[i][j].top    = y0;
      bricks[i][j].color  = rand();
      bricks[i][j].hidden = 0;
      
      x0 -= 30;
    }
    
    x0 = 219;
    y0 += 20;
  }
  
}

void game_loop()
{
  // printf("game_loop\r\n");
  
  // handle input
  touched = ft6206_touched();
  paddle_vel = 0;
  
  if (touched)
  {
    ft6206_touch_data(touchdata);
    
    if (touchdata[0] < 120 && touchdata[1] < 160)
    {
      // touched ">" button
      paddle_vel = -8;
      // paddle.left -= 8;
      // printf("change state\r\n");
      // next = &intro;
    }
    else if (touchdata[0] > 120 && touchdata[1] < 160)
    {
      // touched "<" button
      paddle_vel = 8;
    }
  }
   
  // update paddle
  paddle.left += paddle_vel;
  
  // ensure paddle bounds
  if (paddle.left - paddle.width < 0)
  {
    paddle.left = paddle.width;
  }
  else if (paddle.left > 239)
  {
    paddle.left = 239;
  }
  
  // update ball position
  ball.left += ball_vel[0];
  ball.top  += ball_vel[1];
  
  // ensure ball bounds x
  if (ball.left - ball.width < 0)
  {
    ball.left = ball.width + (ball.width - ball.left);
    ball_vel[0] *= -1;
  }
  else if (ball.left > 239)
  {
    ball.left = 239 - (ball.left - 239);
    ball_vel[0] *= -1;
  }
  
  // ensure ball bounds y
  if (ball.top + ball.height > 160)
  {
    // ball.top = (160 - ball.height) - (ball.top + ball.height - 160);
    // ball_vel[1] *= -1;
    ball.top = (160 - ball.height);
    next = &gameover;
  }
  else if (ball.top < 0)
  {
    ball.top = -ball.top;
    ball_vel[1] *= -1;
  }
  
  // handle ball-paddle collision
  if (collides(&ball, &paddle))
  {
    ball.top = 2*(paddle.top - ball.height) - ball.top;
    ball_vel[1] *= -1;
    
    // the spice
    if (ball.left - ball.width / 2 > paddle.left - paddle.width / 2 && paddle_vel > 0)
    {
      ball_vel[0] = ((ball.left - ball.width/2) - (paddle.left - paddle.width/2)) / 3;
    }
    else if (ball.left - ball.width / 2 < paddle.left - paddle.width / 2 && paddle_vel < 0)
    {
      ball_vel[0] = ((ball.left - ball.width/2) - (paddle.left - paddle.width/2)) / 3;
    }
  }
  
  // handle ball-brick collision
  int ball_left = ball.left, ball_top = ball.top;
  
  for (int i = 0; i < NUM_BRICK_ROWS; ++i)
    for (int j = 0; j < NUM_BRICK_COLS; ++j)
      if (collides(&ball, &bricks[i][j]) && bricks[i][j].hidden == 0)
      {
        // left edge collision
        if (ball.left > bricks[i][j].left && ball_vel[0] < 0)
        {
          ball_vel[0] *= -1;
          // ball.left = bricks[i][j].left + 2;
          ball_left = bricks[i][j].left + 2;
        }
        // right edge collision
        else if (ball.left - ball.width < bricks[i][j].left - bricks[i][j].width && ball_vel[0] > 0)
        {
          ball_vel[0] *= -1;
          // ball.left = bricks[i][j].left - bricks[i][j].width - 2;
          ball_left = bricks[i][j].left - bricks[i][j].width - 2;
        }
        // top edge collision
        else if(ball.top < bricks[i][j].top)
        {
          ball_vel[1] *= -1;
          // ball.top = bricks[i][j].top - 2;
          ball_top = bricks[i][j].top - 2;
        }
        // bottom edge collision
        else 
        {
          ball_vel[1] *= -1;
          // ball.top = bricks[i][j].top + bricks[i][j].width + 2;
          ball_top = bricks[i][j].top + bricks[i][j].width + 2;
        }
        
        bricks[i][j].hidden = 1;
      }
 
  ball.left = ball_left;
  ball.top  = ball_top;
  
  // if all bricks are hidden swap state
  victory = 1;
  for (int i = 0; i < NUM_BRICK_ROWS; ++i)
    for (int j = 0; j < NUM_BRICK_COLS; ++j)
      if (bricks[i][j].hidden == 0)
        victory = 0;
  
  if (victory)
  {
    next = &gameover;
  }
  
  // draw to screen
  gfx_fill_screen(gfx_color(0, 0, 0));
  // draw ball
  go_render(&ball);
  // draw paddle
  go_render(&paddle);
  // draw bricks
  for (int i = 0; i < NUM_BRICK_ROWS; ++i)
    for (int j = 0; j < NUM_BRICK_COLS; ++j)
      go_render(&bricks[i][j]);
  
  gfx_update_screen();
  
}

state game = { game_init, game_loop };