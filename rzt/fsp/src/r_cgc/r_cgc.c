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
#include "r_cgc.h"
#include "r_cgc_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "CGC" in ASCII, used to determine if the module is open. */
#define CGC_OPEN                                        (0x00434743U)
#define CGC_PRV_NUM_CLOCKS                              ((uint8_t) CGC_CLOCK_PLL1 + 1U)

#define CGC_PRV_SCKCR_FSELXSPI_DIVSELXSPI_VALUE_MASK    (0x47U)
#define CGC_PRV_SCKCR_CKIO_VALUE_MASK                   (0x07U)
#define CGC_PRV_SCKCR_FSELCANFD_VALUE_MASK              (0x01U)
#define CGC_PRV_SCKCR_PHYSEL_VALUE_MASK                 (0x01U)
#define CGC_PRV_SCKCR_CLMA_VALUE_MASK                   (0x01U)
#define CGC_PRV_SCKCR_SPIASYNCSEL_VALUE_MASK            (0x01U)
#define CGC_PRV_SCKCR_SCIASYNCSEL_VALUE_MASK            (0x01U)

#define CGC_PRV_SCKCR2_FSELCR52_VALUE_MASK              (0x03U)
#define CGC_PRV_SCKCR2_DIVSUBSEL_VALUE_MASK             (0x01U)
#define CGC_PRV_SCKCR2_SPIASYNCSEL_VALUE_MASK           (0x01U)
#define CGC_PRV_SCKCR2_SCIASYNCSEL_VALUE_MASK           (0x01U)

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
static uint32_t              r_cgc_cfg_to_sckcr_parameter(cgc_sckcr_cfg_t * p_sckcr_cfg);
static uint32_t              r_cgc_cfg_to_sckcr2_parameter(cgc_sckcr2_cfg_t * p_sckcr2_cfg);

#if CGC_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_cgc_common_parameter_checking(cgc_instance_ctrl_t * p_instance_ctrl);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Version data structure used by error logger macro. */
static const fsp_version_t g_cgc_version =
{
    .api_version_minor  = CGC_API_VERSION_MINOR,
    .api_version_major  = CGC_API_VERSION_MAJOR,
    .code_version_major = CGC_CODE_VERSION_MAJOR,
    .code_version_minor = CGC_CODE_VERSION_MINOR
};

static uint32_t volatile * const gp_cgc_clock_stp_registers[CGC_PRV_NUM_CLOCKS] =
{
    [CGC_CLOCK_HOCO]     = NULL,
    [CGC_CLOCK_MOCO]     = NULL,
    [CGC_CLOCK_LOCO]     = (uint32_t *) BSP_FEATURE_CGC_LOCO_CONTROL_ADDRESS,
    [CGC_CLOCK_MAIN_OSC] = NULL,
    [CGC_CLOCK_SUBCLOCK] = NULL,
    [CGC_CLOCK_PLL]      = NULL,
    [CGC_CLOCK_PLL2]     = NULL,
    [CGC_CLOCK_PLL1]     = (uint32_t *) BSP_FEATURE_CGC_PLL1_CONTROL_ADDRESS,
};

/* How long of a software delay is required after starting each clock before activating it as the system clock. */
static const uint32_t g_cgc_software_wait_us[CGC_PRV_NUM_CLOCKS] =
{
    [CGC_CLOCK_HOCO]     = 0U,         // No need to support
    [CGC_CLOCK_MOCO]     = 0U,         // No need to support
    [CGC_CLOCK_LOCO]     = BSP_FEATURE_CGC_LOCO_STABILIZATION_MAX_US,
    [CGC_CLOCK_MAIN_OSC] = 0U,         // No need to support
    [CGC_CLOCK_SUBCLOCK] = 0U,         // No need to support
    [CGC_CLOCK_PLL]      = 0U,         // No need to support
    [CGC_CLOCK_PLL2]     = 0U,         // No need to support
    [CGC_CLOCK_PLL1]     = 0U,         // PLL1 has a stabilization wait flag
};

static const bsp_reg_protect_t g_cgc_register_protect_settings[CGC_PRV_NUM_CLOCKS] =
{
    [CGC_CLOCK_HOCO]     = (bsp_reg_protect_t) NULL, // No need to support
    [CGC_CLOCK_MOCO]     = (bsp_reg_protect_t) NULL, // No need to support
    [CGC_CLOCK_LOCO]     = BSP_REG_PROTECT_CGC,
    [CGC_CLOCK_MAIN_OSC] = (bsp_reg_protect_t) NULL, // No need to support
    [CGC_CLOCK_SUBCLOCK] = (bsp_reg_protect_t) NULL, // No need to support
    [CGC_CLOCK_PLL]      = (bsp_reg_protect_t) NULL, // No need to support
    [CGC_CLOCK_PLL2]     = (bsp_reg_protect_t) NULL, // No need to support
    [CGC_CLOCK_PLL1]     = BSP_REG_PROTECT_LPC_RESET,
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
    .versionGet           = R_CGC_VersionGet,
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
    FSP_ASSERT(NULL != (cgc_clock_extend_cfg_t *) p_clock_cfg->p_extend);

    /* ATCM wait should be 1-wait when CPU0CLK is over 400MHz */
    FSP_ERROR_RETURN(!((0 == R_TCMAW->CPU0WAIT_b.CPU0WAIT) &&
                       (CGC_CPU_CLOCK_DIV_1 == ((cgc_clock_extend_cfg_t *) p_clock_cfg->p_extend)->sckcr2.fsel0cr52)),
                     FSP_ERR_INVALID_ARGUMENT);

    /* Make sure the oscillator is stable. */
    FSP_ERROR_RETURN(!((0 == R_SYSC_S->PLL1MON_b.PLL1MON) &&
                       (CGC_PHY_CLOCK_PLL1 == ((cgc_clock_extend_cfg_t *) p_clock_cfg->p_extend)->sckcr.phy_sel)),
                     FSP_ERR_NOT_STABILIZED);

    /* Do not stop the clock used by other functions. */
    FSP_ERROR_RETURN(!((CGC_CLOCK_CHANGE_STOP == ((cgc_clock_extend_cfg_t *) p_clock_cfg->p_extend)->pll1_state) &&
                       (CGC_PHY_CLOCK_PLL1 == ((cgc_clock_extend_cfg_t *) p_clock_cfg->p_extend)->sckcr.phy_sel)),
                     FSP_ERR_INVALID_ARGUMENT);

    /* Do not select a stopped clock as the clock source. */
    if (0 == R_SYSC_S->PLL1EN_b.PLL1EN)
    {
        FSP_ERROR_RETURN(!((CGC_CLOCK_CHANGE_NONE == ((cgc_clock_extend_cfg_t *) p_clock_cfg->p_extend)->pll1_state) &&
                           (CGC_PHY_CLOCK_PLL1 == ((cgc_clock_extend_cfg_t *) p_clock_cfg->p_extend)->sckcr.phy_sel)),
                         FSP_ERR_INVALID_ARGUMENT);
    }

#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(err);       // unused in some build configurations
#endif

    cgc_clock_extend_cfg_t * p_extend = (cgc_clock_extend_cfg_t *) p_clock_cfg->p_extend;

    cgc_sckcr_cfg_t  sckcr_cfg  = p_extend->sckcr;
    cgc_sckcr2_cfg_t sckcr2_cfg = p_extend->sckcr2;

    cgc_clock_change_t options[CGC_PRV_NUM_CLOCKS];
    options[CGC_CLOCK_HOCO]     = CGC_CLOCK_CHANGE_NONE;
    options[CGC_CLOCK_LOCO]     = p_clock_cfg->loco_state;
    options[CGC_CLOCK_MOCO]     = CGC_CLOCK_CHANGE_NONE;
    options[CGC_CLOCK_MAIN_OSC] = CGC_CLOCK_CHANGE_NONE;
    options[CGC_CLOCK_SUBCLOCK] = CGC_CLOCK_CHANGE_NONE;
    options[CGC_CLOCK_PLL]      = CGC_CLOCK_CHANGE_NONE;
    options[CGC_CLOCK_PLL2]     = CGC_CLOCK_CHANGE_NONE;
    options[CGC_CLOCK_PLL1]     = p_extend->pll1_state;

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

    uint32_t sckcr = r_cgc_cfg_to_sckcr_parameter(&sckcr_cfg);
    sckcr |= R_SYSC_NS->SCKCR_b.CLMASEL & CGC_PRV_SCKCR_CLMA_VALUE_MASK << R_SYSC_NS_SCKCR_CLMASEL_Pos;
    uint32_t sckcr2 = r_cgc_cfg_to_sckcr2_parameter(&sckcr2_cfg);

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);
    bsp_prv_clock_set(sckcr, sckcr2);
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

    cgc_clock_extend_cfg_t * p_extend = (cgc_clock_extend_cfg_t *) (p_divider_cfg->p_extend);

    cgc_sckcr_cfg_t  sckcr_cfg  = p_extend->sckcr;
    cgc_sckcr2_cfg_t sckcr2_cfg = p_extend->sckcr2;

    uint32_t sckcr = r_cgc_cfg_to_sckcr_parameter(&sckcr_cfg);
    sckcr |= R_SYSC_NS->SCKCR_b.CLMASEL & CGC_PRV_SCKCR_CLMA_VALUE_MASK << R_SYSC_NS_SCKCR_CLMASEL_Pos;
    uint32_t sckcr2 = r_cgc_cfg_to_sckcr2_parameter(&sckcr2_cfg);

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);
    bsp_prv_clock_set(sckcr, sckcr2);
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
        *p_clock_source = CGC_CLOCK_PLL;
    }

    cgc_clock_extend_cfg_t * p_extend     = (cgc_clock_extend_cfg_t *) (p_divider_cfg->p_extend);
    cgc_sckcr_cfg_t        * p_sckcr_cfg  = &p_extend->sckcr;
    cgc_sckcr2_cfg_t       * p_sckcr2_cfg = &p_extend->sckcr2;

    /* Get current dividers. */
    if (NULL != p_divider_cfg)
    {
        uint32_t divselxspi0 = R_SYSC_NS->SCKCR_b.DIVSELXSPI0;
        uint32_t fselxspi0   = R_SYSC_NS->SCKCR_b.FSELXSPI0;
        p_sckcr_cfg->fselxspi0_div =
            (cgc_xspi_clock_div_t) ((divselxspi0 << R_SYSC_NS_SCKCR_DIVSELXSPI0_Pos) | fselxspi0);

        uint32_t divselxspi1 = R_SYSC_NS->SCKCR_b.DIVSELXSPI1;
        uint32_t fselxspi1   = R_SYSC_NS->SCKCR_b.FSELXSPI1;

        p_sckcr_cfg->fselxspi1_div =
            (cgc_xspi_clock_div_t) ((divselxspi1 << R_SYSC_NS_SCKCR_DIVSELXSPI1_Pos) | fselxspi1);
        p_sckcr_cfg->ckio_div       = (cgc_clock_out_clock_div_t) (R_SYSC_NS->SCKCR_b.CKIO);
        p_sckcr_cfg->fselcanfd_div  = (cgc_canfd_clock_div_t) (R_SYSC_NS->SCKCR_b.FSELCANFD);
        p_sckcr_cfg->phy_sel        = (cgc_phy_clock_t) (R_SYSC_NS->SCKCR_b.PHYSEL);
        p_sckcr_cfg->spi0_async_sel = (cgc_spi_async_clock_t) (R_SYSC_NS->SCKCR_b.SPI0ASYNCSEL);
        p_sckcr_cfg->spi1_async_sel = (cgc_spi_async_clock_t) (R_SYSC_NS->SCKCR_b.SPI1ASYNCSEL);
        p_sckcr_cfg->spi2_async_sel = (cgc_spi_async_clock_t) (R_SYSC_NS->SCKCR_b.SPI2ASYNCSEL);
        p_sckcr_cfg->sci0_async_sel = (cgc_sci_async_clock_t) (R_SYSC_NS->SCKCR_b.SCI0ASYNCSEL);
        p_sckcr_cfg->sci1_async_sel = (cgc_sci_async_clock_t) (R_SYSC_NS->SCKCR_b.SCI1ASYNCSEL);
        p_sckcr_cfg->sci2_async_sel = (cgc_sci_async_clock_t) (R_SYSC_NS->SCKCR_b.SCI2ASYNCSEL);
        p_sckcr_cfg->sci3_async_sel = (cgc_sci_async_clock_t) (R_SYSC_NS->SCKCR_b.SCI3ASYNCSEL);
        p_sckcr_cfg->sci4_async_sel = (cgc_sci_async_clock_t) (R_SYSC_NS->SCKCR_b.SCI4ASYNCSEL);

        p_sckcr2_cfg->fsel0cr52      = (cgc_cpu_clock_div_t) (R_SYSC_S->SCKCR2_b.FSELCPU0);
        p_sckcr2_cfg->fsel1cr52      = (cgc_cpu_clock_div_t) (R_SYSC_S->SCKCR2_b.FSELCPU1);
        p_sckcr2_cfg->div_sub_sel    = (cgc_baseclock_div_t) (R_SYSC_S->SCKCR2_b.DIVSELSUB);
        p_sckcr2_cfg->spi3_async_sel = (cgc_spi_async_clock_t) (R_SYSC_S->SCKCR2_b.SPI3ASYNCSEL);
        p_sckcr2_cfg->sci5_async_sel = (cgc_sci_async_clock_t) (R_SYSC_S->SCKCR2_b.SCI5ASYNCSEL);
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
fsp_err_t R_CGC_CallbackSet (cgc_ctrl_t * const          p_api_ctrl,
                             void (                    * p_callback)(cgc_callback_args_t *),
                             void const * const          p_context,
                             cgc_callback_args_t * const p_callback_memory)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
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
 * Return the driver version.  Implements @ref cgc_api_t::versionGet.
 *
 * @retval FSP_SUCCESS                 Module version provided in p_version.
 * @retval FSP_ERR_ASSERTION           Invalid input argument.
 **********************************************************************************************************************/
fsp_err_t R_CGC_VersionGet (fsp_version_t * const p_version)
{
#if CGC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_version);
#endif
    p_version->version_id = g_cgc_version.version_id;

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

    /* Get clock run state. */
    return (cgc_prv_clock_state_t) (*gp_cgc_clock_stp_registers[clock]);
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
 * This function starts or stops the selected clock.  Do not call this subroutine with CGC_CLOCK_CHANGE_NONE.
 *
 * @param[in]  clock   Clock to start or stop
 * @param[in]  state   1 to stop clock, 0 to start clock
 **********************************************************************************************************************/
static void r_cgc_clock_change (cgc_clock_t clock, cgc_clock_change_t state)
{
    *gp_cgc_clock_stp_registers[clock] = (uint32_t) state;

    /* Wait setting to be reflected in hardware registers. */
    FSP_HARDWARE_REGISTER_WAIT(*gp_cgc_clock_stp_registers[clock], (uint32_t) state);
}

/*******************************************************************************************************************//**
 * Converts cgc_sckcr_cfg_t to the SCKCR register setting parameter.
 *
 * @param[in]  p_sckcr_cfg   Pointer to clock configuration structure
 *
 * @return     SCKCR setting parameter
 **********************************************************************************************************************/
static uint32_t r_cgc_cfg_to_sckcr_parameter (cgc_sckcr_cfg_t * p_sckcr_cfg)
{
    cgc_sckcr_cfg_t sckcr_cfg = *p_sckcr_cfg;

    uint32_t sckcr =
        (((sckcr_cfg.fselxspi0_div & CGC_PRV_SCKCR_FSELXSPI_DIVSELXSPI_VALUE_MASK) << R_SYSC_NS_SCKCR_FSELXSPI0_Pos) |
         ((sckcr_cfg.fselxspi1_div & CGC_PRV_SCKCR_FSELXSPI_DIVSELXSPI_VALUE_MASK) <<
            R_SYSC_NS_SCKCR_FSELXSPI1_Pos) |
         ((sckcr_cfg.ckio_div & CGC_PRV_SCKCR_CKIO_VALUE_MASK) << R_SYSC_NS_SCKCR_CKIO_Pos) |
         ((sckcr_cfg.fselcanfd_div & CGC_PRV_SCKCR_FSELCANFD_VALUE_MASK) <<
            R_SYSC_NS_SCKCR_FSELCANFD_Pos) |
         ((sckcr_cfg.phy_sel & CGC_PRV_SCKCR_PHYSEL_VALUE_MASK) << R_SYSC_NS_SCKCR_PHYSEL_Pos) |
         ((sckcr_cfg.spi0_async_sel & CGC_PRV_SCKCR_SPIASYNCSEL_VALUE_MASK) <<
            R_SYSC_NS_SCKCR_SPI0ASYNCSEL_Pos) |
         ((sckcr_cfg.spi1_async_sel & CGC_PRV_SCKCR_SPIASYNCSEL_VALUE_MASK) <<
            R_SYSC_NS_SCKCR_SPI1ASYNCSEL_Pos) |
         ((sckcr_cfg.spi2_async_sel & CGC_PRV_SCKCR_SPIASYNCSEL_VALUE_MASK) <<
            R_SYSC_NS_SCKCR_SPI2ASYNCSEL_Pos) |
         ((sckcr_cfg.sci0_async_sel & CGC_PRV_SCKCR_SCIASYNCSEL_VALUE_MASK) <<
            R_SYSC_NS_SCKCR_SCI0ASYNCSEL_Pos) |
         ((sckcr_cfg.sci1_async_sel & CGC_PRV_SCKCR_SCIASYNCSEL_VALUE_MASK) <<
            R_SYSC_NS_SCKCR_SCI1ASYNCSEL_Pos) |
         ((sckcr_cfg.sci2_async_sel & CGC_PRV_SCKCR_SCIASYNCSEL_VALUE_MASK) <<
            R_SYSC_NS_SCKCR_SCI2ASYNCSEL_Pos) |
         ((sckcr_cfg.sci3_async_sel & CGC_PRV_SCKCR_SCIASYNCSEL_VALUE_MASK) <<
            R_SYSC_NS_SCKCR_SCI3ASYNCSEL_Pos) |
         ((sckcr_cfg.sci4_async_sel & CGC_PRV_SCKCR_SCIASYNCSEL_VALUE_MASK) <<
            R_SYSC_NS_SCKCR_SCI4ASYNCSEL_Pos));

    return sckcr;
}

/*******************************************************************************************************************//**
 * Converts cgc_sckcr2_cfg_t to the SCKCR2 register setting parameter.
 *
 * @param[in]  p_sckcr2_cfg  Pointer to clock configuration structure
 * @return     SCKCR2 setting parameter
 **********************************************************************************************************************/
static uint32_t r_cgc_cfg_to_sckcr2_parameter (cgc_sckcr2_cfg_t * p_sckcr2_cfg)
{
    cgc_sckcr2_cfg_t sckcr2_cfg = *p_sckcr2_cfg;

    uint32_t sckcr2 = (((sckcr2_cfg.fsel0cr52 & CGC_PRV_SCKCR2_FSELCR52_VALUE_MASK) << R_SYSC_S_SCKCR2_FSELCPU0_Pos) |
                       ((sckcr2_cfg.fsel1cr52 & CGC_PRV_SCKCR2_FSELCR52_VALUE_MASK) << R_SYSC_S_SCKCR2_FSELCPU1_Pos) |
                       ((sckcr2_cfg.div_sub_sel & CGC_PRV_SCKCR2_DIVSUBSEL_VALUE_MASK) <<
                        R_SYSC_S_SCKCR2_DIVSELSUB_Pos) |
                       ((sckcr2_cfg.spi3_async_sel & CGC_PRV_SCKCR2_SPIASYNCSEL_VALUE_MASK) <<
                        R_SYSC_S_SCKCR2_SPI3ASYNCSEL_Pos) |
                       ((sckcr2_cfg.sci5_async_sel & CGC_PRV_SCKCR2_SCIASYNCSEL_VALUE_MASK) <<
                        R_SYSC_S_SCKCR2_SCI5ASYNCSEL_Pos));

    return sckcr2;
}
