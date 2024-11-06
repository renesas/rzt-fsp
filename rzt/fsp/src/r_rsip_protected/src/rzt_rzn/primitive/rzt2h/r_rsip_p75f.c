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

rsip_ret_t r_rsip_p75f (const uint32_t InData_Cmd[],
                        const uint32_t InData_Msg[],
                        const uint32_t InData_MAC[],
                        const uint32_t InData_length[],
                        uint32_t       MAX_CNT,
                        uint32_t       OutData_MAC[])
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
    WAIT_STS(REG_2030H, 0U, 1U);
    WR1_PROG(REG_1444H, 0x00020064U);
    for (iLoop = 0; iLoop < (MAX_CNT & 0xfffffff0U); iLoop = iLoop + 16)
    {
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_Msg[iLoop + 0]);
        WR1_ADDR(REG_1420H, &InData_Msg[iLoop + 1]);
        WR1_ADDR(REG_1420H, &InData_Msg[iLoop + 2]);
        WR1_ADDR(REG_1420H, &InData_Msg[iLoop + 3]);
        WR1_ADDR(REG_1420H, &InData_Msg[iLoop + 4]);
        WR1_ADDR(REG_1420H, &InData_Msg[iLoop + 5]);
        WR1_ADDR(REG_1420H, &InData_Msg[iLoop + 6]);
        WR1_ADDR(REG_1420H, &InData_Msg[iLoop + 7]);
        WR1_ADDR(REG_1420H, &InData_Msg[iLoop + 8]);
        WR1_ADDR(REG_1420H, &InData_Msg[iLoop + 9]);
        WR1_ADDR(REG_1420H, &InData_Msg[iLoop + 10]);
        WR1_ADDR(REG_1420H, &InData_Msg[iLoop + 11]);
        WR1_ADDR(REG_1420H, &InData_Msg[iLoop + 12]);
        WR1_ADDR(REG_1420H, &InData_Msg[iLoop + 13]);
        WR1_ADDR(REG_1420H, &InData_Msg[iLoop + 14]);
        WR1_ADDR(REG_1420H, &InData_Msg[iLoop + 15]);
    }

    WAIT_STS(REG_1444H, 31U, 1U);
    for (iLoop = (MAX_CNT & 0xfffffff0U); iLoop < MAX_CNT; iLoop = iLoop + 1)
    {
        WR1_ADDR(REG_1420H, &InData_Msg[iLoop + 0]);
    }

    WR1_PROG(REG_1444H, 0x00000000U);
    WAIT_STS(REG_2030H, 8U, 0U);
    WR1_PROG(REG_143CH, 0x00001600U);
    WAIT_STS(REG_2030H, 4U, 1U);
    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_Cmd[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000c00U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    r_rsip_func100(bswap_32big(0xebba5a62U),
                   bswap_32big(0xfa4e2c8aU),
                   bswap_32big(0x43ad8842U),
                   bswap_32big(0x78ef31feU));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func100(bswap_32big(0x513bad6eU), bswap_32big(0x410b35f1U), bswap_32big(0xcb3b32eaU),
                       bswap_32big(0x003eea7dU));
        WR1_PROG(REG_1600H, 0x00007c04U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_143CH, 0x00600000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (0x00000000U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            r_rsip_func100(bswap_32big(0xc87c44d8U), bswap_32big(0x97764761U), bswap_32big(0x4cf0b290U),
                           bswap_32big(0x96f29bf9U));
            WR1_PROG(REG_1408H, 0x00004016U);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_MAC[0]);
            RD1_ADDR(REG_1420H, &OutData_MAC[1]);
            RD1_ADDR(REG_1420H, &OutData_MAC[2]);
            RD1_ADDR(REG_1420H, &OutData_MAC[3]);
            RD1_ADDR(REG_1420H, &OutData_MAC[4]);
            r_rsip_func102(bswap_32big(0x66a549d4U), bswap_32big(0xcfdbf9b4U), bswap_32big(0x28f75a4aU),
                           bswap_32big(0x0ffe6c3cU));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);
        }
        else if (0x00000001U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            r_rsip_func100(bswap_32big(0x3575c150U), bswap_32big(0xe2e832b5U), bswap_32big(0x45cd3027U),
                           bswap_32big(0x5116bd1cU));
            WR1_PROG(REG_1408H, 0x0000401eU);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_MAC[0]);
            RD1_ADDR(REG_1420H, &OutData_MAC[1]);
            RD1_ADDR(REG_1420H, &OutData_MAC[2]);
            RD1_ADDR(REG_1420H, &OutData_MAC[3]);
            RD1_ADDR(REG_1420H, &OutData_MAC[4]);
            RD1_ADDR(REG_1420H, &OutData_MAC[5]);
            RD1_ADDR(REG_1420H, &OutData_MAC[6]);
            r_rsip_func102(bswap_32big(0x8d592225U), bswap_32big(0x04e25d71U), bswap_32big(0xd7a3fc7eU),
                           bswap_32big(0xef191a4bU));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);
        }
        else if (0x00000002U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            r_rsip_func100(bswap_32big(0xa7afa05fU), bswap_32big(0x4d3a9117U), bswap_32big(0x9456a53eU),
                           bswap_32big(0x5bc9c6b3U));
            WR1_PROG(REG_1408H, 0x00004022U);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_MAC[0]);
            RD1_ADDR(REG_1420H, &OutData_MAC[1]);
            RD1_ADDR(REG_1420H, &OutData_MAC[2]);
            RD1_ADDR(REG_1420H, &OutData_MAC[3]);
            RD1_ADDR(REG_1420H, &OutData_MAC[4]);
            RD1_ADDR(REG_1420H, &OutData_MAC[5]);
            RD1_ADDR(REG_1420H, &OutData_MAC[6]);
            RD1_ADDR(REG_1420H, &OutData_MAC[7]);
            r_rsip_func102(bswap_32big(0x6f48a01fU), bswap_32big(0x7e71a847U), bswap_32big(0xa787aabfU),
                           bswap_32big(0xbcd3b31dU));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);
        }

        return RSIP_RET_PASS;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x4027b0b3U), bswap_32big(0x86a83eeeU), bswap_32big(0x3bac79a4U),
                       bswap_32big(0xcbc9e199U));
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x80010020U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_length[0]);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000bffU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00007c04U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_143CH, 0x00600000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (0x00000000U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1600H, 0x0000b440U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00000014U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x8085001fU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1400H, 0x03450015U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            r_rsip_func101(bswap_32big(0x409aa3b3U), bswap_32big(0x62e1f874U), bswap_32big(0xc9652747U),
                           bswap_32big(0x5497183aU));
        }
        else if (0x00000001U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1600H, 0x0000b440U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x0000001cU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x8087001fU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1400H, 0x0345001dU);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            r_rsip_func101(bswap_32big(0x68fb9da6U), bswap_32big(0xac7935a0U), bswap_32big(0xcabb0cb3U),
                           bswap_32big(0x3d7dce1bU));
        }
        else if (0x00000002U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1600H, 0x0000b440U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00000020U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x8088001fU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1400H, 0x03450021U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            r_rsip_func101(bswap_32big(0xbdf05c4dU), bswap_32big(0xdb8a139cU), bswap_32big(0xaf569be5U),
                           bswap_32big(0xad968d7bU));
        }

        WR1_PROG(REG_1600H, 0x3420a820U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000004U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_1600H, 0x34202841U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        r_rsip_func100(bswap_32big(0x81cf6321U), bswap_32big(0xb2d82237U), bswap_32big(0x07c93c43U),
                       bswap_32big(0xee35bf65U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func102(bswap_32big(0xb598923cU), bswap_32big(0x5c388e2cU), bswap_32big(0x5aae6f06U),
                           bswap_32big(0xd72bdef5U));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0x09de9785U), bswap_32big(0x67e847ceU), bswap_32big(0x332a7f37U),
                           bswap_32big(0x30ace2b2U));
            WR1_PROG(REG_1600H, 0x00000800U);
            WR1_PROG(REG_1458H, 0x00000000U);
            for (iLoop = 0; iLoop < 32; iLoop = iLoop + 1)
            {
                WR1_PROG(REG_1600H, 0x3c002be1U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x12003c1fU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00002fe0U);
                WR1_PROG(REG_1458H, 0x00000000U);
            }

            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x08000045U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_MAC[0]);
            WR1_ADDR(REG_1420H, &InData_MAC[1]);
            WR1_ADDR(REG_1420H, &InData_MAC[2]);
            WR1_ADDR(REG_1420H, &InData_MAC[3]);
            WR1_PROG(REG_1600H, 0x00007c04U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_143CH, 0x00600000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (0x00000000U == RD1_MASK(REG_1440H, 0xffffffffU))
            {
                WR1_PROG(REG_1444H, 0x000000c1U);
                WR1_PROG(REG_1824H, 0x08000054U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_MAC[4]);
                r_rsip_func101(bswap_32big(0xc897197cU),
                               bswap_32big(0xd2b86454U),
                               bswap_32big(0x7164999fU),
                               bswap_32big(0xd708a90bU));
            }
            else if (0x00000001U == RD1_MASK(REG_1440H, 0xffffffffU))
            {
                WR1_PROG(REG_1444H, 0x000002c1U);
                WR1_PROG(REG_1824H, 0x08000055U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_MAC[4]);
                WR1_ADDR(REG_1420H, &InData_MAC[5]);
                WR1_ADDR(REG_1420H, &InData_MAC[6]);
                WR1_PROG(REG_1444H, 0x000000a1U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
                r_rsip_func101(bswap_32big(0x471e607dU),
                               bswap_32big(0x948607dcU),
                               bswap_32big(0xcc21c2f2U),
                               bswap_32big(0x6122f26eU));
            }
            else if (0x00000002U == RD1_MASK(REG_1440H, 0xffffffffU))
            {
                WR1_PROG(REG_1444H, 0x000003c1U);
                WR1_PROG(REG_1824H, 0x08000055U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_MAC[4]);
                WR1_ADDR(REG_1420H, &InData_MAC[5]);
                WR1_ADDR(REG_1420H, &InData_MAC[6]);
                WR1_ADDR(REG_1420H, &InData_MAC[7]);
                r_rsip_func101(bswap_32big(0xbc5d16d7U),
                               bswap_32big(0xee9e60ccU),
                               bswap_32big(0xf5dc0f67U),
                               bswap_32big(0x0e1ce5bfU));
            }

            WR1_PROG(REG_1824H, 0x9c000005U);
            WR1_PROG(REG_1600H, 0x00000bffU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x8188001fU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1400H, 0x00490011U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1824H, 0x9c100005U);
            WR1_PROG(REG_1400H, 0x00490011U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            r_rsip_func100(bswap_32big(0xcf50caa5U), bswap_32big(0x4baab408U), bswap_32big(0xde88b697U),
                           bswap_32big(0x662eb02bU));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                r_rsip_func102(bswap_32big(0xaf629ee3U),
                               bswap_32big(0x162c1ce2U),
                               bswap_32big(0x458d1587U),
                               bswap_32big(0xfa02c789U));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12U, 0U);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func102(bswap_32big(0xc56bad5cU),
                               bswap_32big(0x0a357bd2U),
                               bswap_32big(0x046f53d9U),
                               bswap_32big(0xa5cd5533U));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12U, 0U);

                return RSIP_RET_PASS;
            }
        }
    }
}
