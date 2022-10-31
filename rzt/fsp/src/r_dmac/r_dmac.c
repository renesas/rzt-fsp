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
 * Includes
 **********************************************************************************************************************/
#include "r_dmac.h"
#include "r_dmac_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** Driver ID (DMAC in ASCII) */
#define DMAC_ID                        (0x444d4143)

/** Byte limited to 2^32-1 byte */
#define DMAC_BLOCK_MAX_LENGTH          (0xFFFFFFFF)
#define DMAC_BLOCK_COUNT_MAX_LENGTH    (0xFFFFFFFF)

#define DMAC_PRV_MASK_ALIGN_2_BYTES    (0x1U)
#define DMAC_PRV_MASK_ALIGN_4_BYTES    (0x3U)

/* Calculate the mask bits for byte alignment from the transfer_size_t. */
#define DMAC_PRV_MASK_ALIGN_N_BYTES(x)    ((1U << (x)) - 1U)

#define DMAC_PRV_REG(unit)                ((R_DMAC0_Type *) (((uint32_t) R_DMAC1 - (uint32_t) R_DMAC0) * unit + \
                                                             (uint32_t) R_DMAC0))

#define DMAC_PRV_CHANNEL(channel)         (channel % 8)
#define DMAC_PRV_GROUP(channel)           (channel / 8)

#define DMAC_PRV_ATCM_END_ADDRESS                (0x0007FFFF)
#define DMAC_PRV_BTCM_START_ADDRESS              (0x00100000)
#define DMAC_PRV_BTCM_END_ADDRESS                (0x0010FFFF)
#define DMAC_PRV_CPUTCM_BASE_ADDRESS             (0x20000000)

#define DMAC_PRV_DCTRL_DEFAULT_VALUE             (0x00000000U)
#define DMAC_PRV_CHCFG_DEFAULT_VALUE             (0x00000000U)

/* Channel Extension Register Bit Field Definitions */
#define DMAC_PRV_CHEXT_SCA_OFFSET                (4U)
#define DMAC_PRV_CHEXT_DCA_OFFSET                (12U)

/* Channel Control Register Bit Field Definitions */
#define DMAC_PRV_CHCTRL_SETEN_OFFSET             (0U)
#define DMAC_PRV_CHCTRL_SETEN_MASK               (1U << DMAC_PRV_CHCTRL_SETEN_OFFSET)
#define DMAC_PRV_CHCTRL_CLREN_OFFSET             (1U)
#define DMAC_PRV_CHCTRL_CLREN_MASK               (1U << DMAC_PRV_CHCTRL_CLREN_OFFSET)
#define DMAC_PRV_CHCTRL_STG_OFFSET               (2U)
#define DMAC_PRV_CHCTRL_STG_MASK                 (1U << DMAC_PRV_CHCTRL_STG_OFFSET)
#define DMAC_PRV_CHCTRL_SWRST_OFFSET             (3U)
#define DMAC_PRV_CHCTRL_SWRST_MASK               (1U << DMAC_PRV_CHCTRL_SWRST_OFFSET)
#define DMAC_PRV_CHCTRL_CLREND_OFFSET            (5U)
#define DMAC_PRV_CHCTRL_CLREND_MASK              (1U << DMAC_PRV_CHCTRL_CLREND_OFFSET)
#define DMAC_PRV_CHCTRL_SETSUS_OFFSET            (8U)
#define DMAC_PRV_CHCTRL_SETSUS_MASK              (1U << DMAC_PRV_CHCTRL_SETSUS_OFFSET)

/* Channel Configuration Register Bit Field Definitions */
#define DMAC_PRV_CHCFG_SEL_OFFSET                (0U)
#define DMAC_PRV_CHCFG_SEL_VALUE_MASK            (0x07U)
#define DMAC_PRV_CHCFG_REQD_OFFSET               (3U)
#define DMAC_PRV_CHCFG_REQD_VALUE_MASK           (0x01U)
#define DMAC_PRV_CHCFG_LOEN_OFFSET               (4U)
#define DMAC_PRV_CHCFG_DETECT_MODE_VALUE_MASK    (0x07U)
#define DMAC_PRV_CHCFG_AM_OFFSET                 (8U)
#define DMAC_PRV_CHCFG_AM_VALUE_MASK             (0x07U)
#define DMAC_PRV_CHCFG_SDS_OFFSET                (12U)
#define DMAC_PRV_CHCFG_SDS_VALUE_MASK            (0x0FU)
#define DMAC_PRV_CHCFG_DDS_OFFSET                (16U)
#define DMAC_PRV_CHCFG_DDS_VALUE_MASK            (0x0FU)
#define DMAC_PRV_CHCFG_SAD_OFFSET                (20U)
#define DMAC_PRV_CHCFG_SAD_VALUE_MASK            (0x01U)
#define DMAC_PRV_CHCFG_DAD_OFFSET                (21U)
#define DMAC_PRV_CHCFG_DAD_VALUE_MASK            (0x01U)
#define DMAC_PRV_CHCFG_TM_OFFSET                 (22U)
#define DMAC_PRV_CHCFG_TM_VALUE_MASK             (0x01U)
#define DMAC_PRV_CHCFG_DEM_OFFSET                (24U)
#define DMAC_PRV_CHCFG_DEM_MASK                  (1U << DMAC_PRV_CHCFG_DEM_OFFSET)
#define DMAC_PRV_CHCFG_DEM_VALUE_MASK            (0x01U)
#define DMAC_PRV_CHCFG_RSW_OFFSET                (29U)
#define DMAC_PRV_CHCFG_RSW_MASK                  (1U << DMAC_PRV_CHCFG_RSW_OFFSET)
#define DMAC_PRV_NEXT_REG_VALUE_MASK             (0x03U)

/* DMA Control Register Bit Field Definitions */
#define DMAC_PRV_DCTRL_PR_OFFSET                 (0U)
#define DMAC_PRV_DCTRL_PR_VALUE_MASK             (0x01U)

/* DMAC Resource Select Register Bit Field Definitions */
#define DMAC_PRV_RSSEL_REQ_SEL_OFFSET            (10U)
#define DMAC_PRV_RSSEL_REQ_SEL_MASK              (0x3FFU)

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
void dmac_int_isr(void);

static fsp_err_t r_dmac_prv_enable(dmac_instance_ctrl_t * p_ctrl);
static void      r_dmac_prv_disable(dmac_instance_ctrl_t * p_ctrl);
static void      r_dmac_config_transfer_info(dmac_instance_ctrl_t * p_ctrl, transfer_info_t * p_info);
static uint32_t  r_dmac_config_chext(uint32_t src_address, uint32_t dest_address);
static bool      r_dmac_address_tcm_check(uint32_t address);

#if DMAC_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_dma_open_parameter_checking(dmac_instance_ctrl_t * const p_ctrl, transfer_cfg_t const * const p_cfg);
static fsp_err_t r_dmac_info_paramter_checking(transfer_info_t const * const p_info);
static fsp_err_t r_dmac_enable_parameter_checking(dmac_instance_ctrl_t * const p_ctrl);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** Version data structure used by error logger macro. */
static const fsp_version_t g_dmac_version =
{
    .api_version_minor  = TRANSFER_API_VERSION_MINOR,
    .api_version_major  = TRANSFER_API_VERSION_MAJOR,
    .code_version_major = DMAC_CODE_VERSION_MAJOR,
    .code_version_minor = DMAC_CODE_VERSION_MINOR
};

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** DMAC implementation of transfer API. */
const transfer_api_t g_transfer_on_dmac =
{
    .open          = R_DMAC_Open,
    .reconfigure   = R_DMAC_Reconfigure,
    .reset         = R_DMAC_Reset,
    .infoGet       = R_DMAC_InfoGet,
    .softwareStart = R_DMAC_SoftwareStart,
    .softwareStop  = R_DMAC_SoftwareStop,
    .enable        = R_DMAC_Enable,
    .disable       = R_DMAC_Disable,
    .close         = R_DMAC_Close,
    .versionGet    = R_DMAC_VersionGet,
};

/*******************************************************************************************************************//**
 * @addtogroup DMAC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configure a DMAC channel.
 *
 * @retval FSP_SUCCESS                    Successful open.
 * @retval FSP_ERR_ASSERTION              An input parameter is invalid.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The configured channel is invalid.
 * @retval FSP_ERR_IRQ_BSP_DISABLED       The IRQ associated with the activation source is not enabled in the BSP.
 * @retval FSP_ERR_ALREADY_OPEN           The control structure is already opened.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_Open (transfer_ctrl_t * const p_api_ctrl, transfer_cfg_t const * const p_cfg)
{
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = FSP_SUCCESS;
    err = r_dma_open_parameter_checking(p_api_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    dmac_instance_ctrl_t * p_ctrl   = (dmac_instance_ctrl_t *) p_api_ctrl;
    dmac_extended_cfg_t  * p_extend = (dmac_extended_cfg_t *) p_cfg->p_extend;

    p_ctrl->p_cfg = p_cfg;
    p_ctrl->p_reg = DMAC_PRV_REG(p_extend->unit);

    /* Configure the transfer settings. */
    r_dmac_config_transfer_info(p_ctrl, p_cfg->p_info);

    /* Mark driver as open by initializing "DMAC" in its ASCII equivalent.*/
    p_ctrl->open = DMAC_ID;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reconfigure the transfer with new transfer info.
 *
 * @retval FSP_SUCCESS              Transfer is configured and will start when trigger occurs.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_NOT_ENABLED      DMAC is not enabled. The current configuration must not be valid.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_Reconfigure (transfer_ctrl_t * const p_api_ctrl, transfer_info_t * p_info)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if DMAC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ERROR_RETURN(p_ctrl->open == DMAC_ID, FSP_ERR_NOT_OPEN);
    err = r_dmac_info_paramter_checking(p_info);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ASSERT(p_info->p_extend != NULL);
    dmac_extended_info_t * p_extend_info = (dmac_extended_info_t *) p_info->p_extend;
    dmac_extended_cfg_t  * p_extend      = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    if (DMAC_REGISTER_SELECT_REVERSE_DISABLE != p_extend->next_register_operaion)
    {
        FSP_ASSERT(NULL != p_extend_info->p_next1_register_setting);
    }
#endif

    /* Reconfigure the transfer settings. */
    r_dmac_config_transfer_info(p_ctrl, p_info);

    err = r_dmac_prv_enable(p_api_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_NOT_ENABLED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reset transfer source, destination, and number of transfers.
 *
 * @retval FSP_ERR_UNSUPPORTED              API not supported.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_Reset (transfer_ctrl_t * const p_api_ctrl,
                        void const * volatile   p_src,
                        void * volatile         p_dest,
                        uint16_t const          num_transfers)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_src);
    FSP_PARAMETER_NOT_USED(p_dest);
    FSP_PARAMETER_NOT_USED(num_transfers);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Set a transfer request by software.
 *
 * @retval FSP_SUCCESS              Transfer started written successfully.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_SoftwareStart (transfer_ctrl_t * const p_api_ctrl, transfer_start_mode_t mode)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;

#if DMAC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_ctrl->p_cfg);
    FSP_ASSERT(NULL != p_ctrl->p_cfg->p_extend);
    FSP_ERROR_RETURN(p_ctrl->open == DMAC_ID, FSP_ERR_NOT_OPEN);
#endif

    FSP_PARAMETER_NOT_USED(mode);

    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    uint8_t group   = DMAC_PRV_GROUP(p_extend->channel);
    uint8_t channel = DMAC_PRV_CHANNEL(p_extend->channel);

    /* Set auto clear bit and software start bit. */
    p_ctrl->p_reg->GRP[group].CH[channel].CHCTRL = DMAC_PRV_CHCTRL_STG_MASK;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stop software transfers if they were started with TRANSFER_START_MODE_REPEAT.
 *
 * @retval FSP_ERR_UNSUPPORTED              API not supported.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_SoftwareStop (transfer_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Enable transfers for the configured activation source.
 *
 * @retval FSP_SUCCESS              Counter value written successfully.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_Enable (transfer_ctrl_t * const p_api_ctrl)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == DMAC_ID, FSP_ERR_NOT_OPEN);
#endif

    return r_dmac_prv_enable(p_ctrl);
}

/*******************************************************************************************************************//**
 * Disable transfers so that they are no longer triggered by the activation source.
 *
 * @retval FSP_SUCCESS              Counter value written successfully.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_Disable (transfer_ctrl_t * const p_api_ctrl)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == DMAC_ID, FSP_ERR_NOT_OPEN);
#endif

    r_dmac_prv_disable(p_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set driver specific information in provided pointer.
 *
 * @retval FSP_SUCCESS              Information has been written to p_info.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_InfoGet (transfer_ctrl_t * const p_api_ctrl, transfer_properties_t * const p_info)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;

#if DMAC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == DMAC_ID, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_info);
#endif

    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    p_info->transfer_length_max = DMAC_MAX_NORMAL_TRANSFER_LENGTH;
    p_info->block_count_max     = DMAC_BLOCK_COUNT_MAX_LENGTH;

    uint8_t group   = DMAC_PRV_GROUP(p_extend->channel);
    uint8_t channel = DMAC_PRV_CHANNEL(p_extend->channel);

    p_info->block_count_remaining     = DMAC_MAX_BLOCK_TRANSFER_LENGTH;
    p_info->transfer_length_remaining = (p_ctrl->p_reg->GRP[group].CH[channel].CRTB);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disable transfer and clean up internal data. Implements @ref transfer_api_t::close.
 *
 * @retval FSP_SUCCESS           Successful close.
 * @retval FSP_ERR_ASSERTION     An input parameter is invalid.
 * @retval FSP_ERR_NOT_OPEN      Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_Close (transfer_ctrl_t * const p_api_ctrl)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == DMAC_ID, FSP_ERR_NOT_OPEN);
#endif

    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    uint8_t group   = DMAC_PRV_GROUP(p_extend->channel);
    uint8_t channel = DMAC_PRV_CHANNEL(p_extend->channel);

    /* Disable DMAC transfers on this channel. */
    uint32_t rssel_register_num = p_extend->channel / 3;
    uint32_t rssel_bit_bum      = p_extend->channel % 3;
    if (0 == p_extend->unit)
    {
        R_DMA->DMAC0_RSSEL[rssel_register_num] |=
            (uint32_t) (DMAC_PRV_RSSEL_REQ_SEL_MASK << (DMAC_PRV_RSSEL_REQ_SEL_OFFSET * rssel_bit_bum));
    }
    else
    {
        R_DMA->DMAC1_RSSEL[rssel_register_num] |=
            (uint32_t) (DMAC_PRV_RSSEL_REQ_SEL_MASK << (DMAC_PRV_RSSEL_REQ_SEL_OFFSET * rssel_bit_bum));
    }

    /* Disable DMA transfer */
    p_ctrl->p_reg->GRP[group].CH[channel].CHCTRL = DMAC_PRV_CHCTRL_CLREN_MASK;

    /* Wait DMA stop */
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->GRP[group].CH[channel].CHSTAT_b.TACT, 0);

    /* DMA Software Reset. */
    p_ctrl->p_reg->GRP[group].CH[channel].CHCTRL = DMAC_PRV_CHCTRL_SWRST_MASK;

    if ((NULL != p_extend->p_callback) || (NULL != p_extend->p_peripheral_module_handler))
    {
        R_BSP_IrqDisable(p_extend->dmac_int_irq);
        R_FSP_IsrContextSet(p_extend->dmac_int_irq, NULL);
    }

    /* Clear ID so control block can be reused. */
    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set driver version based on compile time macros.
 *
 * @retval FSP_SUCCESS              Successful close.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_VersionGet (fsp_version_t * const p_version)
{
#if DMAC_CFG_PARAM_CHECKING_ENABLE

    /* Verify parameters are valid */
    FSP_ASSERT(NULL != p_version);
#endif

    p_version->version_id = g_dmac_version.version_id;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup DMAC)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Enable transfers for the channel.
 *
 * @param[in]  p_ctrl             Pointer to control structure.
 *
 * @retval     FSP_SUCCESS          Successful close.
 * @retval     FSP_ERR_ASSERTION    An input parameter is invalid.
 **********************************************************************************************************************/
static fsp_err_t r_dmac_prv_enable (dmac_instance_ctrl_t * p_ctrl)
{
    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_dmac_enable_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    uint8_t group   = DMAC_PRV_GROUP(p_extend->channel);
    uint8_t channel = DMAC_PRV_CHANNEL(p_extend->channel);

    /* DMA Software Reset. */
    p_ctrl->p_reg->GRP[group].CH[channel].CHCTRL = DMAC_PRV_CHCTRL_SWRST_MASK;

    /* Does not mask DMA transfer end interrupt */
    p_ctrl->p_reg->GRP[group].CH[channel].CHCFG &= (~((uint32_t) DMAC_PRV_CHCFG_DEM_MASK));

    /* Enable transfer. */
    p_ctrl->p_reg->GRP[group].CH[channel].CHCTRL = DMAC_PRV_CHCTRL_SETEN_MASK;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disable transfers for the channel.
 *
 * @param      p_ctrl          Pointer to the control structure
 **********************************************************************************************************************/
static void r_dmac_prv_disable (dmac_instance_ctrl_t * p_ctrl)
{
    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    uint8_t group   = DMAC_PRV_GROUP(p_extend->channel);
    uint8_t channel = DMAC_PRV_CHANNEL(p_extend->channel);

    /* Disable DMA transfer */
    p_ctrl->p_reg->GRP[group].CH[channel].CHCTRL = DMAC_PRV_CHCTRL_CLREN_MASK;

    /* Wait DMA stop */
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->GRP[group].CH[channel].CHSTAT_b.TACT, 0);

    /* DMA Software Reset */
    p_ctrl->p_reg->GRP[group].CH[channel].CHCTRL = DMAC_PRV_CHCTRL_SWRST_MASK;

    /* Set DMA transfer end interrupt mask */
    p_ctrl->p_reg->GRP[group].CH[channel].CHCFG |= DMAC_PRV_CHCFG_DEM_MASK;
}

/*******************************************************************************************************************//**
 * Write the transfer info to the hardware registers.
 *
 * @param[in]   p_ctrl         Pointer to control structure.
 * @param       p_info         Pointer to transfer info.
 **********************************************************************************************************************/
static void r_dmac_config_transfer_info (dmac_instance_ctrl_t * p_ctrl, transfer_info_t * p_info)
{
    dmac_extended_cfg_t  * p_extend      = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    dmac_extended_info_t * p_extend_info = (dmac_extended_info_t *) p_info->p_extend;

    uint8_t group   = DMAC_PRV_GROUP(p_extend->channel);
    uint8_t channel = DMAC_PRV_CHANNEL(p_extend->channel);

    uint32_t dctrl = DMAC_PRV_DCTRL_DEFAULT_VALUE;
    uint32_t chcfg = DMAC_PRV_CHCFG_DEFAULT_VALUE;

    /* Disable transfers if they are currently enabled. */
    r_dmac_prv_disable(p_ctrl);

    /* Priority control select */
    dctrl |= ((p_extend->channel_scheduling) & DMAC_PRV_DCTRL_PR_VALUE_MASK) << DMAC_PRV_DCTRL_PR_OFFSET;

    /* Configure channel */
    chcfg = ((p_extend->channel % 8 & DMAC_PRV_CHCFG_SEL_VALUE_MASK) << DMAC_PRV_CHCFG_SEL_OFFSET) |
            ((p_extend->activation_request_source_select & DMAC_PRV_CHCFG_REQD_VALUE_MASK) <<
             DMAC_PRV_CHCFG_REQD_OFFSET) |
            ((p_extend->detection_mode & DMAC_PRV_CHCFG_DETECT_MODE_VALUE_MASK) << DMAC_PRV_CHCFG_LOEN_OFFSET) |
            ((p_extend->ack_mode & DMAC_PRV_CHCFG_AM_VALUE_MASK) << DMAC_PRV_CHCFG_AM_OFFSET) |
            ((p_extend_info->src_size & DMAC_PRV_CHCFG_SDS_VALUE_MASK) << DMAC_PRV_CHCFG_SDS_OFFSET) |
            ((p_extend_info->dest_size & DMAC_PRV_CHCFG_DDS_VALUE_MASK) << DMAC_PRV_CHCFG_DDS_OFFSET) |
            ((p_info->src_addr_mode & DMAC_PRV_CHCFG_SAD_VALUE_MASK) << DMAC_PRV_CHCFG_SAD_OFFSET) |
            ((p_info->dest_addr_mode & DMAC_PRV_CHCFG_DAD_VALUE_MASK) << DMAC_PRV_CHCFG_DAD_OFFSET) |
            ((p_info->mode & DMAC_PRV_NEXT_REG_VALUE_MASK) << DMAC_PRV_CHCFG_TM_OFFSET);

    if ((NULL != p_extend->p_callback) || (NULL != p_extend->p_peripheral_module_handler))
    {
        /* Enable transfer end interrupt requests. */
        chcfg &= ~((uint32_t) DMAC_PRV_CHCFG_DEM_MASK);

        /* Enable the IRQ in the GIC. */
        R_BSP_IrqDetectTypeSet(p_extend->dmac_int_irq, p_extend->dmac_int_irq_detect_type);
        R_BSP_IrqCfgEnable(p_extend->dmac_int_irq, p_extend->dmac_int_ipl, p_ctrl);
    }
    else
    {
        /* Set DMA transfer end interrupt mask */
        chcfg |= DMAC_PRV_CHCFG_DEM_MASK;
    }

    if (DMAC_REGISTER_SELECT_REVERSE_DISABLE != p_extend->next_register_operaion)
    {
        /* Set DMA transfer end interrupt mask */
        chcfg |= DMAC_PRV_CHCFG_DEM_MASK;

        /* Configure Register Set Reverse Select */
        chcfg |= ((p_extend->next_register_operaion & DMAC_PRV_NEXT_REG_VALUE_MASK) << DMAC_PRV_CHCFG_RSW_OFFSET);
    }

    uint32_t rssel_register_num = p_extend->channel / 3;
    uint32_t rssel_bit_bum      = p_extend->channel % 3;
    if (0 == p_extend->unit)
    {
        /* DMAC0 trigger source set. */
        uint32_t rssel = R_DMA->DMAC0_RSSEL[rssel_register_num];
        rssel &=
            (uint32_t) ~(DMAC_PRV_RSSEL_REQ_SEL_MASK << (DMAC_PRV_RSSEL_REQ_SEL_OFFSET * rssel_bit_bum));

        rssel |= (ELC_EVENT_NONE != p_extend->activation_source) ?
                 (uint32_t) ((p_extend->activation_source) << (DMAC_PRV_RSSEL_REQ_SEL_OFFSET * rssel_bit_bum)) :
                 (uint32_t) (DMAC_PRV_RSSEL_REQ_SEL_MASK << (DMAC_PRV_RSSEL_REQ_SEL_OFFSET * rssel_bit_bum));

        R_DMA->DMAC0_RSSEL[rssel_register_num] = rssel;
    }
    else
    {
        /* DMAC1 trigger source set. */
        uint32_t rssel = R_DMA->DMAC1_RSSEL[rssel_register_num];
        rssel &=
            (uint32_t) ~(DMAC_PRV_RSSEL_REQ_SEL_MASK << (DMAC_PRV_RSSEL_REQ_SEL_OFFSET * rssel_bit_bum));

        rssel |= (ELC_EVENT_NONE != p_extend->activation_source) ?
                 (uint32_t) ((p_extend->activation_source) << (DMAC_PRV_RSSEL_REQ_SEL_OFFSET * rssel_bit_bum)) :
                 (uint32_t) (DMAC_PRV_RSSEL_REQ_SEL_MASK << (DMAC_PRV_RSSEL_REQ_SEL_OFFSET * rssel_bit_bum));

        R_DMA->DMAC1_RSSEL[rssel_register_num] = rssel;
    }

    p_ctrl->p_reg->GRP[group].DCTRL = dctrl;

    /* When DMAC accesses TCM, use CPU0ATCM(0x20000000 - 0x2007FFFF) / CPU0BTCM(0x20100000 - 0x2010FFFF) area. */
    p_ctrl->p_reg->GRP[group].CH[channel].N[0].SA =
        (true == r_dmac_address_tcm_check((uint32_t) p_info->p_src)) ?
        ((uint32_t) p_info->p_src + DMAC_PRV_CPUTCM_BASE_ADDRESS) : ((uint32_t) p_info->p_src);

    p_ctrl->p_reg->GRP[group].CH[channel].N[0].DA =
        (true == r_dmac_address_tcm_check((uint32_t) p_info->p_dest)) ?
        ((uint32_t) p_info->p_dest + DMAC_PRV_CPUTCM_BASE_ADDRESS) : ((uint32_t) p_info->p_dest);

    p_ctrl->p_reg->GRP[group].CH[channel].N[0].TB      = p_info->length;
    p_ctrl->p_reg->GRP[group].CH[channel].CHCFG        = chcfg;
    p_ctrl->p_reg->GRP[group].CH[channel].CHTVL_b.ITVL = p_extend->transfer_interval;

    uint32_t src_address  = (uint32_t) p_info->p_src;
    uint32_t dest_address = (uint32_t) p_info->p_dest;
    uint32_t chext        = r_dmac_config_chext(src_address, dest_address);

    if (DMAC_REGISTER_SELECT_REVERSE_DISABLE != p_extend->next_register_operaion)
    {
        dmac_register_set_setting_t * p_next1_register = p_extend_info->p_next1_register_setting;

        /* When DMAC accesses TCM, use CPU0ATCM(0x20000000 - 0x2007FFFF) / CPU0BTCM(0x20100000 - 0x2010FFFF) area. */
        p_ctrl->p_reg->GRP[group].CH[channel].N[1].SA =
            (true == r_dmac_address_tcm_check((uint32_t) p_next1_register->p_src)) ?
            ((uint32_t) p_next1_register->p_src + DMAC_PRV_CPUTCM_BASE_ADDRESS) :
            ((uint32_t) p_next1_register->p_src);

        p_ctrl->p_reg->GRP[group].CH[channel].N[1].DA =
            (true == r_dmac_address_tcm_check((uint32_t) p_next1_register->p_dest)) ?
            ((uint32_t) p_next1_register->p_dest + DMAC_PRV_CPUTCM_BASE_ADDRESS) :
            ((uint32_t) p_next1_register->p_dest);

        p_ctrl->p_reg->GRP[group].CH[channel].N[1].TB = p_next1_register->length;

        src_address  = (uint32_t) p_next1_register->p_src;
        dest_address = (uint32_t) p_next1_register->p_dest;

        chext |= r_dmac_config_chext(src_address, dest_address);
    }

    p_ctrl->p_reg->GRP[group].CH[channel].CHEXT = chext;
}

/*******************************************************************************************************************//**
 * Determine CHEXT_n register value.
 *
 * @param[in]   src_address               Transfer source address
 * @param[in]   dest_address              Transfer destination address
 *
 * @retval CHEXT_n register value.
 **********************************************************************************************************************/
static uint32_t r_dmac_config_chext (uint32_t src_address, uint32_t dest_address)
{
    uint32_t chext = 0;

    /* The SCA[3:0] bits in CHEXT_n register should be set to 0x02 if source is TCM.
     * (see Section 'Channel Configuration Register n (CHCFG_n)' of the RZ microprocessor).
     */
    if (true == r_dmac_address_tcm_check(src_address))
    {
        chext |= (uint32_t) 0x02 << DMAC_PRV_CHEXT_SCA_OFFSET;
    }

    /* The DXA[3:0] bits in CHEXT_n register should be set to 0x02 if destination is TCM.
     * (see Section 'Channel Configuration Register n (CHCFG_n)' of the RZ microprocessor).
     */
    if (true == r_dmac_address_tcm_check(dest_address))
    {
        chext |= (uint32_t) 0x02 << DMAC_PRV_CHEXT_DCA_OFFSET;;
    }

    return chext;
}

/*******************************************************************************************************************//**
 * Checks if the address is in the TCM area
 *
 * @param[in]   address             Memory address
 *
 * @retval true if the address is in TCM area, false if not
 **********************************************************************************************************************/
static bool r_dmac_address_tcm_check (uint32_t address)
{
    return (bool) ((address <= DMAC_PRV_ATCM_END_ADDRESS) ||
                   ((DMAC_PRV_BTCM_START_ADDRESS <= address) && (address <= DMAC_PRV_BTCM_END_ADDRESS)));
}

#if DMAC_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Parameter checking of R_DMAC_Open.
 *
 * @param[in]   p_ctrl                    Pointer to control structure.
 * @param[in]   p_cfg                     Pointer to configuration structure. All elements of the structure must be
 *                                        set by user.
 *
 * @retval FSP_SUCCESS                    Input Parameters are Valid.
 * @retval FSP_ERR_ASSERTION              An input parameter is invalid.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The configured channel is invalid.
 * @retval FSP_ERR_IRQ_BSP_DISABLED       Callback is NULL and the DMAC IRQ is not enabled.
 * @retval FSP_ERR_ALREADY_OPEN           The control structure is already opened.
 **********************************************************************************************************************/
static fsp_err_t r_dma_open_parameter_checking (dmac_instance_ctrl_t * const p_ctrl, transfer_cfg_t const * const p_cfg)
{
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open != DMAC_ID, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(NULL != p_cfg);
    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_cfg->p_extend;
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ERROR_RETURN(p_extend->channel < BSP_FEATURE_DMAC_MAX_CHANNEL, FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    if (DMAC_REGISTER_SELECT_REVERSE_DISABLE != p_extend->next_register_operaion)
    {
        transfer_info_t * p_info = p_cfg->p_info;
        FSP_ASSERT(NULL != ((dmac_extended_info_t *) p_info->p_extend)->p_next1_register_setting);
    }

    if ((NULL != p_extend->p_callback) || (NULL != p_extend->p_peripheral_module_handler))
    {
        FSP_ERROR_RETURN(p_extend->dmac_int_irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
    }

    fsp_err_t err = r_dmac_info_paramter_checking(p_cfg->p_info);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Checks for errors in the transfer into structure.
 *
 * @param[in]   p_info              Pointer transfer info.
 *
 * @retval FSP_SUCCESS              The transfer info is valid.
 * @retval FSP_ERR_ASSERTION        A transfer info setting is invalid.
 **********************************************************************************************************************/
static fsp_err_t r_dmac_info_paramter_checking (transfer_info_t const * const p_info)
{
    FSP_ASSERT(p_info != NULL);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Parameter checking for r_dmac_prv_enable.
 *
 * @param[in]   p_ctrl                 Pointer to control structure.
 *
 * @retval      FSP_SUCCESS            Alignment on source and destination pointers is valid.
 * @retval      FSP_ERR_ASSERTION      The current configuration is invalid.
 **********************************************************************************************************************/
static fsp_err_t r_dmac_enable_parameter_checking (dmac_instance_ctrl_t * const p_ctrl)
{
    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    uint8_t group   = DMAC_PRV_GROUP(p_extend->channel);
    uint8_t channel = DMAC_PRV_CHANNEL(p_extend->channel);

    void const * p_src  = (void const *) p_ctrl->p_reg->GRP[group].CH[channel].N[0].SA;
    void const * p_dest = (void const *) p_ctrl->p_reg->GRP[group].CH[channel].N[0].DA;

    dmac_transfer_size_t src_size  = (dmac_transfer_size_t) p_ctrl->p_reg->GRP[group].CH[channel].CHCFG_b.SDS;
    dmac_transfer_size_t dest_size = (dmac_transfer_size_t) p_ctrl->p_reg->GRP[group].CH[channel].CHCFG_b.DDS;

    transfer_addr_mode_t src_addr_mode  = (transfer_addr_mode_t) p_ctrl->p_reg->GRP[group].CH[channel].CHCFG_b.SAD;
    transfer_addr_mode_t dest_addr_mode = (transfer_addr_mode_t) p_ctrl->p_reg->GRP[group].CH[channel].CHCFG_b.DAD;

    /* When the transfer source address is beat-aligned, specify SAD = 0 (increment).
     * (See section 'Channel Configuration Register n (CHCFG_n)' of the RZ microprocessor manual) */
    if (0U != ((uint32_t) p_src & DMAC_PRV_MASK_ALIGN_N_BYTES(src_size)))
    {
        FSP_ASSERT(TRANSFER_ADDR_MODE_INCREMENTED == src_addr_mode);
    }

    /* When the transfer destination address is beat-aligned, specify DAD = 0 (increment).
     * (See section 'Channel Configuration Register n (CHCFG_n)' of the RZ microprocessor manual) */
    if (0U != ((uint32_t) p_dest & DMAC_PRV_MASK_ALIGN_N_BYTES(dest_size)))
    {
        FSP_ASSERT(TRANSFER_ADDR_MODE_INCREMENTED == dest_addr_mode);
    }

    if (1 == p_ctrl->p_reg->GRP[group].CH[channel].CHCFG_b.RSW)
    {
        void const * p_src_next1  = (void const *) p_ctrl->p_reg->GRP[group].CH[channel].N[1].SA;
        void const * p_dest_next1 = (void const *) p_ctrl->p_reg->GRP[group].CH[channel].N[1].DA;

        /* The next1 register set source and destination pointers cannot be NULL. */
        FSP_ASSERT(NULL != p_src_next1);
        FSP_ASSERT(NULL != p_dest_next1);

        /* When the transfer source address is beat-aligned, specify SAD = 0 (increment).
         * (See section 'Channel Configuration Register n (CHCFG_n)' of the RZ microprocessor manual) */
        if (0U != ((uint32_t) p_src_next1 & DMAC_PRV_MASK_ALIGN_N_BYTES(src_size)))
        {
            FSP_ASSERT(TRANSFER_ADDR_MODE_INCREMENTED == src_addr_mode);
        }

        /* When the transfer destination address is beat-aligned, specify DAD = 0 (increment).
         * (See section 'Channel Configuration Register n (CHCFG_n)' of the RZ microprocessor manual) */
        if (0U != ((uint32_t) p_dest_next1 & DMAC_PRV_MASK_ALIGN_N_BYTES(dest_size)))
        {
            FSP_ASSERT(TRANSFER_ADDR_MODE_INCREMENTED == dest_addr_mode);
        }
    }

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * DMAC ISR
 **********************************************************************************************************************/
void dmac_int_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    dmac_instance_ctrl_t * p_ctrl   = R_FSP_IsrContextGet(irq);
    dmac_extended_cfg_t  * p_extend = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    uint8_t group   = DMAC_PRV_GROUP(p_extend->channel);
    uint8_t channel = DMAC_PRV_CHANNEL(p_extend->channel);

    /* Clear interrupt condition. */
    p_ctrl->p_reg->GRP[group].CH[channel].CHCTRL = DMAC_PRV_CHCTRL_CLREND_MASK;

    /* Dummy read to ensure that interrupt event is cleared. */
    volatile uint32_t dummy = p_ctrl->p_reg->GRP[group].CH[channel].CHCTRL;
    FSP_PARAMETER_NOT_USED(dummy);

    if (NULL != p_extend->p_peripheral_module_handler)
    {
        /* Call peripheral module handler */
        p_extend->p_peripheral_module_handler((IRQn_Type) p_extend->activation_source);
    }

    if (NULL != p_extend->p_callback)
    {
        /* Call user callback */
        dmac_callback_args_t args;
        args.p_context = p_extend->p_context;
        args.event     = DMAC_EVENT_TRANSFER_END;
        p_extend->p_callback(&args);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
