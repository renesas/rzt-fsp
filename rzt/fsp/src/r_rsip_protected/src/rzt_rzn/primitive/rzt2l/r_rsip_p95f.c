/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
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

rsip_ret_t r_rsip_p95f (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t OutData_MAC[])
{
    RSIP_PRV_PRIMITIVE_ENTRY;
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
    WR1_PROG(REG_1600H, 0x00003409U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00008c00U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000000fU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);
    r_rsip_func100(bswap_32big(0xe66c8978U),
                   bswap_32big(0xaf2b677bU),
                   bswap_32big(0xdc20aa66U),
                   bswap_32big(0xdfba9a5cU));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        WR1_PROG(REG_1444H, 0x000003c1U);
        WR1_PROG(REG_1824H, 0xe7000d05U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_Text[0]);
        WR1_ADDR(REG_1420H, &InData_Text[1]);
        WR1_ADDR(REG_1420H, &InData_Text[2]);
        WR1_ADDR(REG_1420H, &InData_Text[3]);
        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x80840001U);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_subfunc003(0x03410011U);
        WR1_PROG(REG_1600H, 0x00000821U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000a400U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000b7e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1458H, 0x00000000U);
        for (iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
        {
            WR1_PROG(REG_1600H, 0x3c002be0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x12003c3fU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00002fe0U);
            WR1_PROG(REG_1458H, 0x00000000U);
        }

        r_rsip_func100(bswap_32big(0xa5e8f206U), bswap_32big(0x49bef2ecU), bswap_32big(0x41c5946eU),
                       bswap_32big(0x3b52c43bU));
        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x81840001U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1408H, 0x00005012U);
        WAIT_STS(REG_1408H, 30U, 1U);
        RD1_ADDR(REG_1420H, &OutData_Text[0]);
        WAIT_STS(REG_1408H, 30U, 1U);
        RD1_ADDR(REG_1420H, &OutData_Text[1]);
        WAIT_STS(REG_1408H, 30U, 1U);
        RD1_ADDR(REG_1420H, &OutData_Text[2]);
        WAIT_STS(REG_1408H, 30U, 1U);
        RD1_ADDR(REG_1420H, &OutData_Text[3]);
        r_rsip_func101(bswap_32big(0xadb12cb5U), bswap_32big(0x7c3b2c60U), bswap_32big(0x45882eadU),
                       bswap_32big(0xebd4a1c1U));
    }
    else
    {
        r_rsip_func101(bswap_32big(0xf25ed2c2U), bswap_32big(0xa2e7a22cU), bswap_32big(0x5bbb6a4fU),
                       bswap_32big(0xe1fb1743U));
    }

    WR1_PROG(REG_1444H, 0x000000a1U);
    WR1_PROG(REG_1824H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    r_rsip_func100(bswap_32big(0x6c4a90dfU),
                   bswap_32big(0xb58112e5U),
                   bswap_32big(0x924d4e87U),
                   bswap_32big(0x2e8075ebU));
    WR1_PROG(REG_1824H, 0x09100105U);
    r_rsip_subfunc003(0x00410011U);
    WR1_PROG(REG_1408H, 0x00001012U);
    WAIT_STS(REG_1408H, 30U, 1U);
    RD1_ADDR(REG_1420H, &OutData_MAC[0]);
    RD1_ADDR(REG_1420H, &OutData_MAC[1]);
    RD1_ADDR(REG_1420H, &OutData_MAC[2]);
    RD1_ADDR(REG_1420H, &OutData_MAC[3]);
    r_rsip_func102(bswap_32big(0x83ab9c6dU),
                   bswap_32big(0xfbbfa6b4U),
                   bswap_32big(0x941a71d2U),
                   bswap_32big(0xec1778fcU));
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12U, 0U);

    return RSIP_RET_PASS;
}
