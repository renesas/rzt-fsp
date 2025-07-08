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

rsip_ret_t r_rsip_pe3 (const uint32_t InData_HashType[], const uint32_t InData_EncSecret[], uint32_t OutData_EncMsg[])
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

    WR1_PROG(REG_1B00H, 0x00e30002U);
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
    r_rsip_func100(bswap_32big(0x155308dbU),
                   bswap_32big(0xb468af00U),
                   bswap_32big(0x738e320eU),
                   bswap_32big(0xaa323b68U));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0x6e8443a4U), bswap_32big(0x5e42adb3U), bswap_32big(0x09b1b6e5U),
                       bswap_32big(0x680f0836U));
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
        r_rsip_subfunc009(bswap_32big(0x0000e301U));
        r_rsip_func101(bswap_32big(0xde957ad5U), bswap_32big(0x7f7605c4U), bswap_32big(0x307fafe5U),
                       bswap_32big(0x74601a13U));
        r_rsip_func045();
        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x01227f79U);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_subfunc009(bswap_32big(0x0000e301U));
        r_rsip_func101(bswap_32big(0x1d4c3158U), bswap_32big(0xc0132be3U), bswap_32big(0xd58a1875U),
                       bswap_32big(0x2a46200eU));
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
        r_rsip_func100(bswap_32big(0x0a3f74a4U), bswap_32big(0x009049b2U), bswap_32big(0xc75e3129U),
                       bswap_32big(0x6556580dU));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func102(bswap_32big(0xe85ab248U), bswap_32big(0x2c17b215U), bswap_32big(0x139016a7U),
                           bswap_32big(0xd4284ffcU));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0x8b332f13U), bswap_32big(0xee00ca94U), bswap_32big(0xab0cca1bU),
                           bswap_32big(0x6f9d1e96U));
            r_rsip_func103();
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0c200104U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
            WR1_PROG(REG_1608H, 0x80040000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_subfunc003(0x03420011U);
            r_rsip_subfunc009(bswap_32big(0x0000e302U));
            r_rsip_func101(bswap_32big(0x8586aa5cU), bswap_32big(0xf7c3c3e2U), bswap_32big(0xd0c44addU),
                           bswap_32big(0x82b955fcU));
            r_rsip_func045();
            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x01d083dcU);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_subfunc009(bswap_32big(0x0000e302U));
            r_rsip_func101(bswap_32big(0xc42a873aU), bswap_32big(0x594cce0fU), bswap_32big(0xdc01bafaU),
                           bswap_32big(0xb452c8abU));
            r_rsip_func046();
            r_rsip_func100(bswap_32big(0x602cd60cU), bswap_32big(0x4c8d5a97U), bswap_32big(0x6332e31fU),
                           bswap_32big(0xa73ee559U));
            WR1_PROG(REG_1A2CH, 0x40000100U);
            WR1_PROG(REG_1A24H, 0xe7009d07U);
            WR1_PROG(REG_1608H, 0x81880005U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_subfunc003(0x00890021U);
            WR1_PROG(REG_1408H, 0x00002022U);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[4]);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[5]);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[6]);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[7]);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[8]);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[9]);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[10]);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[11]);
            r_rsip_func100(bswap_32big(0xf42e2d32U), bswap_32big(0xfeafa26dU), bswap_32big(0x0269b9c6U),
                           bswap_32big(0x640948ceU));
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0c000104U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0x09108105U);
            r_rsip_subfunc003(0x00820011U);
            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[12]);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[13]);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[14]);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[15]);
            r_rsip_func100(bswap_32big(0xbdb8ab8cU), bswap_32big(0xbf18d0c0U), bswap_32big(0x8dd8d7e6U),
                           bswap_32big(0x4ad69b7bU));
            WR1_PROG(REG_1608H, 0x81040000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1408H, 0x00005012U);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[0]);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[1]);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[2]);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[3]);
            r_rsip_func102(bswap_32big(0xc27d9fefU), bswap_32big(0xb4be10b4U), bswap_32big(0x36596879U),
                           bswap_32big(0xac3ae2a9U));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_PASS;
        }
    }
}
