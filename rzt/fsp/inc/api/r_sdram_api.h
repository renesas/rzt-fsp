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
 * @ingroup RENESAS_INTERFACES
 * @defgroup SDRAM_API SDRAM Interface
 * @brief Interface for external sdram communication.
 *
 * @section SDRAM_API_SUMMARY Summary
 * The SDRAM interface provides APIs and definitions for SDRAM communication.
 *
 * Implemented by:
 * - @ref BSC_SDRAM
 * @{
 **********************************************************************************************************************/
#ifndef SDRAM_H
#define SDRAM_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** NOR Flash chip select. */
typedef enum e_sdram_chip_select
{
    SDRAM_CHIP_SELECT_0 = 0x00,        ///< Device connected to Chip-Select 0
    SDRAM_CHIP_SELECT_1,               ///< Device connected to Chip-Select 1
    SDRAM_CHIP_SELECT_2,               ///< Device connected to Chip-Select 2
    SDRAM_CHIP_SELECT_3,               ///< Device connected to Chip-Select 3
    SDRAM_CHIP_SELECT_4,               ///< Device connected to Chip-Select 4
    SDRAM_CHIP_SELECT_5,               ///< Device connected to Chip-Select 5
    SDRAM_CHIP_SELECT_6,               ///< Device connected to Chip-Select 6
    SDRAM_CHIP_SELECT_7,               ///< Device connected to Chip-Select 7
} sdram_chip_select_t;

/** SDRAM data bus width. */
typedef enum e_sdram_data_bus_width
{
    SDRAM_DATA_BUS_WIDTH_8BIT  = 0x01, ///< Data bus width 8bit
    SDRAM_DATA_BUS_WIDTH_16BIT = 0x02, ///< Data bus width 16bit
    SDRAM_DATA_BUS_WIDTH_32BIT = 0x03, ///< Data bus width 32bit
} sdram_data_bus_width_t;

/** SDRAM wait cycle. */
typedef enum e_sdram_wait_cycle
{
    SDRAM_WAIT_CYCLE_0 = 0x00,
    SDRAM_WAIT_CYCLE_1 = 0x01,
    SDRAM_WAIT_CYCLE_2 = 0x02,
    SDRAM_WAIT_CYCLE_3 = 0x03,
    SDRAM_WAIT_CYCLE_4 = 0x04,
    SDRAM_WAIT_CYCLE_5 = 0x05,
    SDRAM_WAIT_CYCLE_6 = 0x06,
    SDRAM_WAIT_CYCLE_7 = 0x07,
    SDRAM_WAIT_CYCLE_8 = 0x08,
} sdram_wait_cycle_t;

/** Number of bits of SDRAM Row/Column address. */
typedef enum e_sdram_address_width
{
    SDRAM_ADDRESS_BUS_WIDTH_8_BITS  = 0x0,
    SDRAM_ADDRESS_BUS_WIDTH_9_BITS  = 0x1,
    SDRAM_ADDRESS_BUS_WIDTH_10_BITS = 0x2,
    SDRAM_ADDRESS_BUS_WIDTH_11_BITS = 0x3,
    SDRAM_ADDRESS_BUS_WIDTH_12_BITS = 0x4,
    SDRAM_ADDRESS_BUS_WIDTH_13_BITS = 0x5,
} sdram_address_bus_width_t;

/** Write burst mode */
typedef enum e_sdram_write_burst_mode
{
    SDRAM_WRITE_BURST_MODE_BURST_READ_BURST_WRITE  = 0x0U,
    SDRAM_WRITE_BURST_MODE_BURST_READ_SINGLE_WRITE = 0x01U,
} sdram_write_burst_mode;

/** SDRAM configuration */
typedef struct st_sdram_cfg
{
    sdram_chip_select_t    chip_select;             ///< Select which device to use
    sdram_data_bus_width_t data_width;              ///< Select data bus width

    sdram_address_bus_width_t row_address_width;    ///< Number of bits of SDRAM Row address
    sdram_address_bus_width_t column_address_width; ///< Number of bits of SDRAM Column address

    sdram_wait_cycle_t ras_precharge_cycle;         ///< Cycle between PRECHARGE and ACTIVE command (tRP)
    sdram_wait_cycle_t ras_to_cas_delay_cycle;      ///< Cycle between ACTIVE and READ/WRITE command (tRCD)
    sdram_wait_cycle_t cas_latency;                 ///< CAS Latency cycle (tCL)
    sdram_wait_cycle_t write_recovery_cycle;        ///< Cycle between Data In and PRECHARGE command (tWR)
    sdram_wait_cycle_t row_cycle;                   ///< Cycle between REFRESH/ACTIVE and REFRESH/ACTIVE command (tRC)

    uint32_t auto_refresh_cycle;                    ///< Auto-Refresh cycle time (ms)

    uint32_t refresh_request_count;                 ///< The number of continuous refresh cycles

    /** Select Burst Read / Burst Write or Burst Read / Single Write in MRS */
    sdram_write_burst_mode write_burst_mode;

    void const * p_extend;             ///< SDRAM hardware dependent configuration
} sdram_cfg_t;

/** SDRAM control block.  Allocate an instance specific control block to pass into the SDRAM API calls.
 * @par Implemented as
 * - bsc_instance_ctrl_t
 */
typedef void sdram_ctrl_t;

/** SDRAM implementations follow this API. */
typedef struct st_sdram_api
{
    /** Open the SDRAM driver module.
     * @par Implemented as
     * - @ref R_BSC_SDRAM_Open()
     *
     * @param[in] p_ctrl               Pointer to a driver handle
     * @param[in] p_cfg                Pointer to a configuration structure
     **/
    fsp_err_t (* open)(sdram_ctrl_t * p_ctrl, sdram_cfg_t const * const p_cfg);

    /** Enter Self Refresh mode.
     * @par Implemented as
     * - @ref R_BSC_SDRAM_SelfRefreshEnter()
     *
     * @param[in] p_ctrl               Pointer to a driver handle
     **/
    fsp_err_t (* selfRefreshEnter)(sdram_ctrl_t * p_ctrl);

    /** Exit Self Refresh mode.
     * @par Implemented as
     * - @ref R_BSC_SDRAM_SelfRefreshExit()
     *
     * @param[in] p_ctrl               Pointer to a driver handle
     **/
    fsp_err_t (* selfRefreshExit)(sdram_ctrl_t * p_ctrl);

    /** Enter Power Down mode.
     * @par Implemented as
     * - @ref R_BSC_SDRAM_PowerDownEnter()
     *
     * @param[in] p_ctrl               Pointer to a driver handle
     **/
    fsp_err_t (* powerDownEnter)(sdram_ctrl_t * p_ctrl);

    /** Exit Power Down mode.
     * @par Implemented as
     * - @ref R_BSC_SDRAM_PowerDownExit()
     *
     * @param[in] p_ctrl               Pointer to a driver handle
     **/
    fsp_err_t (* powerDownExit)(sdram_ctrl_t * p_ctrl);

    /** Close the SDRAM driver module.
     * @par Implemented as
     * - @ref R_BSC_SDRAM_Close()
     *
     * @param[in] p_ctrl               Pointer to a driver handle
     **/
    fsp_err_t (* close)(sdram_ctrl_t * p_ctrl);
} sdram_api_t;

typedef struct st_sdram_instance
{
    sdram_ctrl_t      * p_ctrl;        ///< Pointer to the control structure for this instance
    sdram_cfg_t const * p_cfg;         ///< Pointer to the configuration structure for this instance
    sdram_api_t const * p_api;         ///< Pointer to the API structure for this instance
} sdram_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/******************************************************************************************************************//**
 * @} (end addtogroup SDRAM_API)
 **********************************************************************************************************************/
