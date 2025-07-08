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

rsip_ret_t r_rsip_pe4 (const uint32_t InData_HashType[], const uint32_t InData_EncSecret[], uint32_t OutData_KeyIndex[])
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
    if (0x0U != RD1_MASK(REG_14B8H, 0x1eU))
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00e40002U);
    WR1_PROG(REG_144CH, 0x00000000U);
    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010080U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000c84U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);
    r_rsip_func100(bswap_32big(0x6c3ab0d3U),
                   bswap_32big(0x2529174cU),
                   bswap_32big(0x852f1b78U),
                   bswap_32big(0xc56d887dU));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0x43974a37U), bswap_32big(0x1e8baedeU), bswap_32big(0x7b2750d0U),
                       bswap_32big(0x563574a1U));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12U, 0U);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000003c7U);
        WR1_PROG(REG_1608H, 0x80040000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncSecret[0]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[1]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[2]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[3]);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_subfunc009(bswap_32big(0x0000e401U));
        r_rsip_func101(bswap_32big(0x6dd6e658U), bswap_32big(0x7fa37d03U), bswap_32big(0x2db1f1e4U),
                       bswap_32big(0x46bc6977U));
        r_rsip_func045();
        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x013df795U);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_subfunc009(bswap_32big(0x0000e401U));
        r_rsip_func101(bswap_32big(0xe4dcb584U), bswap_32big(0xbfb3be69U), bswap_32big(0xd2f14235U),
                       bswap_32big(0xbb69c32cU));
        r_rsip_func046();
        WR1_PROG(REG_1444H, 0x000007c2U);
        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0xf7009d07U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncSecret[4]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[5]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[6]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[7]);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncSecret[8]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[9]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[10]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[11]);
        WR1_PROG(REG_1600H, 0x000008a5U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x80880005U);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_subfunc003(0x03420021U);
        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncSecret[12]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[13]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[14]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[15]);
        WR1_PROG(REG_1A24H, 0x9c100005U);
        r_rsip_subfunc003(0x00820011U);
        r_rsip_func100(bswap_32big(0x5702c0fbU), bswap_32big(0xbcd536e0U), bswap_32big(0x32b46cc8U),
                       bswap_32big(0xc6ab7acaU));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func102(bswap_32big(0xeac9b820U), bswap_32big(0x1f6af9e3U), bswap_32big(0x90d62a51U),
                           bswap_32big(0xcb16279cU));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0x915d7428U), bswap_32big(0x293772bcU), bswap_32big(0x3182a0afU),
                           bswap_32big(0x43d72faaU));
            r_rsip_func103();
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0c200104U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
            WR1_PROG(REG_1608H, 0x80040000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_subfunc003(0x03420011U);
            r_rsip_subfunc009(bswap_32big(0x0000e402U));
            r_rsip_func101(bswap_32big(0x05252299U), bswap_32big(0x6fc0c4caU), bswap_32big(0x1c3e413dU),
                           bswap_32big(0x9ea24495U));
            r_rsip_func045();
            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x01a5a796U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_subfunc009(bswap_32big(0x0000e402U));
            r_rsip_func101(bswap_32big(0xfdbc3650U), bswap_32big(0x338d6e80U), bswap_32big(0x38b50760U),
                           bswap_32big(0x2eeeeaf4U));
            r_rsip_func046();
            r_rsip_func100(bswap_32big(0xa460c5a3U), bswap_32big(0x0db7b0b4U), bswap_32big(0x6b939c37U),
                           bswap_32big(0x302cd5adU));
            WR1_PROG(REG_1A2CH, 0x40000100U);
            WR1_PROG(REG_1A24H, 0xe7009d07U);
            WR1_PROG(REG_1608H, 0x81880005U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_subfunc003(0x00890021U);
            WR1_PROG(REG_1408H, 0x00002022U);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[4]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[5]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[6]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[7]);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[8]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[9]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[10]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[11]);
            r_rsip_func100(bswap_32big(0x024647f8U), bswap_32big(0x05c0b74eU), bswap_32big(0x081b27bfU),
                           bswap_32big(0x5b105dd7U));
            WR1_PROG(REG_1A2CH, 0x40000100U);
            WR1_PROG(REG_1A24H, 0xe7008d07U);
            r_rsip_subfunc003(0x00800021U);
            WR1_PROG(REG_1408H, 0x00002022U);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[12]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[13]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[14]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[15]);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[16]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[17]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[18]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[19]);
            r_rsip_func100(bswap_32big(0xc4928eb1U), bswap_32big(0xa6b4f1b1U), bswap_32big(0xe0bd722bU),
                           bswap_32big(0x34baedf1U));
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0c000104U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0x09108105U);
            r_rsip_subfunc003(0x00820011U);
            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[20]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[21]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[22]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[23]);
            r_rsip_func100(bswap_32big(0x8465ea14U), bswap_32big(0x3705568fU), bswap_32big(0xb28654eeU),
                           bswap_32big(0x394d87f0U));
            WR1_PROG(REG_1608H, 0x81040000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1408H, 0x00005012U);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[0]);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[1]);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[2]);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[3]);
            r_rsip_func102(bswap_32big(0x6f45dca9U), bswap_32big(0x5e4258dbU), bswap_32big(0xca047e7dU),
                           bswap_32big(0x2e8acc9dU));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_PASS;
        }
    }
}
