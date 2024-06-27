/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_CMT_H
#define R_CMT_H

/*******************************************************************************************************************//**
 * @addtogroup CMT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_cmt_cfg.h"
#include "r_timer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Channel control block. DO NOT INITIALIZE.  Initialization occurs when @ref timer_api_t::open is called. */
typedef struct st_cmt_instance_ctrl
{
    uint32_t            open;                     // Whether or not channel is open
    const timer_cfg_t * p_cfg;                    // Pointer to initial configurations
    R_CMT_Type        * p_reg;                    // Base register for this channel
    timer_variant_t     variant;                  // Timer variant

    void (* p_callback)(timer_callback_args_t *); // Pointer to callback
    timer_callback_args_t * p_callback_memory;    // Pointer to optional callback argument memory
    void const            * p_context;            // Pointer to context to be passed into callback function
} cmt_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const timer_api_t g_timer_on_cmt;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_CMT_Open(timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg);
fsp_err_t R_CMT_Stop(timer_ctrl_t * const p_ctrl);
fsp_err_t R_CMT_Start(timer_ctrl_t * const p_ctrl);
fsp_err_t R_CMT_Reset(timer_ctrl_t * const p_ctrl);
fsp_err_t R_CMT_Enable(timer_ctrl_t * const p_ctrl);
fsp_err_t R_CMT_Disable(timer_ctrl_t * const p_ctrl);
fsp_err_t R_CMT_PeriodSet(timer_ctrl_t * const p_ctrl, uint32_t const period_counts);
fsp_err_t R_CMT_DutyCycleSet(timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin);
fsp_err_t R_CMT_InfoGet(timer_ctrl_t * const p_ctrl, timer_info_t * const p_info);
fsp_err_t R_CMT_StatusGet(timer_ctrl_t * const p_ctrl, timer_status_t * const p_status);
fsp_err_t R_CMT_CounterSet(timer_ctrl_t * const p_ctrl, uint32_t counter);
fsp_err_t R_CMT_CallbackSet(timer_ctrl_t * const          p_ctrl,
                            void (                      * p_callback)(timer_callback_args_t *),
                            void const * const            p_context,
                            timer_callback_args_t * const p_callback_memory);
fsp_err_t R_CMT_Close(timer_ctrl_t * const p_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup CMT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
