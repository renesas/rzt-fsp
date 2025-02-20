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
    r_rsip_func100(bswap_32big(0xc831a0e7U),
                   bswap_32big(0x51ecf709U),
                   bswap_32big(0x0fcb5776U),
                   bswap_32big(0x81825cd2U));
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
        r_rsip_func101(bswap_32big(0xefb0938cU), bswap_32big(0x784d9e32U), bswap_32big(0xc7c3ff44U),
                       bswap_32big(0x3cd71048U));
        r_rsip_func045();
        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x01799093U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e503U));
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func101(bswap_32big(0x99ed9c8cU), bswap_32big(0x156bf674U), bswap_32big(0x5c3600f2U),
                       bswap_32big(0xd2650d9fU));
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
        r_rsip_func100(bswap_32big(0x9ff0c492U), bswap_32big(0xf024135bU), bswap_32big(0x0e93fcbcU),
                       bswap_32big(0xfee93900U));
        r_rsip_func103();
        r_rsip_func100(bswap_32big(0x42610b89U), bswap_32big(0xc9528481U), bswap_32big(0xec20f1d9U),
                       bswap_32big(0xec55b804U));
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
            r_rsip_func100(bswap_32big(0x91c62f24U), bswap_32big(0x88ac0528U), bswap_32big(0xf42ef48cU),
                           bswap_32big(0x628090f4U));
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
            r_rsip_func101(bswap_32big(0xad497e34U), bswap_32big(0xd8d45e26U), bswap_32big(0xdfafe863U),
                           bswap_32big(0x7af11879U));
        }

        WR1_PROG(REG_1600H, 0x38000909U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func100(bswap_32big(0x933a7167U), bswap_32big(0x7b5f0927U), bswap_32big(0x7ac5f425U),
                       bswap_32big(0xbdec7742U));
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
        r_rsip_func100(bswap_32big(0xcb625d12U), bswap_32big(0xccfda730U), bswap_32big(0x9b15b13aU),
                       bswap_32big(0x943ae7b0U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func101(bswap_32big(0x1b8fc295U), bswap_32big(0x9d4edb2fU), bswap_32big(0x3731bdd8U),
                           bswap_32big(0x8fda23a0U));

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
                r_rsip_func101(bswap_32big(0x5fd16972U),
                               bswap_32big(0x20c85bacU),
                               bswap_32big(0x911bbc91U),
                               bswap_32big(0x6da71685U));
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
            r_rsip_func100(bswap_32big(0x08f28680U), bswap_32big(0x0edd9570U), bswap_32big(0x2e5a89a0U),
                           bswap_32big(0x7c0af93bU));
            WR1_PROG(REG_1408H, 0x00020000U);
            r_rsip_func101(bswap_32big(0x7982acd6U), bswap_32big(0x1b9f3c66U), bswap_32big(0xc62d7b90U),
                           bswap_32big(0xf344e236U));

            return RSIP_RET_PASS;
        }
    }
    else
    {
        r_rsip_func101(bswap_32big(0x5cdccd63U), bswap_32big(0xb1b57957U), bswap_32big(0x5631a120U),
                       bswap_32big(0xea1a7ad8U));

        return RSIP_RET_PASS;
    }
}
