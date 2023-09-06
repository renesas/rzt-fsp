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

#ifndef R_GPT_PHASE_COUNT_API_H
#define R_GPT_PHASE_COUNT_API_H

/*******************************************************************************************************************//**
 * @defgroup GPT_PHASE_COUNT_API Phase count Interface
 * @ingroup RENESAS_INTERFACES
 * @brief Interface for phase count timer functions.
 *
 * @section GPT_PHASE_COUNT_API_SUMMARY Summary
 * The Phase count interface provides functionality for synchronous start/stop/reset control of three timer channels for
 * use in phase count counter applications.
 *
 * Implemented by:
 * - @ref GPT_PHASE_COUNT
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
#define GPT_PHASE_COUNT_API_VERSION_MAJOR    (1U) // DEPRECATED
#define GPT_PHASE_COUNT_API_VERSION_MINOR    (3U) // DEPRECATED

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Timer channel indices */
typedef enum e_gpt_phase_count_channel
{
    GPT_PHASE_COUNT_CHANNEL_0,         ///< 0-channel index
    GPT_PHASE_COUNT_CHANNEL_1,         ///< 1-channel index
    GPT_PHASE_COUNT_CHANNEL_2,         ///< 2-channel index
    GPT_PHASE_COUNT_CHANNEL_3,         ///< 3-channel index
    GPT_PHASE_COUNT_CHANNEL_4,         ///< 4-channel index
    GPT_PHASE_COUNT_CHANNEL_5,         ///< 5-channel index
    GPT_PHASE_COUNT_CHANNEL_6,         ///< 6-channel index
    GPT_PHASE_COUNT_CHANNEL_7,         ///< 7-channel index
    GPT_PHASE_COUNT_CHANNEL_8,         ///< 8-channel index
    GPT_PHASE_COUNT_CHANNEL_9,         ///< 9-channel index
    GPT_PHASE_COUNT_CHANNEL_10,        ///< 10-channel index
    GPT_PHASE_COUNT_CHANNEL_11,        ///< 11-channel index
    GPT_PHASE_COUNT_CHANNEL_12,        ///< 12-channel index
    GPT_PHASE_COUNT_CHANNEL_13,        ///< 13-channel index
    GPT_PHASE_COUNT_CHANNEL_14,        ///< 14-channel index
    GPT_PHASE_COUNT_CHANNEL_15,        ///< 15-channel index
    GPT_PHASE_COUNT_CHANNEL_16,        ///< 16-channel index
    GPT_PHASE_COUNT_CHANNEL_17,        ///< 17-channel index
} gpt_phase_count_channel_t;

typedef enum e_gpt_phase_counting_mode
{
    GPT_PHASE_COUNTING_MODE_1,         ///< Mode 1
    GPT_PHASE_COUNTING_MODE_200,       ///< Mode 2 (00)
    GPT_PHASE_COUNTING_MODE_201,       ///< Mode 2 (01)
    GPT_PHASE_COUNTING_MODE_210,       ///< Mode 2 (1x)
    GPT_PHASE_COUNTING_MODE_300,       ///< Mode 3 (00)
    GPT_PHASE_COUNTING_MODE_301,       ///< Mode 3 (01)
    GPT_PHASE_COUNTING_MODE_310,       ///< Mode 3 (1x)
    GPT_PHASE_COUNTING_MODE_4,         ///< Mode 4
    GPT_PHASE_COUNTING_MODE_50,        ///< Mode 5 (0x)
    GPT_PHASE_COUNTING_MODE_51,        ///< Mode 5 (10)
} gpt_phase_counting_mode_t;

/** Three-Phase control block.  Allocate an instance specific control block to pass into the timer API calls.
 * @par Implemented as
 * - gpt_phase_count_instance_ctrl_t
 */
typedef void gpt_phase_count_ctrl_t;

/** User configuration structure, used in open function */
typedef struct st_gpt_phase_count_cfg
{
    gpt_phase_counting_mode_t counting_mode;    ///< Select the counting mode.
    uint32_t period_counts;                     ///< PPR value.

    /** Select a channel corresponding to the channel number of the hardware. */
    uint8_t channel;
    timer_instance_t const  * p_timer_instance; ///< Pointer to the timer instance structs
    gpt_phase_count_channel_t callback_ch;      ///< Channel to enable callback when using gpt_phase_count_api_t::callbackSet
    uint32_t channel_mask;                      ///< Bitmask of timer channels used by this module

    /** Placeholder for user data.  Passed to the user callback in @ref timer_callback_args_t. */
    void const * p_context;
    void const * p_extend;                      ///< Extension parameter for hardware specific settings.
} gpt_phase_count_cfg_t;

/** Phase Count API structure. */
typedef struct st_gpt_phase_count_api
{
    /** Initial configuration.
     * @par Implemented as
     * - @ref R_GPT_PHASE_COUNT_Open()
     *
     * @param[in]   p_ctrl     Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg      Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(gpt_phase_count_ctrl_t * const p_ctrl, gpt_phase_count_cfg_t const * const p_cfg);

    /** Start all three timers synchronously.
     * @par Implemented as
     * - @ref R_GPT_PHASE_COUNT_Start()
     *
     * @param[in]   p_ctrl     Control block set in @ref gpt_phase_count_api_t::open call for this timer.
     */
    fsp_err_t (* start)(gpt_phase_count_ctrl_t * const p_ctrl);

    /** Stop all three timers synchronously.
     * @par Implemented as
     * - @ref R_GPT_PHASE_COUNT_Stop()
     *
     * @param[in]   p_ctrl     Control block set in @ref gpt_phase_count_api_t::open call for this timer.
     */
    fsp_err_t (* stop)(gpt_phase_count_ctrl_t * const p_ctrl);

    /** Reset all three timers synchronously.
     * @par Implemented as
     * - @ref R_GPT_PHASE_COUNT_Reset()
     *
     * @param[in]   p_ctrl     Control block set in @ref gpt_phase_count_api_t::open call for this timer.
     */
    fsp_err_t (* reset)(gpt_phase_count_ctrl_t * const p_ctrl);

    /** Sets the duty cycle match values.  If the timer is counting, the updated duty cycle is
     * reflected after the next timer expiration.
     *
     * @par Implemented as
     * - @ref R_GPT_PHASE_COUNT_Reset()
     *
     * @param[in]   p_ctrl             Control block set in @ref gpt_phase_count_api_t::open call for this timer.
     * @param[in]   p_position       Duty cycle values for all three timer channels.
     */
    fsp_err_t (* set)(gpt_phase_count_ctrl_t * const p_ctrl, uint32_t p_position);
    fsp_err_t (* get)(gpt_phase_count_ctrl_t * const p_ctrl, uint32_t * p_position);

    /** Specify callback function and optional context pointer and working memory pointer.
     * @par Implemented as
     * - @ref R_GPT_PHASE_COUNT_CallbackSet()
     *
     * @param[in]   p_ctrl                   Control block set in @ref gpt_phase_count_api_t::open call.
     * @param[in]   p_callback               Callback function to register with GPT U-channel
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(gpt_phase_count_ctrl_t * const p_api_ctrl, void (* p_callback)(timer_callback_args_t *),
                              void const * const p_context, timer_callback_args_t * const p_callback_memory);

    /** Allows driver to be reconfigured and may reduce power consumption.
     * @par Implemented as
     * - @ref R_GPT_PHASE_COUNT_Close()
     *
     * @param[in]   p_ctrl     Control block set in @ref gpt_phase_count_api_t::open call for this timer.
     */
    fsp_err_t (* close)(gpt_phase_count_ctrl_t * const p_ctrl);

    /** DEPRECATED Get version and store it in provided pointer p_version.
     * @par Implemented as
     * - @ref R_GPT_PHASE_COUNT_VersionGet()
     *
     * @param[out]  p_version  Code and API version used.
     */
    fsp_err_t (* versionGet)(fsp_version_t * const p_version);
} gpt_phase_count_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_gpt_phase_count_instance
{
    gpt_phase_count_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    gpt_phase_count_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    gpt_phase_count_api_t const * p_api;  ///< Pointer to the API structure for this instance
} gpt_phase_count_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup GPT_PHASE_COUNT_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
