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

rsip_ret_t r_rsip_pe5i (const uint32_t InData_KeyType[],
                        const uint32_t InData_KeyIndex[],
                        const uint32_t InData_HashType[],
                        const uint32_t InData_MsgLen[])
{
    RSIP_PRV_PRIMITIVE_ENTRY;
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

    WR1_PROG(REG_1B00H, 0x00e50002U);
    WR1_PROG(REG_144CH, 0x00000000U);
    WR1_PROG(REG_1444H, 0x000001c7U);
    WR1_PROG(REG_1608H, 0x800200a0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_KeyType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000cc6U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);
    r_rsip_func100(bswap_32big(0xa1f565b4U),
                   bswap_32big(0x82d85350U),
                   bswap_32big(0x917b5187U),
                   bswap_32big(0x032ee59bU));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0x1db83ec6U), bswap_32big(0x8d9d2f00U), bswap_32big(0x154714e6U),
                       bswap_32big(0x1a5faecbU));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12U, 0U);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_2000H, 0x00000001U);
        WR1_PROG(REG_2004H, 0x00000050U);
        WR1_PROG(REG_2008H, 0x00000003U);
        WR1_PROG(REG_1600H, 0x38000ca5U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        r_rsip_func100(bswap_32big(0x98e37194U), bswap_32big(0x8961b1ddU), bswap_32big(0x2bf5438aU),
                       bswap_32big(0xd5f50764U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x014320b8U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x0000b500U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00000008U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x063c1122U), bswap_32big(0xda8cbe35U), bswap_32big(0xd05f0916U),
                           bswap_32big(0x56b492adU));
        }
        else
        {
            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x01a5a796U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x0000b500U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00000010U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0xadc21e1cU), bswap_32big(0x45588ad8U), bswap_32big(0x858771c7U),
                           bswap_32big(0x1f0ee8c4U));
        }

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
        r_rsip_subfunc009(bswap_32big(0x0000e501U));
        r_rsip_func101(bswap_32big(0xc49fb9c2U), bswap_32big(0x84bf043aU), bswap_32big(0xb216c30aU),
                       bswap_32big(0x8b51a11fU));
        r_rsip_func045();
        r_rsip_subfunc009(bswap_32big(0x0000e501U));
        r_rsip_func101(bswap_32big(0x25a1bc70U), bswap_32big(0x079ceab1U), bswap_32big(0x774c8aa1U),
                       bswap_32big(0x18571093U));
        r_rsip_func046();
        r_rsip_func100(bswap_32big(0xedca76e4U), bswap_32big(0xc65a3b37U), bswap_32big(0x01b5b5d9U),
                       bswap_32big(0x0fe8f8f3U));
        WR1_PROG(REG_1608H, 0x81010100U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30U, 1U);
        RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[0]);
        WR1_PROG(REG_1600H, 0x00000929U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000044U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        WR1_PROG(REG_1444H, 0x000000a2U);
        WR1_PROG(REG_1A24H, 0x08000054U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
        for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 4)
        {
            WR1_PROG(REG_1444H, 0x000003c2U);
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0xf7008d05U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 4]);
            WR1_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 5]);
            WR1_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 6]);
            WR1_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 7]);
            r_rsip_subfunc003(0x01420011U);
            WR1_PROG(REG_1600H, 0x0000a520U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00000004U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x0b3e97c1U), bswap_32big(0x79816118U), bswap_32big(0x9180d8bdU),
                           bswap_32big(0xf05ba001U));
        }

        WR1_PROG(REG_1600H, 0x38000909U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 4]);
        WR1_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 5]);
        WR1_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 6]);
        WR1_ADDR(REG_1420H, &InData_KeyIndex[iLoop + 7]);
        WR1_PROG(REG_1A24H, 0x9c100005U);
        r_rsip_subfunc003(0x00820011U);
        r_rsip_func100(bswap_32big(0x0887c5d6U), bswap_32big(0xf22d81a7U), bswap_32big(0x3360877dU),
                       bswap_32big(0xa5c0f958U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func102(bswap_32big(0xef29b761U), bswap_32big(0xd1132229U), bswap_32big(0x329d2cbcU),
                           bswap_32big(0xc57d4fd0U));
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
                r_rsip_func101(bswap_32big(0x8e07d2a2U),
                               bswap_32big(0x23580394U),
                               bswap_32big(0x492dca6dU),
                               bswap_32big(0x721558deU));
            }
            else
            {
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_ADDR(REG_2014H, &InData_MsgLen[0]);
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_ADDR(REG_2010H, &InData_MsgLen[1]);
                WR1_PROG(REG_200CH, 0x00000001U);
                r_rsip_func101(bswap_32big(0xa9998fddU),
                               bswap_32big(0x8bf90ad6U),
                               bswap_32big(0x7734c393U),
                               bswap_32big(0x31f42416U));
            }

            return RSIP_RET_PASS;
        }
    }
}
