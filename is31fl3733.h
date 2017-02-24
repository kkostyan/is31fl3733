/** ISSI IS31FL3733 header file.
  */
#ifndef _IS31FL3733_H_
#define _IS31FL3733_H_

#include <stdint.h>

/** Number of CS lines.
  */
#define IS31FL3733_CS (16)

/** Number of SW lines.
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
#define IS31FL3733_PSR  (0xFD) ///< Page select register. Write only.
#define IS31FL3733_PSWL (0xFE) ///< Page select register write lock. Read/Write.
#define IS31FL3733_IMR  (0xF0) ///< Interrupt mask register. Write only.
#define IS31FL3733_ISR  (0xF1) ///< Interrupt status register. Read only.

/** Registers in Page 0.
  */
#define IS31FL3733_LEDONOFF (0x0000) /// ON or OFF state control for each LED. Write only.
#define IS31FL3733_LEDOPEN  (0x0018) /// Open state for each LED. Read only.
#define IS31FL3733_LEDSHORT (0x0030) /// Short state for each LED. Read only.

/** Registers in Page 1.
  */
#define IS31FL3733_LEDPWM (0x0100) /// PWM duty for each LED. Write only.

/** Registers in Page 2.
  */
#define IS31FL3733_LEDABM (0x0200) /// Auto breath mode for each LED. Write only.

/** Registers in Page 3.
  */
#define IS31FL3733_CR    (0x0300) /// Configuration Register. Write only.
#define IS31FL3733_GCC   (0x0301) /// Global Current Control register. Write only.
#define IS31FL3733_ABM1  (0x0302) /// Auto breath control register for ABM-1. Write only.
#define IS31FL3733_ABM2  (0x0306) /// Auto breath control register for ABM-2. Write only.
#define IS31FL3733_ABM3  (0x030A) /// Auto breath control register for ABM-3. Write only.
#define IS31FL3733_TUR   (0x030E) /// Time update register. Write only.
#define IS31FL3733_SWPUR (0x030F) /// SWy Pull-Up Resistor selection register. Write only.
#define IS31FL3733_CSPDR (0x0310) /// CSx Pull-Down Resistor selection register. Write only.
#define IS31FL3733_RESET (0x0311) /// Reset register. Read only.

/// Get register page.
#define IS31FL3733_GET_PAGE(reg_addr) (uint8_t)((reg_addr) >> 8)
/// Get register 8-bit address.
#define IS31FL3733_GET_ADDR(reg_addr) (uint8_t)(reg_addr)

/// PSWL register bits.
#define IS31FL3733_PSWL_DISABLE (0x00) /// Disable write to Page Select register.
#define IS31FL3733_PSWL_ENABLE  (0xC5) /// Enable write to Page select register.

/// IMR register bits.
#define IS31FL3733_IMR_IAC (0x08) /// Auto Clear Interrupt bit.
#define IS31FL3733_IMR_IAB (0x04) /// Auto Breath Interrupt bit.
#define IS31FL3733_IMR_IS  (0x02) /// Dot Short Interrupt bit.
#define IS31FL3733_IMR_IO  (0x01) /// Dot Open Interrupt bit.

/// ISR register bits.
#define IS31FL3733_ISR_ABM3 (0x10) /// Auto Breath Mode 3 Finish Bit.
#define IS31FL3733_ISR_ABM2 (0x08) /// Auto Breath Mode 2 Finish Bit.
#define IS31FL3733_ISR_ABM1 (0x04) /// Auto Breath Mode 1 Finish Bit.
#define IS31FL3733_ISR_SB   (0x02) /// Short Bit.
#define IS31FL3733_ISR_OB   (0x01) /// Open Bit.

/// ABM register bits.
#define IS31FL3733_LEDABM_PWM  (0x00) /// PWM control mode.
#define IS31FL3733_LEDABM_ABM1 (0x01) /// Auto Breath Mode 1.
#define IS31FL3733_LEDABM_ABM2 (0x02) /// Auto Breath Mode 2.
#define IS31FL3733_LEDABM_ABM3 (0x03) /// Auto Breath Mode 3.

/// CR register bits.
#define IS31FL3733_CR_SYNC_MASTER (0x40) /// Configure as clock master device.
#define IS31FL3733_CR_SYNC_SLAVE  (0x80) /// Configure as clock slave device.
#define IS31FL3733_CR_OSD         (0x04) /// Open/Short detection enable bit.
#define IS31FL3733_CR_BEN         (0x02) /// Auto breath mode enable bit.
#define IS31FL3733_CR_SSD         (0x01) /// Software shutdown bit.

/** IS31FL3733 structure.
  */
typedef struct {
  /// Address on I2C bus.
  uint8_t address;
  /// Global Current Control value. Iout = (840 / Rext) * (GCC / 256). Rext = 20 kOhm, typically.
  uint8_t gcc;
  /// LED matrix brightness.
  uint8_t leds[IS31FL3733_CS * IS31FL3733_SW];
  /// Pointer to I2C write register function.
  uint8_t (*pfn_i2c_write_reg) (uint8_t i2c_addr, uint8_t reg_addr, uint8_t *buffer, uint8_t count);
  /// Pointer to I2C read register function.
  uint8_t (*pfn_i2c_read_reg) (uint8_t i2c_addr, uint8_t reg_addr, uint8_t *buffer, uint8_t count);
} IS31FL3733;

/// Select active page.
void IS31FL3733_SelectPage (IS31FL3733 *device, uint8_t page);
/// Write to common register.
void IS31FL3733_WriteCommonReg (IS31FL3733 *device, uint8_t reg_addr, uint8_t reg_value);
/// Write to paged register.
void IS31FL3733_WritePagedReg (IS31FL3733 *device, uint16_t reg_addr, uint8_t reg_value);
/// Init LED matrix for normal operation.
void IS31FL3733_Init (IS31FL3733 *device);
/// Update LED matrix with internal buffer values.
void IS31FL3733_Update (IS31FL3733 *device);
/// Set LED brightness level.
void IS31FL3733_SetLED (IS31FL3733 *device, uint8_t cs, uint8_t sw, uint8_t brightness);
/// Set brightness level for all LEDs.
void IS31FL3733_Fill   (IS31FL3733 *device, uint8_t brightness);

#endif /* _IS31FL3733_H_ */
