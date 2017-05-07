# IS31FL3733 C library #

This library support Pulse Width Mode (PWM) and Auto Breath Mode (ABM) for IS31FL3733.
To use device in PWM mode, include `is31fl3733.h` file to your project.
To use device in ABM mode, include `is31fl3733_abm.h` file to your project.

## Common steps ##

To work with library in any of this modes you need to declare an instance of IS31FL3733:

    IS31FL3733 is31fl3733_0;

Multiple instances with different I2C addresses on same or different I2C buses can be declared.

Implement an `i2c_write_reg` and `i2c_read_reg` functions (example for STM32):

    I2C_HandleTypeDef hi2c1;

    uint8_t i2c_write_reg (uint8_t i2c_addr, uint8_t reg_addr, uint8_t *buffer, uint8_t count)
    {
      return HAL_I2C_Mem_Write (&hi2c1, i2c_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, buffer, count, 1);
    }
    
    uint8_t i2c_read_reg (uint8_t i2c_addr, uint8_t reg_addr, uint8_t *buffer, uint8_t count)
    {
      return HAL_I2C_Mem_Read (&hi2c1, i2c_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, buffer, count, 1);
    }

Set instance parameters and pointer to `i2c_write_reg` and `i2c_read_reg` functions:

    is31fl3733_0.address = IS31FL3733_I2C_ADDR(ADDR_GND, ADDR_GND);
    is31fl3733_0.i2c_write_reg = &i2c_write_reg;
    is31fl3733_0.i2c_read_reg = &i2c_read_reg;

Initialize device:

    // Initialize device.
    IS31FL3733_Init (&is31fl3733_0);
    // Set Global Current Control.
    IS31FL3733_SetGCC (&is31fl3733_0, 127);

## PWM mode ##

Draw something in PWM mode, e.g. set LED brightness at position {1;2} to maximum level:

    // Set PWM value for LED at {1;2}.
    IS31FL3733_SetLEDPWM (&is31fl3733_0, 1, 2, 255);
    // Turn on LED at position {1;2}.
    IS31FL3733_SetLEDState (&is31fl3733_0, 1, 2, IS31FL3733_LED_STATE_ON);

You can control all LED's in column/row and full LED matrix:

    // Set PWM values for all LEDs at 1-st column to 15/255 level.
    IS31FL3733_SetLEDPWM (&is31fl3733_0, 1, IS31FL3733_SW, 15);
    // Turn on selected LEDs.
    IS31FL3733_SetLEDState (&is31fl3733_0, 1, IS31FL3733_SW, IS31FL3733_LED_STATE_ON);
    // Set PWM values for all LEDs at 7-th row to 55/255 level.
    IS31FL3733_SetLEDPWM (&is31fl3733_0, IS31FL3733_CS, 7, 55);
    // Turn on selected LEDs.
    IS31FL3733_SetLEDState (&is31fl3733_0, IS31FL3733_CS, 7, IS31FL3733_LED_STATE_ON);
    // Set PWM values for all LEDs in matrix to 146/255 level.
    IS31FL3733_SetLEDPWM (&is31fl3733_0, IS31FL3733_CS, IS31FL3733_SW, 146);
    // Turn on selected LEDs.
    IS31FL3733_SetLEDState (&is31fl3733_0, IS31FL3733_CS, IS31FL3733_SW, IS31FL3733_LED_STATE_ON);

Also you can update all LEDs state and brightness from an array of values, e.g. draw a heart figure:

    // 16x12 heart figure.
    static const uint8_t heart[] = {
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,
      0x00,0x00,0x00,0xff,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0x00,0x00,0x00,
      0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
      0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    };
    // Set LED brightness for all LEDs from an array.
    IS31FL3733_SetPWM (&is31fl3733_0, (uint8_t*)heart);
    // Turn on LED with non-zero brightness.
    IS31FL3733_SetState (&is31fl3733_0, (uint8_t*)heart);

# ABM mode ##

To draw automatically pulsed heart from PWM mode example declare an instance of IS31FL3733_ABM structure

    IS31FL3733_ABM ABM1;

Initialize device to ABM mode, set ABM mode parameters and start ABM mode operation:

    // Turn on LEDs for heart figure.
    IS31FL3733_SetState (&is31fl3733_0, (uint8_t*)heart);
    // Configure all matrix LEDs to work in ABM1 mode.
    IS31FL3733_SetLEDMode (&is31fl3733_0, IS31FL3733_CS, IS31FL3733_SW, IS31FL3733_LED_MODE_ABM1);
    // Set ABM mode structure parameters.
    ABM1.T1 = IS31FL3733_ABM_T1_840MS;
    ABM1.T2 = IS31FL3733_ABM_T2_840MS;
    ABM1.T3 = IS31FL3733_ABM_T3_840MS;
    ABM1.T4 = IS31FL3733_ABM_T4_840MS;
    ABM1.Tbegin = IS31FL3733_ABM_LOOP_BEGIN_T4;
    ABM1.Tend = IS31FL3733_ABM_LOOP_END_T3;
    ABM1.Times = IS31FL3733_ABM_LOOP_FOREVER;
    // Write ABM structure parameters to device registers.
    IS31FL3733_ConfigABM (&is31fl3733_0, IS31FL3733_ABM_NUM_1, &ABM1);
    // Start ABM mode operation.
    IS31FL3733_StartABM (&is31fl3733_0);
