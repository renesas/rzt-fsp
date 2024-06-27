/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_cgc.h"
#include "r_cgc_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "CGC" in ASCII, used to determine if the module is open. */
#define CGC_OPEN              (0x00434743U)
#define CGC_PRV_NUM_CLOCKS    ((uint8_t) CGC_CLOCK_PLL1 + 1U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Private enumeration used to tell if a clock is running or not. */
typedef enum e_cgc_prv_clock_state
{
    CGC_PRV_CLOCK_STATE_STOPPED = 0,
    CGC_PRV_CLOCK_STATE_RUNNING = 1,
} cgc_prv_clock_state_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static fsp_err_t             r_cgc_clock_check(cgc_clock_t const clock_source);
static bool                  r_cgc_stabilization_check(cgc_clock_t clock, cgc_prv_clock_state_t status);
static void                  r_cgc_clock_change(cgc_clock_t clock, cgc_clock_change_t state);
static cgc_prv_clock_state_t r_cgc_clock_run_state_get(cgc_clock_t clock);

#if CGC_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_cgc_common_parameter_checking(cgc_instance_ctrl_t * p_instance_ctrl);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

static uint32_t volatile * const gp_cgc_clock_stp_registers[CGC_PRV_NUM_CLOCKS] =
{
    [CGC_CLOCK_LOCO] = (uint32_t *) BSP_FEATURE_CGC_LOCO_CONTROL_ADDRESS,
    [CGC_CLOCK_PLL0] = NULL,           // PLL0 is always running
    [CGC_CLOCK_PLL1] = (uint32_t *) BSP_FEATURE_CGC_PLL1_CONTROL_ADDRESS,
};

/* How long of a software delay is required after starting each clock before activating it as the system clock. */
static const uint32_t g_cgc_software_wait_us[CGC_PRV_NUM_CLOCKS] =
{
    [CGC_CLOCK_LOCO] = BSP_FEATURE_CGC_LOCO_STABILIZATION_MAX_US,
    [CGC_CLOCK_PLL0] = 0U,             // PLL0 has a stabilization wait flag
    [CGC_CLOCK_PLL1] = 0U,             // PLL1 has a stabilization wait flag
};

static const bsp_reg_protect_t g_cgc_register_protect_settings[CGC_PRV_NUM_CLOCKS] =
{
    [CGC_CLOCK_LOCO] = BSP_REG_PROTECT_CGC,
    [CGC_CLOCK_PLL0] = (bsp_reg_protect_t) NULL, // PLL0 is always running
    [CGC_CLOCK_PLL1] = BSP_REG_PROTECT_LPC_RESET,
};

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

const cgc_api_t g_cgc_on_cgc =
{
    .open                 = R_CGC_Open,
    .clocksCfg            = R_CGC_ClocksCfg,
    .clockStart           = R_CGC_ClockStart,
    .clockStop            = R_CGC_ClockStop,
    .clockCheck           = R_CGC_ClockCheck,
    .systemClockSet       = R_CGC_SystemClockSet,
    .systemClockGet       = R_CGC_SystemClockGet,
    .oscStopDetectEnable  = R_CGC_OscStopDetectEnable,
    .oscStopDetectDisable = R_CGC_OscStopDetectDisable,
    .oscStopStatusClear   = R_CGC_OscStopStatusClear,
    .callbackSet          = R_CGC_CallbackSet,
    .close                = R_CGC_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup CGC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initialize the CGC API.  Implements @ref cgc_api_t::open.
 *
 * @retval FSP_SUCCESS              CGC successfully initialized.
 * @retval FSP_ERR_ASSERTION        Invalid input argument.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.
 **********************************************************************************************************************/
fsp_err_t R_CGC_Open (cgc_ctrl_t * const p_ctrl, cgc_cfg_t const * const p_cfg)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;

#if CGC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(CGC_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    FSP_PARAMETER_NOT_USED(p_cfg);

    /* Mark the module as open so other APIs can be used. */
    p_instance_ctrl->open = CGC_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reconfigures all main system clocks.  This API can be used for any of the following purposes:
 *   - start or stop clocks
 *
 * If the requested system clock source has a stabilization flag, this function blocks waiting for the stabilization
 * flag of the requested system clock source to be set.  If the requested system clock source was just started and it
 * has no stabilization flag, this function blocks for the stabilization time required by the requested system clock
 * source according to the Electrical Characteristics section of the hardware manual.  If the requested system clock
 * source has no stabilization flag and it is already running, it is assumed to be stable and this function will not
 * block.
 *
 * Do not attempt to stop the requested clock source or the source of the PLL if the PLL will be running after this
 * operation completes.
 *
 * Implements @ref cgc_api_t::clocksCfg.
 *
 * @retval FSP_SUCCESS                  Clock configuration applied successfully.
 * @retval FSP_ERR_ASSERTION            Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN             Module is not open.
 * @retval FSP_ERR_NOT_STABILIZED       Clock not stabilized.
 * @retval FSP_ERR_INVALID_ARGUMENT     Clock configuration setting is invalid.
 **********************************************************************************************************************/
fsp_err_t R_CGC_ClocksCfg (cgc_ctrl_t * const p_ctrl, cgc_clocks_cfg_t const * const p_clock_cfg)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;

    fsp_err_t err = FSP_SUCCESS;
#if CGC_CFG_PARAM_CHECKING_ENABLE
    err = r_cgc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ASSERT(NULL != p_clock_cfg);

    /* ATCM wait should be 1-wait when CPU0CLK is over 400MHz */
    FSP_ERROR_RETURN(!((0 == R_TCMAW->CPU0WAIT_b.CPU0WAIT) &&
                       (CGC_CPU_CLOCK_DIV_1 == p_clock_cfg->divider_cfg.sckcr2_b.fsel0cr52)),
                     FSP_ERR_INVALID_ARGUMENT);

    /* Make sure the oscillator is stable. */
    FSP_ERROR_RETURN(!((0 == R_SYSC_S->PLL1MON_b.PLL1MON) &&
                       (CGC_PHY_CLOCK_PLL1 == p_clock_cfg->divider_cfg.sckcr_b.phy_sel)),
                     FSP_ERR_NOT_STABILIZED);

    /* Do not stop the clock used by other functions. */
    FSP_ERROR_RETURN(!((CGC_CLOCK_CHANGE_STOP == p_clock_cfg->pll1_state) &&
                       (CGC_PHY_CLOCK_PLL1 == p_clock_cfg->divider_cfg.sckcr_b.phy_sel)),
                     FSP_ERR_INVALID_ARGUMENT);

    /* Do not select a stopped clock as the clock source. */
    if (0 == R_SYSC_S->PLL1EN_b.PLL1EN)
    {
        FSP_ERROR_RETURN(!((CGC_CLOCK_CHANGE_NONE == p_clock_cfg->pll1_state) &&
                           (CGC_PHY_CLOCK_PLL1 == p_clock_cfg->divider_cfg.sckcr_b.phy_sel)),
                         FSP_ERR_INVALID_ARGUMENT);
    }

#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(err);       // unused in some build configurations
#endif

    cgc_divider_cfg_t clock_cfg;
    clock_cfg.sckcr_w  = p_clock_cfg->divider_cfg.sckcr_w;
    clock_cfg.sckcr2_w = p_clock_cfg->divider_cfg.sckcr2_w;

    cgc_clock_change_t options[CGC_PRV_NUM_CLOCKS];
    options[CGC_CLOCK_LOCO] = p_clock_cfg->loco_state;
    options[CGC_CLOCK_PLL0] = CGC_CLOCK_CHANGE_NONE;
    options[CGC_CLOCK_PLL1] = p_clock_cfg->pll1_state;

    /* Start or stop clocks based on the input configuration. */
    for (int32_t i = (CGC_PRV_NUM_CLOCKS - 1); i >= 0; i--)
    {
        cgc_clock_change_t clock_state     = options[i];
        cgc_clock_t        clock_to_change = (cgc_clock_t) i;

        if (CGC_CLOCK_CHANGE_STOP == clock_state)
        {
            R_BSP_RegisterProtectDisable(g_cgc_register_protect_settings[clock_to_change]);
            r_cgc_clock_change(clock_to_change, CGC_CLOCK_CHANGE_STOP);
            R_BSP_RegisterProtectEnable(g_cgc_register_protect_settings[clock_to_change]);
        }
        else if (CGC_CLOCK_CHANGE_START == clock_state)
        {
            R_BSP_RegisterProtectDisable(g_cgc_register_protect_settings[clock_to_change]);
            r_cgc_clock_change(clock_to_change, CGC_CLOCK_CHANGE_START);
            R_BSP_RegisterProtectEnable(g_cgc_register_protect_settings[clock_to_change]);
        }
        else
        {
            /* Do nothing. */
        }

        /* If the requested clock is not the subclock and it was just started and it has no stabilization flag, wait
         * for the required stabilization time in software. */
        if (g_cgc_software_wait_us[i] > 0U)
        {
            if (CGC_CLOCK_CHANGE_START == options[i])
            {
                R_BSP_SoftwareDelay(g_cgc_software_wait_us[i], BSP_DELAY_UNITS_MICROSECONDS);
            }
        }
    }

    /* CLMA settings are unsupported for CGC, so do not overwrite CLMA setting value. */
    clock_cfg.sckcr_w |= (uint32_t) (R_SYSC_NS->SCKCR_b.CLMASEL << R_SYSC_NS_SCKCR_CLMASEL_Pos);

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);
    bsp_prv_clock_set(clock_cfg.sckcr_w, clock_cfg.sckcr2_w);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_CGC);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Start the specified clock if it is not currently active. Implements @ref cgc_api_t::clockStart.
 *
 * @retval FSP_SUCCESS                  Clock initialized successfully.
 * @retval FSP_ERR_ASSERTION            Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN             Module is not open.
 **********************************************************************************************************************/
fsp_err_t R_CGC_ClockStart (cgc_ctrl_t * const p_ctrl, cgc_clock_t clock_source, cgc_pll_cfg_t const * const p_pll_cfg)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if CGC_CFG_PARAM_CHECKING_ENABLE
    err = r_cgc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(err);
#endif

    FSP_PARAMETER_NOT_USED(p_pll_cfg);

    /* Start the clock. */
    R_BSP_RegisterProtectDisable(g_cgc_register_protect_settings[clock_source]);
    r_cgc_clock_change(clock_source, CGC_CLOCK_CHANGE_START);
    R_BSP_RegisterProtectEnable(g_cgc_register_protect_settings[clock_source]);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stop the specified clock if it is active.  Implements @ref cgc_api_t::clockStop.
 *
 * @retval FSP_SUCCESS                      Clock stopped successfully.
 * @retval FSP_ERR_ASSERTION                Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN                 Module is not open.
 * @retval FSP_ERR_IN_USE                   Attempt to stop the current system clock or the PLL source clock.
 * @retval FSP_ERR_NOT_STABILIZED           Clock not stabilized after starting.
 **********************************************************************************************************************/
fsp_err_t R_CGC_ClockStop (cgc_ctrl_t * const p_ctrl, cgc_clock_t clock_source)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;

#if CGC_CFG_PARAM_CHECKING_ENABLE

    /* Verify p_instance_ctrl is not NULL and the module is open. */
    fsp_err_t err = r_cgc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Make sure the oscillator is stable. */
    FSP_ERROR_RETURN(r_cgc_stabilization_check(clock_source, r_cgc_clock_run_state_get(clock_source)),
                     FSP_ERR_NOT_STABILIZED);

    /* If clock source is in use, return error */
    FSP_ERROR_RETURN(!((clock_source == CGC_CLOCK_PLL1) && (R_SYSC_NS->SCKCR_b.PHYSEL == 0)), FSP_ERR_IN_USE);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Stop the clock. */
    R_BSP_RegisterProtectDisable(g_cgc_register_protect_settings[clock_source]);
    r_cgc_clock_change(clock_source, CGC_CLOCK_CHANGE_STOP);
    R_BSP_RegisterProtectEnable(g_cgc_register_protect_settings[clock_source]);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set the specified clock as the system clock and configure the internal dividers.
 * Implements @ref cgc_api_t::systemClockSet.
 *
 * This function also updates the SystemCoreClock CMSIS global variable.
 *
 * @retval FSP_SUCCESS                  Operation performed successfully.
 * @retval FSP_ERR_ASSERTION            Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN             Module is not open.
 * @retval FSP_ERR_CLOCK_INACTIVE       The specified clock source is inactive.
 * @retval FSP_ERR_NOT_STABILIZED       The clock source is not stabilized after being turned off or PLL clock source
 *                                      is not stable.
 **********************************************************************************************************************/
fsp_err_t R_CGC_SystemClockSet (cgc_ctrl_t * const              p_ctrl,
                                cgc_clock_t                     clock_source,
                                cgc_divider_cfg_t const * const p_divider_cfg)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;

#if CGC_CFG_PARAM_CHECKING_ENABLE

    /* Verify p_instance_ctrl is not NULL and the module is open. */
    fsp_err_t err = r_cgc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ASSERT(NULL != p_divider_cfg);

    /* Confirm the requested clock is stable. */
    err = r_cgc_clock_check(clock_source);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(clock_source);
#endif

    cgc_divider_cfg_t clock_cfg;
    clock_cfg.sckcr_w  = p_divider_cfg->sckcr_w;
    clock_cfg.sckcr2_w = p_divider_cfg->sckcr2_w;

    /* CLMA settings are unsupported for CGC, so do not overwrite CLMA setting values. */
    clock_cfg.sckcr_w |= (uint32_t) (R_SYSC_NS->SCKCR_b.CLMASEL << R_SYSC_NS_SCKCR_CLMASEL_Pos);

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);
    bsp_prv_clock_set(clock_cfg.sckcr_w, clock_cfg.sckcr2_w);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_CGC);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Return the current system clock source and configuration.  Implements @ref cgc_api_t::systemClockGet.
 *
 * @retval FSP_SUCCESS                 Parameters returned successfully.
 * @retval FSP_ERR_ASSERTION           Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN            Module is not open.
 **********************************************************************************************************************/
fsp_err_t R_CGC_SystemClockGet (cgc_ctrl_t * const        p_ctrl,
                                cgc_clock_t * const       p_clock_source,
                                cgc_divider_cfg_t * const p_divider_cfg)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;

#if CGC_CFG_PARAM_CHECKING_ENABLE

    /* Verify p_instance_ctrl is not NULL and the module is open. */
    fsp_err_t err = r_cgc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Get the system clock source */
    if (NULL != p_clock_source)
    {
        /* System clock source is always PLL0. */
        *p_clock_source = CGC_CLOCK_PLL0;
    }

    /* Get current dividers. */
    if (NULL != p_divider_cfg)
    {
        p_divider_cfg->sckcr_w  = R_SYSC_NS->SCKCR & (~(R_SYSC_NS_SCKCR_CLMASEL_Msk));
        p_divider_cfg->sckcr2_w = R_SYSC_S->SCKCR2;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Check the specified clock for stability.  Implements @ref cgc_api_t::clockCheck.
 *
 * @retval FSP_SUCCESS                 Clock is running and stable.
 * @retval FSP_ERR_ASSERTION           Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN            Module is not open.
 * @retval FSP_ERR_NOT_STABILIZED      Clock not stabilized.
 * @retval FSP_ERR_CLOCK_INACTIVE      Clock not turned on.
 **********************************************************************************************************************/
fsp_err_t R_CGC_ClockCheck (cgc_ctrl_t * const p_ctrl, cgc_clock_t clock_source)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;
    fsp_err_t             err;

#if CGC_CFG_PARAM_CHECKING_ENABLE

    /* Verify p_instance_ctrl is not NULL and the module is open. */
    err = r_cgc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Ensure the clock is running and stable. */
    err = r_cgc_clock_check(clock_source);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enable the oscillation stop detection for the main clock. API not supported.
 *
 * Implements @ref cgc_api_t::oscStopDetectEnable.
 *
 * @retval FSP_ERR_UNSUPPORTED    API not supported.
 **********************************************************************************************************************/
fsp_err_t R_CGC_OscStopDetectEnable (cgc_ctrl_t * const p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Disable the oscillation stop detection for the main clock. API not supported.
 *
 * Implements @ref cgc_api_t::oscStopDetectDisable.
 *
 * @retval FSP_ERR_UNSUPPORTED    API not supported.
 **********************************************************************************************************************/
fsp_err_t R_CGC_OscStopDetectDisable (cgc_ctrl_t * const p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Clear the Oscillation Stop Detection Status register. API not supported.
 *
 * Implements @ref cgc_api_t::oscStopStatusClear.
 *
 * @retval FSP_ERR_UNSUPPORTED    API not supported.
 **********************************************************************************************************************/
fsp_err_t R_CGC_OscStopStatusClear (cgc_ctrl_t * const p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements cgc_api_t::callbackSet
 *
 * @retval FSP_ERR_UNSUPPORTED    API not supported.
 **********************************************************************************************************************/
fsp_err_t R_CGC_CallbackSet (cgc_ctrl_t * const          p_ctrl,
                             void (                    * p_callback)(cgc_callback_args_t *),
                             void const * const          p_context,
                             cgc_callback_args_t * const p_callback_memory)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_callback);
    FSP_PARAMETER_NOT_USED(p_context);
    FSP_PARAMETER_NOT_USED(p_callback_memory);

    return FSP_ERR_UNSUPPORTED;
}

/******************************************************************************************************************//**
 * Closes the CGC module.  Implements @ref cgc_api_t::close.
 *
 * @retval FSP_SUCCESS                 The module is successfully closed.
 * @retval FSP_ERR_ASSERTION           Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN            Module is not open.
 **********************************************************************************************************************/
fsp_err_t R_CGC_Close (cgc_ctrl_t * const p_ctrl)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;

#if CGC_CFG_PARAM_CHECKING_ENABLE

    /* Verify p_instance_ctrl is not NULL and the module is open. */
    fsp_err_t err = r_cgc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    p_instance_ctrl->open = 0U;

    /* All done, return success. */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup CGC)
 **********************************************************************************************************************/

#if CGC_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Verifies the control structure is not NULL and the module is open. This reduces code size when the error logger is
 * used.
 *
 * @param[in]  p_instance_ctrl          Pointer to instance control structure.
 *
 * @retval FSP_SUCCESS                  No error detected.
 * @retval FSP_ERR_ASSERTION            Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN             Module is not open.
 **********************************************************************************************************************/
static fsp_err_t r_cgc_common_parameter_checking (cgc_instance_ctrl_t * p_instance_ctrl)
{
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(CGC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Check if the specified clock is running and stable
 *
 * @param[in]   clock_source           Clock to be verified
 *
 * @retval FSP_SUCCESS                 Clock is running and stable.
 * @retval FSP_ERR_NOT_STABILIZED      Clock not stabilized.
 * @retval FSP_ERR_CLOCK_INACTIVE      Clock not turned on.
 **********************************************************************************************************************/
static fsp_err_t r_cgc_clock_check (cgc_clock_t const clock_source)
{
    cgc_prv_clock_state_t running = r_cgc_clock_run_state_get(clock_source);

    /* Ensure the clock is stable if the clock has a stabilization flag. */
    FSP_ERROR_RETURN(r_cgc_stabilization_check(clock_source, running), FSP_ERR_NOT_STABILIZED);

    /* Ensure the clock is running. */
    FSP_ERROR_RETURN(running, FSP_ERR_CLOCK_INACTIVE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function returns the run state of the selected clock
 *
 * @param[in]  clock   Clock to check
 *
 * @return  1 if running, 0 if stopped
 **********************************************************************************************************************/
static cgc_prv_clock_state_t r_cgc_clock_run_state_get (cgc_clock_t clock)
{
    cgc_prv_clock_state_t ret = CGC_PRV_CLOCK_STATE_STOPPED;

    /* Get clock run state via control register if clock have control register. */
    if (NULL != gp_cgc_clock_stp_registers[clock])
    {
        /* Get clock run state. */
        ret = (cgc_prv_clock_state_t) (*gp_cgc_clock_stp_registers[clock]);
    }
    else
    {
        /* PLL0 have no control register and is always running. */
        ret = CGC_PRV_CLOCK_STATE_RUNNING;
    }

    return ret;
}

/*******************************************************************************************************************//**
 * This function checks the selected clock for stability.
 *
 * @param[in]  clock   Clock to check
 * @param[in]  status  Current state of the clock
 *
 * @return true if stable or the clock has no stability flag, false if not stable
 **********************************************************************************************************************/
static bool r_cgc_stabilization_check (cgc_clock_t clock, cgc_prv_clock_state_t status)
{
    uint32_t mon_bit = R_SYSC_S->PLL1MON_b.PLL1MON;

    /* LOCO have no stabilization flags, so return true if the clock is any of these. */
    bool ret = true;

    if (CGC_CLOCK_PLL1 == clock)
    {
        ret = (mon_bit == (uint32_t) status);
    }
    else
    {
        /* Do nothing. */
    }

    return ret;
}

/*******************************************************************************************************************//**
 * This function starts or stops the selected clock.
 * Do not call this subroutine with CGC_CLOCK_CHANGE_NONE or CGC_CLOCK_CHANGE_UNSUPPORTED.
 *
 * @param[in]  clock   Clock to start or stop
 * @param[in]  state   1 to stop clock, 0 to start clock
 **********************************************************************************************************************/
static void r_cgc_clock_change (cgc_clock_t clock, cgc_clock_change_t state)
{
    /* Convert api defined value to register setting value. */
    uint32_t state_set_value = ((uint32_t) (~state) & 0x00000001U);

    *gp_cgc_clock_stp_registers[clock] = state_set_value;

    /* Wait setting to be reflected in hardware registers. */
    FSP_HARDWARE_REGISTER_WAIT(*gp_cgc_clock_stp_registers[clock], state_set_value);
}
