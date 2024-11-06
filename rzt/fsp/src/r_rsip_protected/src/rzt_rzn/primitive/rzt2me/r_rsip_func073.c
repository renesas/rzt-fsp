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

void r_rsip_func073 (uint32_t ARG1)
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
    WR1_PROG(REG_1600H, 0x0000377dU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000007f0U);
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
    OFS_ADR = ARG1;
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x0000f073U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0x454edaf4U),
                   bswap_32big(0xffbdee68U),
                   bswap_32big(0xb355c7b0U),
                   bswap_32big(0x0ab049fdU));
    r_rsip_func086(OFS_ADR);
    WR1_PROG(REG_1010H, 0x00000020U);
    WR1_PROG(REG_101CH, 0x000000c0U);
    WR1_PROG(REG_1004H, 0x04040010U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0U, 0U);
    WR1_PROG(REG_1010H, 0x00000018U);
    WR1_PROG(REG_101CH, 0x00000070U);
    WR1_PROG(REG_1004H, 0x04040010U);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0U, 0U);
    WR1_PROG(REG_1404H, 0x11e00000U);
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
    WR1_PROG(REG_1014H, 0x000000c0U);
    WR1_PROG(REG_1018H, 0x00000200U);
    WR1_PROG(REG_1020H, 0x00000160U);
    WR1_PROG(REG_1004H, 0x0404000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0U, 0U);
    WR1_PROG(REG_1014H, 0x00000160U);
    WR1_PROG(REG_1018H, 0x00000930U);
    WR1_PROG(REG_1020H, 0x000001b0U);
    WR1_PROG(REG_1004H, 0x0404000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0U, 0U);
    WR1_PROG(REG_143CH, 0x00210000U);
    WR1_PROG(REG_1014H, 0x00000930U);
    WR1_PROG(REG_1018H, 0x00000200U);
    WR1_PROG(REG_1020H, 0x000001b0U);
    WR1_PROG(REG_1004H, 0x0404000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0U, 0U);
    WR1_PROG(REG_143CH, 0x00210000U);
    WR1_PROG(REG_1014H, 0x00000160U);
    WR1_PROG(REG_1018H, 0x00000980U);
    WR1_PROG(REG_1020H, 0x000001b0U);
    WR1_PROG(REG_1004H, 0x0404000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0U, 0U);
    WR1_PROG(REG_143CH, 0x00210000U);
    WR1_PROG(REG_1014H, 0x00000980U);
    WR1_PROG(REG_1018H, 0x00000200U);
    WR1_PROG(REG_1020H, 0x000001b0U);
    WR1_PROG(REG_1004H, 0x0404000aU);
    WR1_PROG(REG_1000H, 0x00010001U);
    WAIT_STS(REG_1000H, 0U, 0U);
    WR1_PROG(REG_143CH, 0x00210000U);
    r_rsip_func100(bswap_32big(0xc68ab49dU),
                   bswap_32big(0xfb438bbcU),
                   bswap_32big(0xe7d29cb2U),
                   bswap_32big(0xcff64177U));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        WR1_PROG(REG_1600H, 0x00000800U);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func101(bswap_32big(0xbd4c8396U), bswap_32big(0xff5e7ebbU), bswap_32big(0xbec67c05U),
                       bswap_32big(0x43469ad9U));
    }
    else
    {
        r_rsip_func100(bswap_32big(0xaff58a80U), bswap_32big(0x69553a85U), bswap_32big(0x788e64a8U),
                       bswap_32big(0x0ed1de86U));
        WR1_PROG(REG_1014H, 0x00000160U);
        WR1_PROG(REG_1018H, 0x00000200U);
        WR1_PROG(REG_1020H, 0x000001b0U);
        WR1_PROG(REG_1004H, 0x0404000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000980U);
        WR1_PROG(REG_1018H, 0x000001b0U);
        WR1_PROG(REG_101CH, 0x000000c0U);
        WR1_PROG(REG_1020H, 0x00000110U);
        WR1_PROG(REG_1010H, 0x00000020U);
        WR1_PROG(REG_1004H, 0x0404000fU);
        WR1_PROG(REG_1408H, 0x00020000U);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_143CH, 0x00000d00U);
        WR1_PROG(REG_1014H, 0x00000110U);
        WR1_PROG(REG_1018H, 0x00000840U);
        WR1_PROG(REG_101CH, 0x000000c0U);
        WR1_PROG(REG_1020H, 0x00000160U);
        WR1_PROG(REG_1004H, 0x04040002U);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x10c00000U);
        WR1_PROG(REG_1400H, 0x00c00051U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1404H, 0x10f00000U);
        WR1_PROG(REG_1600H, 0x00000bffU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x8188001fU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1400H, 0x00c90021U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000110U);
        WR1_PROG(REG_1018H, 0x00000160U);
        WR1_PROG(REG_101CH, 0x000000c0U);
        WR1_PROG(REG_1020H, 0x00000340U);
        WR1_PROG(REG_1004H, 0x04040002U);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000930U);
        WR1_PROG(REG_1018H, 0x00000160U);
        WR1_PROG(REG_101CH, 0x000000c0U);
        WR1_PROG(REG_1020H, 0x00000110U);
        WR1_PROG(REG_1004H, 0x04040002U);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1010H, 0x00000018U);
        WR1_PROG(REG_1404H, 0x11600000U);
        WR1_PROG(REG_1400H, 0x00c000f1U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x0000f073U));
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func101(bswap_32big(0x62100a06U), bswap_32big(0x7584ff7fU), bswap_32big(0xfed583afU),
                       bswap_32big(0x83f51ed6U));
        r_rsip_func087(OFS_ADR);
        WR1_PROG(REG_1014H, 0x00000390U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000250U);
        WR1_PROG(REG_1004H, 0x04040004U);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x11400000U);
        WR1_PROG(REG_1400H, 0x00c00021U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000890U);
        WR1_PROG(REG_1018H, 0x00000160U);
        WR1_PROG(REG_1020H, 0x000002c8U);
        WR1_PROG(REG_1004H, 0x04040009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x14800000U);
        WR1_PROG(REG_1400H, 0x00c000f1U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000390U);
        WR1_PROG(REG_1018H, 0x00000160U);
        WR1_PROG(REG_1020H, 0x00000980U);
        WR1_PROG(REG_1004H, 0x04040009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000390U);
        WR1_PROG(REG_1018H, 0x00000980U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000548U);
        WR1_PROG(REG_1004H, 0x04040002U);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x15500000U);
        WR1_PROG(REG_1400H, 0x00c00015U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
        WR1_PROG(REG_1400H, 0x00c2000dU);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1400H, 0x00020005U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000548U);
        WR1_PROG(REG_1018H, 0x00000570U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000980U);
        WR1_PROG(REG_1004H, 0x04040002U);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000200U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000520U);
        WR1_PROG(REG_1004H, 0x04040004U);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000228U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000548U);
        WR1_PROG(REG_1004H, 0x04040004U);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x11600000U);
        WR1_PROG(REG_1400H, 0x00c000f1U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000520U);
        WR1_PROG(REG_1018H, 0x00000980U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x000001f0U);
        WR1_PROG(REG_1004H, 0x04040002U);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000548U);
        WR1_PROG(REG_1018H, 0x00000980U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000220U);
        WR1_PROG(REG_1004H, 0x04040002U);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000980U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000250U);
        WR1_PROG(REG_1004H, 0x04040004U);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x12500000U);
        WR1_PROG(REG_1400H, 0x00c000a1U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1014H, 0x00000890U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000570U);
        WR1_PROG(REG_1004H, 0x04040004U);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000570U);
        WR1_PROG(REG_1018H, 0x00000980U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x000002c0U);
        WR1_PROG(REG_1004H, 0x04040002U);
        WR1_PROG(REG_1000H, 0x00010201U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000070U);
        WR1_PROG(REG_1018H, 0x00000160U);
        WR1_PROG(REG_1020H, 0x000002f0U);
        WR1_PROG(REG_1004H, 0x04040009U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1404H, 0x14100000U);
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
        WR1_PROG(REG_1014H, 0x00000340U);
        WR1_PROG(REG_1018H, 0x00000430U);
        WR1_PROG(REG_1020H, 0x000001b0U);
        WR1_PROG(REG_1004H, 0x0404000aU);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_143CH, 0x00210000U);
        r_rsip_func100(bswap_32big(0x89f61e58U), bswap_32big(0xf2f02ea4U), bswap_32big(0xe2270c46U),
                       bswap_32big(0x523ffdbbU));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1404H, 0x14000000U);
            WR1_PROG(REG_1400H, 0x00c00081U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_1020H, 0x00000450U);
            WR1_PROG(REG_1004H, 0x04040009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x00000420U);
            WR1_PROG(REG_1020H, 0x00000160U);
            WR1_PROG(REG_1004H, 0x04040009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            r_rsip_func101(bswap_32big(0x66783184U), bswap_32big(0x8c7c88c4U), bswap_32big(0xae99d1fdU),
                           bswap_32big(0xc2647073U));
        }
        else
        {
            r_rsip_func100(bswap_32big(0x6cf82e08U), bswap_32big(0xc16bd956U), bswap_32big(0xb3c56abeU),
                           bswap_32big(0xf49e91f1U));
            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x00000340U);
            WR1_PROG(REG_101CH, 0x000002f0U);
            WR1_PROG(REG_1020H, 0x00000480U);
            WR1_PROG(REG_1004H, 0x05050015U);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_143CH, 0x00000d00U);
            WR1_PROG(REG_1404H, 0x11e00000U);
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
            WR1_PROG(REG_1014H, 0x00000480U);
            WR1_PROG(REG_1018H, 0x00000200U);
            WR1_PROG(REG_1020H, 0x000001b0U);
            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_143CH, 0x00210000U);
            r_rsip_func101(bswap_32big(0xdaf30074U), bswap_32big(0x532785a8U), bswap_32big(0xcd923d9bU),
                           bswap_32big(0x3e706ba5U));
        }

        r_rsip_func100(bswap_32big(0x744dd913U), bswap_32big(0x38b0ab10U), bswap_32big(0x276e666fU),
                       bswap_32big(0xe3bb31e1U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x7b0f00e1U), bswap_32big(0x96b13837U), bswap_32big(0xb2a12fcaU),
                           bswap_32big(0x3a6615a3U));
        }
        else
        {
            WR1_PROG(REG_1404H, 0x11e00000U);
            WR1_PROG(REG_1400H, 0x00c00021U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000200U);
            WR1_PROG(REG_1020H, 0x00000340U);
            WR1_PROG(REG_1004H, 0x04040009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1404H, 0x10f00000U);
            WR1_PROG(REG_1608H, 0x81880001U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1400H, 0x00c90021U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000390U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000200U);
            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010201U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1404H, 0x10f00000U);
            WR1_PROG(REG_1600H, 0x000037e1U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x0000a7e0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00000020U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x8188001fU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1400H, 0x00c90021U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000390U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000228U);
            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010201U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000200U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000520U);
            WR1_PROG(REG_1004H, 0x04040004U);
            WR1_PROG(REG_1000H, 0x00010201U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000228U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000548U);
            WR1_PROG(REG_1004H, 0x04040004U);
            WR1_PROG(REG_1000H, 0x00010201U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1404H, 0x11600000U);
            WR1_PROG(REG_1400H, 0x00c000f1U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1014H, 0x00000520U);
            WR1_PROG(REG_1018H, 0x00000980U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x000001f0U);
            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010201U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000548U);
            WR1_PROG(REG_1018H, 0x00000980U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000220U);
            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010201U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000980U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000250U);
            WR1_PROG(REG_1004H, 0x04040004U);
            WR1_PROG(REG_1000H, 0x00010201U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1404H, 0x15500000U);
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
            WR1_PROG(REG_1014H, 0x00000340U);
            WR1_PROG(REG_1018H, 0x00000570U);
            WR1_PROG(REG_1020H, 0x000001b0U);
            WR1_PROG(REG_1004H, 0x0404000aU);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_143CH, 0x00210000U);
            r_rsip_func100(bswap_32big(0x0943897dU), bswap_32big(0x26628311U), bswap_32big(0xd5dde870U),
                           bswap_32big(0xda81d8a8U));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                WR1_PROG(REG_1404H, 0x14f00000U);
                WR1_PROG(REG_1400H, 0x00c00081U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_1018H, 0x00000510U);
                WR1_PROG(REG_1020H, 0x00000540U);
                WR1_PROG(REG_1004H, 0x04040009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                r_rsip_func101(bswap_32big(0xc29f1803U),
                               bswap_32big(0x82af0ad0U),
                               bswap_32big(0xac097be3U),
                               bswap_32big(0x0511c4b9U));
            }
            else
            {
                r_rsip_func100(bswap_32big(0x73b5e1dcU),
                               bswap_32big(0xa438e62dU),
                               bswap_32big(0x9e7ef657U),
                               bswap_32big(0x0dadaec4U));
                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_1018H, 0x00000340U);
                WR1_PROG(REG_101CH, 0x000002f0U);
                WR1_PROG(REG_1020H, 0x00000570U);
                WR1_PROG(REG_1004H, 0x05050015U);
                WR1_PROG(REG_1408H, 0x00020000U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_143CH, 0x00000d00U);
                WR1_PROG(REG_1404H, 0x11e00000U);
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
                WR1_PROG(REG_1014H, 0x00000570U);
                WR1_PROG(REG_1018H, 0x00000200U);
                WR1_PROG(REG_1020H, 0x000001b0U);
                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_143CH, 0x00210000U);
                r_rsip_func101(bswap_32big(0x52a899ffU),
                               bswap_32big(0x7a9874bcU),
                               bswap_32big(0x14b168dbU),
                               bswap_32big(0x49ddc7ffU));
            }

            r_rsip_func100(bswap_32big(0xe6ee5540U), bswap_32big(0x5ca6b3b8U), bswap_32big(0x4cf87d6aU),
                           bswap_32big(0xd817f4dcU));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                WR1_PROG(REG_1600H, 0x00000800U);
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xa64e6d4cU),
                               bswap_32big(0x1f9b8f1cU),
                               bswap_32big(0x53a21c52U),
                               bswap_32big(0x04271fbaU));
            }
            else
            {
                WR1_PROG(REG_1404H, 0x11e00000U);
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
                WR1_PROG(REG_1014H, 0x00000420U);
                WR1_PROG(REG_1018H, 0x00000200U);
                WR1_PROG(REG_1020H, 0x00000110U);
                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_143CH, 0x00a10000U);
                WR1_PROG(REG_1014H, 0x00000450U);
                WR1_PROG(REG_1018H, 0x00000160U);
                WR1_PROG(REG_1020H, 0x00000110U);
                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_143CH, 0x00210000U);
                WR1_PROG(REG_1014H, 0x00000160U);
                WR1_PROG(REG_1018H, 0x00000450U);
                WR1_PROG(REG_1020H, 0x00000110U);
                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_143CH, 0x00210000U);
                WR1_PROG(REG_1014H, 0x00000480U);
                WR1_PROG(REG_1018H, 0x00000200U);
                WR1_PROG(REG_1020H, 0x00000110U);
                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_143CH, 0x00a10000U);
                r_rsip_func100(bswap_32big(0xa4f000beU),
                               bswap_32big(0x407a6325U),
                               bswap_32big(0x9c40b804U),
                               bswap_32big(0xa6bb3649U));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    WR1_PROG(REG_1014H, 0x00000510U);
                    WR1_PROG(REG_1018H, 0x00000200U);
                    WR1_PROG(REG_1020H, 0x00000110U);
                    WR1_PROG(REG_1004H, 0x0404000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_143CH, 0x00a10000U);
                    WR1_PROG(REG_1014H, 0x00000540U);
                    WR1_PROG(REG_1018H, 0x00000250U);
                    WR1_PROG(REG_1020H, 0x00000110U);
                    WR1_PROG(REG_1004H, 0x0404000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_143CH, 0x00210000U);
                    WR1_PROG(REG_1014H, 0x00000250U);
                    WR1_PROG(REG_1018H, 0x00000540U);
                    WR1_PROG(REG_1020H, 0x00000110U);
                    WR1_PROG(REG_1004H, 0x0404000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_143CH, 0x00210000U);
                    WR1_PROG(REG_1014H, 0x00000570U);
                    WR1_PROG(REG_1018H, 0x00000200U);
                    WR1_PROG(REG_1020H, 0x00000110U);
                    WR1_PROG(REG_1004H, 0x0404000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_143CH, 0x00a10000U);
                    r_rsip_func100(bswap_32big(0xc14d174dU),
                                   bswap_32big(0xe143ff36U),
                                   bswap_32big(0x9b53e22aU),
                                   bswap_32big(0xbc58bfbdU));
                    WR1_PROG(REG_143CH, 0x00400000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    if (CHCK_STS(REG_143CH, 22U, 1U))
                    {
                        WR1_PROG(REG_1014H, 0x00000480U);
                        WR1_PROG(REG_1018H, 0x00000570U);
                        WR1_PROG(REG_101CH, 0x00000070U);
                        WR1_PROG(REG_1020H, 0x00000250U);
                        WR1_PROG(REG_1004H, 0x05050013U);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0U, 0U);
                        WR1_PROG(REG_143CH, 0x00000d00U);
                        r_rsip_func101(bswap_32big(0xdcad5e66U),
                                       bswap_32big(0x71ad646cU),
                                       bswap_32big(0x5e81fca4U),
                                       bswap_32big(0x4c7a16dcU));
                    }
                    else
                    {
                        WR1_PROG(REG_1404H, 0x11400000U);
                        WR1_PROG(REG_1400H, 0x00c00021U);
                        WAIT_STS(REG_1404H, 30U, 0U);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1014H, 0x00000420U);
                        WR1_PROG(REG_1018H, 0x00000160U);
                        WR1_PROG(REG_1020H, 0x000001f0U);
                        WR1_PROG(REG_1004H, 0x04040009U);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0U, 0U);
                        WR1_PROG(REG_1014H, 0x00000450U);
                        WR1_PROG(REG_1018H, 0x00000160U);
                        WR1_PROG(REG_1020H, 0x00000220U);
                        WR1_PROG(REG_1004H, 0x04040009U);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0U, 0U);
                        WR1_PROG(REG_1014H, 0x00000480U);
                        WR1_PROG(REG_1018H, 0x00000160U);
                        WR1_PROG(REG_1020H, 0x00000250U);
                        WR1_PROG(REG_1004H, 0x04040009U);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0U, 0U);
                        r_rsip_func101(bswap_32big(0x44d82737U),
                                       bswap_32big(0xb2dd7bd1U),
                                       bswap_32big(0xe5648765U),
                                       bswap_32big(0xd7cf98d6U));
                    }

                    r_rsip_func101(bswap_32big(0xc319eabdU),
                                   bswap_32big(0x1539b348U),
                                   bswap_32big(0x45fe2454U),
                                   bswap_32big(0xa651c0baU));
                }
                else
                {
                    WR1_PROG(REG_1404H, 0x11400000U);
                    WR1_PROG(REG_1400H, 0x00c00021U);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1014H, 0x00000510U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    WR1_PROG(REG_1020H, 0x000001f0U);
                    WR1_PROG(REG_1004H, 0x04040009U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_1014H, 0x00000540U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    WR1_PROG(REG_1020H, 0x00000220U);
                    WR1_PROG(REG_1004H, 0x04040009U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_1014H, 0x00000570U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    WR1_PROG(REG_1020H, 0x00000250U);
                    WR1_PROG(REG_1004H, 0x04040009U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    r_rsip_func101(bswap_32big(0xb6cac786U),
                                   bswap_32big(0x65547b91U),
                                   bswap_32big(0x0671181cU),
                                   bswap_32big(0xbfeba71dU));
                }

                WR1_PROG(REG_1014H, 0x000001f0U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x00000110U);
                WR1_PROG(REG_1004H, 0x05050004U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1014H, 0x00000220U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x00000160U);
                WR1_PROG(REG_1004H, 0x05050004U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x000002a0U);
                WR1_PROG(REG_1004H, 0x05050004U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1404H, 0x11600000U);
                WR1_PROG(REG_1400H, 0x00c000f1U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1014H, 0x00000110U);
                WR1_PROG(REG_1018H, 0x00000390U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x00000200U);
                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010201U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1014H, 0x00000160U);
                WR1_PROG(REG_1018H, 0x00000390U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x00000228U);
                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010201U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1014H, 0x000002a0U);
                WR1_PROG(REG_1018H, 0x00000390U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x00000250U);
                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010201U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1404H, 0x12800000U);
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
                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_1018H, 0x000002a0U);
                WR1_PROG(REG_1020H, 0x000002f0U);
                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_143CH, 0x00210000U);
                r_rsip_func100(bswap_32big(0xdba1ce12U),
                               bswap_32big(0x1b628e9dU),
                               bswap_32big(0xe81c54b1U),
                               bswap_32big(0x548a7810U));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    WR1_PROG(REG_1600H, 0x00000800U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0xf5dc8ac0U),
                                   bswap_32big(0x5674baa6U),
                                   bswap_32big(0x1c6ce695U),
                                   bswap_32big(0xac0893c6U));
                }
                else
                {
                    r_rsip_func100(bswap_32big(0x2c2f60c2U),
                                   bswap_32big(0xbd6bcdefU),
                                   bswap_32big(0xb5ea029eU),
                                   bswap_32big(0x94fdfb24U));
                    WR1_PROG(REG_1014H, 0x00000250U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x000002a0U);
                    WR1_PROG(REG_1004H, 0x04040004U);
                    WR1_PROG(REG_1000H, 0x00010201U);
                    WAIT_STS(REG_1000H, 0U, 0U);
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
                    WR1_PROG(REG_1014H, 0x00000070U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    WR1_PROG(REG_1020H, 0x00000110U);
                    WR1_PROG(REG_1004H, 0x0404000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_1014H, 0x000002a0U);
                    WR1_PROG(REG_1018H, 0x00000110U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x00000160U);
                    WR1_PROG(REG_1004H, 0x0404000fU);
                    WR1_PROG(REG_1408H, 0x00020000U);
                    WR1_PROG(REG_1000H, 0x00010201U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_143CH, 0x00000d00U);
                    WR1_PROG(REG_1014H, 0x00000200U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x000002a0U);
                    WR1_PROG(REG_1004H, 0x04040002U);
                    WR1_PROG(REG_1000H, 0x00010201U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_1014H, 0x000002a0U);
                    WR1_PROG(REG_1018H, 0x00000930U);
                    WR1_PROG(REG_1020H, 0x000001b0U);
                    WR1_PROG(REG_1004H, 0x0404000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_143CH, 0x00210000U);
                    WR1_PROG(REG_1014H, 0x00000930U);
                    WR1_PROG(REG_1018H, 0x000002a0U);
                    WR1_PROG(REG_1020H, 0x000001b0U);
                    WR1_PROG(REG_1004H, 0x0404000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_143CH, 0x00210000U);
                    r_rsip_func100(bswap_32big(0x69d4adfdU),
                                   bswap_32big(0x0cc2bb6cU),
                                   bswap_32big(0x2f92fe29U),
                                   bswap_32big(0x3bfd4abeU));
                    WR1_PROG(REG_143CH, 0x00400000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    if (CHCK_STS(REG_143CH, 22U, 1U))
                    {
                        WR1_PROG(REG_1600H, 0x00000800U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        r_rsip_func101(bswap_32big(0xd61f4139U),
                                       bswap_32big(0x09329ee4U),
                                       bswap_32big(0x70eee500U),
                                       bswap_32big(0x32d0f33dU));
                    }
                    else
                    {
                        WR1_PROG(REG_1600H, 0x0000b400U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x9ba0d38fU);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        r_rsip_func101(bswap_32big(0xe3afc75dU),
                                       bswap_32big(0xb3f66d37U),
                                       bswap_32big(0x7c0cda97U),
                                       bswap_32big(0x97c8c1d2U));
                    }
                }
            }
        }
    }

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x9ba0d38fU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);
    WR1_PROG(REG_1600H, 0x000037bbU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
