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
#include "r_spi.h"
#include "r_spi_cfg.h"

#if SPI_DMAC_SUPPORT_ENABLE == 1
 #include "r_dmac.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** "SPI" in ASCII, used to determine if channel is open. */
#define SPI_OPEN                         (0x52535049ULL)

/** SPI base register access macro.  */
#define SPI_REG(channel)    ((R_SPI0_Type *) ((uint32_t) R_SPI0 +                       \
                                              ((uint32_t) R_SPI1 - (uint32_t) R_SPI0) * \
                                              (channel)))

#define SPI_DMAC_RX_TRANSFER_SETTINGS    ((TRANSFER_MODE_NORMAL << TRANSFER_SETTINGS_MODE_BITS) |         \
                                          (TRANSFER_ADDR_MODE_FIXED << TRANSFER_SETTINGS_SRC_ADDR_BITS) | \
                                          (TRANSFER_ADDR_MODE_INCREMENTED << TRANSFER_SETTINGS_DEST_ADDR_BITS))

#define SPI_DMAC_TX_TRANSFER_SETTINGS    ((TRANSFER_MODE_NORMAL << TRANSFER_SETTINGS_MODE_BITS) |               \
                                          (TRANSFER_ADDR_MODE_INCREMENTED << TRANSFER_SETTINGS_SRC_ADDR_BITS) | \
                                          (TRANSFER_ADDR_MODE_FIXED << TRANSFER_SETTINGS_DEST_ADDR_BITS))

#define SPI_CLK_N_DIV_MULTIPLIER         (512U)  ///< Maximum divider for N=0
#define SPI_CLK_MAX_DIV                  (4096U) ///< Maximum SPI CLK divider
#define SPI_CLK_MIN_DIV                  (2U)    ///< Minimum SPI CLK divider
#define SPI_SPDR_BYTE_VALUE_MASK         (0xFFU)
#define SPI_SPDR_HALFWARD_VALUE_MASK     (0xFFFFU)
#define SPI_SPDCR2_TTRG_DMA_VALUE        (0x0U)
#define SPI_SPDCR2_RTRG_DMA_VALUE        (0x0U)

/* Clock frequency 96MHz. */
#define SPI_CLOCK_96MHZ                  (96000000)

/* Worst case ratio of (CPUnCLK/PCLKSPIn) = 10.666... -> 11 bytes approximately.
 * A synchronization delay time of 3PCLKSPIn is required for signal propagation.
 */
#define SPI_PERIPHERAL_REG_MAX_WAIT      (0x0BU * 0x03U)

/* This macro is used for status poring of SPPSR.SPEPS.
 * Reference section "SPI Operation" in the RZ microprocessor manual.
 */
#define SPI_HARDWARE_REGISTER_WAIT(reg, required_value, timeout) \
    while ((timeout))                                            \
    {                                                            \
        if ((required_value) == (reg))                           \
        {                                                        \
            break;                                               \
        }                                                        \
        (timeout)--;                                             \
    }

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Frame data length */
typedef enum e_spi_spcmd_bit_length
{
    SPI_SPCMD_BIT_LENGTH_8  = (0x7),   /**< 00111 = 8 bits data length */
    SPI_SPCMD_BIT_LENGTH_16 = (0xF),   /**< 01111 = 16 bits data length */
    SPI_SPCMD_BIT_LENGTH_32 = (0x1F)   /**< 11111 = 32 bits data length */
} spi_spcmd_bit_length_t;

/***********************************************************************************************************************
 * Private function declarations
 **********************************************************************************************************************/
static fsp_err_t r_spi_transfer_config(spi_cfg_t const * const p_cfg);
static void      r_spi_hw_config(spi_instance_ctrl_t * p_ctrl);
static void      r_spi_gic_config(spi_instance_ctrl_t * p_ctrl);

static void      r_spi_bit_width_config(spi_instance_ctrl_t * p_ctrl);
static void      r_spi_start_transfer(spi_instance_ctrl_t * p_ctrl);
static fsp_err_t r_spi_write_read_common(spi_ctrl_t * const    p_api_ctrl,
                                         void const          * p_src,
                                         void                * p_dest,
                                         uint32_t const        length,
                                         spi_bit_width_t const bit_width);

static void r_spi_receive(spi_instance_ctrl_t * p_ctrl);
static void r_spi_transmit(spi_instance_ctrl_t * p_ctrl);

static void spi_rxi_common(spi_instance_ctrl_t * p_ctrl);

#if SPI_TRANSMIT_FROM_RXI_ISR == 0
static void spi_txi_common(spi_instance_ctrl_t * p_ctrl);

#endif

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/
void spi_rxi_isr(void);
void spi_txi_isr(void);
void spi_tei_isr(void);
void spi_eri_isr(void);

#if SPI_DMAC_SUPPORT_ENABLE == 1
void spi_rxi_dmac_isr(IRQn_Type irq);
void spi_txi_dmac_isr(IRQn_Type irq);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Version data structure used by error logger macro. */
static const fsp_version_t module_version =
{
    .api_version_major  = SPI_API_VERSION_MAJOR,
    .api_version_minor  = SPI_API_VERSION_MINOR,
    .code_version_major = SPI_CODE_VERSION_MAJOR,
    .code_version_minor = SPI_CODE_VERSION_MINOR
};

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/* SPI implementation of SPI interface. */
const spi_api_t g_spi_on_spi =
{
    .open        = R_SPI_Open,
    .read        = R_SPI_Read,
    .write       = R_SPI_Write,
    .writeRead   = R_SPI_WriteRead,
    .close       = R_SPI_Close,
    .versionGet  = R_SPI_VersionGet,
    .callbackSet = R_SPI_CallbackSet
};

/*******************************************************************************************************************//**
 * @addtogroup SPI
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * This functions initializes a channel for SPI communication mode. Implements @ref spi_api_t::open.
 *
 * This function performs the following tasks:
 * - Performs parameter checking and processes error conditions.
 * - Configures the pperipheral registers acording to the configuration.
 * - Initialize the control structure for use in other @ref SPI_API functions.
 *
 * @retval     FSP_SUCCESS                     Channel initialized successfully.
 * @retval     FSP_ERR_ALREADY_OPEN            Instance was already initialized.
 * @retval     FSP_ERR_ASSERTION               An invalid argument was given in the configuration structure.
 * @retval     FSP_ERR_UNSUPPORTED             A requested setting is not possible on this device with the current build
 *                                             configuration.
 * @retval     FSP_ERR_IP_CHANNEL_NOT_PRESENT  The channel number is invalid.
 * @retval     FSP_ERR_INVALID_ARGUMENT        Invalid input parameter.
 * @return     See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes. This
 *             function calls: @ref transfer_api_t::open
 * @note       This function is reentrant.
 **********************************************************************************************************************/
fsp_err_t R_SPI_Open (spi_ctrl_t * p_api_ctrl, spi_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

    spi_instance_ctrl_t * p_ctrl = (spi_instance_ctrl_t *) p_api_ctrl;

#if SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SPI_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_callback);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ERROR_RETURN(BSP_FEATURE_SPI_MAX_CHANNEL > p_cfg->channel, FSP_ERR_IP_CHANNEL_NOT_PRESENT);
    FSP_ASSERT(p_cfg->rxi_irq >= 0);
    FSP_ASSERT(p_cfg->txi_irq >= 0);
    FSP_ASSERT(p_cfg->tei_irq >= 0);
    FSP_ASSERT(p_cfg->eri_irq >= 0);

    /* CPHA=0 is not supported in slave mode because of hardware limitations. Reference section "Slave
     * mode operation" in the RZ microprocessor manual. */
    if (SPI_MODE_SLAVE == p_cfg->operating_mode)
    {
        FSP_ERROR_RETURN(SPI_CLK_PHASE_EDGE_EVEN == p_cfg->clk_phase, FSP_ERR_UNSUPPORTED);
    }

 #if BSP_FEATURE_SPI_HAS_SSL_LEVEL_KEEP == 0 || BSP_FEATURE_SPI_HAS_BYTE_SWAP == 0 || SPI_TRANSMIT_FROM_RXI_ISR == 1 || \
    SPI_DMAC_SUPPORT_ENABLE == 1
    spi_extended_cfg_t * p_extend = (spi_extended_cfg_t *) p_cfg->p_extend;
 #endif
 #if SPI_TRANSMIT_FROM_RXI_ISR == 1

    /* Half Duplex - Transmit Only mode is not supported when transmit interrupt is handled in the RXI ISR. */
    FSP_ERROR_RETURN(p_extend->spi_comm != SPI_COMMUNICATION_TRANSMIT_ONLY, FSP_ERR_UNSUPPORTED);

    /* When the TXI Interrupt is handled in the RXI ISR, a TX DMAC instance must be present if there is a
     * RX DMAC instance present otherwise the TXI Interrupts will not be processed. */
    if (p_cfg->p_transfer_rx)
    {
        FSP_ERROR_RETURN(0 != p_cfg->p_transfer_tx, FSP_ERR_UNSUPPORTED);
    }
 #endif

 #if BSP_FEATURE_SPI_HAS_BYTE_SWAP == 0
    FSP_ERROR_RETURN(SPI_BYTE_SWAP_DISABLE == p_extend->byte_swap, FSP_ERR_UNSUPPORTED);
 #endif
 #if BSP_FEATURE_SPI_HAS_SSL_LEVEL_KEEP == 0
    if ((SPI_MODE_MASTER == p_cfg->operating_mode))
    {
        /* 4-Wire Mode is not supported in master mode on devices without SSL_LEVEL_KEEP */
        FSP_ERROR_RETURN(SPI_SSL_MODE_SPI != p_extend->spi_clksyn, FSP_ERR_UNSUPPORTED);
    }
 #endif

 #if SPI_DMAC_SUPPORT_ENABLE == 1
    if ((NULL != p_ctrl->p_cfg->p_transfer_rx) || (NULL != p_ctrl->p_cfg->p_transfer_tx))
    {
        /* DMAC activation is not available for safety channel. */
        FSP_ERROR_RETURN(BSP_FEATURE_SPI_SAFETY_CHANNEL != p_cfg->channel, FSP_ERR_INVALID_ARGUMENT);

        /* When using DMA, set the threshold to 0 for RTRG and TTRG bits. */
        FSP_ERROR_RETURN(SPI_SPDCR2_TTRG_DMA_VALUE == p_extend->transmit_fifo_threshold, FSP_ERR_UNSUPPORTED);
        FSP_ERROR_RETURN(SPI_SPDCR2_RTRG_DMA_VALUE == p_extend->receive_fifo_threshold, FSP_ERR_UNSUPPORTED);
    }
 #endif
#endif

    /* Configure transfers if they are provided in p_cfg. */
    err = r_spi_transfer_config(p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Get the register address of the channel. */
    p_ctrl->p_cfg             = p_cfg;
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

    if (p_cfg->channel != BSP_FEATURE_SPI_SAFETY_CHANNEL)
    {
        /* Non-Safety Peripheral */
        p_ctrl->p_regs = SPI_REG(p_ctrl->p_cfg->channel);
    }
    else
    {
        /* Safety Peripheral */
        p_ctrl->p_regs = (R_SPI0_Type *) BSP_FEATURE_SPI_SAFETY_CHANNEL_BASE_ADDRESS;
    }

    /* Configure hardware registers according to the r_spi_api configuration structure. */
    r_spi_hw_config(p_ctrl);

    /* Enable interrupts in GIC. */
    r_spi_gic_config(p_ctrl);

    p_ctrl->open = SPI_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * This function receives data from a SPI device. Implements @ref spi_api_t::read.
 *
 * The function performs the following tasks:
 * - Performs parameter checking and processes error conditions.
 * - Sets up the instance to complete a SPI read operation.
 *
 * @retval  FSP_SUCCESS                   Read operation successfully completed.
 * @retval  FSP_ERR_ASSERTION             NULL pointer to control or destination parameters or transfer length is zero.
 * @retval  FSP_ERR_NOT_OPEN              The channel has not been opened. Open channel first.
 * @retval  FSP_ERR_IN_USE                A transfer is already in progress.
 **********************************************************************************************************************/
fsp_err_t R_SPI_Read (spi_ctrl_t * const    p_api_ctrl,
                      void                * p_dest,
                      uint32_t const        length,
                      spi_bit_width_t const bit_width)
{
    return r_spi_write_read_common(p_api_ctrl, NULL, p_dest, length, bit_width);
}

/*******************************************************************************************************************//**
 * This function transmits data to a SPI device using the TX Only Communications Operation Mode.
 * Implements @ref spi_api_t::write.
 *
 * The function performs the following tasks:
 * - Performs parameter checking and processes error conditions.
 * - Sets up the instance to complete a SPI write operation.
 *
 * @retval  FSP_SUCCESS                     Write operation successfully completed.
 * @retval  FSP_ERR_ASSERTION               NULL pointer to control or source parameters or transfer length is zero.
 * @retval  FSP_ERR_NOT_OPEN                The channel has not been opened. Open the channel first.
 * @retval  FSP_ERR_IN_USE                  A transfer is already in progress.
 **********************************************************************************************************************/
fsp_err_t R_SPI_Write (spi_ctrl_t * const    p_api_ctrl,
                       void const          * p_src,
                       uint32_t const        length,
                       spi_bit_width_t const bit_width)
{
    return r_spi_write_read_common(p_api_ctrl, p_src, NULL, length, bit_width);
}

/*******************************************************************************************************************//**
 * This function simultaneously transmits and receive data. Implements @ref spi_api_t::writeRead.
 *
 * The function performs the following tasks:
 * - Performs parameter checking and processes error conditions.
 * - Sets up the instance to complete a SPI writeRead operation.
 *
 * @retval  FSP_SUCCESS                   Write operation successfully completed.
 * @retval  FSP_ERR_ASSERTION             NULL pointer to control, source or destination parameters or
 *                                        transfer length is zero.
 * @retval  FSP_ERR_NOT_OPEN              The channel has not been opened. Open the channel first.
 * @retval  FSP_ERR_IN_USE                A transfer is already in progress.
 *********************************************************************************************************************/
fsp_err_t R_SPI_WriteRead (spi_ctrl_t * const    p_api_ctrl,
                           void const          * p_src,
                           void                * p_dest,
                           uint32_t const        length,
                           spi_bit_width_t const bit_width)
{
#if SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_src != NULL);
    FSP_ASSERT(p_dest != NULL);
#endif

    return r_spi_write_read_common(p_api_ctrl, p_src, p_dest, length, bit_width);
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements spi_api_t::callbackSet
 *
 * @retval  FSP_ERR_UNSUPPORTED              API not supported.
 **********************************************************************************************************************/
fsp_err_t R_SPI_CallbackSet (spi_ctrl_t * const          p_api_ctrl,
                             void (                    * p_callback)(spi_callback_args_t *),
                             void const * const          p_context,
                             spi_callback_args_t * const p_callback_memory)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_callback);
    FSP_PARAMETER_NOT_USED(p_context);
    FSP_PARAMETER_NOT_USED(p_callback_memory);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * This function manages the closing of a channel by the following task. Implements @ref spi_api_t::close.
 *
 * Disables SPI operations by disabling the SPI bus.
 * - Disables the SPI peripheral.
 * - Disables all the associated interrupts.
 * - Update control structure so it will not work with @ref SPI_API functions.
 *
 * @retval  FSP_SUCCESS              Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION        A required pointer argument is NULL.
 * @retval  FSP_ERR_NOT_OPEN         The channel has not been opened. Open the channel first.
 **********************************************************************************************************************/
fsp_err_t R_SPI_Close (spi_ctrl_t * const p_api_ctrl)
{
    spi_instance_ctrl_t * p_ctrl = (spi_instance_ctrl_t *) p_api_ctrl;

#if SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SPI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if SPI_DMAC_SUPPORT_ENABLE == 1
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        p_ctrl->p_cfg->p_transfer_rx->p_api->close(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
    }

    if (NULL != p_ctrl->p_cfg->p_transfer_tx)
    {
        p_ctrl->p_cfg->p_transfer_tx->p_api->close(p_ctrl->p_cfg->p_transfer_tx->p_ctrl);
    }
#endif

    /* Disable interrupts in GIC. */
    R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->tei_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->eri_irq);

    /* Disable the SPI Transfer. */
    p_ctrl->p_regs->SPCR_b.SPE = 0U;

    /* Clear the status register. */
    p_ctrl->p_regs->SPSRC = (R_SPI0_SPSRC_SPDRFC_Msk) | (R_SPI0_SPSRC_OVRFC_Msk) | (R_SPI0_SPSRC_MODFC_Msk) |
                            (R_SPI0_SPSRC_PERFC_Msk) | (R_SPI0_SPSRC_UDRFC_Msk);

    /* Remove power to the channel. */
    /* Disable the clock to the SPI channel. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_STOP(FSP_IP_SPI, p_ctrl->p_cfg->channel);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    p_ctrl->open = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function gets the version information of the underlying driver. Implements @ref spi_api_t::versionGet.
 *
 * @retval      FSP_SUCCESS            Successful version get.
 * @retval      FSP_ERR_ASSERTION      The parameter p_version is NULL.
 **********************************************************************************************************************/
fsp_err_t R_SPI_VersionGet (fsp_version_t * p_version)
{
#if SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_version != NULL);
#endif

    p_version->version_id = module_version.version_id;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Calculates the SPBR register value and the BRDV bits for a desired bitrate.
 * If the desired bitrate is faster than the maximum bitrate, than the bitrate is set to the
 * maximum bitrate. If the desired bitrate is slower than the minimum bitrate, than an error is returned.
 *
 * @param[in] bitrate             Desired bitrate
 * @param[out] spck_div           Memory location to store bitrate register settings.
 *
 * @retval FSP_SUCCESS            Valid spbr and brdv values were calculated
 * @retval FSP_ERR_UNSUPPORTED    Bitrate is not achievable
 **********************************************************************************************************************/
fsp_err_t R_SPI_CalculateBitrate (uint32_t bitrate, rspck_div_setting_t * spck_div)
{
    /* desired_divider = Smallest integer greater than or equal to SPI_CLK / bitrate. */
    uint32_t desired_divider = (SPI_CLOCK_96MHZ + bitrate - 1) / bitrate;

    /* Can't achieve bitrate slower than desired. */
    if (desired_divider > SPI_CLK_MAX_DIV)
    {
        return FSP_ERR_UNSUPPORTED;
    }

    if (desired_divider < SPI_CLK_MIN_DIV)
    {
        /* Configure max bitrate (SPI_CLK / 2) */
        spck_div->brdv = 0;
        spck_div->spbr = 0;

        return FSP_SUCCESS;
    }

    /*
     * Possible SPI_CLK dividers for values of N:
     *   N = 0; div = [2,4,6,..,512]
     *   N = 1; div = [4,8,12,..,1024]
     *   N = 2; div = [8,16,32,..,2048]
     *   N = 3; div = [16,32,64,..,4096]
     */
    uint8_t i;
    for (i = 0; i < 4; i++)
    {
        /* Select smallest value for N possible. */

        /* div <= 512; N = 0
         * 512 < div <= 1024; N=1
         * ...
         */
        if (desired_divider <= (SPI_CLK_N_DIV_MULTIPLIER << i))
        {
            break;
        }
    }

    spck_div->brdv = i & 0x03U;

    /*
     * desired_divider = 2 * (spbr + 1) * 2^i.
     *
     * With desired_divider and i known, solve for spbr.
     *
     * spbr = SPI_CLK_DIV / (2 * 2^i) - 1
     */
    uint32_t spbr_divisor = (2U * (1U << i));

    /* spbr = (Smallest integer greater than or equal to SPI_CLK_DIV / (2 * 2^i)) - 1. */
    spck_div->spbr = (uint8_t) (((desired_divider + spbr_divisor - 1U) / spbr_divisor) - 1U) & UINT8_MAX;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SPI)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configure the given transfer instances for receiving and transmitting data without CPU intervention.
 *
 * @param      p_cfg           Configuration structure with references to receive and transmit transfer instances.
 *
 * @retval     FSP_SUCCESS     The given transfer instances were configured successfully.
 * @return                     See @ref RENESAS_ERROR_CODES for other possible return codes. This function internally
 *                             calls @ref transfer_api_t::open.
 **********************************************************************************************************************/
static fsp_err_t r_spi_transfer_config (spi_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

#if SPI_DMAC_SUPPORT_ENABLE == 1
    const transfer_instance_t * p_transfer_tx = p_cfg->p_transfer_tx;
    void * p_spdr = (void *) &(SPI_REG(p_cfg->channel)->SPDR);
    if (p_transfer_tx)
    {
        p_transfer_tx->p_cfg->p_info->transfer_settings_word = SPI_DMAC_TX_TRANSFER_SETTINGS;
        p_transfer_tx->p_cfg->p_info->p_dest                 = p_spdr;

        err = p_transfer_tx->p_api->open(p_transfer_tx->p_ctrl, p_transfer_tx->p_cfg);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    const transfer_instance_t * p_transfer_rx = p_cfg->p_transfer_rx;
    if (p_transfer_rx)
    {
        p_transfer_rx->p_cfg->p_info->transfer_settings_word = SPI_DMAC_RX_TRANSFER_SETTINGS;
        p_transfer_rx->p_cfg->p_info->p_src = p_spdr;

        err = p_transfer_rx->p_api->open(p_transfer_rx->p_ctrl, p_transfer_rx->p_cfg);

        if ((FSP_SUCCESS != err) && p_transfer_tx)
        {
            p_transfer_tx->p_api->close(p_transfer_tx->p_ctrl);
        }
    }

#else
    FSP_PARAMETER_NOT_USED(p_cfg);
#endif

    return err;
}

/*******************************************************************************************************************//**
 * Hardware configuration for settings given by the configuration structure.
 *
 * @param[in]  p_ctrl          pointer to control structure.
 **********************************************************************************************************************/
static void r_spi_hw_config (spi_instance_ctrl_t * p_ctrl)
{
    uint32_t spcr   = 0;
    uint32_t sslp   = 0;
    uint32_t sppcr  = 0;
    uint32_t spcr2  = 0;
    uint32_t spckd  = 0;
    uint32_t sslnd  = 0;
    uint32_t spnd   = 0;
    uint32_t spcmd  = 0;
    uint32_t spdcr  = 0;
    uint32_t spdcr2 = 0;
    uint32_t mrckd  = 0;
    uint32_t spdrcr = 0;

    spi_extended_cfg_t * p_extend = ((spi_extended_cfg_t *) p_ctrl->p_cfg->p_extend);

    /* Enable Receive Buffer Full interrupt. */
    spcr |= R_SPI0_SPCR_SPRIE_Msk;

    /* The TXI interrupt is not needed when TRANSMIT_FROM_RXI_ISR optimization is enabled. */
#if SPI_TRANSMIT_FROM_RXI_ISR == 0

    /* Enable Transmit Buffer Empty interrupt. */
    spcr |= R_SPI0_SPCR_SPTIE_Msk;
#endif

    /* Enable Error interrupt. */
    spcr |= R_SPI0_SPCR_SPEIE_Msk;

    /* Enable Transmit end interrupt */
    spcr |= R_SPI0_SPCR_CENDIE_Msk;

    /* Configure Master Mode setting. */
    spcr |= (uint32_t) (SPI_MODE_MASTER == p_ctrl->p_cfg->operating_mode) << R_SPI0_SPCR_MSTR_Pos;

    /* Enable SCK Auto Stop setting in order to prevent RX Overflow in Master Mode */
    spcr |= (uint32_t) (SPI_MODE_MASTER == p_ctrl->p_cfg->operating_mode) << R_SPI0_SPCR_SCKASE_Pos;

    /* Configure Synchronization Circuit Bypass. */
    spcr |= (uint32_t) p_extend->sync_bypass << R_SPI0_SPCR_BPEN_Pos;

    /* Configure CPHA setting. */
    spcmd |= (uint32_t) p_ctrl->p_cfg->clk_phase << R_SPI0_SPCMD_CPHA_Pos;

    /* Configure CPOL setting. */
    spcmd |= (uint32_t) p_ctrl->p_cfg->clk_polarity << R_SPI0_SPCMD_CPOL_Pos;

    /* Configure Bit Order (MSB,LSB) */
    spcmd |= (uint32_t) p_ctrl->p_cfg->bit_order << R_SPI0_SPCMD_LSBF_Pos;

    if (p_ctrl->p_cfg->p_transfer_tx)
    {
        /* Transmit Buffer Empty IRQ must be enabled for DMAC even if TRANSMIT_FROM_RXI is enabled. */
        spcr |= R_SPI0_SPCR_SPTIE_Msk;
    }

    if (SPI_SSL_MODE_SPI == p_extend->spi_clksyn)
    {
#if BSP_FEATURE_SPI_HAS_SSL_LEVEL_KEEP == 1

        /* Configure SSL Level Keep Setting. */
        spcmd |= R_SPI0_SPCMD_SSLKP_Msk;
#endif

        /* Configure 4-Wire Mode Setting. */
        spcr &= ~R_SPI0_SPCR_SPMS_Msk;
    }
    else
    {
        /* Configure 3-Wire Mode Setting. */
        spcr |= R_SPI0_SPCR_SPMS_Msk;
    }

    /* Configure Full Duplex or TX Only Setting. */
    spcr &= (uint32_t) ~(p_extend->spi_comm << R_SPI0_SPCR_SPRIE_Pos),
    spcr |=
        (uint32_t) ((p_extend->spi_comm << R_SPI0_SPCR_TXMD_Pos) |
                    (p_extend->spi_comm << R_SPI0_SPCR_SPTIE_Pos));

    /* Configure SSLn polarity setting. */
    sslp &= ~0x0FU;
    sslp |= (uint32_t) p_extend->ssl_polarity << p_extend->ssl_select;

    /* Configure SSLn setting. (SSL0, SSL1, SSL2, SSL3)*/
    spcmd &= ~R_SPI0_SPCMD_SSLA_Msk;
    spcmd |= (uint32_t) p_extend->ssl_select << R_SPI0_SPCMD_SSLA_Pos;

    if (SPI_MOSI_IDLE_VALUE_FIXING_DISABLE != p_extend->mosi_idle)
    {
        /* Enable mosi value fixing */
        sppcr |= R_SPI0_SPPCR_MOIFE_Msk;

        if (SPI_MOSI_IDLE_VALUE_FIXING_HIGH == p_extend->mosi_idle)
        {
            sppcr |= R_SPI0_SPPCR_MOIFV_Msk;
        }
    }

    if (SPI_PARITY_MODE_DISABLE != p_extend->parity)
    {
        /* Enable Parity Mode. */
        spcr |= R_SPI0_SPCR_SPPE_Msk;

        if (SPI_PARITY_MODE_ODD == p_extend->parity)
        {
            /* Configure ODD Parity Setting. */
            spcr |= R_SPI0_SPCR_SPOE_Msk;
        }
    }

    /* Configure byte swapping for 16/32-Bit mode. */
    spdcr |= p_extend->byte_swap;

    /* Configure the Bit Rate Division Setting */
    spcmd |= (uint32_t) p_extend->spck_div.brdv << R_SPI0_SPCMD_BRDV_Pos;

    /* Enable all delay settings. */
    if (SPI_MODE_MASTER == p_ctrl->p_cfg->operating_mode)
    {
        /* Note that disabling delay settings is same as setting delay to 1. */
        spcmd |= (uint32_t) R_SPI0_SPCMD_SPNDEN_Msk | R_SPI0_SPCMD_SLNDEN_Msk | R_SPI0_SPCMD_SCKDEN_Msk;

        spckd = p_extend->spck_delay;
        sslnd = p_extend->ssl_negation_delay;
        spnd  = p_extend->next_access_delay;
    }

    /* Sets the receive FIFO threshold and the transmit FIFO threshold */
    spdcr2 =
        (uint32_t) ((p_extend->transmit_fifo_threshold <<
                     R_SPI0_SPDCR2_TTRG_Pos) | (p_extend->receive_fifo_threshold << R_SPI0_SPDCR2_RTRG_Pos));

    /* Sets the received data ready detection timing */
    spdrcr = p_extend->receive_data_ready_detect_adjustment;

    /* Power up the SPI module. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_START(FSP_IP_SPI, p_ctrl->p_cfg->channel);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    /* Write registers */
    p_ctrl->p_regs->SPCR     = spcr;
    p_ctrl->p_regs->SSLP     = (uint8_t) sslp;
    p_ctrl->p_regs->SPPCR    = (uint8_t) sppcr;
    p_ctrl->p_regs->SPBR     = p_extend->spck_div.spbr;
    p_ctrl->p_regs->SPCKD    = (uint8_t) spckd;
    p_ctrl->p_regs->SSLND    = (uint8_t) sslnd;
    p_ctrl->p_regs->SPND     = (uint8_t) spnd;
    p_ctrl->p_regs->SPCR2    = (uint8_t) spcr2;
    p_ctrl->p_regs->SPCMD[0] = spcmd;
    p_ctrl->p_regs->SPDCR    = (uint16_t) spdcr;
    p_ctrl->p_regs->SPDCR2   = (uint16_t) spdcr2;
    p_ctrl->p_regs->MRCKD    = (uint8_t) mrckd;
    p_ctrl->p_regs->SPDRCR   = (uint8_t) spdrcr;

#if BSP_FEATURE_SPI_HAS_SPCR3 == 1
    p_ctrl->p_regs->SPCR3 = R_SPI0_SPCR3_CENDIE_Msk;
#endif
}

/*******************************************************************************************************************//**
 * Enable Receive Buffer Full, Transmit Buffer Empty, and Error Interrupts in the GIC.
 *
 * @param[in]  p_ctrl          pointer to control structure.
 **********************************************************************************************************************/
static void r_spi_gic_config (spi_instance_ctrl_t * p_ctrl)
{
    R_BSP_IrqCfgEnable(p_ctrl->p_cfg->txi_irq, p_ctrl->p_cfg->txi_ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_ctrl->p_cfg->rxi_irq, p_ctrl->p_cfg->rxi_ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_ctrl->p_cfg->eri_irq, p_ctrl->p_cfg->eri_ipl, p_ctrl);

    R_BSP_IrqCfg(p_ctrl->p_cfg->tei_irq, p_ctrl->p_cfg->tei_ipl, p_ctrl);

    /* Note tei_irq is not enabled until the last data frame is transfered. */
}

/*******************************************************************************************************************//**
 * Setup the bit width configuration for a transfer.
 *
 * @param[in]  p_ctrl          pointer to control structure.
 *
 * Note: For 8-Bit wide data frames, the devices require the SPBYT bit to enable byte level access to the
 * data register. Although this register is not documented in some MCU hardware manuals, it does seem to be available
 * on all of them.
 **********************************************************************************************************************/
static void r_spi_bit_width_config (spi_instance_ctrl_t * p_ctrl)
{
    uint32_t spcmd = p_ctrl->p_regs->SPCMD[0];

    if (SPI_BIT_WIDTH_8_BITS == p_ctrl->bit_width)
    {
        /* Configure 8-Bit Mode.  */
        spcmd &= ~R_SPI0_SPCMD_SPB_Msk;
        spcmd |= SPI_SPCMD_BIT_LENGTH_8 << R_SPI0_SPCMD_SPB_Pos;
    }
    else if (SPI_BIT_WIDTH_16_BITS == p_ctrl->bit_width)
    {
        /* Configure 16-Bit Mode. */
        spcmd &= ~R_SPI0_SPCMD_SPB_Msk;
        spcmd |= SPI_SPCMD_BIT_LENGTH_16 << R_SPI0_SPCMD_SPB_Pos;
    }
    else                               /* SPI_BIT_WIDTH_32_BITS */
    {
        /* Configure 32-Bit Mode. */
        spcmd &= ~R_SPI0_SPCMD_SPB_Msk;
        spcmd |= SPI_SPCMD_BIT_LENGTH_32 << R_SPI0_SPCMD_SPB_Pos;
    }

    p_ctrl->p_regs->SPCMD[0] = spcmd;
}

/*******************************************************************************************************************//**
 * Initiates a SPI transfer by setting the SPE bit in SPCR.
 *
 * @param[in]  p_ctrl          pointer to control structure.
 *
 * Note: When not using the DMAC to transmit, this function pre-loads the SPI shift-register and shift-register-buffer
 * instead of waiting for the transmit buffer empty interrupt. This is required when transmitting from the
 * Receive Buffer Full interrupt, but it does not interfere with transmitting when using the transmit buffer empty
 * interrupt.
 **********************************************************************************************************************/
static void r_spi_start_transfer (spi_instance_ctrl_t * p_ctrl)
{
#if SPI_TRANSMIT_FROM_RXI_ISR == 1
    if (!p_ctrl->p_cfg->p_transfer_tx)
    {
        /* Handle the first two transmit empty events here because transmit interrupt may not be enabled. */

        /* Critical section required so that the txi interrupt can be handled here instead of in the ISR. */
        FSP_CRITICAL_SECTION_DEFINE;
        FSP_CRITICAL_SECTION_ENTER;

        /* Clear the status register. */
        p_ctrl->p_regs->SPSRC = (R_SPI0_SPSRC_SPDRFC_Msk) | (R_SPI0_SPSRC_OVRFC_Msk) | (R_SPI0_SPSRC_MODFC_Msk) |
                                (R_SPI0_SPSRC_PERFC_Msk) | (R_SPI0_SPSRC_UDRFC_Msk);

        /* Clear the FIFO status */
        p_ctrl->p_regs->SPFCR = R_SPI0_SPFCR_SPFRST_Msk;

        /* Disable the transmit end interrupt */
        p_ctrl->p_regs->SPCR_b.CENDIE = 0;

        /* Enable the SPI Transfer. */
        p_ctrl->p_regs->SPCR_b.SPE = 1;

        /* Must call transmit to kick off transfer when transmitting from rxi ISR. */
        r_spi_transmit(p_ctrl);        ///< First data immediately copied into the SPI shift register.

        /* Second transmit significantly improves slave mode performance. */
        r_spi_transmit(p_ctrl);        ///< Second data copied into the SPI transmit buffer.

        /* Must clear the txi IRQ status (The interrupt was handled here). */
        R_BSP_IrqEnable(p_ctrl->p_cfg->txi_irq);

        FSP_CRITICAL_SECTION_EXIT;
    }
    else
    {
        /* Clear the status register. */
        p_ctrl->p_regs->SPSRC = (R_SPI0_SPSRC_SPDRFC_Msk) | (R_SPI0_SPSRC_OVRFC_Msk) | (R_SPI0_SPSRC_MODFC_Msk) |
                                (R_SPI0_SPSRC_PERFC_Msk) | (R_SPI0_SPSRC_UDRFC_Msk);

        /* Clear the FIFO status */
        p_ctrl->p_regs->SPFCR = R_SPI0_SPFCR_SPFRST_Msk;

        /* Disable the transmit end interrupt */
        p_ctrl->p_regs->SPCR_b.CENDIE = 0;

        /* Enable the SPI Transfer. */
        p_ctrl->p_regs->SPCR_b.SPE = 1;
    }

#else

    /* Clear the status register. */
    p_ctrl->p_regs->SPSRC = (R_SPI0_SPSRC_SPDRFC_Msk) | (R_SPI0_SPSRC_OVRFC_Msk) | (R_SPI0_SPSRC_MODFC_Msk) |
                            (R_SPI0_SPSRC_PERFC_Msk) | (R_SPI0_SPSRC_UDRFC_Msk);

    /* Clear the FIFO status */
    p_ctrl->p_regs->SPFCR = R_SPI0_SPFCR_SPFRST_Msk;

    /* Disable the transmit end interrupt */
    p_ctrl->p_regs->SPCR_b.CENDIE = 0;

    /* Enable the SPI Transfer. */
    p_ctrl->p_regs->SPCR_b.SPE = 1;
#endif
}

/*******************************************************************************************************************//**
 * Configures the driver state and initiates a SPI transfer for all modes of operation.
 *
 * @param[in]  p_api_ctrl        pointer to control structure.
 * @param      p_src             Buffer to transmit data from.
 * @param      p_dest            Buffer to store received data in.
 * @param[in]  length            Number of transfers
 * @param[in]  bit_width         Data frame size (8-Bit, 16-Bit, 32-Bit)
 *
 * @retval     FSP_SUCCESS       Transfer was started successfully.
 * @retval     FSP_ERR_ASSERTION An argument is invalid.
 * @retval     FSP_ERR_NOT_OPEN  The instance has not been initialized.
 * @retval     FSP_ERR_IN_USE    A transfer is already in progress.
 * @return                       See @ref RENESAS_ERROR_CODES for other possible return codes. This function internally
 *                               calls @ref transfer_api_t::reconfigure.
 **********************************************************************************************************************/
static fsp_err_t r_spi_write_read_common (spi_ctrl_t * const    p_api_ctrl,
                                          void const          * p_src,
                                          void                * p_dest,
                                          uint32_t const        length,
                                          spi_bit_width_t const bit_width)
{
    spi_instance_ctrl_t * p_ctrl = (spi_instance_ctrl_t *) p_api_ctrl;

#if SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SPI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(p_src || p_dest);
    FSP_ASSERT(0 != length);
#endif

    FSP_ERROR_RETURN(0 == (p_ctrl->p_regs->SPCR & R_SPI0_SPCR_SPE_Msk), FSP_ERR_IN_USE);

    p_ctrl->p_tx_data = p_src;
    p_ctrl->p_rx_data = p_dest;
    p_ctrl->tx_count  = 0;
    p_ctrl->rx_count  = 0;
    p_ctrl->count     = length;
    p_ctrl->bit_width = bit_width;

#if SPI_DMAC_SUPPORT_ENABLE == 1
    if (p_ctrl->p_cfg->p_transfer_rx)
    {
        /* When the rxi interrupt is called, all transfers will be finished. */
        p_ctrl->rx_count = length;

        /* Configure the receive DMA instance. */
        dmac_extended_info_t * p_extend_rx =
            (dmac_extended_info_t *) p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->p_extend;
        if (SPI_BIT_WIDTH_32_BITS == p_ctrl->bit_width)
        {
            p_extend_rx->src_size  = DMAC_TRANSFER_SIZE_4_BYTE;
            p_extend_rx->dest_size = DMAC_TRANSFER_SIZE_4_BYTE;
        }
        else if (SPI_BIT_WIDTH_16_BITS == p_ctrl->bit_width)
        {
            p_extend_rx->src_size  = DMAC_TRANSFER_SIZE_2_BYTE;
            p_extend_rx->dest_size = DMAC_TRANSFER_SIZE_2_BYTE;
        }
        else
        {
            p_extend_rx->src_size  = DMAC_TRANSFER_SIZE_1_BYTE;
            p_extend_rx->dest_size = DMAC_TRANSFER_SIZE_1_BYTE;
        }

        p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
        p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->length         = length * bit_width;
        p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->p_dest         = p_dest;

        if (NULL == p_dest)
        {
            static uint32_t dummy_rx;
            p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->dest_addr_mode = TRANSFER_ADDR_MODE_FIXED;
            p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->p_dest         = &dummy_rx;
        }

        /* Disable the corresponding IRQ when transferring using DMAC. */
        R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);

        fsp_err_t err = p_ctrl->p_cfg->p_transfer_rx->p_api->reconfigure(p_ctrl->p_cfg->p_transfer_rx->p_ctrl,
                                                                         p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (p_ctrl->p_cfg->p_transfer_tx)
    {
        /* When the txi interrupt is called, all transfers will be finished. */
        p_ctrl->tx_count = length;

        /* Configure the transmit DMA instance. */
        dmac_extended_info_t * p_extend_tx =
            (dmac_extended_info_t *) p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->p_extend;
        if (SPI_BIT_WIDTH_32_BITS == p_ctrl->bit_width)
        {
            p_extend_tx->src_size  = DMAC_TRANSFER_SIZE_4_BYTE;
            p_extend_tx->dest_size = DMAC_TRANSFER_SIZE_4_BYTE;
        }
        else if (SPI_BIT_WIDTH_16_BITS == p_ctrl->bit_width)
        {
            p_extend_tx->src_size  = DMAC_TRANSFER_SIZE_2_BYTE;
            p_extend_tx->dest_size = DMAC_TRANSFER_SIZE_2_BYTE;
        }
        else
        {
            p_extend_tx->src_size  = DMAC_TRANSFER_SIZE_1_BYTE;
            p_extend_tx->dest_size = DMAC_TRANSFER_SIZE_1_BYTE;
        }

        p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
        p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->length        = length * bit_width;
        p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->p_src         = p_src;

        if (NULL == p_src)
        {
            static uint32_t dummy_tx = 0;
            p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->src_addr_mode = TRANSFER_ADDR_MODE_FIXED;
            p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->p_src         = &dummy_tx;
        }

        /* Disable the corresponding IRQ when transferring using DMAC. */
        R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);

        fsp_err_t err = p_ctrl->p_cfg->p_transfer_tx->p_api->reconfigure(p_ctrl->p_cfg->p_transfer_tx->p_ctrl,
                                                                         p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

    r_spi_bit_width_config(p_ctrl);
    r_spi_start_transfer(p_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Copy configured bit width from the SPI data register to the current rx data location.
 * If the receive buffer is NULL, just read the SPI data register.
 * If the total transfer length has already been received than do nothing.
 *
 * @param[in]  p_ctrl          pointer to control structure.
 **********************************************************************************************************************/
static void r_spi_receive (spi_instance_ctrl_t * p_ctrl)
{
    uint32_t rx_count = p_ctrl->rx_count;
    if (rx_count == p_ctrl->count)
    {
        return;
    }

    while (p_ctrl->p_regs->SPRFSR != 0 && rx_count != p_ctrl->count)
    {
        if (0 == p_ctrl->p_rx_data)
        {
            /* Read the received data but do nothing with it. */
            p_ctrl->p_regs->SPDR;
        }
        else
        {
            if (SPI_BIT_WIDTH_8_BITS == p_ctrl->bit_width)
            {
                ((uint8_t *) (p_ctrl->p_rx_data))[rx_count] = p_ctrl->p_regs->SPDR & SPI_SPDR_BYTE_VALUE_MASK;
            }
            else if (SPI_BIT_WIDTH_16_BITS == p_ctrl->bit_width)
            {
                ((uint16_t *) (p_ctrl->p_rx_data))[rx_count] = p_ctrl->p_regs->SPDR & SPI_SPDR_HALFWARD_VALUE_MASK;
            }
            else                       /* SPI_BIT_WIDTH_32_BITS */
            {
                ((uint32_t *) (p_ctrl->p_rx_data))[rx_count] = p_ctrl->p_regs->SPDR;
            }
        }

        rx_count++;
        p_ctrl->rx_count = rx_count;
    }
}

/*******************************************************************************************************************//**
 * Copy configured bit width from the current tx data location into the SPI data register.
 * If the transmit buffer is NULL, than write zero to the SPI data register.
 * If the total transfer length has already been transmitted than do nothing.
 *
 * @param[in]  p_ctrl          pointer to control structure.
 **********************************************************************************************************************/
static void r_spi_transmit (spi_instance_ctrl_t * p_ctrl)
{
    uint32_t             tx_count = p_ctrl->tx_count;
    spi_extended_cfg_t * p_extend = ((spi_extended_cfg_t *) p_ctrl->p_cfg->p_extend);
    if (tx_count == p_ctrl->count)
    {
        return;
    }

    while (p_ctrl->p_regs->SPTFSR != 0 && tx_count < p_ctrl->count)
    {
        if (p_extend && (SPI_COMMUNICATION_TRANSMIT_ONLY == p_extend->spi_comm) && (tx_count == p_ctrl->count - 1) &&
            (0 == p_ctrl->p_regs->SPCR_b.CENDIE))
        {
            return;
        }

        if (0 == p_ctrl->p_tx_data)
        {
            /* Transmit zero if no tx buffer present. */
            p_ctrl->p_regs->SPDR = 0;
        }
        else
        {
            if (SPI_BIT_WIDTH_8_BITS == p_ctrl->bit_width)
            {
                p_ctrl->p_regs->SPDR = ((uint8_t *) p_ctrl->p_tx_data)[tx_count];;
            }
            else if (SPI_BIT_WIDTH_16_BITS == p_ctrl->bit_width)
            {
                p_ctrl->p_regs->SPDR = ((uint16_t *) p_ctrl->p_tx_data)[tx_count];;
            }
            else                       /* SPI_BIT_WIDTH_32_BITS */
            {
                p_ctrl->p_regs->SPDR = ((uint32_t *) p_ctrl->p_tx_data)[tx_count];;
            }
        }

        tx_count++;
        p_ctrl->tx_count = tx_count;
    }
}

/*******************************************************************************************************************//**
 * Common processing for RXI interrupt and DMA transfer completion interrupt in SPI read operation.
 **********************************************************************************************************************/
static void spi_rxi_common (spi_instance_ctrl_t * p_ctrl)
{
    r_spi_receive(p_ctrl);

#if SPI_TRANSMIT_FROM_RXI_ISR == 1

    /* It is a little faster to handle the transmit buffer empty event in the receive buffer full ISR.
     * Note that this is only possible when the instance is not using a transfer instance to receive data. */
    r_spi_transmit(p_ctrl);
#endif

    if (p_ctrl->rx_count == p_ctrl->count)
    {
        /* If the transmit and receive ISRs are too slow to keep up at high bitrates,
         * the hardware will generate an interrupt before all of the transfers are completed.
         * By enabling the transfer end ISR here, all of the transfers are guaranteed to be completed. */
        R_BSP_IrqEnableNoClear(p_ctrl->p_cfg->tei_irq);

        /* Enable Transmit end interrupt */
        p_ctrl->p_regs->SPCR_b.CENDIE = 1;
    }

    /* Clear the SPI Receive Data Ready Flag */
    if (1 == p_ctrl->p_regs->SPSR_b.SPDRF)
    {
        p_ctrl->p_regs->SPSRC_b.SPDRFC = 1;
    }

    /* Clear the receive buffer full flag */
    p_ctrl->p_regs->SPSRC = R_SPI0_SPSRC_SPRFC_Msk;
}

/*******************************************************************************************************************//**
 * ISR called when data is loaded into SPI data register from the shift register. This function calls spi_rxi_common().
 **********************************************************************************************************************/
void spi_rxi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    spi_instance_ctrl_t * p_ctrl = (spi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    spi_rxi_common(p_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

#if SPI_DMAC_SUPPORT_ENABLE == 1

/*******************************************************************************************************************//**
 * Processing called when the DMA transfer is completed for SPI read operation. This function calls spi_rxi_common().
 **********************************************************************************************************************/
void spi_rxi_dmac_isr (IRQn_Type irq)
{
    spi_instance_ctrl_t * p_ctrl = (spi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Now that the transfer using DMAC is finished, enable the corresponding IRQ. */
    R_BSP_IrqEnable(p_ctrl->p_cfg->rxi_irq);

    spi_rxi_common(p_ctrl);
}

#endif

#if SPI_TRANSMIT_FROM_RXI_ISR == 0

/*******************************************************************************************************************//**
 * Common processing for TXI interrupt and DMA transfer completion interrupt in SPI write operation.
 **********************************************************************************************************************/
static void spi_txi_common (spi_instance_ctrl_t * p_ctrl)
{
    spi_extended_cfg_t * p_extend = ((spi_extended_cfg_t *) p_ctrl->p_cfg->p_extend);
    if (p_extend && (SPI_COMMUNICATION_TRANSMIT_ONLY == p_extend->spi_comm))
    {
        /* Only enable the transfer end ISR if there are no receive buffer full interrupts expected to be handled
         * after this interrupt. */
        if (p_ctrl->tx_count == p_ctrl->count - 1)
        {
            /* If the transmit and receive ISRs are too slow to keep up at high bitrates,
             * the hardware will generate an interrupt before all of the transfers are completed.
             * By enabling the transfer end ISR here, all of the transfers are guaranteed to be completed. */
            R_BSP_IrqEnable(p_ctrl->p_cfg->tei_irq);

            /* Enable Transmit end interrupt */
            p_ctrl->p_regs->SPCR_b.CENDIE = 1;
        }
        else if (p_ctrl->p_cfg->p_transfer_tx)
        {
            /* If DMA is used to transmit data, enable the interrupt after all the data has been transfered, but do not
             * clear the IRQ Pending Bit. */
            R_BSP_IrqEnableNoClear(p_ctrl->p_cfg->tei_irq);

            /* Enable Transmit end interrupt */
            p_ctrl->p_regs->SPCR_b.CENDIE = 1;
        }
        else
        {
        }
    }

    /* Transmit happens after checking if the last transfer has been written to the transmit buffer in order
     * to ensure that the end interrupt is not enabled while there is data still in the transmit buffer. */
    r_spi_transmit(p_ctrl);

    /* Clear transmit buffer empty flag */
    if (p_ctrl->tx_count != p_ctrl->count)
    {
        p_ctrl->p_regs->SPSRC = R_SPI0_SPSRC_SPTEFC_Msk;
    }
}

#endif

/*******************************************************************************************************************//**
 * ISR called when data is copied from the SPI data register into the SPI shift register. This function calls
 * spi_txi_common().
 **********************************************************************************************************************/
void spi_txi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

#if SPI_TRANSMIT_FROM_RXI_ISR == 0
    spi_instance_ctrl_t * p_ctrl = (spi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    spi_txi_common(p_ctrl);
#else
    FSP_PARAMETER_NOT_USED(irq);
#endif

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

#if SPI_DMAC_SUPPORT_ENABLE == 1

/*******************************************************************************************************************//**
 * Processing called when the DMA transfer is completed for SPI write operation. This function calls spi_txi_common().
 **********************************************************************************************************************/
void spi_txi_dmac_isr (IRQn_Type irq)
{
 #if SPI_TRANSMIT_FROM_RXI_ISR == 0
    spi_instance_ctrl_t * p_ctrl = (spi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Now that the transfer using DMAC is finished, enable the corresponding IRQ. */
    R_BSP_IrqEnable(p_ctrl->p_cfg->txi_irq);

    spi_txi_common(p_ctrl);
 #else
    FSP_PARAMETER_NOT_USED(irq);
 #endif
}

#endif

/*******************************************************************************************************************//**
 * ISR called when the SPI peripheral transitions from the transferring state to the IDLE state.
 **********************************************************************************************************************/
void spi_tei_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    spi_instance_ctrl_t * p_ctrl = (spi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Since the FIFO threshold is set to 0, there is no need to perform final data read. */

    if ((0 == p_ctrl->p_regs->SPSR_b.IDLNF) || (SPI_MODE_SLAVE == p_ctrl->p_cfg->operating_mode))
    {
        R_BSP_IrqDisable(irq);

        /* Disable the SPI Transfer. */
        p_ctrl->p_regs->SPCR_b.SPE = 0;

        /* Disable the transmit end interrupt */
        p_ctrl->p_regs->SPCR_b.CENDIE = 0;

        /* Check SPCR.SPE = 0 */
        uint32_t timeout_count = SPI_PERIPHERAL_REG_MAX_WAIT;

        SPI_HARDWARE_REGISTER_WAIT(p_ctrl->p_regs->SPPSR_b.SPEPS, 0, timeout_count);

        /* Setup callback args. */
        spi_callback_args_t spi_cb_data;
        spi_cb_data.channel   = p_ctrl->p_cfg->channel;
        spi_cb_data.event     = SPI_EVENT_TRANSFER_COMPLETE;
        spi_cb_data.p_context = p_ctrl->p_cfg->p_context;

        /* Signal that a transfer has completed. */
        p_ctrl->p_cfg->p_callback(&spi_cb_data);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * ISR called in the event that an error occurs (Ex: RX_OVERFLOW).
 **********************************************************************************************************************/
void spi_eri_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type             irq    = R_FSP_CurrentIrqGet();
    spi_instance_ctrl_t * p_ctrl = (spi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Disable the SPI Transfer. */
    p_ctrl->p_regs->SPCR_b.SPE = 0;

    /* Setup callback args. */
    spi_callback_args_t spi_cb_data;
    spi_cb_data.channel   = p_ctrl->p_cfg->channel;
    spi_cb_data.p_context = p_ctrl->p_cfg->p_context;

    /* Read the status register. */
    uint16_t status = p_ctrl->p_regs->SPSR;

    /* Check SPCR.SPE = 0 */
    uint32_t timeout_count = SPI_PERIPHERAL_REG_MAX_WAIT;

    SPI_HARDWARE_REGISTER_WAIT(p_ctrl->p_regs->SPPSR_b.SPEPS, 0, timeout_count);

    /* Clear the flag */
    p_ctrl->p_regs->SPSRC = (R_SPI0_SPSRC_PERFC_Msk) | (R_SPI0_SPSRC_MODFC_Msk) | (R_SPI0_SPSRC_OVRFC_Msk) |
                            (R_SPI0_SPSRC_UDRFC_Msk);

    /* Dummy read to ensure that interrupt flags are cleared. */
    uint16_t dummy = p_ctrl->p_regs->SPSRC;
    FSP_PARAMETER_NOT_USED(dummy);

    /* Check if the error is a Parity Error. */
    if (R_SPI0_SPSR_PERF_Msk & status)
    {
        spi_cb_data.event = SPI_EVENT_ERR_PARITY;
        p_ctrl->p_cfg->p_callback(&spi_cb_data);
    }

    /* Check if the error is a Receive Buffer Overflow Error. */
    if (R_SPI0_SPSR_OVRF_Msk & status)
    {
        spi_cb_data.event = SPI_EVENT_ERR_READ_OVERFLOW;
        p_ctrl->p_cfg->p_callback(&spi_cb_data);
    }

    /* Check if the error is a Mode Fault Error. */
    if (R_SPI0_SPSR_MODF_Msk & status)
    {
        /* Check if the error is a Transmit Buffer Underflow Error. */
        if (R_SPI0_SPSR_UDRF_Msk & status)
        {
            spi_cb_data.event = SPI_EVENT_ERR_MODE_UNDERRUN;
            p_ctrl->p_cfg->p_callback(&spi_cb_data);
        }
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/* End of file R_SPI. */
