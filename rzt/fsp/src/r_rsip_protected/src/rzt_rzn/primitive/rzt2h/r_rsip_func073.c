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
    OFS_ADR = ARG1;
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x0000f073U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0xe4202b79U),
                   bswap_32big(0xb966fbb2U),
                   bswap_32big(0x906eb86aU),
                   bswap_32big(0xc26b1d1cU));
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
    r_rsip_func100(bswap_32big(0x1d1f0053U),
                   bswap_32big(0x32f3159dU),
                   bswap_32big(0xb3244936U),
                   bswap_32big(0x8a457b1bU));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        WR1_PROG(REG_1600H, 0x00000800U);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func101(bswap_32big(0xde08e011U), bswap_32big(0x9d12da2aU), bswap_32big(0x2efa1d2eU),
                       bswap_32big(0x70023781U));
    }
    else
    {
        r_rsip_func100(bswap_32big(0x67f738bcU), bswap_32big(0x61844eb8U), bswap_32big(0xf35e10b8U),
                       bswap_32big(0x481a8c5cU));
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
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_143CH, 0x00000d00U);
        WR1_PROG(REG_1014H, 0x00000110U);
        WR1_PROG(REG_1018H, 0x00000840U);
        WR1_PROG(REG_101CH, 0x000000c0U);
        WR1_PROG(REG_1020H, 0x00000160U);
        WR1_PROG(REG_1004H, 0x04040002U);
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
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
        WR1_PROG(REG_1000H, 0x00010001U);
        WAIT_STS(REG_1000H, 0U, 0U);
        WR1_PROG(REG_1014H, 0x00000930U);
        WR1_PROG(REG_1018H, 0x00000160U);
        WR1_PROG(REG_101CH, 0x000000c0U);
        WR1_PROG(REG_1020H, 0x00000110U);
        WR1_PROG(REG_1004H, 0x04040002U);
        WR1_PROG(REG_1000H, 0x00010001U);
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
        r_rsip_func101(bswap_32big(0x8143cd44U), bswap_32big(0xc3fee4a5U), bswap_32big(0x50a20b1fU),
                       bswap_32big(0xbcef0d3bU));
        r_rsip_func087(OFS_ADR);
        WR1_PROG(REG_1014H, 0x00000390U);
        WR1_PROG(REG_101CH, 0x00000070U);
        WR1_PROG(REG_1020H, 0x00000250U);
        WR1_PROG(REG_1004H, 0x04040004U);
        WR1_PROG(REG_1000H, 0x00010001U);
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
        r_rsip_func100(bswap_32big(0x633be8f1U), bswap_32big(0xc8ce4a94U), bswap_32big(0x59b6eea0U),
                       bswap_32big(0x9c8deef7U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1404H, 0x14100000U);
            WR1_PROG(REG_1400H, 0x00c00081U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x00000160U);
            WR1_PROG(REG_1020H, 0x00000458U);
            WR1_PROG(REG_1004H, 0x04040009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x00000430U);
            WR1_PROG(REG_1020H, 0x00000160U);
            WR1_PROG(REG_1004H, 0x04040009U);
            WR1_PROG(REG_1000H, 0x00010001U);
            WAIT_STS(REG_1000H, 0U, 0U);
            r_rsip_func101(bswap_32big(0x7c4ca779U), bswap_32big(0xe8f7fac5U), bswap_32big(0x26b4311bU),
                           bswap_32big(0x22aafc8bU));
        }
        else
        {
            r_rsip_func100(bswap_32big(0x8a6f73cfU), bswap_32big(0x877a7bceU), bswap_32big(0x9a41f1b8U),
                           bswap_32big(0x177d5684U));
            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x00000340U);
            WR1_PROG(REG_101CH, 0x000002f0U);
            WR1_PROG(REG_1020H, 0x00000480U);
            WR1_PROG(REG_1004H, 0x04040015U);
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
            r_rsip_func101(bswap_32big(0x9fac00d7U), bswap_32big(0x72cd5299U), bswap_32big(0x55a44b8dU),
                           bswap_32big(0xacaae051U));
        }

        r_rsip_func100(bswap_32big(0xb8f35b1bU), bswap_32big(0xbeb7ea95U), bswap_32big(0xb1339e21U),
                       bswap_32big(0xed768929U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x69cb73b1U), bswap_32big(0xe88bec6aU), bswap_32big(0xb1161decU),
                           bswap_32big(0xede1905fU));
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
            WR1_PROG(REG_1000H, 0x00010001U);
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
            WR1_PROG(REG_1000H, 0x00010001U);
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
            r_rsip_func100(bswap_32big(0xfbfdcf83U), bswap_32big(0xa4df30bcU), bswap_32big(0xc72c20dbU),
                           bswap_32big(0x17ae39f3U));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                WR1_PROG(REG_1404H, 0x15000000U);
                WR1_PROG(REG_1400H, 0x00c00081U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_1018H, 0x00000520U);
                WR1_PROG(REG_1020H, 0x00000548U);
                WR1_PROG(REG_1004H, 0x04040009U);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                r_rsip_func101(bswap_32big(0xffb7fba5U),
                               bswap_32big(0x04c716a5U),
                               bswap_32big(0x2884e3b9U),
                               bswap_32big(0xea227fcaU));
            }
            else
            {
                r_rsip_func100(bswap_32big(0x5e9072feU),
                               bswap_32big(0x750452f7U),
                               bswap_32big(0x6d0c203eU),
                               bswap_32big(0x9f9cf6cdU));
                WR1_PROG(REG_1014H, 0x00000250U);
                WR1_PROG(REG_1018H, 0x00000340U);
                WR1_PROG(REG_101CH, 0x000002f0U);
                WR1_PROG(REG_1020H, 0x00000570U);
                WR1_PROG(REG_1004H, 0x04040015U);
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
                r_rsip_func101(bswap_32big(0x73b8c0bdU),
                               bswap_32big(0x7d658693U),
                               bswap_32big(0xcd4235acU),
                               bswap_32big(0xe194d1efU));
            }

            r_rsip_func100(bswap_32big(0x52570720U), bswap_32big(0xf9ad09c4U), bswap_32big(0xfc576208U),
                           bswap_32big(0xdc05b394U));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                WR1_PROG(REG_1600H, 0x00000800U);
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x7d0cecceU),
                               bswap_32big(0xe10ea022U),
                               bswap_32big(0x5bd9940cU),
                               bswap_32big(0x4e9d9ef3U));
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
                WR1_PROG(REG_1014H, 0x00000430U);
                WR1_PROG(REG_1018H, 0x00000200U);
                WR1_PROG(REG_1020H, 0x00000110U);
                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_143CH, 0x00a10000U);
                WR1_PROG(REG_1014H, 0x00000458U);
                WR1_PROG(REG_1018H, 0x00000160U);
                WR1_PROG(REG_1020H, 0x00000110U);
                WR1_PROG(REG_1004H, 0x0404000aU);
                WR1_PROG(REG_1000H, 0x00010001U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_143CH, 0x00210000U);
                WR1_PROG(REG_1014H, 0x00000160U);
                WR1_PROG(REG_1018H, 0x00000458U);
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
                r_rsip_func100(bswap_32big(0xf81d5e2eU),
                               bswap_32big(0x7fc3608fU),
                               bswap_32big(0x4861f2a6U),
                               bswap_32big(0x01f109acU));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    WR1_PROG(REG_1014H, 0x00000520U);
                    WR1_PROG(REG_1018H, 0x00000200U);
                    WR1_PROG(REG_1020H, 0x00000110U);
                    WR1_PROG(REG_1004H, 0x0404000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_143CH, 0x00a10000U);
                    WR1_PROG(REG_1014H, 0x00000548U);
                    WR1_PROG(REG_1018H, 0x00000250U);
                    WR1_PROG(REG_1020H, 0x00000110U);
                    WR1_PROG(REG_1004H, 0x0404000aU);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_143CH, 0x00210000U);
                    WR1_PROG(REG_1014H, 0x00000250U);
                    WR1_PROG(REG_1018H, 0x00000548U);
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
                    r_rsip_func100(bswap_32big(0x1ca78c81U),
                                   bswap_32big(0x2262def3U),
                                   bswap_32big(0xe64dc439U),
                                   bswap_32big(0x260ac906U));
                    WR1_PROG(REG_143CH, 0x00400000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    if (CHCK_STS(REG_143CH, 22U, 1U))
                    {
                        WR1_PROG(REG_1014H, 0x00000480U);
                        WR1_PROG(REG_1018H, 0x00000570U);
                        WR1_PROG(REG_101CH, 0x00000070U);
                        WR1_PROG(REG_1020H, 0x00000250U);
                        WR1_PROG(REG_1004H, 0x04040013U);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0U, 0U);
                        WR1_PROG(REG_143CH, 0x00000d00U);
                        r_rsip_func101(bswap_32big(0xac67ad69U),
                                       bswap_32big(0x595a0a88U),
                                       bswap_32big(0x38405285U),
                                       bswap_32big(0x436d894cU));
                    }
                    else
                    {
                        WR1_PROG(REG_1404H, 0x11400000U);
                        WR1_PROG(REG_1400H, 0x00c00021U);
                        WAIT_STS(REG_1404H, 30U, 0U);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1014H, 0x00000430U);
                        WR1_PROG(REG_1018H, 0x00000160U);
                        WR1_PROG(REG_1020H, 0x00000200U);
                        WR1_PROG(REG_1004H, 0x04040009U);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0U, 0U);
                        WR1_PROG(REG_1014H, 0x00000458U);
                        WR1_PROG(REG_1018H, 0x00000160U);
                        WR1_PROG(REG_1020H, 0x00000228U);
                        WR1_PROG(REG_1004H, 0x04040009U);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0U, 0U);
                        WR1_PROG(REG_1014H, 0x00000480U);
                        WR1_PROG(REG_1018H, 0x00000160U);
                        WR1_PROG(REG_1020H, 0x00000250U);
                        WR1_PROG(REG_1004H, 0x04040009U);
                        WR1_PROG(REG_1000H, 0x00010001U);
                        WAIT_STS(REG_1000H, 0U, 0U);
                        r_rsip_func101(bswap_32big(0x96611c07U),
                                       bswap_32big(0x2bf46664U),
                                       bswap_32big(0xd31783a6U),
                                       bswap_32big(0x8dc38f42U));
                    }

                    r_rsip_func101(bswap_32big(0xf4d4680eU),
                                   bswap_32big(0xb0e20d94U),
                                   bswap_32big(0xee53303aU),
                                   bswap_32big(0xf359fc20U));
                }
                else
                {
                    WR1_PROG(REG_1404H, 0x11400000U);
                    WR1_PROG(REG_1400H, 0x00c00021U);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1014H, 0x00000520U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    WR1_PROG(REG_1020H, 0x00000200U);
                    WR1_PROG(REG_1004H, 0x04040009U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_1014H, 0x00000548U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    WR1_PROG(REG_1020H, 0x00000228U);
                    WR1_PROG(REG_1004H, 0x04040009U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_1014H, 0x00000570U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    WR1_PROG(REG_1020H, 0x00000250U);
                    WR1_PROG(REG_1004H, 0x04040009U);
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    r_rsip_func101(bswap_32big(0x927818c3U),
                                   bswap_32big(0xd9778e5bU),
                                   bswap_32big(0xf4bfe962U),
                                   bswap_32big(0xde8e069dU));
                }

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
                r_rsip_func100(bswap_32big(0x7c93ae50U),
                               bswap_32big(0x65ede6ceU),
                               bswap_32big(0xe7aa783dU),
                               bswap_32big(0x43170693U));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    WR1_PROG(REG_1600H, 0x00000800U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0xc705573cU),
                                   bswap_32big(0x0ed23e04U),
                                   bswap_32big(0x6c0038e9U),
                                   bswap_32big(0xdf9ee42dU));
                }
                else
                {
                    r_rsip_func100(bswap_32big(0x68f3b108U),
                                   bswap_32big(0xc73073e5U),
                                   bswap_32big(0x70e45f0dU),
                                   bswap_32big(0xdbbc1b07U));
                    WR1_PROG(REG_1014H, 0x00000250U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x000002a0U);
                    WR1_PROG(REG_1004H, 0x04040004U);
                    WR1_PROG(REG_1000H, 0x00010001U);
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
                    WR1_PROG(REG_1000H, 0x00010001U);
                    WAIT_STS(REG_1000H, 0U, 0U);
                    WR1_PROG(REG_143CH, 0x00000d00U);
                    WR1_PROG(REG_1014H, 0x00000200U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    WR1_PROG(REG_101CH, 0x00000070U);
                    WR1_PROG(REG_1020H, 0x000002a0U);
                    WR1_PROG(REG_1004H, 0x04040002U);
                    WR1_PROG(REG_1000H, 0x00010001U);
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
                    r_rsip_func100(bswap_32big(0x20ef39baU),
                                   bswap_32big(0x21e4923aU),
                                   bswap_32big(0x52846aa3U),
                                   bswap_32big(0x89123ea5U));
                    WR1_PROG(REG_143CH, 0x00400000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    if (CHCK_STS(REG_143CH, 22U, 1U))
                    {
                        WR1_PROG(REG_1600H, 0x00000800U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        r_rsip_func101(bswap_32big(0x331bd06fU),
                                       bswap_32big(0x14f36f8bU),
                                       bswap_32big(0xfa059786U),
                                       bswap_32big(0xa51db786U));
                    }
                    else
                    {
                        WR1_PROG(REG_1600H, 0x0000b400U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x9ba0d38fU);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        r_rsip_func101(bswap_32big(0x7d6b3e13U),
                                       bswap_32big(0x98251e1bU),
                                       bswap_32big(0x115b4643U),
                                       bswap_32big(0xb533e688U));
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
