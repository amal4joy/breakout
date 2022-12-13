#ifndef __FT6206_H__
#define __FT6206_H__

#include "types.h"
#include "main.h"

i32 ft6206_init();
i32 ft6206_touched();
i32 ft6206_touch_data(u16 data[2]);

#endif