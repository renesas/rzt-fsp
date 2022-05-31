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
#include "r_mtu3_phase_count.h"
#include "r_mtu3_phase_count_cfg.h"

#include "r_mtu3.h"
#include "r_mtu3_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "MTPH" in ASCII, used to determine if channel is open. */
#define MTU3_PHASE_COUNT_OPEN               (0x4D545048ULL)

/* MTUx.TCR2 offset address */
#define MTU0_TCR2_OFFSET_ADDRESS            (0x0028U)
#define MTU1_TCR2_OFFSET_ADDRESS            (0x0014U)
#define MTU2_TCR2_OFFSET_ADDRESS            (0x000CU)
#define MTU3_TCR2_OFFSET_ADDRESS            (0x014CU)
#define MTU4_TCR2_OFFSET_ADDRESS            (0x004DU)
#define MTU5_TCR2_OFFSET_ADDRESS            (0x0000U)
#define MTU6_TCR2_OFFSET_ADDRESS            (0x014CU)
#define MTU7_TCR2_OFFSET_ADDRESS            (0x004DU)
#define MTU8_TCR2_OFFSET_ADDRESS            (0x0006U)

/* MTUx.TCNT offset address */
#define MTU0_TCNT_OFFSET_ADDRESS            (0x0006U)
#define MTU1_TCNT_OFFSET_ADDRESS            (0x0006U)
#define MTU2_TCNT_OFFSET_ADDRESS            (0x0006U)
#define MTU3_TCNT_OFFSET_ADDRESS            (0x0110U)
#define MTU4_TCNT_OFFSET_ADDRESS            (0x0012U)
#define MTU5_TCNT_OFFSET_ADDRESS            (0x0080U)
#define MTU6_TCNT_OFFSET_ADDRESS            (0x0110U)
#define MTU7_TCNT_OFFSET_ADDRESS            (0x0012U)
#define MTU8_TCNT_OFFSET_ADDRESS            (0x0008U)

/* MTUx.TMDR1 offset address */
#define MTU0_TMDR1_OFFSET_ADDRESS           (0x0001U)
#define MTU1_TMDR1_OFFSET_ADDRESS           (0x0001U)
#define MTU2_TMDR1_OFFSET_ADDRESS           (0x0001U)
#define MTU3_TMDR1_OFFSET_ADDRESS           (0x0102U)
#define MTU4_TMDR1_OFFSET_ADDRESS           (0x0003U)
#define MTU5_TMDR1_OFFSET_ADDRESS           (0x0000U) /* Nothing */
#define MTU6_TMDR1_OFFSET_ADDRESS           (0x0102U)
#define MTU7_TMDR1_OFFSET_ADDRESS           (0x0003U)
#define MTU8_TMDR1_OFFSET_ADDRESS           (0x0001U)

/* MTUx.TGRA offset address */
#define MTU0_TGRA_OFFSET_ADDRESS            (0x0008U)
#define MTU1_TGRA_OFFSET_ADDRESS            (0x0008U)
#define MTU2_TGRA_OFFSET_ADDRESS            (0x0008U)
#define MTU3_TGRA_OFFSET_ADDRESS            (0x0118U)
#define MTU4_TGRA_OFFSET_ADDRESS            (0x001CU)
#define MTU5_TGRA_OFFSET_ADDRESS            (0x0082U) /* Nothing */
#define MTU6_TGRA_OFFSET_ADDRESS            (0x0118U)
#define MTU7_TGRA_OFFSET_ADDRESS            (0x001CU)
#define MTU8_TGRA_OFFSET_ADDRESS            (0x000CU)

/* TGR offset address */
#define MTU3_TGRB_D_OFFSET_WORD             (0x2U)

#define MTU1_TIOR_IOB_INPUT_MTU8_TGRC       (0x0EU)   /* Input capture at occurrence of compare match or input capture in the MTU8.TGRC register */
#define MTU8_TCR_CCLR_TGRC_COMPARE          (0x05U)   /* TCNT cleared by TGRC compare match/input capture */
#define MTU8_TIOR_IOB_INPUT_MTU1_TCNT       (0x0EU)   /* Capture input source is the clock source for counting in MTU1.Input capture on counting up or down by MTU1.TCNT */
#define MTU0_TCR2_TPSC_MTIOC1A              (0x07U)   /* External clock: counts on MTIOC1A pin input */
#define MTU0_TIOR_IOB_INPUT_MTU1_TCNT       (0x0CU)   /* Capture input source is the clock source for counting in MTU1.Input capture on counting up or down by MTU1.TCNT */
#define MTU0_TIOR_IOA_INPUT_MTU8_TGTC       (0x0EU)   /* Input capture on generation of compare match with MTU8.TGRC */
#define MTU0_TCR_CCLR_TGRC_COMPARE          (0x05U)   /* TCNT cleared by TGRC compare match/input capture */

#define MTU_TIOR_INPUT_RISING_EDGE          (0x08U)   /* Input capture at rising edge */
#define MTU_TIOR_INPUT_FALLING_EDGE         (0x09U)   /* Input capture at falling edge */
#define MTU_TIOR_INPUT_BOTH_EDGE            (0x0AU)   /* Input capture at both edge */

#define MTU_TGR_INITIAL_VAL                 (0xFFFFU) /* TGR initial value */

#define MTU0_TGRA_16BIT_MODE_INITIAL_VAL    (40000)   /* 0.2ms(200MHz) */
#define MTU0_TGRC_16BIT_MODE_INITIAL_VAL    (50000)   /* 0.25ms(200MHz) */
#define MTU8_TGRC_32BIT_MODE_INITIAL_VAL    (200000)  /* 1ms(200MHz) */

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** MTU3 Channel No */
typedef enum e_mtu3_channel
{
    MTU3_CHANNEL_0 = 0,                ///< MTU3 channel0
    MTU3_CHANNEL_1 = 1,                ///< MTU3 channel1
    MTU3_CHANNEL_2 = 2,                ///< MTU3 channel2
    MTU3_CHANNEL_3 = 3,                ///< MTU3 channel3
    MTU3_CHANNEL_4 = 4,                ///< MTU3 channel4
    MTU3_CHANNEL_5 = 5,                ///< MTU3 channel5
    MTU3_CHANNEL_6 = 6,                ///< MTU3 channel6
    MTU3_CHANNEL_7 = 7,                ///< MTU3 channel7
    MTU3_CHANNEL_8 = 8,                ///< MTU3 channel8
} mtu3_channel_t;

#define MTU3_PHASE_COUNTING_MODE_1_MD     0x4U
#define MTU3_PHASE_COUNTING_MODE_2_MD     0x5U
#define MTU3_PHASE_COUNTING_MODE_3_MD     0x6U
#define MTU3_PHASE_COUNTING_MODE_4_MD     0x7U
#define MTU3_PHASE_COUNTING_MODE_5_MD     0x9U

#define MTU3_PHASE_COUNTING_MODE_PCB_0    0x0U
#define MTU3_PHASE_COUNTING_MODE_PCB_1    (0x1U << 3)
#define MTU3_PHASE_COUNTING_MODE_PCB_2    (0x2U << 3)

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void mtu3_phase_count_hardware_initialize(mtu3_phase_count_instance_ctrl_t * const p_instance_ctrl,
                                                 mtu3_phase_count_cfg_t const * const     p_cfg);
static void mtu3_phase_count_stop_timer(mtu3_phase_count_instance_ctrl_t * const p_instance_ctrl);
static void mtu3_phase_count_set_count(mtu3_phase_count_instance_ctrl_t * const p_instance_ctrl, uint32_t counter);
static void mtu3_phase_count_mode_set(mtu3_phase_count_instance_ctrl_t * const p_instance_ctrl,
                                      mtu3_phase_counting_mode_t               mode);

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Version data structure used by error logger macro. */
static const fsp_version_t g_mtu3_phase_count_version =
{
    .api_version_minor  = MTU3_PHASE_COUNT_API_VERSION_MINOR,
    .api_version_major  = MTU3_PHASE_COUNT_API_VERSION_MAJOR,
    .code_version_major = MTU3_PHASE_COUNT_CODE_VERSION_MAJOR,
    .code_version_minor = MTU3_PHASE_COUNT_CODE_VERSION_MINOR
};

/* MTUx.TCR2 offset address */
static const uint32_t tcr2_ofs_addr[BSP_FEATURE_MTU3_MAX_CHANNELS] =
{
    MTU0_TCR2_OFFSET_ADDRESS,
    MTU1_TCR2_OFFSET_ADDRESS,
    MTU2_TCR2_OFFSET_ADDRESS,
    MTU3_TCR2_OFFSET_ADDRESS,
    MTU4_TCR2_OFFSET_ADDRESS,
    MTU5_TCR2_OFFSET_ADDRESS,          /* (Nothing) */
    MTU6_TCR2_OFFSET_ADDRESS,
    MTU7_TCR2_OFFSET_ADDRESS,
    MTU8_TCR2_OFFSET_ADDRESS,
};

/* MTUx.TCNT offset address */
static const uint32_t tcnt_ofs_addr[BSP_FEATURE_MTU3_MAX_CHANNELS] =
{
    MTU0_TCNT_OFFSET_ADDRESS,
    MTU1_TCNT_OFFSET_ADDRESS,
    MTU2_TCNT_OFFSET_ADDRESS,
    MTU3_TCNT_OFFSET_ADDRESS,
    MTU4_TCNT_OFFSET_ADDRESS,
    MTU5_TCNT_OFFSET_ADDRESS,          /* (Nothing) */
    MTU6_TCNT_OFFSET_ADDRESS,
    MTU7_TCNT_OFFSET_ADDRESS,
    MTU8_TCNT_OFFSET_ADDRESS,
};

/* MTUx.TMDR1 offset address */
static const uint32_t tmdr1_ofs_addr[BSP_FEATURE_MTU3_MAX_CHANNELS] =
{
    MTU0_TMDR1_OFFSET_ADDRESS,
    MTU1_TMDR1_OFFSET_ADDRESS,
    MTU2_TMDR1_OFFSET_ADDRESS,
    MTU3_TMDR1_OFFSET_ADDRESS,
    MTU4_TMDR1_OFFSET_ADDRESS,
    MTU5_TMDR1_OFFSET_ADDRESS,         /* Nothing */
    MTU6_TMDR1_OFFSET_ADDRESS,
    MTU7_TMDR1_OFFSET_ADDRESS,
    MTU8_TMDR1_OFFSET_ADDRESS,
};

/* MTU3.TSTR value */
static const uint8_t mtu3_tstr_val[BSP_FEATURE_MTU3_MAX_CHANNELS] =
{
    (1U << R_MTU_TSTRA_CST0_Pos),
    (1U << R_MTU_TSTRA_CST1_Pos),
    (1U << R_MTU_TSTRA_CST2_Pos),
    (1U << R_MTU_TSTRA_CST3_Pos),
    (1U << R_MTU_TSTRA_CST4_Pos),
    0U,
    (1U << R_MTU_TSTRB_CST6_Pos),
    (1U << R_MTU_TSTRB_CST7_Pos),
    (1U << R_MTU_TSTRA_CST8_Pos),
};

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* Implementation of MTU3_PHASE_COUNT interface  */
const mtu3_phase_count_api_t g_mtu3_phase_count_on_mtu3_phase_count =
{
    .open           = R_MTU3_PHASE_COUNT_Open,
    .stop           = R_MTU3_PHASE_COUNT_Stop,
    .start          = R_MTU3_PHASE_COUNT_Start,
    .reset          = R_MTU3_PHASE_COUNT_Reset,
    .positionSet    = R_MTU3_PHASE_COUNT_PositionSet,
    .positionGet    = R_MTU3_PHASE_COUNT_PositionGet,
    .controlmodeSet = R_MTU3_PHASE_COUNT_ControlModeSet,
    .speedControl   = R_MTU3_PHASE_COUNT_SpeedControl,
    .speedGet       = R_MTU3_PHASE_COUNT_SpeedGet,
    .callbackSet    = R_MTU3_PHASE_COUNT_CallbackSet,
    .close          = R_MTU3_PHASE_COUNT_Close,
    .versionGet     = R_MTU3_PHASE_COUNT_VersionGet
};

/*******************************************************************************************************************//**
 * @addtogroup MTU3_PHASE_COUNT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes the phase_count timer module (and associated timers) and applies configurations. Implements
 * @ref mtu3_phase_count_api_t::open.
 *
 * Example:
 * @snippet r_mtu3_phase_count_example.c R_MTU3_PHASE_COUNT_Open
 *
 * @retval FSP_SUCCESS                    Initialization was successful.
 * @retval FSP_ERR_ASSERTION              A required input pointer is NULL.
 * @retval FSP_ERR_ALREADY_OPEN           Module is already open.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The channel requested in the p_cfg parameter is not available on this device.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_PHASE_COUNT_Open (mtu3_phase_count_ctrl_t * const p_ctrl, mtu3_phase_count_cfg_t const * const p_cfg)
{
    mtu3_phase_count_instance_ctrl_t * p_instance_ctrl = (mtu3_phase_count_instance_ctrl_t *) p_ctrl;
#if MTU3_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(MTU3_PHASE_COUNT_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ERROR_RETURN((p_cfg->channel < MTU3_CHANNEL_3), FSP_ERR_IP_CHANNEL_NOT_PRESENT);
    FSP_ERROR_RETURN((p_cfg->channel > MTU3_CHANNEL_0), FSP_ERR_IP_CHANNEL_NOT_PRESENT);
#endif

    fsp_err_t err;

    /* Open all MTU3 submodules */
    err = R_MTU3_Open(p_cfg->p_timer_instance->p_ctrl, p_cfg->p_timer_instance->p_cfg);
#if MTU3_CFG_PARAM_CHECKING_ENABLE
    if (err)
    {
        /* In case of an error on MTU3 open, close all opened instances and return the error */
        R_MTU3_Close(p_cfg->p_timer_instance->p_ctrl);

        return err;
    }

#else
    FSP_PARAMETER_NOT_USED(err);
#endif

    /* Save a pointer to the MTU3 registers for this channel */
    p_instance_ctrl->p_reg     = ((mtu3_instance_ctrl_t *) (p_cfg->p_timer_instance->p_ctrl))->p_reg;
    p_instance_ctrl->p_reg_com = ((mtu3_instance_ctrl_t *) (p_cfg->p_timer_instance->p_ctrl))->p_reg_com;
    p_instance_ctrl->p_reg_nf  = ((mtu3_instance_ctrl_t *) (p_cfg->p_timer_instance->p_ctrl))->p_reg_nf;

    /* Get copy of MTU3 channel mask and base register */
    p_instance_ctrl->channel_mask = p_cfg->channel_mask;

    /* Save pointer to config struct */
    p_instance_ctrl->p_cfg = p_cfg;

    mtu3_phase_count_hardware_initialize(p_instance_ctrl, p_cfg);

    /* Configure the up/down count mode. These are not affected by enable/disable. */
    mtu3_phase_count_mode_set(p_instance_ctrl, p_cfg->counting_mode);

    if (MTU3_BIT_MODE_NORMAL_32BIT == p_instance_ctrl->p_cfg->bit_mode)
    {
        p_instance_ctrl->p_reg_com->TSTRA |= mtu3_tstr_val[p_instance_ctrl->p_cfg->channel];
        *((uint8_t *) p_instance_ctrl->p_reg +
          tmdr1_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_2_MD;

        /* Set MTU1.TCNTLW count clear factor to MTU1.TGRALW input capture. */
        R_MTU1->TCR_b.CCLR = MTU3_TCNT_CLEAR_TGRA;

        switch (p_cfg->counting_mode)
        {
            case MTU3_PHASE_COUNTING_MODE_1:
            case MTU3_PHASE_COUNTING_MODE_210:
            case MTU3_PHASE_COUNTING_MODE_310:
            case MTU3_PHASE_COUNTING_MODE_4:
            {
                /* Set the effective edge of both edge. */
                R_MTU1->TIOR_b.IOA = MTU_TIOR_INPUT_BOTH_EDGE;
                R_MTU1->TIOR_b.IOB = MTU_TIOR_INPUT_BOTH_EDGE;
                break;
            }

            case MTU3_PHASE_COUNTING_MODE_200:
            case MTU3_PHASE_COUNTING_MODE_300:
            case MTU3_PHASE_COUNTING_MODE_50:
            case MTU3_PHASE_COUNTING_MODE_51:
            {
                /* Set the effective edge of falling edge. */
                R_MTU1->TIOR_b.IOA = MTU_TIOR_INPUT_FALLING_EDGE;
                R_MTU1->TIOR_b.IOB = MTU_TIOR_INPUT_FALLING_EDGE;
                break;
            }

            case MTU3_PHASE_COUNTING_MODE_201:
            case MTU3_PHASE_COUNTING_MODE_301:
            {
                /* Set the effective edge of rising edge. */
                R_MTU1->TIOR_b.IOA = MTU_TIOR_INPUT_RISING_EDGE;
                R_MTU1->TIOR_b.IOB = MTU_TIOR_INPUT_RISING_EDGE;
                break;
            }
        }
    }

    p_instance_ctrl->open = MTU3_PHASE_COUNT_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops all timers synchronously. Implements @ref mtu3_phase_count_api_t::stop.
 *
 * @retval FSP_SUCCESS                 Timers successfully stopped.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_PHASE_COUNT_Stop (mtu3_phase_count_ctrl_t * const p_ctrl)
{
    mtu3_phase_count_instance_ctrl_t * p_instance_ctrl = (mtu3_phase_count_instance_ctrl_t *) p_ctrl;
#if MTU3_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(MTU3_PHASE_COUNT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Stop timer */
    mtu3_phase_count_stop_timer(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Starts all timers synchronously. Implements @ref mtu3_phase_count_api_t::start.
 *
 * Example:
 * @snippet r_mtu3_phase_count_example.c R_MTU3_PHASE_COUNT_Start
 *
 * @retval FSP_SUCCESS                 Timers successfully started.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_PHASE_COUNT_Start (mtu3_phase_count_ctrl_t * const p_ctrl)
{
    mtu3_phase_count_instance_ctrl_t * p_instance_ctrl = (mtu3_phase_count_instance_ctrl_t *) p_ctrl;
#if MTU3_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(MTU3_PHASE_COUNT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Start timer */
    if (MTU3_BIT_MODE_NORMAL_16BIT == p_instance_ctrl->p_cfg->bit_mode)
    {
        p_instance_ctrl->p_reg_com->TSTRA |= mtu3_tstr_val[p_instance_ctrl->p_cfg->channel];
    }
    else if (MTU3_BIT_MODE_NORMAL_32BIT == p_instance_ctrl->p_cfg->bit_mode)
    {
        if (p_instance_ctrl->p_cfg->channel == MTU3_CHANNEL_1)
        {
            p_instance_ctrl->p_reg_com->TSTRA = (R_MTU_TSTRA_CST1_Msk | R_MTU_TSTRA_CST2_Msk);
        }
    }
    else if (MTU3_BIT_MODE_16BIT == p_instance_ctrl->p_cfg->bit_mode)
    {
        p_instance_ctrl->p_reg_com->TSTRA |= (R_MTU_TSTRA_CST0_Msk | R_MTU_TSTRA_CST1_Msk);
    }
    else
    {
        /* 32-bit mode uses 0-2, 8 */
        p_instance_ctrl->p_reg_com->TSTRA |=
            (R_MTU_TSTRA_CST0_Msk | R_MTU_TSTRA_CST1_Msk | R_MTU_TSTRA_CST2_Msk | R_MTU_TSTRA_CST8_Msk);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Resets the counter values to 0. Implements @ref mtu3_phase_count_api_t::reset.
 *
 * @retval FSP_SUCCESS                 Counters were reset successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_PHASE_COUNT_Reset (mtu3_phase_count_ctrl_t * const p_ctrl)
{
    mtu3_phase_count_instance_ctrl_t * p_instance_ctrl = (mtu3_phase_count_instance_ctrl_t *) p_ctrl;
#if MTU3_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(MTU3_PHASE_COUNT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear timer counter. */
    mtu3_phase_count_set_count(p_instance_ctrl, 0x0U);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set location information
 *
 * Get the MTU3 count value.
 *
 * @retval FSP_SUCCESS                 Count value updated successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_PHASE_COUNT_PositionSet (mtu3_phase_count_ctrl_t * const p_ctrl, uint32_t position)
{
    mtu3_phase_count_instance_ctrl_t * p_instance_ctrl = (mtu3_phase_count_instance_ctrl_t *) p_ctrl;
#if MTU3_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(MTU3_PHASE_COUNT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set to location information counter. */
    mtu3_phase_count_set_count(p_instance_ctrl, position);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get location information.
 *
 * Set the MTU3 count value.
 *
 * @retval FSP_SUCCESS                 Count value geted successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_PHASE_COUNT_PositionGet (mtu3_phase_count_ctrl_t * const p_ctrl, uint32_t * p_position)
{
    mtu3_phase_count_instance_ctrl_t * p_instance_ctrl = (mtu3_phase_count_instance_ctrl_t *) p_ctrl;
#if MTU3_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_position);
    FSP_ERROR_RETURN(MTU3_PHASE_COUNT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Get location information. */
    if ((MTU3_BIT_MODE_32BIT == p_instance_ctrl->p_cfg->bit_mode) ||
        (MTU3_BIT_MODE_NORMAL_32BIT == p_instance_ctrl->p_cfg->bit_mode))
    {
        *p_position = R_MTU1->TCNTLW;
    }
    else
    {
        *p_position =
            *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tcnt_ofs_addr[p_instance_ctrl->p_cfg->channel]);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set the phase counting mode.
 *
 * @retval FSP_SUCCESS                 Configuration setting successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 * @retval FSP_ERR_IN_USE              The timer is running.  Stop the timer before calling this function.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_PHASE_COUNT_ControlModeSet (mtu3_phase_count_ctrl_t * const p_ctrl, mtu3_phase_counting_mode_t mode)
{
    mtu3_phase_count_instance_ctrl_t * p_instance_ctrl = (mtu3_phase_count_instance_ctrl_t *) p_ctrl;
#if MTU3_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(MTU3_PHASE_COUNT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(0U == (p_instance_ctrl->p_reg_com->TSTRA & mtu3_tstr_val[p_instance_ctrl->p_cfg->channel]),
                     FSP_ERR_IN_USE);
#endif

    /* Select phase counting mode. */
    mtu3_phase_count_mode_set(p_instance_ctrl, mode);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set speed cycle.(16-bit mode)
 *
 * @retval FSP_SUCCESS                 Configuration setting successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 * @retval FSP_ERR_INVALID_MODE        When executed in other than 16-bit mode.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_PHASE_COUNT_SpeedControl (mtu3_phase_count_ctrl_t * const p_ctrl, uint16_t speed)
{
    mtu3_phase_count_instance_ctrl_t * p_instance_ctrl = (mtu3_phase_count_instance_ctrl_t *) p_ctrl;
#if MTU3_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(MTU3_PHASE_COUNT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(MTU3_BIT_MODE_16BIT == p_instance_ctrl->p_cfg->bit_mode, FSP_ERR_INVALID_MODE);
#endif

    /* Set the speed cycle */
    if (MTU3_BIT_MODE_16BIT == p_instance_ctrl->p_cfg->bit_mode)
    {
        R_MTU0->TGRA = speed;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get speed information.(16-bit mode)
 *
 * @retval FSP_SUCCESS                 Configuration setting successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 * @retval FSP_ERR_INVALID_MODE        When executed in other than 16-bit mode.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_PHASE_COUNT_SpeedGet (mtu3_phase_count_ctrl_t * const p_ctrl, uint16_t * p_speed)
{
    mtu3_phase_count_instance_ctrl_t * p_instance_ctrl = (mtu3_phase_count_instance_ctrl_t *) p_ctrl;
#if MTU3_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_speed);
    FSP_ERROR_RETURN(MTU3_PHASE_COUNT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(MTU3_BIT_MODE_16BIT == p_instance_ctrl->p_cfg->bit_mode, FSP_ERR_INVALID_MODE);
#endif

    /* Get the speed information(The value is stored in MTU1.TGRA by input capture) */
    if (MTU3_BIT_MODE_16BIT == p_instance_ctrl->p_cfg->bit_mode)
    {
        *p_speed = R_MTU1->TGRA;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback for the MTU3 channel with the option to provide memory for the callback argument
 * structure.
 * Implements @ref mtu3_phase_count_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_PHASE_COUNT_CallbackSet (mtu3_phase_count_ctrl_t * const p_ctrl,
                                          void (                        * p_callback)(timer_callback_args_t *),
                                          void const * const              p_context,
                                          timer_callback_args_t * const   p_callback_memory)
{
    mtu3_phase_count_instance_ctrl_t * p_instance_ctrl = (mtu3_phase_count_instance_ctrl_t *) p_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if MTU3_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_callback);
    FSP_ERROR_RETURN(MTU3_PHASE_COUNT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    err =
        R_MTU3_CallbackSet(p_instance_ctrl->p_cfg->p_timer_instance->p_ctrl, p_callback, p_context, p_callback_memory);

    return err;
}

/*******************************************************************************************************************//**
 * Stops counters, disables output pins, and clears internal driver data. Implements @ref mtu3_phase_count_api_t::close.
 *
 * @retval FSP_SUCCESS                 Successful close.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_PHASE_COUNT_Close (mtu3_phase_count_ctrl_t * const p_ctrl)
{
    mtu3_phase_count_instance_ctrl_t * p_instance_ctrl = (mtu3_phase_count_instance_ctrl_t *) p_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if MTU3_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(MTU3_PHASE_COUNT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear open flag. */
    p_instance_ctrl->open = 0U;

    /* Stop timer */
    mtu3_phase_count_stop_timer(p_instance_ctrl);

    /* Close all MTU3 modules */
    R_MTU3_Close(p_instance_ctrl->p_cfg->p_timer_instance->p_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 * Sets driver version based on compile time macros. Implements @ref mtu3_phase_count_api_t::versionGet.
 *
 * @retval FSP_SUCCESS                 Version stored in p_version.
 * @retval FSP_ERR_ASSERTION           p_version was NULL.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_PHASE_COUNT_VersionGet (fsp_version_t * const p_version)
{
#if MTU3_PHASE_COUNT_CFG_PARAM_CHECKING_ENABLE

    /* Verify parameters are valid */
    FSP_ASSERT(NULL != p_version);
#endif

    p_version->version_id = g_mtu3_phase_count_version.version_id;

    return FSP_SUCCESS;
}

/** @} (end addtogroup MTU3_PHASE_COUNT) */

/*******************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Performs hardware initialization of the MTU3.
 *
 * @param[in]  p_instance_ctrl        Instance control block.
 * @param[in]  p_cfg                  Pointer to timer configuration.
 **********************************************************************************************************************/
static void mtu3_phase_count_hardware_initialize (mtu3_phase_count_instance_ctrl_t * const p_instance_ctrl,
                                                  mtu3_phase_count_cfg_t const * const     p_cfg)
{
    /* Save pointer to extended configuration structure. */
    mtu3_phase_count_extended_cfg_t * p_extend = (mtu3_phase_count_extended_cfg_t *) p_cfg->p_extend;

    /* Normal mode */
    if ((MTU3_BIT_MODE_NORMAL_16BIT == p_cfg->bit_mode) || (MTU3_BIT_MODE_NORMAL_32BIT == p_cfg->bit_mode))
    {
        if (MTU3_BIT_MODE_NORMAL_16BIT == p_cfg->bit_mode)
        {
            /* 16-bit access is enabled. */
            R_MTU1->TMDR3 &= (uint8_t) ~R_MTU1_TMDR3_LWA_Msk;

            /* Select phase counting mode. */
            *((uint8_t *) p_instance_ctrl->p_reg +
              tmdr1_ofs_addr[p_instance_ctrl->p_cfg->channel]) =
                (uint8_t) (p_cfg->counting_mode << R_MTU1_TMDR1_MD_Pos);
        }
        else
        {
            /* 32-bit access is enabled. */
            R_MTU1->TMDR3 = R_MTU1_TMDR3_LWA_Msk;

            /* Select phase counting mode. If LWA = 1, the MTU1 setting takes precedence. */
            R_MTU1->TMDR1 = (uint8_t) (p_cfg->counting_mode << R_MTU1_TMDR1_MD_Pos);
        }

        /* Select A- or B-phase input pin */
        R_MTU1->TMDR3 |= (uint8_t) (p_cfg->external_clock << R_MTU1_TMDR3_PHCKSEL_Pos);
    }
    /* 16-bit application example */
    else if (MTU3_BIT_MODE_16BIT == p_cfg->bit_mode)
    {
        /* 16-bit access is enabled. */
        R_MTU1->TMDR3 = (uint8_t) ~R_MTU1_TMDR3_LWA_Msk;

        /* Select phase counting mode. */
        *((uint8_t *) p_instance_ctrl->p_reg +
          tmdr1_ofs_addr[p_instance_ctrl->p_cfg->channel]) = (uint8_t) (p_cfg->counting_mode << R_MTU1_TMDR1_MD_Pos);

        /* Select A- or B-phase input pin */
        R_MTU1->TMDR3 |= (uint8_t) (p_cfg->external_clock << R_MTU1_TMDR3_PHCKSEL_Pos);

        /* MTU1.TGRA and MTU1.TGRB of MTU1 are set to the input capture function. */
        if (MTU3_PHASE_COUNT_SPEED_DETECTION_ENABLE == p_extend->speed_enable)
        {
            R_MTU1->TIOR_b.IOA = MTU_TIOR_INPUT_BOTH_EDGE;

            /* Set the speed cycle */
            R_MTU0->TGRA = MTU0_TGRA_16BIT_MODE_INITIAL_VAL;
        }
        else
        {
            R_MTU1->TIOR_b.IOA = MTU3_IO_PIN_LEVEL_NO_OUTPUT;
            R_MTU0->TGRA       = MTU_TGR_INITIAL_VAL;
        }

        R_MTU1->TIOR_b.IOB = MTU_TIOR_INPUT_BOTH_EDGE;

        /* Sets TCNT to counter clear with a compare match of MTU0.TGRC */
        R_MTU0->TCR_b.CCLR = MTU0_TCR_CCLR_TGRC_COMPARE;

        /* Set TGRB and TGRD to buffer operation */
        R_MTU0->TMDR1       = (R_MTU0->TMDR1 & (uint8_t) ~(R_MTU0_TMDR1_BFA_Msk | R_MTU0_TMDR1_BFB_Msk));
        R_MTU0->TMDR1_b.BFB = 0x1U;

        /* Set the input capture factor of MTU0.TGRB to the counter input clock of MTU1. */
        R_MTU0->TIORH_b.IOA = MTU3_IO_PIN_LEVEL_NO_OUTPUT;
        R_MTU0->TIORL_b.IOC = MTU3_IO_PIN_LEVEL_NO_OUTPUT;
        R_MTU0->TIORH_b.IOB = MTU0_TIOR_IOA_INPUT_MTU8_TGTC;

        /* Set the control cycle */
        R_MTU0->TGRC = MTU0_TGRC_16BIT_MODE_INITIAL_VAL;
    }
    /* 32-bit application example */
    else
    {
        /* When the LWA bit in MTU1.TMDR3 is set to 1, the TCR, TCR2, TMDR1, and TIOR registers in MTU1 are effective in
         * controlling cascaded operation. */

        /* 32-bit access is enabled. */
        R_MTU1->TMDR3 = R_MTU1_TMDR3_LWA_Msk;

        /* Select phase counting mode. */
        R_MTU1->TMDR1 = (uint8_t) (p_cfg->counting_mode << R_MTU1_TMDR1_MD_Pos);

        /* Select A- or B-phase input pin */
        R_MTU1->TMDR3 |= (uint8_t) (p_cfg->external_clock << R_MTU1_TMDR3_PHCKSEL_Pos);

        /* Set MTU1.TCNTLW count clear factor to MTU1.TGRALW input capture. */
        R_MTU1->TCR_b.CCLR = MTU3_TCNT_CLEAR_TGRA;

        /* Set the effective edge of MTU1.TGRALW input capture. */
        R_MTU1->TIOR_b.IOA = MTU_TIOR_INPUT_RISING_EDGE;

        /* Set the input capture factor of MTU1.TGRBLW to the compare match of MTU8.TGRC. */
        R_MTU1->TIOR_b.IOB = MTU1_TIOR_IOB_INPUT_MTU8_TGRC;

        /* Set the MTU8.TCNT counter clear factor to the MTU8.TRGC compare match. */
        R_MTU8->TCR_b.CCLR = MTU8_TCR_CCLR_TGRC_COMPARE;

        /* Set the input capture factor of MTU8.TGRB to the count clock source of MTU1.TCNTLW */
        R_MTU8->TIORH_b.IOB = MTU8_TIOR_IOB_INPUT_MTU1_TCNT;

        /* Set TGRB and TGRD to buffer operation */
        R_MTU8->TMDR1       = (R_MTU8->TMDR1 & (uint8_t) ~(R_MTU8_TMDR1_BFA_Msk | R_MTU8_TMDR1_BFB_Msk));
        R_MTU8->TMDR1_b.BFB = 0x1U;

        /* Set the control cycle */
        R_MTU8->TGRC = MTU8_TGRC_32BIT_MODE_INITIAL_VAL;

        /* Z-phase signal connects to MITOC1A pin */
        if (MTU3_PHASE_COUNT_Z_PHASE_ENABLE == p_extend->z_phase_enable)
        {
            /* Set the count clock source of MTU0.TCNT to the MTIOC1A pin. */
            R_MTU0->TCR2_b.TPSC2 = MTU0_TCR2_TPSC_MTIOC1A;

            /* Set the MTU0.TCNT counter clear factor to the MTU0.TGRA input capture. */
            R_MTU0->TCR_b.CCLR = MTU3_TCNT_CLEAR_TGRA;

            /* Set MTU0.TGRA input capture factor to MTU8.TGRC compare match. */
            R_MTU0->TIORH_b.IOA = MTU0_TIOR_IOA_INPUT_MTU8_TGTC;
        }
    }
}

/*******************************************************************************************************************//**
 * Stops timer
 *
 * @param[in]  p_instance_ctrl         Instance control structure
 **********************************************************************************************************************/
static void mtu3_phase_count_stop_timer (mtu3_phase_count_instance_ctrl_t * const p_instance_ctrl)
{
    /* Stop timer */
    if ((MTU3_BIT_MODE_32BIT == p_instance_ctrl->p_cfg->bit_mode) ||
        (MTU3_BIT_MODE_NORMAL_32BIT == p_instance_ctrl->p_cfg->bit_mode))
    {
        /* 32-bit mode uses ch0-2, 8 */
        p_instance_ctrl->p_reg_com->TSTRA &=
            (uint8_t) ~(R_MTU_TSTRA_CST0_Msk | R_MTU_TSTRA_CST1_Msk | R_MTU_TSTRA_CST2_Msk | R_MTU_TSTRA_CST8_Msk);
    }
    else
    {
        p_instance_ctrl->p_reg_com->TSTRA &= (uint8_t) ~mtu3_tstr_val[p_instance_ctrl->p_cfg->channel];
    }
}

/*******************************************************************************************************************//**
 * The counter value can only be updated while the counter
 *
 * @param[in]  p_instance_ctrl         Instance control structure
 * @param[in]  counter                 Timer counter
 **********************************************************************************************************************/
static void mtu3_phase_count_set_count (mtu3_phase_count_instance_ctrl_t * const p_instance_ctrl, uint32_t counter)
{
    /* Set timer counter. */
    if ((MTU3_BIT_MODE_32BIT == p_instance_ctrl->p_cfg->bit_mode) ||
        (MTU3_BIT_MODE_NORMAL_32BIT == p_instance_ctrl->p_cfg->bit_mode))
    {
        /* In the case of 32bit, the position information (encoder counter) is stored in MTU1. */
        R_MTU1->TCNTLW = counter;
    }
    else
    {
        *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg +
                       tcnt_ofs_addr[p_instance_ctrl->p_cfg->channel]) = (uint16_t) counter;
    }
}

/*******************************************************************************************************************//**
 * Performs phase_count_mode_set of the MTU3.
 *
 * @param[in]  p_instance_ctrl        Instance control block.
 * @param[in]  mode                   Set the mode.
 **********************************************************************************************************************/
static void mtu3_phase_count_mode_set (mtu3_phase_count_instance_ctrl_t * const p_instance_ctrl,
                                       mtu3_phase_counting_mode_t               mode)
{
    switch (mode)
    {
        case MTU3_PHASE_COUNTING_MODE_1:
        {
            *((uint8_t *) p_instance_ctrl->p_reg +
              tmdr1_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_1_MD;
            break;
        }

        case MTU3_PHASE_COUNTING_MODE_200:
        {
            *((uint8_t *) p_instance_ctrl->p_reg +
              tmdr1_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_2_MD;
            *((uint8_t *) p_instance_ctrl->p_reg +
              tcr2_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_PCB_0;
            break;
        }

        case MTU3_PHASE_COUNTING_MODE_201:
        {
            *((uint8_t *) p_instance_ctrl->p_reg +
              tmdr1_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_2_MD;
            *((uint8_t *) p_instance_ctrl->p_reg +
              tcr2_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_PCB_1;
            break;
        }

        case MTU3_PHASE_COUNTING_MODE_210:
        {
            *((uint8_t *) p_instance_ctrl->p_reg +
              tmdr1_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_2_MD;
            *((uint8_t *) p_instance_ctrl->p_reg +
              tcr2_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_PCB_2;
            break;
        }

        case MTU3_PHASE_COUNTING_MODE_300:
        {
            *((uint8_t *) p_instance_ctrl->p_reg +
              tmdr1_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_3_MD;
            *((uint8_t *) p_instance_ctrl->p_reg +
              tcr2_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_PCB_0;
            break;
        }

        case MTU3_PHASE_COUNTING_MODE_301:
        {
            *((uint8_t *) p_instance_ctrl->p_reg +
              tmdr1_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_3_MD;
            *((uint8_t *) p_instance_ctrl->p_reg +
              tcr2_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_PCB_1;
            break;
        }

        case MTU3_PHASE_COUNTING_MODE_310:
        {
            *((uint8_t *) p_instance_ctrl->p_reg +
              tmdr1_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_3_MD;
            *((uint8_t *) p_instance_ctrl->p_reg +
              tcr2_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_PCB_2;
            break;
        }

        case MTU3_PHASE_COUNTING_MODE_4:
        {
            *((uint8_t *) p_instance_ctrl->p_reg +
              tmdr1_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_4_MD;
            break;
        }

        case MTU3_PHASE_COUNTING_MODE_50:
        {
            *((uint8_t *) p_instance_ctrl->p_reg +
              tmdr1_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_5_MD;
            *((uint8_t *) p_instance_ctrl->p_reg +
              tcr2_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_PCB_0;
            break;
        }

        case MTU3_PHASE_COUNTING_MODE_51:
        {
            *((uint8_t *) p_instance_ctrl->p_reg +
              tmdr1_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_5_MD;
            *((uint8_t *) p_instance_ctrl->p_reg +
              tcr2_ofs_addr[p_instance_ctrl->p_cfg->channel]) = MTU3_PHASE_COUNTING_MODE_PCB_1;
            break;
        }

        default:
        {
            break;
        }
    }
}
