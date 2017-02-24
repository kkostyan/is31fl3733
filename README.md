# IS31FL3733 C library #

To work with library you need to declare an instance of IS31FL3733:

`IS31FL3733 is31fl3733_0;`

Multiple instances with diffrent I2C addresses on same or different I2C buses can be declared.

Implement an `i2c_write_reg` function (example for STM32):

    I2C_HandleTypeDef hi2c1;

    uint8_t i2c_write_reg (uint8_t i2c_addr, uint8_t reg_addr, uint8_t *buffer, uint8_t count)
    {
      return HAL_I2C_Mem_Write (&hi2c1, i2c_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, buffer, count, 5);
    }

Set instance parameters and pointer to `i2c_write_reg` function:

    is31fl3733_0.address = IS31FL3733_I2C_ADDR(ADDR_GND, ADDR_GND);
    is31fl3733_0.gcc = 255;
    is31fl3733_0.pfn_i2c_write_reg = &i2c_write_reg;

Then, initialize device and try to draw something, e.g. set led brightness at position {1,2} to maximum level.

    IS31FL3733_Init (&is31fl3733_0);
    IS31FL3733_Fill (&is31fl3733_0, 0x00);
    IS31FL3733_SetLED (&is31fl3733_0, 1, 2, 255);
    IS31FL3733_Update (&is31fl3733_0);
