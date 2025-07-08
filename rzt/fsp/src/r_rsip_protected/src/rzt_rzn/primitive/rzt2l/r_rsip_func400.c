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

void r_rsip_func400 (const uint32_t ARG1[])
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
    WR1_PROG(REG_1000H, 0x00010000U);
    WR1_PROG(REG_1024H, 0x000007f0U);
    WR1_PROG(REG_1600H, 0x00000b5aU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000b9cU);
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_subfunc009(bswap_32big(0x000000ffU));
    r_rsip_func101(bswap_32big(0xb17f6cf5U),
                   bswap_32big(0x19fd57efU),
                   bswap_32big(0xddd7043eU),
                   bswap_32big(0x2f0aa0b1U));
    r_rsip_func084();
    r_rsip_subfunc006(0x00000020U, 0x000000c0U, 0x04040010U);
    r_rsip_subfunc006(0x00000018U, 0x00000070U, 0x04040010U);
    WR1_PROG(REG_1404H, 0x19100000U);
    WR1_PROG(REG_1444H, 0x00000fc1U);
    WR1_PROG(REG_182CH, 0x00000300U);
    WR1_PROG(REG_1824H, 0x08008107U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &ARG1[0]);
    WR1_ADDR(REG_1420H, &ARG1[1]);
    WR1_ADDR(REG_1420H, &ARG1[2]);
    WR1_ADDR(REG_1420H, &ARG1[3]);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &ARG1[4]);
    WR1_ADDR(REG_1420H, &ARG1[5]);
    WR1_ADDR(REG_1420H, &ARG1[6]);
    WR1_ADDR(REG_1420H, &ARG1[7]);
    r_rsip_subfunc003(0x00c10021U);
    WR1_PROG(REG_1404H, 0x19600000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &ARG1[8]);
    WR1_ADDR(REG_1420H, &ARG1[9]);
    WR1_ADDR(REG_1420H, &ARG1[10]);
    WR1_ADDR(REG_1420H, &ARG1[11]);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &ARG1[12]);
    WR1_ADDR(REG_1420H, &ARG1[13]);
    WR1_ADDR(REG_1420H, &ARG1[14]);
    WR1_ADDR(REG_1420H, &ARG1[15]);
    r_rsip_subfunc003(0x00c10021U);
    WR1_PROG(REG_1404H, 0x11e00000U);
    WR1_PROG(REG_1444H, 0x000000a1U);
    WR1_PROG(REG_1824H, 0x08000104U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
    r_rsip_subfunc003(0x00c0001dU);
    r_rsip_subfunc003(0x00c10005U);
    r_rsip_subfunc003(0x0001000dU);
    WR1_PROG(REG_1014H, 0x000000c0U);
    WR1_PROG(REG_1018H, 0x00000200U);
    r_rsip_subfunc002(0x000000c0U, 0x00000160U, 0x0404000aU);
    r_rsip_subfunc001(0x00000160U, 0x00000930U, 0x000001b0U, 0x0404000aU);
    WR1_PROG(REG_143CH, 0x00210000U);
    r_rsip_subfunc001(0x00000930U, 0x00000200U, 0x000001b0U, 0x0404000aU);
    WR1_PROG(REG_143CH, 0x00210000U);
    r_rsip_subfunc001(0x00000160U, 0x00000980U, 0x000001b0U, 0x0404000aU);
    WR1_PROG(REG_143CH, 0x00210000U);
    r_rsip_subfunc001(0x00000980U, 0x00000200U, 0x000001b0U, 0x0404000aU);
    WR1_PROG(REG_143CH, 0x00210000U);
    r_rsip_func100(bswap_32big(0xd1587468U),
                   bswap_32big(0x3bd50c53U),
                   bswap_32big(0xf9e5c6afU),
                   bswap_32big(0xfea267efU));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        WR1_PROG(REG_1600H, 0x00000800U);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func101(bswap_32big(0x48da8210U), bswap_32big(0x040d4d86U), bswap_32big(0x2d6f37ffU),
                       bswap_32big(0x218b63adU));
    }
    else
    {
        r_rsip_func100(bswap_32big(0x5366b5deU), bswap_32big(0x09b7e7b7U), bswap_32big(0xfa0bac90U),
                       bswap_32big(0xe492f254U));
        WR1_PROG(REG_1014H, 0x00000160U);
        WR1_PROG(REG_1018H, 0x00000200U);
        r_rsip_subfunc002(0x000000c0U, 0x000001b0U, 0x0404000aU);
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
        r_rsip_subfunc002(0x000000c0U, 0x00000160U, 0x04040002U);
        WR1_PROG(REG_1404H, 0x10f00000U);
        WR1_PROG(REG_1600H, 0x00000bffU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x8188001fU);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_subfunc003(0x00c90021U);
        WR1_PROG(REG_1014H, 0x00000110U);
        WR1_PROG(REG_1018H, 0x00000160U);
        r_rsip_subfunc002(0x000000c0U, 0x00000340U, 0x04040002U);
        WR1_PROG(REG_1014H, 0x00000930U);
        WR1_PROG(REG_1018H, 0x00000160U);
        r_rsip_subfunc002(0x000000c0U, 0x00000110U, 0x04040002U);
        WR1_PROG(REG_1010H, 0x00000018U);
        WR1_PROG(REG_1404H, 0x11600000U);
        r_rsip_subfunc003(0x00c000f1U);
        r_rsip_subfunc009(bswap_32big(0x000000ffU));
        r_rsip_func101(bswap_32big(0x42b4a08eU), bswap_32big(0xba289d10U), bswap_32big(0xc246235eU),
                       bswap_32big(0x50776875U));
        r_rsip_func085();
        WR1_PROG(REG_1014H, 0x00000390U);
        r_rsip_subfunc002(0x00000070U, 0x00000250U, 0x04040004U);
        WR1_PROG(REG_1404H, 0x18700000U);
        WR1_PROG(REG_182CH, 0x00000100U);
        WR1_PROG(REG_1824H, 0x08008107U);
        r_rsip_subfunc003(0x00430021U);
        WR1_PROG(REG_1404H, 0x12a80000U);
        r_rsip_subfunc003(0x00c10021U);
        r_rsip_func100(bswap_32big(0x0765b71fU), bswap_32big(0xc857f072U), bswap_32big(0xb7b6ead6U),
                       bswap_32big(0x1eb3d77bU));
        WR1_PROG(REG_1404H, 0x10500000U);
        WR1_PROG(REG_182CH, 0x00000100U);
        WR1_PROG(REG_1824H, 0x08008107U);
        r_rsip_subfunc003(0x00430021U);
        WR1_PROG(REG_1404H, 0x12d00000U);
        r_rsip_subfunc003(0x00c10021U);
        r_rsip_subfunc005(0x00000250U, 0x00000340U, 0x000002f0U, 0x00000480U, 0x04040015U, 0x00020000U);
        WR1_PROG(REG_143CH, 0x00000d00U);
        WR1_PROG(REG_1404H, 0x11e00000U);
        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_1824H, 0x08000104U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
        r_rsip_subfunc003(0x00c0001dU);
        r_rsip_subfunc003(0x00c10005U);
        r_rsip_subfunc003(0x0001000dU);
        r_rsip_subfunc001(0x00000480U, 0x00000200U, 0x000001b0U, 0x0404000aU);
        WR1_PROG(REG_143CH, 0x00210000U);
        r_rsip_func100(bswap_32big(0x0b9ba8eeU), bswap_32big(0xb87b9128U), bswap_32big(0x96c3139bU),
                       bswap_32big(0x3fcdda40U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x4b1621dfU), bswap_32big(0x696a5bc7U), bswap_32big(0xd309fa4dU),
                           bswap_32big(0xd78b316aU));
        }
        else
        {
            r_rsip_func100(bswap_32big(0x8a1f5c27U), bswap_32big(0x4e8edfacU), bswap_32big(0x07a0532eU),
                           bswap_32big(0x4ab44b69U));
            WR1_PROG(REG_1404H, 0x10f00000U);
            WR1_PROG(REG_182CH, 0x00000100U);
            WR1_PROG(REG_1824H, 0x08008107U);
            r_rsip_subfunc003(0x00430021U);
            WR1_PROG(REG_1404H, 0x13200000U);
            r_rsip_subfunc003(0x00c10021U);
            WR1_PROG(REG_1404H, 0x10f00000U);
            WR1_PROG(REG_1608H, 0x81880001U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_subfunc003(0x00c90021U);
            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000390U);
            r_rsip_subfunc002(0x00000070U, 0x00000200U, 0x04040002U);
            WR1_PROG(REG_1404H, 0x10f00000U);
            WR1_PROG(REG_1600H, 0x000037e1U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x0000a7e0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00000020U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x8188001fU);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_subfunc003(0x00c90021U);
            WR1_PROG(REG_1014H, 0x00000110U);
            WR1_PROG(REG_1018H, 0x00000390U);
            r_rsip_subfunc002(0x00000070U, 0x00000228U, 0x04040002U);
            r_rsip_subfunc005(0x00000250U, 0x00000340U, 0x000002f0U, 0x00000570U, 0x04040015U, 0x00020000U);
            WR1_PROG(REG_143CH, 0x00000d00U);
            WR1_PROG(REG_1404H, 0x11e00000U);
            WR1_PROG(REG_1444H, 0x000000a1U);
            WR1_PROG(REG_1824H, 0x08000104U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
            r_rsip_subfunc003(0x00c0001dU);
            r_rsip_subfunc003(0x00c10005U);
            r_rsip_subfunc003(0x0001000dU);
            r_rsip_subfunc001(0x00000570U, 0x00000200U, 0x000001b0U, 0x0404000aU);
            WR1_PROG(REG_143CH, 0x00210000U);
            r_rsip_func100(bswap_32big(0x3e75fd62U), bswap_32big(0x6eb86471U), bswap_32big(0x359fcc86U),
                           bswap_32big(0xfa1c1a79U));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                WR1_PROG(REG_1600H, 0x00000800U);
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x0b7ba399U),
                               bswap_32big(0xd33f3cc3U),
                               bswap_32big(0x74626a83U),
                               bswap_32big(0xfc3e792aU));
            }
            else
            {
                WR1_PROG(REG_1014H, 0x00000480U);
                WR1_PROG(REG_1018H, 0x00000570U);
                r_rsip_subfunc002(0x00000070U, 0x00000250U, 0x04040013U);
                WR1_PROG(REG_143CH, 0x00000d00U);
                WR1_PROG(REG_1404H, 0x12800000U);
                WR1_PROG(REG_1444H, 0x000000a1U);
                WR1_PROG(REG_1824H, 0x08000104U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00000001U));
                r_rsip_subfunc003(0x00c0001dU);
                r_rsip_subfunc003(0x00c10005U);
                r_rsip_subfunc003(0x0001000dU);
                r_rsip_subfunc001(0x00000480U, 0x000002a0U, 0x000002f0U, 0x0404000aU);
                WR1_PROG(REG_143CH, 0x00210000U);
                r_rsip_func100(bswap_32big(0xddb652d0U),
                               bswap_32big(0x9bc97bbfU),
                               bswap_32big(0x29193fe9U),
                               bswap_32big(0x5852bfe7U));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    WR1_PROG(REG_1600H, 0x00000800U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0x5c854876U),
                                   bswap_32big(0xbe0debffU),
                                   bswap_32big(0x84c62ae1U),
                                   bswap_32big(0xd545ee4aU));
                }
                else
                {
                    r_rsip_func100(bswap_32big(0xf6bb27e5U),
                                   bswap_32big(0x5d35094bU),
                                   bswap_32big(0x6e485de5U),
                                   bswap_32big(0x5fee18f8U));
                    WR1_PROG(REG_1014H, 0x00000250U);
                    r_rsip_subfunc002(0x00000070U, 0x000002a0U, 0x04040004U);
                    WR1_PROG(REG_1404H, 0x11400000U);
                    WR1_PROG(REG_1444H, 0x000000a1U);
                    WR1_PROG(REG_1824H, 0x08000104U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000002U));
                    r_rsip_subfunc003(0x00c0001dU);
                    r_rsip_subfunc003(0x00c10005U);
                    r_rsip_subfunc003(0x0001000dU);
                    WR1_PROG(REG_1014H, 0x00000070U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    r_rsip_subfunc002(0x00000070U, 0x00000110U, 0x0404000aU);
                    r_rsip_subfunc005(0x000002a0U, 0x00000110U, 0x00000070U, 0x00000160U, 0x0404000fU, 0x00020000U);
                    WR1_PROG(REG_143CH, 0x00000d00U);
                    WR1_PROG(REG_1014H, 0x00000200U);
                    WR1_PROG(REG_1018H, 0x00000160U);
                    r_rsip_subfunc002(0x00000070U, 0x000002a0U, 0x04040002U);
                    r_rsip_subfunc001(0x000002a0U, 0x00000930U, 0x000001b0U, 0x0404000aU);
                    WR1_PROG(REG_143CH, 0x00210000U);
                    r_rsip_subfunc001(0x00000930U, 0x000002a0U, 0x000001b0U, 0x0404000aU);
                    WR1_PROG(REG_143CH, 0x00210000U);
                    r_rsip_func100(bswap_32big(0x6d984900U),
                                   bswap_32big(0xc8a360cfU),
                                   bswap_32big(0x663b409fU),
                                   bswap_32big(0x74502826U));
                    WR1_PROG(REG_143CH, 0x00400000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    if (CHCK_STS(REG_143CH, 22U, 1U))
                    {
                        WR1_PROG(REG_1600H, 0x00000800U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        r_rsip_func101(bswap_32big(0xaf2f0497U),
                                       bswap_32big(0x40d05bb9U),
                                       bswap_32big(0xe23859aeU),
                                       bswap_32big(0x1959407eU));
                    }
                    else
                    {
                        WR1_PROG(REG_1600H, 0x0000b400U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x19bac63dU);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        r_rsip_func101(bswap_32big(0xb53de242U),
                                       bswap_32big(0x2e3f2e6eU),
                                       bswap_32big(0xf6c054c7U),
                                       bswap_32big(0xe626a85eU));
                    }
                }
            }
        }
    }

    WR1_PROG(REG_1600H, 0x38008800U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x19bac63dU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);
    WR1_PROG(REG_1600H, 0x00007c1bU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
