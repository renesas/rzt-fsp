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

void r_rsip_func088 (void)
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
    r_rsip_func100(bswap_32big(0xbaef43edU),
                   bswap_32big(0x79906bf5U),
                   bswap_32big(0x11cbc2a9U),
                   bswap_32big(0xc7822b16U));
    WR1_PROG(REG_1404H, 0x11400000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
    r_rsip_subfunc003(0x00c0001dU);
    r_rsip_subfunc003(0x00c20005U);
    r_rsip_subfunc003(0x0002000dU);
    r_rsip_subfunc001(0x000000c0U, 0x00000160U, 0x00000430U, 0x0404000aU);
    r_rsip_subfunc006(0x00000020U, 0x00000430U, 0x04040010U);
    WR1_PROG(REG_1404H, 0x10c00000U);
    r_rsip_subfunc003(0x00c00051U);
    r_rsip_func103();
    r_rsip_func100(bswap_32big(0x3f28911eU),
                   bswap_32big(0xdb602c42U),
                   bswap_32big(0x35e0b25dU),
                   bswap_32big(0xa3665db8U));
    WR1_PROG(REG_1404H, 0x10f00000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    r_rsip_subfunc003(0x00c20011U);
    r_rsip_func103();
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x0c200104U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    r_rsip_subfunc003(0x00c20011U);
    WR1_PROG(REG_1014H, 0x00000110U);
    WR1_PROG(REG_101CH, 0x00000430U);
    WR1_PROG(REG_1020H, 0x00000480U);
    WR1_PROG(REG_1010H, 0x00000020U);
    WR1_PROG(REG_1004H, 0x04040004U);
    WR1_PROG(REG_1000H, 0x00010201U);
    WAIT_STS(REG_1000H, 0U, 0U);
    WR1_PROG(REG_1404H, 0x14380000U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
    r_rsip_subfunc003(0x00c0001dU);
    r_rsip_subfunc003(0x00c20005U);
    r_rsip_subfunc003(0x0002000dU);
    r_rsip_subfunc001(0x00000480U, 0x00000458U, 0x00000160U, 0x04040009U);
    r_rsip_subfunc006(0x00000020U, 0x000000c0U, 0x04040010U);
    WR1_PROG(REG_1014H, 0x00000340U);
    WR1_PROG(REG_1018H, 0x00000160U);
    r_rsip_subfunc002(0x000000c0U, 0x00000110U, 0x04040005U);
    WR1_PROG(REG_1014H, 0x00000390U);
    WR1_PROG(REG_101CH, 0x00000070U);
    WR1_PROG(REG_1020H, 0x00000250U);
    WR1_PROG(REG_1010H, 0x00000018U);
    WR1_PROG(REG_1004H, 0x04040004U);
    WR1_PROG(REG_1000H, 0x00010201U);
    WAIT_STS(REG_1000H, 0U, 0U);
    WR1_PROG(REG_1404H, 0x14100000U);
    r_rsip_subfunc003(0x00c00021U);
    r_rsip_subfunc001(0x00000890U, 0x00000430U, 0x000002c8U, 0x04040009U);
    WR1_PROG(REG_1404H, 0x14800000U);
    r_rsip_subfunc003(0x00c000f1U);
    r_rsip_subfunc001(0x00000390U, 0x00000430U, 0x00000980U, 0x04040009U);
    WR1_PROG(REG_1014H, 0x00000390U);
    WR1_PROG(REG_1018H, 0x00000980U);
    WR1_PROG(REG_101CH, 0x00000070U);
    WR1_PROG(REG_1020H, 0x00000548U);
    WR1_PROG(REG_1004H, 0x04040002U);
    WR1_PROG(REG_1000H, 0x00010201U);
    WAIT_STS(REG_1000H, 0U, 0U);
    WR1_PROG(REG_1404H, 0x15500000U);
    r_rsip_subfunc003(0x00c00015U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000104U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
    r_rsip_subfunc003(0x00c2000dU);
    r_rsip_subfunc003(0x00020005U);
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
    r_rsip_subfunc003(0x00c000f1U);
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
    r_rsip_subfunc003(0x00c000a1U);
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
    r_rsip_subfunc001(0x00000070U, 0x00000430U, 0x000002f0U, 0x04040009U);
    r_rsip_subfunc001(0x00000110U, 0x00000458U, 0x00000480U, 0x0404000aU);
    WR1_PROG(REG_143CH, 0x00210000U);
    r_rsip_func100(bswap_32big(0x9b9a3683U),
                   bswap_32big(0x45afa93dU),
                   bswap_32big(0xe6a612e3U),
                   bswap_32big(0xef3b3b50U));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        WR1_PROG(REG_1404H, 0x14000000U);
        r_rsip_subfunc003(0x00c00081U);
        r_rsip_subfunc001(0x00000250U, 0x00000420U, 0x00000450U, 0x04040009U);
        r_rsip_func101(bswap_32big(0x575cb0d6U), bswap_32big(0x88b4248aU), bswap_32big(0x2fc4762fU),
                       bswap_32big(0x60a4e277U));
    }
    else
    {
        r_rsip_func100(bswap_32big(0x9986ce95U), bswap_32big(0x9b1ea03fU), bswap_32big(0x61fad319U),
                       bswap_32big(0xfa747609U));
        r_rsip_subfunc005(0x00000250U, 0x00000110U, 0x000002f0U, 0x00000480U, 0x05050015U, 0x00020000U);
        WR1_PROG(REG_143CH, 0x00000d00U);
        WR1_PROG(REG_1404H, 0x10f00000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
        r_rsip_subfunc003(0x00c0001dU);
        r_rsip_subfunc003(0x00c20005U);
        r_rsip_subfunc003(0x0002000dU);
        r_rsip_subfunc001(0x00000480U, 0x00000110U, 0x00000520U, 0x0404000aU);
        WR1_PROG(REG_143CH, 0x00210000U);
        r_rsip_func101(bswap_32big(0x220c8279U), bswap_32big(0x9eea64c4U), bswap_32big(0x0fe45144U),
                       bswap_32big(0x6d7dcfafU));
    }

    r_rsip_func100(bswap_32big(0x4cb54f9eU),
                   bswap_32big(0x28fefa68U),
                   bswap_32big(0xdd5d9b84U),
                   bswap_32big(0xbe902ef3U));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        WR1_PROG(REG_1600H, 0x00000800U);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func101(bswap_32big(0x808ae565U), bswap_32big(0xff6ae3baU), bswap_32big(0x304b0e44U),
                       bswap_32big(0xe7f346afU));
    }
    else
    {
        r_rsip_func100(bswap_32big(0x3d6f8852U), bswap_32big(0xb58dac5fU), bswap_32big(0xf9d5c52cU),
                       bswap_32big(0x192495d4U));
        r_rsip_subfunc005(0x00000250U, 0x00000160U, 0x000002f0U, 0x00000570U, 0x05050015U, 0x00020000U);
        WR1_PROG(REG_143CH, 0x00000d00U);
        WR1_PROG(REG_1404H, 0x10f00000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000104U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
        r_rsip_subfunc003(0x00c0001dU);
        r_rsip_subfunc003(0x00c20005U);
        r_rsip_subfunc003(0x0002000dU);
        r_rsip_subfunc001(0x00000570U, 0x00000110U, 0x000001b0U, 0x0404000aU);
        WR1_PROG(REG_143CH, 0x00210000U);
        r_rsip_func100(bswap_32big(0xae1de4d2U), bswap_32big(0xe13bd6d3U), bswap_32big(0xc7228d22U),
                       bswap_32big(0xfc546538U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0xd6570058U), bswap_32big(0xe1d02e94U), bswap_32big(0x387106a5U),
                           bswap_32big(0xaa4952c4U));
        }
        else
        {
            r_rsip_func100(bswap_32big(0x86ffd038U), bswap_32big(0xcb577c14U), bswap_32big(0xe8b9cdaeU),
                           bswap_32big(0xcaa9ae6fU));
            WR1_PROG(REG_1014H, 0x00000570U);
            r_rsip_subfunc002(0x00000070U, 0x00000250U, 0x05050004U);
            WR1_PROG(REG_1404H, 0x11400000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
            r_rsip_subfunc003(0x00c0001dU);
            r_rsip_subfunc003(0x00c20005U);
            r_rsip_subfunc003(0x0002000dU);
            r_rsip_subfunc001(0x00000070U, 0x00000160U, 0x00000110U, 0x0404000aU);
            WR1_PROG(REG_1014H, 0x00000250U);
            WR1_PROG(REG_1018H, 0x00000110U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000160U);
            WR1_PROG(REG_1004H, 0x0404000fU);
            WR1_PROG(REG_1408H, 0x00020000U);
            WR1_PROG(REG_1000H, 0x00010201U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_143CH, 0x00000d00U);
            WR1_PROG(REG_1014H, 0x00000510U);
            WR1_PROG(REG_1018H, 0x00000160U);
            r_rsip_subfunc002(0x00000070U, 0x000001b0U, 0x05050002U);
            WR1_PROG(REG_1014H, 0x00000540U);
            WR1_PROG(REG_1018H, 0x00000160U);
            r_rsip_subfunc002(0x00000070U, 0x00000200U, 0x05050002U);
            r_rsip_subfunc001(0x00000070U, 0x00000200U, 0x00000110U, 0x0404000aU);
            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000980U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000540U);
            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010201U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x000001b0U);
            WR1_PROG(REG_1018H, 0x00000980U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000510U);
            WR1_PROG(REG_1004H, 0x04040002U);
            WR1_PROG(REG_1000H, 0x00010201U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1014H, 0x00000980U);
            WR1_PROG(REG_101CH, 0x00000070U);
            WR1_PROG(REG_1020H, 0x00000570U);
            WR1_PROG(REG_1004H, 0x04040004U);
            WR1_PROG(REG_1000H, 0x00010201U);
            WAIT_STS(REG_1000H, 0U, 0U);
            WR1_PROG(REG_1404H, 0x11400000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
            r_rsip_subfunc003(0x00c0001dU);
            r_rsip_subfunc003(0x00c20005U);
            r_rsip_subfunc003(0x0002000dU);
            r_rsip_subfunc001(0x00000420U, 0x00000160U, 0x00000110U, 0x0404000aU);
            WR1_PROG(REG_143CH, 0x00a10000U);
            r_rsip_subfunc001(0x00000450U, 0x00000570U, 0x00000110U, 0x0404000aU);
            WR1_PROG(REG_143CH, 0x00210000U);
            r_rsip_subfunc001(0x00000570U, 0x00000450U, 0x00000110U, 0x0404000aU);
            WR1_PROG(REG_143CH, 0x00210000U);
            r_rsip_subfunc001(0x00000480U, 0x00000160U, 0x00000110U, 0x0404000aU);
            WR1_PROG(REG_143CH, 0x00a10000U);
            r_rsip_func100(bswap_32big(0x1c20becfU), bswap_32big(0xc3314a44U), bswap_32big(0x6bddac5dU),
                           bswap_32big(0xd4291cebU));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                WR1_PROG(REG_1014H, 0x00000480U);
                WR1_PROG(REG_1018H, 0x00000570U);
                r_rsip_subfunc002(0x00000070U, 0x00000250U, 0x05050013U);
                WR1_PROG(REG_143CH, 0x00000d00U);
                r_rsip_func101(bswap_32big(0x286226c7U),
                               bswap_32big(0xc6db5df9U),
                               bswap_32big(0x4e5b16a7U),
                               bswap_32big(0xa12a9020U));
            }
            else
            {
                WR1_PROG(REG_1404H, 0x11400000U);
                r_rsip_subfunc003(0x00c00021U);
                r_rsip_subfunc001(0x00000510U, 0x00000160U, 0x000001f0U, 0x04040009U);
                r_rsip_subfunc001(0x00000540U, 0x00000160U, 0x00000220U, 0x04040009U);
                r_rsip_subfunc001(0x00000570U, 0x00000160U, 0x00000250U, 0x04040009U);
                r_rsip_func101(bswap_32big(0x80363bc4U),
                               bswap_32big(0x741077f8U),
                               bswap_32big(0x33d031e1U),
                               bswap_32big(0x00a9813bU));
            }

            WR1_PROG(REG_1014H, 0x000001f0U);
            r_rsip_subfunc002(0x00000070U, 0x00000110U, 0x05050004U);
            WR1_PROG(REG_1014H, 0x00000220U);
            r_rsip_subfunc002(0x00000070U, 0x00000160U, 0x05050004U);
            WR1_PROG(REG_1014H, 0x00000250U);
            r_rsip_subfunc002(0x00000070U, 0x000002a0U, 0x05050004U);
            WR1_PROG(REG_1404H, 0x11600000U);
            r_rsip_subfunc003(0x00c000f1U);
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
            WR1_PROG(REG_1404H, 0x12d00000U);
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x08000104U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
            r_rsip_subfunc003(0x00c0001dU);
            r_rsip_subfunc003(0x00c20005U);
            r_rsip_subfunc003(0x0002000dU);
            r_rsip_subfunc001(0x00000250U, 0x000002f0U, 0x000002a0U, 0x0404000aU);
            WR1_PROG(REG_143CH, 0x00210000U);
            r_rsip_func100(bswap_32big(0x677836b5U), bswap_32big(0x823f2784U), bswap_32big(0x92bcc33eU),
                           bswap_32big(0x61f2b47eU));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                WR1_PROG(REG_1600H, 0x00000800U);
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x3c093fb4U),
                               bswap_32big(0x359a07b4U),
                               bswap_32big(0x003d7fdeU),
                               bswap_32big(0xea3e295eU));
            }
            else
            {
                r_rsip_func100(bswap_32big(0x02cfe638U),
                               bswap_32big(0xfb5038caU),
                               bswap_32big(0x136be235U),
                               bswap_32big(0x33c5325dU));
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
                r_rsip_subfunc003(0x00c0001dU);
                r_rsip_subfunc003(0x00c20005U);
                r_rsip_subfunc003(0x0002000dU);
                r_rsip_subfunc001(0x00000070U, 0x00000160U, 0x00000110U, 0x0404000aU);
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
                WR1_PROG(REG_1014H, 0x00000228U);
                WR1_PROG(REG_1018H, 0x00000160U);
                WR1_PROG(REG_101CH, 0x00000070U);
                WR1_PROG(REG_1020H, 0x000002f0U);
                WR1_PROG(REG_1004H, 0x04040002U);
                WR1_PROG(REG_1000H, 0x00010201U);
                WAIT_STS(REG_1000H, 0U, 0U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x5bbd746cU);
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x24f2bbf2U),
                               bswap_32big(0x7517b1bdU),
                               bswap_32big(0x4c0cac1eU),
                               bswap_32big(0x97b4ae4dU));
            }
        }
    }

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x5bbd746cU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);
    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
