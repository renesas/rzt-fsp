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

#ifndef R_MTU3_PHASE_COUNT_H
#define R_MTU3_PHASE_COUNT_H

/*******************************************************************************************************************//**
 * @addtogroup MTU3_PHASE_COUNT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_mtu3_phase_count_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define MTU3_PHASE_COUNT_CODE_VERSION_MAJOR    (1U) // DEPRECATED
#define MTU3_PHASE_COUNT_CODE_VERSION_MINOR    (2U) // DEPRECATED

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Enable capturing Z phase */
typedef enum e_mtu3_phase_count_z_phase
{
    MTU3_PHASE_COUNT_Z_PHASE_DISABLE = 0, ///< Disable z-phase
    MTU3_PHASE_COUNT_Z_PHASE_ENABLE  = 1, ///< Enable z-phase
} mtu3_phase_count_z_phase_t;

/** Enable speed detection */
typedef enum e_mtu3_phase_count_speed_detection
{
    MTU3_PHASE_COUNT_SPEED_DETECTION_DISABLE = 0, ///< Disable speed detection
    MTU3_PHASE_COUNT_SPEED_DETECTION_ENABLE  = 1, ///< Enable speed detection
} mtu3_phase_count_speed_detection_t;

/** Channel control block. DO NOT INITIALIZE. Initialization occurs when @ref mtu3_phase_count_api_t::open is called. */
typedef struct st_mtu3_phase_count_instance_ctrl
{
    uint32_t     open;                    ///< Whether or not channel is open
    void       * p_reg;                   ///< Base register for this channel
    R_MTU_Type * p_reg_com;               ///< Base register for this channel(common ch)
    void       * p_reg_nf;                ///< Base register for this channel(noise filter)
    uint32_t     channel_mask;            ///< Bitmask of MTU3 channels used
    mtu3_phase_count_cfg_t const * p_cfg; ///< Pointer to configuration struct
} mtu3_phase_count_instance_ctrl_t;

/** The MTU3 extension constitutes a unique feature of MTU3. */
typedef struct st_mtu3_phase_count_extended_cfg
{
    mtu3_phase_count_z_phase_t         z_phase_enable; ///< Select whether capture Z phase. (32bit Mode only)
    mtu3_phase_count_speed_detection_t speed_enable;   ///< Select whether measure speed by using MTU0. (16bit Mode only)
} mtu3_phase_count_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const mtu3_phase_count_api_t g_mtu3_phase_count_on_mtu3_phase_count;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_MTU3_PHASE_COUNT_Open(mtu3_phase_count_ctrl_t * const p_ctrl, mtu3_phase_count_cfg_t const * const p_cfg);
fsp_err_t R_MTU3_PHASE_COUNT_Stop(mtu3_phase_count_ctrl_t * const p_ctrl);
fsp_err_t R_MTU3_PHASE_COUNT_Start(mtu3_phase_count_ctrl_t * const p_ctrl);
fsp_err_t R_MTU3_PHASE_COUNT_Reset(mtu3_phase_count_ctrl_t * const p_ctrl);
fsp_err_t R_MTU3_PHASE_COUNT_PositionSet(mtu3_phase_count_ctrl_t * const p_ctrl, uint32_t position);
fsp_err_t R_MTU3_PHASE_COUNT_PositionGet(mtu3_phase_count_ctrl_t * const p_ctrl, uint32_t * p_position);
fsp_err_t R_MTU3_PHASE_COUNT_ControlModeSet(mtu3_phase_count_ctrl_t * const p_ctrl, mtu3_phase_counting_mode_t mode);
fsp_err_t R_MTU3_PHASE_COUNT_SpeedControl(mtu3_phase_count_ctrl_t * const p_ctrl, uint16_t speed);
fsp_err_t R_MTU3_PHASE_COUNT_SpeedGet(mtu3_phase_count_ctrl_t * const p_ctrl, uint16_t * p_speed);
fsp_err_t R_MTU3_PHASE_COUNT_CallbackSet(mtu3_phase_count_ctrl_t * const p_ctrl,
                                         void (                        * p_callback)(timer_callback_args_t *),
                                         void const * const              p_context,
                                         timer_callback_args_t * const   p_callback_memory);
fsp_err_t R_MTU3_PHASE_COUNT_Close(mtu3_phase_count_ctrl_t * const p_ctrl);
fsp_err_t R_MTU3_PHASE_COUNT_VersionGet(fsp_version_t * const p_version);

/*******************************************************************************************************************//**
 * @} (end defgroup MTU3_PHASE_COUNT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
