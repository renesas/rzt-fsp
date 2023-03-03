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
 * @addtogroup SHARED_MEMORY
 * @{
 **********************************************************************************************************************/

#ifndef R_SHARED_MEMORY_H
#define R_SHARED_MEMORY_H

#include "bsp_api.h"
#include "r_shared_memory_cfg.h"
#include "r_shared_memory_api.h"
#include "r_icu_inter_cpu_irq_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
#define SHARED_MEMORY_CODE_VERSION_MAJOR    (1U) // DEPRECATED
#define SHARED_MEMORY_CODE_VERSION_MINOR    (2U) // DEPRECATED

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/* Extended configuration */
typedef struct st_shared_memory_extended_cfg
{
    /* For RZ/T2M */
    icu_inter_cpu_irq_instance_t const * p_software_int_tx; ///< Pointer to icu_inter_cpu_irq_instance_t to transmit
    icu_inter_cpu_irq_instance_t const * p_software_int_rx; ///< Pointer to icu_inter_cpu_irq_instance_t to receive
} shared_memory_extended_cfg_t;

/* SHARED_MEMORY control structure. DO NOT INITIALIZE. */
typedef struct st_shared_memory_instance_ctrl
{
    shared_memory_cfg_t const * p_cfg;                    // Information describing SHARED_MEMORY
    uint32_t              open;                           // Flag to determine if the device is open
    shared_memory_state_t state;                          // Connection status with communication partner

    void (* p_callback)(shared_memory_callback_args_t *); // Pointer to callback
    shared_memory_callback_args_t * p_callback_memory;    // Pointer to optional callback argument memory
    void const * p_context;                               // Pointer to context to be passed into callback function
} shared_memory_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 ***********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern shared_memory_api_t const g_shared_memory_on_shared_memory;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/

fsp_err_t R_SHARED_MEMORY_Open(shared_memory_ctrl_t * const p_api_ctrl, shared_memory_cfg_t const * const p_cfg);
fsp_err_t R_SHARED_MEMORY_Read(shared_memory_ctrl_t * const p_api_ctrl,
                               uint8_t * const              p_dest,
                               uint32_t const               offset,
                               uint32_t const               bytes);
fsp_err_t R_SHARED_MEMORY_Write(shared_memory_ctrl_t * const p_api_ctrl,
                                uint8_t * const              p_src,
                                uint32_t const               offset,
                                uint32_t const               bytes);
fsp_err_t R_SHARED_MEMORY_StatusGet(shared_memory_ctrl_t * const p_api_ctrl, shared_memory_status_t * p_status);
fsp_err_t R_SHARED_MEMORY_CallbackSet(shared_memory_ctrl_t * const p_api_ctrl,
                                      void (                     * p_callback)(
                                          shared_memory_callback_args_t *),
                                      void const * const                    p_context,
                                      shared_memory_callback_args_t * const p_callback_memory);
fsp_err_t R_SHARED_MEMORY_Close(shared_memory_ctrl_t * const p_api_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup SHARED_MEMORY)
 ***********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_SHARED_MEMORY_H
