#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "types.h"

typedef struct game_object
{
  i32 left, top, width, height;
  u32 hidden;
  u16 color;
} go;

void go_render(go *obj);

i32 collides(go *obj1, go *obj2);

#endif