/** ISSI IS31FL3733 Auto Breath Mode (ABM) control.
  */
#ifndef _IS31FL3733_ABM_H_
#define _IS31FL3733_ABM_H_

#include "is31fl3733.h"

/// Maximum number of ABM loop times.
#define IS31FL3733_ABM_LOOP_TIMES_MAX (0x0FFF)

/// Enter to ABM endless loop.
#define IS31FL3733_ABM_LOOP_FOREVER (0x0000)

/// LED mode enumeration.
typedef enum {
  IS31FL3733_LED_MODE_PWM  = 0x00, ///< PWM control mode.
  IS31FL3733_LED_MODE_ABM1 = 0x01, ///< Auto Breath Mode 1.
  IS31FL3733_LED_MODE_ABM2 = 0x02, ///< Auto Breath Mode 2.
  IS31FL3733_LED_MODE_ABM3 = 0x03  ///< Auto Breath Mode 3.
} IS31FL3733_LED_MODE;

/// ABM T1 period time, ms.
typedef enum {
  IS31FL3733_ABM_T1_210MS   = 0x00,
  IS31FL3733_ABM_T1_420MS   = 0x20,
  IS31FL3733_ABM_T1_840MS   = 0x40,
  IS31FL3733_ABM_T1_1680MS  = 0x60,
  IS31FL3733_ABM_T1_3360MS  = 0x80,
  IS31FL3733_ABM_T1_6720MS  = 0xA0,
  IS31FL3733_ABM_T1_13440MS = 0xC0,
  IS31FL3733_ABM_T1_26880MS = 0xE0
} IS31FL3733_ABM_T1;

/// ABM T2 period time, ms.
typedef enum {
  IS31FL3733_ABM_T2_0MS     = 0x00,
  IS31FL3733_ABM_T2_210MS   = 0x02,
  IS31FL3733_ABM_T2_420MS   = 0x04,
  IS31FL3733_ABM_T2_840MS   = 0x06,
  IS31FL3733_ABM_T2_1680MS  = 0x08,
  IS31FL3733_ABM_T2_3360MS  = 0x0A,
  IS31FL3733_ABM_T2_6720MS  = 0x0C,
  IS31FL3733_ABM_T2_13440MS = 0x0E,
  IS31FL3733_ABM_T2_26880MS = 0x10
} IS31FL3733_ABM_T2;

/// ABM T3 period time, ms.
typedef enum {
  IS31FL3733_ABM_T3_210MS   = 0x00,
  IS31FL3733_ABM_T3_420MS   = 0x20,
  IS31FL3733_ABM_T3_840MS   = 0x40,
  IS31FL3733_ABM_T3_1680MS  = 0x60,
  IS31FL3733_ABM_T3_3360MS  = 0x80,
  IS31FL3733_ABM_T3_6720MS  = 0xA0,
  IS31FL3733_ABM_T3_13440MS = 0xC0,
  IS31FL3733_ABM_T3_26880MS = 0xE0
} IS31FL3733_ABM_T3;

/// ABM T4 period time, ms.
typedef enum {
  IS31FL3733_ABM_T4_0MS      = 0x00,
  IS31FL3733_ABM_T4_210MS    = 0x02,
  IS31FL3733_ABM_T4_420MS    = 0x04,
  IS31FL3733_ABM_T4_840MS    = 0x06,
  IS31FL3733_ABM_T4_1680MS   = 0x08,
  IS31FL3733_ABM_T4_3360MS   = 0x0A,
  IS31FL3733_ABM_T4_6720MS   = 0x0C,
  IS31FL3733_ABM_T4_13440MS  = 0x0E,
  IS31FL3733_ABM_T4_26880MS  = 0x10,
  IS31FL3733_ABM_T4_53760MS  = 0x12,
  IS31FL3733_ABM_T4_107520MS = 0x14
} IS31FL3733_ABM_T4;

/// ABM loop beginning time.
typedef enum {
  IS31FL3733_ABM_LOOP_BEGIN_T1 = 0x00, ///< Loop begin from T1.
  IS31FL3733_ABM_LOOP_BEGIN_T2 = 0x10, ///< Loop begin from T2.
  IS31FL3733_ABM_LOOP_BEGIN_T3 = 0x20, ///< Loop begin from T3.
  IS31FL3733_ABM_LOOP_BEGIN_T4 = 0x30  ///< Loop begin from T4.
} IS31FL3733_ABM_LOOP_BEGIN;

/// ABM loop end time.
typedef enum {
  IS31FL3733_ABM_LOOP_END_T3 = 0x00, ///< Loop end at end of T3.
  IS31FL3733_ABM_LOOP_END_T1 = 0x40  ///< Loop end at end of T1.
} IS31FL3733_ABM_LOOP_END;

/// ABM function number (also used as register offset).
typedef enum {
  IS31FL3733_ABM_NUM_1 = IS31FL3733_ABM1,
  IS31FL3733_ABM_NUM_2 = IS31FL3733_ABM2,
  IS31FL3733_ABM_NUM_3 = IS31FL3733_ABM3
} IS31FL3733_ABM_NUM;

/** Auto Breath Mode (ABM) configuration structure.
  *      +----+              +
  *     /      \            / 
  *    /        \          /  
  *   /          \        /   
  *  /            \      /    
  * +              +----+     
  * | T1 | T2 | T3 | T4 | T1 |
  *
  */
typedef struct {
  /// T1 time.
  IS31FL3733_ABM_T1 T1;
  /// T2 time.
  IS31FL3733_ABM_T2 T2;
  /// T3 time.
  IS31FL3733_ABM_T3 T3;
  /// T4 time.
  IS31FL3733_ABM_T4 T4;
  /// Loop beginning time.
  IS31FL3733_ABM_LOOP_BEGIN Tbegin;
  /// Loop end time.
  IS31FL3733_ABM_LOOP_END Tend;
  /// Total loop times.
  uint16_t Times;
} IS31FL3733_ABM;

/// Set LED operating mode: PWM/ABM1,2,3. Could be set ALL / CS / SW.
void IS31FL3733_SetLEDMode (IS31FL3733 *device, uint8_t cs, uint8_t sw, IS31FL3733_LED_MODE mode);
/// Configure ABM Mode.
void IS31FL3733_ConfigABM (IS31FL3733 *device, IS31FL3733_ABM_NUM n, IS31FL3733_ABM *config);
/// Start ABM operation.
void IS31FL3733_StartABM (IS31FL3733 *device);

#endif /* _IS31FL3733_ABM_H_ */
