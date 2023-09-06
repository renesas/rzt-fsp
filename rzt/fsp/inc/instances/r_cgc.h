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

#ifndef R_CGC_H
#define R_CGC_H

/*******************************************************************************************************************//**
 * @addtogroup CGC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_cgc_cfg.h"
#include "r_cgc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define CGC_CODE_VERSION_MAJOR    (1U) // DEPRECATED
#define CGC_CODE_VERSION_MINOR    (3U) // DEPRECATED

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** DEPRECATED: Removed due to newer CGC API in the next major release. */
typedef enum e_cgc_xspi_clock_div
{
    CGC_XSPI_CLOCK_DIV_18  = 0x02,     ///< XSPI_CLKn 133.3MHz
    CGC_XSPI_CLOCK_DIV_24  = 0x03,     ///< XSPI_CLKn 100.0MHz
    CGC_XSPI_CLOCK_DIV_48  = 0x04,     ///< XSPI_CLKn 50.0MHz
    CGC_XSPI_CLOCK_DIV_96  = 0x05,     ///< XSPI_CLKn 25.0MHz
    CGC_XSPI_CLOCK_DIV_192 = 0x06,     ///< XSPI_CLKn 12.5MHz
    CGC_XSPI_CLOCK_DIV_32  = 0x43,     ///< XSPI_CLKn 75.0MHz
    CGC_XSPI_CLOCK_DIV_64  = 0x44,     ///< XSPI_CLKn 37.5MHz
} cgc_xspi_clock_div_t;

typedef enum e_cgc_clock_out_clock_div
{
    CGC_CLOCK_OUT_CLOCK_DIV_2 = 0,     ///< CKIO 100.0MHz / 75.0MHz (Base clock divided by 3 / divided by 4)
    CGC_CLOCK_OUT_CLOCK_DIV_3 = 1,     ///< CKIO 66.7MHz / 50.0MHz (Base clock divided by 3 / divided by 4)
    CGC_CLOCK_OUT_CLOCK_DIV_4 = 2,     ///< CKIO 50.0MHz / 37.5MHz (Base clock divided by 3 / divided by 4)
    CGC_CLOCK_OUT_CLOCK_DIV_5 = 3,     ///< CKIO 40.0MHz / 30.0MHz (Base clock divided by 3 / divided by 4)
    CGC_CLOCK_OUT_CLOCK_DIV_6 = 4,     ///< CKIO 33.3MHz / 25.0MHz (Base clock divided by 3 / divided by 4)
    CGC_CLOCK_OUT_CLOCK_DIV_7 = 5,     ///< CKIO 28.6MHz / 21.4MHz (Base clock divided by 3 / divided by 4)
    CGC_CLOCK_OUT_CLOCK_DIV_8 = 6,     ///< CKIO 25.0MHz / 18.75MHz (Base clock divided by 3 / divided by 4)
} cgc_clock_out_clock_div_t;

typedef enum e_cgc_canfd_clock_div
{
    CGC_CANFD_CLOCK_DIV_10 = 0,        ///< CANFD clock 80.0MHz
    CGC_CANFD_CLOCK_DIV_20 = 1,        ///< CANFD clock 40.0MHz
} cgc_canfd_clock_div_t;

typedef enum e_cgc_phy_clock
{
    CGC_PHY_CLOCK_PLL1     = 0,        ///< PLL1 divider clock
    CGC_PHY_CLOCK_MAIN_OSC = 1,        ///< Main clock oscillator
} cgc_phy_clock_t;

typedef enum e_cgc_spi_async_clock
{
    CGC_SPI_ASYNC_CLOCK_75MHZ = 0,     ///< SPI asynchronous serial clock 75MHz
    CGC_SPI_ASYNC_CLOCK_96MHZ = 1,     ///< SPI asynchronous serial clock 96MHz
} cgc_spi_async_clock_t;

typedef enum e_cgc_sci_async_clock
{
    CGC_SCI_ASYNC_CLOCK_75MHZ = 0,     ///< SCI asynchronous serial clock 75MHz
    CGC_SCI_ASYNC_CLOCK_96MHZ = 1,     ///< SCI asynchronous serial clock 96MHz
} cgc_sci_async_clock_t;

typedef enum e_cgc_cpu_clock_div
{
    CGC_CPU_CLOCK_DIV_1 = 0,           ///< CPU 800.0MHz / 600.0MHz (Base clock divided by 3 / divided by 4)
    CGC_CPU_CLOCK_DIV_2 = 1,           ///< CPU 400.0MHz / 300.0MHz (Base clock divided by 3 / divided by 4)
    CGC_CPU_CLOCK_DIV_4 = 2,           ///< CPU 200.0MHz / 150.0MHz (Base clock divided by 3 / divided by 4)
} cgc_cpu_clock_div_t;

typedef enum e_cgc_baseclock_div
{
    CGC_BASECLOCK_DIV_3 = 0,           ///< Base clock divided by 3 (ICLK=200.0MHz etc.)
    CGC_BASECLOCK_DIV_4 = 1,           ///< Base clock divided by 4 (ICLK=150.0MHz etc.)
} cgc_baseclock_div_t;

/** DEPRECATED: Removed due to newer CGC API in the next major release. */
typedef struct st_cgc_sckcr_cfg
{
    cgc_xspi_clock_div_t      fselxspi0_div;  ///< Divider value for XSPI_CLK0
    cgc_xspi_clock_div_t      fselxspi1_div;  ///< Divider value for XSPI_CLK1
    cgc_clock_out_clock_div_t ckio_div;       ///< Divider value for CKIO
    cgc_canfd_clock_div_t     fselcanfd_div;  ///< Divider value for CANFD clock
    cgc_phy_clock_t           phy_sel;        ///< Ethernet PHY reference clock output
    cgc_spi_async_clock_t     spi0_async_sel; ///< SPI0 asynchronous serial clock
    cgc_spi_async_clock_t     spi1_async_sel; ///< SPI1 asynchronous serial clock
    cgc_spi_async_clock_t     spi2_async_sel; ///< SPI2 asynchronous serial clock
    cgc_sci_async_clock_t     sci0_async_sel; ///< SCI0 asynchronous serial clock
    cgc_sci_async_clock_t     sci1_async_sel; ///< SCI1 asynchronous serial clock
    cgc_sci_async_clock_t     sci2_async_sel; ///< SCI2 asynchronous serial clock
    cgc_sci_async_clock_t     sci3_async_sel; ///< SCI3 asynchronous serial clock
    cgc_sci_async_clock_t     sci4_async_sel; ///< SCI4 asynchronous serial clock
} cgc_sckcr_cfg_t;

/** DEPRECATED: Removed due to newer CGC API in the next major release. */
typedef struct st_cgc_sckcr2_cfg
{
    cgc_cpu_clock_div_t   fsel0cr52;      ///< Divider value for Cortex-R52 CPU0
    cgc_cpu_clock_div_t   fsel1cr52;      ///< Divider value for Cortex-R52 CPU1
    cgc_baseclock_div_t   div_sub_sel;    ///< Divider value for base clock
    cgc_spi_async_clock_t spi3_async_sel; ///< SPI3 asynchronous serial clock
    cgc_sci_async_clock_t sci5_async_sel; ///< SCI5 asynchronous serial clock
} cgc_sckcr2_cfg_t;

/** DEPRECATED: Removed due to newer CGC API in the next major release. */
typedef struct st_cgc_clock_extend_cfg
{
    cgc_sckcr_cfg_t    sckcr;          ///< System Clock Control Register Settings
    cgc_sckcr2_cfg_t   sckcr2;         ///< System Clock Control Register 2 Settings
    cgc_clock_change_t pll1_state;     ///< State of PLL1
} cgc_clock_extend_cfg_t;

/** CGC private control block. DO NOT MODIFY. Initialization occurs when R_CGC_Open() is called. */
typedef struct st_cgc_instance_ctrl
{
    uint32_t open;
} cgc_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const cgc_api_t g_cgc_on_cgc;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_CGC_Open(cgc_ctrl_t * const p_ctrl, cgc_cfg_t const * const p_cfg);
fsp_err_t R_CGC_ClocksCfg(cgc_ctrl_t * const p_ctrl, cgc_clocks_cfg_t const * const p_clock_cfg);
fsp_err_t R_CGC_ClockStart(cgc_ctrl_t * const p_ctrl, cgc_clock_t clock_source, cgc_pll_cfg_t const * const p_pll_cfg);
fsp_err_t R_CGC_ClockStop(cgc_ctrl_t * const p_ctrl, cgc_clock_t clock_source);
fsp_err_t R_CGC_ClockCheck(cgc_ctrl_t * const p_ctrl, cgc_clock_t clock_source);
fsp_err_t R_CGC_SystemClockSet(cgc_ctrl_t * const              p_ctrl,
                               cgc_clock_t                     clock_source,
                               cgc_divider_cfg_t const * const p_divider_cfg);
fsp_err_t R_CGC_SystemClockGet(cgc_ctrl_t * const        p_ctrl,
                               cgc_clock_t * const       p_clock_source,
                               cgc_divider_cfg_t * const p_divider_cfg);
fsp_err_t R_CGC_OscStopDetectEnable(cgc_ctrl_t * const p_ctrl);
fsp_err_t R_CGC_OscStopDetectDisable(cgc_ctrl_t * const p_ctrl);
fsp_err_t R_CGC_OscStopStatusClear(cgc_ctrl_t * const p_ctrl);
fsp_err_t R_CGC_CallbackSet(cgc_ctrl_t * const          p_api_ctrl,
                            void (                    * p_callback)(cgc_callback_args_t *),
                            void const * const          p_context,
                            cgc_callback_args_t * const p_callback_memory);
fsp_err_t R_CGC_Close(cgc_ctrl_t * const p_ctrl);
fsp_err_t R_CGC_VersionGet(fsp_version_t * version);

/*******************************************************************************************************************//**
 * @} (end defgroup CGC)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

/* R_CGC_H */
#endif                                 // R_CGC_H
