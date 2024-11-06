/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_primitive.h"
#include "r_rsip_reg.h"
#include "r_rsip_util.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func302 (void)
{
    uint32_t iLoop;
    uint32_t jLoop;
    uint32_t kLoop;
    uint32_t oLoop;
    uint32_t oLoop1;
    uint32_t OFS_ADR;
    (void) iLoop;
    (void) jLoop;
    (void) kLoop;
    (void) oLoop;
    (void) oLoop1;
    (void) OFS_ADR;
    WR1_PROG(REG_1404H, 0x17a80000U);
    WR1_PROG(REG_1608H, 0x800102e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1400H, 0x00030005U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x03430005U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1404H, 0x1f480000U);
    WR1_PROG(REG_1608H, 0x80010300U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1400H, 0x00030005U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x03430005U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1014H, 0x00000838U);
    WR1_PROG(REG_1018H, 0x00000fd8U);
    WR1_PROG(REG_1020H, 0x00000e50U);
    WR1_PROG(REG_1004H, 0x1111000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0U, 0U);
    WR1_PROG(REG_143CH, 0x00a10000U);
    r_rsip_func100(bswap_32big(0x0ad147d1U),
                   bswap_32big(0xc15f605eU),
                   bswap_32big(0x98b8d053U),
                   bswap_32big(0xcaf90da0U));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        WR1_PROG(REG_1600H, 0x38000af8U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        r_rsip_func100(bswap_32big(0x25b8b836U), bswap_32big(0xa683a101U), bswap_32big(0x2728a978U),
                       bswap_32big(0x4ac23913U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1014H, 0x00000838U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000838U);
            WR1_PROG(REG_1004H, 0x11110009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            r_rsip_func101(bswap_32big(0xfbd25faaU), bswap_32big(0xad06cdafU), bswap_32big(0x8af078f2U),
                           bswap_32big(0xe85ad4f9U));
        }
        else
        {
            WR1_PROG(REG_1014H, 0x00000838U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000838U);
            WR1_PROG(REG_1004H, 0x1111000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            r_rsip_func101(bswap_32big(0x260d4f6fU), bswap_32big(0x17e04d4dU), bswap_32big(0xa28beda1U),
                           bswap_32big(0xeee7456aU));
        }
    }
    else
    {
        WR1_PROG(REG_1600H, 0x38000af8U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        r_rsip_func100(bswap_32big(0xdfd7e8ebU), bswap_32big(0xcf0d10feU), bswap_32big(0xcb4654e4U),
                       bswap_32big(0x93e9f40bU));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1014H, 0x00000838U);
            WR1_PROG(REG_1018H, 0x00000fd8U);
            WR1_PROG(REG_1020H, 0x00000838U);
            WR1_PROG(REG_1004H, 0x11110009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            r_rsip_func101(bswap_32big(0x102f78a7U), bswap_32big(0x1d299a05U), bswap_32big(0x2a7b9fd1U),
                           bswap_32big(0x52f9290cU));
        }
        else
        {
            WR1_PROG(REG_1014H, 0x00000fd8U);
            WR1_PROG(REG_1018H, 0x00000838U);
            WR1_PROG(REG_1020H, 0x00000838U);
            WR1_PROG(REG_1004H, 0x1111000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1600H, 0x0000dee0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0xd71d061cU), bswap_32big(0x04f6ae8eU), bswap_32big(0x41bf5b4fU),
                           bswap_32big(0x9155cf06U));
        }
    }

    WR1_PROG(REG_1404H, 0x17a80000U);
    WR1_PROG(REG_1608H, 0x810102e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1400H, 0x00c00005U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1400H, 0x00c90005U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
