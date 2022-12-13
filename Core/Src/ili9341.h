#ifndef __ILI9341_H__
#define __ILI9341_H__

#include "types.h"

#define LCD_WIDTH  240
#define LCD_HEIGHT 320

void ili9341_init(SPI_HandleTypeDef *spi_handle);

i32 ili9341_reset();

i32 ili9341_get_identification(u8 data[3]);

i32 ili9341_get_madctl(u8 *data);

i32 ili9341_get_pixel_format(u8 *data);

i32 ili9341_get_display_status(u8 data[4]);

i32 ili9341_set_madctl(u8 data);

i32 ili9341_set_pixel_format(u8 data);

i32 ili9341_sleep_out();

i32 ili9341_display_on();

i32 ili9341_display_off();

i32 ili9341_write(u8* frame);

i32 ili9341_write_bottom(u8 *frame);

#endif