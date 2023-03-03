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

#ifndef R_DSMIF_B_H
#define R_DSMIF_B_H

/*******************************************************************************************************************//**
 * @addtogroup DSMIF_B
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_dsmif_b_cfg.h"
#include "r_adc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define DSMIF_B_MAX_NUM_CHANNELS    (3U)

#define DSMIF_B_STOP_TIMEOUT        (0x000FFFFFU)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* 39.2.1.2 DSSECSR : Overcurrent Sum Error Detect Channel Setting Register */
typedef enum e_dsmif_b_sum_err_detect_channel
{
    DSMIF_B_SUM_ERR_DETECT_CHANNEL_0_2 = 0, ///< Detects error of sum value of overcurrent data of CH0, CH1, CH2
    DSMIF_B_SUM_ERR_DETECT_CHANNEL_0_1 = 1, ///< Detects error of sum value of overcurrent data of CH0, CH1
    DSMIF_B_SUM_ERR_DETECT_CHANNEL_0   = 2, ///< Detects error of overcurrent data of CH0
    DSMIF_B_SUM_ERR_DETECT_CHANNEL_1   = 3, ///< Detects error of overcurrent data of CH1
    DSMIF_B_SUM_ERR_DETECT_CHANNEL_2   = 4, ///< Detects error of overcurrent data of CH2
} dsmif_b_sum_err_detect_channel_t;

/* 39.2.2.2 DSCMCCRCHn : Current Measurement Clock Control Register Channel n (n = 0 to 2) */
typedef enum e_dsmif_b_clock_ctrl
{
    DSMIF_B_CLOCK_CTRL_SLAVE  = 0,     ///< MCLKn pin is input (slave operation)
    DSMIF_B_CLOCK_CTRL_MASTER = 1,     ///< MCLKn pin is output (master operation)
} dsmif_b_clock_ctrl_t;

typedef enum e_dsmif_b_clock_edge
{
    DSMIF_B_CLOCK_EDGE_NEGATIVE = 0,   ///< Capture MDATn at the negative edge of MCLKn
    DSMIF_B_CLOCK_EDGE_POSITIVE = 1,   ///< Capture MDATn at the positive edge of MCLKn
} dsmif_b_clock_edge_t;

typedef enum e_dsmif_b_master_clock
{
    DSMIF_B_MASTER_CLOCK_25MHZ_PCLKH200   = 3,   ///< Master clock 25MHz, PCLKH 200MHz
    DSMIF_B_MASTER_CLOCK_20MHZ_PCLKH200   = 4,   ///< Master clock 20MHz, PCLKH 200MHz
    DSMIF_B_MASTER_CLOCK_12_5MHZ_PCLKH200 = 7,   ///< Master clock 12.5MHz, PCLKH 200MHz
    DSMIF_B_MASTER_CLOCK_10MHZ_PCLKH200   = 9,   ///< Master clock 10MHz, PCLKH 200MHz
    DSMIF_B_MASTER_CLOCK_6_25MHZ_PCLKH200 = 15,  ///< Master clock 6.25MHz, PCLKH 200MHz
    DSMIF_B_MASTER_CLOCK_5MHZ_PCLKH200    = 19,  ///< Master clock 5MHz, PCLKH 200MHz

    DSMIF_B_MASTER_CLOCK_25MHZ_PCLKH150    = 2,  ///< Master clock 25MHz, PCLKH 150MHz
    DSMIF_B_MASTER_CLOCK_18_75MHZ_PCLKH150 = 3,  ///< Master clock 18.75MHz, PCLKH 150MHz
    DSMIF_B_MASTER_CLOCK_12_5MHZ_PCLKH150  = 5,  ///< Master clock 12.5MHz, PCLKH 150MHz
    DSMIF_B_MASTER_CLOCK_9_375MHZ_PCLKH150 = 7,  ///< Master clock 9.375MHz, PCLKH 150MHz
    DSMIF_B_MASTER_CLOCK_6_25MHZ_PCLKH150  = 11, ///< Master clock 6.25MHz, PCLKH 150MHz
    DSMIF_B_MASTER_CLOCK_5MHZ_PCLKH150     = 14, ///< Master clock 5MHz, PCLKH 150MHz
} dsmif_b_master_clock_t;

/* 39.2.2.3 DSCMFCRCHn : Current Measurement Filter Control Register Channel n (n = 0 to 2) */
/* 39.2.2.6 DSOCFCRCHn : Overcurrent Detect Filter Control Register Channel n (n = 0 to 2) */
typedef enum e_dsmif_b_filter_order
{
    DSMIF_B_FILTER_ORDER_3RD = 0,      ///< Overcurrent detection filter order setting 3rd order
    DSMIF_B_FILTER_ORDER_1ST = 1,      ///< Overcurrent detection filter order setting 1st order
    DSMIF_B_FILTER_ORDER_2ND = 2,      ///< Overcurrent detection filter order setting 2nd order
} dsmif_b_filter_order_t;

typedef enum e_dsmif_b_data_shift
{
    DSMIF_B_DATA_SHIFT_23_8 = 0,       ///< Data shift setting for overcurrent detection [23:8]
    DSMIF_B_DATA_SHIFT_22_7 = 1,       ///< Data shift setting for overcurrent detection [22:7]
    DSMIF_B_DATA_SHIFT_21_6 = 2,       ///< Data shift setting for overcurrent detection [21:6]
    DSMIF_B_DATA_SHIFT_20_5 = 3,       ///< Data shift setting for overcurrent detection [20:5]
    DSMIF_B_DATA_SHIFT_19_4 = 4,       ///< Data shift setting for overcurrent detection [19:4]
    DSMIF_B_DATA_SHIFT_18_3 = 5,       ///< Data shift setting for overcurrent detection [18:3]
    DSMIF_B_DATA_SHIFT_17_2 = 6,       ///< Data shift setting for overcurrent detection [17:2]
    DSMIF_B_DATA_SHIFT_16_1 = 7,       ///< Data shift setting for overcurrent detection [16:1]
    DSMIF_B_DATA_SHIFT_15_0 = 8,       ///< Data shift setting for overcurrent detection [15:0]
    DSMIF_B_DATA_SHIFT_14_0 = 9,       ///< Data shift setting for overcurrent detection [14:0]
    DSMIF_B_DATA_SHIFT_13_0 = 10,      ///< Data shift setting for overcurrent detection [13:0]
    DSMIF_B_DATA_SHIFT_12_0 = 11,      ///< Data shift setting for overcurrent detection [12:0]
    DSMIF_B_DATA_SHIFT_11_0 = 12,      ///< Data shift setting for overcurrent detection [11:0]
    DSMIF_B_DATA_SHIFT_10_0 = 13,      ///< Data shift setting for overcurrent detection [10:0]
    DSMIF_B_DATA_SHIFT_9_0  = 14,      ///< Data shift setting for overcurrent detection [9:0]
    DSMIF_B_DATA_SHIFT_8_0  = 15,      ///< Data shift setting for overcurrent detection [8:0]
    DSMIF_B_DATA_SHIFT_7_0  = 16,      ///< Data shift setting for overcurrent detection [7:0]
    DSMIF_B_DATA_SHIFT_6_0  = 17,      ///< Data shift setting for overcurrent detection [6:0]
    DSMIF_B_DATA_SHIFT_5_0  = 18,      ///< Data shift setting for overcurrent detection [5:0]
    DSMIF_B_DATA_SHIFT_4_0  = 19,      ///< Data shift setting for overcurrent detection [4:0]
} dsimf_b_data_shift_t;

/* 39.2.2.4 DSCMCTCRCHn : Current Measurement Capture Trigger Control Register Channel n (n = 0 to 2) */
typedef enum e_dsmif_b_capture_trigger
{
    DSMIF_B_CAPTURE_TRIGGER_NOT = 0,   ///< Do not capture
    DSMIF_B_CAPTURE_TRIGGER_0   = 1,   ///< Select current data capture trigger 0
    DSMIF_B_CAPTURE_TRIGGER_1   = 2,   ///< Select current data capture trigger 1
    DSMIF_B_CAPTURE_TRIGGER_2   = 3,   ///< Select current data capture trigger 2
    DSMIF_B_CAPTURE_TRIGGER_3   = 4,   ///< Select current data capture trigger 3
    DSMIF_B_CAPTURE_TRIGGER_4   = 5,   ///< Select current data capture trigger 4
    DSMIF_B_CAPTURE_TRIGGER_5   = 6,   ///< Select current data capture trigger 5
} dsmif_b_capture_trigger_t;

typedef enum e_dsmif_b_counter_init_trigger
{
    DSMIF_B_COUNTER_INIT_TRIGGER_NOT = 0, ///< Do not initialize
    DSMIF_B_COUNTER_INIT_TRIGGER_0   = 1, ///< Select decimation dividing counter initialization trigger 0
    DSMIF_B_COUNTER_INIT_TRIGGER_1   = 2, ///< Select decimation dividing counter initialization trigger 1
    DSMIF_B_COUNTER_INIT_TRIGGER_2   = 3, ///< Select decimation dividing counter initialization trigger 2
} dsmif_b_counter_init_trigger_t;

/** DSMIF data register */
typedef enum e_dsmif_b_current_data
{
    DSMIF_B_CURRENT_DATA           = 0, ///< DSCDRCHn   : Current Data Register
    DSMIF_B_CURRENT_DATA_CAPTURE_A = 1, ///< DSCCDRACHn : Capture Current Data Register A
    DSMIF_B_CURRENT_DATA_CAPTURE_B = 2, ///< DSCCDRBCHn : Capture Current Data Register B
} dsmif_b_current_data_t;

/** For DSMIF Scan configuration e_dsmif_ch_mask::channel_mask.
 *  Use bitwise OR to combine these masks for desired channels and sensors.    */
typedef enum e_dsmif_b_channel_mask
{
    DSMIF_B_CHANNEL_MASK_OFF = (0U),       ///< No channels selected
    DSMIF_B_CHANNEL_MASK_0   = (1U << 0U), ///< Channel 0 mask
    DSMIF_B_CHANNEL_MASK_1   = (1U << 1U), ///< Channel 1 mask
    DSMIF_B_CHANNEL_MASK_2   = (1U << 2U), ///< Channel 2 mask
    DSMIF_B_CHANNEL_MASK_3   = (1U << 3U), ///< Channel 3 mask
    DSMIF_B_CHANNEL_MASK_4   = (1U << 4U), ///< Channel 4 mask
    DSMIF_B_CHANNEL_MASK_5   = (1U << 5U), ///< Channel 5 mask
} dsmif_b_channel_mask_t;

/** DSMIF Data Format Select */
typedef enum e_dsmif_b_format
{
    DSMIF_B_FORMAT_LEFT  = 0,          ///< Left justified
    DSMIF_B_FORMAT_RIGHT = 1           ///< Right justified
} dsmif_b_format_t;

/** DSMIF overcurrent detection window notification 3 mode select register */
typedef enum e_dsmif_b_owwm3_mode
{
    DSMIF_B_OWNM3_MODE_0             = 0x0, ///< Overcurrent detection window notification 0
    DSMIF_B_OWNM3_MODE_1             = 0x1, ///< Overcurrent detection window notification 1
    DSMIF_B_OWNM3_MODE_2             = 0x2, ///< Overcurrent detection window notification 2
    DSMIF_B_OWNM3_MODE_0_OR_1        = 0x3, ///< Overcurrent detection window notification 0 OR 1
    DSMIF_B_OWNM3_MODE_0_AND_1       = 0x4, ///< Overcurrent detection window notification 0 AND 1
    DSMIF_B_OWNM3_MODE_0_OR_2        = 0x5, ///< Overcurrent detection window notification 0 OR 2
    DSMIF_B_OWNM3_MODE_0_AND_2       = 0x6, ///< Overcurrent detection window notification 0 AND 2
    DSMIF_B_OWNM3_MODE_1_OR_2        = 0x7, ///< Overcurrent detection window notification 1 OR 2
    DSMIF_B_OWNM3_MODE_1_AND_2       = 0x8, ///< Overcurrent detection window notification 1 AND 2
    DSMIF_B_OWNM3_MODE_0_OR_1_OR_2   = 0x9, ///< Overcurrent detection window notification 0 OR 1 OR 2
    DSMIF_B_OWNM3_MODE_0_AND_1_AND_2 = 0xA, ///< Overcurrent detection window notification 0 AND 1 AND 2
} dsmif_b_owwm3_mode_t;

typedef struct st_dsmif_b_channel_cfg
{
    bool                   ioel[3];    ///< Overcurrent lower limit detection interrupt enable
    bool                   ioeh[3];    ///< Overcurrent upper limit exceeded output interrupt enable
    bool                   ise;        ///< Short circuit detection error interrupt enable bit
    bool                   iue;        ///< Current data register update interrupt enable
    dsmif_b_clock_ctrl_t   ckdir;      ///< A/D conversion clock master/slave switching
    dsmif_b_clock_edge_t   sedge;      ///< Sampling edge selection
    dsmif_b_master_clock_t ckdiv;      ///< A/D conversion clock division ratio
    dsmif_b_filter_order_t cmsinc;     ///< Current measurement filter order setting
    uint32_t               cmdec;      ///< Decimation ratio selection for current measurement
    dsimf_b_data_shift_t   cmsh;       ///< Data shift setting for current measurement
    bool                   sde;        ///< Short circuit detection enable bit
    dsmif_b_filter_order_t ocsinc;     ///< Overcurrent detection filter order setting
    uint32_t               ocdec;      ///< Decimation ratio selection for overcurrent detection
    dsimf_b_data_shift_t   ocsh;       ///< Data shift setting for overcurrent detection
    uint32_t               ocmptbl[3]; ///< Overcurrent detection lower limit
    uint32_t               ocmptbh[3]; ///< Overcurrent detection upper limit
    uint32_t               scntl;      ///< Short circuit detection low continuous detection count
    uint32_t               scnth;      ///< Short circuit detection high continuous detection count
    bool                   odel[3];    ///< Overcurrent lower limit detection enable bit
    bool                   odeh[3];    ///< Overcurrent upper limit exceeded detection enable bit
    bool                   owne[4];    ///< Overcurrent detection window notification output enable
    bool                   owfe[4];    ///< Overcurrent detection window function enable
    bool                   ownm0_2[3]; ///< Channel n overcurrent detection window notification mode select
    dsmif_b_owwm3_mode_t   ownm3;      ///< Channel n overcurrent detection window notification 3 mode select
} dsmif_b_channel_cfg_t;

/** DSMIF configuration extension. This extension is required and must be provided in dsmif_cfg_t::p_extend. */
typedef struct st_dsmif_b_extended_cfg
{
    bool isel;                                                               ///< Overcurrent sum error lower limit detection interrupt enable bit
    bool iseh;                                                               ///< Overcurrent sum error upper limit detection interrupt enable bit
    dsmif_b_sum_err_detect_channel_t sedm;                                   ///< Overcurrent sum error detect mode setting bit
    uint32_t scmptbl;                                                        ///< DSSELTR : Overcurrent Sum Error Detect Low Threshold Register
    uint32_t scmptbh;                                                        ///< DSSEHTR : Overcurrent Sum Error Detect High Threshold Register
    bool     seel;                                                           ///< DSSECR : Overcurrent Sum Error lower limit detection enable
    bool     seeh;                                                           ///< DSSECR : Overcurrent Sum Error upper limit detection enable
    dsmif_b_capture_trigger_t      cap_trig_a;                               ///< DSCMCTCRCHn.CTSELA[2:0] : Current capture trigger A selection bit
    dsmif_b_capture_trigger_t      cap_trig_b;                               ///< DSCMCTCRCHn.CTSELB[2:0] : Current capture trigger B selection bit
    dsmif_b_counter_init_trigger_t cnt_init_trig;                            ///< DSCMCTCRCHn.DITSEL[2:0] : Current measurement filter initialization trigger division counter for decimation.
    dsmif_b_clock_edge_t           edge;                                     ///< DSCMCTCRCHn.DEDGE[2:0]  : Current measurement filter initialization trigger for division counter for decimation edge.
    dsmif_b_format_t               dfs;                                      ///< Data Format Select
    dsmif_b_channel_cfg_t        * p_channel_cfgs[DSMIF_B_MAX_NUM_CHANNELS]; ///< Configuration for each channel, set to NULL if unused
    dsmif_b_channel_mask_t         channel_mask;                             ///< Channel bitmask
} dsmif_b_extended_cfg_t;

/** DSMIF instance control block. DO NOT INITIALIZE. */
typedef struct
{
    R_DSMIF0_Type   * p_reg;           // Base register for this unit
    adc_cfg_t const * p_cfg;
    uint32_t          opened;          // Boolean to verify that the Unit has been initialized
    uint32_t          channel_mask;    // Channel bitmask
    adc_mode_t        mode;            // DSMIF operation mode
    union
    {
        uint16_t results_16[DSMIF_B_MAX_NUM_CHANNELS];
        uint32_t results_32[DSMIF_B_MAX_NUM_CHANNELS];
    } results;
    void (* p_callback)(adc_callback_args_t *); // Pointer to callback that is called when an dsmif_event_t occurs.
    adc_callback_args_t * p_callback_memory;    // Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.

    /* Pointer to context to be passed into callback function */
    void const * p_context;
} dsmif_b_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Interface Structure for user access */
extern const adc_api_t g_adc_on_dsmif_b;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_B_Open(adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg);
fsp_err_t R_DSMIF_B_ScanStart(adc_ctrl_t * p_ctrl);
fsp_err_t R_DSMIF_B_ScanStop(adc_ctrl_t * p_ctrl);
fsp_err_t R_DSMIF_B_CfgSet(adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg);
fsp_err_t R_DSMIF_B_Read(adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint32_t * const p_data);
fsp_err_t R_DSMIF_B_StatusGet(adc_ctrl_t * p_ctrl, adc_status_t * p_status);
fsp_err_t R_DSMIF_B_RegStatusGet(adc_ctrl_t * p_ctrl, uint32_t * p_status);
fsp_err_t R_DSMIF_B_Close(adc_ctrl_t * p_ctrl);
fsp_err_t R_DSMIF_B_CallbackSet(adc_ctrl_t * const          p_api_ctrl,
                                void (                    * p_callback)(adc_callback_args_t *),
                                void const * const          p_context,
                                adc_callback_args_t * const p_callback_memory);

/*******************************************************************************************************************//**
 * @} (end defgroup DSMIF_B)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
