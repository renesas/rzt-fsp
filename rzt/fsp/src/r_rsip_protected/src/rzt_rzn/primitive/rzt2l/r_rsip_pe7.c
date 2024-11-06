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

rsip_ret_t r_rsip_pe7 (const uint32_t InData_HashType[],
                       const uint32_t InData_KDFInfo[],
                       const uint32_t InData_KDFInfo_Count[],
                       const uint32_t InData_OutDataType[],
                       const uint32_t InData_OutDataLocation[],
                       const uint32_t InData_SeqNum[],
                       uint32_t       OutData_HMACKeyIndex[],
                       uint32_t       OutData_KeyIndex[],
                       uint32_t       OutData_EncIV[])
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

    WR1_PROG(REG_1B00H, 0x00e70002U);
    WR1_PROG(REG_144CH, 0x00000000U);
    WR1_PROG(REG_1444H, 0x000002c7U);
    WR1_PROG(REG_1608H, 0x80030080U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_HashType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_KDFInfo_Count[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_OutDataType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000c84U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);
    WR1_PROG(REG_1600H, 0x38000ca5U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    WR1_PROG(REG_1600H, 0x3420a8c0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000007U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);
    r_rsip_func100(bswap_32big(0x64273a25U),
                   bswap_32big(0xf5438cf3U),
                   bswap_32big(0x3b16ad2bU),
                   bswap_32big(0x63587ccbU));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0x27dba319U), bswap_32big(0x25030af4U), bswap_32big(0xf36415f6U),
                       bswap_32big(0xc750fb26U));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12U, 0U);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0xea3f3cd3U), bswap_32big(0x611c5875U), bswap_32big(0x0dbf130aU),
                       bswap_32big(0xb9b8ba6cU));
        WR1_PROG(REG_1600H, 0x00007c06U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_143CH, 0x00600000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (0x00000000U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x012dfa89U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x0000000fU));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x7bd250feU), bswap_32big(0x3d675f31U), bswap_32big(0x8248c879U),
                           bswap_32big(0xf1923889U));
        }
        else if (0x00000001U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x01fd3426U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x0000001fU));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x2078fd98U), bswap_32big(0x9eaa4f9eU), bswap_32big(0x3addca24U),
                           bswap_32big(0x0a102ce5U));
        }
        else if (0x00000002U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x01c27d60U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x0000000fU));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x86cb190dU), bswap_32big(0xe042967bU), bswap_32big(0x694583b8U),
                           bswap_32big(0x71ad15b8U));
        }
        else if (0x00000003U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x01c27d60U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000003U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0xffe2f63dU), bswap_32big(0x98f6aedeU), bswap_32big(0x33da1732U),
                           bswap_32big(0x10a7ce2dU));
        }
        else if (0x00000004U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x01c27d60U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x0000000bU));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x7fd440ecU), bswap_32big(0x18a2f74cU), bswap_32big(0xd3f8fadfU),
                           bswap_32big(0xfd8a795dU));
        }
        else if (0x00000005U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x010d760aU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000013U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x05fcebc9U), bswap_32big(0x230de865U), bswap_32big(0x0584779aU),
                           bswap_32big(0xc079ff33U));
        }
        else if (0x00000006U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x0171f209U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x0000001fU));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x16db2147U), bswap_32big(0x20e06c2dU), bswap_32big(0x61d676efU),
                           bswap_32big(0x6af7cba2U));
        }

        WR1_PROG(REG_1444H, 0x000000c7U);
        WR1_PROG(REG_1608H, 0x80010100U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_OutDataLocation[0]);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00003608U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00056a10U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00003628U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000262eU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00056a31U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00002e20U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x342028b1U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_1600H, 0x34202a11U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00A60000U);
        r_rsip_func100(bswap_32big(0x7a1f998eU), bswap_32big(0x8ebaeb01U), bswap_32big(0x51a461b3U),
                       bswap_32big(0xbe804c1fU));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func102(bswap_32big(0xa6b41b4eU), bswap_32big(0xb18bc466U), bswap_32big(0x643dbc31U),
                           bswap_32big(0xfbc8322dU));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0x1295ef71U), bswap_32big(0x132f84feU), bswap_32big(0xdbfaff77U),
                           bswap_32big(0x3b3eb2c7U));
            WR1_PROG(REG_1600H, 0x00003651U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00002a50U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00000a73U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x000009efU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00000a94U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00000ad6U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x81010200U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[0]);
            r_rsip_func100(bswap_32big(0xf9ad47b3U), bswap_32big(0x315771aeU), bswap_32big(0x5c4ee660U),
                           bswap_32big(0xd2612614U));
            WR1_PROG(REG_1608H, 0x81010220U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[1]);
            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x01d083dcU);
            WR1_PROG(REG_1458H, 0x00000000U);
            for (iLoop = S_RAM[0]; iLoop < S_RAM[0 + 1]; iLoop = iLoop + 1)
            {
                WR1_PROG(REG_1600H, 0x34202a72U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x2000d2c0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00007c16U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_143CH, 0x00602000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1444H, 0x000003c7U);
                WR1_PROG(REG_1608H, 0x80040000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 0]);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 1]);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 2]);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 3]);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000e701U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xb1138acbU),
                               bswap_32big(0xfe23c85bU),
                               bswap_32big(0x58b13ff6U),
                               bswap_32big(0x06a41c15U));
                r_rsip_func045();
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000e701U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xe6937145U),
                               bswap_32big(0x6a53853bU),
                               bswap_32big(0xa4fcd267U),
                               bswap_32big(0x67fe963cU));
                r_rsip_func046();
                WR1_PROG(REG_1444H, 0x000007c2U);
                WR1_PROG(REG_1A2CH, 0x40000100U);
                WR1_PROG(REG_1A24H, 0xf7009d07U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 4]);
                WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 5]);
                WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 6]);
                WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 7]);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 8]);
                WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 9]);
                WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 10]);
                WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 11]);
                WR1_PROG(REG_1608H, 0x8088000fU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1400H, 0x03420021U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1444H, 0x000003c2U);
                WR1_PROG(REG_1A2CH, 0x40000000U);
                WR1_PROG(REG_1A24H, 0x07008d05U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 12]);
                WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 13]);
                WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 14]);
                WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 15]);
                WR1_PROG(REG_1A24H, 0x9c100005U);
                WR1_PROG(REG_1400H, 0x00820011U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1600H, 0x0000a5e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000020U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00002e60U);
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func100(bswap_32big(0x5638975eU),
                               bswap_32big(0xeb57e042U),
                               bswap_32big(0xe66a28e9U),
                               bswap_32big(0xf6893938U));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    WR1_PROG(REG_1600H, 0x0000d280U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0xa8261735U),
                                   bswap_32big(0x86197b97U),
                                   bswap_32big(0x6d47b593U),
                                   bswap_32big(0x2163a910U));
                }
                else
                {
                    r_rsip_func101(bswap_32big(0x4c5e9b78U),
                                   bswap_32big(0x8aba4d6eU),
                                   bswap_32big(0xb5584d64U),
                                   bswap_32big(0x3abac480U));
                }
            }

            WR1_PROG(REG_1600H, 0x38000a72U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);
            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x38000e94U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00A60000U);
            r_rsip_func100(bswap_32big(0x03411efeU), bswap_32big(0xf732dd03U), bswap_32big(0x253715e6U),
                           bswap_32big(0xc8b02e01U));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                r_rsip_func102(bswap_32big(0xdd5af3edU),
                               bswap_32big(0x382593d2U),
                               bswap_32big(0xbbb637f9U),
                               bswap_32big(0x42d7591dU));
                WR1_PROG(REG_14B8H, 0x00000040U);
                WAIT_STS(REG_142CH, 12U, 0U);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0x9a481fd2U),
                               bswap_32big(0xbe1648f9U),
                               bswap_32big(0xcd0a0044U),
                               bswap_32big(0x041c95e5U));
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
                WR1_PROG(REG_1420H, bswap_32big(0x0000e702U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x0e662266U),
                               bswap_32big(0x80555664U),
                               bswap_32big(0x84758574U),
                               bswap_32big(0x0d660f9bU));
                r_rsip_func045();
                WR1_PROG(REG_1600H, 0x000034e9U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000e702U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xc71cbbe1U),
                               bswap_32big(0x27d699a1U),
                               bswap_32big(0x1933bb34U),
                               bswap_32big(0x0b019fb8U));
                r_rsip_func046();
                WR1_PROG(REG_1600H, 0x00008d00U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000001fU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000b5e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000080U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x3420a8c0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000002U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                r_rsip_func100(bswap_32big(0xefdd3676U),
                               bswap_32big(0x1cd5c05bU),
                               bswap_32big(0x3c1fba62U),
                               bswap_32big(0x31e79e84U));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    for (iLoop = 0; iLoop < 32; iLoop = iLoop + 1)
                    {
                        WR1_PROG(REG_1600H, 0x00000ab5U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x02003aa8U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x02003eafU);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00002d00U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00002de0U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                    }

                    WR1_PROG(REG_1600H, 0x0000b5e0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00000080U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x38000cc6U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);
                    r_rsip_func100(bswap_32big(0x37d11bbdU),
                                   bswap_32big(0xb3f5270aU),
                                   bswap_32big(0x5c7e8eedU),
                                   bswap_32big(0x44868c6cU));
                    WR1_PROG(REG_143CH, 0x00400000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    if (CHCK_STS(REG_143CH, 22U, 1U))
                    {
                        r_rsip_func100(bswap_32big(0x18b602bdU),
                                       bswap_32big(0x546ae953U),
                                       bswap_32big(0x18c7bd20U),
                                       bswap_32big(0xf1a4997fU));
                        WR1_PROG(REG_1A2CH, 0x40000000U);
                        WR1_PROG(REG_1A24H, 0xe7009d05U);
                        WR1_PROG(REG_1608H, 0x8184000fU);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1400H, 0x00890011U);
                        WAIT_STS(REG_1404H, 30U, 0U);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1408H, 0x00002012U);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[4]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[5]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[6]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[7]);
                        r_rsip_func100(bswap_32big(0xb17c3641U),
                                       bswap_32big(0xed77f126U),
                                       bswap_32big(0xc383446fU),
                                       bswap_32big(0xf2071824U));
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
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[8]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[9]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[10]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[11]);
                        r_rsip_func101(bswap_32big(0x3ec09e90U),
                                       bswap_32big(0xf8397b78U),
                                       bswap_32big(0xb236ebe2U),
                                       bswap_32big(0x485d9308U));
                    }
                    else
                    {
                        r_rsip_func100(bswap_32big(0x8ce28fc0U),
                                       bswap_32big(0x698006ccU),
                                       bswap_32big(0x7ea39ae2U),
                                       bswap_32big(0x958695adU));
                        WR1_PROG(REG_1A2CH, 0x40000100U);
                        WR1_PROG(REG_1A24H, 0xe7009d07U);
                        WR1_PROG(REG_1608H, 0x8188000fU);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1400H, 0x00890021U);
                        WAIT_STS(REG_1404H, 30U, 0U);
                        WR1_PROG(REG_143CH, 0x00001800U);
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
                        r_rsip_func100(bswap_32big(0x4b921026U),
                                       bswap_32big(0xb1bebbd1U),
                                       bswap_32big(0x14240682U),
                                       bswap_32big(0xbf423ed4U));
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
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[12]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[13]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[14]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[15]);
                        r_rsip_func101(bswap_32big(0xd7448375U),
                                       bswap_32big(0x02286230U),
                                       bswap_32big(0xc681c78bU),
                                       bswap_32big(0xe18230afU));
                    }

                    r_rsip_func100(bswap_32big(0xcd68919fU),
                                   bswap_32big(0xbc89c510U),
                                   bswap_32big(0x6928981eU),
                                   bswap_32big(0x6a02d05fU));
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
                    r_rsip_func102(bswap_32big(0xfcde49e6U),
                                   bswap_32big(0x8b0accdeU),
                                   bswap_32big(0x3b7dbaf7U),
                                   bswap_32big(0x04f86277U));
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12U, 0U);

                    return RSIP_RET_PASS;
                }
                else
                {
                    WR1_PROG(REG_1600H, 0x3420a8c0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00000005U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00A60000U);
                    r_rsip_func100(bswap_32big(0xbcb70088U),
                                   bswap_32big(0x6fca28afU),
                                   bswap_32big(0x3af2e086U),
                                   bswap_32big(0x0d4a3affU));
                    WR1_PROG(REG_143CH, 0x00400000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    if (CHCK_STS(REG_143CH, 22U, 1U))
                    {
                        for (iLoop = 0; iLoop < 32; iLoop = iLoop + 1)
                        {
                            WR1_PROG(REG_1600H, 0x00000ab5U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x02003aa8U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x02003eafU);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x00002d00U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x00002de0U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                        }

                        WR1_PROG(REG_1600H, 0x0000b5e0U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00000080U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x380088c0U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00000005U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);
                        r_rsip_func100(bswap_32big(0xd95b8f64U),
                                       bswap_32big(0xde075d38U),
                                       bswap_32big(0xf712db90U),
                                       bswap_32big(0x2aa85ca9U));
                        WR1_PROG(REG_143CH, 0x00400000U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        if (CHCK_STS(REG_143CH, 22U, 1U))
                        {
                            WR1_PROG(REG_1600H, 0x0000a5e0U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x00000014U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1608H, 0x8083000fU);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1400H, 0x0340000dU);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1600H, 0x0000b5e0U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x00000080U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            r_rsip_func101(bswap_32big(0x9da1f133U),
                                           bswap_32big(0x742c6f85U),
                                           bswap_32big(0x18f99ef9U),
                                           bswap_32big(0xd679a849U));
                        }
                        else
                        {
                            r_rsip_func101(bswap_32big(0xec44dc83U),
                                           bswap_32big(0x119da89bU),
                                           bswap_32big(0x07264498U),
                                           bswap_32big(0x06d0e2b8U));
                        }

                        r_rsip_func100(bswap_32big(0x24536ac8U),
                                       bswap_32big(0xeddd571dU),
                                       bswap_32big(0x262ba529U),
                                       bswap_32big(0x57ae5ba8U));
                        WR1_PROG(REG_1A2CH, 0x40000100U);
                        WR1_PROG(REG_1A24H, 0xe7009d07U);
                        WR1_PROG(REG_1608H, 0x8188000fU);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1400H, 0x00890021U);
                        WAIT_STS(REG_1404H, 30U, 0U);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1408H, 0x00002022U);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_HMACKeyIndex[4]);
                        RD1_ADDR(REG_1420H, &OutData_HMACKeyIndex[5]);
                        RD1_ADDR(REG_1420H, &OutData_HMACKeyIndex[6]);
                        RD1_ADDR(REG_1420H, &OutData_HMACKeyIndex[7]);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_HMACKeyIndex[8]);
                        RD1_ADDR(REG_1420H, &OutData_HMACKeyIndex[9]);
                        RD1_ADDR(REG_1420H, &OutData_HMACKeyIndex[10]);
                        RD1_ADDR(REG_1420H, &OutData_HMACKeyIndex[11]);
                        r_rsip_func100(bswap_32big(0xf0512731U),
                                       bswap_32big(0x93f8ea49U),
                                       bswap_32big(0xc5a3df95U),
                                       bswap_32big(0x4ab640d2U));
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
                        RD1_ADDR(REG_1420H, &OutData_HMACKeyIndex[12]);
                        RD1_ADDR(REG_1420H, &OutData_HMACKeyIndex[13]);
                        RD1_ADDR(REG_1420H, &OutData_HMACKeyIndex[14]);
                        RD1_ADDR(REG_1420H, &OutData_HMACKeyIndex[15]);
                        r_rsip_func100(bswap_32big(0x3718d4b6U),
                                       bswap_32big(0x8473fd89U),
                                       bswap_32big(0x8a84cf20U),
                                       bswap_32big(0x8c8f2333U));
                        WR1_PROG(REG_1608H, 0x81040000U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1408H, 0x00005012U);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_HMACKeyIndex[0]);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_HMACKeyIndex[1]);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_HMACKeyIndex[2]);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_HMACKeyIndex[3]);
                        r_rsip_func102(bswap_32big(0xb9ebd784U),
                                       bswap_32big(0xcd24c9d7U),
                                       bswap_32big(0xee58251bU),
                                       bswap_32big(0x65d61705U));
                        WR1_PROG(REG_14B8H, 0x00000040U);
                        WAIT_STS(REG_142CH, 12U, 0U);

                        return RSIP_RET_PASS;
                    }
                    else
                    {
                        for (iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
                        {
                            WR1_PROG(REG_1600H, 0x00000ab5U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x02003aa8U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x02003eafU);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x00002d00U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x00002de0U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                        }

                        WR1_PROG(REG_1600H, 0x0000b5e0U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00000080U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x380088c0U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00000002U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);
                        r_rsip_func100(bswap_32big(0x0a2463a2U),
                                       bswap_32big(0x8d1d3071U),
                                       bswap_32big(0xceb17539U),
                                       bswap_32big(0x085d6d6cU));
                        WR1_PROG(REG_143CH, 0x00400000U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        if (CHCK_STS(REG_143CH, 22U, 1U))
                        {
                            WR1_PROG(REG_1A24H, 0x08000105U);
                            WR1_PROG(REG_1608H, 0x8184000fU);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1400H, 0x00890011U);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1608H, 0x80040140U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1400H, 0x03420011U);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            r_rsip_func101(bswap_32big(0x6e36a2faU),
                                           bswap_32big(0xed63b3c1U),
                                           bswap_32big(0x0317d86eU),
                                           bswap_32big(0x18be0f95U));
                        }
                        else
                        {
                            WR1_PROG(REG_1444H, 0x000001c7U);
                            WR1_PROG(REG_1608H, 0x80020080U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WAIT_STS(REG_1444H, 31U, 1U);
                            WR1_ADDR(REG_1420H, &InData_SeqNum[0]);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WAIT_STS(REG_1444H, 31U, 1U);
                            WR1_ADDR(REG_1420H, &InData_SeqNum[1]);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x380088c0U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x00000003U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1608H, 0x00000080U);
                            WR1_PROG(REG_143CH, 0x00260000U);
                            r_rsip_func100(bswap_32big(0x173a5480U),
                                           bswap_32big(0xe022d2c0U),
                                           bswap_32big(0xe8f28e4cU),
                                           bswap_32big(0x5d2b8dbbU));
                            WR1_PROG(REG_143CH, 0x00400000U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            if (CHCK_STS(REG_143CH, 22U, 1U))
                            {
                                WR1_PROG(REG_1600H, 0x0000394fU);
                                WR1_PROG(REG_1458H, 0x00000000U);
                                WR1_PROG(REG_1600H, 0x00003564U);
                                WR1_PROG(REG_1458H, 0x00000000U);
                                WR1_PROG(REG_1600H, 0x00003585U);
                                WR1_PROG(REG_1458H, 0x00000000U);
                                WR1_PROG(REG_1600H, 0x0000b5a0U);
                                WR1_PROG(REG_1458H, 0x00000000U);
                                WR1_PROG(REG_1600H, 0x00000001U);
                                WR1_PROG(REG_1458H, 0x00000000U);
                                r_rsip_func101(bswap_32big(0x3cc742d6U), bswap_32big(0xd769b72fU),
                                               bswap_32big(0xb46e7f0dU), bswap_32big(0x564543e2U));
                            }
                            else
                            {
                                WR1_PROG(REG_1A24H, 0x08000105U);
                                WR1_PROG(REG_1608H, 0x8183000fU);
                                WR1_PROG(REG_1458H, 0x00000000U);
                                WR1_PROG(REG_1400H, 0x0089000dU);
                                WAIT_STS(REG_1404H, 30U, 0U);
                                WR1_PROG(REG_143CH, 0x00001800U);
                                WR1_PROG(REG_1400H, 0x00800005U);
                                WAIT_STS(REG_1404H, 30U, 0U);
                                WR1_PROG(REG_143CH, 0x00001800U);
                                WR1_PROG(REG_1608H, 0x80040140U);
                                WR1_PROG(REG_1458H, 0x00000000U);
                                WR1_PROG(REG_1400H, 0x03420011U);
                                WAIT_STS(REG_1404H, 30U, 0U);
                                WR1_PROG(REG_143CH, 0x00001800U);
                                WR1_PROG(REG_1600H, 0x00000964U);
                                WR1_PROG(REG_1458H, 0x00000000U);
                                WR1_PROG(REG_1600H, 0x00000985U);
                                WR1_PROG(REG_1458H, 0x00000000U);
                                WR1_PROG(REG_1600H, 0x0000b5a0U);
                                WR1_PROG(REG_1458H, 0x00000000U);
                                WR1_PROG(REG_1600H, 0x00000001U);
                                WR1_PROG(REG_1458H, 0x00000000U);
                                r_rsip_func101(bswap_32big(0x39eba7b2U), bswap_32big(0x70f0a41cU),
                                               bswap_32big(0xb0084d85U), bswap_32big(0xf5adfd69U));
                            }
                        }

                        r_rsip_func100(bswap_32big(0xb4152df9U),
                                       bswap_32big(0xb57b110aU),
                                       bswap_32big(0x52b68a65U),
                                       bswap_32big(0x0ee33839U));
                        WR1_PROG(REG_1A2CH, 0x40000000U);
                        WR1_PROG(REG_1A24H, 0xe7009d05U);
                        WR1_PROG(REG_1608H, 0x81040140U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1400H, 0x00890011U);
                        WAIT_STS(REG_1404H, 30U, 0U);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1408H, 0x00002012U);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_EncIV[4]);
                        RD1_ADDR(REG_1420H, &OutData_EncIV[5]);
                        RD1_ADDR(REG_1420H, &OutData_EncIV[6]);
                        RD1_ADDR(REG_1420H, &OutData_EncIV[7]);
                        r_rsip_func100(bswap_32big(0x1836e805U),
                                       bswap_32big(0xe442ff5dU),
                                       bswap_32big(0xb591bcd9U),
                                       bswap_32big(0xfc20b88cU));
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
                        RD1_ADDR(REG_1420H, &OutData_EncIV[8]);
                        RD1_ADDR(REG_1420H, &OutData_EncIV[9]);
                        RD1_ADDR(REG_1420H, &OutData_EncIV[10]);
                        RD1_ADDR(REG_1420H, &OutData_EncIV[11]);
                        r_rsip_func100(bswap_32big(0xe035c0d5U),
                                       bswap_32big(0x3a8a5821U),
                                       bswap_32big(0x2deb19f8U),
                                       bswap_32big(0x0a4dea93U));
                        WR1_PROG(REG_1608H, 0x81040000U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1408H, 0x00005012U);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_EncIV[0]);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_EncIV[1]);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_EncIV[2]);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_EncIV[3]);
                        r_rsip_func102(bswap_32big(0x82b304aeU),
                                       bswap_32big(0xb3794986U),
                                       bswap_32big(0x017a2330U),
                                       bswap_32big(0xe34cc19eU));
                        WR1_PROG(REG_14B8H, 0x00000040U);
                        WAIT_STS(REG_142CH, 12U, 0U);

                        return RSIP_RET_PASS;
                    }
                }
            }
        }
    }
}
