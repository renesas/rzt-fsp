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

rsip_ret_t r_rsip_p48i (const uint32_t InData_Cmd[],
                        const uint32_t InData_KeyIndex[],
                        const uint32_t InData_IVType[],
                        const uint32_t InData_IV[])
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

    WR1_PROG(REG_1B00H, 0x00480002U);
    WR1_PROG(REG_144CH, 0x00000000U);
    WR1_PROG(REG_1608H, 0x80010080U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1444H, 0x000000c7U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_Cmd[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x3000a880U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00010020U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000b480U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000080U);
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
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00004801U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0xd375e8daU),
                   bswap_32big(0x4eafce27U),
                   bswap_32big(0x88dfee5aU),
                   bswap_32big(0xdd33e0a2U));
    r_rsip_func045();
    WR1_PROG(REG_1600H, 0x0000b4e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x01352c2eU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1444H, 0x000000a7U);
    WR1_PROG(REG_1608H, 0x800103a0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_PROG(REG_1420H, bswap_32big(0x00004801U));
    WR1_PROG(REG_1458H, 0x00000000U);
    r_rsip_func101(bswap_32big(0xe504e051U),
                   bswap_32big(0x80756e1dU),
                   bswap_32big(0x4938cfc2U),
                   bswap_32big(0xaa86ed8bU));
    r_rsip_func046();
    r_rsip_func100(bswap_32big(0xa8702514U),
                   bswap_32big(0xebf2adcaU),
                   bswap_32big(0x21287dbcU),
                   bswap_32big(0x18e6f0ccU));
    WR1_PROG(REG_1444H, 0x000003c2U);
    WR1_PROG(REG_1A2CH, 0x40000000U);
    WR1_PROG(REG_1A24H, 0xf7009d05U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[4]);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[5]);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[6]);
    WR1_ADDR(REG_1420H, &InData_KeyIndex[7]);
    WR1_PROG(REG_1824H, 0x08000085U);
    WR1_PROG(REG_1400H, 0x00420011U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
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
    WR1_PROG(REG_1400H, 0x00820011U);
    WAIT_STS(REG_1404H, 30U, 0U);
    WR1_PROG(REG_143CH, 0x00001800U);
    r_rsip_func100(bswap_32big(0x5f6d6cf6U),
                   bswap_32big(0x45ff68bcU),
                   bswap_32big(0xcfa27726U),
                   bswap_32big(0xac830edaU));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0x6480b0d7U), bswap_32big(0x0ccdf9cbU), bswap_32big(0xda0b58c3U),
                       bswap_32big(0x2e0fd025U));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12U, 0U);

        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0xc6f3c52aU), bswap_32big(0x73b05938U), bswap_32big(0xb89b8354U),
                       bswap_32big(0x393fc235U));
        WR1_PROG(REG_1600H, 0x00007c04U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_143CH, 0x00600000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (0x00000000U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            r_rsip_func101(bswap_32big(0xb116c5f8U), bswap_32big(0x3bdfa9f5U), bswap_32big(0x2100bee6U),
                           bswap_32big(0x89475f47U));
        }
        else if (0x00000001U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            r_rsip_func101(bswap_32big(0xfea5e09bU), bswap_32big(0x7aa8742cU), bswap_32big(0xa985147eU),
                           bswap_32big(0x516b0b79U));
        }
        else if (0x00000002U == RD1_MASK(REG_1440H, 0xffffffffU))
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
            r_rsip_func100(bswap_32big(0x4b1ac35aU), bswap_32big(0xe5e91f67U), bswap_32big(0xfbfd94e1U),
                           bswap_32big(0x71cf39abU));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                WR1_PROG(REG_1444H, 0x000003c1U);
                WR1_PROG(REG_1824H, 0x08000045U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_IV[0]);
                WR1_ADDR(REG_1420H, &InData_IV[1]);
                WR1_ADDR(REG_1420H, &InData_IV[2]);
                WR1_ADDR(REG_1420H, &InData_IV[3]);
                r_rsip_func101(bswap_32big(0xec89d868U),
                               bswap_32big(0x65c5a84eU),
                               bswap_32big(0x24db92caU),
                               bswap_32big(0x2bf272b8U));
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
                WR1_PROG(REG_1420H, bswap_32big(0x00004802U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x682e78dcU),
                               bswap_32big(0x09ff0a92U),
                               bswap_32big(0xd7ec531cU),
                               bswap_32big(0x79479f18U));
                r_rsip_func045();
                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0199e556U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00004802U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x7c0f7489U),
                               bswap_32big(0x129ffe91U),
                               bswap_32big(0xe1291ca9U),
                               bswap_32big(0x7bbce31dU));
                r_rsip_func046();
                WR1_PROG(REG_1444H, 0x000003c2U);
                WR1_PROG(REG_1A2CH, 0x40000000U);
                WR1_PROG(REG_1A24H, 0xf7009d05U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_IV[4]);
                WR1_ADDR(REG_1420H, &InData_IV[5]);
                WR1_ADDR(REG_1420H, &InData_IV[6]);
                WR1_ADDR(REG_1420H, &InData_IV[7]);
                WR1_PROG(REG_1824H, 0x08000045U);
                WR1_PROG(REG_1400H, 0x00420011U);
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
                r_rsip_func100(bswap_32big(0x191fd474U),
                               bswap_32big(0x2a52bdfaU),
                               bswap_32big(0xa380ae3fU),
                               bswap_32big(0x39d1005fU));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    r_rsip_func102(bswap_32big(0xb65aa886U),
                                   bswap_32big(0x3a4abb39U),
                                   bswap_32big(0x05764458U),
                                   bswap_32big(0x3d2d01b5U));
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12U, 0U);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    r_rsip_func101(bswap_32big(0xeb397040U),
                                   bswap_32big(0x8d165049U),
                                   bswap_32big(0x4734e414U),
                                   bswap_32big(0xf1960cc4U));
                }
            }
        }
        else if (0x00000003U == RD1_MASK(REG_1440H, 0xffffffffU))
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
            r_rsip_func100(bswap_32big(0x14add256U), bswap_32big(0x0f347bf2U), bswap_32big(0x7cf563f8U),
                           bswap_32big(0xfb5747ccU));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                WR1_PROG(REG_1444H, 0x000003c1U);
                WR1_PROG(REG_1824H, 0x08000045U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_IV[0]);
                WR1_ADDR(REG_1420H, &InData_IV[1]);
                WR1_ADDR(REG_1420H, &InData_IV[2]);
                WR1_ADDR(REG_1420H, &InData_IV[3]);
                r_rsip_func101(bswap_32big(0xe83ee641U),
                               bswap_32big(0xcbd1b8abU),
                               bswap_32big(0xf570c85eU),
                               bswap_32big(0xa80bc352U));
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
                WR1_PROG(REG_1420H, bswap_32big(0x00004803U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xb9103fa3U),
                               bswap_32big(0xf442a2d4U),
                               bswap_32big(0xb57fa213U),
                               bswap_32big(0xf7561caaU));
                r_rsip_func045();
                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0199e556U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x00004803U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xf29a7ef8U),
                               bswap_32big(0xbf3c3274U),
                               bswap_32big(0x7a1c8d78U),
                               bswap_32big(0x76c853a0U));
                r_rsip_func046();
                WR1_PROG(REG_1444H, 0x000003c2U);
                WR1_PROG(REG_1A2CH, 0x40000000U);
                WR1_PROG(REG_1A24H, 0xf7009d05U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_IV[4]);
                WR1_ADDR(REG_1420H, &InData_IV[5]);
                WR1_ADDR(REG_1420H, &InData_IV[6]);
                WR1_ADDR(REG_1420H, &InData_IV[7]);
                WR1_PROG(REG_1824H, 0x08000045U);
                WR1_PROG(REG_1400H, 0x00420011U);
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
                r_rsip_func100(bswap_32big(0x33fa1eb1U),
                               bswap_32big(0x7f5038fdU),
                               bswap_32big(0x16ac7d8cU),
                               bswap_32big(0x29bf864bU));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    r_rsip_func102(bswap_32big(0xb9ffbed6U),
                                   bswap_32big(0x25c10deeU),
                                   bswap_32big(0x3913c976U),
                                   bswap_32big(0xb37cdfbfU));
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12U, 0U);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    r_rsip_func101(bswap_32big(0xb7c2af02U),
                                   bswap_32big(0x6d2c313cU),
                                   bswap_32big(0x95a729d2U),
                                   bswap_32big(0x7afa8281U));
                }
            }
        }
        else if (0x00000004U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1444H, 0x000003c1U);
            WR1_PROG(REG_1824H, 0x08000045U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_IV[0]);
            WR1_ADDR(REG_1420H, &InData_IV[1]);
            WR1_ADDR(REG_1420H, &InData_IV[2]);
            WR1_ADDR(REG_1420H, &InData_IV[3]);
            r_rsip_func101(bswap_32big(0xcbb587fcU), bswap_32big(0xf9184cf6U), bswap_32big(0xea680b6cU),
                           bswap_32big(0x2961d22eU));
        }

        return RSIP_RET_PASS;
    }
}
