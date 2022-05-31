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

#ifndef R_SHARED_MEMORY_API_H
#define R_SHARED_MEMORY_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup SHARED_MEMORY_API Shared Memory Interface
 * @brief Interface for Shared Memory.
 *
 * @section SHARED_MEMORY_API_Summary Summary
 * The SHARED_MEMORY interface provides Shared Memory functionality.
 *
 * The SHARED_MEMORY Interface can be implemented by:
 * - @ref SHARED_MEMORY
 *
 * @{
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
#define SHARED_MEMORY_API_VERSION_MAJOR    (1U)
#define SHARED_MEMORY_API_VERSION_MINOR    (0U)

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/** States of SHARED_MEMORY module **/
typedef enum e_shared_memory_state
{
    SHARED_MEMORY_STATE_NOT_READY,           ///< This driver has been opened. But the oppsite driver has not
    SHARED_MEMORY_STATE_READY_TO_WRITE,      ///< This driver can write data
    SHARED_MEMORY_STATE_READY_TO_READ_WRITE, ///< This driver can write and read data
} shared_memory_state_t;

/** SHARED_MEMORY callback parameter definition */
typedef struct st_shared_memory_callback_args
{
    void const          * p_context;   ///< Pointer to user-provided context
    shared_memory_state_t state;       ///< Connection status with the communication partner
} shared_memory_callback_args_t;

/** SHARED_MEMORY status indicators */
typedef struct st_shared_memory_status
{
    shared_memory_state_t state;       ///< State of this driver
} shared_memory_status_t;

/** SHARED_MEMORY configuration block */
typedef struct st_shared_memory_cfg
{
    /** Generic configuration */
    uint8_t   semaphore_reg;                                     ///< Identifier recognizable by implementation
    uint8_t * p_memory;                                          ///< Start address of shared memory region
    uint32_t  memory_size;                                       ///< Size of shared memory area in bytes

    /** Parameters to control software behavior */
    void (* p_callback)(shared_memory_callback_args_t * p_args); ///< Pointer to callback function
    void const * p_context;                                      ///< Pointer to the user-provided context

    /** Extended configuration */
    void const * p_extend;                                       ///< Extended configuration of hardware dependent
} shared_memory_cfg_t;

/** SHARED_MEMORY control block.  Allocate an instance specific control block to pass into the SHARED_MEMORY API calls.
 * @par Implemented as
 * - shared_memory_instance_ctrl_t
 */
typedef void shared_memory_ctrl_t;

/** Interface definition for inter-core data access via inter-core shared memory */
typedef struct st_shared_memory_api
{
    /** Opens the shared memory driver and initializes the hardware.
     * @par Implemented as
     * - @ref R_SHARED_MEMORY_Open()
     *
     * @param[in] p_ctrl    Pointer to control block. Must be declared by user. Elements are set here.
     * @param[in] p_cfg     Pointer to configuration structure.
     */
    fsp_err_t (* open)(shared_memory_ctrl_t * const p_ctrl, shared_memory_cfg_t const * const p_cfg);

    /** Performs a read operation from inter-core shared memory.
     * @par Implemented as
     * - @ref R_SHARED_MEMORY_Read()
     *
     * @param[in]  p_ctrl   Pointer to control block set in @ref shared_memory_api_t::open call.
     * @param[out] p_dest   Pointer to the location to store read data.
     * @param[in]  offset   Offset position from the start address of the shared memory to read (bytes).
     * @param[in]  bytes    Number of bytes to read.
     */
    fsp_err_t (* read)(shared_memory_ctrl_t * const p_ctrl, uint8_t * const p_dest, uint32_t const offset,
                       uint32_t const bytes);

    /** Performs a write operation to inter-core shared memory.
     * @par Implemented as
     * - @ref R_SHARED_MEMORY_Write()
     *
     * @param[in] p_ctrl    Pointer to control block set in @ref shared_memory_api_t::open call.
     * @param[in] p_src     Pointer to the location to get write data from.
     * @param[in] offset    Offset position from the start address of the shared memory to write (bytes).
     * @param[in] bytes     Number of bytes to write.
     */
    fsp_err_t (* write)(shared_memory_ctrl_t * const p_ctrl, uint8_t * const p_src, uint32_t const offset,
                        uint32_t const bytes);

    /** Gets the status of the shared memory.
     * @par Implemented as
     * - @ref R_SHARED_MEMORY_StatusGet()
     *
     * @param[in]  p_ctrl    Pointer to control block set in @ref shared_memory_api_t::open call.
     * @param[out] p_status  Pointer to store current status.
     */
    fsp_err_t (* statusGet)(shared_memory_ctrl_t * const p_ctrl, shared_memory_status_t * p_status);

    /** Closes the driver and releases the device.
     * @par Implemented as
     * - @ref R_SHARED_MEMORY_Close()
     *
     * @param[in] p_ctrl    Pointer to control block set in @ref shared_memory_api_t::open call.
     */
    fsp_err_t (* close)(shared_memory_ctrl_t * const p_ctrl);
} shared_memory_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_shared_memory_instance
{
    shared_memory_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    shared_memory_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    shared_memory_api_t const * p_api;  ///< Pointer to the API structure for this instance
} shared_memory_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup SHARED_MEMORY_API)
 ***********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_SHARED_MEMORY_H
