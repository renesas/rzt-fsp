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

rsip_ret_t r_rsip_p75i (const uint32_t InData_KeyIndex[],
                        const uint32_t InData_HashType[],
                        const uint32_t InData_MsgLen[])
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

    WR1_PROG(REG_1B00H, 0x00750002U);
    WR1_PROG(REG_144CH, 0x00000000U);
    r_rsip_func100(bswap_32big(0xcbf2cf25U),
                   bswap_32big(0x9832c2dbU),
                   bswap_32big(0x8c302a0fU),
                   bswap_32big(0xc6012ec4U));
    WR1_PROG(REG_2000H, 0x00000001U);
    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010080U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x3420a880U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x2000b480U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000002U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00007c04U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_143CH, 0x00600000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (0x00000000U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x010d760aU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_2004H, 0x00000000U);
        r_rsip_func101(bswap_32big(0x6da9b806U), bswap_32big(0xbd89a190U), bswap_32big(0x241ec1f5U),
                       bswap_32big(0x43bb460dU));
    }
    else if (0x00000001U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x01e65c9eU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_2004H, 0x00000040U);
        r_rsip_func101(bswap_32big(0xe72ce292U), bswap_32big(0x36a9c8ccU), bswap_32big(0xcd1fd9a9U),
                       bswap_32big(0x0c4f2d41U));
    }
    else if (0x00000002U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0171f209U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_2004H, 0x00000050U);
        r_rsip_func101(bswap_32big(0x94a26036U), bswap_32big(0x3a4175c8U), bswap_32big(0xb7db7960U),
                       bswap_32big(0x8ec98da2U));
    }

    WR1_PROG(REG_2008H, 0x00000003U);
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
    WR1_PROG(REG_1420H, bswap_32big(0x00007501U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0x55811f30U),
                   bswap_32big(0x243ce92cU),
                   bswap_32big(0x40f58c20U),
                   bswap_32big(0x44248066U));
    r_rsip_func045();
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00007501U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0x06bd23bcU),
                   bswap_32big(0xe111f7b8U),
                   bswap_32big(0x50c1d59eU),
                   bswap_32big(0x9e5ee5b5U));
    r_rsip_func046();
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
    WR1_PROG(REG_1400H, 0x01420021U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
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
    r_rsip_func100(bswap_32big(0x14e2281aU),
                   bswap_32big(0x3ebe561cU),
                   bswap_32big(0xc730b562U),
                   bswap_32big(0x3459aefaU));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0xccd86e05U), bswap_32big(0x0d9be19eU), bswap_32big(0x0c96fa38U),
                       bswap_32big(0x1d59f0d2U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12U, 0U);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        if ((InData_MsgLen[0] == 0) && (InData_MsgLen[1] == 0))
        {
            WR1_PROG(REG_1444H, 0x00000020U);
            WR1_PROG(REG_2014H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x00000020U);
            WR1_PROG(REG_2010H, 0x00000080U);
            WR1_PROG(REG_200CH, 0x00000001U);
            WAIT_STS(REG_2030H, 8U, 0U);
            WR1_PROG(REG_1444H, 0x00000020U);
            WR1_PROG(REG_2014H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x00000020U);
            WR1_PROG(REG_2010H, 0x00000000U);
            WR1_PROG(REG_200CH, 0x00000100U);
            r_rsip_func101(bswap_32big(0x9cc115baU), bswap_32big(0x9905d6a0U), bswap_32big(0x974ff6c8U),
                           bswap_32big(0x14b8743fU));
        }
        else
        {
            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_ADDR(REG_2014H, &InData_MsgLen[0]);
            WR1_PROG(REG_1444H, 0x00000040U);
            WR1_ADDR(REG_2010H, &InData_MsgLen[1]);
            WR1_PROG(REG_200CH, 0x00000001U);
            r_rsip_func101(bswap_32big(0xb89252f5U), bswap_32big(0x5364c0b3U), bswap_32big(0x251a9fd1U),
                           bswap_32big(0xa84c624bU));
        }

        return RSIP_RET_PASS;
    }
}
