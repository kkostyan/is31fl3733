#include "is31fl3733.h"

void
IS31FL3733_SelectPage (IS31FL3733 *device, uint8_t page)
{
  // Unlock Command Register.
  IS31FL3733_WriteCommonReg (device, IS31FL3733_PSWL, IS31FL3733_PSWL_ENABLE);
  // Select requested page in Command Register.
  IS31FL3733_WriteCommonReg (device, IS31FL3733_PSR, page);
}

void
IS31FL3733_WriteCommonReg (IS31FL3733 *device, uint8_t reg_addr, uint8_t reg_value)
{
  // Write value to register.
  device->pfn_i2c_write_reg(device->address, reg_addr, &reg_value, sizeof(uint8_t));
}

void
IS31FL3733_WritePagedReg (IS31FL3733 *device, uint16_t reg_addr, uint8_t reg_value)
{
  // Select register page.
  IS31FL3733_SelectPage (device, IS31FL3733_GET_PAGE(reg_addr));
  // Write value to register.
  device->pfn_i2c_write_reg(device->address, IS31FL3733_GET_ADDR(reg_addr), &reg_value, sizeof(uint8_t));
}

void
IS31FL3733_Init (IS31FL3733 *device)
{
  // Clear software reset in configuration register.
  IS31FL3733_WritePagedReg (device, IS31FL3733_CR, IS31FL3733_CR_SSD);
  // Set global current control register.
  IS31FL3733_WritePagedReg (device, IS31FL3733_GCC, device->gcc);
}

void
IS31FL3733_Update (IS31FL3733 *device)
{
  uint8_t led_states[IS31FL3733_CS * IS31FL3733_SW / 8];
  uint8_t cs;
  uint8_t sw;
  
  // Calculate state of LEDs.
  for (sw = 0; sw < IS31FL3733_SW; sw++)
  {
    led_states[(sw << 1)] = 0x00;
    led_states[(sw << 1) + 1] = 0x00;
    for (cs = 0; cs < IS31FL3733_CS; cs++)
    {
      if (device->leds[sw * IS31FL3733_CS + cs] != 0)
      {
        led_states[(sw << 1) + (cs / 8)] |= 0x01 << (cs % 8);
      }
    }
  }
  // Select IS31FL3733_LEDONOFF register page.
  IS31FL3733_SelectPage (device, IS31FL3733_GET_PAGE(IS31FL3733_LEDONOFF));
  // Write LED states.
  device->pfn_i2c_write_reg(device->address, IS31FL3733_GET_ADDR(IS31FL3733_LEDONOFF), led_states, sizeof(led_states));
  // Select IS31FL3733_LEDPWM register page.
  IS31FL3733_SelectPage (device, IS31FL3733_GET_PAGE(IS31FL3733_LEDPWM));
  // Write PWM values.
  device->pfn_i2c_write_reg(device->address, IS31FL3733_GET_ADDR(IS31FL3733_LEDPWM), device->leds, sizeof(device->leds));
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
