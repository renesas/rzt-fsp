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

#ifndef R_MTU3_PHASE_COUNT_API_H
#define R_MTU3_PHASE_COUNT_API_H

/*******************************************************************************************************************//**
 * @defgroup MTU3_PHASE_COUNT_API Phase count Interface
 * @ingroup RENESAS_INTERFACES
 * @brief Interface for phase count timer functions.
 *
 * @section MTU3_PHASE_COUNT_API_SUMMARY Summary
 * The Phase count interface provides functionality for synchronous start/stop/reset control of three timer channels for
 * use in phase count counter applications.
 *
 * Implemented by:
 * - @ref MTU3_PHASE_COUNT
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"
#include "r_timer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Leading zeroes removed to avoid coding standard violation. */
#define MTU3_PHASE_COUNT_API_VERSION_MAJOR    (1U) // DEPRECATED
#define MTU3_PHASE_COUNT_API_VERSION_MINOR    (3U) // DEPRECATED

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Timer channel indices */
typedef enum e_mtu3_phase_count_channel
{
    MTU3_PHASE_COUNT_CHANNEL_1 = 1,    ///< 1-channel index
    MTU3_PHASE_COUNT_CHANNEL_2 = 2,    ///< 2-channel index
} mtu3_phase_count_channel_t;

typedef enum e_mtu3_bit_mode
{
    MTU3_BIT_MODE_NORMAL_16BIT,        ///< normal mode(16bit mode)
    MTU3_BIT_MODE_NORMAL_32BIT,        ///< normal mode(32bit mode)
    MTU3_BIT_MODE_16BIT,               ///< 16-bit mode uses ch0-1,
    MTU3_BIT_MODE_32BIT,               ///< 32-bit mode uses ch0-2, 8
} mtu3_bit_mode_t;

typedef enum e_mtu3_external_clock
{
    MTU3_EXTERAL_CLOCK_MTCLKA_B = 0x0, ///< MTCLKA, MTCLKB
    MTU3_EXTERAL_CLOCK_MTCLKC_D = 0x1, ///< MTCLKC, MTCLKD
} mtu3_external_clock_t;

typedef enum e_mtu3_phase_counting_mode
{
    MTU3_PHASE_COUNTING_MODE_1,        ///< Mode 1
    MTU3_PHASE_COUNTING_MODE_200,      ///< Mode 2 (00)
    MTU3_PHASE_COUNTING_MODE_201,      ///< Mode 2 (01)
    MTU3_PHASE_COUNTING_MODE_210,      ///< Mode 2 (1x)
    MTU3_PHASE_COUNTING_MODE_300,      ///< Mode 3 (00)
    MTU3_PHASE_COUNTING_MODE_301,      ///< Mode 3 (01)
    MTU3_PHASE_COUNTING_MODE_310,      ///< Mode 3 (1x)
    MTU3_PHASE_COUNTING_MODE_4,        ///< Mode 4
    MTU3_PHASE_COUNTING_MODE_50,       ///< Mode 5 (0x)
    MTU3_PHASE_COUNTING_MODE_51,       ///< Mode 5 (10)
} mtu3_phase_counting_mode_t;

/** Three-Phase control block.  Allocate an instance specific control block to pass into the timer API calls.
 * @par Implemented as
 * - mtu3_phase_count_instance_ctrl_t
 */
typedef void mtu3_phase_count_ctrl_t;

/** User configuration structure, used in open function */
typedef struct st_mtu3_phase_count_cfg
{
    mtu3_phase_counting_mode_t counting_mode;    ///< Select the counting mode.
    mtu3_bit_mode_t            bit_mode;         ///< Select bit mode
    mtu3_external_clock_t      external_clock;   ///< Select External Clock Input Pins
    uint32_t period_counts;                      ///< PPR value.

    /** Select a channel corresponding to the channel number of the hardware. */
    uint8_t channel;
    timer_instance_t const   * p_timer_instance; ///< Pointer to the timer instance structs
    mtu3_phase_count_channel_t callback_ch;      ///< Channel to enable callback when using mtu3_phase_count_api_t::callbackSet
    uint32_t channel_mask;                       ///< Bitmask of timer channels used by this module

    /** Placeholder for user data.  Passed to the user callback in @ref timer_callback_args_t. */
    void const * p_context;
    void const * p_extend;                       ///< Extension parameter for hardware specific settings.
} mtu3_phase_count_cfg_t;

/** Phase Count API structure. */
typedef struct st_mtu3_phase_count_api
{
    /** Initial configuration.
     * @par Implemented as
     * - @ref R_MTU3_PHASE_COUNT_Open()
     *
     * @param[in]   p_ctrl     Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg      Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(mtu3_phase_count_ctrl_t * const p_ctrl, mtu3_phase_count_cfg_t const * const p_cfg);

    /** Start the counter.
     * @par Implemented as
     * - @ref R_MTU3_PHASE_COUNT_Start()
     *
     * @param[in]   p_ctrl     Control block set in @ref mtu3_phase_count_api_t::open call for this timer.
     */
    fsp_err_t (* start)(mtu3_phase_count_ctrl_t * const p_ctrl);

    /** Stop the counter.
     * @par Implemented as
     * - @ref R_MTU3_PHASE_COUNT_Stop()
     *
     * @param[in]   p_ctrl     Control block set in @ref mtu3_phase_count_api_t::open call for this timer.
     */
    fsp_err_t (* stop)(mtu3_phase_count_ctrl_t * const p_ctrl);

    /** Reset the counter to the initial value.
     * @par Implemented as
     * - @ref R_MTU3_PHASE_COUNT_Reset()
     *
     * @param[in]   p_ctrl     Control block set in @ref mtu3_phase_count_api_t::open call for this timer.
     */
    fsp_err_t (* reset)(mtu3_phase_count_ctrl_t * const p_ctrl);

    /** Set the location information.
     *
     * @par Implemented as
     * - @ref R_MTU3_PHASE_COUNT_PositionSet()
     *
     * @param[in]   p_ctrl         Control block set in @ref mtu3_phase_count_api_t::open call for this timer.
     * @param[in]   position       Location information. (timer counter)
     */
    fsp_err_t (* positionSet)(mtu3_phase_count_ctrl_t * const p_ctrl, uint32_t position);

    /** Get the location information.
     *
     * @par Implemented as
     * - @ref R_MTU3_PHASE_COUNT_PositionGet()
     *
     * @param[in]   p_ctrl          Control block set in @ref mtu3_phase_count_api_t::open call for this timer.
     * @param[in]   *p_position     Location information. (timer counter)
     */
    fsp_err_t (* positionGet)(mtu3_phase_count_ctrl_t * const p_ctrl, uint32_t * p_position);

    /** Set the phase counting mode.
     *
     * @par Implemented as
     * - @ref R_MTU3_PHASE_COUNT_ControlModeSet()
     *
     * @param[in]   p_ctrl           Control block set in @ref mtu3_phase_count_api_t::open call for this timer.
     * @param[in]   mode             Set the phase counting mode.
     */
    fsp_err_t (* controlmodeSet)(mtu3_phase_count_ctrl_t * const p_ctrl, mtu3_phase_counting_mode_t mode);

    /** For 16-bit mode, set speed detection.
     *
     * @par Implemented as
     * - @ref R_MTU3_PHASE_COUNT_SpeedControl()
     *
     * @param[in]   p_ctrl           Control block set in @ref mtu3_phase_count_api_t::open call for this timer.
     * @param[in]   speed            Speed detection value. (timer counter)
     */
    fsp_err_t (* speedControl)(mtu3_phase_count_ctrl_t * const p_ctrl, uint16_t speed);

    /** For 16-bit mode, get speed.
     *
     * @par Implemented as
     * - @ref R_MTU3_PHASE_COUNT_SpeedGet()
     *
     * @param[in]   p_ctrl           Control block set in @ref mtu3_phase_count_api_t::open call for this timer.
     * @param[in]   *p_speed         Speed value. (timer counter)
     */
    fsp_err_t (* speedGet)(mtu3_phase_count_ctrl_t * const p_ctrl, uint16_t * p_speed);

    /** Specify callback function and optional context pointer and working memory pointer.
     * @par Implemented as
     * - @ref R_MTU3_PHASE_COUNT_CallbackSet()
     *
     * @param[in]   p_ctrl                   Control block set in @ref mtu3_phase_count_api_t::open call.
     * @param[in]   p_callback               Callback function to register with MTU3 U-channel
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(mtu3_phase_count_ctrl_t * const p_api_ctrl, void (* p_callback)(timer_callback_args_t *),
                              void const * const p_context, timer_callback_args_t * const p_callback_memory);

    /** Allows driver to be reconfigured and may reduce power consumption.
     * @par Implemented as
     * - @ref R_MTU3_PHASE_COUNT_Close()
     *
     * @param[in]   p_ctrl     Control block set in @ref mtu3_phase_count_api_t::open call for this timer.
     */
    fsp_err_t (* close)(mtu3_phase_count_ctrl_t * const p_ctrl);

    /** DEPRECATED Get version and store it in provided pointer p_version.
     * @par Implemented as
     * - @ref R_MTU3_PHASE_COUNT_VersionGet()
     *
     * @param[out]  p_version  Code and API version used.
     */
    fsp_err_t (* versionGet)(fsp_version_t * const p_version);
} mtu3_phase_count_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_mtu3_phase_count_instance
{
    mtu3_phase_count_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    mtu3_phase_count_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    mtu3_phase_count_api_t const * p_api;  ///< Pointer to the API structure for this instance
} mtu3_phase_count_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup MTU3_PHASE_COUNT_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
