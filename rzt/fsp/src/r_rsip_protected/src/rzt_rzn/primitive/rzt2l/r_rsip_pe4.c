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

rsip_ret_t r_rsip_pe4 (const uint32_t InData_HashType[], const uint32_t InData_EncSecret[], uint32_t OutData_KeyIndex[])
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
    if (0x0U != RD1_MASK(REG_14B8H, 0x1eU))
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00e40002U);
    WR1_PROG(REG_144CH, 0x00000000U);
    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010080U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000c84U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);
    r_rsip_func100(bswap_32big(0xba17a38fU),
                   bswap_32big(0x1073ff84U),
                   bswap_32big(0x62beaffbU),
                   bswap_32big(0xbd3b1848U));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0x49f120b9U), bswap_32big(0x74d1c2f3U), bswap_32big(0xeef188dbU),
                       bswap_32big(0x5c90c73cU));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12U, 0U);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000003c7U);
        WR1_PROG(REG_1608H, 0x80040000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncSecret[0]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[1]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[2]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[3]);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_subfunc009(bswap_32big(0x0000e401U));
        r_rsip_func101(bswap_32big(0xa76b220dU), bswap_32big(0xd8aa687bU), bswap_32big(0xb3ff503dU),
                       bswap_32big(0x61df4a7eU));
        r_rsip_func045();
        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x01227f79U);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_subfunc009(bswap_32big(0x0000e401U));
        r_rsip_func101(bswap_32big(0xcc483f55U), bswap_32big(0x07417536U), bswap_32big(0x01891534U),
                       bswap_32big(0x57c7e565U));
        r_rsip_func046();
        WR1_PROG(REG_1444H, 0x000007c2U);
        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0xf7009d07U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncSecret[4]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[5]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[6]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[7]);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncSecret[8]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[9]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[10]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[11]);
        WR1_PROG(REG_1600H, 0x000008a5U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x80880005U);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_subfunc003(0x03420021U);
        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncSecret[12]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[13]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[14]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[15]);
        WR1_PROG(REG_1A24H, 0x9c100005U);
        r_rsip_subfunc003(0x00820011U);
        r_rsip_func100(bswap_32big(0xb42d99c2U), bswap_32big(0x33505c3fU), bswap_32big(0xeebf3d4eU),
                       bswap_32big(0xa4876f3aU));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func102(bswap_32big(0xe494ad64U), bswap_32big(0x7af9f7f3U), bswap_32big(0x49433216U),
                           bswap_32big(0xf08e6de2U));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0xade4541eU), bswap_32big(0x6a7440e1U), bswap_32big(0xb790535bU),
                           bswap_32big(0xbe4a9008U));
            r_rsip_func103();
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0c200104U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
            WR1_PROG(REG_1608H, 0x80040000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_subfunc003(0x03420011U);
            r_rsip_subfunc009(bswap_32big(0x0000e402U));
            r_rsip_func101(bswap_32big(0xd6d07ca5U), bswap_32big(0xba9eae4dU), bswap_32big(0x8d60f196U),
                           bswap_32big(0x2773fba6U));
            r_rsip_func045();
            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x01b7bbf3U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_subfunc009(bswap_32big(0x0000e402U));
            r_rsip_func101(bswap_32big(0x53f27065U), bswap_32big(0x999e77caU), bswap_32big(0x8d83e132U),
                           bswap_32big(0xd58451e3U));
            r_rsip_func046();
            r_rsip_func100(bswap_32big(0xbe0e1315U), bswap_32big(0xd1786424U), bswap_32big(0xa4abb54aU),
                           bswap_32big(0xacfd200cU));
            WR1_PROG(REG_1A2CH, 0x40000100U);
            WR1_PROG(REG_1A24H, 0xe7009d07U);
            WR1_PROG(REG_1608H, 0x81880005U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_subfunc003(0x00890021U);
            WR1_PROG(REG_1408H, 0x00002022U);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[4]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[5]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[6]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[7]);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[8]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[9]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[10]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[11]);
            r_rsip_func100(bswap_32big(0x5ac5305cU), bswap_32big(0x19b524d0U), bswap_32big(0x0075edfdU),
                           bswap_32big(0x13d5160eU));
            WR1_PROG(REG_1A2CH, 0x40000100U);
            WR1_PROG(REG_1A24H, 0xe7008d07U);
            r_rsip_subfunc003(0x00800021U);
            WR1_PROG(REG_1408H, 0x00002022U);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[12]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[13]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[14]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[15]);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[16]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[17]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[18]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[19]);
            r_rsip_func100(bswap_32big(0x61c367efU), bswap_32big(0xa3f95534U), bswap_32big(0x2918fcc0U),
                           bswap_32big(0x9c82f3b4U));
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0c000104U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0x09108105U);
            r_rsip_subfunc003(0x00820011U);
            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[20]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[21]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[22]);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[23]);
            r_rsip_func100(bswap_32big(0x99de2413U), bswap_32big(0x5bf0b96cU), bswap_32big(0x6ef6a050U),
                           bswap_32big(0x8f0a2090U));
            WR1_PROG(REG_1608H, 0x81040000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1408H, 0x00005012U);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[0]);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[1]);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[2]);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_KeyIndex[3]);
            r_rsip_func102(bswap_32big(0x5818bca5U), bswap_32big(0x1b8fc259U), bswap_32big(0x77760eafU),
                           bswap_32big(0x6dd4c1d9U));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_PASS;
        }
    }
}
