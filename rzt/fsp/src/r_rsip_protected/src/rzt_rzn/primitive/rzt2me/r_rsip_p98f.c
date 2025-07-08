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

rsip_ret_t r_rsip_p98f (const uint32_t InData_Text[], const uint32_t InData_MAC[], uint32_t OutData_Text[])
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
    WR1_PROG(REG_1600H, 0x38008940U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    WR1_PROG(REG_1600H, 0x0000b7e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000010U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x34202beaU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    r_rsip_func100(bswap_32big(0x8efd6c78U),
                   bswap_32big(0xe635f38aU),
                   bswap_32big(0xae33ea67U),
                   bswap_32big(0x5be69c48U));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0xa00a1b84U), bswap_32big(0xeabc7afbU), bswap_32big(0xe24354fcU),
                       bswap_32big(0x583e7646U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12U, 0U);

        return RSIP_RET_FAIL;
    }
    else
    {
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
        r_rsip_func100(bswap_32big(0x8b81be78U), bswap_32big(0x6945822fU), bswap_32big(0x7302b71eU),
                       bswap_32big(0x4a44e352U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x07000d05U);
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

            r_rsip_func100(bswap_32big(0x78ade9bbU), bswap_32big(0x5a0f4162U), bswap_32big(0xc286a185U),
                           bswap_32big(0xcd5a4b3cU));
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
            WR1_PROG(REG_1824H, 0x0e100405U);
            WR1_PROG(REG_1608H, 0x81840001U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_subfunc003(0x00490011U);
            r_rsip_func101(bswap_32big(0x837f3f9aU), bswap_32big(0x341f947eU), bswap_32big(0x7e595be8U),
                           bswap_32big(0x87f6e286U));
        }
        else
        {
            r_rsip_func101(bswap_32big(0xce87cbeeU), bswap_32big(0xfd735e5eU), bswap_32big(0xf4088d3dU),
                           bswap_32big(0x0f06b561U));
        }

        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_1824H, 0x0c100104U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        WR1_PROG(REG_1824H, 0x07200d05U);
        r_rsip_subfunc003(0x00410011U);
        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x80840001U);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_subfunc003(0x03410011U);
        WR1_PROG(REG_1600H, 0x0000a540U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000b7e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000821U);
        WR1_PROG(REG_1458H, 0x00000000U);
        for (iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
        {
            WR1_PROG(REG_1600H, 0x3c002beaU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x12003c3fU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00002fe0U);
            WR1_PROG(REG_1458H, 0x00000000U);
        }

        WR1_PROG(REG_1444H, 0x000003c1U);
        WR1_PROG(REG_1824H, 0x08000055U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_MAC[0]);
        WR1_ADDR(REG_1420H, &InData_MAC[1]);
        WR1_ADDR(REG_1420H, &InData_MAC[2]);
        WR1_ADDR(REG_1420H, &InData_MAC[3]);
        WR1_PROG(REG_1824H, 0x9c100005U);
        WR1_PROG(REG_1600H, 0x0000b420U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x81840001U);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_subfunc003(0x00490011U);
        WR1_PROG(REG_1824H, 0x00000000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func100(bswap_32big(0x51915896U), bswap_32big(0xca181c5cU), bswap_32big(0xc71d120fU),
                       bswap_32big(0x8c9b8123U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func102(bswap_32big(0xedd3e586U), bswap_32big(0x1843c696U), bswap_32big(0x97221ad8U),
                           bswap_32big(0xa74bdb80U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_AUTH_FAIL;
        }
        else
        {
            r_rsip_func102(bswap_32big(0xd8d8ebdaU), bswap_32big(0xe313085dU), bswap_32big(0x12aa4193U),
                           bswap_32big(0x58514629U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_PASS;
        }
    }
}
