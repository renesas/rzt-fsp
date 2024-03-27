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

#ifndef R_ICU_ERROR_H
#define R_ICU_ERROR_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_error_api.h"
#include "r_icu_error_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define ERROR_TABLE_MAX_ENTRIES    (128)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef void (* error_table_t)(uint32_t id);

/** ICU_ERROR CPU0 Error Code */
typedef enum e_icu_error_cpu0_error
{
    ICU_ERROR_CPU0_ERROR_EVENT0  = (1UL << 0),
    ICU_ERROR_CPU0_ERROR_EVENT1  = (1UL << 1),
    ICU_ERROR_CPU0_ERROR_EVENT2  = (1UL << 2),
    ICU_ERROR_CPU0_ERROR_EVENT3  = (1UL << 3),
    ICU_ERROR_CPU0_ERROR_EVENT4  = (1UL << 4),
    ICU_ERROR_CPU0_ERROR_EVENT5  = (1UL << 5),
    ICU_ERROR_CPU0_ERROR_EVENT6  = (1UL << 6),
    ICU_ERROR_CPU0_ERROR_EVENT7  = (1UL << 7),
    ICU_ERROR_CPU0_ERROR_EVENT8  = (1UL << 8),
    ICU_ERROR_CPU0_ERROR_EVENT9  = (1UL << 9),
    ICU_ERROR_CPU0_ERROR_EVENT10 = (1UL << 10),
    ICU_ERROR_CPU0_ERROR_EVENT11 = (1UL << 11),
    ICU_ERROR_CPU0_ERROR_EVENT12 = (1UL << 12),
    ICU_ERROR_CPU0_ERROR_EVENT13 = (1UL << 13),
    ICU_ERROR_CPU0_ERROR_EVENT14 = (1UL << 14),
    ICU_ERROR_CPU0_ERROR_EVENT15 = (1UL << 15),
    ICU_ERROR_CPU0_ERROR_EVENT16 = (1UL << 16),
    ICU_ERROR_CPU0_ERROR_EVENT17 = (1UL << 17),
    ICU_ERROR_CPU0_ERROR_EVENT18 = (1UL << 18),
    ICU_ERROR_CPU0_ERROR_EVENT19 = (1UL << 19),
    ICU_ERROR_CPU0_ERROR_EVENT20 = (1UL << 20),
    ICU_ERROR_CPU0_ERROR_EVENT21 = (1UL << 21),
    ICU_ERROR_CPU0_ERROR_EVENT22 = (1UL << 22),
    ICU_ERROR_CPU0_ERROR_EVENT23 = (1UL << 23),
    ICU_ERROR_CPU0_ERROR_EVENT24 = (1UL << 24),
    ICU_ERROR_CPU0_ERROR_EVENT25 = (1UL << 25)
} icu_error_cpu0_error_t;

#if BSP_FEATURE_ICU_ERROR_CR52_CPU1_SUPPORTED

/** ICU_ERROR CPU1 Error Code */
typedef enum e_icu_error_cpu1_error
{
    ICU_ERROR_CPU1_ERROR_EVENT0  = (1UL << 0),
    ICU_ERROR_CPU1_ERROR_EVENT1  = (1UL << 1),
    ICU_ERROR_CPU1_ERROR_EVENT2  = (1UL << 2),
    ICU_ERROR_CPU1_ERROR_EVENT3  = (1UL << 3),
    ICU_ERROR_CPU1_ERROR_EVENT4  = (1UL << 4),
    ICU_ERROR_CPU1_ERROR_EVENT5  = (1UL << 5),
    ICU_ERROR_CPU1_ERROR_EVENT6  = (1UL << 6),
    ICU_ERROR_CPU1_ERROR_EVENT7  = (1UL << 7),
    ICU_ERROR_CPU1_ERROR_EVENT8  = (1UL << 8),
    ICU_ERROR_CPU1_ERROR_EVENT9  = (1UL << 9),
    ICU_ERROR_CPU1_ERROR_EVENT10 = (1UL << 10),
    ICU_ERROR_CPU1_ERROR_EVENT11 = (1UL << 11),
    ICU_ERROR_CPU1_ERROR_EVENT12 = (1UL << 12),
    ICU_ERROR_CPU1_ERROR_EVENT13 = (1UL << 13),
    ICU_ERROR_CPU1_ERROR_EVENT14 = (1UL << 14),
    ICU_ERROR_CPU1_ERROR_EVENT15 = (1UL << 15),
    ICU_ERROR_CPU1_ERROR_EVENT16 = (1UL << 16),
    ICU_ERROR_CPU1_ERROR_EVENT17 = (1UL << 17),
    ICU_ERROR_CPU1_ERROR_EVENT18 = (1UL << 18),
    ICU_ERROR_CPU1_ERROR_EVENT19 = (1UL << 19),
    ICU_ERROR_CPU1_ERROR_EVENT20 = (1UL << 20),
    ICU_ERROR_CPU1_ERROR_EVENT21 = (1UL << 21),
    ICU_ERROR_CPU1_ERROR_EVENT22 = (1UL << 22),
    ICU_ERROR_CPU1_ERROR_EVENT23 = (1UL << 23),
    ICU_ERROR_CPU1_ERROR_EVENT24 = (1UL << 24),
    ICU_ERROR_CPU1_ERROR_EVENT25 = (1UL << 25)
} icu_error_cpu1_error_t;
#endif

#if BSP_FEATURE_ICU_ERROR_PERIPHERAL_TYPE == 1

/** ICU_ERROR Peripheral 0 Error Code */
typedef enum e_icu_error_peripheral_error_0
{
    ICU_ERROR_PERIPHERAL_ERROR_0_CLMA_INT      = (1UL << 0),  // Main OSC stop detection
    ICU_ERROR_PERIPHERAL_ERROR_0_CLMA0_INT     = (1UL << 1),  // CLMA0 error detection
    ICU_ERROR_PERIPHERAL_ERROR_0_CLMA1_INT     = (1UL << 2),  // CLMA1 error detection
    ICU_ERROR_PERIPHERAL_ERROR_0_CLMA2_INT     = (1UL << 3),  // CLMA2 error detection
    ICU_ERROR_PERIPHERAL_ERROR_0_BSC_WTO       = (1UL << 4),  // External wait timeout detection interrupt
    ICU_ERROR_PERIPHERAL_ERROR_0_DMAC0_ERR     = (1UL << 5),  // DMAC0 transfer error
    ICU_ERROR_PERIPHERAL_ERROR_0_DMAC1_ERR     = (1UL << 6),  // DMAC1 transfer error
    ICU_ERROR_PERIPHERAL_ERROR_0_WDT_NMIUNDF0  = (1UL << 7),  // Down-counter underflow/refresh error for CPU0
    ICU_ERROR_PERIPHERAL_ERROR_0_WDT_NMIUNDF1  = (1UL << 8),  // Down-counter underflow/refresh error for CPU1
    ICU_ERROR_PERIPHERAL_ERROR_0_USB_FDMAERR   = (1UL << 9),  // USB (Function) DMA error
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_LTCSE  = (1UL << 10), // DSMIF0 lower threshold current sum error
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_UTCSE  = (1UL << 11), // DSMIF0 upper threshold current sum error
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_LTODE0 = (1UL << 12), // DSMIF0 lower threshold overcurrent detection 0
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_LTODE1 = (1UL << 13), // DSMIF0 lower threshold overcurrent detection 1
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_LTODE2 = (1UL << 14), // DSMIF0 lower threshold overcurrent detection 2
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_UTODE0 = (1UL << 15), // DSMIF0 upper threshold overcurrent detection 0
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_UTODE1 = (1UL << 16), // DSMIF0 upper threshold overcurrent detection 1
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_UTODE2 = (1UL << 17), // DSMIF0 upper threshold overcurrent detection 2
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_SCDE0  = (1UL << 18), // DSMIF0 Short-circuit detection 0
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_SCDE1  = (1UL << 19), // DSMIF0 Short-circuit detection 1
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_SCDE2  = (1UL << 20), // DSMIF0 Short-circuit detection 2
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_LTCSE  = (1UL << 21), // DSMIF1 lower threshold current sum error
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_UTCSE  = (1UL << 22), // DSMIF1 upper threshold current sum error
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_LTODE0 = (1UL << 23), // DSMIF1 lower threshold overcurrent detection 0
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_LTODE1 = (1UL << 24), // DSMIF1 lower threshold overcurrent detection 1
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_LTODE2 = (1UL << 25), // DSMIF1 lower threshold overcurrent detection 2
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_UTODE0 = (1UL << 26), // DSMIF1 upper threshold overcurrent detection 0
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_UTODE1 = (1UL << 27), // DSMIF1 upper threshold overcurrent detection 1
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_UTODE2 = (1UL << 28), // DSMIF1 upper threshold overcurrent detection 2
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_SCDE0  = (1UL << 29), // DSMIF1 Short-circuit detection 0
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_SCDE1  = (1UL << 30), // DSMIF1 Short-circuit detection 1
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_SCDE2  = (1UL << 31), // DSMIF1 Short-circuit detection 2
} icu_error_peripheral_error_0_t;

/** ICU_ERROR Peripheral 1 Error Code */
typedef enum e_icu_error_peripheral_error_1
{
    ICU_ERROR_PERIPHERAL_ERROR_1_DOC_DOPCI       = (1UL << 0),  // DOC interrupt
    ICU_ERROR_PERIPHERAL_ERROR_1_SRAM0_IE1       = (1UL << 1),  // System SRAM0 ECC 1 bit error
    ICU_ERROR_PERIPHERAL_ERROR_1_SRAM0_IE2       = (1UL << 2),  // System SRAM0 ECC 2 bits error
    ICU_ERROR_PERIPHERAL_ERROR_1_SRAM0_OVF       = (1UL << 3),  // System SRAM0 ECC error address capture overflow
    ICU_ERROR_PERIPHERAL_ERROR_1_SRAM1_IE1       = (1UL << 4),  // System SRAM1 ECC 1 bit error
    ICU_ERROR_PERIPHERAL_ERROR_1_SRAM1_IE2       = (1UL << 5),  // System SRAM1 ECC 2 bits error
    ICU_ERROR_PERIPHERAL_ERROR_1_SRAM1_OVF       = (1UL << 6),  // System SRAM1 ECC error address capture overflow
    ICU_ERROR_PERIPHERAL_ERROR_1_SRAM2_IE1       = (1UL << 7),  // System SRAM2 ECC 1 bit error
    ICU_ERROR_PERIPHERAL_ERROR_1_SRAM2_IE2       = (1UL << 8),  // System SRAM2 ECC 2 bits error
    ICU_ERROR_PERIPHERAL_ERROR_1_SRAM2_OVF       = (1UL << 9),  // System SRAM2 ECC error address capture overflow
    ICU_ERROR_PERIPHERAL_ERROR_1_SRAM3_IE1       = (1UL << 10), // System SRAM3 ECC 1 bit error
    ICU_ERROR_PERIPHERAL_ERROR_1_SRAM3_IE2       = (1UL << 11), // System SRAM3 ECC 2 bits error
    ICU_ERROR_PERIPHERAL_ERROR_1_SRAM3_OVF       = (1UL << 12), // System SRAM3 ECC error address capture overflow
    ICU_ERROR_PERIPHERAL_ERROR_1_MAIN_BUS_ERRINT = (1UL << 13), // Main bus error
    ICU_ERROR_PERIPHERAL_ERROR_1_LLPP_BUS_ERRINT = (1UL << 14), // LLPP bus error
    ICU_ERROR_PERIPHERAL_ERROR_1_CPU1RMPU        = (1UL << 15), // CPU1 read error to Master MPU registers
    ICU_ERROR_PERIPHERAL_ERROR_1_CPU1WMPU        = (1UL << 16), // CPU1 write error to Master MPU registers
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_DMACR0      = (1UL << 17), // Master MPU Read channel for DMAC0 error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_DMACW0      = (1UL << 18), // Master MPU Write channel for DMAC0 error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_DMACR1      = (1UL << 19), // Master MPU Read channel for DMAC1 error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_DMACW1      = (1UL << 20), // Master MPU Write channel for DMAC1 error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_GMACR       = (1UL << 21), // Master MPU Read channel for GMAC error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_GMACW       = (1UL << 22), // Master MPU Write channel for GMAC error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_USBH        = (1UL << 23), // Master MPU for USB Host error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_USBF        = (1UL << 24), // Master MPU for USB Function error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_DBGR        = (1UL << 27), // Master MPU Read channel for Debug error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_DBGW        = (1UL << 28), // Master MPU Write channel for Debug error
} icu_error_peripheral_error_1_t;
#endif

#if BSP_FEATURE_ICU_ERROR_PERIPHERAL_TYPE == 2

/** ICU_ERROR Peripheral 0 Error Code */
typedef enum e_icu_error_peripheral_error_0
{
    ICU_ERROR_PERIPHERAL_ERROR_0_CLMA_INT       = (1UL << 0),  // Main OSC stop detection
    ICU_ERROR_PERIPHERAL_ERROR_0_CLMA0_INT      = (1UL << 1),  // CLMA0 error detection
    ICU_ERROR_PERIPHERAL_ERROR_0_CLMA1_INT      = (1UL << 2),  // CLMA1 error detection
    ICU_ERROR_PERIPHERAL_ERROR_0_CLMA2_INT      = (1UL << 3),  // CLMA2 error detection
    ICU_ERROR_PERIPHERAL_ERROR_0_BSC_WTO        = (1UL << 4),  // External wait timeout detection interrupt
    ICU_ERROR_PERIPHERAL_ERROR_0_DMAC0_ERR      = (1UL << 5),  // DMAC0 transfer error
    ICU_ERROR_PERIPHERAL_ERROR_0_DMAC1_ERR      = (1UL << 6),  // DMAC1 transfer error
    ICU_ERROR_PERIPHERAL_ERROR_0_WDT_NMIUNDF0   = (1UL << 7),  // Down-counter underflow/refresh error for CPU0
    ICU_ERROR_PERIPHERAL_ERROR_0_USB_FDMAERR    = (1UL << 9),  // USB (Function) DMA error
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_LTCSE   = (1UL << 10), // DSMIF0 lower threshold current sum error
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_UTCSE   = (1UL << 11), // DSMIF0 upper threshold current sum error
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_OVC0EL0 = (1UL << 12), // DSMIF0 lower threshold overcurrent detection 0 CH0
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_OVC0EL1 = (1UL << 13), // DSMIF0 lower threshold overcurrent detection 0 CH1
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_OVC0EL2 = (1UL << 14), // DSMIF0 lower threshold overcurrent detection 0 CH2
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_OVC0EH0 = (1UL << 15), // DSMIF0 upper threshold overcurrent detection 0 CH0
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_OVC0EH1 = (1UL << 16), // DSMIF0 upper threshold overcurrent detection 0 CH1
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_OVC0EH2 = (1UL << 17), // DSMIF0 upper threshold overcurrent detection 0 CH2
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_SCDE0   = (1UL << 18), // DSMIF0 Short-circuit detection 0
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_SCDE1   = (1UL << 19), // DSMIF0 Short-circuit detection 1
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF0_SCDE2   = (1UL << 20), // DSMIF0 Short-circuit detection 2
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_LTCSE   = (1UL << 21), // DSMIF1 lower threshold current sum error
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_UTCSE   = (1UL << 22), // DSMIF1 upper threshold current sum error
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_OVC0EL0 = (1UL << 23), // DSMIF1 lower threshold overcurrent detection 0 CH3
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_OVC0EL1 = (1UL << 24), // DSMIF1 lower threshold overcurrent detection 0 CH4
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_OVC0EL2 = (1UL << 25), // DSMIF1 lower threshold overcurrent detection 0 CH5
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_OVC0EH0 = (1UL << 26), // DSMIF1 upper threshold overcurrent detection 0 CH3
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_OVC0EH1 = (1UL << 27), // DSMIF1 upper threshold overcurrent detection 0 CH4
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_OVC0EH2 = (1UL << 28), // DSMIF1 upper threshold overcurrent detection 0 CH5
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_SCDE0   = (1UL << 29), // DSMIF1 Short-circuit detection 0
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_SCDE1   = (1UL << 30), // DSMIF1 Short-circuit detection 1
    ICU_ERROR_PERIPHERAL_ERROR_0_DSMIF1_SCDE2   = (1UL << 31), // DSMIF1 Short-circuit detection 2
} icu_error_peripheral_error_0_t;

/** ICU_ERROR Peripheral 1 Error Code */
typedef enum e_icu_error_peripheral_error_1
{
    ICU_ERROR_PERIPHERAL_ERROR_1_DOC_DOPCI      = (1UL << 0),  // DOC interrupt
    ICU_ERROR_PERIPHERAL_ERROR_1_SRAM0_IE1      = (1UL << 1),  // System SRAM0 ECC 1 bit error
    ICU_ERROR_PERIPHERAL_ERROR_1_SRAM0_IE2      = (1UL << 2),  // System SRAM0 ECC 2 bits error
    ICU_ERROR_PERIPHERAL_ERROR_1_SRAM0_OVF      = (1UL << 3),  // System SRAM0 ECC error address capture overflow
    ICU_ERROR_PERIPHERAL_ERROR_1_SRAM1_IE1      = (1UL << 4),  // System SRAM1 ECC 1 bit error
    ICU_ERROR_PERIPHERAL_ERROR_1_SRAM1_IE2      = (1UL << 5),  // System SRAM1 ECC 2 bits error
    ICU_ERROR_PERIPHERAL_ERROR_1_SRAM1_OVF      = (1UL << 6),  // System SRAM1 ECC error address capture overflow
    ICU_ERROR_PERIPHERAL_ERROR_1_BUSERR         = (1UL << 13), // Bus error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_SHOST      = (1UL << 15), // Master MPU for Serial Host I/F error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_DMACR0     = (1UL << 17), // Master MPU Read channel for DMAC0 error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_DMACW0     = (1UL << 18), // Master MPU Write channel for DMAC0 error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_DMACR1     = (1UL << 19), // Master MPU Read channel for DMAC1 error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_DMACW1     = (1UL << 20), // Master MPU Write channel for DMAC1 error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_GMACR      = (1UL << 21), // Master MPU Read channel for GMAC error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_GMACW      = (1UL << 22), // Master MPU Write channel for GMAC error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_USBH       = (1UL << 23), // Master MPU for USB Host error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_USBF       = (1UL << 24), // Master MPU for USB Function error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_DBGR       = (1UL << 27), // Master MPU Read channel for Debug error
    ICU_ERROR_PERIPHERAL_ERROR_1_MPU_DBGW       = (1UL << 28), // Master MPU Write channel for Debug error
    ICU_ERROR_PERIPHERAL_ERROR_1_DSMIF0_OVC1EL0 = (1UL << 29), // DSMIF0 lower threshold overcurrent detection 1 CH0
    ICU_ERROR_PERIPHERAL_ERROR_1_DSMIF0_OVC1EH0 = (1UL << 30), // DSMIF0 upper threshold overcurrent detection 1 CH0
    ICU_ERROR_PERIPHERAL_ERROR_1_DSMIF0_OVC2EL0 = (1UL << 31), // DSMIF0 lower threshold overcurrent detection 2 CH0
} icu_error_peripheral_error_1_t;

/** ICU_ERROR Peripheral 2 Error Code */
typedef enum e_icu_error_peripheral_error_2
{
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC2EH0 = (1UL << 0),  // DSMIF0 upper threshold overcurrent detection 2 CH0
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC1EL1 = (1UL << 1),  // DSMIF0 lower threshold overcurrent detection 1 CH1
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC1EH1 = (1UL << 2),  // DSMIF0 upper threshold overcurrent detection 1 CH1
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC2EL1 = (1UL << 3),  // DSMIF0 lower threshold overcurrent detection 2 CH1
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC2EH1 = (1UL << 4),  // DSMIF0 upper threshold overcurrent detection 2 CH1
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC1EL2 = (1UL << 5),  // DSMIF0 lower threshold overcurrent detection 1 CH2
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC1EH2 = (1UL << 6),  // DSMIF0 upper threshold overcurrent detection 1 CH2
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC2EL2 = (1UL << 7),  // DSMIF0 lower threshold overcurrent detection 2 CH2
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC2EH2 = (1UL << 8),  // DSMIF0 upper threshold overcurrent detection 2 CH2
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC0WN0 = (1UL << 9),  // DSMIF0 Overcurrent Detection Window Notification 0 CH0
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC1WN0 = (1UL << 10), // DSMIF0 Overcurrent Detection Window Notification 1 CH0
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC2WN0 = (1UL << 11), // DSMIF0 Overcurrent Detection Window Notification 2 CH0
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC3WN0 = (1UL << 12), // DSMIF0 Overcurrent Detection Window Notification 3 CH0
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC0WN1 = (1UL << 13), // DSMIF0 Overcurrent Detection Window Notification 0 CH1
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC1WN1 = (1UL << 14), // DSMIF0 Overcurrent Detection Window Notification 1 CH1
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC2WN1 = (1UL << 15), // DSMIF0 Overcurrent Detection Window Notification 2 CH1
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC3WN1 = (1UL << 16), // DSMIF0 Overcurrent Detection Window Notification 3 CH1
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC0WN2 = (1UL << 17), // DSMIF0 Overcurrent Detection Window Notification 0 CH2
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC1WN2 = (1UL << 18), // DSMIF0 Overcurrent Detection Window Notification 1 CH2
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC2WN2 = (1UL << 19), // DSMIF0 Overcurrent Detection Window Notification 2 CH2
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF0_OVC3WN2 = (1UL << 20), // DSMIF0 Overcurrent Detection Window Notification 3 CH2
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF1_OVC1EL0 = (1UL << 21), // DSMIF1 lower threshold overcurrent detection 1 CH3
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF1_OVC1EH0 = (1UL << 22), // DSMIF1 upper threshold overcurrent detection 1 CH3
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF1_OVC2EL0 = (1UL << 23), // DSMIF1 lower threshold overcurrent detection 2 CH3
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF1_OVC2EH0 = (1UL << 24), // DSMIF1 upper threshold overcurrent detection 2 CH3
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF1_OVC1EL1 = (1UL << 25), // DSMIF1 lower threshold overcurrent detection 1 CH4
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF1_OVC1EH1 = (1UL << 26), // DSMIF1 upper threshold overcurrent detection 1 CH4
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF1_OVC2EL1 = (1UL << 27), // DSMIF1 lower threshold overcurrent detection 2 CH4
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF1_OVC2EH1 = (1UL << 28), // DSMIF1 upper threshold overcurrent detection 2 CH4
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF1_OVC1EL2 = (1UL << 29), // DSMIF1 lower threshold overcurrent detection 1 CH5
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF1_OVC1EH2 = (1UL << 30), // DSMIF1 upper threshold overcurrent detection 1 CH5
    ICU_ERROR_PERIPHERAL_ERROR_2_DSMIF1_OVC2EL2 = (1UL << 31), // DSMIF1 lower threshold overcurrent detection 2 CH5
} icu_error_peripheral_error_2_t;

/** ICU_ERROR Peripheral 3 Error Code */
typedef enum e_icu_error_peripheral_error_3
{
    ICU_ERROR_PERIPHERAL_ERROR_3_DSMIF1_OVC2EH2         = (1UL << 0),  // DSMIF1 upper threshold overcurrent detection 2 CH5
    ICU_ERROR_PERIPHERAL_ERROR_3_DSMIF1_OVC0WN0         = (1UL << 1),  // DSMIF1 Overcurrent Detection Window Notification 0 CH3
    ICU_ERROR_PERIPHERAL_ERROR_3_DSMIF1_OVC1WN0         = (1UL << 2),  // DSMIF1 Overcurrent Detection Window Notification 1 CH3
    ICU_ERROR_PERIPHERAL_ERROR_3_DSMIF1_OVC2WN0         = (1UL << 3),  // DSMIF1 Overcurrent Detection Window Notification 2 CH3
    ICU_ERROR_PERIPHERAL_ERROR_3_DSMIF1_OVC3WN0         = (1UL << 4),  // DSMIF1 Overcurrent Detection Window Notification 3 CH3
    ICU_ERROR_PERIPHERAL_ERROR_3_DSMIF1_OVC0WN1         = (1UL << 5),  // DSMIF1 Overcurrent Detection Window Notification 0 CH4
    ICU_ERROR_PERIPHERAL_ERROR_3_DSMIF1_OVC1WN1         = (1UL << 6),  // DSMIF1 Overcurrent Detection Window Notification 1 CH4
    ICU_ERROR_PERIPHERAL_ERROR_3_DSMIF1_OVC2WN1         = (1UL << 7),  // DSMIF1 Overcurrent Detection Window Notification 2 CH4
    ICU_ERROR_PERIPHERAL_ERROR_3_DSMIF1_OVC3WN1         = (1UL << 8),  // DSMIF1 Overcurrent Detection Window Notification 3 CH4
    ICU_ERROR_PERIPHERAL_ERROR_3_DSMIF1_OVC0WN2         = (1UL << 9),  // DSMIF1 Overcurrent Detection Window Notification 0 CH5
    ICU_ERROR_PERIPHERAL_ERROR_3_DSMIF1_OVC1WN2         = (1UL << 10), // DSMIF1 Overcurrent Detection Window Notification 1 CH5
    ICU_ERROR_PERIPHERAL_ERROR_3_DSMIF1_OVC2WN2         = (1UL << 11), // DSMIF1 Overcurrent Detection Window Notification 2 CH5
    ICU_ERROR_PERIPHERAL_ERROR_3_DSMIF1_OVC3WN2         = (1UL << 12), // DSMIF1 Overcurrent Detection Window Notification 3 CH5
    ICU_ERROR_PERIPHERAL_ERROR_3_BISS0_NER              = (1UL << 13), // BISS0 Error interrupt
    ICU_ERROR_PERIPHERAL_ERROR_3_BISS1_NER              = (1UL << 14), // BISS1 Error interrupt
    ICU_ERROR_PERIPHERAL_ERROR_3_HDSL0_estimator_on     = (1UL << 15), // HDSL0 Position Estimator activated
    ICU_ERROR_PERIPHERAL_ERROR_3_HDSL0_safe_channel_err = (1UL << 16), // HDSL0 Transmission error in safe channel 1
    ICU_ERROR_PERIPHERAL_ERROR_3_HDSL0_safe_pos_err     = (1UL << 17), // HDSL0 Safe position not valid
    ICU_ERROR_PERIPHERAL_ERROR_3_HDSL0_acceleration_err = (1UL << 18), // HDSL0 Fast channel / position error
    ICU_ERROR_PERIPHERAL_ERROR_3_HDSL0_acc_thr_err      = (1UL << 19), // HDSL0 Fast channel / position threshold error
    ICU_ERROR_PERIPHERAL_ERROR_3_HDSL0_encoding_err     = (1UL << 20), // HDSL0 DSL message encoding error
    ICU_ERROR_PERIPHERAL_ERROR_3_HDSL0_dev_thr_err      = (1UL << 21), // HDSL0 Estimator deviation threshold reached
    ICU_ERROR_PERIPHERAL_ERROR_3_HDSL1_estimator_on     = (1UL << 22), // HDSL1 Position Estimator activated
    ICU_ERROR_PERIPHERAL_ERROR_3_HDSL1_safe_channel_err = (1UL << 23), // HDSL1 Transmission error in safe channel 1
    ICU_ERROR_PERIPHERAL_ERROR_3_HDSL1_safe_pos_err     = (1UL << 24), // HDSL1 Safe position not valid
    ICU_ERROR_PERIPHERAL_ERROR_3_HDSL1_acceleration_err = (1UL << 25), // HDSL1 Fast channel / position error
    ICU_ERROR_PERIPHERAL_ERROR_3_HDSL1_acc_thr_err      = (1UL << 26), // HDSL1 Fast channel / position threshold error
    ICU_ERROR_PERIPHERAL_ERROR_3_HDSL1_encoding_err     = (1UL << 27), // HDSL1 DSL message encoding error
    ICU_ERROR_PERIPHERAL_ERROR_3_HDSL1_dev_thr_err      = (1UL << 28), // HDSL1 Estimator deviation threshold reached
    ICU_ERROR_PERIPHERAL_ERROR_3_AFMT0_TMOUT            = (1UL << 29), // AFMT0 Time out error
    ICU_ERROR_PERIPHERAL_ERROR_3_AFMT1_TMOUT            = (1UL << 30), // AFMT1 Time out error
} icu_error_peripheral_error_3_t;
#endif

/** ERROR instance control block. Do not initialize. Initialization occurs when the @ref error_api_t::open function is called. */
typedef struct st_icu_error_instance_ctrl
{
    error_cfg_t const * p_cfg;         // Pointer to the configuration structure
    uint32_t            open;          ///< Used by driver to check if the control structure is valid

    /* Pointer to callback and optional working memory */
    void (* p_callback)(error_callback_args_t *);
    error_callback_args_t * p_callback_memory;
    void const            * p_context; ///< User defined context passed into callback function
} icu_error_instance_ctrl_t;

/** ERROR event configuration extension. */
typedef struct st_icu_error_extended_cfg
{
    uint8_t   cpu0_err0_ipl;                     ///< Cortex-R52 CPU0 error 0 interrupt priority
    IRQn_Type cpu0_err0_irq;                     ///< Cortex-R52 CPU0 error 0 interrupt IRQ number
    uint8_t   cpu0_err1_ipl;                     ///< Cortex-R52 CPU0 error 1 interrupt priority
    IRQn_Type cpu0_err1_irq;                     ///< Cortex-R52 CPU0 error 1 interrupt IRQ number
    uint8_t   cpu1_err0_ipl;                     ///< Cortex-R52 CPU1 error 0 interrupt interrupt priority
    IRQn_Type cpu1_err0_irq;                     ///< Cortex-R52 CPU1 error 0 interrupt IRQ number
    uint8_t   cpu1_err1_ipl;                     ///< Cortex-R52 CPU1 error 1 interrupt interrupt priority
    IRQn_Type cpu1_err1_irq;                     ///< Cortex-R52 CPU1 error 1 interrupt IRQ number
    uint8_t   peri_err0_ipl;                     ///< Peripheral error 0 interrupt priority
    IRQn_Type peri_err0_irq;                     ///< Peripheral error 0 interrupt IRQ number
    uint8_t   peri_err1_ipl;                     ///< Peripheral error 1 interrupt priority
    IRQn_Type peri_err1_irq;                     ///< Peripheral error 1 interrupt IRQ number

    uint32_t cpu0_err_reset_mask;                ///< Cortex-R52 CPU0 error reset mask
    uint32_t cpu0_err0_event_mask;               ///< Cortex-R52 CPU0 error 0 event mask
    uint32_t cpu0_err1_event_mask;               ///< Cortex-R52 CPU0 error 1 event mask
#if BSP_FEATURE_ICU_ERROR_CR52_CPU1_SUPPORTED
    uint32_t cpu1_err_reset_mask;                ///< Cortex-R52 CPU1 error reset mask
    uint32_t cpu1_err0_event_mask;               ///< Cortex-R52 CPU1 error 0 event mask
    uint32_t cpu1_err1_event_mask;               ///< Cortex-R52 CPU1 error 1 event mask
#endif
    uint32_t peri_err_event_0_reset_mask;        ///< Peripheral error event 0 reset mask
    uint32_t peri_err0_event_0_mask;             ///< Peripheral error 0 event 0 mask
    uint32_t peri_err1_event_0_mask;             ///< Peripheral error 1 event 0 mask
    uint32_t peri_err_event_1_reset_mask;        ///< Peripheral error event 1 reset mask
    uint32_t peri_err0_event_1_mask;             ///< Peripheral error 0 event 1 mask
    uint32_t peri_err1_event_1_mask;             ///< Peripheral error 1 event 1 mask
#if BSP_FEATURE_ICU_ERROR_PERI_ERR_REG_NUM == 4
    uint32_t peri_err_event_2_reset_mask;        ///< Peripheral error event 2 reset mask
    uint32_t peri_err0_event_2_mask;             ///< Peripheral error 0 event 2 mask
    uint32_t peri_err1_event_2_mask;             ///< Peripheral error 1 event 2 mask
    uint32_t peri_err_event_3_reset_mask;        ///< Peripheral error event 3 reset mask
    uint32_t peri_err0_event_3_mask;             ///< Peripheral error 0 event 3 mask
    uint32_t peri_err1_event_3_mask;             ///< Peripheral error 1 event 3 mask
#endif

    const error_table_t * p_error_handler_table; ///< Peripheral error handler table
} icu_error_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const error_api_t g_error_on_icu_error;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_ICU_ERROR_Open(error_ctrl_t * const p_ctrl, error_cfg_t const * const p_cfg);
fsp_err_t R_ICU_ERROR_Close(error_ctrl_t * const p_ctrl);
fsp_err_t R_ICU_ERROR_StatusGet(error_ctrl_t * const p_ctrl, uint32_t source, uint32_t * p_status);
fsp_err_t R_ICU_ERROR_StatusClear(error_ctrl_t * const p_ctrl, uint32_t source, uint32_t event);
fsp_err_t R_ICU_ERROR_CallbackSet(error_ctrl_t * const          p_ctrl,
                                  void (                      * p_callback)(error_callback_args_t *),
                                  void const * const            p_context,
                                  error_callback_args_t * const p_callback_memory);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
