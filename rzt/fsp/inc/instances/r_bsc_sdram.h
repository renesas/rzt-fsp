/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * @addtogroup BSC_SDRAM
 * @{
 **********************************************************************************************************************/
#ifndef R_BSC_SDRAM_H
#define R_BSC_SDRAM_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_bsc_sdram_cfg.h"
#include "r_sdram_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Callback function parameter data. */
typedef struct st_bsc_sdram_callback_args_t
{
    void const * p_context;            ///< Placeholder for user data.
} bsc_sdram_callback_args_t;

/** SDRAM chip select. */
typedef enum e_bsc_sdram_chip_select
{
    BSC_SDRAM_CHIP_SELECT_3 = 3,       ///< Device connected to Chip-Select 3
} bsc_sdram_chip_select_t;

/** Number of insertion idle cycle between access cycles */
typedef enum e_bsc_sdram_idle_cycle
{
    BSC_SDRAM_IDLE_CYCLE_0 = 0x0,      ///< No idle cycle insertion
    BSC_SDRAM_IDLE_CYCLE_1,            ///< 1 idle cycle insertion
    BSC_SDRAM_IDLE_CYCLE_2,            ///< 2 idle cycle insertion
    BSC_SDRAM_IDLE_CYCLE_4,            ///< 4 idle cycle insertion
    BSC_SDRAM_IDLE_CYCLE_6,            ///< 6 idle cycle insertion
    BSC_SDRAM_IDLE_CYCLE_8,            ///< 8 idle cycle insertion
    BSC_SDRAM_IDLE_CYCLE_10,           ///< 10 idle cycle insertion
    BSC_SDRAM_IDLE_CYCLE_12,           ///< 12 idle cycle insertion
} bsc_sdram_idle_cycle_t;

/** Specify SDRAM command */
typedef enum e_bsc_sdram_command
{
    BSC_SDRAM_COMMAND_AUTO_PRECHARGE_MODE = 0x00,
    BSC_SDRAM_COMMAND_BANK_ACTIVE_MODE,
} bsc_sdram_command_t;

/** Extended configuration. */
typedef struct st_bsc_sdram_extended_cfg
{
    bsc_sdram_chip_select_t chip_select; ///< Select which device to use

    /** Idle cycle between Read-Read cycles in the same CS space */
    bsc_sdram_idle_cycle_t r_r_same_space_idle_cycle;

    /** Idle cycle between Read-Read cycles in the different CS space */
    bsc_sdram_idle_cycle_t r_r_different_space_idle_cycle;

    /** Idle cycle between Read-Write cycles in the same CS space */
    bsc_sdram_idle_cycle_t r_w_same_space_idle_cycle;

    /** Idle cycle between Read-Write cycles in the different CS space */
    bsc_sdram_idle_cycle_t r_w_different_space_idle_cycle;

    /** Idle cycle between Write-Read cycles and Write-Write cycles */
    bsc_sdram_idle_cycle_t w_r_w_w_idle_cycle;

    /** Auto-precharge mode (using READA/WRITA commands) or Bank active mode (using READ/WRIT commands) */
    bsc_sdram_command_t command_mode;

    uint8_t   cmi_ipl;                 ///< SDRAM refresh compare match interrupt
    IRQn_Type cmi_irq;                 ///< SDRAM refresh compare match interrupt priority

    /** Callback for SDRAM refresh compare match. */
    void (* p_callback)(bsc_sdram_callback_args_t * p_args);

    /** Placeholder for user data.  Passed to the user callback in @ref bsc_sdram_callback_args_t. */
    void const * p_context;
} bsc_sdram_extended_cfg_t;

/** Instance control block. DO NOT INITIALIZE.  Initialization occurs when @ref sdram_api_t::open is called */
typedef struct st_bsc_sdram_instance_ctrl
{
    uint32_t            open;                         // Whether or not driver is open
    sdram_cfg_t const * p_cfg;                        // Pointer to initial configuration

    void (* p_callback)(bsc_sdram_callback_args_t *); // Pointer to callback that is called when a timer_event_t occurs.
    void const * p_context;                           // Pointer to context to be passed into callback function
} bsc_sdram_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const sdram_api_t g_sdram_on_bsc_sdram;

/** @endcond */

fsp_err_t R_BSC_SDRAM_Open(sdram_ctrl_t * p_ctrl, sdram_cfg_t const * const p_cfg);
fsp_err_t R_BSC_SDRAM_SelfRefreshEnter(sdram_ctrl_t * p_ctrl);
fsp_err_t R_BSC_SDRAM_SelfRefreshExit(sdram_ctrl_t * p_ctrl);
fsp_err_t R_BSC_SDRAM_PowerDownEnter(sdram_ctrl_t * p_ctrl);
fsp_err_t R_BSC_SDRAM_PowerDownExit(sdram_ctrl_t * p_ctrl);
fsp_err_t R_BSC_SDRAM_Close(sdram_ctrl_t * p_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup BSC_SDRAM)
 **********************************************************************************************************************/
