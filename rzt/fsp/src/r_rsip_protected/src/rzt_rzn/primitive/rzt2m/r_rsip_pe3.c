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
    r_rsip_func100(bswap_32big(0x75aeeaa5U),
                   bswap_32big(0x8d645e76U),
                   bswap_32big(0x4b7aaf37U),
                   bswap_32big(0xde11a5efU));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0x367031deU), bswap_32big(0x2266975bU), bswap_32big(0xc48f33b3U),
                       bswap_32big(0xf5def656U));
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
        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e301U));
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func101(bswap_32big(0xbf9d9497U), bswap_32big(0xd88a7123U), bswap_32big(0x21a5554bU),
                       bswap_32big(0xb1598208U));
        r_rsip_func045();
        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x015c5d71U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e301U));
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func101(bswap_32big(0x292eaaffU), bswap_32big(0x275b83f4U), bswap_32big(0xf005ef31U),
                       bswap_32big(0x0c81dca2U));
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
        WR1_PROG(REG_1400H, 0x03420021U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncSecret[12]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[13]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[14]);
        WR1_ADDR(REG_1420H, &InData_EncSecret[15]);
        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        r_rsip_func100(bswap_32big(0x426ee63eU), bswap_32big(0x1d42c39bU), bswap_32big(0x78ad38aeU),
                       bswap_32big(0x6a4b0832U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func102(bswap_32big(0x8bfa8137U), bswap_32big(0x506dd5e7U), bswap_32big(0xd4bee07bU),
                           bswap_32big(0xce82c35fU));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0xee701632U), bswap_32big(0x50e55374U), bswap_32big(0x66a20708U),
                           bswap_32big(0x4b615f6dU));
            r_rsip_func103();
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0c200104U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
            WR1_PROG(REG_1608H, 0x80040000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1400H, 0x03420011U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x0000e302U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0xc197d5f1U), bswap_32big(0x9f8e195bU), bswap_32big(0x6634e335U),
                           bswap_32big(0xe7658799U));
            r_rsip_func045();
            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x01799093U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800103a0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x0000e302U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0xd9d6e6ffU), bswap_32big(0x0bab6e5dU), bswap_32big(0x9e3432b3U),
                           bswap_32big(0x4a93165cU));
            r_rsip_func046();
            r_rsip_func100(bswap_32big(0x4e37a8f7U), bswap_32big(0xbdfc54e8U), bswap_32big(0xaffa2c91U),
                           bswap_32big(0x8b936d57U));
            WR1_PROG(REG_1A2CH, 0x40000100U);
            WR1_PROG(REG_1A24H, 0xe7009d07U);
            WR1_PROG(REG_1608H, 0x81880005U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1400H, 0x00890021U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
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
            r_rsip_func100(bswap_32big(0x345d492fU), bswap_32big(0x669baa76U), bswap_32big(0xe55963f6U),
                           bswap_32big(0x1b4ba4baU));
            WR1_PROG(REG_1444H, 0x000000a2U);
            WR1_PROG(REG_1A24H, 0x0c000104U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
            WR1_PROG(REG_1A2CH, 0x40000000U);
            WR1_PROG(REG_1A24H, 0x09108105U);
            WR1_PROG(REG_1400H, 0x00820011U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1408H, 0x00002012U);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[12]);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[13]);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[14]);
            RD1_ADDR(REG_1420H, &OutData_EncMsg[15]);
            r_rsip_func100(bswap_32big(0x491a1c79U), bswap_32big(0x6922740dU), bswap_32big(0xd4aa06b5U),
                           bswap_32big(0x882ec2a8U));
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
            r_rsip_func102(bswap_32big(0x588c7c13U), bswap_32big(0xf7feea72U), bswap_32big(0x89cb5383U),
                           bswap_32big(0x7e955918U));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_PASS;
        }
    }
}
