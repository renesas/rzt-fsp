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

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

#include <r_dsmif_cfg.h>
#include "bsp_api.h"
#include "r_adc_api.h"
#include "r_dsmif.h"

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define DSMIF_VALID_UNIT_MASK      (0x3U) /* Unit0-1 */

#define DSMIF_CMSH_DEFAULT         (0x0U)

#define VECNUM_DSMIF0_CDRUI        ((IRQn_Type) 343)
#define VECNUM_DSMIF1_CDRUI        ((IRQn_Type) 344)

#define DSMIF_OPEN                 (0x44534D49U)

#define DSMIF_DATA_TYPE_MASK       (0x0300U)
#define DSMIF_DATA_CHANNEL_MASK    (0x0003U)
#define DSMIF_DATA_TYPE_SHIFT      (0x8U)

#define DSMIF_REGID_MASK           (0x000000FFU)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

#if (1 == DSMIF_CFG_PARAM_CHECKING_ENABLE)

static fsp_err_t r_dsmif_open_param_check(dsmif_instance_ctrl_t * const p_instance_ctrl, adc_cfg_t const * const p_cfg);

#endif

static void      r_dsmif_start(dsmif_instance_ctrl_t * const p_instance_ctrl);
static fsp_err_t r_dsmif_stop(dsmif_instance_ctrl_t * const p_instance_ctrl);
static void      r_dsmif_open_irq_cfg(dsmif_instance_ctrl_t * const p_instance_ctrl, adc_cfg_t const * const p_cfg);
static void      r_dsmif_disable_irq(IRQn_Type irq);

/** Version data structure used by error logger macro. */
static const fsp_version_t g_dsmif_version =
{
    .api_version_minor  = ADC_API_VERSION_MINOR,
    .api_version_major  = ADC_API_VERSION_MAJOR,
    .code_version_major = DSMIF_CODE_VERSION_MAJOR,
    .code_version_minor = DSMIF_CODE_VERSION_MINOR
};

void dsmif_cdrui_isr(void);

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/** DSMIF Implementation of DSMIF interface. */
const adc_api_t g_adc_on_dsmif =
{
    .open          = R_DSMIF_Open,
    .scanStart     = R_DSMIF_ScanStart,
    .scanStop      = R_DSMIF_ScanStop,
    .scanStatusGet = R_DSMIF_StatusGet,
    .read32        = R_DSMIF_Read,
    .close         = R_DSMIF_Close,
    .versionGet    = R_DSMIF_VersionGet
};

/*******************************************************************************************************************//**
 * @addtogroup DSMIF
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Applies power to the DSMIF and initializes the hardware based on the user configuration.
 * As part of this initialization, set interrupts, set DSMIF error interrupt registers, etc.
 *
 * @note The DSMIF error interrupt is PERI_ERR0, which is an interrupt handler common to other modules,
 *       so IRQ interrupts are not allowed here.
 *
 * @retval  FSP_SUCCESS                 Configuration successful.
 * @retval  FSP_ERR_ASSERTION           An input pointer is NULL or an input parameter is invalid.
 * @retval  FSP_ERR_ALREADY_OPEN        Control block is already open.
 * @retval  FSP_ERR_IRQ_BSP_DISABLED    A required interrupt is disabled
 * @retval  FSP_ERR_IP_UNIT_NOT_PRESENT The Unit requested in the p_cfg parameter is not available on this device.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_Open (adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg)
{
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) p_ctrl;
    fsp_err_t               err             = FSP_SUCCESS;

#if (1 == DSMIF_CFG_PARAM_CHECKING_ENABLE)
    err = r_dsmif_open_param_check(p_instance_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Set all p_instance_ctrl fields prior to using it in any functions. */
    p_instance_ctrl->p_cfg = p_cfg;

    p_instance_ctrl->p_callback = p_cfg->p_callback;
    p_instance_ctrl->p_context  = p_cfg->p_context;
    p_instance_ctrl->mode       = p_cfg->mode;

    /* Configure and enable interrupts. */
    r_dsmif_open_irq_cfg(p_instance_ctrl, p_cfg);

    dsmif_extended_cfg_t const * p_cfg_extend = p_cfg->p_extend;

    /* mask_bit DSMIF unit0 0-2bit, DSMIF unit1 0-2bit */
    /* Calculate the register base address. */
    uint32_t base_address;
    if (0U == p_cfg->unit)
    {
        p_instance_ctrl->channel_mask = p_cfg_extend->channel_mask;
        base_address = (uint32_t) R_DSMIF0;
    }
    else
    {
        p_instance_ctrl->channel_mask = (p_cfg_extend->channel_mask >> 3U);
        base_address = (uint32_t) R_DSMIF1;
    }

    p_instance_ctrl->p_reg = (R_DSMIF0_Type *) base_address;

    /* Figure 39.2 Start flow of DSMIF */
    /* Release from the module-stop state */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_START(FSP_IP_DSMIF, p_cfg->unit);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    /* Set Overcurrent Sum Error Detection */
    /* DSSELTR : Overcurrent Sum Error Detect Low Threshold Register */
    p_instance_ctrl->p_reg->DSSELTR = (p_cfg_extend->scmptbl & R_DSMIF0_DSSELTR_SCMPTBL_Msk);

    /* DSSEHTR : Overcurrent Sum Error Detect High Threshold Register */
    p_instance_ctrl->p_reg->DSSEHTR = (p_cfg_extend->scmptbh & R_DSMIF0_DSSEHTR_SCMPTBH_Msk);

    /* DSSECSR : Overcurrent Sum Error Detect Channel Setting Register */
    p_instance_ctrl->p_reg->DSSECSR = (p_cfg_extend->sedm << R_DSMIF0_DSSECSR_SEDM_Pos);

    /* DSSEICR : Overcurrent Sum Error Detect Interrupt Control Register */
    p_instance_ctrl->p_reg->DSSEICR =
        (((uint32_t) p_cfg_extend->isel << R_DSMIF0_DSSEICR_ISEL_Pos) |
         ((uint32_t) p_cfg_extend->iseh << R_DSMIF0_DSSEICR_ISEH_Pos));

    /* Register settings for each channel */
    for (uint32_t ch = 0U; ch < DSMIF_MAX_NUM_CHANNELS; ch++)
    {
        p_instance_ctrl->results.results_32[ch] = 0U;

        if (p_cfg_extend->p_channel_cfgs[ch] != NULL)
        {
            /* DSICRCHn : Interrupt Control Register Channel */
            p_instance_ctrl->p_reg->CH[ch].DSICR =
                ((((uint32_t) p_cfg_extend->p_channel_cfgs[ch]->ioel << R_DSMIF0_CH_DSICR_IOEL_Pos) &
                  R_DSMIF0_CH_DSICR_IOEL_Msk) |
                 (((uint32_t) p_cfg_extend->p_channel_cfgs[ch]->ioeh <<
                    R_DSMIF0_CH_DSICR_IOEH_Pos) & R_DSMIF0_CH_DSICR_IOEH_Msk) |
                 (((uint32_t) p_cfg_extend->p_channel_cfgs[ch]->ise <<
                    R_DSMIF0_CH_DSICR_ISE_Pos) & R_DSMIF0_CH_DSICR_ISE_Msk) |
                 (((uint32_t) p_cfg_extend->p_channel_cfgs[ch]->iue <<
                    R_DSMIF0_CH_DSICR_IUE_Pos) & R_DSMIF0_CH_DSICR_IUE_Msk));

            /* Set Channel's Error Detection Control */
            p_instance_ctrl->p_reg->CH[ch].DSOCLTR =
                (p_cfg_extend->p_channel_cfgs[ch]->ocmptbl << R_DSMIF0_CH_DSOCLTR_OCMPTBL_Pos) &
                R_DSMIF0_CH_DSOCLTR_OCMPTBL_Msk;
            p_instance_ctrl->p_reg->CH[ch].DSOCHTR =
                (p_cfg_extend->p_channel_cfgs[ch]->ocmptbh << R_DSMIF0_CH_DSOCHTR_OCMPTBH_Pos) &
                R_DSMIF0_CH_DSOCHTR_OCMPTBH_Msk;
            p_instance_ctrl->p_reg->CH[ch].DSSCTSR =
                (((p_cfg_extend->p_channel_cfgs[ch]->scntl << R_DSMIF0_CH_DSSCTSR_SCNTL_Pos) &
                  R_DSMIF0_CH_DSSCTSR_SCNTL_Msk) |
                 ((p_cfg_extend->p_channel_cfgs[ch]->scnth <<
                    R_DSMIF0_CH_DSSCTSR_SCNTH_Pos) & R_DSMIF0_CH_DSSCTSR_SCNTH_Msk));
            p_instance_ctrl->p_reg->CH[ch].DSEDCR =
                ((uint32_t) p_cfg_extend->p_channel_cfgs[ch]->sde << R_DSMIF0_CH_DSEDCR_SDE_Pos) &
                R_DSMIF0_CH_DSEDCR_SDE_Msk;

            /* Set Channel's Current Measurement Control */
            uint32_t dscmctcrch;
            dscmctcrch =
                (((uint32_t) p_cfg_extend->cap_trig_a << R_DSMIF0_CH_DSCMCTCR_CTSELA_Pos) |
                 ((uint32_t) p_cfg_extend->cap_trig_b << R_DSMIF0_CH_DSCMCTCR_CTSELB_Pos) | \
                 ((uint32_t) p_cfg_extend->cnt_init_trig << R_DSMIF0_CH_DSCMCTCR_DITSEL_Pos) |
                 ((uint32_t) p_cfg_extend->edge << R_DSMIF0_CH_DSCMCTCR_DEDGE_Pos));
            p_instance_ctrl->p_reg->CH[ch].DSCMCTCR = dscmctcrch;

            /* Set Current Measurement Clock Control Register */
            /* For Slave, set DSCMCCRCHn.CKDIV to 0 (default) */
            uint32_t ckdiv;
            if (DSMIF_CLOCK_CTRL_SLAVE == p_cfg_extend->p_channel_cfgs[ch]->ckdir)
            {
                ckdiv = 0U;
            }
            else
            {
                ckdiv = p_cfg_extend->p_channel_cfgs[ch]->ckdiv;
            }

            p_instance_ctrl->p_reg->CH[ch].DSCMCCR =
                ((((uint32_t) p_cfg_extend->p_channel_cfgs[ch]->ckdir << R_DSMIF0_CH_DSCMCCR_CKDIR_Pos) &
                  R_DSMIF0_CH_DSCMCCR_CKDIR_Msk) |
                 (((uint32_t) p_cfg_extend->p_channel_cfgs[ch]->sedge <<
                    R_DSMIF0_CH_DSCMCCR_SEDGE_Pos) & R_DSMIF0_CH_DSCMCCR_SEDGE_Msk) |
                 ((ckdiv << R_DSMIF0_CH_DSCMCCR_CKDIV_Pos) & R_DSMIF0_CH_DSCMCCR_CKDIV_Msk));

            /* Set Current Measurement Filter Control Register */
            p_instance_ctrl->p_reg->CH[ch].DSCMFCR =
                (((uint32_t) p_cfg_extend->p_channel_cfgs[ch]->cmsinc << R_DSMIF0_CH_DSCMFCR_CMSINC_Pos) |
                 (p_cfg_extend->p_channel_cfgs[ch]->cmdec <<
                    R_DSMIF0_CH_DSCMFCR_CMDEC_Pos) |
                 ((uint32_t) p_cfg_extend->p_channel_cfgs[ch]->cmsh <<
                    R_DSMIF0_CH_DSCMFCR_CMSH_Pos));

            /* Set Overcurrent Detect Filter Control Register */
            p_instance_ctrl->p_reg->CH[ch].DSOCFCR =
                (((uint32_t) p_cfg_extend->p_channel_cfgs[ch]->ocsinc << R_DSMIF0_CH_DSOCFCR_OCSINC_Pos) |
                 (p_cfg_extend->p_channel_cfgs[ch]->ocdec <<
                    R_DSMIF0_CH_DSOCFCR_OCDEC_Pos) |
                 ((uint32_t) p_cfg_extend->p_channel_cfgs[ch]->ocsh <<
                    R_DSMIF0_CH_DSOCFCR_OCSH_Pos));
        }
    }

    /* Mark driver as open by initializing it to "DSMI" - its ASCII equivalent. */
    p_instance_ctrl->opened = DSMIF_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * Starts either synchronous control mode or individual control mode .
 *
 * @note After executing R_DSMIF_ScanStart, it is necessary to wait until the filter result is output stably.
 *       (Reference section 39.3.15.1 "Settling Time of Channel Activation")
 *
 * @retval  FSP_SUCCESS                Scan started or hardware triggers enabled successfully.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_ScanStart (adc_ctrl_t * p_ctrl)
{
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) p_ctrl;
    fsp_err_t               err             = FSP_SUCCESS;

#if (1 == DSMIF_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the DSMIF unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(DSMIF_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    r_dsmif_start(p_instance_ctrl);

    /* Return the error code */
    return err;
}

/*******************************************************************************************************************//**
 * Stops any in-progress scan started by software.
 *
 * @retval  FSP_SUCCESS                Scan stopped or hardware triggers disabled successfully.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 * @retval  FSP_ERR_TIMEOUT            Timeout error.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_ScanStop (adc_ctrl_t * p_ctrl)
{
    fsp_err_t               err;
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) p_ctrl;

#if (1 == DSMIF_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the DSMIF unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(DSMIF_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    err = r_dsmif_stop(p_instance_ctrl);

    /* Return the error code */
    return err;
}

/*******************************************************************************************************************//**
 * Configuration settings.(Overcurrent detection and Sum error detection).
 *
 * @retval  FSP_SUCCESS                Configuration setting successfully.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_CfgSet (adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg)
{
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) p_ctrl;

#if (1 == DSMIF_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the DSMIF unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(DSMIF_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    dsmif_extended_cfg_t const * p_cfg_extend = (dsmif_extended_cfg_t *) p_cfg->p_extend;

    /* Set overcurrent detection */
    for (uint32_t ch = 0U; ch < DSMIF_MAX_NUM_CHANNELS; ch++)
    {
        /* Set overcurrent detection valid */
        p_instance_ctrl->p_reg->CH[ch].DSODCR_b.ODEL = p_cfg_extend->p_channel_cfgs[ch]->odel;
        p_instance_ctrl->p_reg->CH[ch].DSODCR_b.ODEH = p_cfg_extend->p_channel_cfgs[ch]->odeh;
    }

    /* Set sum error detection */
    /* DSSECR : Overcurrent Sum Error Detect Control Register */
    p_instance_ctrl->p_reg->DSSECR = (uint32_t) ((p_cfg_extend->seel << R_DSMIF0_DSSECR_SEEL_Pos) |
                                                 (p_cfg_extend->seeh << R_DSMIF0_DSSECR_SEEH_Pos));

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Returns the status of a scan started by software.
 *
 * @retval  FSP_SUCCESS                No software scan is in progress.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_StatusGet (adc_ctrl_t * p_ctrl, adc_status_t * p_status)
{
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) p_ctrl;

#if (1 == DSMIF_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the DSMIF unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(DSMIF_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    if (ADC_MODE_SYNCHRONIZE_SCAN == p_instance_ctrl->mode)
    {
        /* Channel synchronization control mode */

        if (0U == (p_instance_ctrl->p_reg->DSCSSR & (R_DSMIF0_DSCSSR_CHSTATE0_Msk | \
                                                     R_DSMIF0_DSCSSR_CHSTATE1_Msk | R_DSMIF0_DSCSSR_CHSTATE2_Msk)))
        {
            p_status->state = ADC_STATE_IDLE;
        }
        else
        {
            p_status->state = ADC_STATE_SCAN_IN_PROGRESS;
        }
    }
    else
    {
        /* Channel individual control mode */
        if ((0U == (p_instance_ctrl->p_reg->CH[0].DSCSR & R_DSMIF0_CH_DSCSR_CHSTATE_Msk)) &&
            (0U == (p_instance_ctrl->p_reg->CH[1].DSCSR & R_DSMIF0_CH_DSCSR_CHSTATE_Msk)) &&
            (0U == (p_instance_ctrl->p_reg->CH[2].DSCSR & R_DSMIF0_CH_DSCSR_CHSTATE_Msk)))
        {
            p_status->state = ADC_STATE_IDLE;
        }
        else
        {
            p_status->state = ADC_STATE_SCAN_IN_PROGRESS;
        }
    }

    p_status->error_status = p_instance_ctrl->p_reg->DSCESR;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads the most recent result from a channel.
 *
 * @retval  FSP_SUCCESS                Result in p_data.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL or an input parameter was invalid.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_Read (adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint32_t * const p_data)
{
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) p_ctrl;

#if (1 == DSMIF_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the DSMIF unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(DSMIF_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(0U != ((1U << ((uint32_t) reg_id & DSMIF_REGID_MASK)) & p_instance_ctrl->channel_mask));
#endif

    adc_channel_t        channel         = (adc_channel_t) (reg_id & DSMIF_DATA_CHANNEL_MASK);
    dsmif_current_data_t dsmif_data_type =
        (dsmif_current_data_t) ((reg_id & DSMIF_DATA_TYPE_MASK) >> DSMIF_DATA_TYPE_SHIFT);
    if (DSMIF_CURRENT_DATA == dsmif_data_type)
    {
        p_instance_ctrl->results.results_32[channel] = p_instance_ctrl->p_reg->CH[channel].DSCDR;
    }
    else if (DSMIF_CURRENT_DATA_CAPTURE_A == dsmif_data_type)
    {
        p_instance_ctrl->results.results_32[channel] = p_instance_ctrl->p_reg->CH[channel].DSCCDRA;
    }
    else
    {
        p_instance_ctrl->results.results_32[channel] = p_instance_ctrl->p_reg->CH[channel].DSCCDRB;
    }

    *p_data = p_instance_ctrl->results.results_32[channel];

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops any scan in progress, disables interrupts, and powers down the DSMIF peripheral.
 *
 * @note This function is delayed at least until the outage is complete, as required by the DSMIF outage procedure.
 *
 * @retval  FSP_SUCCESS                Instance control block closed successfully.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_Close (adc_ctrl_t * p_ctrl)
{
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) p_ctrl;

    /* Perform parameter checking*/
#if (1 == DSMIF_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the DSMIF unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(DSMIF_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Mark driver as closed   */
    p_instance_ctrl->opened = 0U;

    /* Disable interrupts. */
    r_dsmif_disable_irq(p_instance_ctrl->p_cfg->scan_end_irq);

    for (uint32_t ch = 0U; ch < DSMIF_MAX_NUM_CHANNELS; ch++)
    {
        p_instance_ctrl->results.results_32[ch] = 0U;
        p_instance_ctrl->p_reg->CH[ch].DSICR    = 0x00000000U;
    }

    /* Stop processing(No error is returned because it is forcibly terminated.) */
    (void) r_dsmif_stop(p_instance_ctrl);

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_STOP(FSP_IP_DSMIF, p_instance_ctrl->p_cfg->unit);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets driver version based on compile time macros.
 *
 * @retval FSP_SUCCESS                 Version stored in p_version.
 * @retval FSP_ERR_ASSERTION           p_version was NULL.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_VersionGet (fsp_version_t * const p_version)
{
#if DSMIF_CFG_PARAM_CHECKING_ENABLE

    /* Verify parameters are valid */
    FSP_ASSERT(NULL != p_version);
#endif

    p_version->version_id = g_dsmif_version.version_id;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup DSMIF)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/
#if (1 == DSMIF_CFG_PARAM_CHECKING_ENABLE)

/*******************************************************************************************************************//**
 * Validates the input parameters to open().
 *
 * @param[in]  p_instance_ctrl  Pointer to instance control block
 * @param[in]  p_cfg   Pointer to configuration structure
 *
 * @retval  FSP_SUCCESS                 No invalid configurations identified.
 * @retval  FSP_ERR_ALREADY_OPEN        Control block is already open.
 * @retval  FSP_ERR_ASSERTION           An input pointer is NULL or an input parameter is invalid.
 * @retval  FSP_ERR_IRQ_BSP_DISABLED    A callback is provided, but the interrupt is not enabled.
 * @retval  FSP_ERR_IP_UNIT_NOT_PRESENT The Unit requested in the p_cfg parameter is not available on this device.
 **********************************************************************************************************************/
static fsp_err_t r_dsmif_open_param_check (dsmif_instance_ctrl_t * const p_instance_ctrl, adc_cfg_t const * const p_cfg)
{
    /* Verify the pointers are not NULL. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);

    /* Verify the control block has not already been initialized. */
    FSP_ERROR_RETURN(DSMIF_OPEN != p_instance_ctrl->opened, FSP_ERR_ALREADY_OPEN);

    /* Verify the unit exists on the MCU. */
    FSP_ERROR_RETURN(((1U << p_cfg->unit) & DSMIF_VALID_UNIT_MASK), FSP_ERR_IP_UNIT_NOT_PRESENT);

    /* If a callback is used, then make sure the scan end interrupt is enabled */
    if (NULL != p_cfg->p_callback)
    {
        FSP_ERROR_RETURN(p_cfg->scan_end_irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
    }

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Start processing of channel synchronization control mode and individual control mode
 *
 * @param[in]  p_instance_ctrl     Pointer to instance control block
 *
 **********************************************************************************************************************/
static void r_dsmif_start (dsmif_instance_ctrl_t * const p_instance_ctrl)
{
    /* DSCSTRTR : Channel Software Start Trigger Register (Channel synchronization control mode)*/
    /* Write 1 to Channel's start trigger */
    if (ADC_MODE_SYNCHRONIZE_SCAN == p_instance_ctrl->mode)
    {
        p_instance_ctrl->p_reg->DSCSTRTR = p_instance_ctrl->channel_mask;
    }
    else
    {
        uint32_t ch_mask = p_instance_ctrl->channel_mask;
        for (uint32_t ch = 0U; ch < DSMIF_MAX_NUM_CHANNELS; ch++)
        {
            /* Start if channel mask bit is set */
            if (1U == (ch_mask & 0x1U))
            {
                /* DSCSTRTRCHn : Channel Software Start Trigger Register (Channel individual control mode)*/
                /* Write 1 to Channel's start trigger */
                p_instance_ctrl->p_reg->CH[ch].DSCSTRTR_b.STRTRG = R_DSMIF0_CH_DSCSTRTR_STRTRG_Msk;
            }

            ch_mask >>= 1U;
        }
    }
}

/*******************************************************************************************************************//**
 * Stop processing of channel synchronization control mode and individual control mode
 *
 * @param[in]  p_instance_ctrl     Pointer to instance control block
 *
 * @retval  FSP_SUCCESS            Stop processing succeeded.
 * @retval  FSP_ERR_TIMEOUT        Timeout error.
 **********************************************************************************************************************/
static fsp_err_t r_dsmif_stop (dsmif_instance_ctrl_t * const p_instance_ctrl)
{
    fsp_err_t err     = FSP_SUCCESS;
    uint32_t  timeout = DSMIF_STOP_TIMEOUT;

    if (ADC_MODE_SYNCHRONIZE_SCAN == p_instance_ctrl->mode)
    {
        /* DSCSTPTR : Channel Software Stop Trigger Register (Channel synchronization control mode) */
        /* Write 1 to Channel's stop trigger */
        p_instance_ctrl->p_reg->DSCSTPTR = p_instance_ctrl->channel_mask;

        /* Check that all channels are down */
        while (0 != (p_instance_ctrl->p_reg->DSCSSR & (R_DSMIF0_DSCSSR_CHSTATE0_Msk | \
                                                       R_DSMIF0_DSCSSR_CHSTATE1_Msk | R_DSMIF0_DSCSSR_CHSTATE2_Msk)))
        {
            /* Exit processing when time out. */
            if (0U == timeout)
            {
                err = FSP_ERR_TIMEOUT;
                break;
            }

            timeout--;
        }

        /* Disable overcurrent detection of all target channels */
        for (uint32_t ch = 0U; ch < DSMIF_MAX_NUM_CHANNELS; ch++)
        {
            p_instance_ctrl->p_reg->CH[ch].DSODCR = 0x00000000U;
        }

        /* Disable sum error detection  */
        /* DSSECR : Overcurrent Sum Error Detect Control Register */
        p_instance_ctrl->p_reg->DSSECR = 0x00000000U;
    }
    else
    {
        /* DSCSTPTRCH : Channel Software Stop Trigger Register (Channel individual control mode)*/
        /* Write 1 to Channel's stop trigger */
        for (uint32_t ch = 0U; ch < DSMIF_MAX_NUM_CHANNELS; ch++)
        {
            p_instance_ctrl->p_reg->CH[ch].DSCSTPTR = R_DSMIF0_CH_DSCSTPTR_STPTRG_Msk;
        }

        /* Check that all channels are down */
        while ((0 != (p_instance_ctrl->p_reg->CH[0].DSCSR & R_DSMIF0_CH_DSCSR_CHSTATE_Msk)) &&
               (0 != (p_instance_ctrl->p_reg->CH[1].DSCSR & R_DSMIF0_CH_DSCSR_CHSTATE_Msk)) &&
               (0 != (p_instance_ctrl->p_reg->CH[2].DSCSR & R_DSMIF0_CH_DSCSR_CHSTATE_Msk)))
        {
            /* Exit processing when time out. */
            if (0U == timeout)
            {
                err = FSP_ERR_TIMEOUT;
                break;
            }

            timeout--;
        }

        /* Disable overcurrent detection of all target channels */
        for (uint32_t ch = 0U; ch < DSMIF_MAX_NUM_CHANNELS; ch++)
        {
            p_instance_ctrl->p_reg->CH[ch].DSODCR = 0x00000000U;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Configures interrupts and ensures required interrupts are enabled.
 *
 * @param[in]  p_instance_ctrl     Pointer to instance control block
 * @param[in]  p_cfg      Pointer to configuration structure
 *
 **********************************************************************************************************************/
static void r_dsmif_open_irq_cfg (dsmif_instance_ctrl_t * const p_instance_ctrl, adc_cfg_t const * const p_cfg)
{
    /* Set the interrupt priorities. */
    if (p_cfg->scan_end_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg->scan_end_irq, p_cfg->scan_end_ipl, p_instance_ctrl);
    }
}

/*******************************************************************************************************************//**
 * Disables an interrupt.
 *
 * @param[in]  irq     Interrupt to disable
 **********************************************************************************************************************/
static void r_dsmif_disable_irq (IRQn_Type irq)
{
    if (irq >= 0)
    {
        R_BSP_IrqDisable(irq);
        R_FSP_IsrContextSet(irq, NULL);
    }
}

/*******************************************************************************************************************//**
 * DSMIFx current data register update interrupt.
 **********************************************************************************************************************/
void dsmif_cdrui_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type               irq             = R_FSP_CurrentIrqGet();
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* If a callback was provided, call it with the argument */
    if (NULL != p_instance_ctrl->p_cfg->p_callback)
    {
        /* Store the event into the callback argument */
        adc_callback_args_t args;
        if (VECNUM_DSMIF0_CDRUI == irq)
        {
            args.unit = 0U;
        }
        else
        {
            args.unit = 1U;
        }

        args.event     = ADC_EVENT_SCAN_COMPLETE;
        args.p_context = p_instance_ctrl->p_cfg->p_context;
        p_instance_ctrl->p_cfg->p_callback(&args);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}
