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
#include "r_mtu3_cfg.h"
#include "r_mtu3.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "MTU3" in ASCII, used to determine if channel is open. */
#define MTU3_OPEN                           (0x4D545533ULL)

/* MTU3_CFG_OUTPUT_SUPPORT_ENABLE is set to 2 to enable extra features. */
#define MTU3_PRV_EXTRA_FEATURES_ENABLED     (2U)

/* MTU3_CFG_UVW_SUPPORT_ENABLE is set to 3 to enable extra features. */
#define MTU3_PRV_UVW_FEATURES_ENABLED       (3U)

#define MTU3_TOERA_MSK                      (R_MTU_TOERA_OE4D_Msk | R_MTU_TOERA_OE4C_Msk | R_MTU_TOERA_OE3D_Msk | \
                                             R_MTU_TOERA_OE4B_Msk | R_MTU_TOERA_OE4A_Msk | R_MTU_TOERA_OE3B_Msk)

#define MTU3_TOERB_MSK                      (R_MTU_TOERB_OE7D_Msk | R_MTU_TOERB_OE7C_Msk | R_MTU_TOERB_OE6D_Msk | \
                                             R_MTU_TOERB_OE7B_Msk | R_MTU_TOERB_OE7A_Msk | R_MTU_TOERB_OE6B_Msk)

#define MTU3_TCR_TPSC_POS                   (3U) /* MTUx.TCR.TPSC bit2-0 */
#define MTU3_TCR_TPSC_POS_CH5               (2U) /* MTU5.TCR.TPSC bit1-0 */

#define MTU3_PCLK_DIV_1                     (1U)
#define MTU3_PCLK_DIV_2                     (2U)
#define MTU3_PCLK_DIV_4                     (4U)
#define MTU3_PCLK_DIV_8                     (8U)
#define MTU3_PCLK_DIV_16                    (16U)
#define MTU3_PCLK_DIV_32                    (32U)
#define MTU3_PCLK_DIV_64                    (64U)
#define MTU3_PCLK_DIV_256                   (256U)
#define MTU3_PCLK_DIV_1024                  (1024U)

#define MTU3_TPSC_OFS_ARRAY                 (8U)  /* MTUxTCR.TPSC bit2-0(The value is 0-7) */
#define MTU3_TPSC_OFS_ARRAY_CH5             (4U)  /* MTU5TCR.TPSC bit1-0(The value is 0-3) */

#define MTU3_CLK_TPSC_NUM                   (15U) /* TPSC and TPSC2 setting range */

/* Noise fileter offset address */
#define MTU0_NOISEFILTER_OFFSET_ADDRESS     (0x0000U)
#define MTU1_NOISEFILTER_OFFSET_ADDRESS     (0x0001U)
#define MTU2_NOISEFILTER_OFFSET_ADDRESS     (0x0002U)
#define MTU3_NOISEFILTER_OFFSET_ADDRESS     (0x0003U)
#define MTU4_NOISEFILTER_OFFSET_ADDRESS     (0x0004U)
#define MTU5_NOISEFILTER_OFFSET_ADDRESS     (0x0805U)
#define MTU6_NOISEFILTER_OFFSET_ADDRESS     (0x0803U)
#define MTU7_NOISEFILTER_OFFSET_ADDRESS     (0x0804U)
#define MTU8_NOISEFILTER_OFFSET_ADDRESS     (0x0008U)
#define MTU_NOISEFILTER_C_OFFSET_ADDRESS    (0x0009U)

/* MTUx.TCR offset address */
#define MTU0_TCR_OFFSET_ADDRESS             (0x0000U)
#define MTU1_TCR_OFFSET_ADDRESS             (0x0000U)
#define MTU2_TCR_OFFSET_ADDRESS             (0x0000U)
#define MTU3_TCR_OFFSET_ADDRESS             (0x0100U)
#define MTU4_TCR_OFFSET_ADDRESS             (0x0001U)
#define MTU5_TCR_OFFSET_ADDRESS             (0x0084U)
#define MTU6_TCR_OFFSET_ADDRESS             (0x0100U)
#define MTU7_TCR_OFFSET_ADDRESS             (0x0001U)
#define MTU8_TCR_OFFSET_ADDRESS             (0x0000U)

/* MTUx.TCR2 offset address */
#define MTU0_TCR2_OFFSET_ADDRESS            (0x0028U)
#define MTU1_TCR2_OFFSET_ADDRESS            (0x0014U)
#define MTU2_TCR2_OFFSET_ADDRESS            (0x000CU)
#define MTU3_TCR2_OFFSET_ADDRESS            (0x014CU)
#define MTU4_TCR2_OFFSET_ADDRESS            (0x004DU)
#define MTU5_TCR2_OFFSET_ADDRESS            (0x0085U)
#define MTU6_TCR2_OFFSET_ADDRESS            (0x014CU)
#define MTU7_TCR2_OFFSET_ADDRESS            (0x004DU)
#define MTU8_TCR2_OFFSET_ADDRESS            (0x0006U)

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

/* MTUx.TIOR offset address */
#define MTU0_TIOR_OFFSET_ADDRESS            (0x0002U)
#define MTU1_TIOR_OFFSET_ADDRESS            (0x0002U)
#define MTU2_TIOR_OFFSET_ADDRESS            (0x0002U)
#define MTU3_TIOR_OFFSET_ADDRESS            (0x0104U)
#define MTU4_TIOR_OFFSET_ADDRESS            (0x0006U)
#define MTU5_TIOR_OFFSET_ADDRESS            (0x0086U)
#define MTU6_TIOR_OFFSET_ADDRESS            (0x0104U)
#define MTU7_TIOR_OFFSET_ADDRESS            (0x0006U)
#define MTU8_TIOR_OFFSET_ADDRESS            (0x0002U)

/* MTUx.TIER offset address */
#define MTU0_TIER_OFFSET_ADDRESS            (0x0004U)
#define MTU1_TIER_OFFSET_ADDRESS            (0x0004U)
#define MTU2_TIER_OFFSET_ADDRESS            (0x0004U)
#define MTU3_TIER_OFFSET_ADDRESS            (0x0108U)
#define MTU4_TIER_OFFSET_ADDRESS            (0x0009U)
#define MTU5_TIER_OFFSET_ADDRESS            (0x00B2U)
#define MTU6_TIER_OFFSET_ADDRESS            (0x0108U)
#define MTU7_TIER_OFFSET_ADDRESS            (0x0009U)
#define MTU8_TIER_OFFSET_ADDRESS            (0x0004U)

/* MTUx.TSR offset address */
#define MTU0_TSR_OFFSET_ADDRESS             (0x0000U) /* Nothing */
#define MTU1_TSR_OFFSET_ADDRESS             (0x0005U)
#define MTU2_TSR_OFFSET_ADDRESS             (0x0005U)
#define MTU3_TSR_OFFSET_ADDRESS             (0x012CU)
#define MTU4_TSR_OFFSET_ADDRESS             (0x002DU)
#define MTU5_TSR_OFFSET_ADDRESS             (0x0000U) /* Nothing */
#define MTU6_TSR_OFFSET_ADDRESS             (0x012CU)
#define MTU7_TSR_OFFSET_ADDRESS             (0x002DU)
#define MTU8_TSR_OFFSET_ADDRESS             (0x0000U) /* Nothing */

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

/* MTUx.TGRC offset address */
#define MTU0_TGRC_OFFSET_ADDRESS            (0x000CU)
#define MTU1_TGRC_OFFSET_ADDRESS            (0x000AU) /* Nothing */
#define MTU2_TGRC_OFFSET_ADDRESS            (0x000AU) /* Nothing */
#define MTU3_TGRC_OFFSET_ADDRESS            (0x0124U)
#define MTU4_TGRC_OFFSET_ADDRESS            (0x0028U)
#define MTU5_TGRC_OFFSET_ADDRESS            (0x0082U) /* Nothing */
#define MTU6_TGRC_OFFSET_ADDRESS            (0x0124U)
#define MTU7_TGRC_OFFSET_ADDRESS            (0x0028U)
#define MTU8_TGRC_OFFSET_ADDRESS            (0x0014U)

/* MTUx.TADCR offset address */
#define MTU0_TADCR_OFFSET_ADDRESS           (0x0000U) /* Nothing */
#define MTU1_TADCR_OFFSET_ADDRESS           (0x0000U) /* Nothing */
#define MTU2_TADCR_OFFSET_ADDRESS           (0x0000U) /* Nothing */
#define MTU3_TADCR_OFFSET_ADDRESS           (0x0000U) /* Nothing */
#define MTU4_TADCR_OFFSET_ADDRESS           (0x0040U)
#define MTU5_TADCR_OFFSET_ADDRESS           (0x0000U) /* Nothing */
#define MTU6_TADCR_OFFSET_ADDRESS           (0x0000U) /* Nothing */
#define MTU7_TADCR_OFFSET_ADDRESS           (0x0040U)
#define MTU8_TADCR_OFFSET_ADDRESS           (0x0000U) /* Nothing */

/* TGR offset address */
#define MTU3_TGRB_D_OFFSET_WORD             (0x2U)
#define MTU3_TGRB_D_OFFSET_LONG             (0x4U)
#define MTU3_TGRU_OFFSET_WORD               (0x0U)
#define MTU3_TGRV_OFFSET_WORD               (0x10U)
#define MTU3_TGRW_OFFSET_WORD               (0x20U)

/* UVW offset address(ch5) */
#define MTU5_U_OFFSET_ADDRESS               (0x0U)
#define MTU5_V_OFFSET_ADDRESS               (0x10U)
#define MTU5_W_OFFSET_ADDRESS               (0x20U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef enum e_mtu3_prv_capture_event
{
    MTU3_PRV_CAPTURE_EVENT_A = 0U,
    MTU3_PRV_CAPTURE_EVENT_B = 1U,
    MTU3_PRV_CAPTURE_EVENT_U = 6U,
    MTU3_PRV_CAPTURE_EVENT_V = 7U,
    MTU3_PRV_CAPTURE_EVENT_W = 8U,
} mtu3_prv_capture_event_t;

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

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void     mtu3_hardware_initialize(mtu3_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg);
static void     mtu3_counter_initialize(mtu3_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg);
static void     mtu3_common_open(mtu3_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg);
static void     mtu3_set_count(mtu3_instance_ctrl_t * const p_instance_ctrl, uint32_t counter);
static void     mtu3_stop_timer(mtu3_instance_ctrl_t * const p_instance_ctrl);
static uint32_t mtu3_clock_frequency_get(mtu3_instance_ctrl_t * const p_instance_ctrl, uint32_t ch_addr_ofs);
static uint8_t  mtu3_get_tstr(mtu3_instance_ctrl_t * const p_instance_ctrl);
static void     r_mtu3_disable_irq(IRQn_Type irq);
static void     r_mtu3_enable_irq(IRQn_Type const irq, uint32_t priority, void * p_context) __attribute__((noinline));
static void     mtu3_enable_interrupt(mtu3_instance_ctrl_t * const p_instance_ctrl);
static void     mtu3_disable_interrupt(mtu3_instance_ctrl_t * const p_instance_ctrl);
static void     r_mtu3_call_callback(mtu3_instance_ctrl_t * p_ctrl, timer_event_t event, uint32_t capture);

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/
void mtu3_counter_overflow_isr(void);
void mtu3_counter_underflow_isr(void);
void mtu3_capture_a_isr(void);
void mtu3_capture_b_isr(void);
void mtu3_capture_u_isr(void);
void mtu3_capture_v_isr(void);
void mtu3_capture_w_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Version data structure used by error logger macro. */
static const fsp_version_t g_mtu3_version =
{
    .api_version_minor  = TIMER_API_VERSION_MINOR,
    .api_version_major  = TIMER_API_VERSION_MAJOR,
    .code_version_major = MTU3_CODE_VERSION_MAJOR,
    .code_version_minor = MTU3_CODE_VERSION_MINOR
};

/* Divided value table of MTU3. */
/* Defined based on the values of TCR.TPSC and TCR2.TPSC2.(External clock(MTCLKA, MTIOC1A, etc) is defined as 1 division) */
/* [0]-[7]: TCR.TPSC setting value. [8]-[15]: TCR2.TPSC2 setting value(For other than ch5) */
/* [0]-[3]: TCR.TPSC setting value. [4]-[12]: TCR2.TPSC2-TCR2.CKEG setting value(For ch5) */
static const uint16_t mtu3_clk_div[BSP_FEATURE_MTU3_MAX_CHANNELS][MTU3_CLK_TPSC_NUM] =
{
    {MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_4, MTU3_PCLK_DIV_16, MTU3_PCLK_DIV_64, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1,      /* MTU ch0 */
     MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_2, MTU3_PCLK_DIV_8, MTU3_PCLK_DIV_32, MTU3_PCLK_DIV_256,
     MTU3_PCLK_DIV_1024, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1},
    {MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_4, MTU3_PCLK_DIV_16, MTU3_PCLK_DIV_64, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1,      /* MTU ch1 */
     MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_2, MTU3_PCLK_DIV_8, MTU3_PCLK_DIV_32, MTU3_PCLK_DIV_1024,
     MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1},
    {MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_4, MTU3_PCLK_DIV_16, MTU3_PCLK_DIV_64, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1,      /* MTU ch2 */
     MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1024, MTU3_PCLK_DIV_2, MTU3_PCLK_DIV_8, MTU3_PCLK_DIV_32, MTU3_PCLK_DIV_256,
     MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1},
    {MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_4, MTU3_PCLK_DIV_16, MTU3_PCLK_DIV_64, MTU3_PCLK_DIV_256, MTU3_PCLK_DIV_1024, /* MTU ch3 */
     MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_2, MTU3_PCLK_DIV_8, MTU3_PCLK_DIV_32, MTU3_PCLK_DIV_1,
     MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1},
    {MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_4, MTU3_PCLK_DIV_16, MTU3_PCLK_DIV_64, MTU3_PCLK_DIV_256, MTU3_PCLK_DIV_1024, /* MTU ch4 */
     MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_2, MTU3_PCLK_DIV_8, MTU3_PCLK_DIV_32, MTU3_PCLK_DIV_1,
     MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1},
    {MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_4, MTU3_PCLK_DIV_16, MTU3_PCLK_DIV_64, MTU3_PCLK_DIV_2, MTU3_PCLK_DIV_8,      /* MTU ch5 */
     MTU3_PCLK_DIV_32, MTU3_PCLK_DIV_256, MTU3_PCLK_DIV_1024, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1,
     MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1},
    {MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_4, MTU3_PCLK_DIV_16, MTU3_PCLK_DIV_64, MTU3_PCLK_DIV_256, MTU3_PCLK_DIV_1024, /* MTU ch6 */
     MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_2, MTU3_PCLK_DIV_8, MTU3_PCLK_DIV_32, MTU3_PCLK_DIV_1,
     MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1},
    {MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_4, MTU3_PCLK_DIV_16, MTU3_PCLK_DIV_64, MTU3_PCLK_DIV_256, MTU3_PCLK_DIV_1024, /* MTU ch7 */
     MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_2, MTU3_PCLK_DIV_8, MTU3_PCLK_DIV_32, MTU3_PCLK_DIV_1,
     MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1},
    {MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_4, MTU3_PCLK_DIV_16, MTU3_PCLK_DIV_64, MTU3_PCLK_DIV_256, MTU3_PCLK_DIV_1024, /* MTU ch8 */
     MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_2, MTU3_PCLK_DIV_8, MTU3_PCLK_DIV_32, MTU3_PCLK_DIV_1,
     MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1, MTU3_PCLK_DIV_1},
};

/* MTUx base address */
static const uint32_t volatile * p_mtu3_base_address[BSP_FEATURE_MTU3_MAX_CHANNELS] =
{
    (uint32_t *) R_MTU0,               /* 0x90001300UL */
    (uint32_t *) R_MTU1,               /* 0x90001380UL */
    (uint32_t *) R_MTU2,               /* 0x90001400UL */
    (uint32_t *) R_MTU3,               /* 0x90001100UL */
    (uint32_t *) R_MTU4,               /* 0x90001200UL */
    (uint32_t *) R_MTU5,               /* 0x90001C00UL */
    (uint32_t *) R_MTU6,               /* 0x90001900UL */
    (uint32_t *) R_MTU7,               /* 0x90001A00UL */
    (uint32_t *) R_MTU8,               /* 0x90001600UL */
};

/* Noise fileter offset address */
static const uint32_t nfcr_ofs_addr[BSP_FEATURE_MTU3_MAX_CHANNELS] =
{
    MTU0_NOISEFILTER_OFFSET_ADDRESS,
    MTU1_NOISEFILTER_OFFSET_ADDRESS,
    MTU2_NOISEFILTER_OFFSET_ADDRESS,
    MTU3_NOISEFILTER_OFFSET_ADDRESS,
    MTU4_NOISEFILTER_OFFSET_ADDRESS,
    MTU5_NOISEFILTER_OFFSET_ADDRESS,
    MTU6_NOISEFILTER_OFFSET_ADDRESS,
    MTU7_NOISEFILTER_OFFSET_ADDRESS,
    MTU8_NOISEFILTER_OFFSET_ADDRESS,
};

/* MTUx.TCR offset address */
static const uint32_t tcr_ofs_addr[BSP_FEATURE_MTU3_MAX_CHANNELS] =
{
    MTU0_TCR_OFFSET_ADDRESS,
    MTU1_TCR_OFFSET_ADDRESS,
    MTU2_TCR_OFFSET_ADDRESS,
    MTU3_TCR_OFFSET_ADDRESS,
    MTU4_TCR_OFFSET_ADDRESS,
    MTU5_TCR_OFFSET_ADDRESS,
    MTU6_TCR_OFFSET_ADDRESS,
    MTU7_TCR_OFFSET_ADDRESS,
    MTU8_TCR_OFFSET_ADDRESS,
};

/* MTUx.TCR2 offset address */
static const uint32_t tcr2_ofs_addr[BSP_FEATURE_MTU3_MAX_CHANNELS] =
{
    MTU0_TCR2_OFFSET_ADDRESS,
    MTU1_TCR2_OFFSET_ADDRESS,
    MTU2_TCR2_OFFSET_ADDRESS,
    MTU3_TCR2_OFFSET_ADDRESS,
    MTU4_TCR2_OFFSET_ADDRESS,
    MTU5_TCR2_OFFSET_ADDRESS,
    MTU6_TCR2_OFFSET_ADDRESS,
    MTU7_TCR2_OFFSET_ADDRESS,
    MTU8_TCR2_OFFSET_ADDRESS,
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

/* MTUx.TIOR offset address */
static const uint32_t tior_ofs_addr[BSP_FEATURE_MTU3_MAX_CHANNELS] =
{
    MTU0_TIOR_OFFSET_ADDRESS,
    MTU1_TIOR_OFFSET_ADDRESS,
    MTU2_TIOR_OFFSET_ADDRESS,
    MTU3_TIOR_OFFSET_ADDRESS,
    MTU4_TIOR_OFFSET_ADDRESS,
    MTU5_TIOR_OFFSET_ADDRESS,
    MTU6_TIOR_OFFSET_ADDRESS,
    MTU7_TIOR_OFFSET_ADDRESS,
    MTU8_TIOR_OFFSET_ADDRESS,
};

/* MTUx.TIER offset address */
static const uint32_t tier_ofs_addr[BSP_FEATURE_MTU3_MAX_CHANNELS] =
{
    MTU0_TIER_OFFSET_ADDRESS,
    MTU1_TIER_OFFSET_ADDRESS,
    MTU2_TIER_OFFSET_ADDRESS,
    MTU3_TIER_OFFSET_ADDRESS,
    MTU4_TIER_OFFSET_ADDRESS,
    MTU5_TIER_OFFSET_ADDRESS,
    MTU6_TIER_OFFSET_ADDRESS,
    MTU7_TIER_OFFSET_ADDRESS,
    MTU8_TIER_OFFSET_ADDRESS,
};

/* MTUx.TSR offset address */
static const uint32_t tsr_ofs_addr[BSP_FEATURE_MTU3_MAX_CHANNELS] =
{
    MTU0_TSR_OFFSET_ADDRESS,
    MTU1_TSR_OFFSET_ADDRESS,
    MTU2_TSR_OFFSET_ADDRESS,
    MTU3_TSR_OFFSET_ADDRESS,
    MTU4_TSR_OFFSET_ADDRESS,
    MTU5_TSR_OFFSET_ADDRESS,
    MTU6_TSR_OFFSET_ADDRESS,
    MTU7_TSR_OFFSET_ADDRESS,
    MTU8_TSR_OFFSET_ADDRESS,
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

/* MTUx.TGRA offset address */
static const uint32_t tgra_ofs_addr[BSP_FEATURE_MTU3_MAX_CHANNELS] =
{
    MTU0_TGRA_OFFSET_ADDRESS,
    MTU1_TGRA_OFFSET_ADDRESS,
    MTU2_TGRA_OFFSET_ADDRESS,
    MTU3_TGRA_OFFSET_ADDRESS,
    MTU4_TGRA_OFFSET_ADDRESS,
    MTU5_TGRA_OFFSET_ADDRESS,          /* (Nothing) */
    MTU6_TGRA_OFFSET_ADDRESS,
    MTU7_TGRA_OFFSET_ADDRESS,
    MTU8_TGRA_OFFSET_ADDRESS,
};

/* MTUx.TGRC offset address */
static const uint32_t tgrc_ofs_addr[BSP_FEATURE_MTU3_MAX_CHANNELS] =
{
    MTU0_TGRC_OFFSET_ADDRESS,
    MTU1_TGRC_OFFSET_ADDRESS,          /* (Nothing) */
    MTU2_TGRC_OFFSET_ADDRESS,          /* (Nothing) */
    MTU3_TGRC_OFFSET_ADDRESS,
    MTU4_TGRC_OFFSET_ADDRESS,
    MTU5_TGRC_OFFSET_ADDRESS,          /* (Nothing) */
    MTU6_TGRC_OFFSET_ADDRESS,
    MTU7_TGRC_OFFSET_ADDRESS,
    MTU8_TGRC_OFFSET_ADDRESS,
};

/* MTUx.TADCR offset address */
static const uint32_t tadcr_ofs_addr[BSP_FEATURE_MTU3_MAX_CHANNELS] =
{
    MTU0_TADCR_OFFSET_ADDRESS,         /* Nothing */
    MTU1_TADCR_OFFSET_ADDRESS,         /* Nothing */
    MTU2_TADCR_OFFSET_ADDRESS,         /* Nothing */
    MTU3_TADCR_OFFSET_ADDRESS,         /* Nothing */
    MTU4_TADCR_OFFSET_ADDRESS,
    MTU5_TADCR_OFFSET_ADDRESS,         /* Nothing */
    MTU6_TADCR_OFFSET_ADDRESS,         /* Nothing */
    MTU7_TADCR_OFFSET_ADDRESS,
    MTU8_TADCR_OFFSET_ADDRESS,         /* Nothing */
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

/* MTU3 implementation of timer interface  */
const timer_api_t g_timer_on_mtu3 =
{
    .open        = R_MTU3_Open,
    .stop        = R_MTU3_Stop,
    .start       = R_MTU3_Start,
    .reset       = R_MTU3_Reset,
    .callbackSet = R_MTU3_CallbackSet,
    .close       = R_MTU3_Close,
    .versionGet  = R_MTU3_VersionGet
};

/*******************************************************************************************************************//**
 * @addtogroup MTU3
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes the timer module and applies configurations.
 *
 * The MTU3 implementation of the general timer can accept a mtu3_extended_cfg_t extension parameter.
 *
 * Example:
 * @snippet r_mtu3_example.c R_MTU3_Open
 *
 * @retval FSP_SUCCESS                    Initialization was successful and timer has started.
 * @retval FSP_ERR_ASSERTION              A required input pointer is NULL.
 * @retval FSP_ERR_ALREADY_OPEN           Module is already open.
 * @retval FSP_ERR_INVALID_MODE           PWM is only supported if MTU3_CFG_OUTPUT_SUPPORT_ENABLE is 2.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The channel requested in the p_cfg parameter is not available on this device.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_Open (timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg)
{
    mtu3_instance_ctrl_t * p_instance_ctrl = (mtu3_instance_ctrl_t *) p_ctrl;
#if MTU3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(p_cfg->mode != TIMER_MODE_ONE_SHOT, FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN(p_cfg->mode <= TIMER_MODE_PWM, FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN(MTU3_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /** mask_bit MTU3 0-8bit*/
    p_instance_ctrl->channel_mask = (1U << p_cfg->channel);

#if MTU3_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN((p_instance_ctrl->channel_mask & BSP_FEATURE_MTU3_VALID_CHANNEL_MASK),
                     FSP_ERR_IP_CHANNEL_NOT_PRESENT);
#endif

    /* Initialize control structure based on configurations. */
    mtu3_common_open(p_instance_ctrl, p_cfg);

    mtu3_hardware_initialize(p_instance_ctrl, p_cfg);

    p_instance_ctrl->open = MTU3_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops timer.
 *
 * Example:
 * @snippet r_mtu3_example.c R_MTU3_Stop
 *
 * @retval FSP_SUCCESS                 Timer successfully stopped.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_Stop (timer_ctrl_t * const p_ctrl)
{
    mtu3_instance_ctrl_t * p_instance_ctrl = (mtu3_instance_ctrl_t *) p_ctrl;
#if MTU3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(MTU3_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Stop timer */
    mtu3_stop_timer(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Starts timer.
 *
 * Example:
 * @snippet r_mtu3_example.c R_MTU3_Start
 *
 * @retval FSP_SUCCESS                 Timer successfully started.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_Start (timer_ctrl_t * const p_ctrl)
{
    mtu3_instance_ctrl_t * p_instance_ctrl = (mtu3_instance_ctrl_t *) p_ctrl;
#if MTU3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(MTU3_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Start timer */
    if ((MTU3_CHANNEL_6 == p_instance_ctrl->p_cfg->channel) || (MTU3_CHANNEL_7 == p_instance_ctrl->p_cfg->channel))
    {
        p_instance_ctrl->p_reg_com->TSTRB |= mtu3_tstr_val[p_instance_ctrl->p_cfg->channel];
    }

#if MTU3_PRV_UVW_FEATURES_ENABLED == MTU3_CFG_UVW_SUPPORT_ENABLE
    else if (MTU3_CHANNEL_5 == p_instance_ctrl->p_cfg->channel)
    {
        /* Since it is a register dedicated to MTU5, set it directly. */
        R_MTU5->TSTR = (R_MTU5_TSTR_CSTW5_Msk | R_MTU5_TSTR_CSTV5_Msk | R_MTU5_TSTR_CSTU5_Msk);
    }
#endif
    else
    {
        p_instance_ctrl->p_reg_com->TSTRA |= mtu3_tstr_val[p_instance_ctrl->p_cfg->channel];
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Resets the counter value to 0.
 *
 * @note This function also updates to the new period if no counter overflow has occurred since the last call to
 * R_MTU3_PeriodSet().
 *
 * @retval FSP_SUCCESS                 Counter value written successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_Reset (timer_ctrl_t * const p_ctrl)
{
    mtu3_instance_ctrl_t * p_instance_ctrl = (mtu3_instance_ctrl_t *) p_ctrl;
#if MTU3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(MTU3_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    mtu3_set_count(p_instance_ctrl, 0U);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets period value provided. If the timer is running, the period will be updated after the next compare match.
 * If the timer is stopped, this function resets the counter and updates the period.
 *
 * Example:
 * @snippet r_mtu3_example.c R_MTU3_PeriodSet
 *
 * @retval FSP_SUCCESS                 Period value written successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_PeriodSet (timer_ctrl_t * const p_ctrl, mtu3_counter_t * const p_counter)
{
    mtu3_instance_ctrl_t * p_instance_ctrl = (mtu3_instance_ctrl_t *) p_ctrl;
#if MTU3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(MTU3_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* In the case of ch5, there is no buffer register, so set a value in TGR and exit. */
#if MTU3_PRV_UVW_FEATURES_ENABLED == MTU3_CFG_UVW_SUPPORT_ENABLE
    if (MTU3_CHANNEL_5 == p_instance_ctrl->p_cfg->channel)
    {
        *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg +
                       tgra_ofs_addr[p_instance_ctrl->p_cfg->channel]) = (uint16_t) (p_counter->tgru_counts - 1U);
        *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgra_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                       MTU5_V_OFFSET_ADDRESS) = (uint16_t) (p_counter->tgrv_counts - 1U);
        *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgra_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                       MTU5_W_OFFSET_ADDRESS) = (uint16_t) (p_counter->tgrw_counts - 1U);

        return FSP_SUCCESS;
    }
#endif

    /* Update period buffer register. The actual period is one cycle longer than the register value.
     * Reference section 17.6.3 "Note on Period Setting" */
    uint32_t new_tgra_counts = p_counter->tgra_counts - 1U;
    uint32_t new_tgrb_counts = p_counter->tgrb_counts - 1U;

    /* Update period register and reset counter. */
    if (MTU3_CHANNEL_8 == p_instance_ctrl->p_cfg->channel)
    {
        /* If the counter is not counting, TGRA and TGRB update */
        if (0U == mtu3_get_tstr(p_instance_ctrl))
        {
            *(uint32_t *) ((uint8_t *) p_instance_ctrl->p_reg +
                           tgra_ofs_addr[p_instance_ctrl->p_cfg->channel]) = new_tgra_counts;
            *(uint32_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgra_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                           MTU3_TGRB_D_OFFSET_LONG) = new_tgrb_counts;
        }

        *(uint32_t *) ((uint8_t *) p_instance_ctrl->p_reg +
                       tgrc_ofs_addr[p_instance_ctrl->p_cfg->channel]) = new_tgra_counts;
        *(uint32_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgrc_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                       MTU3_TGRB_D_OFFSET_LONG) = new_tgrb_counts;
    }
    else if ((MTU3_CHANNEL_1 == p_instance_ctrl->p_cfg->channel) ||
             (MTU3_CHANNEL_2 == p_instance_ctrl->p_cfg->channel))
    {
        /* MTU1 and 2 without TGRC and TGRD should write TGRA and TGRB */
        *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg +
                       tgra_ofs_addr[p_instance_ctrl->p_cfg->channel]) = (uint16_t) new_tgra_counts;
        *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgra_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                       MTU3_TGRB_D_OFFSET_WORD) = (uint16_t) new_tgrb_counts;
    }
    else
    {
        /* If the counter is not counting, TGRA and TGRB update */
        if (0U == mtu3_get_tstr(p_instance_ctrl))
        {
            *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg +
                           tgra_ofs_addr[p_instance_ctrl->p_cfg->channel]) = (uint16_t) new_tgra_counts;
            *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgra_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                           MTU3_TGRB_D_OFFSET_WORD) = (uint16_t) new_tgrb_counts;
        }

        *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg +
                       tgrc_ofs_addr[p_instance_ctrl->p_cfg->channel]) = (uint16_t) new_tgra_counts;
        *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgrc_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                       MTU3_TGRB_D_OFFSET_WORD) = (uint16_t) new_tgrb_counts;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get timer information and store it in provided pointer p_info.
 *
 * @retval FSP_SUCCESS                 TGRx, count direction, frequency, structure successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_info was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_InfoGet (timer_ctrl_t * const p_ctrl, mtu3_info_t * const p_info)
{
    mtu3_instance_ctrl_t * p_instance_ctrl = (mtu3_instance_ctrl_t *) p_ctrl;
#if MTU3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_info);
    FSP_ERROR_RETURN(MTU3_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Get tgrx value */
    if (MTU3_CHANNEL_8 == p_instance_ctrl->p_cfg->channel)
    {
        p_info->count_param.tgra_counts =
            *(uint32_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgra_ofs_addr[p_instance_ctrl->p_cfg->channel]);
        p_info->count_param.tgrb_counts =
            *(uint32_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgra_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                           MTU3_TGRB_D_OFFSET_LONG);
    }

#if MTU3_PRV_UVW_FEATURES_ENABLED == MTU3_CFG_UVW_SUPPORT_ENABLE
    else if (MTU3_CHANNEL_5 == p_instance_ctrl->p_cfg->channel)
    {
        /* Since it is a register dedicated to MTU5, get it directly. */
        p_info->count_param.tgru_counts = R_MTU5->TGRU;
        p_info->count_param.tgrv_counts = R_MTU5->TGRV;
        p_info->count_param.tgrw_counts = R_MTU5->TGRW;
    }
#endif
    else
    {
        p_info->count_param.tgra_counts =
            *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgra_ofs_addr[p_instance_ctrl->p_cfg->channel]);
        p_info->count_param.tgrb_counts =
            *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgra_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                           MTU3_TGRB_D_OFFSET_WORD);
    }

    /* Get and store clock frequency */
    if (MTU3_CHANNEL_5 != p_instance_ctrl->p_cfg->channel)
    {
        p_info->clock_frequency[0] = mtu3_clock_frequency_get(p_instance_ctrl, 0U);
    }

#if MTU3_PRV_UVW_FEATURES_ENABLED == MTU3_CFG_UVW_SUPPORT_ENABLE
    else
    {
        for (uint8_t uvw_ch = 0U; uvw_ch < BSP_FEATURE_MTU3_UVW_MAX_CHANNELS; uvw_ch++)
        {
            p_info->clock_frequency[uvw_ch] =
                mtu3_clock_frequency_get(p_instance_ctrl, (uvw_ch * MTU5_V_OFFSET_ADDRESS));
        }
    }
#endif

    /* Get and store clock counting direction. Read count direction setting */
    p_info->count_direction = TIMER_DIRECTION_UP;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get current timer status and store it in provided pointer p_status.
 *
 * Example:
 * @snippet r_mtu3_example.c R_MTU3_StatusGet
 *
 * @retval FSP_SUCCESS                 Current timer state and counter value set successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_StatusGet (timer_ctrl_t * const p_ctrl, mtu3_status_t * const p_status)
{
    mtu3_instance_ctrl_t * p_instance_ctrl = (mtu3_instance_ctrl_t *) p_ctrl;
#if MTU3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(MTU3_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Get counter state. */
    if (0U == mtu3_get_tstr(p_instance_ctrl))
    {
        p_status->state = TIMER_STATE_STOPPED;
    }
    else
    {
        p_status->state = TIMER_STATE_COUNTING;
    }

    /* Get counter value */
    if (MTU3_CHANNEL_8 == p_instance_ctrl->p_cfg->channel)
    {
        /* MTU8.TCNT should be accessed in 32-bit units */
        p_status->counter =
            *(uint32_t *) ((uint8_t *) p_instance_ctrl->p_reg + tcnt_ofs_addr[p_instance_ctrl->p_cfg->channel]);
    }

#if MTU3_PRV_UVW_FEATURES_ENABLED == MTU3_CFG_UVW_SUPPORT_ENABLE
    else if (MTU3_CHANNEL_5 == p_instance_ctrl->p_cfg->channel)
    {
        p_status->tgru_counter =
            *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tcnt_ofs_addr[p_instance_ctrl->p_cfg->channel]);
        p_status->tgrv_counter =
            *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tcnt_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                           MTU5_V_OFFSET_ADDRESS);
        p_status->tgrv_counter =
            *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tcnt_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                           MTU5_W_OFFSET_ADDRESS);
    }
#endif
    else
    {
        p_status->counter =
            *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tcnt_ofs_addr[p_instance_ctrl->p_cfg->channel]);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set counter value.
 *
 * @note Do not call this API while the counter is counting.  The counter value can only be updated while the counter
 * is stopped.
 *
 * @retval FSP_SUCCESS                 Counter value updated.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 * @retval FSP_ERR_IN_USE              The timer is running.  Stop the timer before calling this function.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_CounterSet (timer_ctrl_t * const p_ctrl, uint32_t counter)
{
    mtu3_instance_ctrl_t * p_instance_ctrl = (mtu3_instance_ctrl_t *) p_ctrl;
#if MTU3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(MTU3_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(0U == mtu3_get_tstr(p_instance_ctrl), FSP_ERR_IN_USE);
#endif

    /* Set counter value */
    mtu3_set_count(p_instance_ctrl, counter);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enable output for MTIOCA and/or MTIOCB.
 *
 * @retval FSP_SUCCESS                 Output is enabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_OutputEnable (timer_ctrl_t * const p_ctrl, mtu3_output_pin_t pin_level)
{
    mtu3_instance_ctrl_t * p_instance_ctrl = (mtu3_instance_ctrl_t *) p_ctrl;
#if MTU3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(MTU3_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    *((uint8_t *) p_instance_ctrl->p_reg + tior_ofs_addr[p_instance_ctrl->p_cfg->channel]) =
        (uint8_t) ((pin_level.output_pin_level_b << R_MTU0_TIORH_IOB_Pos) | pin_level.output_pin_level_a);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disable output for MTIOCA and/or MTIOCB.
 *
 * @retval FSP_SUCCESS                 Output is disabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_OutputDisable (timer_ctrl_t * const p_ctrl, mtu3_io_pin_t pin)
{
    mtu3_instance_ctrl_t * p_instance_ctrl = (mtu3_instance_ctrl_t *) p_ctrl;
#if MTU3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(MTU3_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    uint8_t tior = *((uint8_t *) p_instance_ctrl->p_reg + tior_ofs_addr[p_instance_ctrl->p_cfg->channel]);
    if (MTU3_IO_PIN_MTIOCB != pin)
    {
        /* MTIOCA or both MTIOCA and MTIOCB. */
        tior &= (uint8_t) ~R_MTU0_TIORH_IOA_Msk;
    }

    if (MTU3_IO_PIN_MTIOCA != pin)
    {
        /* MTIOCB or both MTIOCA and MTIOCB. */
        tior &= (uint8_t) ~R_MTU0_TIORH_IOB_Msk;
    }

    *((uint8_t *) p_instance_ctrl->p_reg + tior_ofs_addr[p_instance_ctrl->p_cfg->channel]) = tior;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set A/D converter start request compare match value.
 *
 * @note MTU ch4, ch7 only
 *
 * @retval FSP_SUCCESS                 Counter value updated.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_AdcTriggerSet (timer_ctrl_t * const     p_ctrl,
                                mtu3_adc_compare_match_t which_compare_match,
                                uint16_t                 compare_match_value)
{
    mtu3_instance_ctrl_t * p_instance_ctrl = (mtu3_instance_ctrl_t *) p_ctrl;
#if MTU3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(MTU3_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set A/D converter start request compare match value. */
    if (MTU3_ADC_COMPARE_MATCH_ADC_A == which_compare_match)
    {
        if (MTU3_CHANNEL_4 == p_instance_ctrl->p_cfg->channel)
        {
            R_MTU4->TADCORA = compare_match_value;
        }
        else
        {
            R_MTU7->TADCORA = compare_match_value;
        }
    }

    if (MTU3_ADC_COMPARE_MATCH_ADC_B == which_compare_match)
    {
        if (MTU3_CHANNEL_4 == p_instance_ctrl->p_cfg->channel)
        {
            R_MTU4->TADCORB = compare_match_value;
        }
        else
        {
            R_MTU7->TADCORB = compare_match_value;
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_CallbackSet (timer_ctrl_t * const          p_api_ctrl,
                              void (                      * p_callback)(timer_callback_args_t *),
                              void const * const            p_context,
                              timer_callback_args_t * const p_callback_memory)
{
    mtu3_instance_ctrl_t * p_ctrl = (mtu3_instance_ctrl_t *) p_api_ctrl;

#if MTU3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(MTU3_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */
    p_ctrl->p_callback        = p_callback;
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops counter, disables output pins, and clears internal driver data.
 *
 * @retval FSP_SUCCESS                 Successful close.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_Close (timer_ctrl_t * const p_ctrl)
{
    mtu3_instance_ctrl_t * p_instance_ctrl = (mtu3_instance_ctrl_t *) p_ctrl;
    fsp_err_t              err             = FSP_SUCCESS;

#if MTU3_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(MTU3_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Stop counter. */
    mtu3_stop_timer(p_instance_ctrl);

    /* Clear open flag. */
    p_instance_ctrl->open = 0U;

    /* Disable output. */
    *((uint8_t *) p_instance_ctrl->p_reg + tior_ofs_addr[p_instance_ctrl->p_cfg->channel]) = 0U;

    /* Disable interrupts. */
    mtu3_disable_interrupt(p_instance_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 * DEPRECATED Sets driver version based on compile time macros.
 *
 * @retval FSP_SUCCESS                 Version stored in p_version.
 * @retval FSP_ERR_ASSERTION           p_version was NULL.
 **********************************************************************************************************************/
fsp_err_t R_MTU3_VersionGet (fsp_version_t * const p_version)
{
#if MTU3_CFG_PARAM_CHECKING_ENABLE

    /* Verify parameters are valid */
    FSP_ASSERT(NULL != p_version);
#endif

    p_version->version_id = g_mtu3_version.version_id;

    return FSP_SUCCESS;
}

/** @} (end addtogroup MTU3) */

/*******************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes control structure based on configuration.
 *
 * @param[in]  p_instance_ctrl         Instance control block.
 * @param[in]  p_cfg                   Pointer to timer configuration.
 **********************************************************************************************************************/
static void mtu3_common_open (mtu3_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg)
{
    /* Initialize control structure.  */
    p_instance_ctrl->p_cfg = p_cfg;

    /* If callback is not nullt, make sure the IRQ is enabled and store callback in the control block. */

    /* Save register base address. */
    uint32_t base_address;
    base_address = (uint32_t) (p_mtu3_base_address[p_cfg->channel]);

    p_instance_ctrl->p_reg_com = R_MTU;
    p_instance_ctrl->p_reg_nf  = (void *) R_MTU_NF;
    p_instance_ctrl->p_reg     = (void *) base_address;

    /* Set callback and context pointers, if configured */
    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;
}

/*******************************************************************************************************************//**
 * Performs hardware initialization of the MTU3.
 *
 * @param[in]  p_instance_ctrl        Instance control block.
 * @param[in]  p_cfg                  Pointer to timer configuration.
 **********************************************************************************************************************/
static void mtu3_hardware_initialize (mtu3_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg)
{
    /* Save pointer to extended configuration structure. */
    mtu3_extended_cfg_t * p_extend = (mtu3_extended_cfg_t *) p_cfg->p_extend;
#if MTU3_PRV_UVW_FEATURES_ENABLED == MTU3_CFG_UVW_SUPPORT_ENABLE
    mtu3_extended_uvw_cfg_t const * p_uvw_cfg = p_extend->p_uvw_cfg;
#endif

    /* Counter related initialization */
    mtu3_counter_initialize(p_instance_ctrl, p_cfg);

    /* In MTU3 and MTU4, set TOERA prior to setting TIOR. */
    p_instance_ctrl->p_reg_com->TOERA = MTU3_TOERA_MSK;
    p_instance_ctrl->p_reg_com->TOERB = MTU3_TOERB_MSK;

#if MTU3_PRV_EXTRA_FEATURES_ENABLED == MTU3_CFG_OUTPUT_SUPPORT_ENABLE
    mtu3_extended_pwm_cfg_t const * p_pwm_cfg = p_extend->p_pwm_cfg;
    if (NULL != p_pwm_cfg)
    {
        /* Interrupt Skipping Function Select */
        p_instance_ctrl->p_reg_com->TITMRA = p_pwm_cfg->interrupt_skip_mode_a;
        p_instance_ctrl->p_reg_com->TITMRB = p_pwm_cfg->interrupt_skip_mode_b;

        switch (p_instance_ctrl->p_cfg->channel)
        {
            case MTU3_CHANNEL_3:
            {
                /* When TITMRA = 0 */
                if (MTU3_INTERRUPT_SKIP_MODE_1 == p_pwm_cfg->interrupt_skip_mode_a)
                {
                    /* T3ACNT clear */
                    p_instance_ctrl->p_reg_com->TITCR1A &=
                        (uint8_t) ~((uint8_t) R_MTU_TITCR1A_T3AEN_Msk | R_MTU_TITCR1A_T3ACOR_Msk);
                    p_instance_ctrl->p_reg_com->TITCR1A = (uint8_t) ((uint8_t) R_MTU_TITCR1A_T3AEN_Msk | \
                                                                     (uint8_t) p_pwm_cfg->interrupt_skip_count_tgia3 <<
                                                                     R_MTU_TITCR1A_T3ACOR_Pos);
                }

                break;
            }

            case MTU3_CHANNEL_4:
            {
                /* When TITMRA = 0 */
                if (MTU3_INTERRUPT_SKIP_MODE_1 == p_pwm_cfg->interrupt_skip_mode_a)
                {
                    /* T4VCNT clear */
                    p_instance_ctrl->p_reg_com->TITCR1A &=
                        (uint8_t) ~((uint8_t) R_MTU_TITCR1A_T4VEN_Msk | R_MTU_TITCR1A_T4VCOR_Msk);
                    p_instance_ctrl->p_reg_com->TITCR1A = (uint8_t) ((uint8_t) R_MTU_TITCR1A_T4VEN_Msk | \
                                                                     (uint8_t) p_pwm_cfg->interrupt_skip_count_tciv4 <<
                                                                     R_MTU_TITCR1A_T4VCOR_Pos);
                }
                /* When TITMRA = 1 */
                else
                {
                    /* TRG4CNT clear */
                    p_instance_ctrl->p_reg_com->TITCR2A &= (uint8_t) ~((uint8_t) R_MTU_TITCR2A_TRG4COR_Msk);
                    p_instance_ctrl->p_reg_com->TITCR2A  = (uint8_t) (p_pwm_cfg->interrupt_skip_count_tgr4an_bn <<
                                                                     R_MTU_TITCR2A_TRG4COR_Pos);
                }

                R_MTU4->TADCORA = p_pwm_cfg->adc_a_compare_match;
                R_MTU4->TADCORB = p_pwm_cfg->adc_b_compare_match;
                break;
            }

            case MTU3_CHANNEL_6:
            {
                /* When TITMRB = 0 */
                if (MTU3_INTERRUPT_SKIP_MODE_1 == p_pwm_cfg->interrupt_skip_mode_b)
                {
                    /* T6ACNT clear */
                    p_instance_ctrl->p_reg_com->TITCR1B &=
                        (uint8_t) ~((uint8_t) R_MTU_TITCR1B_T6AEN_Msk | R_MTU_TITCR1B_T6ACOR_Msk);
                    p_instance_ctrl->p_reg_com->TITCR1B = (uint8_t) ((uint8_t) R_MTU_TITCR1B_T6AEN_Msk | \
                                                                     (uint8_t) p_pwm_cfg->interrupt_skip_count_tgia6 <<
                                                                     R_MTU_TITCR1B_T6ACOR_Pos);
                }

                break;
            }

            case MTU3_CHANNEL_7:
            {
                /* When TITMRB = 0 */
                if (MTU3_INTERRUPT_SKIP_MODE_1 == p_pwm_cfg->interrupt_skip_mode_b)
                {
                    /* T7VCNT clear */
                    p_instance_ctrl->p_reg_com->TITCR1B &=
                        (uint8_t) ~(R_MTU_TITCR1B_T7VEN_Msk | R_MTU_TITCR1B_T7VCOR_Msk);
                    p_instance_ctrl->p_reg_com->TITCR1B = (uint8_t) ((uint8_t) R_MTU_TITCR1B_T7VEN_Msk | \
                                                                     (uint8_t) p_pwm_cfg->interrupt_skip_count_tciv7 <<
                                                                     R_MTU_TITCR1B_T7VCOR_Pos);
                }
                /* When TITMRB = 1 */
                else
                {
                    /* TRG7CNT clear */
                    p_instance_ctrl->p_reg_com->TITCR2B &= (uint8_t) ~(R_MTU_TITCR2B_TRG7COR_Msk);
                    p_instance_ctrl->p_reg_com->TITCR2B  = (uint8_t) (p_pwm_cfg->interrupt_skip_count_tgr7an_bn <<
                                                                     R_MTU_TITCR2B_TRG7COR_Pos);
                }

                R_MTU7->TADCORA = p_pwm_cfg->adc_a_compare_match;
                R_MTU7->TADCORB = p_pwm_cfg->adc_b_compare_match;
                break;
            }

            default:
            {
                break;
            }
        }
    }
#endif

    /* Configure the noise filter for the MTIOC pins. */
    uint8_t nfcr = 0U;
    if (MTU3_CHANNEL_5 != p_instance_ctrl->p_cfg->channel)
    {
        nfcr =
            (uint8_t) (p_extend->noise_filter_mtioc_setting & (R_MTU_NF_NFCR0_NFAEN_Msk | R_MTU_NF_NFCR0_NFBEN_Msk));
        nfcr |= (uint8_t) (p_extend->noise_filter_mtioc_clk << R_MTU_NF_NFCR0_NFCS_Pos);
    }

#if MTU3_PRV_UVW_FEATURES_ENABLED == MTU3_CFG_UVW_SUPPORT_ENABLE
    else
    {
        nfcr =
            (uint8_t) (p_uvw_cfg->noise_filter_mtioc_setting_uvw &
                       (R_MTU_NF_NFCR5_NFUEN_Msk | R_MTU_NF_NFCR5_NFVEN_Msk | R_MTU_NF_NFCR5_NFWEN_Msk));
        nfcr |= (uint8_t) (p_uvw_cfg->noise_filter_mtioc_clk_uvw << R_MTU_NF_NFCR5_NFCS_Pos);
    }
#endif
    *((uint8_t *) p_instance_ctrl->p_reg_nf + nfcr_ofs_addr[p_instance_ctrl->p_cfg->channel]) = nfcr;

    /* Configure the noise filter for the MTCLKx pins. */
    uint8_t nfcrc = 0U;
    nfcrc =
        (uint8_t) (p_extend->noise_filter_mtclk_setting &
                   (R_MTU_NF_NFCRC_NFAEN_Msk | R_MTU_NF_NFCRC_NFBEN_Msk | R_MTU_NF_NFCRC_NFCEN_Msk |
                    R_MTU_NF_NFCRC_NFDEN_Msk));
    nfcrc |= (uint8_t) (p_extend->noise_filter_mtclk_clk << R_MTU_NF_NFCRC_NFCS_Pos);
    *((uint8_t *) p_instance_ctrl->p_reg_nf + MTU_NOISEFILTER_C_OFFSET_ADDRESS) = nfcrc;

    uint8_t tmdr1 = 0U;

    /* Enable the compare match buffer. */
    if (!((MTU3_CHANNEL_1 == p_instance_ctrl->p_cfg->channel) || (MTU3_CHANNEL_2 == p_instance_ctrl->p_cfg->channel) ||
          (MTU3_CHANNEL_5 == p_instance_ctrl->p_cfg->channel)))
    {
        tmdr1 = (R_MTU0_TMDR1_BFA_Msk | R_MTU0_TMDR1_BFB_Msk);
    }

    tmdr1 |= (uint8_t) (p_cfg->mode);
    *((uint8_t *) p_instance_ctrl->p_reg + tmdr1_ofs_addr[p_instance_ctrl->p_cfg->channel]) = tmdr1;

    /* A/D converter start requests enable. */
    if (((MTU3_CHANNEL_4 == p_instance_ctrl->p_cfg->channel) || (MTU3_CHANNEL_7 == p_instance_ctrl->p_cfg->channel)))
    {
        *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg +
                       tadcr_ofs_addr[p_instance_ctrl->p_cfg->channel]) =
            (R_MTU4_TADCR_UT4AE_Msk | R_MTU4_TADCR_DT4AE_Msk | \
             R_MTU4_TADCR_UT4BE_Msk |
             R_MTU4_TADCR_DT4BE_Msk);
    }

    /* Set the I/O control register. */
    if (MTU3_CHANNEL_5 != p_instance_ctrl->p_cfg->channel)
    {
        uint8_t tior_ioa = p_extend->mtioc_ctrl_setting.output_pin_level_a;
        uint8_t tior_iob = p_extend->mtioc_ctrl_setting.output_pin_level_b;
        *((uint8_t *) p_instance_ctrl->p_reg +
          tior_ofs_addr[p_instance_ctrl->p_cfg->channel]) =
            ((uint8_t) (tior_iob << R_MTU0_TIORH_IOB_Pos) | tior_ioa);
    }

#if MTU3_PRV_UVW_FEATURES_ENABLED == MTU3_CFG_UVW_SUPPORT_ENABLE
    else
    {
        *((uint8_t *) p_instance_ctrl->p_reg +
          tior_ofs_addr[p_instance_ctrl->p_cfg->channel]) = p_uvw_cfg->output_pin_level_u;
        *((uint8_t *) p_instance_ctrl->p_reg + tior_ofs_addr[p_instance_ctrl->p_cfg->channel] +
          MTU5_V_OFFSET_ADDRESS) = p_uvw_cfg->output_pin_level_v;
        *((uint8_t *) p_instance_ctrl->p_reg + tior_ofs_addr[p_instance_ctrl->p_cfg->channel] +
          MTU5_W_OFFSET_ADDRESS) = p_uvw_cfg->output_pin_level_w;
    }
#endif
    mtu3_enable_interrupt(p_instance_ctrl);
}

/*******************************************************************************************************************//**
 * Counter initialization of the MTU3.
 *
 * @param[in]  p_instance_ctrl        Instance control block.
 * @param[in]  p_cfg                  Pointer to timer configuration.
 **********************************************************************************************************************/
static void mtu3_counter_initialize (mtu3_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg)
{
    /* Save pointer to extended configuration structure. */
    mtu3_extended_cfg_t * p_extend = (mtu3_extended_cfg_t *) p_cfg->p_extend;
#if MTU3_PRV_UVW_FEATURES_ENABLED == MTU3_CFG_UVW_SUPPORT_ENABLE
    mtu3_extended_uvw_cfg_t const * p_uvw_cfg = p_extend->p_uvw_cfg;
#endif

    /* Power on MTU3 before setting any hardware registers. Make sure the counter is stopped before setting mode
     * register, PCLK divisor register, and counter register. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_START(FSP_IP_MTU3, p_cfg->channel);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    /* Initialize all registers that may affect operation of this driver to reset values.  Skip these since they
     * affect all channels, and are initialized in TSTR and TCNT is set immediately after
     * clearing the module stop bit to ensure the timer is stopped before proceeding with configuration. */
    mtu3_stop_timer(p_instance_ctrl);
    mtu3_set_count(p_instance_ctrl, 0U);

    /* Set the division ratio */
    if (MTU3_CHANNEL_5 != p_instance_ctrl->p_cfg->channel)
    {
        uint8_t tcr = (uint8_t) ((uint8_t) (p_extend->mtu3_clear << R_MTU0_TCR_CCLR_Pos) |
                                 (uint8_t) (p_extend->clk_edge << R_MTU0_TCR_CKEG_Pos) |
                                 (uint8_t) (p_extend->mtu3_clk_div & R_MTU0_TCR_TPSC_Msk));
        uint8_t tcr2 = ((p_extend->mtu3_clk_div >> MTU3_TCR_TPSC_POS) & R_MTU0_TCR2_TPSC2_Msk);
        *((uint8_t *) p_instance_ctrl->p_reg + tcr_ofs_addr[p_instance_ctrl->p_cfg->channel])  = tcr;
        *((uint8_t *) p_instance_ctrl->p_reg + tcr2_ofs_addr[p_instance_ctrl->p_cfg->channel]) = tcr2;
    }

#if MTU3_PRV_UVW_FEATURES_ENABLED == MTU3_CFG_UVW_SUPPORT_ENABLE
    else
    {
        *((uint8_t *) p_instance_ctrl->p_reg + tcr_ofs_addr[p_instance_ctrl->p_cfg->channel]) =
            (p_uvw_cfg->mtu3_clk_div_u & R_MTU5_TCRU_TPSC_Msk);
        *((uint8_t *) p_instance_ctrl->p_reg + tcr2_ofs_addr[p_instance_ctrl->p_cfg->channel]) =
            ((p_uvw_cfg->mtu3_clk_div_u >> MTU3_TCR_TPSC_POS_CH5) & (R_MTU5_TCR2U_TPSC2_Msk | R_MTU5_TCR2U_CKEG_Msk));
        *((uint8_t *) p_instance_ctrl->p_reg + tcr_ofs_addr[p_instance_ctrl->p_cfg->channel] + MTU5_V_OFFSET_ADDRESS) =
            (p_uvw_cfg->mtu3_clk_div_v & R_MTU5_TCRU_TPSC_Msk);
        *((uint8_t *) p_instance_ctrl->p_reg + tcr2_ofs_addr[p_instance_ctrl->p_cfg->channel] + MTU5_V_OFFSET_ADDRESS) =
            ((p_uvw_cfg->mtu3_clk_div_v >> MTU3_TCR_TPSC_POS_CH5) & (R_MTU5_TCR2U_TPSC2_Msk | R_MTU5_TCR2U_CKEG_Msk));
        *((uint8_t *) p_instance_ctrl->p_reg + tcr_ofs_addr[p_instance_ctrl->p_cfg->channel] + MTU5_W_OFFSET_ADDRESS) =
            (p_uvw_cfg->mtu3_clk_div_w & R_MTU5_TCRU_TPSC_Msk);
        *((uint8_t *) p_instance_ctrl->p_reg + tcr2_ofs_addr[p_instance_ctrl->p_cfg->channel] + MTU5_W_OFFSET_ADDRESS) =
            ((p_uvw_cfg->mtu3_clk_div_w >> MTU3_TCR_TPSC_POS_CH5) & (R_MTU5_TCR2U_TPSC2_Msk | R_MTU5_TCR2U_CKEG_Msk));
    }
#endif

    /* Store period register setting. The actual period and is one cycle longer than the register value. */
    if (MTU3_CHANNEL_8 == p_instance_ctrl->p_cfg->channel)
    {
        /* MTU ch8 should be written in 32-bit length */
        *(uint32_t *) ((uint8_t *) p_instance_ctrl->p_reg +
                       tgra_ofs_addr[p_instance_ctrl->p_cfg->channel]) = (p_extend->tgra_val - 1U);
        *(uint32_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgra_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                       MTU3_TGRB_D_OFFSET_LONG) = (p_extend->tgrb_val - 1U);
        *(uint32_t *) ((uint8_t *) p_instance_ctrl->p_reg +
                       tgrc_ofs_addr[p_instance_ctrl->p_cfg->channel]) = (p_extend->tgrc_val - 1U);
        *(uint32_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgrc_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                       MTU3_TGRB_D_OFFSET_LONG) = (p_extend->tgrd_val - 1U);
    }

#if MTU3_PRV_UVW_FEATURES_ENABLED == MTU3_CFG_UVW_SUPPORT_ENABLE
    else if (MTU3_CHANNEL_5 == p_instance_ctrl->p_cfg->channel)
    {
        *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg +
                       tgra_ofs_addr[p_instance_ctrl->p_cfg->channel]) = (uint16_t) (p_uvw_cfg->tgru_val - 1U);
        *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgra_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                       MTU5_V_OFFSET_ADDRESS) = (uint16_t) (p_uvw_cfg->tgrv_val - 1U);
        *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgra_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                       MTU5_W_OFFSET_ADDRESS) = (uint16_t) (p_uvw_cfg->tgrw_val - 1U);
    }
#endif
    else
    {
        *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg +
                       tgra_ofs_addr[p_instance_ctrl->p_cfg->channel]) = (uint16_t) (p_extend->tgra_val - 1U);
        *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgra_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                       MTU3_TGRB_D_OFFSET_WORD) = (uint16_t) (p_extend->tgrb_val - 1U);

        /* TGRC and TGRD do not exist in MTU1 and MTU2 */
        if (!((MTU3_CHANNEL_1 == p_instance_ctrl->p_cfg->channel) ||
              (MTU3_CHANNEL_2 == p_instance_ctrl->p_cfg->channel)))
        {
            *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgrc_ofs_addr[p_instance_ctrl->p_cfg->channel]) =
                (uint16_t) (p_extend->tgrc_val - 1U);
            *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgrc_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                           MTU3_TGRB_D_OFFSET_WORD) = (uint16_t) (p_extend->tgrd_val - 1U);
        }
    }
}

/*******************************************************************************************************************//**
 * The counter value can only be updated while the counter
 *
 * @param[in]  p_instance_ctrl         Instance control structure
 * @param[in]  counter                 Timer counter
 **********************************************************************************************************************/
static void mtu3_set_count (mtu3_instance_ctrl_t * const p_instance_ctrl, uint32_t counter)
{
    /* Set timer counter. */
    if (MTU3_CHANNEL_8 == p_instance_ctrl->p_cfg->channel)
    {
        /* MTU8.TCNT should be accessed in 32-bit units */
        *(uint32_t *) ((uint8_t *) p_instance_ctrl->p_reg + tcnt_ofs_addr[p_instance_ctrl->p_cfg->channel]) = counter;
    }

#if MTU3_PRV_UVW_FEATURES_ENABLED == MTU3_CFG_UVW_SUPPORT_ENABLE
    else if (MTU3_CHANNEL_5 == p_instance_ctrl->p_cfg->channel)
    {
        /* Since it is a register dedicated to MTU5, set it directly. */
        *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg +
                       tcnt_ofs_addr[p_instance_ctrl->p_cfg->channel]) = (uint16_t) counter;
        *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tcnt_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                       MTU5_V_OFFSET_ADDRESS) = (uint16_t) counter;
        *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tcnt_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                       MTU5_W_OFFSET_ADDRESS) = (uint16_t) counter;
    }
#endif
    else
    {
        *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg +
                       tcnt_ofs_addr[p_instance_ctrl->p_cfg->channel]) = (uint16_t) counter;
    }
}

/*******************************************************************************************************************//**
 * Check the operating status
 *
 * @param[in]  p_instance_ctrl         Instance control structure
 **********************************************************************************************************************/
static uint8_t mtu3_get_tstr (mtu3_instance_ctrl_t * const p_instance_ctrl)
{
    uint8_t ret_val;

    /* Check the operating status */
    if ((MTU3_CHANNEL_6 == p_instance_ctrl->p_cfg->channel) || (MTU3_CHANNEL_7 == p_instance_ctrl->p_cfg->channel))
    {
        ret_val = (p_instance_ctrl->p_reg_com->TSTRB & mtu3_tstr_val[p_instance_ctrl->p_cfg->channel]);
    }

#if MTU3_PRV_UVW_FEATURES_ENABLED == MTU3_CFG_UVW_SUPPORT_ENABLE
    else if (MTU3_CHANNEL_5 == p_instance_ctrl->p_cfg->channel)
    {
        /* Since it is a register dedicated to MTU5, get it directly. */
        ret_val = R_MTU5->TSTR;
    }
#endif
    else
    {
        ret_val = (p_instance_ctrl->p_reg_com->TSTRA & mtu3_tstr_val[p_instance_ctrl->p_cfg->channel]);
    }

    return ret_val;
}

/*******************************************************************************************************************//**
 * Stops timer
 *
 * @param[in]  p_instance_ctrl         Instance control structure
 **********************************************************************************************************************/
static void mtu3_stop_timer (mtu3_instance_ctrl_t * const p_instance_ctrl)
{
    /* Stop timer */
    if ((MTU3_CHANNEL_6 == p_instance_ctrl->p_cfg->channel) || (MTU3_CHANNEL_7 == p_instance_ctrl->p_cfg->channel))
    {
        p_instance_ctrl->p_reg_com->TSTRB &= (uint8_t) ~mtu3_tstr_val[p_instance_ctrl->p_cfg->channel];
    }

#if MTU3_PRV_UVW_FEATURES_ENABLED == MTU3_CFG_UVW_SUPPORT_ENABLE
    else if (MTU3_CHANNEL_5 == p_instance_ctrl->p_cfg->channel)
    {
        /* Since it is a register dedicated to MTU5, set it directly. */
        R_MTU5->TSTR &= (uint8_t) ~(R_MTU5_TSTR_CSTW5_Msk | R_MTU5_TSTR_CSTV5_Msk | R_MTU5_TSTR_CSTU5_Msk);
    }
#endif
    else
    {
        p_instance_ctrl->p_reg_com->TSTRA &= (uint8_t) ~mtu3_tstr_val[p_instance_ctrl->p_cfg->channel];
    }
}

/*******************************************************************************************************************//**
 * Disables interrupt if it is a valid vector number.
 *
 * @param[in]  irq                     Interrupt number
 **********************************************************************************************************************/
static void r_mtu3_disable_irq (IRQn_Type irq)
{
    /* Disable interrupts. */
    if (irq >= 0)
    {
        R_BSP_IrqDisable(irq);
        R_FSP_IsrContextSet(irq, NULL);
    }
}

/*******************************************************************************************************************//**
 * Configures and enables interrupt if it is a valid vector number.
 *
 * @param[in]  irq                     Interrupt number
 * @param[in]  priority                NVIC priority of the interrupt
 * @param[in]  p_context               The interrupt context is a pointer to data required in the ISR.
 **********************************************************************************************************************/
static void r_mtu3_enable_irq (IRQn_Type const irq, uint32_t priority, void * p_context)
{
    if (irq >= 0)
    {
        R_BSP_IrqCfgEnable(irq, priority, p_context);
    }
}

/*******************************************************************************************************************//**
 * Disable interrupts
 *
 * @param[in]  p_instance_ctrl           Instance control block
 **********************************************************************************************************************/
static void mtu3_disable_interrupt (mtu3_instance_ctrl_t * const p_instance_ctrl)
{
    /* Save pointer to extended configuration structure. */
    mtu3_extended_cfg_t * p_extend = (mtu3_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

#if MTU3_PRV_UVW_FEATURES_ENABLED == MTU3_CFG_UVW_SUPPORT_ENABLE
    if (MTU3_CHANNEL_5 == p_instance_ctrl->p_cfg->channel)
    {
        mtu3_extended_uvw_cfg_t const * p_uvw_cfg = p_extend->p_uvw_cfg;
        *((uint8_t *) p_instance_ctrl->p_reg +
          tier_ofs_addr[p_instance_ctrl->p_cfg->channel]) &= (uint8_t) ~R_MTU5_TIER_TGIE5U_Msk;
        *((uint8_t *) p_instance_ctrl->p_reg +
          tier_ofs_addr[p_instance_ctrl->p_cfg->channel]) &= (uint8_t) ~R_MTU5_TIER_TGIE5V_Msk;
        *((uint8_t *) p_instance_ctrl->p_reg +
          tier_ofs_addr[p_instance_ctrl->p_cfg->channel]) &= (uint8_t) ~R_MTU5_TIER_TGIE5W_Msk;

        r_mtu3_disable_irq(p_uvw_cfg->capture_u_irq);
        r_mtu3_disable_irq(p_uvw_cfg->capture_v_irq);
        r_mtu3_disable_irq(p_uvw_cfg->capture_w_irq);
    }
    else
#endif
    {
        *((uint8_t *) p_instance_ctrl->p_reg +
          tier_ofs_addr[p_instance_ctrl->p_cfg->channel]) &= (uint8_t) ~R_MTU0_TIER_TCIEV_Msk;
        *((uint8_t *) p_instance_ctrl->p_reg +
          tier_ofs_addr[p_instance_ctrl->p_cfg->channel]) &= (uint8_t) ~R_MTU0_TIER_TGIEA_Msk;
        *((uint8_t *) p_instance_ctrl->p_reg +
          tier_ofs_addr[p_instance_ctrl->p_cfg->channel]) &= (uint8_t) ~R_MTU0_TIER_TGIEB_Msk;

        r_mtu3_disable_irq(p_instance_ctrl->p_cfg->cycle_end_irq);
        r_mtu3_disable_irq(p_extend->capture_a_irq);
        r_mtu3_disable_irq(p_extend->capture_b_irq);
    }
}

/*******************************************************************************************************************//**
 * Enable interrupts
 *
 * @param[in]  p_instance_ctrl           Instance control block
 **********************************************************************************************************************/
static void mtu3_enable_interrupt (mtu3_instance_ctrl_t * const p_instance_ctrl)
{
    /* Save pointer to extended configuration structure. */
    mtu3_extended_cfg_t * p_extend = (mtu3_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Initialize TIER */
    *((uint8_t *) p_instance_ctrl->p_reg + tier_ofs_addr[p_instance_ctrl->p_cfg->channel]) = 0x00U;

#if MTU3_PRV_UVW_FEATURES_ENABLED == MTU3_CFG_UVW_SUPPORT_ENABLE
    if (MTU3_CHANNEL_5 == p_instance_ctrl->p_cfg->channel)
    {
        mtu3_extended_uvw_cfg_t const * p_uvw_cfg = p_extend->p_uvw_cfg;
        *((uint8_t *) p_instance_ctrl->p_reg +
          tier_ofs_addr[p_instance_ctrl->p_cfg->channel]) |= R_MTU5_TIER_TGIE5U_Msk;
        *((uint8_t *) p_instance_ctrl->p_reg +
          tier_ofs_addr[p_instance_ctrl->p_cfg->channel]) |= R_MTU5_TIER_TGIE5V_Msk;
        *((uint8_t *) p_instance_ctrl->p_reg +
          tier_ofs_addr[p_instance_ctrl->p_cfg->channel]) |= R_MTU5_TIER_TGIE5W_Msk;

        r_mtu3_enable_irq(p_uvw_cfg->capture_u_irq, p_uvw_cfg->capture_u_ipl, p_instance_ctrl);
        r_mtu3_enable_irq(p_uvw_cfg->capture_v_irq, p_uvw_cfg->capture_v_ipl, p_instance_ctrl);
        r_mtu3_enable_irq(p_uvw_cfg->capture_w_irq, p_uvw_cfg->capture_w_ipl, p_instance_ctrl);
    }
    else
#endif
    {
        /* Enable CPU interrupts if callback is not null. */
        *((uint8_t *) p_instance_ctrl->p_reg +
          tier_ofs_addr[p_instance_ctrl->p_cfg->channel]) |= R_MTU0_TIER_TCIEV_Msk;
        *((uint8_t *) p_instance_ctrl->p_reg +
          tier_ofs_addr[p_instance_ctrl->p_cfg->channel]) |= R_MTU0_TIER_TGIEA_Msk;
        *((uint8_t *) p_instance_ctrl->p_reg +
          tier_ofs_addr[p_instance_ctrl->p_cfg->channel]) |= R_MTU0_TIER_TGIEB_Msk;

        r_mtu3_enable_irq(p_instance_ctrl->p_cfg->cycle_end_irq, p_instance_ctrl->p_cfg->cycle_end_ipl,
                          p_instance_ctrl);
        r_mtu3_enable_irq(p_extend->capture_a_irq, p_extend->capture_a_ipl, p_instance_ctrl);
        r_mtu3_enable_irq(p_extend->capture_b_irq, p_extend->capture_b_ipl, p_instance_ctrl);
    }
}

/*******************************************************************************************************************//**
 * Calculates clock frequency of MTU3 counter.  Divides MTU3 clock by MTU3 clock divisor.
 *
 * @param[in]  p_instance_ctrl           Instance control block
 * @param[in]  ch_addr_ofs               Offset address of register
 *
 * @return     Clock frequency of the MTU3 counter.
 **********************************************************************************************************************/
static uint32_t mtu3_clock_frequency_get (mtu3_instance_ctrl_t * const p_instance_ctrl, uint32_t ch_addr_ofs)
{
    uint32_t pclk_freq_hz;
    uint16_t pclk_divisor;
    uint8_t  tpsc;
    uint8_t  tcr_tpsc;
    uint8_t  tcr2_tpsc;

    /* Get frequency division from TCR and TCR2. */
    tcr_tpsc =
        *((uint8_t *) p_instance_ctrl->p_reg + tcr_ofs_addr[p_instance_ctrl->p_cfg->channel] + ch_addr_ofs);
    tcr2_tpsc =
        *((uint8_t *) p_instance_ctrl->p_reg + tcr2_ofs_addr[p_instance_ctrl->p_cfg->channel] + ch_addr_ofs);

    if (MTU3_CHANNEL_5 == p_instance_ctrl->p_cfg->channel)
    {
        tcr_tpsc  &= R_MTU5_TCRU_TPSC_Msk;
        tcr2_tpsc &= R_MTU5_TCR2U_TPSC2_Msk;
    }
    else
    {
        tcr_tpsc  &= R_MTU0_TCR_TPSC_Msk;
        tcr2_tpsc &= R_MTU0_TCR2_TPSC2_Msk;
    }

    /* If TCR2.TPSC2 is 1 or greater, get from the array that stores the TCR2.TPSC2 settings. */
    if (tcr2_tpsc >= 1U)
    {
        if (MTU3_CHANNEL_5 == p_instance_ctrl->p_cfg->channel)
        {
            /* Get from the 4th array(for ch5) */
            tpsc = (uint8_t) ((tcr2_tpsc + MTU3_TPSC_OFS_ARRAY_CH5) - 1U);
        }
        else
        {
            /* Get from the 8th array */
            tpsc = (uint8_t) ((tcr2_tpsc + MTU3_TPSC_OFS_ARRAY) - 1U);
        }
    }
    else
    {
        tpsc = tcr_tpsc;
    }

    pclk_divisor = mtu3_clk_div[p_instance_ctrl->p_cfg->channel][tpsc];

    pclk_freq_hz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKH);

    return pclk_freq_hz / pclk_divisor;
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to MTU3 instance control block
 * @param[in]     event      Event code
 * @param[in]     capture    Event capture counts (if applicable)
 **********************************************************************************************************************/
static void r_mtu3_call_callback (mtu3_instance_ctrl_t * p_ctrl, timer_event_t event, uint32_t capture)
{
    timer_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    timer_callback_args_t * p_args = p_ctrl->p_callback_memory;
    if (NULL == p_args)
    {
        /* Store on stack */
        p_args = &args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args;
    }

    p_args->event     = event;
    p_args->capture   = capture;
    p_args->p_context = p_ctrl->p_context;

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_ctrl->p_callback(p_args);

    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }
}

/*******************************************************************************************************************//**
 * Common processing for input capture interrupt.
 *
 * @param[in]  event  Which input capture event occurred
 **********************************************************************************************************************/
static void r_mtu3_capture_common_isr (mtu3_prv_capture_event_t event)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    mtu3_instance_ctrl_t * p_instance_ctrl = (mtu3_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    uint32_t               counter         = 0U;

    /* Get captured value. */
    if (event == MTU3_PRV_CAPTURE_EVENT_A)
    {
        if (MTU3_CHANNEL_8 == p_instance_ctrl->p_cfg->channel)
        {
            counter =
                *(uint32_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgra_ofs_addr[p_instance_ctrl->p_cfg->channel]);
        }
        else
        {
            counter =
                *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgra_ofs_addr[p_instance_ctrl->p_cfg->channel]);
        }

        /* TSR.TGFA Flag Clear(MTU ch1-ch4, ch6-ch7) */
        if (((p_instance_ctrl->p_cfg->channel >= MTU3_CHANNEL_1) &&
             (p_instance_ctrl->p_cfg->channel <= MTU3_CHANNEL_4)) ||
            ((p_instance_ctrl->p_cfg->channel >= MTU3_CHANNEL_6) &&
             (p_instance_ctrl->p_cfg->channel <= MTU3_CHANNEL_7)))
        {
            *((uint8_t *) p_instance_ctrl->p_reg +
              tsr_ofs_addr[p_instance_ctrl->p_cfg->channel]) &= (uint8_t) ~R_MTU1_TSR_TGFA_Msk;
        }
    }
    else if (event == MTU3_PRV_CAPTURE_EVENT_B)
    {
        if (MTU3_CHANNEL_8 == p_instance_ctrl->p_cfg->channel)
        {
            counter =
                *(uint32_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgra_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                               MTU3_TGRB_D_OFFSET_LONG);
        }
        else
        {
            counter =
                *(uint16_t *) ((uint8_t *) p_instance_ctrl->p_reg + tgra_ofs_addr[p_instance_ctrl->p_cfg->channel] +
                               MTU3_TGRB_D_OFFSET_WORD);
        }

        /* TSR.TGFB Flag Clear(MTU ch1-ch4, ch6-ch7) */
        if (((p_instance_ctrl->p_cfg->channel >= MTU3_CHANNEL_1) &&
             (p_instance_ctrl->p_cfg->channel <= MTU3_CHANNEL_4)) ||
            ((p_instance_ctrl->p_cfg->channel >= MTU3_CHANNEL_6) &&
             (p_instance_ctrl->p_cfg->channel <= MTU3_CHANNEL_7)))
        {
            *((uint8_t *) p_instance_ctrl->p_reg +
              tsr_ofs_addr[p_instance_ctrl->p_cfg->channel]) &= (uint8_t) ~R_MTU1_TSR_TGFB_Msk;
        }
    }
    else
    {
#if MTU3_PRV_UVW_FEATURES_ENABLED == MTU3_CFG_UVW_SUPPORT_ENABLE
        if (event == MTU3_PRV_CAPTURE_EVENT_U)
        {
            counter = R_MTU5->TGRU;
        }
        else if (event == MTU3_PRV_CAPTURE_EVENT_V)
        {
            counter = R_MTU5->TGRV;
        }
        else
        {
            counter = R_MTU5->TGRW;
        }
#endif
    }

    /* If a callback is provided, then call it with the captured counter value. */
    if (NULL != p_instance_ctrl->p_callback)
    {
        r_mtu3_call_callback(p_instance_ctrl,
                             (timer_event_t) ((uint32_t) TIMER_EVENT_CAPTURE_A + (uint32_t) event),
                             counter);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void mtu3_counter_overflow_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    mtu3_instance_ctrl_t * p_instance_ctrl = (mtu3_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    if (NULL != p_instance_ctrl->p_callback)
    {
        r_mtu3_call_callback(p_instance_ctrl, TIMER_EVENT_CYCLE_END, 0);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * Interrupt triggered by a capture A source.
 *
 * Calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void mtu3_capture_a_isr (void)
{
    r_mtu3_capture_common_isr(MTU3_PRV_CAPTURE_EVENT_A);
}

/*******************************************************************************************************************//**
 * Interrupt triggered by a capture B source.
 *
 * Calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void mtu3_capture_b_isr (void)
{
    r_mtu3_capture_common_isr(MTU3_PRV_CAPTURE_EVENT_B);
}

/*******************************************************************************************************************//**
 * Interrupt triggered by a capture U source.(ch5)
 *
 * Calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void mtu3_capture_u_isr (void)
{
    r_mtu3_capture_common_isr(MTU3_PRV_CAPTURE_EVENT_U);
}

/*******************************************************************************************************************//**
 * Interrupt triggered by a capture V source.(ch5)
 *
 * Calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void mtu3_capture_v_isr (void)
{
    r_mtu3_capture_common_isr(MTU3_PRV_CAPTURE_EVENT_V);
}

/*******************************************************************************************************************//**
 * Interrupt triggered by a capture W source.(ch5)
 *
 * Calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void mtu3_capture_w_isr (void)
{
    r_mtu3_capture_common_isr(MTU3_PRV_CAPTURE_EVENT_W);
}
