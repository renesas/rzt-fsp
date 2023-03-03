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
#include "r_xspi_ospi.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define XSPI_OSPI_PRV_OPEN                                 (0x4F535049)

#define XSPI_OSPI_DEVICE_START_ADDRESS                     (0x60000000)

#define XSPI_OSPI_PRV_WRAPCFG_DSSFTCS0_OFFSET              (8U)
#define XSPI_OSPI_PRV_WRAPCFG_DSSFTCS0_VALUE_MASK          (0x1F)
#define XSPI_OSPI_PRV_WRAPCFG_DSSFTCS1_OFFSET              (24U)
#define XSPI_OSPI_PRV_WRAPCFG_DSSFTCS1_VALUE_MASK          (0x1F)

#define XSPI_OSPI_PRV_LIOCFGCS_PRTMD_OFFSET                (0U)
#define XSPI_OSPI_PRV_LIOCFGCS_PRTMD_VALUE_MASK            (0x3FFU)
#define XSPI_OSPI_PRV_LIOCFGCS_PRTMD_MASK                  (0x3FFU << XSPI_OSPI_PRV_LIOCFGCS_PRTMD_OFFSET)
#define XSPI_OSPI_PRV_LIOCFGCS_CSMIN_OFFSET                (16U)
#define XSPI_OSPI_PRV_LIOCFGCS_CSMIN_VALUE_MASK            (0x0FU)
#define XSPI_OSPI_PRV_LIOCFGCS_CSASTEX_OFFSET              (20U)
#define XSPI_OSPI_PRV_LIOCFGCS_CSASTEX_VALUE_MASK          (0x01U)
#define XSPI_OSPI_PRV_LIOCFGCS_CSENGEX_OFFSET              (21U)
#define XSPI_OSPI_PRV_LIOCFGCS_CSENGEX_VALUE_MASK          (0x01U)

#define XSPI_OSPI_PRV_CMCFG0_FFMT_OFFSET                   (0U)
#define XSPI_OSPI_PRV_CMCFG0_ADDSIZE_OFFSET                (2U)
#define XSPI_OSPI_PRV_CMCFG0_ADDSIZE_VALUE_MASK            (0x03U)
#define XSPI_OSPI_PRV_CMCFG1_RDCMD_OFFSET                  (0U)
#define XSPI_OSPI_PRV_CMCFG1_RDCMD_UPPER_OFFSET            (8U)
#define XSPI_OSPI_PRV_CMCFG1_RDCMD_1B_VALUE_MASK           (0xFFU)
#define XSPI_OSPI_PRV_CMCFG1_RDCMD_2B_VALUE_MASK           (0xFFFFU)
#define XSPI_OSPI_PRV_CMCFG1_RDLATE_OFFSET                 (16U)
#define XSPI_OSPI_PRV_CMCFG1_RDLATE_VALUE_MASK             (0x1FU)

#define XSPI_OSPI_PRV_CMCFG2_WRCMD_OFFSET                  (0U)
#define XSPI_OSPI_PRV_CMCFG2_WRCMD_UPPER_OFFSET            (8U)
#define XSPI_OSPI_PRV_CMCFG2_WRCMD_1B_VALUE_MASK           (0xFFU)
#define XSPI_OSPI_PRV_CMCFG2_WRCMD_2B_VALUE_MASK           (0xFFFFU)
#define XSPI_OSPI_PRV_CMCFG2_WRLATE_OFFSET                 (16U)

#define XSPI_OSPI_PRV_BMCFG_WRMD_OFFSET                    (0U)
#define XSPI_OSPI_PRV_BMCFG_MWRCOMB_OFFSET                 (7U)
#define XSPI_OSPI_PRV_BMCFG_MWRSIZE_OFFSET                 (8U)
#define XSPI_OSPI_PRV_BMCFG_PREEN_OFFSET                   (16U)
#define XSPI_OSPI_PRV_BMCFG_PREEN_VALUE_MASK               (0x01U)

#define XSPI_OSPI_PRV_BMCTL_DEFAULT_VALUE                  (0xFF)

#define XSPI_OSPI_PRV_CDTBUF_CMDSIZE_OFFSET                (0U)
#define XSPI_OSPI_PRV_CDTBUF_CMDSIZE_VALUE_MASK            (0x03U)
#define XSPI_OSPI_PRV_CDTBUF_ADDSIZE_OFFSET                (2U)
#define XSPI_OSPI_PRV_CDTBUF_ADDSIZE_VALUE_MASK            (0x07U)
#define XSPI_OSPI_PRV_CDTBUF_DATASIZE_OFFSET               (5U)
#define XSPI_OSPI_PRV_CDTBUF_DATASIZE_VALUE_MASK           (0x0FU)
#define XSPI_OSPI_PRV_CDTBUF_LATE_OFFSET                   (9U)
#define XSPI_OSPI_PRV_CDTBUF_LATE_VALUE_MASK               (0x1FU)
#define XSPI_OSPI_PRV_CDTBUF_TRTYPE_OFFSET                 (15U)
#define XSPI_OSPI_PRV_CDTBUF_TRTYPE_VALUE_MASK             (0x01U)
#define XSPI_OSPI_PRV_CDTBUF_CMD_OFFSET                    (16U)
#define XSPI_OSPI_PRV_CDTBUF_CMD_UPPER_OFFSET              (24U)
#define XSPI_OSPI_PRV_CDTBUF_CMD_1B_VALUE_MASK             (0xFFU)
#define XSPI_OSPI_PRV_CDTBUF_CMD_2B_VALUE_MASK             (0xFFFFU)

#define XSPI_OSPI_PRV_CCCTL0_CANOWR_OFFSET                 (1U)
#define XSPI_OSPI_PRV_CCCTL0_CAITV_OFFSET                  (8U)
#define XSPI_OSPI_PRV_CCCTL0_CASFTSTA_OFFSET               (16U)
#define XSPI_OSPI_PRV_CCCTL0_CASFTEND_OFFSET               (24U)

#define XSPI_OSPI_PRV_CCCTL1_CACMDSIZE_OFFSET              (0U)
#define XSPI_OSPI_PRV_CCCTL1_CACMDSIZE_VALUE_MASK          (0x3U)
#define XSPI_OSPI_PRV_CCCTL1_CAADDSIZE_OFFSET              (2U)
#define XSPI_OSPI_PRV_CCCTL1_CAADDSIZE_VALUE_MASK          (0xFU)
#define XSPI_OSPI_PRV_CCCTL1_CADATASIZE_OFFSET             (5U)
#define XSPI_OSPI_PRV_CCCTL1_CAWRLATE_OFFSET               (16U)
#define XSPI_OSPI_PRV_CCCTL1_CARDLATE_OFFSET               (24U)
#define XSPI_OSPI_PRV_CCCTL1_CARDLATE_VALUE_MASK           (0x1FU)

#define XSPI_OSPI_PRV_CCCTL2_CARDCMD_OFFSET                (16U)
#define XSPI_OSPI_PRV_CCCTL2_CARDCMD_VALUE_MASK            (0xFFFFU)

#define XSPI_OSPI_PRV_COMSTT_MEMACC_OFFSET                 (0U)
#define XSPI_OSPI_PRV_COMSTT_MEMACC_VALUE_MASK             (0x01U)
#define XSPI_OSPI_PRV_COMSTT_WRBUFNE_OFFSET                (6U)
#define XSPI_OSPI_PRV_COMSTT_WRBUFNE_VALUE_MASK            (0x01U)

#define XSPI_OSPI_PRV_INTC_CMDCMPC_OFFSET                  (0U)

#define XSPI_OSPI_PRV_MAX_COMBINE_SIZE                     (64U)

#define XSPI_OSPI_PRV_WORD_ACCESS_SIZE                     (4U)
#define XSPI_OSPI_PRV_HALF_WORD_ACCESS_SIZE                (2U)

#define XSPI_OSPI_PRV_DIRECT_ADDR_AND_DATA_MASK            (7U)
#define XSPI_OSPI_PRV_PAGE_SIZE_BYTES                      (256U)

#define XSPI_OSPI_PRV_AUTOCALIBARION_PREAMBLE_PATTERN_0    (0xFFFF0000)
#define XSPI_OSPI_PRV_AUTOCALIBARION_PREAMBLE_PATTERN_1    (0x000800FF)
#define XSPI_OSPI_PRV_AUTOCALIBARION_PREAMBLE_PATTERN_2    (0x00FFF700)
#define XSPI_OSPI_PRV_AUTOCALIBARION_PREAMBLE_PATTERN_3    (0xF700F708)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Number of address bytes in 4 byte address mode. */
#define XSPI_OSPI_4_BYTE_ADDRESS                           (4U)

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static fsp_err_t r_xspi_ospi_automatic_calibration_seq(xspi_ospi_instance_ctrl_t * p_instance_ctrl);
static bool      r_xspi_ospi_status_sub(xspi_ospi_instance_ctrl_t * p_instance_ctrl, uint8_t bit_pos);
static fsp_err_t r_xspi_ospi_spi_protocol_specific_settings(xspi_ospi_instance_ctrl_t * p_instance_ctrl,
                                                            spi_flash_protocol_t        spi_protocol);
static void r_xspi_ospi_write_enable(xspi_ospi_instance_ctrl_t * p_instance_ctrl);
static void r_xspi_ospi_direct_transfer(xspi_ospi_instance_ctrl_t         * p_instance_ctrl,
                                        spi_flash_direct_transfer_t * const p_transfer,
                                        spi_flash_direct_transfer_dir_t     direction);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** Version data structure used by error logger macro. */
static const fsp_version_t g_ospi_version =
{
    .api_version_minor  = SPI_FLASH_API_VERSION_MINOR,
    .api_version_major  = SPI_FLASH_API_VERSION_MAJOR,
    .code_version_major = XSPI_OSPI_CODE_VERSION_MAJOR,
    .code_version_minor = XSPI_OSPI_CODE_VERSION_MINOR
};

/*******************************************************************************************************************//**
 * @addtogroup XSPI_OSPI
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

const spi_flash_api_t g_spi_flash_on_xspi_ospi =
{
    .open           = R_XSPI_OSPI_Open,
    .directWrite    = R_XSPI_OSPI_DirectWrite,
    .directRead     = R_XSPI_OSPI_DirectRead,
    .directTransfer = R_XSPI_OSPI_DirectTransfer,
    .spiProtocolSet = R_XSPI_OSPI_SpiProtocolSet,
    .write          = R_XSPI_OSPI_Write,
    .erase          = R_XSPI_OSPI_Erase,
    .statusGet      = R_XSPI_OSPI_StatusGet,
    .xipEnter       = R_XSPI_OSPI_XipEnter,
    .xipExit        = R_XSPI_OSPI_XipExit,
    .bankSet        = R_XSPI_OSPI_BankSet,
    .close          = R_XSPI_OSPI_Close,
    .versionGet     = R_XSPI_OSPI_VersionGet,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Open the OSPI driver module. After the driver is open, the OSPI can be accessed like internal flash memory.
 *
 * Implements @ref spi_flash_api_t::open.
 *
 * Example:
 * @snippet r_xspi_ospi_example.c R_XSPI_OSPI_Open
 *
 * @retval FSP_SUCCESS              Configuration was successful.
 * @retval FSP_ERR_ASSERTION        The parameter p_ctrl or p_cfg is NULL.
 * @retval FSP_ERR_ALREADY_OPEN     Driver has already been opened with the same p_ctrl.
 * @retval FSP_ERR_CALIBRATE_FAILED Failed to perform auto-calibrate.
 **********************************************************************************************************************/
fsp_err_t R_XSPI_OSPI_Open (spi_flash_ctrl_t * p_ctrl, spi_flash_cfg_t const * const p_cfg)
{
    xspi_ospi_instance_ctrl_t * p_instance_ctrl = (xspi_ospi_instance_ctrl_t *) p_ctrl;

#if XSPI_OSPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ERROR_RETURN(XSPI_OSPI_PRV_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    xspi_ospi_extended_cfg_t * p_cfg_extend = (xspi_ospi_extended_cfg_t *) p_cfg->p_extend;

    /* Enable clock to the OSPI block */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_START(FSP_IP_XSPI, p_cfg_extend->unit);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    /* Set base address. */
    uint32_t base_address = (uint32_t) R_XSPI0 + (p_cfg_extend->unit * ((uint32_t) R_XSPI1 - (uint32_t) R_XSPI0));
    p_instance_ctrl->p_reg = (R_XSPI0_Type *) base_address;

    /* Initialize control block. */
    p_instance_ctrl->p_cfg        = p_cfg;
    p_instance_ctrl->spi_protocol = p_cfg->spi_protocol;
    p_instance_ctrl->chip_select  = p_cfg_extend->chip_select;

    /* xSPI configuration (see RZ microprocessor User's Manual section "Flow of Configuration"). */
    /* Set xSPI CSn size. */
    if (XSPI_OSPI_CHIP_SELECT_0 == p_instance_ctrl->chip_select)
    {
        p_instance_ctrl->p_reg->CSSCTL_b.CS0SIZE = p_cfg_extend->memory_size;
    }
    else
    {
        p_instance_ctrl->p_reg->CSSCTL_b.CS1SIZE = p_cfg_extend->memory_size;
    }

    /* Set xSPI protocol mode. */
    p_instance_ctrl->p_reg->LIOCFGCS[p_cfg_extend->chip_select] = (p_cfg->spi_protocol) <<
                                                                  XSPI_OSPI_PRV_LIOCFGCS_PRTMD_OFFSET;

    /* Set xSPI drive/sampling timing. */
    if (XSPI_OSPI_CHIP_SELECT_0 == p_instance_ctrl->chip_select)
    {
        p_instance_ctrl->p_reg->WRAPCFG =
            (p_cfg_extend->data_latch_delay_clocks & XSPI_OSPI_PRV_WRAPCFG_DSSFTCS0_VALUE_MASK) <<
                XSPI_OSPI_PRV_WRAPCFG_DSSFTCS0_OFFSET;
    }
    else
    {
        p_instance_ctrl->p_reg->WRAPCFG =
            (p_cfg_extend->data_latch_delay_clocks & XSPI_OSPI_PRV_WRAPCFG_DSSFTCS1_VALUE_MASK) <<
                XSPI_OSPI_PRV_WRAPCFG_DSSFTCS1_OFFSET;
    }

    /* Set xSPI CSn signal timings. */
    p_instance_ctrl->p_reg->LIOCFGCS[p_instance_ctrl->chip_select] =
        ((p_cfg->spi_protocol & XSPI_OSPI_PRV_LIOCFGCS_PRTMD_VALUE_MASK) << XSPI_OSPI_PRV_LIOCFGCS_PRTMD_OFFSET) |
        ((p_cfg_extend->p_timing_settings->command_to_command_interval &
          XSPI_OSPI_PRV_LIOCFGCS_CSMIN_VALUE_MASK) << XSPI_OSPI_PRV_LIOCFGCS_CSMIN_OFFSET) |
        ((p_cfg_extend->p_timing_settings->cs_pulldown_lead & XSPI_OSPI_PRV_LIOCFGCS_CSASTEX_VALUE_MASK) <<
            XSPI_OSPI_PRV_LIOCFGCS_CSASTEX_OFFSET) |
        ((p_cfg_extend->p_timing_settings->cs_pullup_lag & XSPI_OSPI_PRV_LIOCFGCS_CSENGEX_VALUE_MASK) <<
            XSPI_OSPI_PRV_LIOCFGCS_CSENGEX_OFFSET);

    /* Set xSPI memory-mapping operation. */
    fsp_err_t ret = r_xspi_ospi_spi_protocol_specific_settings(p_instance_ctrl, p_instance_ctrl->spi_protocol);

    /* Set the access from AHB channel. */
    p_instance_ctrl->p_reg->BMCTL0 = XSPI_OSPI_PRV_BMCTL_DEFAULT_VALUE;

    /* Return response after issuing write transaction to xSPI bus, Enable prefetch function. */
    p_instance_ctrl->p_reg->BMCFG = (0 << XSPI_OSPI_PRV_BMCFG_WRMD_OFFSET) |
                                    (1 << XSPI_OSPI_PRV_BMCFG_MWRCOMB_OFFSET) |
                                    (0x0F << XSPI_OSPI_PRV_BMCFG_MWRSIZE_OFFSET) |
                                    ((p_cfg_extend->prefetch_en & XSPI_OSPI_PRV_BMCFG_PREEN_VALUE_MASK) <<
                                     XSPI_OSPI_PRV_BMCFG_PREEN_OFFSET);

    /* Set use Channel. */
    p_instance_ctrl->p_reg->CDCTL0_b.CSSEL = p_instance_ctrl->chip_select;

    if (FSP_SUCCESS == ret)
    {
        p_instance_ctrl->open = XSPI_OSPI_PRV_OPEN;
    }

    return ret;
}

/*******************************************************************************************************************//**
 * Writes raw data directly to the OctaFlash. API not supported. Use R_XSPI_OSPI_DirectTransfer
 *
 * Implements @ref spi_flash_api_t::directWrite.
 *
 * @retval FSP_ERR_UNSUPPORTED         API not supported by OSPI.
 **********************************************************************************************************************/
fsp_err_t R_XSPI_OSPI_DirectWrite (spi_flash_ctrl_t    * p_ctrl,
                                   uint8_t const * const p_src,
                                   uint32_t const        bytes,
                                   bool const            read_after_write)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_src);
    FSP_PARAMETER_NOT_USED(bytes);
    FSP_PARAMETER_NOT_USED(read_after_write);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * Reads raw data directly from the OctaFlash. API not supported. Use R_XSPI_OSPI_DirectTransfer.
 *
 * Implements @ref spi_flash_api_t::directRead.
 *
 * @retval FSP_ERR_UNSUPPORTED         API not supported by OSPI.
 **********************************************************************************************************************/
fsp_err_t R_XSPI_OSPI_DirectRead (spi_flash_ctrl_t * p_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_dest);
    FSP_PARAMETER_NOT_USED(bytes);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * Read/Write raw data directly with the OctaFlash.
 *
 * Implements @ref spi_flash_api_t::directTransfer.
 *
 * Example:
 * @snippet r_xspi_ospi_example.c R_XSPI_OSPI_DirectTransfer
 *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_XSPI_OSPI_DirectTransfer (spi_flash_ctrl_t                  * p_ctrl,
                                      spi_flash_direct_transfer_t * const p_transfer,
                                      spi_flash_direct_transfer_dir_t     direction)
{
    xspi_ospi_instance_ctrl_t * p_instance_ctrl = (xspi_ospi_instance_ctrl_t *) p_ctrl;
#if XSPI_OSPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_transfer);
    FSP_ASSERT(0 != p_transfer->command_length);
    FSP_ERROR_RETURN(XSPI_OSPI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    r_xspi_ospi_direct_transfer(p_instance_ctrl, p_transfer, direction);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enters XIP (execute in place) mode.
 *
 * Implements @ref spi_flash_api_t::xipEnter.
 *
 * @retval FSP_ERR_UNSUPPORTED         API not supported by OSPI.
 **********************************************************************************************************************/
fsp_err_t R_XSPI_OSPI_XipEnter (spi_flash_ctrl_t * p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Exits XIP (execute in place) mode.
 *
 * Implements @ref spi_flash_api_t::xipExit.
 *
 * @retval FSP_ERR_UNSUPPORTED         API not supported by OSPI.
 **********************************************************************************************************************/
fsp_err_t R_XSPI_OSPI_XipExit (spi_flash_ctrl_t * p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Program a page of data to the flash.
 *
 * Implements @ref spi_flash_api_t::write.
 *
 * Example:
 * @snippet r_xspi_ospi_example.c R_XSPI_OSPI_Write
 *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           p_instance_ctrl, p_dest or p_src is NULL, or byte_count crosses a page boundary.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_DEVICE_BUSY         Another Write/Erase transaction is in progress.
 *
 * @note In this API, data can be written up to 64 bytes at a time.
 * @note In 8D-8D-8D(OPI) mode, written data must be even bytes in size.
 **********************************************************************************************************************/
fsp_err_t R_XSPI_OSPI_Write (spi_flash_ctrl_t    * p_ctrl,
                             uint8_t const * const p_src,
                             uint8_t * const       p_dest,
                             uint32_t              byte_count)
{
    xspi_ospi_instance_ctrl_t * p_instance_ctrl = (xspi_ospi_instance_ctrl_t *) p_ctrl;
#if XSPI_OSPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_src);
    FSP_ASSERT(NULL != p_dest);
    FSP_ERROR_RETURN(XSPI_OSPI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(XSPI_OSPI_PRV_MAX_COMBINE_SIZE >= byte_count);
    FSP_ASSERT(0 != byte_count);
    FSP_ASSERT((0 == byte_count % XSPI_OSPI_PRV_HALF_WORD_ACCESS_SIZE) ||
               (XSPI_OSPI_BYTE_ORDER_1032 != ((xspi_ospi_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend)->byte_order) ||
               (SPI_FLASH_PROTOCOL_8D_8D_8D != p_instance_ctrl->spi_protocol));
#endif
    xspi_ospi_extended_cfg_t * p_cfg_extend = (xspi_ospi_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    FSP_ERROR_RETURN(false == r_xspi_ospi_status_sub(p_instance_ctrl, p_instance_ctrl->p_cfg->write_status_bit),
                     FSP_ERR_DEVICE_BUSY);

    r_xspi_ospi_write_enable(p_instance_ctrl);

    uint32_t i = 0;

    /* Word access */
    if (0 == byte_count % XSPI_OSPI_PRV_WORD_ACCESS_SIZE)
    {
        uint32_t * p_word_aligned_dest = (uint32_t *) p_dest;
        uint32_t * p_word_aligned_src  = (uint32_t *) p_src;
        if ((XSPI_OSPI_BYTE_ORDER_1032 == p_cfg_extend->byte_order) &&
            (SPI_FLASH_PROTOCOL_8D_8D_8D == p_instance_ctrl->spi_protocol))
        {
            for (i = 0; i < byte_count / XSPI_OSPI_PRV_WORD_ACCESS_SIZE; i++)
            {
                /* Apply __REV16 to convert the data to match the OctaFlash byte order. */
                *p_word_aligned_dest = __REV16(*p_word_aligned_src);
                p_word_aligned_dest++;
                p_word_aligned_src++;
            }
        }
        else
        {
            for (i = 0; i < byte_count / XSPI_OSPI_PRV_WORD_ACCESS_SIZE; i++)
            {
                *p_word_aligned_dest = *p_word_aligned_src;
                p_word_aligned_dest++;
                p_word_aligned_src++;
            }
        }
    }
    /* Half Word access */
    else if (0 == byte_count % XSPI_OSPI_PRV_HALF_WORD_ACCESS_SIZE)
    {
        uint16_t * p_half_word_aligned_dest = (uint16_t *) p_dest;
        uint16_t * p_half_word_aligned_src  = (uint16_t *) p_src;
        if ((XSPI_OSPI_BYTE_ORDER_1032 == p_cfg_extend->byte_order) &&
            (SPI_FLASH_PROTOCOL_8D_8D_8D == p_instance_ctrl->spi_protocol))
        {
            for (i = 0; i < byte_count / XSPI_OSPI_PRV_HALF_WORD_ACCESS_SIZE; i++)
            {
                /* Apply __REV16 to convert the data to match the OctaFlash byte order. */
                *p_half_word_aligned_dest = (uint16_t) __REV16((uint32_t) (*p_half_word_aligned_src & UINT16_MAX));
                p_half_word_aligned_dest++;
                p_half_word_aligned_src++;
            }
        }
        else
        {
            for (i = 0; i < byte_count / XSPI_OSPI_PRV_HALF_WORD_ACCESS_SIZE; i++)
            {
                *p_half_word_aligned_dest = *p_half_word_aligned_src;
                p_half_word_aligned_dest++;
                p_half_word_aligned_src++;
            }
        }
    }
    /* Byte access */
    else
    {
        for (i = 0; i < byte_count; i++)
        {
            p_dest[i] = p_src[i];
        }
    }

    /* Ensure that all write data is in the xSPI write buffer. */
    __asm volatile ("dsb");

    /* Request to push the pending data */
    if (XSPI_OSPI_PRV_MAX_COMBINE_SIZE > byte_count)
    {
        /* Push the pending data. */
        p_instance_ctrl->p_reg->BMCTL1_b.MWRPUSH = 1;
    }

    /* Wait until memory access starts in write API. */
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->COMSTT_b.MEMACC, 1);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Erase a block or sector of flash.  The byte_count must exactly match one of the erase sizes defined in spi_flash_cfg_t.
 * For chip erase, byte_count must be SPI_FLASH_ERASE_SIZE_CHIP_ERASE.
 *
 * Implements @ref spi_flash_api_t::erase.
 *
 * @retval FSP_SUCCESS                 The command to erase the flash was executed successfully.
 * @retval FSP_ERR_ASSERTION           p_instance_ctrl or p_device_address is NULL, byte_count doesn't match an erase
 *                                     size defined in spi_flash_cfg_t, or byte_count is set to 0.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_DEVICE_BUSY         The device is busy.
 **********************************************************************************************************************/
fsp_err_t R_XSPI_OSPI_Erase (spi_flash_ctrl_t * p_ctrl, uint8_t * const p_device_address, uint32_t byte_count)
{
    xspi_ospi_instance_ctrl_t * p_instance_ctrl = (xspi_ospi_instance_ctrl_t *) p_ctrl;

#if XSPI_OSPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_device_address);
    FSP_ASSERT(0 != byte_count);
    FSP_ERROR_RETURN(XSPI_OSPI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    spi_flash_cfg_t const * p_cfg         = p_instance_ctrl->p_cfg;
    uint16_t                erase_command = 0;
    uint32_t                chip_address  = (uint32_t) p_device_address - XSPI_OSPI_DEVICE_START_ADDRESS;
    bool send_address = true;
    xspi_ospi_extended_cfg_t * p_cfg_extend = (xspi_ospi_extended_cfg_t *) p_cfg->p_extend;
    FSP_ERROR_RETURN(false == r_xspi_ospi_status_sub(p_instance_ctrl, p_cfg->write_status_bit), FSP_ERR_DEVICE_BUSY);

    for (uint32_t index = 0; index < p_cfg->erase_command_list_length; index++)
    {
        /* If requested byte_count is supported by underlying flash, store the command. */
        if (byte_count == p_cfg->p_erase_command_list[index].size)
        {
            if (SPI_FLASH_ERASE_SIZE_CHIP_ERASE == byte_count)
            {
                /* Don't send address for chip erase. */
                send_address = false;
            }

            erase_command = p_cfg->p_erase_command_list[index].command;
            break;
        }
    }

#if XSPI_OSPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(0U != erase_command);
#endif

    r_xspi_ospi_write_enable(p_instance_ctrl);

    spi_flash_direct_transfer_t direct_command = {0};
    direct_command.command        = erase_command;
    direct_command.address        = chip_address;
    direct_command.address_length = (true == send_address) ?
                                    (XSPI_OSPI_PRV_DIRECT_ADDR_AND_DATA_MASK &
                                     (p_instance_ctrl->p_cfg->address_bytes + 1U)) : 0U;
    direct_command.command_length = (SPI_FLASH_PROTOCOL_1S_1S_1S == p_instance_ctrl->spi_protocol) ?
                                    1U : (p_cfg_extend->p_opi_commands->command_bytes);

    r_xspi_ospi_direct_transfer(p_instance_ctrl, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Gets the write or erase status of the flash.
 *
 * Implements @ref spi_flash_api_t::statusGet.
 *
 * Example:
 * @snippet r_xspi_ospi_example.c R_XSPI_OSPI_StatusGet
 *
 * @retval FSP_SUCCESS                 The write status is in p_status.
 * @retval FSP_ERR_ASSERTION           p_instance_ctrl or p_status is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_XSPI_OSPI_StatusGet (spi_flash_ctrl_t * p_ctrl, spi_flash_status_t * const p_status)
{
    xspi_ospi_instance_ctrl_t * p_instance_ctrl = (xspi_ospi_instance_ctrl_t *) p_ctrl;

#if XSPI_OSPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(XSPI_OSPI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    uint32_t comstt  = p_instance_ctrl->p_reg->COMSTT;
    bool     memacc  = (bool) ((comstt >> XSPI_OSPI_PRV_COMSTT_MEMACC_OFFSET) & XSPI_OSPI_PRV_COMSTT_MEMACC_VALUE_MASK);
    bool     wrbufne =
        (bool) ((comstt >> XSPI_OSPI_PRV_COMSTT_WRBUFNE_OFFSET) & XSPI_OSPI_PRV_COMSTT_WRBUFNE_VALUE_MASK);

    if ((true == memacc) || (true == wrbufne))
    {
        /* If the xSPI is accessing memory or data is in the write buffer,
         * it is judged a "write in progress" without access to device. */
        p_status->write_in_progress = (bool) (wrbufne | memacc);
    }
    else
    {
        /* Read device status. */
        p_status->write_in_progress = r_xspi_ospi_status_sub(p_instance_ctrl, p_instance_ctrl->p_cfg->write_status_bit);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Selects the bank to access.
 *
 * Implements @ref spi_flash_api_t::bankSet.
 *
 * @retval FSP_ERR_UNSUPPORTED         API not supported by OSPI.
 **********************************************************************************************************************/
fsp_err_t R_XSPI_OSPI_BankSet (spi_flash_ctrl_t * p_ctrl, uint32_t bank)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(bank);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * Sets the SPI protocol.
 *
 * Implements @ref spi_flash_api_t::spiProtocolSet.
 *
 * Example:
 * @snippet r_xspi_ospi_example.c R_XSPI_OSPI_SpiProtocolSet
 *
 * @retval FSP_SUCCESS                SPI protocol updated on MPU peripheral.
 * @retval FSP_ERR_ASSERTION          A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN           Driver is not opened.
 * @retval FSP_ERR_CALIBRATE_FAILED   Failed to perform auto-calibrate.
 **********************************************************************************************************************/
fsp_err_t R_XSPI_OSPI_SpiProtocolSet (spi_flash_ctrl_t * p_ctrl, spi_flash_protocol_t spi_protocol)
{
    xspi_ospi_instance_ctrl_t * p_instance_ctrl = (xspi_ospi_instance_ctrl_t *) p_ctrl;

#if XSPI_OSPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(XSPI_OSPI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    p_instance_ctrl->spi_protocol = spi_protocol;

    /* Update the SPI protocol and its associated registers. */
    return r_xspi_ospi_spi_protocol_specific_settings(p_instance_ctrl, spi_protocol);
}

/*******************************************************************************************************************//**
 * Close the OSPI driver module.
 *
 * Implements @ref spi_flash_api_t::close.
 *
 * @retval FSP_SUCCESS             Configuration was successful.
 * @retval FSP_ERR_ASSERTION       p_instance_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN        Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_XSPI_OSPI_Close (spi_flash_ctrl_t * p_ctrl)
{
    xspi_ospi_instance_ctrl_t * p_instance_ctrl = (xspi_ospi_instance_ctrl_t *) p_ctrl;

#if XSPI_OSPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(XSPI_OSPI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    spi_flash_cfg_t          * p_cfg        = (spi_flash_cfg_t *) p_instance_ctrl->p_cfg;
    xspi_ospi_extended_cfg_t * p_cfg_extend = (xspi_ospi_extended_cfg_t *) p_cfg->p_extend;

    /* Disable clock to the OSPI block */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_STOP(FSP_IP_XSPI, p_cfg_extend->unit);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * DEPRECATED Get the driver version based on compile time macros.
 *
 * Implements @ref spi_flash_api_t::versionGet.
 *
 * @retval     FSP_SUCCESS          Successful close.
 * @retval     FSP_ERR_ASSERTION    p_version is NULL.
 *
 **********************************************************************************************************************/
fsp_err_t R_XSPI_OSPI_VersionGet (fsp_version_t * const p_version)
{
#if XSPI_OSPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_version);
#endif

    p_version->version_id = g_ospi_version.version_id;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup XSPI_OSPI)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Perform initialization based on SPI/OPI protocol
 *
 * @param[in]   p_instance_ctrl    Pointer to OSPI specific control structure
 * @param[in]   spi_protocol       SPI/OPI protocol request
 *
 * @retval      FSP_SUCCESS                Protocol based settings completed successfully.
 * @retval      FSP_ERR_CALIBRATE_FAILED   Auto-Calibration failed.
 **********************************************************************************************************************/
static fsp_err_t r_xspi_ospi_spi_protocol_specific_settings (xspi_ospi_instance_ctrl_t * p_instance_ctrl,
                                                             spi_flash_protocol_t        spi_protocol)
{
    spi_flash_cfg_t const    * p_cfg        = p_instance_ctrl->p_cfg;
    xspi_ospi_extended_cfg_t * p_cfg_extend = (xspi_ospi_extended_cfg_t *) p_cfg->p_extend;
    fsp_err_t               ret             = FSP_SUCCESS;
    xspi_ospi_chip_select_t chip_select     = p_instance_ctrl->chip_select;

    /* Update the SPI protocol. */
    p_instance_ctrl->p_reg->LIOCFGCS_b[p_cfg_extend->chip_select].PRTMD = spi_protocol &
                                                                          XSPI_OSPI_PRV_LIOCFGCS_PRTMD_MASK;

    /* Specifies the read/write commands and Read dummy clocks for Device
     * (see RZ microprocessor User's Manual section "Flow of Memory-mapping"). */
    if ((SPI_FLASH_PROTOCOL_1S_1S_1S == spi_protocol))
    {
        p_instance_ctrl->p_reg->CSa[chip_select].CMCFG0 =
            (0U << XSPI_OSPI_PRV_CMCFG0_FFMT_OFFSET) |
            ((p_cfg->address_bytes & XSPI_OSPI_PRV_CMCFG0_ADDSIZE_VALUE_MASK) << XSPI_OSPI_PRV_CMCFG0_ADDSIZE_OFFSET);

        p_instance_ctrl->p_reg->CSa[chip_select].CMCFG1 =
            ((p_cfg->read_command & XSPI_OSPI_PRV_CMCFG1_RDCMD_1B_VALUE_MASK) <<
                XSPI_OSPI_PRV_CMCFG1_RDCMD_UPPER_OFFSET) |
            ((p_cfg->dummy_clocks & XSPI_OSPI_PRV_CMCFG1_RDLATE_VALUE_MASK) << XSPI_OSPI_PRV_CMCFG1_RDLATE_OFFSET);

        p_instance_ctrl->p_reg->CSa[chip_select].CMCFG2 =
            ((p_cfg->page_program_command & XSPI_OSPI_PRV_CMCFG2_WRCMD_1B_VALUE_MASK) <<
                XSPI_OSPI_PRV_CMCFG2_WRCMD_UPPER_OFFSET) |
            (0 << XSPI_OSPI_PRV_CMCFG2_WRLATE_OFFSET);
    }
    else
    {
        xspi_ospi_opi_command_set_t const * p_opi_commands = p_cfg_extend->p_opi_commands;
        p_instance_ctrl->p_reg->CSa[chip_select].CMCFG0 =
            (1U << XSPI_OSPI_PRV_CMCFG0_FFMT_OFFSET) |
            ((p_cfg->address_bytes & XSPI_OSPI_PRV_CMCFG0_ADDSIZE_VALUE_MASK) << XSPI_OSPI_PRV_CMCFG0_ADDSIZE_OFFSET);

        p_instance_ctrl->p_reg->CSa[chip_select].CMCFG1 =
            ((p_opi_commands->dual_read_command & XSPI_OSPI_PRV_CMCFG1_RDCMD_2B_VALUE_MASK) <<
                XSPI_OSPI_PRV_CMCFG1_RDCMD_OFFSET) |
            ((p_cfg_extend->opi_mem_read_dummy_cycles & XSPI_OSPI_PRV_CMCFG1_RDLATE_VALUE_MASK) <<
                XSPI_OSPI_PRV_CMCFG1_RDLATE_OFFSET);

        p_instance_ctrl->p_reg->CSa[chip_select].CMCFG2 =
            ((p_opi_commands->page_program_command & XSPI_OSPI_PRV_CMCFG2_WRCMD_2B_VALUE_MASK) <<
                XSPI_OSPI_PRV_CMCFG2_WRCMD_OFFSET) |
            (0 << XSPI_OSPI_PRV_CMCFG2_WRLATE_OFFSET);

        /* Perform Automatic Calibration to appropriately update WRAPCFG DSSFTCSn field. */
        if (0 == p_cfg_extend->data_latch_delay_clocks)
        {
            ret = r_xspi_ospi_automatic_calibration_seq(p_instance_ctrl);
        }
    }

    return ret;
}

/*******************************************************************************************************************//**
 * Gets device status.
 *
 * @param[in]  p_instance_ctrl         Pointer to a driver handle
 * @param[in]  bit_pos                 Write-in-progress bit position
 *
 * @return True if busy, false if not.
 **********************************************************************************************************************/
static bool r_xspi_ospi_status_sub (xspi_ospi_instance_ctrl_t * p_instance_ctrl, uint8_t bit_pos)
{
    spi_flash_cfg_t const     * p_cfg          = p_instance_ctrl->p_cfg;
    spi_flash_direct_transfer_t direct_command = {0};

    if (SPI_FLASH_PROTOCOL_1S_1S_1S == p_instance_ctrl->spi_protocol)
    {
        direct_command.command        = p_cfg->status_command;
        direct_command.command_length = 1U;
    }
    else
    {
        xspi_ospi_opi_command_set_t const * p_opi_commands =
            ((xspi_ospi_extended_cfg_t *) p_cfg->p_extend)->p_opi_commands;
        direct_command.command        = p_opi_commands->status_command;
        direct_command.command_length = p_opi_commands->command_bytes;
        direct_command.address_length = (p_cfg->address_bytes + 1U) &
                                        XSPI_OSPI_PRV_DIRECT_ADDR_AND_DATA_MASK;
        direct_command.dummy_cycles = 4U;
    }

    direct_command.data_length = 1U;
    r_xspi_ospi_direct_transfer(p_instance_ctrl, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_READ);

    return (direct_command.data >> bit_pos) & 1U;
}

/*******************************************************************************************************************//**
 * Send Write enable command to the OctaFlash
 *
 * @param[in]   p_instance_ctrl    Pointer to OSPI specific control structure
 **********************************************************************************************************************/
static void r_xspi_ospi_write_enable (xspi_ospi_instance_ctrl_t * p_instance_ctrl)
{
    spi_flash_direct_transfer_t direct_command = {0};
    spi_flash_cfg_t const     * p_cfg          = p_instance_ctrl->p_cfg;
    if ((SPI_FLASH_PROTOCOL_1S_1S_1S == p_instance_ctrl->spi_protocol))
    {
        direct_command.command        = p_cfg->write_enable_command;
        direct_command.command_length = 1U;
    }
    else
    {
        xspi_ospi_opi_command_set_t const * p_opi_commands =
            ((xspi_ospi_extended_cfg_t *) p_cfg->p_extend)->p_opi_commands;
        direct_command.command        = p_opi_commands->write_enable_command;
        direct_command.command_length = p_opi_commands->command_bytes;
    }

    r_xspi_ospi_direct_transfer(p_instance_ctrl, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
}

/*******************************************************************************************************************//**
 * Perform Automatic Calibration
 *
 * @param[in]   p_instance_ctrl    Pointer to OSPI specific control structure
 *
 * @retval      FSP_SUCCESS                Auto-Calibration completed successfully.
 * @retval      FSP_ERR_CALIBRATE_FAILED   Auto-Calibration failed.
 **********************************************************************************************************************/
static fsp_err_t r_xspi_ospi_automatic_calibration_seq (xspi_ospi_instance_ctrl_t * p_instance_ctrl)
{
    fsp_err_t                           ret            = FSP_SUCCESS;
    spi_flash_cfg_t                   * p_cfg          = (spi_flash_cfg_t *) p_instance_ctrl->p_cfg;
    xspi_ospi_extended_cfg_t          * p_cfg_extend   = (xspi_ospi_extended_cfg_t *) p_cfg->p_extend;
    xspi_ospi_opi_command_set_t const * p_opi_commands = p_cfg_extend->p_opi_commands;

    xspi_ospi_chip_select_t chip_select = p_instance_ctrl->chip_select;

    /* Perform Automatic Calibration
     * (see RZ microprocessor User's Manual section "Flow of Automatic Calibration") */

    /* Check no callibration run. */
    if (0 != p_instance_ctrl->p_reg->CSb[chip_select].CCCTL0_b.CAEN)
    {
        ret = FSP_ERR_CALIBRATE_FAILED;
    }
    else
    {
        p_instance_ctrl->p_reg->CSb[chip_select].CCCTL1 =
            ((p_opi_commands->command_bytes & XSPI_OSPI_PRV_CCCTL1_CACMDSIZE_VALUE_MASK) <<
                XSPI_OSPI_PRV_CCCTL1_CACMDSIZE_OFFSET) |
            (((p_cfg->address_bytes + 1U) & XSPI_OSPI_PRV_CCCTL1_CAADDSIZE_VALUE_MASK) <<
                XSPI_OSPI_PRV_CCCTL1_CAADDSIZE_OFFSET) |
            (0xF << XSPI_OSPI_PRV_CCCTL1_CADATASIZE_OFFSET) |
            (0 << XSPI_OSPI_PRV_CCCTL1_CAWRLATE_OFFSET) |
            ((p_cfg_extend->opi_mem_read_dummy_cycles & XSPI_OSPI_PRV_CCCTL1_CARDLATE_VALUE_MASK) <<
                XSPI_OSPI_PRV_CCCTL1_CARDLATE_OFFSET);

        p_instance_ctrl->p_reg->CSb[chip_select].CCCTL2 =
            ((p_opi_commands->dual_read_command & XSPI_OSPI_PRV_CCCTL2_CARDCMD_VALUE_MASK) <<
                XSPI_OSPI_PRV_CCCTL2_CARDCMD_OFFSET);
        p_instance_ctrl->p_reg->CSb[chip_select].CCCTL3 =
            (uint32_t) p_cfg_extend->p_autocalibration_preamble_pattern_addr;

        if (XSPI_OSPI_BYTE_ORDER_1032 == p_cfg_extend->byte_order)
        {
            /* Apply __REV16 to match the preamble pattern with the data to be read in the auto calibration sequence. */
            p_instance_ctrl->p_reg->CSb[chip_select].CCCTL4 = __REV16(XSPI_OSPI_PRV_AUTOCALIBARION_PREAMBLE_PATTERN_0);
            p_instance_ctrl->p_reg->CSb[chip_select].CCCTL5 = __REV16(XSPI_OSPI_PRV_AUTOCALIBARION_PREAMBLE_PATTERN_1);
            p_instance_ctrl->p_reg->CSb[chip_select].CCCTL6 = __REV16(XSPI_OSPI_PRV_AUTOCALIBARION_PREAMBLE_PATTERN_2);
            p_instance_ctrl->p_reg->CSb[chip_select].CCCTL7 = __REV16(XSPI_OSPI_PRV_AUTOCALIBARION_PREAMBLE_PATTERN_3);
        }
        else
        {
            p_instance_ctrl->p_reg->CSb[chip_select].CCCTL4 = XSPI_OSPI_PRV_AUTOCALIBARION_PREAMBLE_PATTERN_0;
            p_instance_ctrl->p_reg->CSb[chip_select].CCCTL5 = XSPI_OSPI_PRV_AUTOCALIBARION_PREAMBLE_PATTERN_1;
            p_instance_ctrl->p_reg->CSb[chip_select].CCCTL6 = XSPI_OSPI_PRV_AUTOCALIBARION_PREAMBLE_PATTERN_2;
            p_instance_ctrl->p_reg->CSb[chip_select].CCCTL7 = XSPI_OSPI_PRV_AUTOCALIBARION_PREAMBLE_PATTERN_3;
        }

        p_instance_ctrl->p_reg->CSb[chip_select].CCCTL0 = (1 << XSPI_OSPI_PRV_CCCTL0_CANOWR_OFFSET) |
                                                          (0x1F << XSPI_OSPI_PRV_CCCTL0_CAITV_OFFSET) |
                                                          (0 << XSPI_OSPI_PRV_CCCTL0_CASFTSTA_OFFSET) |
                                                          (0x1F << XSPI_OSPI_PRV_CCCTL0_CASFTEND_OFFSET);

        /* Automatic Calibration Enable */
        p_instance_ctrl->p_reg->CSb[chip_select].CCCTL0_b.CAEN = 1;

        /* Check calibration success or failure. */
        while ((0 == ((p_instance_ctrl->p_reg->INTS >> (R_XSPI0_INTS_CASUCCS0_Pos + chip_select)) & 0x01)) &&
               (0 == ((p_instance_ctrl->p_reg->INTS >> (R_XSPI0_INTS_CAFAILCS0_Pos + chip_select)) & 0x01)))
        {
            /* Do nothing. */
        }

        /* Disable automatic calibration */
        p_instance_ctrl->p_reg->CSb[chip_select].CCCTL0_b.CAEN = 0;

        if (1 == ((p_instance_ctrl->p_reg->INTS >> (R_XSPI0_INTS_CASUCCS0_Pos + chip_select)) & 0x01))
        {
            /* Clear automatic calibration success status */
            p_instance_ctrl->p_reg->INTC = (uint32_t) 1 << (R_XSPI0_INTC_CASUCCS0C_Pos + chip_select);
        }
        else if (1 == ((p_instance_ctrl->p_reg->INTS >> (R_XSPI0_INTS_CAFAILCS0_Pos + chip_select)) & 0x01))
        {
            ret = FSP_ERR_CALIBRATE_FAILED;

            /* Clear automatic calibration failure status */
            p_instance_ctrl->p_reg->INTC = (uint32_t) 1 << (R_XSPI0_INTC_CAFAILCS0C_Pos + chip_select);
        }
        else
        {
            /* Do nothing. */
        }
    }

    return ret;
}

/*******************************************************************************************************************//**
 * Performs direct data transfer with the OctaFlash
 *
 * @param[in]   p_instance_ctrl    Pointer to OSPI specific control structure
 * @param[in]   p_transfer         Pointer to transfer parameters
 * @param[in]   direction          Read/Write
 **********************************************************************************************************************/
static void r_xspi_ospi_direct_transfer (xspi_ospi_instance_ctrl_t         * p_instance_ctrl,
                                         spi_flash_direct_transfer_t * const p_transfer,
                                         spi_flash_direct_transfer_dir_t     direction)
{
    xspi_ospi_extended_cfg_t * p_cfg_extend = (xspi_ospi_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    p_instance_ctrl->p_reg->CDCTL0_b.TRNUM = 0;

    /* Direct Read/Write settings
     * (see RZ microprocessor User's Manual section "Flow of Manual-command Procedure"). */
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->CDCTL0_b.TRREQ, 0);

    uint32_t cdtbuf0 =
        ((p_transfer->command_length & XSPI_OSPI_PRV_CDTBUF_CMDSIZE_VALUE_MASK) <<
            XSPI_OSPI_PRV_CDTBUF_CMDSIZE_OFFSET) |
        ((p_transfer->address_length & XSPI_OSPI_PRV_CDTBUF_ADDSIZE_VALUE_MASK) <<
            XSPI_OSPI_PRV_CDTBUF_ADDSIZE_OFFSET) |
        ((p_transfer->data_length & XSPI_OSPI_PRV_CDTBUF_DATASIZE_VALUE_MASK) <<
            XSPI_OSPI_PRV_CDTBUF_DATASIZE_OFFSET) |
        ((p_transfer->dummy_cycles & XSPI_OSPI_PRV_CDTBUF_LATE_VALUE_MASK) <<
            XSPI_OSPI_PRV_CDTBUF_LATE_OFFSET) |
        ((direction & XSPI_OSPI_PRV_CDTBUF_TRTYPE_VALUE_MASK) <<
            XSPI_OSPI_PRV_CDTBUF_TRTYPE_OFFSET);

    cdtbuf0 |= (1 == p_transfer->command_length) ?
               ((p_transfer->command & XSPI_OSPI_PRV_CDTBUF_CMD_1B_VALUE_MASK) <<
                XSPI_OSPI_PRV_CDTBUF_CMD_UPPER_OFFSET) :
               ((p_transfer->command & XSPI_OSPI_PRV_CDTBUF_CMD_2B_VALUE_MASK) << XSPI_OSPI_PRV_CDTBUF_CMD_OFFSET);

    p_instance_ctrl->p_reg->BUF[0].CDT = cdtbuf0;

    p_instance_ctrl->p_reg->BUF[0].CDA = p_transfer->address;

    if (SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE == direction)
    {
        if ((1U < p_transfer->data_length) &&
            (XSPI_OSPI_BYTE_ORDER_1032 == p_cfg_extend->byte_order) &&
            (SPI_FLASH_PROTOCOL_8D_8D_8D == p_instance_ctrl->spi_protocol))
        {
            /* Apply __REV16 to convert the data to match the OctaFlash byte order. */
            p_instance_ctrl->p_reg->BUF[0].CDD0 = __REV16(p_transfer->data);
        }
        else
        {
            p_instance_ctrl->p_reg->BUF[0].CDD0 = p_transfer->data;
        }
    }

    p_instance_ctrl->p_reg->CDCTL0_b.TRREQ = 1;
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->INTS_b.CMDCMP, 1);

    if (SPI_FLASH_DIRECT_TRANSFER_DIR_READ == direction)
    {
        if ((1U < p_transfer->data_length) &&
            (XSPI_OSPI_BYTE_ORDER_1032 == p_cfg_extend->byte_order) &&
            (SPI_FLASH_PROTOCOL_8D_8D_8D == p_instance_ctrl->spi_protocol))
        {
            /* Apply __REV16 to convert the data to match the OctaFlash byte order. */
            p_transfer->data = __REV16(p_instance_ctrl->p_reg->BUF[0].CDD0);
        }
        else
        {
            p_transfer->data = p_instance_ctrl->p_reg->BUF[0].CDD0;
        }
    }

    p_instance_ctrl->p_reg->INTC = 1 << XSPI_OSPI_PRV_INTC_CMDCMPC_OFFSET;
}
