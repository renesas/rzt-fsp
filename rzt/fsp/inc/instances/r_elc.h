/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup ELC
 * @{
 **********************************************************************************************************************/

#ifndef R_ELC_H
#define R_ELC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_elc_cfg.h"
#include "r_elc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** GPT/MTU event source definitions. */
typedef enum e_elc_gpt_event_mask
{
    ELC_GPT_EVENT_MASK_OFF         = (0x3FFF3FFFU), ///< GPT Event not selected
    ELC_GPT_EVENT_MASK_GPTX_BIT_0  = (1U << 0U),    ///< GPT2n Event BIT0  mask
    ELC_GPT_EVENT_MASK_GPTX_BIT_1  = (1U << 1U),    ///< GPT2n Event BIT1  mask
    ELC_GPT_EVENT_MASK_GPTX_BIT_2  = (1U << 2U),    ///< GPT2n Event BIT2  mask
    ELC_GPT_EVENT_MASK_GPTX_BIT_3  = (1U << 3U),    ///< GPT2n Event BIT3  mask
    ELC_GPT_EVENT_MASK_GPTX_BIT_4  = (1U << 4U),    ///< GPT2n Event BIT4  mask
    ELC_GPT_EVENT_MASK_GPTX_BIT_5  = (1U << 5U),    ///< GPT2n Event BIT5  mask
    ELC_GPT_EVENT_MASK_GPTX_BIT_6  = (1U << 6U),    ///< GPT2n Event BIT6  mask
    ELC_GPT_EVENT_MASK_GPTX_BIT_7  = (1U << 7U),    ///< GPT2n Event BIT7  mask
    ELC_GPT_EVENT_MASK_GPTX_BIT_8  = (1U << 8U),    ///< GPT2n Event BIT8  mask
    ELC_GPT_EVENT_MASK_GPTX_BIT_9  = (1U << 9U),    ///< GPT2n Event BIT9  mask
    ELC_GPT_EVENT_MASK_GPTX_BIT_10 = (1U << 10U),   ///< GPT2n Event BIT10 mask
    ELC_GPT_EVENT_MASK_GPTX_BIT_11 = (1U << 11U),   ///< GPT2n Event BIT11 mask
    ELC_GPT_EVENT_MASK_GPTX_BIT_12 = (1U << 12U),   ///< GPT2n Event BIT12 mask
    ELC_GPT_EVENT_MASK_GPTX_BIT_13 = (1U << 13U),   ///< GPT2n Event BIT13 mask
    ELC_GPT_EVENT_MASK_GPTY_BIT_0  = (1U << 16U),   ///< GPT2n+1 Event BIT0  mask
    ELC_GPT_EVENT_MASK_GPTY_BIT_1  = (1U << 17U),   ///< GPT2n+1 Event BIT1  mask
    ELC_GPT_EVENT_MASK_GPTY_BIT_2  = (1U << 18U),   ///< GPT2n+1 Event BIT2  mask
    ELC_GPT_EVENT_MASK_GPTY_BIT_3  = (1U << 19U),   ///< GPT2n+1 Event BIT3  mask
    ELC_GPT_EVENT_MASK_GPTY_BIT_4  = (1U << 20U),   ///< GPT2n+1 Event BIT4  mask
    ELC_GPT_EVENT_MASK_GPTY_BIT_5  = (1U << 21U),   ///< GPT2n+1 Event BIT5  mask
    ELC_GPT_EVENT_MASK_GPTY_BIT_6  = (1U << 22U),   ///< GPT2n+1 Event BIT6  mask
    ELC_GPT_EVENT_MASK_GPTY_BIT_7  = (1U << 23U),   ///< GPT2n+1 Event BIT7  mask
    ELC_GPT_EVENT_MASK_GPTY_BIT_8  = (1U << 24U),   ///< GPT2n+1 Event BIT8  mask
    ELC_GPT_EVENT_MASK_GPTY_BIT_9  = (1U << 25U),   ///< GPT2n+1 Event BIT9  mask
    ELC_GPT_EVENT_MASK_GPTY_BIT_10 = (1U << 26U),   ///< GPT2n+1 Event BIT10 mask
    ELC_GPT_EVENT_MASK_GPTY_BIT_11 = (1U << 27U),   ///< GPT2n+1 Event BIT11 mask
    ELC_GPT_EVENT_MASK_GPTY_BIT_12 = (1U << 28U),   ///< GPT2n+1 Event BIT12 mask
    ELC_GPT_EVENT_MASK_GPTY_BIT_13 = (1U << 29U),   ///< GPT2n+1 Event BIT13 mask
} elc_gpt_event_mask_t;

#if (1 == ELC_CFG_EXTEND_SUPPORTED)

/** Extended configuration structure for ELC. */
typedef struct st_elc_extended_cfg
{
    uint32_t elc_gpt_event_mask[BSP_FEATURE_ELC_GPT_EVENT_MASK_NUM]; ///< ELC GPT Event source mask
} elc_extended_cfg_t;
#endif

/** ELC private control block. DO NOT MODIFY. Initialization occurs when R_ELC_Open() is called. */
typedef struct st_elc_instance_ctrl
{
    uint32_t open;
} elc_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const elc_api_t g_elc_on_elc;

/** @endcond */

/**********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/

fsp_err_t R_ELC_Open(elc_ctrl_t * const p_ctrl, elc_cfg_t const * const p_cfg);
fsp_err_t R_ELC_Close(elc_ctrl_t * const p_ctrl);
fsp_err_t R_ELC_SoftwareEventGenerate(elc_ctrl_t * const p_ctrl, elc_software_event_t event_number);
fsp_err_t R_ELC_LinkSet(elc_ctrl_t * const p_ctrl, elc_peripheral_t peripheral, elc_event_t signal);
fsp_err_t R_ELC_LinkBreak(elc_ctrl_t * const p_ctrl, elc_peripheral_t peripheral);
fsp_err_t R_ELC_Enable(elc_ctrl_t * const p_ctrl);
fsp_err_t R_ELC_Disable(elc_ctrl_t * const p_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_ELC_H

/*******************************************************************************************************************//**
 * @} (end defgroup ELC)
 **********************************************************************************************************************/
