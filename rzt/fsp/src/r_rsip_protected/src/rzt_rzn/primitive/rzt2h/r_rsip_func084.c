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

void r_rsip_func084 (uint32_t ARG1)
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
    r_rsip_func100(bswap_32big(0xc888f2e3U),
                   bswap_32big(0x71ca6759U),
                   bswap_32big(0x918b39f4U),
                   bswap_32big(0xbc659b01U));
    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x000001f0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x8184001eU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1A24H, 0x08000085U);
    WR1_PROG(REG_1400H, 0x00890011U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WAIT_STS(REG_1A28H, 6U, 0U);
    WR1_PROG(REG_143CH, 0x00000900U);
    WR1_PROG(REG_1600H, 0x30003340U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00050020U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x016df932U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00030040U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x011922f0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00070040U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x30003380U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00070020U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x01c72842U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00030040U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x012af360U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00050040U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000b7c0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x016479c0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func100(bswap_32big(0x4d04a8c7U),
                   bswap_32big(0xb4f35de4U),
                   bswap_32big(0x482271edU),
                   bswap_32big(0x3c0b4678U));
    WR1_PROG(REG_1A24H, 0x30001084U);
    WR1_PROG(REG_1608H, 0x810103c0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1400H, 0x00890005U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WAIT_STS(REG_1A28H, 6U, 0U);
    WR1_PROG(REG_143CH, 0x00000900U);
    WR1_PROG(REG_1444H, 0x000000a2U);
    WR1_PROG(REG_1A24H, 0x08000004U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
    WR1_PROG(REG_1404H, 0x10500000U);
    WR1_PROG(REG_1444H, 0x00002fc2U);
    WR1_PROG(REG_1A2CH, 0x00000b00U);
    WR1_PROG(REG_1A24H, 0xf7009d07U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 20]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 21]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 22]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 23]);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 24]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 25]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 26]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 27]);
    WR1_PROG(REG_1400H, 0x00c20021U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1404H, 0x13700000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 28]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 29]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 30]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 31]);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 32]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 33]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 34]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 35]);
    WR1_PROG(REG_1400H, 0x00c20021U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1404H, 0x18700000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 36]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 37]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 38]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 39]);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 40]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 41]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 42]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 43]);
    WR1_PROG(REG_1400H, 0x00c20021U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1404H, 0x18c00000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 44]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 45]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 46]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 47]);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 48]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 49]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 50]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 51]);
    WR1_PROG(REG_1400H, 0x00c20021U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1404H, 0x10a00000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 52]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 53]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 54]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 55]);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 56]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 57]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 58]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 59]);
    WR1_PROG(REG_1400H, 0x00c20021U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1404H, 0x18200000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 60]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 61]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 62]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 63]);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 64]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 65]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 66]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 67]);
    WR1_PROG(REG_1400H, 0x00c20021U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A24H, 0x07000d05U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 68]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 69]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 70]);
    WR1_ADDR(REG_1420H, &S_FLASH[ARG1 + 71]);
    WR1_PROG(REG_1A24H, 0x8c100005U);
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    WR1_PROG(REG_1600H, 0x00007c1dU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_143CH, 0x00602000U);
    WR1_PROG(REG_1458H, 0x00000000U);
}
