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

/**********************************************************************************************************************
 * Includes
 *********************************************************************************************************************/
#include "r_shared_memory.h"
#include "r_shared_memory_cfg.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/* "SHARED_MEMORY" in ASCII, used to determine if channel is open. */
#define SHARED_MEMORY_OPEN           (0x0053484DULL)

#define SHARED_MEMORY_MEMORY_INIT    (0x00U)
#define SHARED_MEMORY_MEMORY_OPEN    (0x53U)

/**********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Private function prototypes
 *********************************************************************************************************************/

void r_shared_memory_callback(icu_inter_cpu_irq_callback_args_t * p_args);

/**********************************************************************************************************************
 * Private global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Global variables
 *********************************************************************************************************************/

shared_memory_api_t const g_shared_memory_on_shared_memory =
{
    .open        = R_SHARED_MEMORY_Open,
    .read        = R_SHARED_MEMORY_Read,
    .write       = R_SHARED_MEMORY_Write,
    .statusGet   = R_SHARED_MEMORY_StatusGet,
    .close       = R_SHARED_MEMORY_Close,
    .callbackSet = R_SHARED_MEMORY_CallbackSet,
};

/*******************************************************************************************************************//**
 * @addtogroup SHARED_MEMORY
 * @{
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Functions
 *********************************************************************************************************************/

/******************************************************************************************************************//**
 * Opens the shared memory driver. Implements @ref shared_memory_api_t::open().
 *
 * @retval  FSP_SUCCESS                       Module opened successfully.
 * @retval  FSP_ERR_ALREADY_OPEN              Module is already open.
 * @retval  FSP_ERR_IN_USE                    Semaphore registor selected in configuration is in use.
 * @retval  FSP_ERR_ASSERTION                 Parameter check failure due to one or more reasons below:
 *                                            1. p_api_ctrl or p_cfg is NULL.
 *                                            2. extended parameter is NULL.
 *                                            3. Callback parameter is NULL.
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *         This function calls:
 *             - @ref icu_inter_cpu_irq_api_t::open
 *             - @ref icu_inter_cpu_irq_api_t::generate
 *********************************************************************************************************************/
fsp_err_t R_SHARED_MEMORY_Open (shared_memory_ctrl_t * const p_api_ctrl, shared_memory_cfg_t const * const p_cfg)
{
    shared_memory_instance_ctrl_t * p_ctrl = (shared_memory_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err;

#if SHARED_MEMORY_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ASSERT(p_cfg != NULL);
    FSP_ASSERT(p_cfg->semaphore_reg < 8);
    FSP_ASSERT(p_cfg->p_memory != NULL);
    FSP_ASSERT(p_cfg->p_callback != NULL);
    FSP_ASSERT(p_cfg->p_extend != NULL);
    FSP_ASSERT(((shared_memory_extended_cfg_t *) p_cfg->p_extend)->p_software_int_tx != NULL);
    FSP_ASSERT(((shared_memory_extended_cfg_t *) p_cfg->p_extend)->p_software_int_rx != NULL);

    FSP_ERROR_RETURN(SHARED_MEMORY_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Check the initialization status of the shared memory. */
    FSP_ERROR_RETURN(((SHARED_MEMORY_MEMORY_INIT == p_cfg->p_memory[0]) ||
                      (SHARED_MEMORY_MEMORY_OPEN == p_cfg->p_memory[0])),
                     FSP_ERR_ALREADY_OPEN);

    R_SEM->SYTSEMFEN_b.SEMFEN = 1;     // Enable Read clear function
    R_SEM->SYTSEMF_b[p_cfg->semaphore_reg].SEMF = 1;

    /* Record the configuration for using it later */
    p_ctrl->p_cfg = p_cfg;

    /* Set callback and context pointers, if configured */
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

    icu_inter_cpu_irq_instance_t * p_software_int_tx =
        (icu_inter_cpu_irq_instance_t *) ((shared_memory_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->p_software_int_tx;
    icu_inter_cpu_irq_instance_t * p_software_int_rx =
        (icu_inter_cpu_irq_instance_t *) ((shared_memory_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->p_software_int_rx;

    ((icu_inter_cpu_irq_cfg_t *) (p_software_int_tx->p_cfg))->p_context = p_ctrl;
    err = p_software_int_tx->p_api->open(p_software_int_tx->p_ctrl, p_software_int_tx->p_cfg);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    ((icu_inter_cpu_irq_cfg_t *) (p_software_int_rx->p_cfg))->p_context = p_ctrl;
    err = p_software_int_rx->p_api->open(p_software_int_rx->p_ctrl, p_software_int_rx->p_cfg);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    if (0x00000000 == R_SEM->SYTSEMF[p_ctrl->p_cfg->semaphore_reg]) // wait Shared memory available
    {
        return FSP_ERR_IN_USE;
    }

    if (SHARED_MEMORY_MEMORY_INIT == p_ctrl->p_cfg->p_memory[0])
    {
        p_ctrl->p_cfg->p_memory[0] = SHARED_MEMORY_MEMORY_OPEN;
        __asm("dmb");                  /* Ensuring data-changing */
        p_ctrl->state = SHARED_MEMORY_STATE_NOT_READY;
    }
    else
    {
        p_ctrl->p_cfg->p_memory[0] = (uint8_t) (p_ctrl->p_cfg->p_memory[0] + SHARED_MEMORY_MEMORY_OPEN);
        __asm("dmb");                  /* Ensuring data-changing */

        err = p_software_int_tx->p_api->generate(p_software_int_tx->p_ctrl);
        if (FSP_SUCCESS != err)
        {
            return err;
        }

        p_ctrl->state = SHARED_MEMORY_STATE_READY_TO_WRITE;
    }

    R_SEM->SYTSEMF[p_ctrl->p_cfg->semaphore_reg] = 0x00000001; // Shared memory becomes available

    /* Finally, we can consider this module opened */
    p_ctrl->open = SHARED_MEMORY_OPEN;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Performs a read from the shared memory. Implements @ref shared_memory_api_t::read().
 *
 * @retval  FSP_SUCCESS        Function executed without issue
 * @retval  FSP_ERR_ASSERTION  p_api_ctrl or p_dest is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT    Invalid input parameter.
 * @retval  FSP_ERR_IN_USE     Another transfer was in progress.
 * @retval  FSP_ERR_NOT_OPEN   Module is not open.
 *********************************************************************************************************************/
fsp_err_t R_SHARED_MEMORY_Read (shared_memory_ctrl_t * const p_api_ctrl,
                                uint8_t * const              p_dest,
                                uint32_t const               offset,
                                uint32_t const               bytes)
{
    shared_memory_instance_ctrl_t * p_ctrl = (shared_memory_instance_ctrl_t *) p_api_ctrl;

#if SHARED_MEMORY_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ASSERT(p_dest != NULL);

    /* Return an error if this module have already been opened */
    FSP_ERROR_RETURN(SHARED_MEMORY_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    if ((p_ctrl->p_cfg->memory_size < (offset + bytes)) || (p_ctrl->p_cfg->memory_size < offset) ||
        (p_ctrl->p_cfg->memory_size < bytes))
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    if (0x00000000 == R_SEM->SYTSEMF[p_ctrl->p_cfg->semaphore_reg]) // wait Shared memory available
    {
        return FSP_ERR_IN_USE;
    }

    memcpy(p_dest, &p_ctrl->p_cfg->p_memory[offset], bytes);

    R_SEM->SYTSEMF[p_ctrl->p_cfg->semaphore_reg] = 0x00000001; // Shared memory becomes available

    if (SHARED_MEMORY_STATE_READY_TO_READ_WRITE == p_ctrl->state)
    {
        p_ctrl->state = SHARED_MEMORY_STATE_READY_TO_WRITE;
    }

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Performs a write to the shared memory. Implements @ref shared_memory_api_t::write().
 *
 * @retval  FSP_SUCCESS        Function executed without issue.
 * @retval  FSP_ERR_ASSERTION  p_api_ctrl or p_src is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT    Invalid input parameter.
 * @retval  FSP_ERR_IN_USE     Another transfer was in progress.
 * @retval  FSP_ERR_NOT_OPEN   Module is not open.
 *********************************************************************************************************************/
fsp_err_t R_SHARED_MEMORY_Write (shared_memory_ctrl_t * const p_api_ctrl,
                                 uint8_t * const              p_src,
                                 uint32_t const               offset,
                                 uint32_t const               bytes)
{
    shared_memory_instance_ctrl_t * p_ctrl = (shared_memory_instance_ctrl_t *) p_api_ctrl;

#if SHARED_MEMORY_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ASSERT(p_src != NULL);

    /* Return an error if this module have already been opened */
    FSP_ERROR_RETURN(SHARED_MEMORY_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    icu_inter_cpu_irq_instance_t * p_software_int_tx =
        (icu_inter_cpu_irq_instance_t *) ((shared_memory_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->p_software_int_tx;

    if ((p_ctrl->p_cfg->memory_size < (offset + bytes)) || (p_ctrl->p_cfg->memory_size < offset) ||
        (p_ctrl->p_cfg->memory_size < bytes))
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    if (0x00000000 == R_SEM->SYTSEMF[p_ctrl->p_cfg->semaphore_reg]) // wait Shared memory available
    {
        return FSP_ERR_IN_USE;
    }

    memcpy(&p_ctrl->p_cfg->p_memory[offset], p_src, bytes);
    __asm("dmb");                                              /*Ensuring data-changing */

    R_SEM->SYTSEMF[p_ctrl->p_cfg->semaphore_reg] = 0x00000001; // Shared memory becomes available

    p_software_int_tx->p_api->generate(p_software_int_tx->p_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides driver status. Implements @ref shared_memory_api_t::statusGet().
 *
 * @retval     FSP_SUCCESS                   Status is stored in p_status.
 * @retval     FSP_ERR_ASSERTION             p_api_ctrl or p_status is NULL.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 **********************************************************************************************************************/
fsp_err_t R_SHARED_MEMORY_StatusGet (shared_memory_ctrl_t * const p_api_ctrl, shared_memory_status_t * p_status)
{
    shared_memory_instance_ctrl_t * p_ctrl = (shared_memory_instance_ctrl_t *) p_api_ctrl;

#if SHARED_MEMORY_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ASSERT(p_status != NULL);

    /* Return an error if this module have already been opened */
    FSP_ERROR_RETURN(SHARED_MEMORY_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_status->state = p_ctrl->state;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements @ref shared_memory_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_SHARED_MEMORY_CallbackSet (shared_memory_ctrl_t * const p_api_ctrl,
                                       void (                     * p_callback)(
                                           shared_memory_callback_args_t *),
                                       void const * const                    p_context,
                                       shared_memory_callback_args_t * const p_callback_memory)
{
    shared_memory_instance_ctrl_t * p_ctrl = (shared_memory_instance_ctrl_t *) p_api_ctrl;

#if (SHARED_MEMORY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(SHARED_MEMORY_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */
    p_ctrl->p_callback        = p_callback;
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Closes the SHARED_MEMORY. Implements @ref shared_memory_api_t::close().
 *
 * @retval  FSP_SUCCESS         Module closed successfully.
 * @retval  FSP_ERR_NOT_OPEN    Module is not open.
 * @retval  FSP_ERR_ASSERTION   p_api_ctrl is NULL.
 *********************************************************************************************************************/
fsp_err_t R_SHARED_MEMORY_Close (shared_memory_ctrl_t * const p_api_ctrl)
{
    shared_memory_instance_ctrl_t * p_ctrl = (shared_memory_instance_ctrl_t *) p_api_ctrl;

#if SHARED_MEMORY_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);

    /* Return an error if this module have already been opened */
    FSP_ERROR_RETURN(SHARED_MEMORY_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    icu_inter_cpu_irq_instance_t * p_software_int_tx =
        (icu_inter_cpu_irq_instance_t *) ((shared_memory_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->p_software_int_tx;
    icu_inter_cpu_irq_instance_t * p_software_int_rx =
        (icu_inter_cpu_irq_instance_t *) ((shared_memory_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->p_software_int_rx;

    R_SEM->SYTSEMF_b[p_ctrl->p_cfg->semaphore_reg].SEMF = 1; // Shared memory becomes available

    p_software_int_tx->p_api->close(p_software_int_tx->p_ctrl);
    p_software_int_rx->p_api->close(p_software_int_rx->p_ctrl);

    /* This module is considered closed */
    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * @} (end addtogroup SHARED_MEMORY)
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Private Functions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Interrupt Vectors
 *********************************************************************************************************************/

/******************************************************************************************************************//**
 * Processing when an interrupt occurs from core to core.
 *********************************************************************************************************************/
void r_shared_memory_callback (icu_inter_cpu_irq_callback_args_t * p_args)
{
    shared_memory_instance_ctrl_t * p_ctrl = (shared_memory_instance_ctrl_t *) p_args->p_context;
    shared_memory_callback_args_t   args_stacked;
    shared_memory_callback_args_t   args;
    memset(&args, 0U, sizeof(shared_memory_callback_args_t));

    /* Store callback arguments in memory provided by user if available. */
    shared_memory_callback_args_t * p_args_memory = p_ctrl->p_callback_memory;

    if (NULL == p_args_memory)
    {
        /* Use provided args struct on stack */
        p_args_memory = &args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args_stacked = *p_args_memory;

        /* Copy the stacked args to callback memory */
        *p_args_memory = args;
    }

    p_args_memory->p_context = p_ctrl->p_context;

    if (SHARED_MEMORY_STATE_READY_TO_WRITE == p_ctrl->state)
    {
        p_ctrl->state        = SHARED_MEMORY_STATE_READY_TO_READ_WRITE;
        p_args_memory->state = SHARED_MEMORY_STATE_READY_TO_READ_WRITE;
    }
    else
    {
        p_ctrl->state        = SHARED_MEMORY_STATE_READY_TO_WRITE;
        p_args_memory->state = SHARED_MEMORY_STATE_READY_TO_WRITE;
    }

    p_ctrl->p_cfg->p_callback(p_args_memory);

    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args_stacked;
    }
}
