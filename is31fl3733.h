/** ISSI IS31FL3733 header file.
  */
#ifndef _IS31FL3733_H_
#define _IS31FL3733_H_

#include <stdint.h>

/** Maximum number of CS lines.
  */
#define IS31FL3733_CS (16)

/** Maximum number of SW lines.
  */
#define IS31FL3733_SW (12)

/** IS31FL3733 base address on I2C bus.
  */
#define IS31FL3733_I2C_BASE_ADDR (0xA0)

/** IS31FL3733 ADDR[2:1] connection.
  */
#define ADDR_GND (0x00) ///< ADDRx pin connected to GND.
#define ADDR_SCL (0x01) ///< ADDRx pin connected to SCL.
#define ADDR_SDA (0x02) ///< ADDRx pin connected to SDA.
#define ADDR_VCC (0x03) ///< ADDRx pin connected to VCC.

/** IS31FL3733 real address on I2C bus, see Table 1 on page 9 in datasheet.
    Example: IS31FL3733_I2C_ADDR(ADDR_SDA, ADDR_VCC) is 0xB6 address on I2C bus.
  */
#define IS31FL3733_I2C_ADDR(ADDR2, ADDR1) ((IS31FL3733_I2C_BASE_ADDR) | ((ADDR2) << 3) | ((ADDR1) << 1))

/** IS31FL3733 common registers.
  */
#define IS31FL3733_CR   (0xFD) ///< Command register.
#define IS31FL3733_CRWL (0xFE) ///< Command register write lock.
#define IS31FL3733_IMR  (0xF0) ///< Interrupt mask register.
#define IS31FL3733_ISR  (0xF1) ///< Interrupt status register.

#define IS31FL3733_CR_PTR_PG0 (0x00) /// Set CR pointer to Page 0.
#define IS31FL3733_CR_PTR_PG1 (0x01) /// Set CR pointer to Page 1.
#define IS31FL3733_CR_PTR_PG2 (0x02) /// Set CR pointer to Page 2.
#define IS31FL3733_CR_PTR_PG3 (0x03) /// Set CR pointer to Page 3.

#define IS31FL3733_CRWL_DISABLE (0x00) /// Disable write to CR.
#define IS31FL3733_CRWL_ENABLE  (0xC5) /// Enable write to CR.

#define IS31FL3733_IMR_IAC (0x08)
#define IS31FL3733_IMR_IAB (0x04)
#define IS31FL3733_IMR_IS  (0x02)
#define IS31FL3733_IMR_IO  (0x01)

#define IS31FL3733_ISR_ABM3 (0x10)
#define IS31FL3733_ISR_ABM2 (0x08)
#define IS31FL3733_ISR_ABM1 (0x04)
#define IS31FL3733_ISR_SB   (0x02)
#define IS31FL3733_ISR_OB   (0x01)

/// Registers in Page 0.
#define IS31FL3733_PG0_LEDONOFF (0x00)
#define IS31FL3733_PG0_LEDOPEN  (0x18)
#define IS31FL3733_PG0_LEDSHORT (0x30)

/// Registers in Page 1.
#define IS31FL3733_PG1_PWM (0x00)

/// Registers in Page 2.
#define IS31FL3733_PG2_ABM (0x00)

/// Registers in Page 3.
#define IS31FL3733_PG3_CR    (0x00)
#define IS31FL3733_PG3_GCC   (0x01)
#define IS31FL3733_PG3_ABM1  (0x02)
#define IS31FL3733_PG3_ABM2  (0x06)
#define IS31FL3733_PG3_ABM3  (0x0A)
#define IS31FL3733_PG3_TUR   (0x0E)
#define IS31FL3733_PG3_SWPUR (0x0F)
#define IS31FL3733_PG3_CSPDR (0x10)
#define IS31FL3733_PG3_RESET (0x11)

/** IS31FL3733 structure.
  */
typedef struct {
  /// Address on I2C bus.
  uint8_t address;
  /// LED matrix brightness.
  uint8_t leds[IS31FL3733_CS * IS31FL3733_SW];
  /// Pointer to I2C write register function.
  uint8_t (*pfn_i2c_write_reg) (uint8_t i2c_addr, uint8_t reg_addr, uint8_t *buffer, uint8_t count);
  /// Pointer to I2C read register function.
  uint8_t (*pfn_i2c_read_reg) (uint8_t i2c_addr, uint8_t reg_addr, uint8_t *buffer, uint8_t count);
} IS31FL3733;

/// Init LED matrix for normal operation.
void IS31FL3733_Init (IS31FL3733 *device);
/// Update LED matrix with internal buffer values.
void IS31FL3733_Update (IS31FL3733 *device);
/// Set LED brightness level.
void IS31FL3733_SetLED (IS31FL3733 *device, uint8_t cs, uint8_t sw, uint8_t brightness);
/// Set brightness level for all LEDs.
void IS31FL3733_Fill   (IS31FL3733 *device, uint8_t brightness);

#endif /* _IS31FL3733_H_ */
