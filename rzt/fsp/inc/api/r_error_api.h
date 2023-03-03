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
 * @defgroup ERROR_API ERROR Interface
 * @brief Interface for the ERROR event handling.
 *
 * Defines the API and data structures for the ERROR event handling implementation of the ERROR interface.
 *
 * @section ERROR_API_SUMMARY Summary
 * @brief The ERROR API provides an interface for error event handling.
 *
 * Implemented by:
 * @ref ICU_ERROR
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_ERROR_API_H
#define R_ERROR_API_H

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

/** Callback function parameter data. */
typedef struct st_error_callback_args
{
    void const * p_context;            ///< Placeholder for user data.
    ///< Set in @ref error_api_t::open function in @ref error_cfg_t.

    uint32_t error_source;             ///< Error source.
    uint32_t error_event;              ///< Error event.
} error_callback_args_t;

/** ERROR control block.  Allocate an instance specific control block to pass into the ERROR API calls.
 * @par Implemented as
 * - icu_error_instance_ctrl_t
 */
typedef void error_ctrl_t;

/** User configuration structure, used in the open function. */
typedef struct st_error_cfg
{
    /** Callback provided when a ERROR ISR occurs. */
    void (* p_callback)(error_callback_args_t * p_args);

    /** Placeholder for user data. Passed to the user callback in @ref error_callback_args_t. */
    void const * p_context;

    /** Pointer to ERROR peripheral specific configuration */
    void const * p_extend;             ///< ERROR event hardware dependent configuration
} error_cfg_t;

/** ERROR API structure. ERROR functions implemented at the HAL layer will follow this API. */
typedef struct st_error_api
{
    /** Initial configuration.
     * @par Implemented as
     * - @ref R_ICU_ERROR_Open()
     * @param[in]   p_ctrl      Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg       Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(error_ctrl_t * const p_ctrl, error_cfg_t const * const p_cfg);

    /** Disable the associated interrupts.
     * @par Implemented as
     * - @ref R_ICU_ERROR_Close()
     * @param[in]   p_ctrl      Control block set in @ref error_api_t::open call.
     */
    fsp_err_t (* close)(error_ctrl_t * const p_ctrl);

    /** Get the status of error events.
     * @par Implemented as
     * - @ref R_ICU_ERROR_StatusGet()
     * @param[in]   p_ctrl      Control block set in @ref error_api_t::open call.
     * @param[in]   source      Select error source.
     * @param[out]  p_status    Collection of error status.
     */
    fsp_err_t (* statusGet)(error_ctrl_t * const p_ctrl, uint32_t source, uint32_t * p_status);

    /** Clear the status of error events.
     * @par Implemented as
     * - @ref R_ICU_ERROR_StatusClear()
     *
     * @param[in]   p_ctrl      Control block set in @ref error_api_t::open call.
     * @param[in]   source      Select error source.
     * @param[in]   data        Event information to be cleared.
     */
    fsp_err_t (* statusClear)(error_ctrl_t * const p_ctrl, uint32_t source, uint32_t event);

    /** Specify callback function and optional context pointer and working memory pointer.
     * @par Implemented as
     * - R_ICU_ERROR_CallbackSet()
     *
     * @param[in]   p_ctrl                   Control block set in @ref error_api_t::open call.
     * @param[in]   p_callback               Callback function to register
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(error_ctrl_t * const p_api_ctrl, void (* p_callback)(error_callback_args_t *),
                              void const * const p_context, error_callback_args_t * const p_callback_memory);
} error_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_error_instance
{
    error_ctrl_t      * p_ctrl;        ///< Pointer to the control structure for this instance
    error_cfg_t const * p_cfg;         ///< Pointer to the configuration structure for this instance
    error_api_t const * p_api;         ///< Pointer to the API structure for this instance
} error_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup ERROR_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
