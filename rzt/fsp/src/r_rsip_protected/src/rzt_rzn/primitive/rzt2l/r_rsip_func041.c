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

void r_rsip_func041 (void)
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
    r_rsip_func100(bswap_32big(0x44b36e76U),
                   bswap_32big(0x80a78d38U),
                   bswap_32big(0xe1daeb26U),
                   bswap_32big(0xb03d4939U));
    WR1_PROG(REG_1600H, 0x0000b420U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x000001f0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x81840001U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1824H, 0x08000085U);
    WR1_PROG(REG_1400H, 0x00490011U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WAIT_STS(REG_1A28H, 6U, 0U);
    WR1_PROG(REG_143CH, 0x00000500U);
    r_rsip_func100(bswap_32big(0x5bed73c7U),
                   bswap_32big(0xccd9e998U),
                   bswap_32big(0x87a81d70U),
                   bswap_32big(0x0c12be2bU));
    WR1_PROG(REG_1444H, 0x000000a1U);
    WR1_PROG(REG_1824H, 0x4a000044U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    WR1_PROG(REG_1444H, 0x000000a1U);
    WR1_PROG(REG_1824H, 0x0e000484U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x0185582bU));
    WAIT_STS(REG_1828H, 6U, 0U);
    WR1_PROG(REG_143CH, 0x00000500U);
    r_rsip_func100(bswap_32big(0xfef7ada1U),
                   bswap_32big(0xa71a74b3U),
                   bswap_32big(0x5d80fd0bU),
                   bswap_32big(0xac95cfacU));
    WR1_PROG(REG_1600H, 0x00008c00U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00ffffffU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00009000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x01000000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1444H, 0x000000a1U);
    WR1_PROG(REG_1824H, 0x4a000044U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    WR1_PROG(REG_1824H, 0x0e000484U);
    WR1_PROG(REG_1608H, 0x81010000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1400H, 0x00490005U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WAIT_STS(REG_1A28H, 6U, 0U);
    WR1_PROG(REG_143CH, 0x00000900U);
    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
