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

rsip_ret_t r_rsip_p95i (const uint32_t InData_TextLen[],
                        const uint32_t InData_KeyIndex[],
                        const uint32_t InData_IV[],
                        const uint32_t InData_Header[],
                        uint32_t       Header_Len)
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

    WR1_PROG(REG_1B00H, 0x00950002U);
    WR1_PROG(REG_144CH, 0x00000000U);
    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010120U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_TextLen[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
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
    r_rsip_subfunc009(bswap_32big(0x00000095U));
    r_rsip_func101(bswap_32big(0xb676c2faU),
                   bswap_32big(0x63863a0dU),
                   bswap_32big(0x6bb57d63U),
                   bswap_32big(0xef9649bbU));
    r_rsip_func045();
    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x011bff02U);
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_subfunc009(bswap_32big(0x00000095U));
    r_rsip_func101(bswap_32big(0x8af4c40cU),
                   bswap_32big(0x6869ca2dU),
                   bswap_32big(0x3cde538fU),
                   bswap_32big(0xef6e9eb9U));
    r_rsip_func046();
    r_rsip_func100(bswap_32big(0xfc46bdf1U),
                   bswap_32big(0x1d78b764U),
                   bswap_32big(0x1572c2bcU),
                   bswap_32big(0x47e83679U));
    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0xf7009d05U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[4]);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[5]);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[6]);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[7]);
    WR1_PROG(REG_1824H, 0x08000085U);
    r_rsip_subfunc003(0x00420011U);
    WAIT_STS(REG_1828H, 6U, 0U);
    WR1_PROG(REG_143CH, 0x00000500U);
    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0x07008d05U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[8]);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[9]);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[10]);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[11]);
    WR1_PROG(REG_1A24H, 0x9c100005U);
    r_rsip_subfunc003(0x00820011U);
    r_rsip_func100(bswap_32big(0x10b64d8dU),
                   bswap_32big(0x79fb1716U),
                   bswap_32big(0xdf310426U),
                   bswap_32big(0x6e8eca4fU));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0xe9b1032cU), bswap_32big(0xd2e90a2aU), bswap_32big(0x48c160b9U),
                       bswap_32big(0x3d83165cU));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12U, 0U);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        r_rsip_func501(InData_IV, InData_Header, Header_Len);
        r_rsip_func101(bswap_32big(0x34a0740dU), bswap_32big(0xff829d9fU), bswap_32big(0x173a3e8dU),
                       bswap_32big(0xd76e469eU));

        return RSIP_RET_PASS;
    }
}
