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

rsip_ret_t r_rsip_pe5e (const uint32_t InData_EncMsg[], const uint32_t MAX_CNT2)
{
    uint32_t max_cnt2 = bswap_32big(MAX_CNT2);
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
    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010100U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &max_cnt2);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000d08U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);
    r_rsip_func100(bswap_32big(0x0d10f17bU),
                   bswap_32big(0x989e3cfaU),
                   bswap_32big(0xb501e197U),
                   bswap_32big(0x56c1a62fU));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        WR1_PROG(REG_1444H, 0x000003c7U);
        WR1_PROG(REG_1608H, 0x80040000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncMsg[0]);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncMsg[1]);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncMsg[2]);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncMsg[3]);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e503U));
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func101(bswap_32big(0x96708310U), bswap_32big(0x05669e7bU), bswap_32big(0x5bec45aeU),
                       bswap_32big(0x292cc4ceU));
        r_rsip_func045();
        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x018f1cdcU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e503U));
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func101(bswap_32big(0x82d16bdcU), bswap_32big(0x4c80c2c4U), bswap_32big(0xb2f72894U),
                       bswap_32big(0x1247d3b1U));
        r_rsip_func046();
        WAIT_STS(REG_2030H, 0U, 1U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000044U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000054U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_1824H, 0x08000044U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_1824H, 0x08000054U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        r_rsip_func100(bswap_32big(0xd93ab801U), bswap_32big(0x83df13c8U), bswap_32big(0xc632ba16U),
                       bswap_32big(0x7ac9cfa7U));
        r_rsip_func103();
        r_rsip_func100(bswap_32big(0xab9e5737U), bswap_32big(0x7cf419a5U), bswap_32big(0x2b3e7d2bU),
                       bswap_32big(0xb4d618b7U));
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x0c2000c4U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        WAIT_STS(REG_1A28H, 6U, 0U);
        WR1_PROG(REG_143CH, 0x00000900U);
        WR1_PROG(REG_1600H, 0x0000a900U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000005U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00026908U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000929U);
        WR1_PROG(REG_1458H, 0x00000000U);
        for (iLoop = 0; iLoop < MAX_CNT2 - 8; iLoop = iLoop + 4)
        {
            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xf7008d05U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_EncMsg[iLoop + 4]);
            WR1_ADDR(REG_1420H, &InData_EncMsg[iLoop + 5]);
            WR1_ADDR(REG_1420H, &InData_EncMsg[iLoop + 6]);
            WR1_ADDR(REG_1420H, &InData_EncMsg[iLoop + 7]);
            r_rsip_func100(bswap_32big(0x0022b222U), bswap_32big(0xb44f9facU), bswap_32big(0x259acd25U),
                           bswap_32big(0xe4d99b73U));
            WR1_PROG(REG_1824H, 0xe7040d05U);
            WR1_PROG(REG_1400H, 0x00420011U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1408H, 0x00001012U);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &S_HEAP[iLoop]);
            RD1_ADDR(REG_1420H, &S_HEAP[iLoop + 1]);
            RD1_ADDR(REG_1420H, &S_HEAP[iLoop + 2]);
            RD1_ADDR(REG_1420H, &S_HEAP[iLoop + 3]);
            WR1_PROG(REG_1600H, 0x00002d20U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x40beee20U), bswap_32big(0x70949fabU), bswap_32big(0x33bd9cf3U),
                           bswap_32big(0xfad6a69bU));
        }

        WR1_PROG(REG_1600H, 0x38000909U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func100(bswap_32big(0x6aca649dU), bswap_32big(0xf1334b4dU), bswap_32big(0xd386c963U),
                       bswap_32big(0x073378b3U));
        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_1824H, 0x0c000104U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        WR1_PROG(REG_1824H, 0x09140105U);
        WR1_PROG(REG_1400H, 0x00410011U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1408H, 0x00001012U);
        WAIT_STS(REG_1408H, 30U, 1U);
        RD1_ADDR(REG_1420H, &S_HEAP[iLoop]);
        RD1_ADDR(REG_1420H, &S_HEAP[iLoop + 1]);
        RD1_ADDR(REG_1420H, &S_HEAP[iLoop + 2]);
        RD1_ADDR(REG_1420H, &S_HEAP[iLoop + 3]);
        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncMsg[MAX_CNT2 - 4]);
        WR1_ADDR(REG_1420H, &InData_EncMsg[MAX_CNT2 - 3]);
        WR1_ADDR(REG_1420H, &InData_EncMsg[MAX_CNT2 - 2]);
        WR1_ADDR(REG_1420H, &InData_EncMsg[MAX_CNT2 - 1]);
        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        r_rsip_func100(bswap_32big(0x6b409a91U), bswap_32big(0x42feb428U), bswap_32big(0x18198981U),
                       bswap_32big(0x4a654464U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func101(bswap_32big(0x72296688U), bswap_32big(0x6dcd401aU), bswap_32big(0xa3e875beU),
                           bswap_32big(0x34bc687fU));

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000000a1U);
            WR1_PROG(REG_1824H, 0x08000044U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
            WR1_PROG(REG_1444H, 0x000000a1U);
            WR1_PROG(REG_1824H, 0x08000054U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
            WR1_PROG(REG_1600H, 0x00000929U);
            WR1_PROG(REG_1458H, 0x00000000U);
            for (iLoop = 0; iLoop < MAX_CNT2 - 8; iLoop = iLoop + 4)
            {
                WR1_PROG(REG_1444H, 0x000003c1U);
                WR1_PROG(REG_1824H, 0xf7040d05U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &S_HEAP[iLoop + 0]);
                WR1_ADDR(REG_1420H, &S_HEAP[iLoop + 1]);
                WR1_ADDR(REG_1420H, &S_HEAP[iLoop + 2]);
                WR1_ADDR(REG_1420H, &S_HEAP[iLoop + 3]);
                WR1_PROG(REG_1400H, 0x01410011U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1600H, 0x00002d20U);
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xe31e7295U),
                               bswap_32big(0xf79d38ceU),
                               bswap_32big(0x533e2feeU),
                               bswap_32big(0x075807dcU));
            }

            WR1_PROG(REG_1600H, 0x38000909U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);
            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x07040d05U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &S_HEAP[iLoop + 0]);
            WR1_ADDR(REG_1420H, &S_HEAP[iLoop + 1]);
            WR1_ADDR(REG_1420H, &S_HEAP[iLoop + 2]);
            WR1_ADDR(REG_1420H, &S_HEAP[iLoop + 3]);
            WR1_PROG(REG_1824H, 0x8c100005U);
            WR1_PROG(REG_1400H, 0x00410011U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            r_rsip_func100(bswap_32big(0xd9a02013U), bswap_32big(0xaca428c4U), bswap_32big(0xa72554b6U),
                           bswap_32big(0xe25b19f1U));
            WR1_PROG(REG_1408H, 0x00020000U);
            r_rsip_func101(bswap_32big(0x50febbfcU), bswap_32big(0xce518d15U), bswap_32big(0x8c6e068aU),
                           bswap_32big(0x97166816U));

            return RSIP_RET_PASS;
        }
    }
    else
    {
        r_rsip_func101(bswap_32big(0x7c69e01fU), bswap_32big(0x9dcbda7cU), bswap_32big(0x3b9180cdU),
                       bswap_32big(0xe1336690U));

        return RSIP_RET_PASS;
    }
}
