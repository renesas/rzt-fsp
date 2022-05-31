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

#include "bsp_api.h"

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_bsc.h"
#include "r_bsc_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BSC_PRV_OPEN                               (0x425343)
#define BSC_CHANNEL_DUMMY                          (0x0U)

#define BSC_VALID_CS_CHANNELS                      (0x2D) /* Valid channel : CS0,2,3,5 */
#define BSC_R_W_SAME_ACCESS_WAIT_CHANNELS          (0x0D) /* Valid channel : CS0,2,3 */
#define BSC_CS_TIMING_CONFIGURE_ENABLE_CHANNELS    (0x21) /* Valid channel : CS0,5 */

#define BSC_PRV_CSNBCR_BSZ_VALUE_MASK              (0x03U)
#define BSC_PRV_CSNBCR_TYPE_VALUE_MASK             (0x07U)
#define BSC_PRV_CSNBCR_IWRRS_VALUE_MASK            (0x07U)
#define BSC_PRV_CSNBCR_IWRRD_VALUE_MASK            (0x07U)
#define BSC_PRV_CSNBCR_IWRWS_VALUE_MASK            (0x07U)
#define BSC_PRV_CSNBCR_IWRWD_VALUE_MASK            (0x07U)
#define BSC_PRV_CSNBCR_IWW_VALUE_MASK              (0x07U)

#define BSC_PRV_CSNWCR_HW_VALUE_MASK               (0x03U)
#define BSC_PRV_CSNWCR_SW_VALUE_MASK               (0x03U)
#define BSC_PRV_CSNWCR_WM_VALUE_MASK               (0x01U)
#define BSC_PRV_CSNWCR_WR_VALUE_MASK               (0x0FU)

#define BSC_PRV_CSNWCR_WW_VALUE_MASK               (0x07U)
#define BSC_PRV_CSNWCR_MPXWSBAS_VALUE_MASK         (0x01U)
#define BSC_PRV_CSNWCR_SZSEL_VALUE_MASK            (0x01U)

/*******************************************************************************************************************//**
 * @addtogroup BSC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/
const external_bus_api_t g_external_bus_on_bsc =
{
    .open  = R_BSC_Open,
    .close = R_BSC_Close,
};

/*******************************************************************************************************************//**
 * Open the BSC driver module. After the driver is open, the BSC can be accessed like internal flash memory starting
 * at address 0x70000000 or 0x50000000.
 *
 * Implements @ref external_bus_api_t::open.
 *
 * @retval FSP_SUCCESS             Configuration was successful.
 * @retval FSP_ERR_ASSERTION       The parameter p_instance_ctrl or p_cfg is NULL.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT Invalid Channel.
 * @retval FSP_ERR_ALREADY_OPEN    Driver has already been opened with the same p_instance_ctrl.
 **********************************************************************************************************************/
fsp_err_t R_BSC_Open (external_bus_ctrl_t * p_ctrl, external_bus_cfg_t const * const p_cfg)
{
    bsc_instance_ctrl_t * p_instance_ctrl = (bsc_instance_ctrl_t *) p_ctrl;

#if BSC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ERROR_RETURN(BSC_VALID_CS_CHANNELS & (1U << p_cfg->chip_select), FSP_ERR_IP_CHANNEL_NOT_PRESENT);
    FSP_ERROR_RETURN(BSC_PRV_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    /* The number of wait insertions for read and write access cannot be set individually.
     * This depends on the CS number. */
    if (BSC_R_W_SAME_ACCESS_WAIT_CHANNELS & (1U << p_cfg->chip_select))
    {
        FSP_ASSERT(BSC_ACCESS_WAIT_CYCLE_SAME_AS_READ_ACCESS ==
                   ((bsc_extended_cfg_t *) p_cfg->p_extend)->write_access_wait_cycle);
    }

    /* If wait insertion can be set individually for read and write,
     * the number of wait insertion for write access should be less than 6 wait or the same as read access waits. */
    if (!(BSC_R_W_SAME_ACCESS_WAIT_CHANNELS & (1U << p_cfg->chip_select)))
    {
        FSP_ASSERT((((bsc_extended_cfg_t *) p_cfg->p_extend)->write_access_wait_cycle <= BSC_ACCESS_WAIT_CYCLE_6) ||
                   ((bsc_extended_cfg_t *) p_cfg->p_extend)->write_access_wait_cycle ==
                   BSC_ACCESS_WAIT_CYCLE_SAME_AS_READ_ACCESS);
    }
#endif

    bsc_extended_cfg_t * p_cfg_extend = (bsc_extended_cfg_t *) p_cfg->p_extend;

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
    uint32_t csnbcr = (((p_cfg->data_width & BSC_PRV_CSNBCR_BSZ_VALUE_MASK) <<
                        R_BSC_CSnBCR_BSZ_Pos) |
                       ((p_cfg_extend->memory_type & BSC_PRV_CSNBCR_TYPE_VALUE_MASK) <<
                        R_BSC_CSnBCR_TYPE_Pos) |
                       ((p_cfg_extend->r_r_same_space_idle_cycle & BSC_PRV_CSNBCR_IWRRS_VALUE_MASK) <<
                        R_BSC_CSnBCR_IWRRS_Pos) |
                       ((p_cfg_extend->r_r_different_space_idle_cycle & BSC_PRV_CSNBCR_IWRRD_VALUE_MASK) <<
                        R_BSC_CSnBCR_IWRRD_Pos) |
                       ((p_cfg_extend->r_w_same_space_idle_cycle & BSC_PRV_CSNBCR_IWRWS_VALUE_MASK) <<
                        R_BSC_CSnBCR_IWRWS_Pos) |
                       ((p_cfg_extend->r_w_different_space_idle_cycle & BSC_PRV_CSNBCR_IWRWD_VALUE_MASK) <<
                        R_BSC_CSnBCR_IWRWD_Pos) |
                       ((p_cfg_extend->w_r_w_w_idle_cycle & BSC_PRV_CSNBCR_IWW_VALUE_MASK) <<
                        R_BSC_CSnBCR_IWW_Pos));

    /* Set access wait cycle.
     * If the channel can be set read/write individually, set read access wait cycle here. */
    uint32_t csnwcr = (p_cfg_extend->read_access_wait_cycle & BSC_PRV_CSNWCR_WR_VALUE_MASK) << R_BSC_CS0WCR_0_WR_Pos;

    /* Set write access wait cycle if it can be set individually. */
    if (!((BSC_R_W_SAME_ACCESS_WAIT_CHANNELS) & (1U << p_cfg->chip_select)))
    {
        if (BSC_ACCESS_WAIT_CYCLE_SAME_AS_READ_ACCESS != p_cfg_extend->write_access_wait_cycle)
        {
            csnwcr |=
                (uint32_t) ((p_cfg_extend->write_access_wait_cycle & BSC_PRV_CSNWCR_WW_VALUE_MASK) + 1) <<
                    R_BSC_CS5WCR_WW_Pos;
        }
        else
        {
            /* Set 0 if set write access wait cycle to be the same as the read access wait cycle. */
            csnwcr &= ~R_BSC_CS5WCR_WW_Msk;
        }
    }

    /* Set CS timing. */
    if (BSC_CS_TIMING_CONFIGURE_ENABLE_CHANNELS & (1U << p_cfg->chip_select))
    {
        csnwcr |= (((p_cfg_extend->cs_pullup_lag & BSC_PRV_CSNWCR_HW_VALUE_MASK) << R_BSC_CS0WCR_0_HW_Pos) |
                   ((p_cfg_extend->cs_pulldown_lead & BSC_PRV_CSNWCR_SW_VALUE_MASK) << R_BSC_CS0WCR_0_SW_Pos));
    }

    R_BSC->CSnBCR[p_cfg->chip_select] = csnbcr;
    *p_csnwcr = csnwcr;

    p_instance_ctrl->open = BSC_PRV_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Close the BSC driver module.
 *
 * Implements @ref external_bus_api_t::close.
 *
 * @retval FSP_SUCCESS             Configuration was successful.
 * @retval FSP_ERR_ASSERTION       p_instance_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN        Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_BSC_Close (external_bus_ctrl_t * p_ctrl)
{
    bsc_instance_ctrl_t * p_instance_ctrl = (bsc_instance_ctrl_t *) p_ctrl;
#if BSC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(BSC_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
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
 * @} (end addtogroup BSC)
 **********************************************************************************************************************/
