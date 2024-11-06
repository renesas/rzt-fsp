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

rsip_ret_t r_rsip_pf0 (const uint32_t InData_CurveType[],
                       const uint32_t InData_Cmd[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_MsgDgst[],
                       uint32_t       OutData_Signature[])
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
    if (0x0U != RD1_MASK(REG_14B8H, 0x1eU))
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00f00002U);
    WR1_PROG(REG_144CH, 0x00000000U);
    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000007f0U);
    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010340U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_CurveType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010380U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_Cmd[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000bdeU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1444H, 0x000007c7U);
    WR1_PROG(REG_1608H, 0x8088001eU);
    WR1_PROG(REG_1458H, 0x00000000U);
    for (iLoop = 0; iLoop < 8; iLoop = iLoop + 1)
    {
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_MsgDgst[iLoop + 0]);
        WR1_PROG(REG_1458H, 0x00000000U);
    }

    WR1_PROG(REG_1600H, 0x00000bffU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x30003380U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00070020U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000d3e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00030040U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000381eU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000c00U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x1000d3e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00050040U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000381eU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x000037beU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000a7a0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000383dU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38001001U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x1000d3e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x30000f5aU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00030020U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000d3e1U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000060U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000f9cU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x1000d3e1U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38008be0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);
    r_rsip_func100(bswap_32big(0xecdceaedU),
                   bswap_32big(0xcb25aa4aU),
                   bswap_32big(0x40c47301U),
                   bswap_32big(0x1c764753U));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0x41f6cb62U), bswap_32big(0x191382a9U), bswap_32big(0x1aa1e3d6U),
                       bswap_32big(0xaad8bb9bU));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12U, 0U);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1404H, 0x10200000U);
        WR1_PROG(REG_1400H, 0x00c00051U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1404H, 0x10700000U);
        WR1_PROG(REG_1400H, 0x00c00051U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1404H, 0x13400000U);
        WR1_PROG(REG_1400H, 0x00c00051U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1404H, 0x17f00000U);
        WR1_PROG(REG_1400H, 0x00c00051U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1404H, 0x18400000U);
        WR1_PROG(REG_1400H, 0x00c00051U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1404H, 0x18900000U);
        WR1_PROG(REG_1400H, 0x00c00051U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        r_rsip_func100(bswap_32big(0xc9a5c4f5U), bswap_32big(0xf8fe5330U), bswap_32big(0x6fd32599U),
                       bswap_32big(0xf0546f3fU));
        WR1_PROG(REG_1600H, 0x30003340U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00010020U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000b400U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000158U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000060U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x30003380U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00070020U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000b400U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00030040U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000b400U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x000000C8U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00050040U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000b400U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000110U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000080U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x81010000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30U, 1U);
        RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[0]);
        OFS_ADR = S_RAM[0];
        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x000000f0U));
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func101(bswap_32big(0xc0474e7fU), bswap_32big(0xa752613fU), bswap_32big(0x02813af6U),
                       bswap_32big(0x71c69bd1U));
        r_rsip_func086(OFS_ADR);
        r_rsip_func100(bswap_32big(0x9ab8f63fU), bswap_32big(0x4cb6da8eU), bswap_32big(0x41cf34f0U),
                       bswap_32big(0xb62a93ecU));
        WR1_PROG(REG_1404H, 0x11400000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
        WR1_PROG(REG_1400H, 0x00c0001dU);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00c20005U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x000000c0U);
        WR1_PROG(REG_1018H, 0x00000160U);
        WR1_PROG(REG_1020H, 0x00000430U);
        WR1_PROG(REG_1004H, 0x0404000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1010H, 0x00000020U);
        WR1_PROG(REG_101CH, 0x00000430U);
        WR1_PROG(REG_1004H, 0x04040010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1010H, 0x00000018U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1004H, 0x04040010U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x10c00000U);
        WR1_PROG(REG_1400H, 0x00c00051U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1404H, 0x10f00000U);
        r_rsip_func103();
        r_rsip_func100(bswap_32big(0x6ca8eaf5U), bswap_32big(0x5ee6f62eU), bswap_32big(0x787fa8feU),
                       bswap_32big(0xb613e7a9U));
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c200104U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        WR1_PROG(REG_1400H, 0x00c20011U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        r_rsip_func103();
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c200104U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        WR1_PROG(REG_1400H, 0x00c20011U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000110U);
        WR1_PROG(REG_101CH, 0x00000430U);
        WR1_PROG(REG_1020H, 0x00000160U);
        WR1_PROG(REG_1010H, 0x00000020U);
        WR1_PROG(REG_1004H, 0x04040004U);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x14380000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
        WR1_PROG(REG_1400H, 0x00c0001dU);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00c20005U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x0002000dU);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000160U);
        WR1_PROG(REG_1018H, 0x00000458U);
        WR1_PROG(REG_1020H, 0x00000340U);
        WR1_PROG(REG_1004H, 0x04040009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x11600000U);
        WR1_PROG(REG_1400H, 0x00c000f1U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x000000f0U));
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func101(bswap_32big(0x88b70eb0U), bswap_32big(0xce76e0c7U), bswap_32big(0xaa2b88a4U),
                       bswap_32big(0x8f3bee9cU));
        r_rsip_func087(OFS_ADR);
        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x000000f0U));
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func101(bswap_32big(0x3f1224feU), bswap_32big(0xdf195f83U), bswap_32big(0x4514b14eU),
                       bswap_32big(0x5b464bc9U));
        r_rsip_func088();
        r_rsip_func100(bswap_32big(0x6574c38bU), bswap_32big(0xe26cb475U), bswap_32big(0x68475596U),
                       bswap_32big(0xea732206U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func102(bswap_32big(0xce463649U), bswap_32big(0x4dd4e93aU), bswap_32big(0x110bd0ccU),
                           bswap_32big(0x1935d7e3U));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_1010H, 0x00000020U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1004H, 0x04040010U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x000002a0U);
            WR1_PROG(REG_1018H, 0x00000840U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x000002f0U);
            WR1_PROG(REG_1010H, 0x00000020U);
            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010201U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x000002f0U);
            WR1_PROG(REG_101CH, 0x000000c0U);
            WR1_PROG(REG_1020H, 0x000002a0U);
            WR1_PROG(REG_1004H, 0x04040004U);
            WR1_PROG(REG_1000H, 0x00010201U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1404H, 0x10f00000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
            WR1_PROG(REG_1400H, 0x00c0001dU);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x00c20005U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1400H, 0x0002000dU);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1014H, 0x000002a0U);
            WR1_PROG(REG_1018H, 0x00000110U);
            WR1_PROG(REG_1020H, 0x00000140U);
            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_143CH, 0x00210000U);
            r_rsip_func100(bswap_32big(0x12111ebeU), bswap_32big(0x7aca18e8U), bswap_32big(0x1cf9b58bU),
                           bswap_32big(0xa54fa5e7U));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                r_rsip_func102(bswap_32big(0x87694088U),
                               bswap_32big(0x72310acbU),
                               bswap_32big(0xf4355379U),
                               bswap_32big(0x3512f1d2U));
                WR1_PROG(REG_14B8H, 0x00000040U);
                WAIT_STS(REG_142CH, 12U, 0U);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0x8a3f3767U),
                               bswap_32big(0x6270de61U),
                               bswap_32big(0xf318f59cU),
                               bswap_32big(0xc1b29df4U));
                WR1_PROG(REG_1404H, 0x11400000U);
                WR1_PROG(REG_1444H, 0x000000a2U);
                WR1_PROG(REG_1A24H, 0x08000104U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
                WR1_PROG(REG_1400H, 0x00c0001dU);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x00c20005U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1400H, 0x0002000dU);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1014H, 0x000000c0U);
                WR1_PROG(REG_1018H, 0x00000160U);
                WR1_PROG(REG_1020H, 0x00000110U);
                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1014H, 0x00000340U);
                WR1_PROG(REG_1018H, 0x00000110U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x00000160U);
                WR1_PROG(REG_1004H, 0x0404000fU);
                WR1_PROG(REG_1408H, 0x00020000U);
                WR1_PROG(REG_1000H, 0x00010201U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_143CH, 0x00000d00U);
                WR1_PROG(REG_1014H, 0x00000160U);
                WR1_PROG(REG_1018H, 0x00000840U);
                WR1_PROG(REG_101CH, 0x000000c0U);
                WR1_PROG(REG_1020H, 0x00000110U);
                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010201U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1600H, 0x00000bdeU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x8188001eU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1404H, 0x11400000U);
                WR1_PROG(REG_1400H, 0x00c90021U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1444H, 0x000003c7U);
                WR1_PROG(REG_1608H, 0x80040000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_KeyIndex[0]);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_KeyIndex[1]);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_KeyIndex[2]);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_KeyIndex[3]);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x000000f0U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xf47b5bdcU),
                               bswap_32big(0x3c7ed257U),
                               bswap_32big(0x72c5f86eU),
                               bswap_32big(0xb0873f36U));
                r_rsip_func045();
                r_rsip_func022();
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x000000f0U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xda603f23U),
                               bswap_32big(0x69a5d167U),
                               bswap_32big(0xcaad0a44U),
                               bswap_32big(0x40645b58U));
                r_rsip_func046();
                WR1_PROG(REG_1444H, 0x000007c2U);
                WR1_PROG(REG_1A2CH, 0x40000100U);
                WR1_PROG(REG_1A24H, 0xf7009d07U);
                for (iLoop = 0; iLoop < 8; iLoop = iLoop + 4)
                {
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 4]);
                    WR1_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 5]);
                    WR1_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 6]);
                    WR1_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 7]);
                }

                WR1_PROG(REG_1404H, 0x11e00000U);
                WR1_PROG(REG_1400H, 0x00c20021U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1444H, 0x000003c2U);
                WR1_PROG(REG_1A2CH, 0x40000000U);
                WR1_PROG(REG_1A24H, 0x07008d05U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 4]);
                WR1_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 5]);
                WR1_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 6]);
                WR1_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 7]);
                WR1_PROG(REG_1A24H, 0x9c100005U);
                WR1_PROG(REG_1400H, 0x00820011U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                r_rsip_func100(bswap_32big(0x686574c2U),
                               bswap_32big(0xd2deac8fU),
                               bswap_32big(0x93b2811fU),
                               bswap_32big(0x5a237e12U));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    r_rsip_func102(bswap_32big(0x1dfe2845U),
                                   bswap_32big(0x1dbc028eU),
                                   bswap_32big(0x8f18af5dU),
                                   bswap_32big(0x72996559U));
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12U, 0U);

                    return RSIP_RET_KEY_FAIL;
                }
                else
                {
                    WR1_PROG(REG_1014H, 0x00000200U);
                    WR1_PROG(REG_1018H, 0x00000840U);
                    WR1_PROG(REG_101CH, 0x000000c0U);
                    WR1_PROG(REG_1020H, 0x000001b0U);
                    WR1_PROG(REG_1004H, 0x04040002U);
                    WR1_PROG(REG_1000H, 0x00010201U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_1014H, 0x000001b0U);
                    WR1_PROG(REG_1018H, 0x000002a0U);
                    WR1_PROG(REG_101CH, 0x000000c0U);
                    WR1_PROG(REG_1020H, 0x00000200U);
                    WR1_PROG(REG_1004H, 0x04040002U);
                    WR1_PROG(REG_1000H, 0x00010201U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_1014H, 0x00000160U);
                    WR1_PROG(REG_1018H, 0x00000200U);
                    WR1_PROG(REG_101CH, 0x000000c0U);
                    WR1_PROG(REG_1020H, 0x000001b0U);
                    WR1_PROG(REG_1004H, 0x04040005U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_1014H, 0x00000110U);
                    WR1_PROG(REG_1018H, 0x000001b0U);
                    WR1_PROG(REG_101CH, 0x000000c0U);
                    WR1_PROG(REG_1020H, 0x00000200U);
                    WR1_PROG(REG_1004H, 0x04040002U);
                    WR1_PROG(REG_1000H, 0x00010201U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_1404H, 0x10f00000U);
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x08000104U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
                    WR1_PROG(REG_1400H, 0x00c0001dU);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x00c20005U);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x0002000dU);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1014H, 0x00000200U);
                    WR1_PROG(REG_1018H, 0x00000110U);
                    WR1_PROG(REG_1020H, 0x00000160U);
                    WR1_PROG(REG_1004H, 0x0404000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_143CH, 0x00210000U);
                    r_rsip_func100(bswap_32big(0x7475169cU),
                                   bswap_32big(0x49852f27U),
                                   bswap_32big(0x3a3aee0aU),
                                   bswap_32big(0xa4f6308dU));
                    WR1_PROG(REG_143CH, 0x00400000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    if (CHCK_STS(REG_143CH, 22U, 1U))
                    {
                        r_rsip_func102(bswap_32big(0xb6b49acfU),
                                       bswap_32big(0x02937201U),
                                       bswap_32big(0xf85d73dbU),
                                       bswap_32big(0xec24eb7bU));
                        WR1_PROG(REG_14B8H, 0x00000040U);
                        WAIT_STS(REG_142CH, 12U, 0U);

                        return RSIP_RET_FAIL;
                    }
                    else
                    {
                        r_rsip_func100(bswap_32big(0x983e3a0cU),
                                       bswap_32big(0x93f43dd0U),
                                       bswap_32big(0xbc5a01a9U),
                                       bswap_32big(0xbd783ae6U));
                        WR1_PROG(REG_1404H, 0x12800000U);
                        WR1_PROG(REG_1A2CH, 0x00000100U);
                        WR1_PROG(REG_1A24H, 0x08008107U);
                        WR1_PROG(REG_1400H, 0x00830021U);
                        WAIT_STS(REG_1404H, 30U, 0U);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1408H, 0x00002022U);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_Signature[0]);
                        RD1_ADDR(REG_1420H, &OutData_Signature[1]);
                        RD1_ADDR(REG_1420H, &OutData_Signature[2]);
                        RD1_ADDR(REG_1420H, &OutData_Signature[3]);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_Signature[4]);
                        RD1_ADDR(REG_1420H, &OutData_Signature[5]);
                        RD1_ADDR(REG_1420H, &OutData_Signature[6]);
                        RD1_ADDR(REG_1420H, &OutData_Signature[7]);
                        r_rsip_func100(bswap_32big(0xaff32dc8U),
                                       bswap_32big(0x894c5ce5U),
                                       bswap_32big(0x41d28829U),
                                       bswap_32big(0x3e2ae2d4U));
                        WR1_PROG(REG_1404H, 0x11e00000U);
                        WR1_PROG(REG_1A2CH, 0x00000100U);
                        WR1_PROG(REG_1A24H, 0x08008107U);
                        WR1_PROG(REG_1400H, 0x00830021U);
                        WAIT_STS(REG_1404H, 30U, 0U);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1408H, 0x00002022U);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_Signature[8]);
                        RD1_ADDR(REG_1420H, &OutData_Signature[9]);
                        RD1_ADDR(REG_1420H, &OutData_Signature[10]);
                        RD1_ADDR(REG_1420H, &OutData_Signature[11]);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_Signature[12]);
                        RD1_ADDR(REG_1420H, &OutData_Signature[13]);
                        RD1_ADDR(REG_1420H, &OutData_Signature[14]);
                        RD1_ADDR(REG_1420H, &OutData_Signature[15]);
                        r_rsip_func102(bswap_32big(0xab845ee7U),
                                       bswap_32big(0x422d26ffU),
                                       bswap_32big(0x8f32349eU),
                                       bswap_32big(0x987c78eaU));
                        WR1_PROG(REG_14B8H, 0x00000040U);
                        WAIT_STS(REG_142CH, 12U, 0U);

                        return RSIP_RET_PASS;
                    }
                }
            }
        }
    }
}
