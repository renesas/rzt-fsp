/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_crc.h"
#include <string.h>

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "CRC" in ASCII, used to determine if channel is open. */
#define CRC_OPEN                          (0x00435243ULL)

#define R_CRC0_CRCDOR_BY_CRCDOR_BY_Msk    (0xFFUL)
#define R_CRC0_CRCDOR_HA_CRCDOR_HA_Msk    (0xFFFFUL)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void crc_calculate_polynomial(crc_instance_ctrl_t * const p_instance_ctrl,
                                     crc_input_t * const         p_crc_input,
                                     uint32_t                  * calculatedValue);

static void     crc_seed_value_update(crc_instance_ctrl_t * const p_instance_ctrl, uint32_t crc_seed);
static uint32_t crc_calculated_value_get(crc_instance_ctrl_t * const p_instance_ctrl);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Filled in Interface API structure for this Instance. */
const crc_api_t g_crc_on_crc =
{
    .open         = R_CRC_Open,
    .close        = R_CRC_Close,
    .calculate    = R_CRC_Calculate,
    .crcResultGet = R_CRC_CalculatedValueGet,
    .snoopEnable  = R_CRC_SnoopEnable,
    .snoopDisable = R_CRC_SnoopDisable,
};

/*******************************************************************************************************************//**
 * @addtogroup CRC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Open the CRC driver module.
 *
 * Implements @ref crc_api_t::open
 *
 * Open the CRC driver module and initialize the driver control block according to the passed-in
 * configuration structure.
 *
 * @retval FSP_SUCCESS                       Configuration was successful.
 * @retval FSP_ERR_ASSERTION                 p_ctrl or p_cfg is NULL.
 * @retval FSP_ERR_ALREADY_OPEN              Module already open.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT    The requested channel does not exist on this MCU.
 **********************************************************************************************************************/
fsp_err_t R_CRC_Open (crc_ctrl_t * const p_ctrl, crc_cfg_t const * const p_cfg)
{
    crc_instance_ctrl_t * p_instance_ctrl = (crc_instance_ctrl_t *) p_ctrl;

#if CRC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_cfg);

    /* Verify the control block has not already been initialized. */
    FSP_ERROR_RETURN(CRC_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    /* Make sure this channel exists. */
    FSP_ERROR_RETURN(BSP_FEATURE_CRC_VALID_CHANNEL_MASK & (1U << p_cfg->channel), FSP_ERR_IP_CHANNEL_NOT_PRESENT);
#endif

    /* Save the configuration  */
    p_instance_ctrl->p_cfg = p_cfg;

    p_instance_ctrl->p_reg = (0U == p_cfg->channel) ? R_CRC0 : R_CRC1;

    /* Mark driver as initialized by setting the open value to the ASCII equivalent of "CRC" */
    p_instance_ctrl->open = CRC_OPEN;

    /* Power on CRC */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_START(FSP_IP_CRC, p_cfg->channel);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    uint8_t crccr0 = 0;

    /* Set bit order value */
    crccr0 = (uint8_t) (p_instance_ctrl->p_cfg->bit_order << R_CRC0_CRCCR0_LMS_Pos);

    /* Set CRC polynomial */
    crccr0 |= (uint8_t) (p_instance_ctrl->p_cfg->polynomial << R_CRC0_CRCCR0_GPS_Pos);

    /* Set DORCLR to clear CRCDOR */
    crccr0 |= (uint8_t) (1 << R_CRC0_CRCCR0_DORCLR_Pos);

    p_instance_ctrl->p_reg->CRCCR0 = crccr0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Close the CRC module driver.
 *
 * Implements @ref crc_api_t::close
 *
 * @retval FSP_SUCCESS             Configuration was successful.
 * @retval FSP_ERR_ASSERTION       p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN        The driver is not opened.
 *
 **********************************************************************************************************************/
fsp_err_t R_CRC_Close (crc_ctrl_t * const p_ctrl)
{
    crc_instance_ctrl_t * p_instance_ctrl = (crc_instance_ctrl_t *) p_ctrl;

#if CRC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(CRC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    crc_cfg_t * p_cfg = (crc_cfg_t *) p_instance_ctrl->p_cfg;

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_STOP(FSP_IP_CRC, p_cfg->channel);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    /* Mark driver as closed */
    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Perform a CRC calculation on a block of 8-bit/32-bit (for 32-bit polynomial) data.
 *
 * Implements @ref crc_api_t::calculate
 *
 * This function performs a CRC calculation on an array of 8-bit/32-bit (for 32-bit polynomial) values and
 * returns an 8-bit/32-bit (for 32-bit polynomial) calculated value
 *
 * @retval FSP_SUCCESS              Calculation successful.
 * @retval FSP_ERR_ASSERTION        Either p_ctrl, p_crc_input, inputBuffer, or calculatedValue is NULL.
 * @retval FSP_ERR_INVALID_ARGUMENT length value is NULL.
 * @retval FSP_ERR_NOT_OPEN         The driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_CRC_Calculate (crc_ctrl_t * const p_ctrl, crc_input_t * const p_crc_input, uint32_t * calculatedValue)
{
    crc_instance_ctrl_t * p_instance_ctrl = (crc_instance_ctrl_t *) p_ctrl;
#if CRC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_crc_input);
    FSP_ASSERT(p_crc_input->p_input_buffer);
    FSP_ASSERT(calculatedValue);
    FSP_ERROR_RETURN((0UL != p_crc_input->num_bytes), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(CRC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Calculate CRC value for the input buffer */
    crc_calculate_polynomial(p_instance_ctrl, p_crc_input, calculatedValue);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Return the current calculated value.
 *
 * Implements @ref crc_api_t::crcResultGet
 *
 * CRC calculation operates on a running value. This function returns the current calculated value.
 *
 * @retval FSP_SUCCESS             Return of calculated value successful.
 * @retval FSP_ERR_ASSERTION       Either p_ctrl or calculatedValue is NULL.
 * @retval FSP_ERR_NOT_OPEN        The driver is not opened.
 *
 **********************************************************************************************************************/
fsp_err_t R_CRC_CalculatedValueGet (crc_ctrl_t * const p_ctrl, uint32_t * calculatedValue)
{
    crc_instance_ctrl_t * p_instance_ctrl = (crc_instance_ctrl_t *) p_ctrl;

#if CRC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(calculatedValue);
    FSP_ERROR_RETURN(CRC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Based on the selected polynomial, return the calculated CRC value */
    *calculatedValue = crc_calculated_value_get(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @ref crc_api_t::snoopEnable is not supported on the CRC.
 *
 * @retval FSP_ERR_UNSUPPORTED         Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_CRC_SnoopEnable (crc_ctrl_t * const p_ctrl, uint32_t crc_seed)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(crc_seed);

    /* Return the unsupported error. */
    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @ref crc_api_t::snoopDisable is not supported on the CRC.
 *
 * @retval FSP_ERR_UNSUPPORTED         Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_CRC_SnoopDisable (crc_ctrl_t * const p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);

    /* Return the unsupported error. */
    return FSP_ERR_UNSUPPORTED;
}

/** @} (end addtogroup CRC) */

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Update CRC seed value
 *
 * @param[in]  p_instance_ctrl         Pointer to instance control block
 * @param[in]  crc_seed                CRC seed value
 **********************************************************************************************************************/
static void crc_seed_value_update (crc_instance_ctrl_t * const p_instance_ctrl, uint32_t crc_seed)
{
    uint32_t crcdor = 0;

    /* Based on the selected polynomial, set the initial CRC seed value */
    switch (p_instance_ctrl->p_cfg->polynomial)
    {
        case CRC_POLYNOMIAL_CRC_8:
        {
            /* CRC seed is masked to use only the lower 8 bits */
            /* Set the starting 8-bit CRC Calculated value */
            crcdor |= (uint32_t) (R_CRC0_CRCDOR_BY_CRCDOR_BY_Msk & crc_seed);
            p_instance_ctrl->p_reg->CRCDOR_BY = (uint8_t) crcdor;
            break;
        }

        case CRC_POLYNOMIAL_CRC_16:
        case CRC_POLYNOMIAL_CRC_CCITT:
        {
            /* CRC seed is masked to use only the lower 16 bits */
            /* Set the starting 16-bit CRC Calculated value. */
            crcdor |= (uint32_t) (R_CRC0_CRCDOR_HA_CRCDOR_HA_Msk & crc_seed);
            p_instance_ctrl->p_reg->CRCDOR_HA = (uint16_t) crcdor;
            break;
        }

        default:
        {
            /* CRC seed uses the 32 bits */
            p_instance_ctrl->p_reg->CRCDOR = crc_seed;
            break;
        }
    }
}

/*******************************************************************************************************************//**
 * Get CRC value
 *
 * @param[in]  p_instance_ctrl         Pointer to instance control block
 **********************************************************************************************************************/
static uint32_t crc_calculated_value_get (crc_instance_ctrl_t * const p_instance_ctrl)
{
    uint32_t calculatedValue = 0;

    /* Based on the selected polynomial, return the calculated CRC value */
    switch (p_instance_ctrl->p_cfg->polynomial)
    {
        case CRC_POLYNOMIAL_CRC_8:
        {
            /* Set bit order value */
            calculatedValue = (uint32_t) p_instance_ctrl->p_reg->CRCDOR_BY;
            break;
        }

        case CRC_POLYNOMIAL_CRC_16:
        case CRC_POLYNOMIAL_CRC_CCITT:
        {
            /* Set bit order value */
            calculatedValue = (uint32_t) p_instance_ctrl->p_reg->CRCDOR_HA;
            break;
        }

        default:
        {
            /* Set bit order value */
            calculatedValue = p_instance_ctrl->p_reg->CRCDOR;
            break;
        }
    }

    return calculatedValue;
}

/*******************************************************************************************************************//**
 * Perform a CRC calculation on a block of data.
 *
 * @param[in]  p_instance_ctrl         Pointer to instance control block
 * @param[in]  p_crc_input             Pointer to input data structure
 * @param[out] calculatedValue         Pointer to the CRC result
 *
 **********************************************************************************************************************/
static void crc_calculate_polynomial (crc_instance_ctrl_t * const p_instance_ctrl,
                                      crc_input_t * const         p_crc_input,
                                      uint32_t                  * calculatedValue)
{
    uint32_t i;
    void   * inputBuffer = p_crc_input->p_input_buffer;
    uint32_t length      = p_crc_input->num_bytes;
    uint32_t crc_seed    = p_crc_input->crc_seed;
    crc_seed_value_update(p_instance_ctrl, crc_seed);

    /* Write each element of the inputBuffer to the CRC Data Input Register. Each write to the
     * Data Input Register generates a new calculated value in the Data Output Register. */
    switch (p_instance_ctrl->p_cfg->polynomial)
    {
        case CRC_POLYNOMIAL_CRC_8:
        case CRC_POLYNOMIAL_CRC_16:
        case CRC_POLYNOMIAL_CRC_CCITT:
        {
            uint8_t * p_data = (uint8_t *) inputBuffer;
            for (i = (uint32_t) 0; i < length; i++)
            {
                /* CRCDIR is a 32-bit read/write register to write data to for CRC-32 or CRC-32C calculation.
                 * CRCDIR_BY is an 8-bit read/write register to write data to for CRC-8, CRC-16, or CRC-CCITT
                 * calculation. Reference section "CRCDIR/CRCDIR_BY : CRC Data Input Register" in the RZ
                 * microprocessor manual. Write an 8-bit value to the input register of the CRC Calculator */
                p_instance_ctrl->p_reg->CRCDIR_BY = *p_data;
                p_data = (p_data + 1UL);
            }

            break;
        }

        default:
        {
            uint32_t * p_data = (uint32_t *) inputBuffer;

            for (i = (uint32_t) 0; i < (length / 4); i++)
            {
                /* Write a 32-bit value to the input register of the CRC Calculator */
                p_instance_ctrl->p_reg->CRCDIR = *p_data;
                p_data = p_data + 1;
            }

            break;
        }
    }

    /* Return the calculated value */
    *calculatedValue = crc_calculated_value_get(p_instance_ctrl);
}
