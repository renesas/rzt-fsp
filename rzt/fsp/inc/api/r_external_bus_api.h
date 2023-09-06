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
 * @defgroup EXTERNAL_BUS_API External Bus Interface
 * @brief Interface for external bus communication.
 *
 * @section EXTERNAL_BUS_API_SUMMARY Summary
 * The External bus interface provides APIs and definitions for external bus communication.
 *
 * Implemented by:
 * - @ref BSC
 * @{
 **********************************************************************************************************************/
#ifndef R_EXTERNAL_BUS_API_H
#define R_EXTERNAL_BUS_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

#define EXTERNAL_BUS_API_VERSION_MAJOR    (1U) // DEPRECATED
#define EXTERNAL_BUS_API_VERSION_MINOR    (2U) // DEPRECATED

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** External bus chip select. */
typedef enum e_external_bus_chip_select
{
    EXTERNAL_BUS_CHIP_SELECT_0 = 0x00, ///< Device connected to Chip-Select 0
    EXTERNAL_BUS_CHIP_SELECT_1,        ///< Device connected to Chip-Select 1
    EXTERNAL_BUS_CHIP_SELECT_2,        ///< Device connected to Chip-Select 2
    EXTERNAL_BUS_CHIP_SELECT_3,        ///< Device connected to Chip-Select 3
    EXTERNAL_BUS_CHIP_SELECT_4,        ///< Device connected to Chip-Select 4
    EXTERNAL_BUS_CHIP_SELECT_5,        ///< Device connected to Chip-Select 5
    EXTERNAL_BUS_CHIP_SELECT_6,        ///< Device connected to Chip-Select 6
    EXTERNAL_BUS_CHIP_SELECT_7,        ///< Device connected to Chip-Select 7
} external_bus_chip_select_t;

/** External bus data bus width. */
typedef enum e_external_bus_data_bus_width
{
    EXTERNAL_BUS_DATA_BUS_WIDTH_8BIT  = 0x01, ///< Data bus width 8bit
    EXTERNAL_BUS_DATA_BUS_WIDTH_16BIT = 0x02, ///< Data bus width 16bit
    EXTERNAL_BUS_DATA_BUS_WIDTH_32BIT = 0x03, ///< Data bus width 32bit
} external_bus_data_bus_width_t;

/** External wait function configuration. */
typedef enum e_external_bus_external_wait
{
    EXTERNAL_BUS_EXTERNAL_WAIT_ENABLE  = 0, ///< Enable external wait function
    EXTERNAL_BUS_EXTERNAL_WAIT_DISABLE = 1, ///< Disable external wait function
} external_bus_external_wait_t;

/** External bus configuration */
typedef struct st_external_bus_cfg
{
    external_bus_chip_select_t    chip_select;     ///< Select which device to use
    external_bus_data_bus_width_t data_width;      ///< Select data bus width

    external_bus_external_wait_t external_wait_en; ///< External wait function setting

    void const * p_extend;                         ///< External bus hardware dependent configuration
} external_bus_cfg_t;

/** External bus control block.  Allocate an instance specific control block to pass into the External bus API calls.
 * @par Implemented as
 * - bsc_instance_ctrl_t
 */
typedef void external_bus_ctrl_t;

/** External bus implementations follow this API. */
typedef struct st_external_bus_api
{
    /** Open the External bus driver module.
     * @par Implemented as
     * - @ref R_BSC_Open()
     *
     * @param[in] p_ctrl               Pointer to a driver handle
     * @param[in] p_cfg                Pointer to a configuration structure
     **/
    fsp_err_t (* open)(external_bus_ctrl_t * p_ctrl, external_bus_cfg_t const * const p_cfg);

    /** Close the External bus driver module.
     * @par Implemented as
     * - @ref R_BSC_Close()
     *
     * @param[in] p_ctrl               Pointer to a driver handle
     **/
    fsp_err_t (* close)(external_bus_ctrl_t * p_ctrl);
} external_bus_api_t;

typedef struct st_external_bus_instance
{
    external_bus_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    external_bus_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    external_bus_api_t const * p_api;  ///< Pointer to the API structure for this instance
} external_bus_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end addtogroup EXTERNAL_BUS_API)
 **********************************************************************************************************************/
