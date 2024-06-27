/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdint.h>
#include "bsp_api.h"
#include "r_ioport.h"
#include "r_ioport_api.h"
#include "r_poe3.h"
#include "r_poe3_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "POE3" in ASCII, used to determine if channel is open. */
#define POE3_OPEN                (0x504F4533ULL)

#define POE3_PRV_STATUS_FLAGS    (R_POE3_ICSR1_POE0F_Msk)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/
void poe3_event_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* POE3 implementation of POE3 interface  */
const poe3_api_t g_poe30_on_poe3 =
{
    .open          = R_POE3_Open,
    .reset         = R_POE3_Reset,
    .outputDisable = R_POE3_OutputDisable,
    .statusGet     = R_POE3_StatusGet,
    .close         = R_POE3_Close,
    .callbackSet   = R_POE3_CallbackSet
};

/*******************************************************************************************************************//**
 * @addtogroup POE3
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes the POE3 module and applies configurations. Implements @ref poe3_api_t::open.
 *
 * @note POE0, POE4 and POE8 Mode Select setting can only be configured once after reset.
 * Reopening with a different mode configuration is not possible.
 *
 * @retval FSP_SUCCESS                    Initialization was successful.
 * @retval FSP_ERR_ASSERTION              A required input pointer is NULL.
 * @retval FSP_ERR_ALREADY_OPEN           Module is already open.
 **********************************************************************************************************************/
fsp_err_t R_POE3_Open (poe3_ctrl_t * const p_ctrl, poe3_cfg_t const * const p_cfg)
{
    poe3_instance_ctrl_t * p_instance_ctrl = (poe3_instance_ctrl_t *) p_ctrl;

#if POE3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(POE3_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Save register base address. */
    uint32_t base_address = (uint32_t) R_POE3;
    p_instance_ctrl->p_reg = (R_POE3_Type *) base_address;
    p_instance_ctrl->p_cfg = p_cfg;

    poe3_extended_cfg_t * p_extend = (poe3_extended_cfg_t *) p_cfg->p_extend;

    /* POE3 Setting Procedure */
    /* Set the M3SELR.M3BSEL[3:0] bits to 0x0 and M3SELR.M3DSEL[3:0] bits to 0x0. */

    p_instance_ctrl->p_reg->ICSR1 = (uint16_t) ((p_extend->poe0.interrupt_enable << 8) | p_extend->poe0.mode);
    p_instance_ctrl->p_reg->ICSR2 = (uint16_t) ((p_extend->poe4.interrupt_enable << 8) | p_extend->poe4.mode);
    p_instance_ctrl->p_reg->ICSR3 = (uint16_t) ((p_extend->poe8.interrupt_enable << 8) | p_extend->poe8.mode);
    p_instance_ctrl->p_reg->ICSR4 = (uint16_t) ((p_extend->poe10.interrupt_enable << 8) | p_extend->poe10.mode);
    p_instance_ctrl->p_reg->ICSR5 = (uint16_t) ((p_extend->poe11.interrupt_enable << 8) | p_extend->poe11.mode);

    p_instance_ctrl->p_reg->ICSR6 = (uint16_t) (p_cfg->oscillation_stop_hiz_output_enable << 9);

#if BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 1
    p_instance_ctrl->p_reg->ICSR7 = (uint16_t) ((p_extend->dsmif1_error << 7) | (p_extend->dsmif0_error << 6));
#elif BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 2
    p_instance_ctrl->p_reg->ICSR7 = (uint16_t) ((p_extend->dsmif1_error << 7) | (p_extend->dsmif0_error << 6) | \
                                                (p_extend->dsmif1_error_1 << 5) | (p_extend->dsmif0_error_1 << 4));
#endif

    p_instance_ctrl->p_reg->OCSR1 =
        (uint16_t) ((p_cfg->p_short_circuit_setting[0].hiz_output_enable << 9) |
                    (p_cfg->p_short_circuit_setting[0].interrupt_enable << 8));
    p_instance_ctrl->p_reg->OCSR2 =
        (uint16_t) ((p_cfg->p_short_circuit_setting[1].hiz_output_enable << 9) |
                    (p_cfg->p_short_circuit_setting[1].interrupt_enable << 8));

    /* Set the ALR1.OLSG0A and OLSG0B bits to 0 and the OLSEN bit to 1 to set MTIOC3B and MTIOC3D as active-low. */
    uint16_t temp_value = (uint16_t) (
        ((p_cfg->p_complementary_pwm_pin_setting[0].pin_setting[2].negative_pwm_pin_active_level) << 5) |
        ((p_cfg->p_complementary_pwm_pin_setting[0].pin_setting[2].positive_pwm_pin_active_level) << 4) |
        ((p_cfg->p_complementary_pwm_pin_setting[0].pin_setting[1].negative_pwm_pin_active_level) << 3) |
        ((p_cfg->p_complementary_pwm_pin_setting[0].pin_setting[1].positive_pwm_pin_active_level) << 2) |
        ((p_cfg->p_complementary_pwm_pin_setting[0].pin_setting[0].negative_pwm_pin_active_level) << 1) |
        ((p_cfg->p_complementary_pwm_pin_setting[0].pin_setting[0].positive_pwm_pin_active_level)));
    if (temp_value != 0)
    {
        temp_value |= R_POE3_ALR1_OLSEN_Msk;
    }

    p_instance_ctrl->p_reg->ALR1 = temp_value;

    /* Setting High-impedance requests to individual pins */
    p_instance_ctrl->p_reg->POECR1 = (uint8_t) (
        ((p_cfg->p_pwm_pin_setting[3].hiz_output_enable) << 3) |
        ((p_cfg->p_pwm_pin_setting[2].hiz_output_enable) << 2) |
        ((p_cfg->p_pwm_pin_setting[1].hiz_output_enable) << 1) |
        ((p_cfg->p_pwm_pin_setting[0].hiz_output_enable)));

    p_instance_ctrl->p_reg->POECR2 = (uint16_t) (
        ((p_cfg->p_complementary_pwm_pin_setting[0].pin_setting[0].hiz_output_enable) << 10) |
        ((p_cfg->p_complementary_pwm_pin_setting[0].pin_setting[1].hiz_output_enable) << 9) |
        ((p_cfg->p_complementary_pwm_pin_setting[0].pin_setting[2].hiz_output_enable) << 8) |
        ((p_cfg->p_complementary_pwm_pin_setting[1].pin_setting[0].hiz_output_enable) << 2) |
        ((p_cfg->p_complementary_pwm_pin_setting[1].pin_setting[1].hiz_output_enable) << 1) |
        ((p_cfg->p_complementary_pwm_pin_setting[1].pin_setting[2].hiz_output_enable)));

    /* Setting target pins for highimpedance control. */
    p_instance_ctrl->p_reg->M0SELR1 = (uint8_t) (
        ((p_cfg->p_pwm_pin_setting[1].pwm_pin_select) << 4) |
        ((p_cfg->p_pwm_pin_setting[0].pwm_pin_select)));

    p_instance_ctrl->p_reg->M0SELR2 = (uint8_t) (
        ((p_cfg->p_pwm_pin_setting[3].pwm_pin_select) << 4) |
        ((p_cfg->p_pwm_pin_setting[2].pwm_pin_select)));

    p_instance_ctrl->p_reg->M3SELR = (uint8_t) (
        ((p_cfg->p_complementary_pwm_pin_setting[0].pin_setting[0].negative_pwm_pin_select) << 4) |
        ((p_cfg->p_complementary_pwm_pin_setting[0].pin_setting[0].positive_pwm_pin_select)));

    p_instance_ctrl->p_reg->M4SELR1 = (uint8_t) (
        ((p_cfg->p_complementary_pwm_pin_setting[0].pin_setting[1].negative_pwm_pin_select) << 4) |
        ((p_cfg->p_complementary_pwm_pin_setting[0].pin_setting[1].positive_pwm_pin_select)));

    p_instance_ctrl->p_reg->M4SELR2 = (uint8_t) (
        ((p_cfg->p_complementary_pwm_pin_setting[0].pin_setting[2].negative_pwm_pin_select) << 4) |
        ((p_cfg->p_complementary_pwm_pin_setting[0].pin_setting[2].positive_pwm_pin_select)));

    p_instance_ctrl->p_reg->M6SELR = (uint8_t) (
        ((p_cfg->p_complementary_pwm_pin_setting[1].pin_setting[0].negative_pwm_pin_select) << 4) |
        ((p_cfg->p_complementary_pwm_pin_setting[1].pin_setting[0].positive_pwm_pin_select)));

    p_instance_ctrl->p_reg->M7SELR1 = (uint8_t) (
        ((p_cfg->p_complementary_pwm_pin_setting[1].pin_setting[1].negative_pwm_pin_select) << 4) |
        ((p_cfg->p_complementary_pwm_pin_setting[1].pin_setting[1].positive_pwm_pin_select)));

    p_instance_ctrl->p_reg->M7SELR2 = (uint8_t) (
        ((p_cfg->p_complementary_pwm_pin_setting[1].pin_setting[2].negative_pwm_pin_select) << 4) |
        ((p_cfg->p_complementary_pwm_pin_setting[1].pin_setting[2].positive_pwm_pin_select)));

    p_instance_ctrl->p_reg->POECR5 = (uint16_t) (p_extend->mtu0_control_channel_mask);
    p_instance_ctrl->p_reg->POECR4 = (uint16_t) (p_extend->mtu3_4_control_channel_mask) |
                                     (uint16_t) (p_extend->mtu6_7_control_channel_mask);

    /* Make sure the module is marked open before enabling the interrupt since the interrupt could fire immediately. */
    p_instance_ctrl->open = POE3_OPEN;

    p_instance_ctrl->p_reg->ICSR1 &= (uint16_t) ~POE3_PRV_STATUS_FLAGS;
    p_instance_ctrl->p_reg->ICSR2 &= (uint16_t) ~POE3_PRV_STATUS_FLAGS;
    p_instance_ctrl->p_reg->ICSR3 &= (uint16_t) ~POE3_PRV_STATUS_FLAGS;
    p_instance_ctrl->p_reg->ICSR6 &= (uint16_t) ~POE3_PRV_STATUS_FLAGS;
    p_instance_ctrl->p_reg->OCSR1 &= (uint16_t) ~R_POE3_OCSR1_OSF1_Msk;
    p_instance_ctrl->p_reg->OCSR2 &= (uint16_t) ~R_POE3_OCSR2_OSF2_Msk;

    /* Set callback and context pointers, if configured */
    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;

    /* Configure interrupt. */
    if (p_extend->oei1_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_extend->oei1_irq, p_extend->oei1_ipl, p_instance_ctrl);
    }

    if (p_extend->oei2_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_extend->oei2_irq, p_extend->oei2_ipl, p_instance_ctrl);
    }

    if (p_extend->oei3_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_extend->oei3_irq, p_extend->oei3_ipl, p_instance_ctrl);
    }

    if (p_extend->oei4_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_extend->oei4_irq, p_extend->oei4_ipl, p_instance_ctrl);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disables MTU3 output pins. Implements @ref poe3_api_t::outputDisable.
 *
 * @retval FSP_SUCCESS                 MTU3 output pins successfully disabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_POE3_OutputDisable (poe3_ctrl_t * const p_ctrl)
{
    poe3_instance_ctrl_t * p_instance_ctrl = (poe3_instance_ctrl_t *) p_ctrl;
#if POE3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(POE3_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->p_reg->SPOER =
        (R_POE3_SPOER_MTUCH0HIZ_Msk | R_POE3_SPOER_MTUCH67HIZ_Msk | R_POE3_SPOER_MTUCH34HIZ_Msk);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Resets status flags. Implements @ref poe3_api_t::reset.
 *
 * @note Status flags are only reset if the original POE3 trigger is resolved. Check the status using
 * @ref R_POE3_StatusGet after calling this function to verify the status is cleared.
 *
 * @retval FSP_SUCCESS                 Function attempted to clear status flags.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_POE3_Reset (poe3_ctrl_t * const p_ctrl)
{
    poe3_instance_ctrl_t * p_instance_ctrl = (poe3_instance_ctrl_t *) p_ctrl;
#if POE3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(POE3_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Recover from High-Impedance State */
    p_instance_ctrl->p_reg->ICSR1 &= (uint16_t) ~POE3_PRV_STATUS_FLAGS;
    p_instance_ctrl->p_reg->ICSR2 &= (uint16_t) ~POE3_PRV_STATUS_FLAGS;
    p_instance_ctrl->p_reg->ICSR3 &= (uint16_t) ~POE3_PRV_STATUS_FLAGS;

    p_instance_ctrl->p_reg->ICSR6 &= (uint16_t) ~POE3_PRV_STATUS_FLAGS;
    p_instance_ctrl->p_reg->OCSR1 &= (uint16_t) ~R_POE3_OCSR1_OSF1_Msk;
    p_instance_ctrl->p_reg->OCSR2 &= (uint16_t) ~R_POE3_OCSR2_OSF2_Msk;
    p_instance_ctrl->p_reg->SPOER &=
        (uint8_t) ~(R_POE3_SPOER_MTUCH0HIZ_Msk | R_POE3_SPOER_MTUCH67HIZ_Msk | R_POE3_SPOER_MTUCH34HIZ_Msk);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get current POE3 status and store it in provided pointer p_status. Implements @ref poe3_api_t::statusGet.
 *
 * @retval FSP_SUCCESS                 Current POE3 state stored successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_POE3_StatusGet (poe3_ctrl_t * const p_ctrl, poe3_status_t * const p_status)
{
    poe3_instance_ctrl_t * p_instance_ctrl = (poe3_instance_ctrl_t *) p_ctrl;

#if POE3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(POE3_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Get POE3 state. */
    p_status->state  = (poe3_state_t) ((p_instance_ctrl->p_reg->ICSR1 & R_POE3_ICSR1_POE0F_Msk) >> 12);                  // 0
    p_status->state |= (poe3_state_t) ((p_instance_ctrl->p_reg->ICSR2 & R_POE3_ICSR2_POE4F_Msk) >> 11);                  // 1
    p_status->state |= (poe3_state_t) ((p_instance_ctrl->p_reg->ICSR3 & R_POE3_ICSR3_POE8F_Msk) >> 10);                  // 2

    p_status->state |= (poe3_state_t) ((p_instance_ctrl->p_reg->ICSR6 & R_POE3_ICSR6_OSTSTF_Msk) >> 6);                  // 6

#if BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 1
    p_status->state |=
        (poe3_state_t) ((p_instance_ctrl->p_reg->ICSR7 & (R_POE3_ICSR7_DERR1ST_Msk | R_POE3_ICSR7_DERR0ST_Msk)) >> 6);   // 7,8
#elif BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 2
    p_status->state |=
        (poe3_state_t) ((p_instance_ctrl->p_reg->ICSR7 & (R_POE3_ICSR7_D1ERR0ST_Msk | R_POE3_ICSR7_D0ERR0ST_Msk)) >> 6); // 7,8
#endif

    p_status->state |= (poe3_state_t) ((p_instance_ctrl->p_reg->OCSR1 & R_POE3_OCSR1_OSF1_Msk) >> 6);                    // 9
    p_status->state |= (poe3_state_t) ((p_instance_ctrl->p_reg->OCSR2 & R_POE3_OCSR2_OSF2_Msk) >> 5);                    // 10
#if BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 2
    p_status->state |=
        (poe3_state_t) (p_instance_ctrl->p_reg->ICSR7 & (R_POE3_ICSR7_D1ERR1ST_Msk | R_POE3_ICSR7_D0ERR1ST_Msk));        // 11,12
#endif

    if ((p_instance_ctrl->p_reg->SPOER) != 0)
    {
        p_status->state |= (POE3_STATE_SOFTWARE_STOP_DISABLE_REQUEST);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disables POE3 interrupt. Implements @ref poe3_api_t::close.
 *
 * @note This function does not disable the POE3.
 *
 * @retval FSP_SUCCESS                 Successful close.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_POE3_Close (poe3_ctrl_t * const p_ctrl)
{
    poe3_instance_ctrl_t * p_instance_ctrl = (poe3_instance_ctrl_t *) p_ctrl;

#if POE3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(POE3_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Disable interrupts. */
    p_instance_ctrl->p_reg->ICSR1 &= (uint16_t) ~R_POE3_ICSR1_PIE1_Msk;
    p_instance_ctrl->p_reg->ICSR2 &= (uint16_t) ~R_POE3_ICSR2_PIE2_Msk;
    p_instance_ctrl->p_reg->ICSR3 &= (uint16_t) ~(R_POE3_ICSR3_POE8E_Msk | R_POE3_ICSR3_PIE3_Msk);
    p_instance_ctrl->p_reg->ICSR4 &= (uint16_t) ~(R_POE3_ICSR4_POE10E_Msk | R_POE3_ICSR4_PIE4_Msk);
    p_instance_ctrl->p_reg->ICSR5 &= (uint16_t) ~(R_POE3_ICSR5_POE11E_Msk | R_POE3_ICSR5_PIE5_Msk);

#if BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 1
    p_instance_ctrl->p_reg->ICSR7 &=
        (uint16_t) ~(R_POE3_ICSR7_DERR1ST_Msk | R_POE3_ICSR7_DERR0ST_Msk | R_POE3_ICSR7_DERR1IE_Msk |
                     R_POE3_ICSR7_DERR0IE_Msk);
#elif BSP_FEATURE_POE3_ERROR_SIGNAL_TYPE == 2
    p_instance_ctrl->p_reg->ICSR7 &=
        (uint16_t) ~(R_POE3_ICSR7_D1ERR0ST_Msk | R_POE3_ICSR7_D0ERR0ST_Msk | R_POE3_ICSR7_D1ERR1ST_Msk |
                     R_POE3_ICSR7_D0ERR1ST_Msk | R_POE3_ICSR7_D1ERR0IE_Msk | R_POE3_ICSR7_D0ERR0IE_Msk |
                     R_POE3_ICSR7_D1ERR1IE_Msk | R_POE3_ICSR7_D0ERR1IE_Msk);
#endif

    p_instance_ctrl->p_reg->OCSR1 &= (uint16_t) ~(R_POE3_OCSR1_OCE1_Msk | R_POE3_OCSR1_OIE1_Msk);
    p_instance_ctrl->p_reg->OCSR2 &= (uint16_t) ~(R_POE3_OCSR2_OCE2_Msk | R_POE3_OCSR2_OIE2_Msk);
    p_instance_ctrl->p_reg->SPOER &=
        (uint8_t) ~(R_POE3_SPOER_MTUCH0HIZ_Msk | R_POE3_SPOER_MTUCH67HIZ_Msk | R_POE3_SPOER_MTUCH34HIZ_Msk);

    /* Clear open flag. */
    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 * Implements @ref poe3_api_t::callbackSet.
 *
 * @retval FSP_SUCCESS                  Callback updated successfully.
 * @retval FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN             The control block has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_POE3_CallbackSet (poe3_ctrl_t * const          p_ctrl,
                              void (                     * p_callback)(poe3_callback_args_t *),
                              void const * const           p_context,
                              poe3_callback_args_t * const p_callback_memory)
{
    poe3_instance_ctrl_t * p_instance_ctrl = (poe3_instance_ctrl_t *) p_ctrl;

#if POE3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(POE3_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */
    p_instance_ctrl->p_callback        = p_callback;
    p_instance_ctrl->p_context         = p_context;
    p_instance_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/** @} (end addtogroup POE3) */

/*******************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Notifies user of POE3 event.
 **********************************************************************************************************************/
void poe3_event_isr (void)
{
    POE3_CFG_MULTIPLEX_INTERRUPT_ENABLE;

    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    poe3_callback_args_t args;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    volatile poe3_instance_ctrl_t * p_instance_ctrl = (poe3_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    poe3_callback_args_t * p_args = p_instance_ctrl->p_callback_memory;
    if (NULL == p_args)
    {
        /* Store on stack */
        p_args = &args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args;
    }

    p_args->p_context = p_instance_ctrl->p_context;

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_instance_ctrl->p_callback(p_args);

    if (NULL != p_instance_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_instance_ctrl->p_callback_memory = args;
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;

    POE3_CFG_MULTIPLEX_INTERRUPT_DISABLE;
}
