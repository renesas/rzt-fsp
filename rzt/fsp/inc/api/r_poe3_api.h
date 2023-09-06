/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup POE3_API POE3 Interface
 *
 * @brief Interface for the Port Output Enable for MTU3.
 *
 * Defines the API and data structures for the Port Output Enable for MTU3 (POE3) interface.
 *
 * @section POE3_API_SUMMARY Summary
 * @brief The POE3 disables MTU3 output pins based on configurable events.
 *
 * Implemented by:
 * @ref POE3
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_POE3_API_H
#define R_POE3_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define POE3_API_VERSION_MAJOR    (1U) // DEPRECATED
#define POE3_API_VERSION_MINOR    (3U) // DEPRECATED

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** POE3 states. */
typedef enum e_poe3_state
{
    POE3_STATE_NO_DISABLE_REQUEST       = 0,               ///< MTU3 output is not disabled by POE3
    POE3_STATE_POE0_HIGH_IMPEDANCE_YES  = 1U,              ///< POE0 Flag by POE3
    POE3_STATE_POE4_HIGH_IMPEDANCE_YES  = 1U << 1,         ///< POE4 Flag by POE3
    POE3_STATE_POE8_HIGH_IMPEDANCE_YES  = 1U << 2,         ///< POE8 Flag by POE3
    POE3_STATE_POE10_HIGH_IMPEDANCE_YES = 1U << 3,         ///< POE10 Flag by POE3
    POE3_STATE_POE11_HIGH_IMPEDANCE_YES = 1U << 4,         ///< POE11 Flag by POE3

    POE3_STATE_SOFTWARE_STOP_DISABLE_REQUEST = 1U << 5,    ///< SPOER Flag by POE3

    POE3_STATE_OSCILLATION_STOP_DISABLE_REQUEST = 1U << 6, ///< MTU3 output disabled due to main oscillator stop

    POE3_STATE_DSMIF0_ERROR_REQUEST = 1U << 7,             ///< ICSR7 Flag by POE3
    POE3_STATE_DSMIF1_ERROR_REQUEST = 1U << 8,             ///< ICSR7 Flag by POE3

    POE3_STATE_OSF1_ERROR_REQUEST = 1U << 9,               ///< OCSR1 Flag by POE3
    POE3_STATE_OSF2_ERROR_REQUEST = 1U << 10,              ///< OCSR2 Flag by POE3

#if BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 2
    POE3_STATE_DSMIF0_1_ERROR_REQUEST = 1U << 11,          ///< ICSR7 Flag by POE3
    POE3_STATE_DSMIF1_1_ERROR_REQUEST = 1U << 12,          ///< ICSR7 Flag by POE3
#endif
} poe3_state_t;

/** Active level for short circuit detection. */
typedef enum e_poe3_active_level
{
    POE3_ACTIVE_LEVEL_HIGH = 0U,       ///< High level is set as the active level to detect a short circuit.
    POE3_ACTIVE_LEVEL_LOW  = 1U,       ///< Low level is set as the active level to detect a short circuit.
} poe3_active_level_t;

/** High-impedance output mode */
typedef enum e_poe3_hiz_mode
{
    POE3_HIZ_MODE_FALLING_EDGE = 0,                    ///< Accepts a request on the falling edge of POE3 pin input.
    POE3_HIZ_MODE_PCLKH_DIV_8_16_TIME_PULSE_LOW   = 1, ///< Accepts a request when POE3 pin input has been sampled 16 times at PCLKH/8 clock pulses and all are low level.
    POE3_HIZ_MODE_PCLKH_DIV_16_16_TIME_PULSE_LOW  = 2, ///< Accepts a request when POE3 pin input has been sampled 16 times at PCLKH/16 clock pulses and all are low level.
    POE3_HIZ_MODE_PCLKH_DIV_128_16_TIME_PULSE_LOW = 3  ///< Accepts a request when POE3 pin input has been sampled 16 times at PCLKH/128 clock pulses and all are low level.
} poe3_hiz_mode_t;

/** High-impedance output enable */
typedef enum e_poe3_hiz_output_enable
{
    POE3_HIZ_OUTPUT_ENABLE_DISABLED = 0, ///< Does not place the MTU complementary PWM output pins, or MTU output pins in highimpedance state.
    POE3_HIZ_OUTPUT_ENABLE_ENABLED  = 1  ///< Places the MTU complementary PWM output pins, and MTU output pins in highimpedance state.
} poe3_hiz_output_enable_t;

/** Interrupt enable */
typedef enum e_poe3_interrupt_enable
{
    POE3_INTERRUPT_ENABLE_DISABLED = 0, ///< Interrupt requests disabled.
    POE3_INTERRUPT_ENABLE_ENABLED  = 1  ///< Interrupt requests enabled.
} poe3_interrupt_enable_t;

/*----------------------------------------------------------------------------------------------------*/

/** Pin select. */
/** MTU0 Pin Select */
/* MTIOC0A Pin Select */
typedef enum e_poe3_mtioc0a_pin_select
{
    POE3_MTIOC0A_PIN_SELECT_P13_2 = 0, ///< Controls the high-impedance state of P13_2 when it is in use as the MTIOC0A pin.
    POE3_MTIOC0A_PIN_SELECT_P14_3 = 1, ///< Controls the high-impedance state of P14_3 when it is in use as the MTIOC0A pin.
    POE3_MTIOC0A_PIN_SELECT_P23_7 = 2  ///< Controls the high-impedance state of P23_7 when it is in use as the MTIOC0A pin.
} poe3_mtioc0a_pin_select_t;

/* MTIOC0B Pin Select */
typedef enum e_poe3_mtioc0b_pin_select
{
    POE3_MTIOC0B_PIN_SELECT_P11_5 = 0, ///< Controls the high-impedance state of P11_5 when it is in use as the MTIOC0B pin.
    POE3_MTIOC0B_PIN_SELECT_P14_4 = 1, ///< Controls the high-impedance state of P14_4 when it is in use as the MTIOC0B pin.
    POE3_MTIOC0B_PIN_SELECT_P24_0 = 2, ///< Controls the high-impedance state of P24_0 when it is in use as the MTIOC0B pin.
    POE3_MTIOC0B_PIN_SELECT_P13_3 = 3  ///< Controls the high-impedance state of P13_3 when it is in use as the MTIOC0B pin.
} poe3_mtioc0b_pin_select_t;

/* MTIOC0C Pin Select */
typedef enum e_poe3_mtioc0c_pin_select
{
    POE3_MTIOC0C_PIN_SELECT_P13_3 = 0, ///< Controls the high-impedance state of P13_3 when it is in use as the MTIOC0C pin.
    POE3_MTIOC0C_PIN_SELECT_P15_1 = 1, ///< Controls the high-impedance state of P15_1 when it is in use as the MTIOC0C pin.
    POE3_MTIOC0C_PIN_SELECT_P24_1 = 2  ///< Controls the high-impedance state of P24_1 when it is in use as the MTIOC0C pin.
} poe3_mtioc0c_pin_select_t;

/* MTIOC0D Pin Select */
typedef enum e_poe3_mtioc0d_pin_select
{
    POE3_MTIOC0D_PIN_SELECT_P13_4 = 0, ///< Controls the high-impedance state of P13_4 when it is in use as the MTIOC0D pin.
    POE3_MTIOC0D_PIN_SELECT_P15_2 = 1, ///< Controls the high-impedance state of P15_2 when it is in use as the MTIOC0D pin.
    POE3_MTIOC0D_PIN_SELECT_P24_2 = 2  ///< Controls the high-impedance state of P24_2 when it is in use as the MTIOC0D pin.
} poe3_mtioc0d_pin_select_t;

/** MTU3 and MTU4 Pin Select */
/* MTIOC3B Pin Select */
typedef enum e_poe3_mtioc3b_pin_select
{
    POE3_MTIOC3B_PIN_SELECT_P17_6 = 0, ///< Controls the high-impedance state of P17_6 when it is in use as the MTIOC3B pin.
    POE3_MTIOC3B_PIN_SELECT_P00_6 = 1, ///< Controls the high-impedance state of P00_6 when it is in use as the MTIOC3B pin.
#if BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 1
    POE3_MTIOC3B_PIN_SELECT_P03_6 = 2  ///< Controls the high-impedance state of P03_6 when it is in use as the MTIOC3B pin.
#elif BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 2
    POE3_MTIOC3B_PIN_SELECT_P08_6 = 2  ///< Controls the high-impedance state of P08_6 when it is in use as the MTIOC3B pin.
#endif
} poe3_mtioc3b_pin_select_t;

/* MTIOC3D Pin Select */
typedef enum e_poe3_mtioc3d_pin_select
{
    POE3_MTIOC3D_PIN_SELECT_P18_1 = 0, ///< Controls the high-impedance state of P18_1 when it is in use as the MTIOC3D pin.
    POE3_MTIOC3D_PIN_SELECT_P01_1 = 1, ///< Controls the high-impedance state of P01_1 when it is in use as the MTIOC3D pin.
#if BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 1
    POE3_MTIOC3D_PIN_SELECT_P04_0 = 2  ///< Controls the high-impedance state of P04_0 when it is in use as the MTIOC3D pin.
#elif BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 2
    POE3_MTIOC3D_PIN_SELECT_P08_7 = 2  ///< Controls the high-impedance state of P08_7 when it is in use as the MTIOC3D pin.
#endif
} poe3_mtioc3d_pin_select_t;

/* MTIOC4B Pin Select */
typedef enum e_poe3_mtioc4b_pin_select
{
    POE3_MTIOC4B_PIN_SELECT_P18_2 = 0, ///< Controls the high-impedance state of P18_2 when it is in use as the MTIOC4B pin.
    POE3_MTIOC4B_PIN_SELECT_P01_2 = 1, ///< Controls the high-impedance state of P01_2 when it is in use as the MTIOC4B pin.
#if BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 1
    POE3_MTIOC4B_PIN_SELECT_P05_1 = 2, ///< Controls the high-impedance state of P05_1 when it is in use as the MTIOC4B pin.
#elif BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 2
    POE3_MTIOC4B_PIN_SELECT_P09_2 = 2, ///< Controls the high-impedance state of P09_2 when it is in use as the MTIOC4B pin.
#endif
    POE3_MTIOC4B_PIN_SELECT_P18_3 = 3  ///< Controls the high-impedance state of P18_3 when it is in use as the MTIOC4B pin.
} poe3_mtioc4b_pin_select_t;

/* MTIOC4D Pin Select */
typedef enum e_poe3_mtioc4d_pin_select
{
    POE3_MTIOC4D_PIN_SELECT_P18_3 = 0, ///< Controls the high-impedance state of P18_3 when it is in use as the MTIOC4D pin.
    POE3_MTIOC4D_PIN_SELECT_P01_3 = 1, ///< Controls the high-impedance state of P01_3 when it is in use as the MTIOC4D pin.
#if BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 1
    POE3_MTIOC4D_PIN_SELECT_P05_3 = 2, ///< Controls the high-impedance state of P05_3 when it is in use as the MTIOC4D pin.
#elif BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 2
    POE3_MTIOC4D_PIN_SELECT_P09_3 = 2, ///< Controls the high-impedance state of P09_3 when it is in use as the MTIOC4D pin.
#endif
    POE3_MTIOC4D_PIN_SELECT_P18_2 = 3  ///< Controls the high-impedance state of P18_2 when it is in use as the MTIOC4D pin.
} poe3_mtioc4d_pin_select_t;

/* MTIOC4A Pin Select */
typedef enum e_poe3_mtioc4a_pin_select
{
    POE3_MTIOC4A_PIN_SELECT_P17_7 = 0, ///< Controls the high-impedance state of P17_7 when it is in use as the MTIOC4A pin.
#if BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 1
    POE3_MTIOC4A_PIN_SELECT_P00_7 = 1, ///< Controls the high-impedance state of P00_7 when it is in use as the MTIOC4A pin.
    POE3_MTIOC4A_PIN_SELECT_P05_0 = 2, ///< Controls the high-impedance state of P05_0 when it is in use as the MTIOC4A pin.
#elif BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 2
    POE3_MTIOC4A_PIN_SELECT_P01_5 = 1, ///< Controls the high-impedance state of P01_5 when it is in use as the MTIOC4A pin.
    POE3_MTIOC4A_PIN_SELECT_P09_0 = 2, ///< Controls the high-impedance state of P09_0 when it is in use as the MTIOC4A pin.
#endif
    POE3_MTIOC4A_PIN_SELECT_P18_0 = 3  ///< Controls the high-impedance state of P18_0 when it is in use as the MTIOC4A pin.
} poe3_mtioc4a_pin_select_t;

/* MTIOC4C Pin Select */
typedef enum e_poe3_mtioc4c_pin_select
{
    POE3_MTIOC4C_PIN_SELECT_P18_0 = 0, ///< Controls the high-impedance state of P18_0 when it is in use as the MTIOC4C pin.
    POE3_MTIOC4C_PIN_SELECT_P01_0 = 1, ///< Controls the high-impedance state of P01_0 when it is in use as the MTIOC4C pin.
#if BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 1
    POE3_MTIOC4C_PIN_SELECT_P05_2 = 2, ///< Controls the high-impedance state of P05_2 when it is in use as the MTIOC4C pin.
#elif BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 2
    POE3_MTIOC4C_PIN_SELECT_P09_1 = 2, ///< Controls the high-impedance state of P09_1 when it is in use as the MTIOC4C pin.
#endif
    POE3_MTIOC4C_PIN_SELECT_P17_7 = 3  ///< Controls the high-impedance state of P17_7 when it is in use as the MTIOC4C pin.
} poe3_mtioc4c_pin_select_t;

/** MTU6 and MTU7 Pin Select */
/* MTIOC6B Pin Select */
typedef enum e_poe3_mtioc6b_pin_select
{
    POE3_MTIOC6B_PIN_SELECT_P19_3 = 0, ///< Controls the high-impedance state of P19_3 when it is in use as the MTIOC6B pin.
    POE3_MTIOC6B_PIN_SELECT_P21_2 = 1, ///< Controls the high-impedance state of P21_2 when it is in use as the MTIOC6B pin.
    POE3_MTIOC6B_PIN_SELECT_P08_5 = 2  ///< Controls the high-impedance state of P08_5 when it is in use as the MTIOC6B pin.
} poe3_mtioc6b_pin_select_t;

/* MTIOC6D Pin Select */
typedef enum e_poe3_mtioc6d_pin_select
{
    POE3_MTIOC6D_PIN_SELECT_P19_6 = 0, ///< Controls the high-impedance state of P19_6 when it is in use as the MTIOC6D pin.
    POE3_MTIOC6D_PIN_SELECT_P21_4 = 1, ///< Controls the high-impedance state of P21_4 when it is in use as the MTIOC6D pin.
    POE3_MTIOC6D_PIN_SELECT_P08_7 = 2  ///< Controls the high-impedance state of P08_7 when it is in use as the MTIOC6D pin.
} poe3_mtioc6d_pin_select_t;

/* MTIOC7B Pin Select */
typedef enum e_poe3_mtioc7b_pin_select
{
    POE3_MTIOC7B_PIN_SELECT_P19_7 = 0, ///< Controls the high-impedance state of P19_7 when it is in use as the MTIOC7B pin.
    POE3_MTIOC7B_PIN_SELECT_P21_6 = 1, ///< Controls the high-impedance state of P21_6 when it is in use as the MTIOC7B pin.
    POE3_MTIOC7B_PIN_SELECT_P09_1 = 2  ///< Controls the high-impedance state of P09_1 when it is in use as the MTIOC7B pin.
} poe3_mtioc7b_pin_select_t;

/* MTIOC7D Pin Select */
typedef enum e_poe3_mtioc7d_pin_select
{
    POE3_MTIOC7D_PIN_SELECT_P20_0 = 0, ///< Controls the high-impedance state of P20_0 when it is in use as the MTIOC7D pin.
    POE3_MTIOC7D_PIN_SELECT_P22_0 = 1, ///< Controls the high-impedance state of P22_0 when it is in use as the MTIOC7D pin.
    POE3_MTIOC7D_PIN_SELECT_P09_3 = 2  ///< Controls the high-impedance state of P09_3 when it is in use as the MTIOC7D pin.
} poe3_mtioc7d_pin_select_t;

/* MTIOC7A Pin Select */
typedef enum e_poe3_mtioc7a_pin_select
{
    POE3_MTIOC7A_PIN_SELECT_P19_4 = 0, ///< Controls the high-impedance state of P19_4 when it is in use as the MTIOC7A pin.
    POE3_MTIOC7A_PIN_SELECT_P21_5 = 1, ///< Controls the high-impedance state of P21_5 when it is in use as the MTIOC7A pin.
    POE3_MTIOC7A_PIN_SELECT_P09_0 = 2  ///< Controls the high-impedance state of P09_0 when it is in use as the MTIOC7A pin.
} poe3_mtioc7a_pin_select_t;

/* MTIOC7C Pin Select */
typedef enum e_poe3_mtioc7c_pin_select
{
    POE3_MTIOC7C_PIN_SELECT_P19_5 = 0, ///< Controls the high-impedance state of P19_5 when it is in use as the MTIOC7C pin.
    POE3_MTIOC7C_PIN_SELECT_P21_7 = 1, ///< Controls the high-impedance state of P21_7 when it is in use as the MTIOC7C pin.
    POE3_MTIOC7C_PIN_SELECT_P09_2 = 2  ///< Controls the high-impedance state of P09_2 when it is in use as the MTIOC7C pin.
} poe3_mtioc7c_pin_select_t;

/*----------------------------------------------------------------------------------------------------*/
/** MTU0 Pin setting. */
/* MTIOC0A Pin Setting */
typedef struct st_poe3_mtioc0a_pin_setting
{
    poe3_mtioc0a_pin_select_t pin_select; ///< MTIOC0A Pin Select
    poe3_hiz_output_enable_t  hiz_output; ///< High-impedance output enable
} poe3_mtioc0a_pin_setting_t;

/* MTIOC0B Pin Setting */
typedef struct st_poe3_mtioc0b_pin_setting
{
    poe3_mtioc0b_pin_select_t pin_select; ///< MTIOC0B Pin Select
    poe3_hiz_output_enable_t  hiz_output; ///< High-impedance output enable
} poe3_mtioc0b_pin_setting_t;

/* MTIOC0C Pin Setting */
typedef struct st_poe3_mtioc0c_pin_setting
{
    poe3_mtioc0c_pin_select_t pin_select; ///< MTIOC0C Pin Select
    poe3_hiz_output_enable_t  hiz_output; ///< High-impedance output enable
} poe3_mtioc0c_pin_setting_t;

/* MTIOC0D Pin Setting */
typedef struct st_poe3_mtioc0d_pin_setting
{
    poe3_mtioc0d_pin_select_t pin_select; ///< MTIOC0D Pin Select
    poe3_hiz_output_enable_t  hiz_output; ///< High-impedance output enable
} poe3_mtioc0d_pin_setting_t;

/** MTU3 and MTU4 Pin setting. */
/* MTIOC3B and MTIOC3D Pin Setting */
typedef struct st_poe3_mtioc3b_mtioc3d_pin_setting
{
    poe3_mtioc3b_pin_select_t mtioc3b_pin_select;   ///< MTIOC3B Pin Select
    poe3_mtioc3d_pin_select_t mtioc3d_pin_select;   ///< MTIOC3D Pin Select
    poe3_active_level_t       mtioc3b_active_level; ///< Active level for short circuit detection.
    poe3_active_level_t       mtioc3d_active_level; ///< Active level for short circuit detection.
    poe3_hiz_output_enable_t  hiz_output;           ///< High-impedance output enable
} poe3_mtioc3b_mtioc3d_pin_setting_t;

/* MTIOC4B and MTIOC4D Pin Setting */
typedef struct st_poe3_mtioc4b_mtioc4d_pin_setting
{
    poe3_mtioc4b_pin_select_t mtioc4b_pin_select;   ///< MTIOC4B Pin Select
    poe3_mtioc4d_pin_select_t mtioc4d_pin_select;   ///< MTIOC4D Pin Select
    poe3_active_level_t       mtioc4b_active_level; ///< Active level for short circuit detection.
    poe3_active_level_t       mtioc4d_active_level; ///< Active level for short circuit detection.
    poe3_hiz_output_enable_t  hiz_output;           ///< High-impedance output enable
} poe3_mtioc4b_mtioc4d_pin_setting_t;

/* MTIOC4A and MTIOC4C Pin Setting */
typedef struct st_poe3_mtioc4a_mtioc4c_pin_setting
{
    poe3_mtioc4a_pin_select_t mtioc4a_pin_select;   ///< MTIOC4A Pin Select
    poe3_mtioc4c_pin_select_t mtioc4c_pin_select;   ///< MTIOC4C Pin Select
    poe3_active_level_t       mtioc4a_active_level; ///< Active level for short circuit detection.
    poe3_active_level_t       mtioc4c_active_level; ///< Active level for short circuit detection.
    poe3_hiz_output_enable_t  hiz_output;           ///< High-impedance output enable
} poe3_mtioc4a_mtioc4c_pin_setting_t;

/** MTU6 and MTU7 Pin setting. */
/* MTIOC6B and MTIOC6D Pin Setting */
typedef struct st_poe3_mtioc6b_mtioc6d_pin_setting
{
    poe3_mtioc6b_pin_select_t mtioc6b_pin_select; ///< MTIOC6B Pin Select
    poe3_mtioc6d_pin_select_t mtioc6d_pin_select; ///< MTIOC6D Pin Select
    poe3_hiz_output_enable_t  hiz_output;         ///< High-impedance output enable
} poe3_mtioc6b_mtioc6d_pin_setting_t;

/* MTIOC7B and MTIOC7D Pin Setting */
typedef struct st_poe3_mtioc7b_mtioc7d_pin_setting
{
    poe3_mtioc7b_pin_select_t mtioc7b_pin_select; ///< MTIOC7B Pin Select
    poe3_mtioc7d_pin_select_t mtioc7d_pin_select; ///< MTIOC7D Pin Select
    poe3_hiz_output_enable_t  hiz_output;         ///< High-impedance output enable
} poe3_mtioc7b_mtioc7d_pin_setting_t;

/* MTIOC7A and MTIOC7C Pin Setting */
typedef struct st_poe3_mtioc7a_mtioc7c_pin_setting
{
    poe3_mtioc7a_pin_select_t mtioc7a_pin_select; ///< MTIOC7A Pin Select
    poe3_mtioc7c_pin_select_t mtioc7c_pin_select; ///< MTIOC7C Pin Select
    poe3_hiz_output_enable_t  hiz_output;         ///< High-impedance output enable
} poe3_mtioc7a_mtioc7c_pin_setting_t;

/*----------------------------------------------------------------------------------------------------*/

/** POE0# MTU3 and MTU4 setting. */
typedef struct st_poe3_poe0_setting
{
    poe3_hiz_mode_t                    mode;            ///< High-impedance output mode
    poe3_interrupt_enable_t            interrupt;       ///< Interrupt enable
    poe3_mtioc3b_mtioc3d_pin_setting_t mtioc3b_mtioc3d; ///< MTIOC3B, MTIOC3D Pin Select
    poe3_mtioc4b_mtioc4d_pin_setting_t mtioc4b_mtioc4d; ///< MTIOC4B, MTIOC4D Pin Select
    poe3_mtioc4a_mtioc4c_pin_setting_t mtioc4a_mtioc4c; ///< MTIOC4A, MTIOC4C Pin Select
} poe3_poe0_setting_t;

/** POE4# MTU6 and MTU7 setting. */
typedef struct st_poe3_poe4_setting
{
    poe3_hiz_mode_t                    mode;            ///< High-impedance output mode
    poe3_interrupt_enable_t            interrupt;       ///< Interrupt enable
    poe3_mtioc6b_mtioc6d_pin_setting_t mtioc6b_mtioc6d; ///< MTIOC6B, MTIOC6D Pin Select
    poe3_mtioc7b_mtioc7d_pin_setting_t mtioc7b_mtioc7d; ///< MTIOC7B, MTIOC7D Pin Select
    poe3_mtioc7a_mtioc7c_pin_setting_t mtioc7a_mtioc7c; ///< MTIOC7A, MTIOC7C Pin Select
} poe3_poe4_setting_t;

/** POE8# MTU0 setting. */
typedef struct st_poe3_poe8_setting
{
    poe3_hiz_mode_t            mode;      ///< High-impedance output mode
    poe3_interrupt_enable_t    interrupt; ///< Interrupt enable
    poe3_mtioc0a_pin_setting_t mtioc0a;   ///< MTIOC0A Pin Select
    poe3_mtioc0b_pin_setting_t mtioc0b;   ///< MTIOC0B Pin Select
    poe3_mtioc0c_pin_setting_t mtioc0c;   ///< MTIOC0C Pin Select
    poe3_mtioc0d_pin_setting_t mtioc0d;   ///< MTIOC0D Pin Select
} poe3_poe8_setting_t;

/** POE10# setting. */
typedef struct st_poe3_poe10_setting
{
    poe3_hiz_mode_t         mode;      ///< High-impedance output mode
    poe3_interrupt_enable_t interrupt; ///< Interrupt enable
} poe3_poe10_setting_t;

/** POE11# setting. */
typedef struct st_poe3_poe11_setting
{
    poe3_hiz_mode_t         mode;      ///< High-impedance output mode
    poe3_interrupt_enable_t interrupt; ///< Interrupt enable
} poe3_poe11_setting_t;

/** Output short circuit setting. */
typedef struct st_poe3_output_short_circuit_setting
{
    poe3_interrupt_enable_t  interrupt;  ///< Interrupt enable
    poe3_hiz_output_enable_t hiz_output; ///< High-impedance output enable
} poe3_output_short_circuit_setting_t;

/** POE3 status */
typedef struct st_poe3_status
{
    poe3_state_t state;                ///< Current state of POE3
} poe3_status_t;

/** Callback function parameter data. */
typedef struct st_poe3_callback_args
{
    void const * p_context;            ///< Placeholder for user data, set in @ref poe3_cfg_t.
} poe3_callback_args_t;

/** DOC control block.  Allocate an instance specific control block to pass into the DOC API calls.
 * @par Implemented as
 * - @ref poe3_instance_ctrl_t
 */
typedef void poe3_ctrl_t;

/** User configuration structure, used in the open function. */
typedef struct st_poe3_cfg
{
    poe3_poe0_setting_t      poe0;                      ///< Setting for the POE0#.
    poe3_poe4_setting_t      poe4;                      ///< Setting for the POE4#.
    poe3_poe8_setting_t      poe8;                      ///< Setting for the POE8#.
    poe3_poe10_setting_t     poe10;                     ///< Setting for the POE10#.
    poe3_poe10_setting_t     poe11;                     ///< Setting for the POE11#.
    poe3_hiz_output_enable_t oscillation_stop;          ///< High impedance output when the oscillator is stopped.
#if BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 2
    poe3_hiz_output_enable_t dsmif0_error_1;            ///< High impedance output when the DSMIF0 Error 1 is error.
    poe3_hiz_output_enable_t dsmif1_error_1;            ///< High impedance output when the DSMIF1 Error 1 is error.
#endif
    poe3_hiz_output_enable_t            dsmif0_error;   ///< High impedance output when the DSMIF0 is error.
    poe3_hiz_output_enable_t            dsmif1_error;   ///< High impedance output when the DSMIF1 is error.
    poe3_output_short_circuit_setting_t short_circuit1; ///< High impedance output when the output short circuit 1.
    poe3_output_short_circuit_setting_t short_circuit2; ///< High impedance output when the output short circuit 2.

    /** Callback called when a POE3 interrupt occurs. */
    void (* p_callback)(poe3_callback_args_t * p_args);

    /** Placeholder for user data. Passed to the user callback in @ref poe3_callback_args_t. */
    void const * p_context;
} poe3_cfg_t;

/** Port Output Enable for MTU3 (POE3) API structure. POE3 functions implemented at the HAL layer will follow this API. */
typedef struct st_poe3_api
{
    /** Initial configuration.
     * @par Implemented as
     * - @ref R_POE3_Open()
     *
     * @param[in]   p_ctrl      Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg       Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(poe3_ctrl_t * const p_ctrl, poe3_cfg_t const * const p_cfg);

    /** Gets the current driver state.
     * @par Implemented as
     * - @ref R_POE3_StatusGet()
     *
     * @param[in]   p_ctrl      Control block set in @ref poe3_api_t::open call.
     * @param[out]  p_status    Provides the current state of the POE3.
     */
    fsp_err_t (* statusGet)(poe3_ctrl_t * const p_ctrl, poe3_status_t * p_status);

    /** Disables MTU3 output pins by software request.
     * @par Implemented as
     * - @ref R_POE3_OutputDisable()
     *
     * @param[in]   p_ctrl      Control block set in @ref poe3_api_t::open call.
     */
    fsp_err_t (* outputDisable)(poe3_ctrl_t * const p_ctrl);

    /** Attempts to clear status flags to reenable MTU3 output pins. Confirm all status flags are cleared after calling
     * this function by calling poe3_api_t::statusGet().
     * @par Implemented as
     * - @ref R_POE3_Reset()
     *
     * @param[in]   p_ctrl      Control block set in @ref poe3_api_t::open call.
     */
    fsp_err_t (* reset)(poe3_ctrl_t * const p_ctrl);

    /** Disables POE3 interrupt.
     * @par Implemented as
     * - @ref R_POE3_Close()
     *
     * @param[in]   p_ctrl      Control block set in @ref poe3_api_t::open call.
     */
    fsp_err_t (* close)(poe3_ctrl_t * const p_ctrl);

    /** DEPRECATED - Get version and stores it in provided pointer p_version.
     * @par Implemented as
     * - @ref R_POE3_VersionGet()
     *
     * @param[out]  p_version  Code and API version used.
     */
    fsp_err_t (* versionGet)(fsp_version_t * const p_version);
} poe3_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_poe3_instance
{
    poe3_ctrl_t      * p_ctrl;         ///< Pointer to the control structure for this instance
    poe3_cfg_t const * p_cfg;          ///< Pointer to the configuration structure for this instance
    poe3_api_t const * p_api;          ///< Pointer to the API structure for this instance
} poe3_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end addtogroup POE3_API)
 **********************************************************************************************************************/
