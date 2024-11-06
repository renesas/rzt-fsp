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

rsip_ret_t r_rsip_p36i (const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[])
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
    if (0x0U != RD1_MASK(REG_14BCH, 0x1fU))
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00360002U);
    WR1_PROG(REG_144CH, 0x00000000U);
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
    WR1_PROG(REG_1420H, bswap_32big(0x00003601U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0xf7ffbecaU),
                   bswap_32big(0x377fb86aU),
                   bswap_32big(0x26b7d7aaU),
                   bswap_32big(0x32db5b4dU));
    r_rsip_func045();
    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x01fd3426U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00003601U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0xfb25460dU),
                   bswap_32big(0xae9c17d2U),
                   bswap_32big(0xcfc23525U),
                   bswap_32big(0x7810de9bU));
    r_rsip_func046();
    r_rsip_func100(bswap_32big(0xb00d4ed9U),
                   bswap_32big(0xe9a4d6aeU),
                   bswap_32big(0xd8113345U),
                   bswap_32big(0xa9608848U));
    WR1_PROG(REG_1444H, 0x000007c2U);
    WR1_PROG(REG_1A2CH, 0x40000100U);
    WR1_PROG(REG_1A24H, 0xf7009d07U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[4]);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[5]);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[6]);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[7]);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[8]);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[9]);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[10]);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[11]);
    WR1_PROG(REG_1824H, 0x08000085U);
    WR1_PROG(REG_1400H, 0x00420011U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WAIT_STS(REG_1828H, 6U, 0U);
    WR1_PROG(REG_143CH, 0x00000500U);
    r_rsip_func100(bswap_32big(0xb1b2fd77U),
                   bswap_32big(0x2f75b77cU),
                   bswap_32big(0x9175dc99U),
                   bswap_32big(0xc46c994fU));
    WR1_PROG(REG_1824H, 0x08000095U);
    WR1_PROG(REG_1400H, 0x00420011U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WAIT_STS(REG_1828H, 6U, 0U);
    WR1_PROG(REG_143CH, 0x00000500U);
    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x07008d05U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[12]);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[13]);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[14]);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[15]);
    WR1_PROG(REG_1A24H, 0x9c100005U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    r_rsip_func100(bswap_32big(0xe901dba2U),
                   bswap_32big(0x8512c560U),
                   bswap_32big(0x91782908U),
                   bswap_32big(0xd5b06bafU));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0x5badca9cU), bswap_32big(0x2718171aU), bswap_32big(0xdf5289d3U),
                       bswap_32big(0x3a0a3643U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12U, 0U);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x80010080U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_IVType[0]);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x38000c84U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        r_rsip_func100(bswap_32big(0xcd90fff2U), bswap_32big(0x4804f922U), bswap_32big(0x0529a2e7U),
                       bswap_32big(0x2c9deb2dU));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1444H, 0x000003c7U);
            WR1_PROG(REG_1608H, 0x80040080U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_IV[0]);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_IV[1]);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_IV[2]);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_IV[3]);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x85ed999bU), bswap_32big(0xa803000cU), bswap_32big(0x5cd0b3edU),
                           bswap_32big(0xe9c1dec3U));
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000003c7U);
            WR1_PROG(REG_1608H, 0x80040000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_IV[0]);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_IV[1]);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_IV[2]);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_IV[3]);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003602U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x837a6eefU), bswap_32big(0x52f15717U), bswap_32big(0xed43dd7fU),
                           bswap_32big(0xd4b3a2f2U));
            r_rsip_func045();
            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x01c27d60U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00003602U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x3f875e9bU), bswap_32big(0xa8b43ca6U), bswap_32big(0x1e45be43U),
                           bswap_32big(0xf352a1dfU));
            r_rsip_func046();
            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xf7009d05U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_IV[4]);
            WR1_ADDR(REG_1420H, &InData_IV[5]);
            WR1_ADDR(REG_1420H, &InData_IV[6]);
            WR1_ADDR(REG_1420H, &InData_IV[7]);
            WR1_PROG(REG_1608H, 0x80040080U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1400H, 0x03420011U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0x07008d05U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_IV[8]);
            WR1_ADDR(REG_1420H, &InData_IV[9]);
            WR1_ADDR(REG_1420H, &InData_IV[10]);
            WR1_ADDR(REG_1420H, &InData_IV[11]);
            WR1_PROG(REG_1A24H, 0x9c100005U);
            WR1_PROG(REG_1400H, 0x00820011U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            r_rsip_func100(bswap_32big(0x309c87f7U), bswap_32big(0xef344a4aU), bswap_32big(0xc8d2a0c6U),
                           bswap_32big(0xd1919175U));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                r_rsip_func102(bswap_32big(0xbb904f39U),
                               bswap_32big(0x4ccb3512U),
                               bswap_32big(0x90cff784U),
                               bswap_32big(0x513f76eeU));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12U, 0U);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func101(bswap_32big(0xb0a3ec02U),
                               bswap_32big(0xbb17a71bU),
                               bswap_32big(0xa1b42c08U),
                               bswap_32big(0x797078bcU));
            }
        }

        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_1824H, 0x08000024U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        WR1_PROG(REG_1444H, 0x000000a1U);
        WR1_PROG(REG_182CH, 0x40070000U);
        WR1_PROG(REG_1824H, 0x0a008004U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        r_rsip_func101(bswap_32big(0x5af4edd9U), bswap_32big(0xb4e18d3dU), bswap_32big(0x5dd0cba0U),
                       bswap_32big(0x2dd12ac9U));

        return RSIP_RET_PASS;
    }
}
