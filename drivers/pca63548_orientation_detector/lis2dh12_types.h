/*$$$LICENCE_NORDIC_STANDARD<2017>$$$*/
/** @file
 *
 * @defgroup lis2dh12_acc LIS2DH12 accelerometer
 * @{
 * @ingroup drv_acc
 * @brief Definitions of LIS2DH12 constants.
 *
 */
#ifndef __LIS2DH12_TYPES_H__
#define __LIS2DH12_TYPES_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BIT_0 0x01 /**< The value of bit 0 */
#define BIT_1 0x02 /**< The value of bit 1 */
#define BIT_2 0x04 /**< The value of bit 2 */
#define BIT_3 0x08 /**< The value of bit 3 */
#define BIT_4 0x10 /**< The value of bit 4 */
#define BIT_5 0x20 /**< The value of bit 5 */
#define BIT_6 0x40 /**< The value of bit 6 */
#define BIT_7 0x80 /**< The value of bit 7 */

/**@brief Output Data Rates (ODR). */
typedef enum
{
    LIS2DH12_ODR_1Hz                 = 0x01,   ///< High resolution/normal/low power mode    1 Hz.
    LIS2DH12_ODR_10Hz                = 0x02,   ///< High resolution/normal/low power mode   10 Hz.
    LIS2DH12_ODR_25Hz                = 0x03,   ///< High resolution/normal/low power mode   25 Hz.
    LIS2DH12_ODR_50Hz                = 0x04,   ///< High resolution/normal/low power mode   50 Hz.
    LIS2DH12_ODR_100Hz               = 0x05,   ///< High resolution/normal/low power mode  100 Hz.
    LIS2DH12_ODR_200Hz               = 0x06,   ///< High resolution/normal/low power mode  200 Hz.
    LIS2DH12_ODR_400Hz               = 0x07,   ///< High resolution/normal/low power mode  400 Hz.
    LIS2DH12_ODR_1620Hz_LP           = 0x08,   ///< Low power mode, 1620 Hz.
    LIS2DH12_ODR_1344Hz_NP_5367HZ_LP = 0x09    ///< High resolution/normal mode 1344 Hz, low power mode 5376 Hz.
} lis2dh12_ODR_t;

/**@brief Operation modes. */
typedef enum
{
    LIS2DH12_POWER_DOWN              = 0x00,   ///< Acclerometer powered down.
    LIS2DH12_LOW_POWER               = 0x01,   ///< Low power mode.
    LIS2DH12_NORMAL                  = 0x02    ///< Normal mode.
} lis2dh12_mode_t;

/**@brief Acceleration ranges. */
typedef enum
{
    LIS2DH12_FULLSCALE_2             = 0x00,   ///<  2 G full scale.
    LIS2DH12_FULLSCALE_4             = 0x01,   ///<  4 G full scale.
    LIS2DH12_FULLSCALE_8             = 0x02,   ///<  8 G full scale.
    LIS2DH12_FULLSCALE_16            = 0x03    ///< 16 G full scale.
} lis2dh12_fullscale_t;

/**@brief Axis selection. */
typedef enum
{
    LIS2DH12_X_ENABLE                = 0x01,   ///< X axis enabled.
    LIS2DH12_Y_ENABLE                = 0x02,   ///< Y axis enabled.
    LIS2DH12_Z_ENABLE                = 0x04    ///< Z axis enabled.
} lis2dh12_axis_enable_t;

/**@brief Interrupt modes. */
typedef enum
{
    LIS2DH12_INT_OR                  = 0x00,   ///< Sources are ORed.
    LIS2DH12_INT_6D_MOV              = 0x01,   ///< 6 direction movement interrupt.
    LIS2DH12_INT_AND                 = 0x02,   ///< Sources are ANDed.
    LIS2DH12_INT_6D_POS              = 0x03,   ///< 6 direction position change interrupt.
    LIS2DH12_INT_4D_MOV              = 0x05,   ///< 4 direction movement interrupt.
    LIS2DH12_INT_4D_POS              = 0x07    ///< 4 direction position interrupt.
} lis2dh12_int_mode_t;

/**@brief Interrupt pin polarity. */
typedef enum
{
    LIS2DH12_INT_ACTIVE_HIGH         = 0x00,   ///< Active hight interrupt.
    LIS2DH12_INT_ACTIVE_LOW          = 0x02    ///< Active low interrupt.
} lis2dh12_int_polarity_t;

/**@brief Click interrupt modes. */
typedef enum
{
    LIS2DH12_CLICK_SINGLE            = 0x00,    ///< Single-click interrupt.
    LIS2DH12_CLICK_DOUBLE            = 0x01     ///< Double-click interrupt.
} lis2dh12_click_mode_t;

/**@brief High-pass filter modes. */
typedef enum
{
    LIS2DH12_HP_NORMAL_RES           = 0x00,    ///< Normal mode, reference register reset when read.
    LIS2DH12_HP_REFERENCE            = 0x01,    ///< Reference mode.
    LIS2DH12_HP_NORMAL               = 0x02,    ///< Normal mode.
    LIS2DH12_HP_AUTO_RES_INT         = 0x03     ///< Autoreset upon interrupt.
} lis2dh12_hp_filter_mode_t;

/**@brief Acceleration data struct. */
typedef struct
{
    int16_t LIS2DH12_XIS_X;
    int16_t LIS2DH12_AXIS_Y;
    int16_t LIS2DH12_AXIS_Z;
} lis2dh12_acc_axes_raw_t;

// Aux status register.
#define LIS2DH12_STATUS_AUX                      0x07
#define LIS2DH12_STATUS_AUX_TOR                  BIT_6
#define LIS2DH12_STATUS_AUX_TDA                  BIT_2

// Temperature sensor data register.
#define LIS2DH12_OUT_TEMP_L                      0x0C
#define LIS2DH12_OUT_TEMP_H                      0x0D

// Device identification register.
#define LIS2DH12_WHO_AM_I                        0x0F
#define LIS2DH12_I_AM_LIS2DH12                   0x33

// Control register 0.
#define LIS2DH12_CTRL_REG0                       0x1E
#define LIS2DH12_CTRL_REG0_SDO_PU_DISC           BIT_7
#define LIS2DH12_CTRL_REG0_CORRECT_OPER          BIT_4

// Temperature configuration register.
#define LIS2DH12_TEMP_CFG_REG                    0x1F
#define LIS2DH12_TEMP_CFG_REG_TEMP1_EN           BIT_7
#define LIS2DH12_TEMP_CFG_REG_TEMP2_EN           BIT_6

// Control register 1.
#define LIS2DH12_CTRL_REG1                       0x20
#define LIS2DH12_CTRL_REG1_ODR_BITS_MASK         0xF0
#define LIS2DH12_CTRL_REG1_ODR_BIT               BIT_4
#define LIS2DH12_CTRL_REG1_LPEN                  BIT_3
#define LIS2DH12_CTRL_REG1_ZEN                   BIT_2
#define LIS2DH12_CTRL_REG1_YEN                   BIT_1
#define LIS2DH12_CTRL_REG1_XEN                   BIT_0

// Control register 2.
#define LIS2DH12_CTRL_REG2                       0x21
#define LIS2DH12_CTRL_REG2_HPM                   BIT_6
#define LIS2DH12_CTRL_REG2_HPCF                  BIT_4
#define LIS2DH12_CTRL_REG2_FDS                   BIT_3
#define LIS2DH12_CTRL_REG2_HPCLICK               BIT_2
#define LIS2DH12_CTRL_REG2_HP_IA2                BIT_1
#define LIS2DH12_CTRL_REG2_HP_IA1                BIT_0

// Control register 3.
#define LIS2DH12_CTRL_REG3                       0x22
#define LIS2DH12_CTRL_REG3_I1_CLICK              BIT_7
#define LIS2DH12_CTRL_REG3_I1_IA1                BIT_6
#define LIS2DH12_CTRL_REG3_I1_IA2                BIT_5
#define LIS2DH12_CTRL_REG3_I1_ZYXDA              BIT_4
#define LIS2DH12_CTRL_REG3_I1_WTM                BIT_2
#define LIS2DH12_CTRL_REG3_I1_ORUN               BIT_1

// Control register 4.
#define LIS2DH12_CTRL_REG4                       0x23
#define LIS2DH12_CTRL_REG4_BDU                   BIT_7
#define LIS2DH12_CTRL_REG4_BLE                   BIT_6
#define LIS2DH12_CTRL_REG4_FS1                   BIT_5
#define LIS2DH12_CTRL_REG4_FS0                   BIT_4
#define LIS2DH12_CTRL_REG4_HR                    BIT_3
#define LIS2DH12_CTRL_REG4_ST                    BIT_1
#define LIS2DH12_CTRL_REG4_SIM                   BIT_0

// Control register 5.
#define LIS2DH12_CTRL_REG5                       0x24
#define LIS2DH12_CTRL_REG5_BOOT                  BIT_7
#define LIS2DH12_CTRL_REG5_FIFO_EN               BIT_6
#define LIS2DH12_CTRL_REG5_LIR_INT1              BIT_3
#define LIS2DH12_CTRL_REG5_D4D_INT1              BIT_2
#define LIS2DH12_CTRL_REG5_LIR_INT2              BIT_1
#define LIS2DH12_CTRL_REG5_D4D_INT2              BIT_0

// Control register 6.
#define LIS2DH12_CTRL_REG6                       0x25
#define LIS2DH12_CTRL_REG_6_I2_CLICK             BIT_7
#define LIS2DH12_CTRL_REG_6_I2_IA1               BIT_6
#define LIS2DH12_CTRL_REG_6_I2_IA2               BIT_5
#define LIS2DH12_CTRL_REG_6_I2_BOOT              BIT_4
#define LIS2DH12_CTRL_REG_6_I2_ACT               BIT_3
#define LIS2DH12_CTRL_REG_6_INT_POLARITY         BIT_1

// Reference/datacapture register.
#define LIS2DH12_REFERENCE_REG                   0x26
#define LIS2DH12_REF0                            BIT_0

// Axis status register.
#define LIS2DH12_STATUS_REG                      0x27
#define LIS2DH12_ZYXOR                           BIT_7
#define LIS2DH12_ZOR                             BIT_6
#define LIS2DH12_YOR                             BIT_5
#define LIS2DH12_XOR                             BIT_4
#define LIS2DH12_ZYXDA                           BIT_3
#define LIS2DH12_ZDA                             BIT_2
#define LIS2DH12_YDA                             BIT_1
#define LIS2DH12_XDA                             BIT_0

// Acceleration data registers.
#define LIS2DH12_OUT_X_L                         0x28
#define LIS2DH12_OUT_X_H                         0x29
#define LIS2DH12_OUT_Y_L                         0x2A
#define LIS2DH12_OUT_Y_H                         0x2B
#define LIS2DH12_OUT_Z_L                         0x2C
#define LIS2DH12_OUT_Z_H                         0x2D

// FIFO registers.
#define LIS2DH12_FIFO_CTRL_REG                   0x2E
#define LIS2DH12_FIFO_CTRL_REG_FM1               BIT_7
#define LIS2DH12_FIFO_CTRL_REG_FM0               BIT_6
#define LIS2DH12_FIFO_CTRL_REG_TR                BIT_5
#define LIS2DH12_FIFO_CTRL_REG_FTH4              BIT_4
#define LIS2DH12_FIFO_CTRL_REG_FTH3              BIT_3
#define LIS2DH12_FIFO_CTRL_REG_FTH2              BIT_2
#define LIS2DH12_FIFO_CTRL_REG_FTH1              BIT_1
#define LIS2DH12_FIFO_CTRL_REG_FTH0              BIT_0

#define LIS2DH12_FIFO_SRC_REG                    0x2F
#define LIS2DH12_FIFO_SRC_REG_WTM                BIT_7
#define LIS2DH12_FIFO_SRC_REG_OVRN_INFO          BIT_6
#define LIS2DH12_FIFO_SRC_REG_EMPTY              BIT_5
#define LIS2DH12_FIFO_SRC_REG_FSS4               BIT_4
#define LIS2DH12_FIFO_SRC_REG_FSS3               BIT_3
#define LIS2DH12_FIFO_SRC_REG_FSS2               BIT_2
#define LIS2DH12_FIFO_SRC_REG_FSS1               BIT_1
#define LIS2DH12_FIFO_SRC_REG_FSS0               BIT_0

// Interrupt 1 registers.
#define LIS2DH12_INT1_CFG                        0x30
#define LIS2DH12_INT1_CFG_ANDOR                  BIT_7
#define LIS2DH12_INT1_CFG_INT_6D                 BIT_6
#define LIS2DH12_INT1_CFG_ZHIE                   BIT_5
#define LIS2DH12_INT1_CFG_ZLIE                   BIT_4
#define LIS2DH12_INT1_CFG_YHIE                   BIT_3
#define LIS2DH12_INT1_CFG_YLIE                   BIT_2
#define LIS2DH12_INT1_CFG_XHIE                   BIT_1
#define LIS2DH12_INT1_CFG_XLIE                   BIT_0

#define LIS2DH12_INT1_SRC                        0x31
#define LIS2DH12_INT1_SRC_IA                     BIT_6
#define LIS2DH12_INT1_SRC_ZH                     BIT_5
#define LIS2DH12_INT1_SRC_ZL                     BIT_4
#define LIS2DH12_INT1_SRC_YH                     BIT_3
#define LIS2DH12_INT1_SRC_YL                     BIT_2
#define LIS2DH12_INT1_SRC_XH                     BIT_1
#define LIS2DH12_INT1_SRC_XL                     BIT_0

#define LIS2DH12_INT1_THS                        0x32
#define LIS2DH12_INT1_THS_THS6                   BIT_6
#define LIS2DH12_INT1_THS_THS5                   BIT_5
#define LIS2DH12_INT1_THS_THS4                   BIT_4
#define LIS2DH12_INT1_THS_THS3                   BIT_3
#define LIS2DH12_INT1_THS_THS2                   BIT_2
#define LIS2DH12_INT1_THS_THS1                   BIT_1
#define LIS2DH12_INT1_THS_THS0                   BIT_0

#define LIS2DH12_INT1_DURATION                   0x33
#define LIS2DH12_INT1_DURATION_D6                BIT_6
#define LIS2DH12_INT1_DURATION_D5                BIT_5
#define LIS2DH12_INT1_DURATION_D4                BIT_4
#define LIS2DH12_INT1_DURATION_D3                BIT_3
#define LIS2DH12_INT1_DURATION_D2                BIT_2
#define LIS2DH12_INT1_DURATION_D1                BIT_1
#define LIS2DH12_INT1_DURATION_D0                BIT_0

// Interrupt 2 registers.
#define LIS2DH12_INT2_CFG                        0x34
#define LIS2DH12_INT2_CFG_ANDOR                  BIT_7
#define LIS2DH12_INT2_CFG_INT_6D                 BIT_6
#define LIS2DH12_INT2_CFG_ZHIE                   BIT_5
#define LIS2DH12_INT2_CFG_ZLIE                   BIT_4
#define LIS2DH12_INT2_CFG_YHIE                   BIT_3
#define LIS2DH12_INT2_CFG_YLIE                   BIT_2
#define LIS2DH12_INT2_CFG_XHIE                   BIT_1
#define LIS2DH12_INT2_CFG_XLIE                   BIT_0

#define LIS2DH12_INT2_SRC                        0x35
#define LIS2DH12_INT2_SRC_IA                     BIT_6
#define LIS2DH12_INT2_SRC_ZH                     BIT_5
#define LIS2DH12_INT2_SRC_ZL                     BIT_4
#define LIS2DH12_INT2_SRC_YH                     BIT_3
#define LIS2DH12_INT2_SRC_YL                     BIT_2
#define LIS2DH12_INT2_SRC_XH                     BIT_1
#define LIS2DH12_INT2_SRC_XL                     BIT_0

#define LIS2DH12_INT2_THS                        0x36
#define LIS2DH12_INT2_THS_THS6                   BIT_6
#define LIS2DH12_INT2_THS_THS5                   BIT_5
#define LIS2DH12_INT2_THS_THS4                   BIT_4
#define LIS2DH12_INT2_THS_THS3                   BIT_3
#define LIS2DH12_INT2_THS_THS2                   BIT_2
#define LIS2DH12_INT2_THS_THS1                   BIT_1
#define LIS2DH12_INT2_THS_THS0                   BIT_0

#define LIS2DH12_INT2_DURATION                   0x37
#define LIS2DH12_INT2_DURATION_D6                BIT_6
#define LIS2DH12_INT2_DURATION_D5                BIT_5
#define LIS2DH12_INT2_DURATION_D4                BIT_4
#define LIS2DH12_INT2_DURATION_D3                BIT_3
#define LIS2DH12_INT2_DURATION_D2                BIT_2
#define LIS2DH12_INT2_DURATION_D1                BIT_1
#define LIS2DH12_INT2_DURATION_D0                BIT_0

// Click interrupt registers.
#define LIS2DH12_CLICK_CFG                       0x38
#define LIS2DH12_CLICK_CFG_ZD                    BIT_5
#define LIS2DH12_CLICK_CFG_ZS                    BIT_4
#define LIS2DH12_CLICK_CFG_YD                    BIT_3
#define LIS2DH12_CLICK_CFG_YS                    BIT_2
#define LIS2DH12_CLICK_CFG_XD                    BIT_1
#define LIS2DH12_CLICK_CFG_XS                    BIT_0

#define LIS2DH12_CLICK_SRC                       0x39
#define LIS2DH12_CLICK_SRC_IA                    BIT_6
#define LIS2DH12_CLICK_SRC_DCLICK                BIT_5
#define LIS2DH12_CLICK_SRC_SCLICK                BIT_4
#define LIS2DH12_CLICK_SRC_SIGN                  BIT_3
#define LIS2DH12_CLICK_SRC_Z                     BIT_2
#define LIS2DH12_CLICK_SRC_Y                     BIT_1
#define LIS2DH12_CLICK_SRC_X                     BIT_0

#define LIS2DH12_CLICK_THS                       0x3A
#define LIS2DH12_CLICK_THS_LIR_CLICK             BIT_7
#define LIS2DH12_CLICK_THS_THS6                  BIT_6
#define LIS2DH12_CLICK_THS_THS5                  BIT_5
#define LIS2DH12_CLICK_THS_THS4                  BIT_4
#define LIS2DH12_CLICK_THS_THS3                  BIT_3
#define LIS2DH12_CLICK_THS_THS2                  BIT_2
#define LIS2DH12_CLICK_THS_THS1                  BIT_1
#define LIS2DH12_CLICK_THS_THS0                  BIT_0

#define LIS2DH12_TIME_LIMIT                      0x3B
#define LIS2DH12_TIME_LATENCY                    0x3C
#define LIS2DH12_TIME_WINDOW                     0x3D
#define LIS2DH12_ACT_THS                         0x3E
#define LIS2DH12_ACT_DUR                         0x3F

#define	LIS2DH12_REG_AUTO_INCREMENT	(0x40)
#define	LIS2DH12_REG_READ	(0x80)

#define LIS2DH12_BOOT_DELAY_MS       6

#ifdef __cplusplus
}
#endif

#endif /* __LIS2DH12_TYPES_H__ */

/** @} */
