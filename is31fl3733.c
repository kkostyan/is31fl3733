#include "is31fl3733.h"

void
IS31FL3733_Init (IS31FL3733 *device)
{
  uint8_t command;
  
  // Unlock Command Register.
  command = IS31FL3733_CRWL_ENABLE;
  device->pfn_i2c_write_reg(device->address, IS31FL3733_CRWL, &command, sizeof(command));
  // Set command register pointer to page 3.
  command = IS31FL3733_CR_PTR_PG3;
  device->pfn_i2c_write_reg(device->address, IS31FL3733_CR, &command, sizeof(command));
  // Clear software reset in configuration register 
  command = 0x01;
  device->pfn_i2c_write_reg(device->address, IS31FL3733_PG3_CR, &command, sizeof(command));
  // Set global current control register to full scale.
  command = 0xFF;
  device->pfn_i2c_write_reg(device->address, IS31FL3733_PG3_GCC, &command, sizeof(command));
}

void
IS31FL3733_Update (IS31FL3733 *device)
{
  uint8_t command;
  uint8_t led_states[IS31FL3733_CS * IS31FL3733_SW / 8];
  uint8_t cs;
  uint8_t sw;
  
  // Unlock Command Register.
  command = IS31FL3733_CRWL_ENABLE;
  device->pfn_i2c_write_reg(device->address, IS31FL3733_CRWL, &command, sizeof(command));
  // Set command register pointer to page 0.
  command = IS31FL3733_CR_PTR_PG0;
  device->pfn_i2c_write_reg(device->address, IS31FL3733_CR, &command, sizeof(command));
  // Calculate state of LEDs.
  for (sw = 0; sw < IS31FL3733_SW; sw++)
  {
    led_states[(sw << 1)] = 0xFF;
    led_states[(sw << 1) + 1] = 0xFF;
    for (cs = 0; cs < IS31FL3733_CS; cs++)
    {
      //led_states[(sw << 1) + (cs / 8)] |= (device->leds[sw * IS31FL3733_CS + cs] == 0);
    }
  }
  // Write LED states.
  device->pfn_i2c_write_reg(device->address, IS31FL3733_PG0_LEDONOFF, led_states, sizeof(led_states));
  // Unlock Command Register.
  command = IS31FL3733_CRWL_ENABLE;
  device->pfn_i2c_write_reg(device->address, IS31FL3733_CRWL, &command, sizeof(command));
  // Set command register pointer to page 1.
  command = IS31FL3733_CR_PTR_PG1;
  device->pfn_i2c_write_reg(device->address, IS31FL3733_CR, &command, sizeof(command));
  // Write PWM values.
  device->pfn_i2c_write_reg(device->address, IS31FL3733_PG1_PWM, device->leds, sizeof(device->leds));
}

void
IS31FL3733_SetLED (IS31FL3733 *device, uint8_t cs, uint8_t sw, uint8_t brightness)
{
  uint8_t offset;
  
  // Calculate LED offset in RAM buffer.
  offset = sw * IS31FL3733_CS + cs;
  // Set brightness level of selected LED.
  device->leds[offset] = brightness;
}

void
IS31FL3733_Fill (IS31FL3733 *device, uint8_t brightness)
{
  uint8_t count;
  
  // Set brightness level of all LED's.
  for (count = 0; count < IS31FL3733_CS * IS31FL3733_SW; count++)
  {
    device->leds[count] = brightness;
  }
}
