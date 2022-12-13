#include "ft6206.h"
#include <stdio.h>

#define MIN_X   0
#define MAX_X 237
#define MIN_Y   0
#define MAX_Y 316

static I2C_HandleTypeDef *i2c_handle;

u8   ft6206_read (u8 reg);
void ft6206_write(u8 reg, u8 val);

i32 ft6206_init(I2C_HandleTypeDef *ih)
{
  i2c_handle = ih; 
  
  // printf("VENID: %d\r\n", ft6206_read(0xA8));
  if (ft6206_read(0xA8) != 17)
  {
    return -1;
  }
  
  return 0;
}

i32 ft6206_touched()
{
  return ft6206_read(0x2) > 0;
}

i32 ft6206_touch_data(u16 data[2])
{
  data[0] = ft6206_read(0x4);
  data[1] = (((u16)ft6206_read(0x5)) << 8) | ft6206_read(0x6);
  data[0] = (data[0] - MIN_X) * (double)(239)/(MAX_X - MIN_X);
  data[1] = (data[1] - MIN_Y) * (double)(319)/(MAX_Y - MIN_Y);
  return 0;
}

// write data to ft6206
void ft6206_write(u8 reg, u8 val)
{
  u8 buf[2];
  
  buf[0] = reg;
  buf[1] = val;
  
  HAL_I2C_Master_Transmit(i2c_handle, (0x38 << 1), (u8*)&buf, 2, HAL_MAX_DELAY);
}

// read data from ft6206
u8 ft6206_read(u8 reg)
{
  u8 buf[2];  
  buf[0] = reg;
  
  HAL_I2C_Master_Transmit(i2c_handle, (0x38 << 1), (u8*)&buf, 1, HAL_MAX_DELAY);
  HAL_I2C_Master_Receive(i2c_handle, (0x38 << 1), (u8*)&buf, 1, HAL_MAX_DELAY);
  
  return buf[0];
}