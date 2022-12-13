#include "main.h"
#include "ili9341.h"
#include <stdio.h>
#include <stdlib.h>

static SPI_HandleTypeDef *spi_handle;
//static u8 frame[76800];

void ili9341_init(SPI_HandleTypeDef *sh)
{
  spi_handle = sh;
  // pull lcd chip select high
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_SET);
  ili9341_reset();
  HAL_Delay(120);
  ili9341_sleep_out();
  ili9341_set_madctl(0x00);
  ili9341_set_pixel_format(0x55);
  ili9341_display_on();
}

i32 ili9341_reset()
{
  u8 txbuf = 0x01;
  // pull lcd chip select line low
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_RESET);
  // set data/command line to command
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
  // transmit command
  HAL_SPI_Transmit(spi_handle, (u8*)&txbuf, 1, HAL_MAX_DELAY);
  // set chip select back to high
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_SET);
  return 0;
}

i32 ili9341_get_identification(u8 data[3])
{
  HAL_StatusTypeDef status;
  u8 txdata[4] = { 0x04, 0x00, 0x00, 0x00 };
  u8 rxdata[4];
  
   // pull lcd chip select line low
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_RESET);
  // set data/command line to command
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
  // transmit and look for a response
  status = HAL_SPI_TransmitReceive(spi_handle, txdata, rxdata, 4, HAL_MAX_DELAY);
  
  if (status == HAL_OK)
  {
    data[0] = rxdata[1];
    data[1] = rxdata[2];
    data[2] = rxdata[3];
  }
  
  // set chip select back to high
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_SET);
  return status;
}

i32 ili9341_get_display_status(u8 data[4])
{
  HAL_StatusTypeDef status;
  u8 txdata[5] = { 0x09, 0x00, 0x00, 0x00, 0x00 };
  u8 rxdata[5];
  
   // pull lcd chip select line low
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_RESET);
  // set data/command line to command
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
  // transmit and look for a response
  status = HAL_SPI_TransmitReceive(spi_handle, txdata, rxdata, 5, HAL_MAX_DELAY);
  
  if (status == HAL_OK)
  {
    data[0] = rxdata[1];
    data[1] = rxdata[2];
    data[2] = rxdata[3];
    data[3] = rxdata[4];
  }
  
  // set chip select back to high
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_SET);
  return status;
}

i32 ili9341_get_madctl(u8 *data)
{
  HAL_StatusTypeDef status;
  u8 txdata[2] = { 0x0B, 0x00 };
  u8 rxdata[2];
  
   // pull lcd chip select line low
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_RESET);
  // set data/command line to command
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
  // transmit and look for a response
  status = HAL_SPI_TransmitReceive(spi_handle, txdata, rxdata, 2, HAL_MAX_DELAY);
  
  if (status == HAL_OK)
  {
    *data = rxdata[1];
  }
  
  // set chip select back to high
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_SET);
  
  return status;
}

i32 ili9341_get_pixel_format(u8 *data)
{
  HAL_StatusTypeDef status;
  u8 txdata[2] = { 0x0C, 0x00 };
  u8 rxdata[2];
  
   // pull lcd chip select line low
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_RESET);
  // set data/command line to command
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
  // transmit and look for a response
  status = HAL_SPI_TransmitReceive(spi_handle, txdata, rxdata, 2, HAL_MAX_DELAY);
  
  if (status == HAL_OK)
  {
    *data = rxdata[1];
  }
  
  // set chip select back to high
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_SET);
  
  return status;  
}  
  
i32 ili9341_set_madctl(u8 data)
{
  u8 txbuf = 0x36;
  
   // pull lcd chip select line low
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_RESET);
  // set data/command line to command
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
  // transmit identification command
  HAL_SPI_Transmit(spi_handle, &txbuf, 1, HAL_MAX_DELAY);
  // set data/command line to data
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
  // transmit parameter 1
  HAL_SPI_Transmit(spi_handle, &data, 1, HAL_MAX_DELAY);
  // set chip select back to high
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_SET);
  return 0;
}

i32 ili9341_set_pixel_format(u8 data)
{
  u8 txbuf = 0x3A;
  
   // pull lcd chip select line low
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_RESET);
  // set data/command line to command
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
  // transmit identification command
  HAL_SPI_Transmit(spi_handle, &txbuf, 1, HAL_MAX_DELAY);
  // set data/command line to data
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
  // transmit parameter 1
  HAL_SPI_Transmit(spi_handle, &data, 1, HAL_MAX_DELAY);
  // set chip select back to high
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_SET);
  return 0;
}

i32 ili9341_sleep_out()
{
  u8 txbuf = 0x11;
  
   // pull lcd chip select line low
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_RESET);
  // set data/command line to command
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
  // transmit sleep out command
  HAL_SPI_Transmit(spi_handle, &txbuf, 1, HAL_MAX_DELAY);
  // set chip select back to high
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_SET);
  return 0;  
}

i32 ili9341_display_on()
{
  u8 txbuf = 0x29;
  
   // pull lcd chip select line low
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_RESET);
  // set data/command line to command
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
  // transmit sleep out command
  HAL_SPI_Transmit(spi_handle, &txbuf, 1, HAL_MAX_DELAY);
  // set chip select back to high
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_SET);
  return 0;
}

i32 ili9341_display_off()
{
  u8 txbuf = 0x28;
  
   // pull lcd chip select line low
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_RESET);
  // set data/command line to command
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
  // transmit sleep out command
  HAL_SPI_Transmit(spi_handle, &txbuf, 1, HAL_MAX_DELAY);
  // set chip select back to high
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_SET);
  return 0;
}

i32 ili9341_write(u8 frame[76800])
{
  u8 txdata1[5] = { 0x2A,       0,      0, 239 >> 8, 239 & 0xFF };
  u8 txdata2[5] = { 0x2B,       0,      0, 319 >> 8, 319 & 0xFF };
  u8 txdata3 = 0x2C;
  // pull lcd chip select line low
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_RESET);
  // set data/command line to command
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
  // transmit command
  HAL_SPI_Transmit(spi_handle, txdata1, 1, HAL_MAX_DELAY);
  // set data/command line to data
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
  // transmit parameters
  HAL_SPI_Transmit(spi_handle, txdata1 + 1, 4, HAL_MAX_DELAY);
  // set data/command line to command
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
  // transmit command
  HAL_SPI_Transmit(spi_handle, txdata2, 1, HAL_MAX_DELAY);
  // set data/command line to data
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
  // transmit parameters
  HAL_SPI_Transmit(spi_handle, txdata2 + 1, 4, HAL_MAX_DELAY);
  // set data/command line to command
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
  // transmit command
  HAL_SPI_Transmit(spi_handle, &txdata3, 1, HAL_MAX_DELAY);
  // set data/command line to data
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
  // transmit over spi
  HAL_SPI_Transmit(spi_handle, frame +      0, 65535, HAL_MAX_DELAY);
  HAL_SPI_Transmit(spi_handle, frame +  65535, 11265, HAL_MAX_DELAY);
  // set data/command line to command
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
  // transmit nop command
  txdata3 = 0x00;
  HAL_SPI_Transmit(spi_handle, &txdata3, 1, HAL_MAX_DELAY);
  // pull lcd chip select high
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_SET);
  return 0;
}

i32 ili9341_write_bottom(u8 frame[76800])
{
  u8 txdata1[5] = { 0x2A,        0,          0, 239 >> 8, 239 & 0xFF };
  u8 txdata2[5] = { 0x2B, 160 >> 8, 160 & 0xFF, 319 >> 8, 319 & 0xFF };
  u8 txdata3 = 0x2C;
  // pull lcd chip select line low
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_RESET);
  // set data/command line to command
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
  // transmit command
  HAL_SPI_Transmit(spi_handle, txdata1, 1, HAL_MAX_DELAY);
  // set data/command line to data
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
  // transmit parameters
  HAL_SPI_Transmit(spi_handle, txdata1 + 1, 4, HAL_MAX_DELAY);
  // set data/command line to command
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
  // transmit command
  HAL_SPI_Transmit(spi_handle, txdata2, 1, HAL_MAX_DELAY);
  // set data/command line to data
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
  // transmit parameters
  HAL_SPI_Transmit(spi_handle, txdata2 + 1, 4, HAL_MAX_DELAY);
  // set data/command line to command
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
  // transmit command
  HAL_SPI_Transmit(spi_handle, &txdata3, 1, HAL_MAX_DELAY);
  // set data/command line to data
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
  // transmit over spi
  HAL_SPI_Transmit(spi_handle, frame +      0, 65535, HAL_MAX_DELAY);
  HAL_SPI_Transmit(spi_handle, frame +  65535, 11265, HAL_MAX_DELAY);
  // set data/command line to command
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
  // transmit nop command
  txdata3 = 0x00;
  HAL_SPI_Transmit(spi_handle, &txdata3, 1, HAL_MAX_DELAY);
  // pull lcd chip select high
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,  GPIO_PIN_SET);
  return 0;
}