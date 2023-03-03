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

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_gpt_phase_count.h"
#include "r_gpt_phase_count_cfg.h"

#include "r_gpt.h"
#include "r_gpt_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "GPT3" in ASCII, used to determine if channel is open. */
#define GPT_PHASE_COUNT_OPEN                       (0x47505433ULL)

#define GPT_PHASE_COUNT_PRV_GTWP_RESET_VALUE       (0xA500U)
#define GPT_PHASE_COUNT_PRV_GTWP_WRITE_PROTECT     (0xA51FU)

#define GPT_PHASE_COUNT_PRV_GTBER_SINGLE_BUFFER    (0x50000U)
#define GPT_PHASE_COUNT_PRV_GTBER_DOUBLE_BUFFER    (0xA0000U)

#define GPT_PHASE_COUNTING_MODE_1_UP               (0x00006900U)
#define GPT_PHASE_COUNTING_MODE_1_DN               (0x00009600U)
#define GPT_PHASE_COUNTING_MODE_200_UP             (0x00000800U)
#define GPT_PHASE_COUNTING_MODE_200_DN             (0x00000400U)
#define GPT_PHASE_COUNTING_MODE_201_UP             (0x00000200U)
#define GPT_PHASE_COUNTING_MODE_201_DN             (0x00000100U)
#define GPT_PHASE_COUNTING_MODE_210_UP             (0x00000A00U)
#define GPT_PHASE_COUNTING_MODE_210_DN             (0x00000500U)
#define GPT_PHASE_COUNTING_MODE_300_UP             (0x00000800U)
#define GPT_PHASE_COUNTING_MODE_300_DN             (0x00008000U)
#define GPT_PHASE_COUNTING_MODE_301_UP             (0x00000200U)
#define GPT_PHASE_COUNTING_MODE_301_DN             (0x00002000U)
#define GPT_PHASE_COUNTING_MODE_310_UP             (0x00000A00U)
#define GPT_PHASE_COUNTING_MODE_310_DN             (0x0000A000U)
#define GPT_PHASE_COUNTING_MODE_4_UP               (0x00006000U)
#define GPT_PHASE_COUNTING_MODE_4_DN               (0x00009000U)
#define GPT_PHASE_COUNTING_MODE_50_UP              (0x00000C00U)
#define GPT_PHASE_COUNTING_MODE_50_DN              (0x00000000U)
#define GPT_PHASE_COUNTING_MODE_51_UP              (0x0000C000U)
#define GPT_PHASE_COUNTING_MODE_51_DN              (0x00000000U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
enum e_gpt_phase_count_prv_gtccr
{
    GPT_PHASE_COUNT_PRV_GTCCRA = 0U,
    GPT_PHASE_COUNT_PRV_GTCCRB,
    GPT_PHASE_COUNT_PRV_GTCCRC,
    GPT_PHASE_COUNT_PRV_GTCCRE,
    GPT_PHASE_COUNT_PRV_GTCCRD,
    GPT_PHASE_COUNT_PRV_GTCCRF
};

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static inline void r_gpt_write_protect_enable(gpt_phase_count_instance_ctrl_t * const p_instance_ctrl);
static inline void r_gpt_write_protect_disable(gpt_phase_count_instance_ctrl_t * const p_instance_ctrl);

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Version data structure used by error logger macro. */
static const fsp_version_t g_gpt_phase_count_version =
{
    .api_version_minor  = GPT_PHASE_COUNT_API_VERSION_MINOR,
    .api_version_major  = GPT_PHASE_COUNT_API_VERSION_MAJOR,
    .code_version_major = GPT_PHASE_COUNT_CODE_VERSION_MAJOR,
    .code_version_minor = GPT_PHASE_COUNT_CODE_VERSION_MINOR
};

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* Implementation of GPT_PHASE_COUNT interface  */
const gpt_phase_count_api_t g_gpt_phase_count_on_gpt_phase_count =
{
    .open        = R_GPT_PHASE_COUNT_Open,
    .stop        = R_GPT_PHASE_COUNT_Stop,
    .start       = R_GPT_PHASE_COUNT_Start,
    .reset       = R_GPT_PHASE_COUNT_Reset,
    .set         = R_GPT_PHASE_COUNT_PositionSet,
    .get         = R_GPT_PHASE_COUNT_PositionGet,
    .callbackSet = R_GPT_PHASE_COUNT_CallbackSet,
    .close       = R_GPT_PHASE_COUNT_Close,
    .versionGet  = R_GPT_PHASE_COUNT_VersionGet
};

/*******************************************************************************************************************//**
 * @addtogroup GPT_PHASE_COUNT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes the phase_count timer module (and associated timers) and applies configurations. Implements
 * @ref gpt_phase_count_api_t::open.
 *
 * Example:
 * @snippet r_gpt_phase_count_example.c R_GPT_PHASE_COUNT_Open
 *
 * @retval FSP_SUCCESS                    Initialization was successful.
 * @retval FSP_ERR_ASSERTION              A required input pointer is NULL.
 * @retval FSP_ERR_ALREADY_OPEN           Module is already open.
 **********************************************************************************************************************/
fsp_err_t R_GPT_PHASE_COUNT_Open (gpt_phase_count_ctrl_t * const p_ctrl, gpt_phase_count_cfg_t const * const p_cfg)
{
    gpt_phase_count_instance_ctrl_t * p_instance_ctrl = (gpt_phase_count_instance_ctrl_t *) p_ctrl;
#if GPT_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_PHASE_COUNT_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    fsp_err_t err;

    /* Open all GPT submodules */
    err = R_GPT_Open(p_cfg->p_timer_instance->p_ctrl, p_cfg->p_timer_instance->p_cfg);
#if GPT_CFG_PARAM_CHECKING_ENABLE
    if (err)
    {
        /* In case of an error on GPT open, close all opened instances and return the error */
        R_GPT_Close(p_cfg->p_timer_instance->p_ctrl);

        return err;
    }

#else
    FSP_PARAMETER_NOT_USED(err);
#endif

    /* Save a pointer to the GPT registers for this channel */
    p_instance_ctrl->p_reg = ((gpt_instance_ctrl_t *) (p_cfg->p_timer_instance->p_ctrl))->p_reg;

#if GPT_CFG_WRITE_PROTECT_ENABLE

    /* Disable write protection on the current GPT channel */
    p_instance_ctrl->p_reg->GTWP = GPT_PHASE_COUNT_PRV_GTWP_RESET_VALUE;
#endif

#if GPT_CFG_WRITE_PROTECT_ENABLE

    /* Re-enable write protection */
    p_instance_ctrl->p_reg->GTWP = GPT_PHASE_COUNT_PRV_GTWP_WRITE_PROTECT;
#endif

    /* Get copy of GPT channel mask and buffer mode */
    p_instance_ctrl->channel_mask = ((gpt_instance_ctrl_t *) (p_cfg->p_timer_instance->p_ctrl))->channel_mask;

    /* Save pointer to config struct */
    p_instance_ctrl->p_cfg = p_cfg;

    r_gpt_write_protect_disable(p_instance_ctrl);

    /* Configure the up/down count mode. These are not affected by enable/disable. */
    switch (p_cfg->counting_mode)
    {
        case GPT_PHASE_COUNTING_MODE_1:
        {
            p_instance_ctrl->p_reg->GTUPSR = GPT_PHASE_COUNTING_MODE_1_UP;
            p_instance_ctrl->p_reg->GTDNSR = GPT_PHASE_COUNTING_MODE_1_DN;
            break;
        }

        case GPT_PHASE_COUNTING_MODE_200:
        {
            p_instance_ctrl->p_reg->GTUPSR = GPT_PHASE_COUNTING_MODE_200_UP;
            p_instance_ctrl->p_reg->GTDNSR = GPT_PHASE_COUNTING_MODE_200_DN;
            break;
        }

        case GPT_PHASE_COUNTING_MODE_201:
        {
            p_instance_ctrl->p_reg->GTUPSR = GPT_PHASE_COUNTING_MODE_201_UP;
            p_instance_ctrl->p_reg->GTDNSR = GPT_PHASE_COUNTING_MODE_201_DN;
            break;
        }

        case GPT_PHASE_COUNTING_MODE_210:
        {
            p_instance_ctrl->p_reg->GTUPSR = GPT_PHASE_COUNTING_MODE_210_UP;
            p_instance_ctrl->p_reg->GTDNSR = GPT_PHASE_COUNTING_MODE_210_DN;
            break;
        }

        case GPT_PHASE_COUNTING_MODE_300:
        {
            p_instance_ctrl->p_reg->GTUPSR = GPT_PHASE_COUNTING_MODE_300_UP;
            p_instance_ctrl->p_reg->GTDNSR = GPT_PHASE_COUNTING_MODE_300_DN;
            break;
        }

        case GPT_PHASE_COUNTING_MODE_301:
        {
            p_instance_ctrl->p_reg->GTUPSR = GPT_PHASE_COUNTING_MODE_301_UP;
            p_instance_ctrl->p_reg->GTDNSR = GPT_PHASE_COUNTING_MODE_301_DN;
            break;
        }

        case GPT_PHASE_COUNTING_MODE_310:
        {
            p_instance_ctrl->p_reg->GTUPSR = GPT_PHASE_COUNTING_MODE_310_UP;
            p_instance_ctrl->p_reg->GTDNSR = GPT_PHASE_COUNTING_MODE_310_DN;
            break;
        }

        case GPT_PHASE_COUNTING_MODE_4:
        {
            p_instance_ctrl->p_reg->GTUPSR = GPT_PHASE_COUNTING_MODE_4_UP;
            p_instance_ctrl->p_reg->GTDNSR = GPT_PHASE_COUNTING_MODE_4_DN;
            break;
        }

        case GPT_PHASE_COUNTING_MODE_50:
        {
            p_instance_ctrl->p_reg->GTUPSR = GPT_PHASE_COUNTING_MODE_50_UP;
            p_instance_ctrl->p_reg->GTDNSR = GPT_PHASE_COUNTING_MODE_50_DN;
            break;
        }

        case GPT_PHASE_COUNTING_MODE_51:
        {
            p_instance_ctrl->p_reg->GTUPSR = GPT_PHASE_COUNTING_MODE_51_UP;
            p_instance_ctrl->p_reg->GTDNSR = GPT_PHASE_COUNTING_MODE_51_DN;
            break;
        }

        default:
        {
            break;
        }
    }

    p_instance_ctrl->p_reg->GTPR = p_cfg->period_counts - 1U;

    r_gpt_write_protect_enable(p_instance_ctrl);

    p_instance_ctrl->open = GPT_PHASE_COUNT_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops all timers synchronously. Implements @ref gpt_phase_count_api_t::stop.
 *
 * @retval FSP_SUCCESS                 Timers successfully stopped.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_PHASE_COUNT_Stop (gpt_phase_count_ctrl_t * const p_ctrl)
{
    gpt_phase_count_instance_ctrl_t * p_instance_ctrl = (gpt_phase_count_instance_ctrl_t *) p_ctrl;
#if GPT_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_PHASE_COUNT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Stop timer */
    p_instance_ctrl->p_reg->GTSTP = p_instance_ctrl->channel_mask;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Starts all timers synchronously. Implements @ref gpt_phase_count_api_t::start.
 *
 * Example:
 * @snippet r_gpt_phase_count_example.c R_GPT_PHASE_COUNT_Start
 *
 * @retval FSP_SUCCESS                 Timers successfully started.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_PHASE_COUNT_Start (gpt_phase_count_ctrl_t * const p_ctrl)
{
    gpt_phase_count_instance_ctrl_t * p_instance_ctrl = (gpt_phase_count_instance_ctrl_t *) p_ctrl;
#if GPT_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_PHASE_COUNT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Start timer */
    p_instance_ctrl->p_reg->GTSTR = p_instance_ctrl->channel_mask;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Resets the counter values to 0. Implements @ref gpt_phase_count_api_t::reset.
 *
 * @retval FSP_SUCCESS                 Counters were reset successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_PHASE_COUNT_Reset (gpt_phase_count_ctrl_t * const p_ctrl)
{
    gpt_phase_count_instance_ctrl_t * p_instance_ctrl = (gpt_phase_count_instance_ctrl_t *) p_ctrl;
#if GPT_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_PHASE_COUNT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear timer counter. */
    p_instance_ctrl->p_reg->GTCLR = p_instance_ctrl->channel_mask;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Change the location information (Phase Count).
 *
 * Set the GPT count value.
 *
 * @retval FSP_SUCCESS                 Duty cycle updated successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_PHASE_COUNT_PositionSet (gpt_phase_count_ctrl_t * const p_ctrl, uint32_t position)
{
    gpt_phase_count_instance_ctrl_t * p_instance_ctrl = (gpt_phase_count_instance_ctrl_t *) p_ctrl;
#if GPT_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_PHASE_COUNT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    r_gpt_write_protect_disable(p_instance_ctrl);

    /* Set a value in the GTCNT register.  */
    p_instance_ctrl->p_reg->GTCNT = position;

    r_gpt_write_protect_enable(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get location information (Phase Count).
 *
 * Get the GPT count value.
 *
 * @retval FSP_SUCCESS                 Duty cycle updated successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_PHASE_COUNT_PositionGet (gpt_phase_count_ctrl_t * const p_ctrl, uint32_t * p_position)
{
    gpt_phase_count_instance_ctrl_t * p_instance_ctrl = (gpt_phase_count_instance_ctrl_t *) p_ctrl;
#if GPT_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_position);
    FSP_ERROR_RETURN(GPT_PHASE_COUNT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Get a value in the GTCNT register. */
    *p_position = p_instance_ctrl->p_reg->GTCNT;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback for the GPT channel with the option to provide memory for the callback argument
 * structure.
 * Implements @ref gpt_phase_count_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_PHASE_COUNT_CallbackSet (gpt_phase_count_ctrl_t * const p_ctrl,
                                         void (                       * p_callback)(timer_callback_args_t *),
                                         void const * const             p_context,
                                         timer_callback_args_t * const  p_callback_memory)
{
    gpt_phase_count_instance_ctrl_t * p_instance_ctrl = (gpt_phase_count_instance_ctrl_t *) p_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if GPT_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_callback);
    FSP_ERROR_RETURN(GPT_PHASE_COUNT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    err = R_GPT_CallbackSet(p_instance_ctrl->p_cfg->p_timer_instance->p_ctrl, p_callback, p_context, p_callback_memory);

    return err;
}

/*******************************************************************************************************************//**
 * Stops counters, disables output pins, and clears internal driver data. Implements @ref gpt_phase_count_api_t::close.
 *
 * @retval FSP_SUCCESS                 Successful close.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_PHASE_COUNT_Close (gpt_phase_count_ctrl_t * const p_ctrl)
{
    gpt_phase_count_instance_ctrl_t * p_instance_ctrl = (gpt_phase_count_instance_ctrl_t *) p_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if GPT_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_PHASE_COUNT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear open flag. */
    p_instance_ctrl->open = 0U;

    /* Stop counter. */
    p_instance_ctrl->p_reg->GTSTP = p_instance_ctrl->channel_mask;

    /* Close all GPT modules */
    R_GPT_Close(p_instance_ctrl->p_cfg->p_timer_instance->p_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 * DEPRECATED Sets driver version based on compile time macros. Implements @ref gpt_phase_count_api_t::versionGet.
 *
 * @retval FSP_SUCCESS                 Version stored in p_version.
 * @retval FSP_ERR_ASSERTION           p_version was NULL.
 **********************************************************************************************************************/
fsp_err_t R_GPT_PHASE_COUNT_VersionGet (fsp_version_t * const p_version)
{
#if GPT_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE

    /* Verify parameters are valid */
    FSP_ASSERT(NULL != p_version);
#endif

    p_version->version_id = g_gpt_phase_count_version.version_id;

    return FSP_SUCCESS;
}

/** @} (end addtogroup GPT_PHASE_COUNT) */

/*******************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Enables write protection for all relevant GPT registers (if enabled).
 *
 * @param[in]  p_instance_ctrl         Instance control block.
 **********************************************************************************************************************/
static inline void r_gpt_write_protect_enable (gpt_phase_count_instance_ctrl_t * const p_instance_ctrl)
{
#if GPT_CFG_WRITE_PROTECT_ENABLE
    p_instance_ctrl->p_reg->GTWP = GPT_PHASE_COUNT_PRV_GTWP_WRITE_PROTECT;
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif
}

/*******************************************************************************************************************//**
 * Disables write protection for all relevant GPT registers (if enabled).
 *
 * @param[in]  p_instance_ctrl         Instance control block.
 **********************************************************************************************************************/
static inline void r_gpt_write_protect_disable (gpt_phase_count_instance_ctrl_t * const p_instance_ctrl)
{
#if GPT_CFG_WRITE_PROTECT_ENABLE
    p_instance_ctrl->p_reg->GTWP = GPT_PHASE_COUNT_PRV_GTWP_RESET_VALUE;
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif
}
