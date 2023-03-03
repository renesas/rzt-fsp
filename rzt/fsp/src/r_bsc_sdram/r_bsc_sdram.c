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

#include "bsp_api.h"

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_bsc_sdram.h"
#include "r_bsc_sdram_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "BSDR" in ASCII, used to determine if channel is open. */
#define BSC_SDRAM_PRV_OPEN                       (0x42534452)

#define BSC_SDRAM_CHANNEL_DUMMY                  (0x0U)
#define BSC_SDRAM_VALID_CS_CHANNELS              (0x08) /* Valid channel : CS3 */

/* BSC CSNBCR register bit masks */
#define BSC_SDRAM_PRV_CSNBCR_BSZ_VALUE_MASK      (0x03U)
#define BSC_SDRAM_PRV_CSNBCR_IWRRS_VALUE_MASK    (0x07U)
#define BSC_SDRAM_PRV_CSNBCR_IWRRD_VALUE_MASK    (0x07U)
#define BSC_SDRAM_PRV_CSNBCR_IWRWS_VALUE_MASK    (0x07U)
#define BSC_SDRAM_PRV_CSNBCR_IWRWD_VALUE_MASK    (0x07U)
#define BSC_SDRAM_PRV_CSNBCR_IWW_VALUE_MASK      (0x07U)

#define BSC_SDRAM_PRV_CSNBCR_TYPE_SDRAM          (0x04U)
#define BSC_SDRAM_PRV_CSNBCR_RESERVED_Pos        (11U)

/* BSC CSNWCR register bit masks */
#define BSC_SDRAM_PRV_CSNWCR_WTRC_VALUE_MASK     (0x03U)
#define BSC_SDRAM_PRV_CSNWCR_TRWL_VALUE_MASK     (0x03U)
#define BSC_SDRAM_PRV_CSNWCR_A3CL_VALUE_MASK     (0x03U)
#define BSC_SDRAM_PRV_CSNWCR_WTRCD_VALUE_MASK    (0x03U)
#define BSC_SDRAM_PRV_CSNWCR_WTRP_VALUE_MASK     (0x03U)

/* BSC SDCR register bit masks */
#define BSC_SDRAM_PRV_SDCR_A3COL_VALUE_MASK      (0x03U)
#define BSC_SDRAM_PRV_SDCR_A3ROW_VALUE_MASK      (0x03U)
#define BSC_SDRAM_PRV_SDCR_BACTV_VALUE_MASK      (0x01U)

/* BSC RTCSR register bit mask */
#define BSC_SDRAM_PRV_RTCSR_RRC_Pos              (0U)
#define BSC_SDRAM_PRV_RTCSR_RRC_VALUE_MASK       (0x07U)
#define BSC_SDRAM_PRV_RTCSR_CKS_Pos              (3U)
#define BSC_SDRAM_PRV_RTCSR_CKS_VALUE_MASK       (0x07U)
#define BSC_SDRAM_PRV_RTCSR_CMIE_Msk             (0x40UL)
#define BSC_SDRAM_PRV_RTCSR_CMF_Msk              (0x80UL)

/* SDRAM MRS Configuration */
#define BSC_SDRAM_MRS_CS3_ACCESS_ADDRESS_BASE    (0x80212000)
#define BSC_SDRAM_MRS_BUTST_LENGTH_1             (0x00U)
#define BSC_SDRAM_MRS_BURST_LENGTH_Pos           (0U)
#define BSC_SDRAM_MRS_WRAP_SEQUENTIAL            (0x00U)
#define BSC_SDRAM_MRS_WRAP_MODE_Pos              (3U)
#define BSC_SDRAM_MRS_LTMODE_Pos                 (4U)
#define BSC_SDRAM_MRS_LTMODE_VALUE_MASK          (0x07U)
#define BSC_SDRAM_MRS_WRITE_MODE_Pos             (9U)
#define BSC_SDRAM_MRS_WRITE_MODE_VALUE_MASK      (0x01U)

#define BSC_SDRAM_MRS_SETTING_DUMMY_DATA         (0x0000U)

#define BSC_SDRAM_PROTECT_KEY                    (0xA55A0000)

#define BSC_SDRAM_UNIT_CONVERSION                (1000U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef enum e_bsc_sdram_refresh_count_source_div
{
    BSC_SDRAM_REFRESH_COUNT_SOURCE_DIV_4    = 2U,
    BSC_SDRAM_REFRESH_COUNT_SOURCE_DIV_16   = 4U,
    BSC_SDRAM_REFRESH_COUNT_SOURCE_DIV_64   = 6U,
    BSC_SDRAM_REFRESH_COUNT_SOURCE_DIV_256  = 8U,
    BSC_SDRAM_REFRESH_COUNT_SOURCE_DIV_1024 = 10U,
    BSC_SDRAM_REFRESH_COUNT_SOURCE_DIV_2048 = 11U,
    BSC_SDRAM_REFRESH_COUNT_SOURCE_DIV_4096 = 12U,
} bsc_sdram_refresh_count_source_div_t;

typedef struct st_refresh_cycle_setting_const_t
{
    uint8_t count;
    bsc_sdram_refresh_count_source_div_t divider;
} refresh_cycle_setting_const_t;

/***********************************************************************************************************************
 * Private function declarations
 **********************************************************************************************************************/
static fsp_err_t r_bsc_sdram_refresh_cycle_calc(bsc_sdram_instance_ctrl_t     * p_instance_ctrl,
                                                refresh_cycle_setting_const_t * p_ref_cycle);

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/
void bsc_sdram_cmi_int_isr(void);

/** Look-up table for WTRC values */
static const uint32_t wtrc_value_lut[] =
{
    [SDRAM_WAIT_CYCLE_2] = 0U,
    [SDRAM_WAIT_CYCLE_3] = 1U,
    [SDRAM_WAIT_CYCLE_5] = 2U,
    [SDRAM_WAIT_CYCLE_8] = 3U,
};

/** Look-up table for Auto-Refresh count clock source */
static const uint32_t cks_value_lut[] =
{
    [BSC_SDRAM_REFRESH_COUNT_SOURCE_DIV_4]    = 1U,
    [BSC_SDRAM_REFRESH_COUNT_SOURCE_DIV_16]   = 2U,
    [BSC_SDRAM_REFRESH_COUNT_SOURCE_DIV_64]   = 3U,
    [BSC_SDRAM_REFRESH_COUNT_SOURCE_DIV_256]  = 4U,
    [BSC_SDRAM_REFRESH_COUNT_SOURCE_DIV_1024] = 5U,
    [BSC_SDRAM_REFRESH_COUNT_SOURCE_DIV_2048] = 6U,
    [BSC_SDRAM_REFRESH_COUNT_SOURCE_DIV_4096] = 7U,
};

/*******************************************************************************************************************//**
 * @addtogroup BSC_SDRAM
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/
const sdram_api_t g_sdram_on_bsc_sdram =
{
    .open             = R_BSC_SDRAM_Open,
    .selfRefreshEnter = R_BSC_SDRAM_SelfRefreshEnter,
    .selfRefreshExit  = R_BSC_SDRAM_SelfRefreshExit,
    .powerDownEnter   = R_BSC_SDRAM_PowerDownEnter,
    .powerDownExit    = R_BSC_SDRAM_PowerDownExit,
    .close            = R_BSC_SDRAM_Close,
};

/*******************************************************************************************************************//**
 * Open the BSC_SDRAM driver module. Configure the BSC and operate the SDRAM initialization.
 * (PALL command is firstly issued. REF command is issued 8 times. MRS command is finally issued.)
 *
 * User can access to the SDRAM like internal memory starting at address 0x78000000 or 0x58000000.
 *
 * @note After the driver is open, Auto-Refresh operation is started.
 *
 * Implements @ref sdram_api_t::open.
 *
 * @retval FSP_SUCCESS              Configuration was successful.
 * @retval FSP_ERR_ASSERTION        The parameter p_instance_ctrl or p_cfg is NULL.
 * @retval FSP_ERR_INVALID_CHANNEL  Invalid Channel.
 * @retval FSP_ERR_ALREADY_OPEN     Driver has already been opened with the same p_instance_ctrl.
 * @retval FSP_ERR_INVALID_ARGUMENT Auto-Refresh time is not achievable.
 **********************************************************************************************************************/
fsp_err_t R_BSC_SDRAM_Open (sdram_ctrl_t * p_ctrl, sdram_cfg_t const * const p_cfg)
{
    bsc_sdram_instance_ctrl_t * p_instance_ctrl = (bsc_sdram_instance_ctrl_t *) p_ctrl;

#if BSC_SDRAM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ERROR_RETURN(BSC_SDRAM_VALID_CS_CHANNELS & (1U << p_cfg->chip_select), FSP_ERR_INVALID_CHANNEL);
    FSP_ERROR_RETURN(BSC_SDRAM_PRV_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    bsc_sdram_extended_cfg_t * p_cfg_extend = (bsc_sdram_extended_cfg_t *) p_cfg->p_extend;

    /* Enable clock to the BSC block */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_START(FSP_IP_BSC, BSC_CHANNEL_DUMMY);
    R_BSP_MODULE_START(FSP_IP_CKIO, BSC_CHANNEL_DUMMY);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    /* Save configurations. */
    p_instance_ctrl->p_cfg = p_cfg;

    /* Calculate the CSnWCR register base address. */
    uint32_t   address_gap = (uint32_t) &R_BSC->CS3WCR_0 - (uint32_t) &R_BSC->CS2WCR_0;
    uint32_t * p_csnwcr    = (uint32_t *) ((uint32_t) &R_BSC->CS0WCR_0 + (address_gap * p_cfg->chip_select));

    /* Set bus access idle cycle. */
    uint32_t csnbcr = (((p_cfg->data_width & BSC_SDRAM_PRV_CSNBCR_BSZ_VALUE_MASK) <<
                        R_BSC_CSnBCR_BSZ_Pos) |
                       1U << BSC_SDRAM_PRV_CSNBCR_RESERVED_Pos |
                       (BSC_SDRAM_PRV_CSNBCR_TYPE_SDRAM << R_BSC_CSnBCR_TYPE_Pos) |
                       ((p_cfg_extend->r_r_same_space_idle_cycle & BSC_SDRAM_PRV_CSNBCR_IWRRS_VALUE_MASK) <<
                        R_BSC_CSnBCR_IWRRS_Pos) |
                       ((p_cfg_extend->r_r_different_space_idle_cycle & BSC_SDRAM_PRV_CSNBCR_IWRRD_VALUE_MASK) <<
                        R_BSC_CSnBCR_IWRRD_Pos) |
                       ((p_cfg_extend->r_w_same_space_idle_cycle & BSC_SDRAM_PRV_CSNBCR_IWRWS_VALUE_MASK) <<
                        R_BSC_CSnBCR_IWRWS_Pos) |
                       ((p_cfg_extend->r_w_different_space_idle_cycle & BSC_SDRAM_PRV_CSNBCR_IWRWD_VALUE_MASK) <<
                        R_BSC_CSnBCR_IWRWD_Pos) |
                       ((p_cfg_extend->w_r_w_w_idle_cycle & BSC_SDRAM_PRV_CSNBCR_IWW_VALUE_MASK) <<
                        R_BSC_CSnBCR_IWW_Pos));

    /* Set SDRAM wait control setting. */
    uint32_t wtrc   = wtrc_value_lut[p_cfg->row_cycle];
    uint32_t csnwcr = (wtrc & BSC_SDRAM_PRV_CSNWCR_WTRC_VALUE_MASK) << R_BSC_CS3WCR_1_WTRC_Pos |
                      (p_cfg->write_recovery_cycle & BSC_SDRAM_PRV_CSNWCR_TRWL_VALUE_MASK) << R_BSC_CS3WCR_1_TRWL_Pos |
                      ((p_cfg->cas_latency - 1U) & BSC_SDRAM_PRV_CSNWCR_A3CL_VALUE_MASK) << R_BSC_CS3WCR_1_A3CL_Pos |
                      (p_cfg->ras_to_cas_delay_cycle & BSC_SDRAM_PRV_CSNWCR_WTRCD_VALUE_MASK) <<
                      R_BSC_CS3WCR_1_WTRCD_Pos |
                      (p_cfg->ras_precharge_cycle & BSC_SDRAM_PRV_CSNWCR_WTRP_VALUE_MASK) << R_BSC_CS3WCR_1_WTRP_Pos;

    /* Set SDRAM control setting. */
    uint32_t sdcr = (p_cfg->column_address_width & BSC_SDRAM_PRV_SDCR_A3COL_VALUE_MASK) << R_BSC_SDCR_A3COL_Pos |
                    ((p_cfg->row_address_width - 3U) & BSC_SDRAM_PRV_SDCR_A3ROW_VALUE_MASK) << R_BSC_SDCR_A3ROW_Pos |
                    (p_cfg_extend->command_mode & BSC_SDRAM_PRV_SDCR_BACTV_VALUE_MASK) << R_BSC_SDCR_BACTV_Pos |
                    0U << R_BSC_SDCR_RMODE_Pos | /* Refresh operation : Auto-Refresh */
                    R_BSC_SDCR_RFSH_Msk;         /* Refresh operation : Enable */

    /* Set SDRAM control setting. For setting RTCSR.RRC bit
     * Refresh count = 1 time  -> RTCSR.RRC = 0
     * Refresh count = 2 times -> RTCSR.RRC = 1
     * Refresh count = 4 times -> RTCSR.RRC = 2
     * Refresh count = 6 times -> RTCSR.RRC = 3
     * Refresh count = 8 times -> RTCSR.RRC = 4 */
    uint32_t rrc = p_cfg->refresh_request_count >> 1;

    refresh_cycle_setting_const_t ref_cycle_settings;
    fsp_err_t ret = r_bsc_sdram_refresh_cycle_calc(p_instance_ctrl, &ref_cycle_settings);

    uint32_t rtcsr = (rrc & BSC_SDRAM_PRV_RTCSR_RRC_VALUE_MASK << BSC_SDRAM_PRV_RTCSR_RRC_Pos) |
                     ((cks_value_lut[ref_cycle_settings.divider] & BSC_SDRAM_PRV_RTCSR_CKS_VALUE_MASK) <<
                      BSC_SDRAM_PRV_RTCSR_CKS_Pos) |
                     BSC_SDRAM_PRV_RTCSR_CMIE_Msk;

    R_BSC->CSnBCR[p_cfg->chip_select] = csnbcr;
    R_BSC->SDCR  = sdcr;
    R_BSC->RTCNT = BSC_SDRAM_PROTECT_KEY | 0x00U;
    R_BSC->RTCOR = BSC_SDRAM_PROTECT_KEY | ref_cycle_settings.count;
    R_BSC->RTCSR = BSC_SDRAM_PROTECT_KEY | rtcsr;

    *p_csnwcr = csnwcr;

    /* Set SDRAM Mode Register (MRS) */
    uint32_t mrs = (BSC_SDRAM_MRS_BUTST_LENGTH_1 << BSC_SDRAM_MRS_BURST_LENGTH_Pos) |
                   (BSC_SDRAM_MRS_WRAP_SEQUENTIAL << BSC_SDRAM_MRS_WRAP_MODE_Pos) |
                   ((p_cfg->cas_latency & BSC_SDRAM_MRS_LTMODE_VALUE_MASK) << BSC_SDRAM_MRS_LTMODE_Pos) |
                   ((p_cfg->write_burst_mode & BSC_SDRAM_MRS_WRITE_MODE_VALUE_MASK) << BSC_SDRAM_MRS_WRITE_MODE_Pos);

    /* The MRS setting value is written to the SDRAM by performing a 16-bit write to particular address.
     * (see RZ microprocessor User's Manual section "Power-On sequence" of "SDRAM Interface") */
    uint32_t mrs_setting_addr = BSC_SDRAM_MRS_CS3_ACCESS_ADDRESS_BASE | (mrs << (p_cfg->data_width - 1));
    *(volatile uint16_t *) mrs_setting_addr = BSC_SDRAM_MRS_SETTING_DUMMY_DATA;
    __asm volatile ("dsb");

    /* Set callback and context pointers */
    p_instance_ctrl->p_callback = p_cfg_extend->p_callback;
    p_instance_ctrl->p_context  = p_cfg_extend->p_context;

    /* Enable CPU interrupts. */
    if (p_cfg_extend->cmi_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg_extend->cmi_irq, p_cfg_extend->cmi_ipl, p_instance_ctrl);
    }

    if (FSP_SUCCESS == ret)
    {
        p_instance_ctrl->open = BSC_SDRAM_PRV_OPEN;
    }

    return ret;
}

/*******************************************************************************************************************//**
 * Enters Self-Refresh mode.
 *
 * Implements @ref sdram_api_t::selfRefreshEnter.
 *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_INVALID_MODE        This function can't be called when SDRAM is in Power-down mode.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_BSC_SDRAM_SelfRefreshEnter (sdram_ctrl_t * p_ctrl)
{
    bsc_sdram_instance_ctrl_t * p_instance_ctrl = (bsc_sdram_instance_ctrl_t *) p_ctrl;
#if BSC_SDRAM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(BSC_SDRAM_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Do not enter Self-Refresh mode from Power-Down mode. */
    FSP_ERROR_RETURN(0U == R_BSC->SDCR_b.PDOWN, FSP_ERR_INVALID_MODE);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Enter Self-Refresh operation by setting both the RMODE bit and the RFSH bit in SDCR to 1.
     * (see RZ microprocessor User's Manual section "Refreshing" of "SDRAM Interface") */
    R_BSC->SDCR |= (R_BSC_SDCR_RMODE_Msk | R_BSC_SDCR_RFSH_Msk);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Exits Self-Refresh mode. Auto-Refresh operation is re-started to the SDRAM.
 *
 * Implements @ref sdram_api_t::selfRefreshExit.
 *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_BSC_SDRAM_SelfRefreshExit (sdram_ctrl_t * p_ctrl)
{
    bsc_sdram_instance_ctrl_t * p_instance_ctrl = (bsc_sdram_instance_ctrl_t *) p_ctrl;
#if BSC_SDRAM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(BSC_SDRAM_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Auto-Refresh is started if the RFSH bit is set to 1 and the RMODE bit is cleared to 0.
     * (see RZ microprocessor User's Manual section "Refreshing" of "SDRAM Interface") */
    uint32_t sdcr = R_BSC->SDCR;
    sdcr       &= ~R_BSC_SDCR_RMODE_Msk;
    sdcr       |= R_BSC_SDCR_RFSH_Msk;
    R_BSC->SDCR = sdcr;

    /* Making the RTCNT value 1 less than the RTCOR value will enable refreshing to be started immediately.
     * (see RZ microprocessor User's Manual section "Refreshing" of "SDRAM Interface") */
    uint32_t rtcor = R_BSC->RTCOR;
    R_BSC->RTCNT = BSC_SDRAM_PROTECT_KEY | (rtcor - 1);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enters Power-Down mode.
 *
 * Implements @ref sdram_api_t::powerDownEnter.
 *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_INVALID_MODE        This function can't be called when SDRAM is in Self-Refresh mode.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_BSC_SDRAM_PowerDownEnter (sdram_ctrl_t * p_ctrl)
{
    bsc_sdram_instance_ctrl_t * p_instance_ctrl = (bsc_sdram_instance_ctrl_t *) p_ctrl;
#if BSC_SDRAM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(BSC_SDRAM_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Do not enter Power-Down mode from Self-Refresh mode. */
    FSP_ERROR_RETURN(0U == R_BSC->SDCR_b.RMODE, FSP_ERR_INVALID_MODE);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* The PDOWN bit in SDCR is set to 1 to enter the SDRAM power-down mode. */
    R_BSC->SDCR |= R_BSC_SDCR_PDOWN_Msk;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Exits Power-Down mode.
 *
 * Implements @ref sdram_api_t::powerDownExit.
 *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_BSC_SDRAM_PowerDownExit (sdram_ctrl_t * p_ctrl)
{
    bsc_sdram_instance_ctrl_t * p_instance_ctrl = (bsc_sdram_instance_ctrl_t *) p_ctrl;
#if BSC_SDRAM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(BSC_SDRAM_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    FSP_PARAMETER_NOT_USED(p_instance_ctrl);

    /* The PDOWN bit in SDCR is set to 0 to exit the SDRAM Power-Down mode. */
    R_BSC->SDCR &= ~R_BSC_SDCR_PDOWN_Msk;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Close the BSC_SDRAM driver module.
 *
 * Implements @ref sdram_api_t::close.
 *
 * @retval FSP_SUCCESS             Configuration was successful.
 * @retval FSP_ERR_ASSERTION       p_instance_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN        Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_BSC_SDRAM_Close (sdram_ctrl_t * p_ctrl)
{
    bsc_sdram_instance_ctrl_t * p_instance_ctrl = (bsc_sdram_instance_ctrl_t *) p_ctrl;
#if BSC_SDRAM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(BSC_SDRAM_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Disable clock to the BSC block */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_STOP(FSP_IP_BSC, BSC_CHANNEL_DUMMY);
    R_BSP_MODULE_STOP(FSP_IP_CKIO, BSC_CHANNEL_DUMMY);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup BSC_SDRAM)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Calculates refresh time settings. Evaluates and determines the best possible settings set to the refresh time
 * related registers.
 *
 * @param[in]  p_instance_ctrl           Pointer to a driver handle
 * @param[out] p_ref_cycle               Timer setting information stored here if successful
 *
 * @retval FSP_SUCCESS                  Valid RTCOR.RFSHTV and RTCSR.CKS values were calculated
 * @retval FSP_ERR_INVALID_ARGUMENT     Auto-Refresh time is not achievable
 **********************************************************************************************************************/
static fsp_err_t r_bsc_sdram_refresh_cycle_calc (bsc_sdram_instance_ctrl_t     * p_instance_ctrl,
                                                 refresh_cycle_setting_const_t * p_ref_cycle)
{
    /* In this function, if the calculated result is indivisible, the decimal point is rounded down.
     * This allows to set an interval time that is always shorter than the user-input tREF,
     * so the SDRAM tREF timing regulation violations do not occur. */

    fsp_err_t ret = FSP_SUCCESS;

    uint32_t peripheral_clock_hz                = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_CKIO);
    uint32_t requested_tref_period_ms           = p_instance_ctrl->p_cfg->auto_refresh_cycle;
    sdram_address_bus_width_t row_address_width = p_instance_ctrl->p_cfg->row_address_width;

    /* Calculate the number of SDRAM row address bit.
     * SDRAM_ADDRESS_BUS_WIDTH_11_BITS = 0x3 -> Row address number = 2^(3 + 8) = 2048 row,
     * SDRAM_ADDRESS_BUS_WIDTH_12_BITS = 0x4 -> Row address number = 2^(4 + 8) = 4096 row,
     * SDRAM_ADDRESS_BUS_WIDTH_13_BITS = 0x5 -> Row address number = 2^(5 + 8) = 8192 row,
     */
    uint32_t sdram_address_row_bit_number = 1U << (row_address_width + 8);

    /* Required refresh period of SDRAM */
    uint64_t requested_refresh_period_ns = requested_tref_period_ms * BSC_SDRAM_UNIT_CONVERSION *
                                           BSC_SDRAM_UNIT_CONVERSION;
    requested_refresh_period_ns = requested_refresh_period_ns / sdram_address_row_bit_number;

    /* Get count number to count */
    uint64_t period_counts = requested_refresh_period_ns * peripheral_clock_hz /
                             BSC_SDRAM_UNIT_CONVERSION / BSC_SDRAM_UNIT_CONVERSION / BSC_SDRAM_UNIT_CONVERSION;

    /* The number of continuous refresh cycles make the period of occurrence of refresh long. */
    period_counts = period_counts * (p_instance_ctrl->p_cfg->refresh_request_count);

    /* BSC is from 4 divisions. Therefore, it is calculated from the 4-divided value first. */
    period_counts /= 4;

    /* Calculate the smallest divider required to fit the period in 8 bits. */
    uint32_t divider     = 2;
    uint32_t max_divider = 12;

    while (period_counts > (UINT8_MAX + 1))
    {
        period_counts /= 2;
        divider       += 1;

        /* 3 (= 2^3 = 8 division), 5 (= 2^5 = 32 division), 7 (= 2^7 = 128 division), 9 (= 2^9 = 512 division)
         * cannot be set by BSC. */
        if ((3 == divider) || (5 == divider) || (7 == divider) || (9 == divider))
        {
            period_counts /= 2;
            divider       += 1;
            continue;
        }

        /* If the divider is larger than the maximum divider, set the period and divider to the maximum. */
        if (divider > max_divider)
        {
            period_counts = UINT8_MAX;
            divider       = max_divider;
            ret           = FSP_ERR_INVALID_ARGUMENT;
            break;
        }
    }

    /* If the requested period is less than one count, set the period to 1 count and the divider to 2. */
    if (period_counts == 0)
    {
        period_counts = 1;
        divider       = 2;
    }

    p_ref_cycle->count   = period_counts & UINT8_MAX;
    p_ref_cycle->divider = (bsc_sdram_refresh_count_source_div_t) divider;

    return ret;
}

/*******************************************************************************************************************//**
 * BSC_CMI interrupt processing. When an CMI interrupt fires, the user callback function is called if it is
 * registered in R_BSC_SDRAM_Open() and clear interrupt flag.
 **********************************************************************************************************************/
void bsc_sdram_cmi_int_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    bsc_sdram_instance_ctrl_t * p_instance_ctrl = (bsc_sdram_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Invoke the callback function if it is set. */
    if (NULL != p_instance_ctrl->p_callback)
    {
        /* Setup parameters for the user-supplied callback function. */
        bsc_sdram_callback_args_t callback_args;

        callback_args.p_context = p_instance_ctrl->p_context;

        p_instance_ctrl->p_callback(&callback_args);
    }

    /* Clear Compare Match Flag. */
    uint32_t rtcsr = R_BSC->RTCSR;
    rtcsr       &= ~BSC_SDRAM_PRV_RTCSR_CMF_Msk;
    R_BSC->RTCSR = BSC_SDRAM_PROTECT_KEY | rtcsr;

    /* Dummy read to ensure that interrupt event is cleared. */
    volatile uint32_t dummy = R_BSC->RTCSR;
    FSP_PARAMETER_NOT_USED(dummy);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
