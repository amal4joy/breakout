#include "game_object.h"
#include "gfx.h"

void go_render(go *obj)
{
  if (obj->hidden == 0)
    gfx_draw_rect(obj->left - obj->width + 1, obj->left, obj->top, obj->top + obj->height - 1, obj->color);
}

i32 collides(go *obj1, go *obj2)
{
  if (obj1->left < obj2->left - obj2->width || obj2->left < obj1->left - obj1->width)
  {
    return 0;
  }
  
  if (obj1->top > obj2->top + obj2->height || obj2->top > obj1->top + obj1->height)
  {
    return 0;
  }
  
  return 1;
}