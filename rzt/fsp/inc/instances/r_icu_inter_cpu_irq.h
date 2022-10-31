/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * @addtogroup ICU_INTER_CPU_IRQ
 * @{
 **********************************************************************************************************************/

#ifndef R_ICU_INTER_CPU_IRQ_H
#define R_ICU_INTER_CPU_IRQ_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_icu_inter_cpu_irq_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
#define ICU_INTER_CPU_IRQ_CODE_VERSION_MAJOR    (1U)
#define ICU_INTER_CPU_IRQ_CODE_VERSION_MINOR    (1U)

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/* ICU_INTER_CPU_IRQ private control structure. DO NOT MODIFY. Initialization occurs when R_ICU_INTER_CPU_IRQ_Open is called. */
typedef struct st_icu_inter_cpu_irq_instance_ctrl
{
    uint32_t open;                     ///< Used to determine if channel control block is in use

    /** Pointer to the configuration block. */
    icu_inter_cpu_irq_cfg_t const * p_cfg;

    void (* p_callback)(icu_inter_cpu_irq_callback_args_t * p_args); // Pointer to callback that is called when a INTCPU is detected.

    /** Placeholder for user data.  Passed to the user callback in ::icu_inter_cpu_irq_callback_args_t. */
    void const * p_context;
} icu_inter_cpu_irq_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 ***********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const icu_inter_cpu_irq_api_t g_icu_inter_cpu_irq_on_icu;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/

fsp_err_t R_ICU_INTER_CPU_IRQ_Open(icu_inter_cpu_irq_ctrl_t * const      p_api_ctrl,
                                   icu_inter_cpu_irq_cfg_t const * const p_cfg);

fsp_err_t R_ICU_INTER_CPU_IRQ_Generate(icu_inter_cpu_irq_ctrl_t * const p_api_ctrl);

fsp_err_t R_ICU_INTER_CPU_IRQ_Close(icu_inter_cpu_irq_ctrl_t * const p_api_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup ICU_INTER_CPU_IRQ)
 ***********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_ICU_INTER_CPU_IRQ_H
