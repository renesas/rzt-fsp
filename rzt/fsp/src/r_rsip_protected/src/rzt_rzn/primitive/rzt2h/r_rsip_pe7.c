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
    r_rsip_func100(bswap_32big(0x999442b6U),
                   bswap_32big(0x7b5cfa45U),
                   bswap_32big(0xb164b643U),
                   bswap_32big(0x3f8cce7bU));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0xce1f9b85U), bswap_32big(0xb5503913U), bswap_32big(0xdda443fdU),
                       bswap_32big(0x92881425U));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12U, 0U);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x8f005c05U), bswap_32big(0xbb9db3cbU), bswap_32big(0xe873017eU),
                       bswap_32big(0x7686f8a9U));
        WR1_PROG(REG_1600H, 0x00007c06U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_143CH, 0x00600000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (0x00000000U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x011bff02U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x0000000fU));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0xf0337f82U), bswap_32big(0x761ab3b0U), bswap_32big(0xc1a5759bU),
                           bswap_32big(0x4d918f32U));
        }
        else if (0x00000001U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x017a9348U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x0000001fU));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x07c0ac37U), bswap_32big(0x48232413U), bswap_32big(0x4d59dd21U),
                           bswap_32big(0xf91addbeU));
        }
        else if (0x00000002U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x0179875aU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x0000000fU));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x534ff908U), bswap_32big(0x2e44ef4cU), bswap_32big(0xb0978fddU),
                           bswap_32big(0xe5c1d344U));
        }
        else if (0x00000003U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x0179875aU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000003U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x76a32a1fU), bswap_32big(0x22b766ebU), bswap_32big(0xabdac0c8U),
                           bswap_32big(0xeddc8d23U));
        }
        else if (0x00000004U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x0179875aU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x0000000bU));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x4d86173eU), bswap_32big(0x87d3ac86U), bswap_32big(0xd0b9b9afU),
                           bswap_32big(0x14750696U));
        }
        else if (0x00000005U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x01ae25b0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x00000013U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0xaaa546c2U), bswap_32big(0xbd769b82U), bswap_32big(0x01810163U),
                           bswap_32big(0xa3fdb60cU));
        }
        else if (0x00000006U == RD1_MASK(REG_1440H, 0xffffffffU))
        {
            WR1_PROG(REG_1600H, 0x0000b520U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x014320b8U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x800101c0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x0000001fU));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x03eaf3d5U), bswap_32big(0x94c0a6c6U), bswap_32big(0xff4ca7b4U),
                           bswap_32big(0x9f276847U));
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
        r_rsip_func100(bswap_32big(0x4b249fc9U), bswap_32big(0x66a3cdb3U), bswap_32big(0x7bc4db3eU),
                       bswap_32big(0xa91a4a08U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func102(bswap_32big(0xac4854feU), bswap_32big(0xa35c2314U), bswap_32big(0xb3711478U),
                           bswap_32big(0x5ce8843eU));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(bswap_32big(0x93d6e49dU), bswap_32big(0xfac1abcaU), bswap_32big(0x2313d98cU),
                           bswap_32big(0x491c39e2U));
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
            r_rsip_func100(bswap_32big(0x143de527U), bswap_32big(0xcd5eba38U), bswap_32big(0x6221edc5U),
                           bswap_32big(0xf07e1a09U));
            WR1_PROG(REG_1608H, 0x81010220U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1408H, 0x00005006U);
            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[1]);
            WR1_PROG(REG_1600H, 0x0000b4e0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x018f1cdcU);
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
                r_rsip_func101(bswap_32big(0x342255c3U),
                               bswap_32big(0x1d58e0b9U),
                               bswap_32big(0x3e59300dU),
                               bswap_32big(0x8ee1f0f9U));
                r_rsip_func045();
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000e701U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xa0349abfU),
                               bswap_32big(0x1a833a54U),
                               bswap_32big(0xad0bdbd7U),
                               bswap_32big(0xa0e7f022U));
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
                r_rsip_func100(bswap_32big(0x35959fbdU),
                               bswap_32big(0x701341fbU),
                               bswap_32big(0xa004a9f7U),
                               bswap_32big(0x88cc35a0U));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    WR1_PROG(REG_1600H, 0x0000d280U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0xc61ae275U),
                                   bswap_32big(0x44eb20b8U),
                                   bswap_32big(0x2f165b01U),
                                   bswap_32big(0xa77531e1U));
                }
                else
                {
                    r_rsip_func101(bswap_32big(0x71754ad5U),
                                   bswap_32big(0x920112a6U),
                                   bswap_32big(0x8e7a605bU),
                                   bswap_32big(0x8049d99eU));
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
            r_rsip_func100(bswap_32big(0xeecb5e39U), bswap_32big(0x80d62b67U), bswap_32big(0x9264b6bdU),
                           bswap_32big(0x47f70677U));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                r_rsip_func102(bswap_32big(0xcda7c065U),
                               bswap_32big(0x35d1b640U),
                               bswap_32big(0x70d4ff32U),
                               bswap_32big(0xfa4592efU));
                WR1_PROG(REG_14B8H, 0x00000040U);
                WAIT_STS(REG_142CH, 12U, 0U);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0xf80c4ad6U),
                               bswap_32big(0x9f14112aU),
                               bswap_32big(0xf437639fU),
                               bswap_32big(0xe45d6a0dU));
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
                r_rsip_func101(bswap_32big(0x4ae3c9deU),
                               bswap_32big(0x41fd8a51U),
                               bswap_32big(0x493da835U),
                               bswap_32big(0x429b238cU));
                r_rsip_func045();
                WR1_PROG(REG_1600H, 0x000034e9U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1444H, 0x000000a7U);
                WR1_PROG(REG_1608H, 0x800103a0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_PROG(REG_1420H, bswap_32big(0x0000e702U));
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xefb77a67U),
                               bswap_32big(0x4a6c9210U),
                               bswap_32big(0x478b1746U),
                               bswap_32big(0x488f9605U));
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
                r_rsip_func100(bswap_32big(0x0b71869cU),
                               bswap_32big(0x7a1b3219U),
                               bswap_32big(0x4fac3b2fU),
                               bswap_32big(0x2451cd51U));
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
                    r_rsip_func100(bswap_32big(0xc37f0b58U),
                                   bswap_32big(0x83b35b69U),
                                   bswap_32big(0x7d2ca045U),
                                   bswap_32big(0xa523d254U));
                    WR1_PROG(REG_143CH, 0x00400000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    if (CHCK_STS(REG_143CH, 22U, 1U))
                    {
                        r_rsip_func100(bswap_32big(0xdc98dfbdU),
                                       bswap_32big(0xc6d46599U),
                                       bswap_32big(0x28b8bafaU),
                                       bswap_32big(0x60c76db9U));
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
                        r_rsip_func100(bswap_32big(0x94b586b3U),
                                       bswap_32big(0x03fd94fcU),
                                       bswap_32big(0x9b2a41ecU),
                                       bswap_32big(0xe0c1ac7bU));
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
                        r_rsip_func101(bswap_32big(0xc007b8eeU),
                                       bswap_32big(0x91a560f9U),
                                       bswap_32big(0x126cd13cU),
                                       bswap_32big(0x8e589a7dU));
                    }
                    else
                    {
                        r_rsip_func100(bswap_32big(0xc946f854U),
                                       bswap_32big(0xd4418b1eU),
                                       bswap_32big(0x1ed80455U),
                                       bswap_32big(0xe2b96dfbU));
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
                        r_rsip_func100(bswap_32big(0x7e1d46bcU),
                                       bswap_32big(0x75dc8e60U),
                                       bswap_32big(0x6c093988U),
                                       bswap_32big(0xbb5f9479U));
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
                        r_rsip_func101(bswap_32big(0x046b937fU),
                                       bswap_32big(0x84b84e51U),
                                       bswap_32big(0x48df0073U),
                                       bswap_32big(0xb82df13eU));
                    }

                    r_rsip_func100(bswap_32big(0x5135e58cU),
                                   bswap_32big(0x39fa21ccU),
                                   bswap_32big(0x2951d04dU),
                                   bswap_32big(0x7767e352U));
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
                    r_rsip_func102(bswap_32big(0xa837f4fbU),
                                   bswap_32big(0x1bc89435U),
                                   bswap_32big(0xa975aed2U),
                                   bswap_32big(0x0040b986U));
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
                    r_rsip_func100(bswap_32big(0xac78c2beU),
                                   bswap_32big(0x9be2f1bfU),
                                   bswap_32big(0x1eece4aaU),
                                   bswap_32big(0x26d07e82U));
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
                        r_rsip_func100(bswap_32big(0x9c1259e8U),
                                       bswap_32big(0x3c2ef223U),
                                       bswap_32big(0x91de3798U),
                                       bswap_32big(0xc9dbefd9U));
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
                            r_rsip_func101(bswap_32big(0x5015800fU),
                                           bswap_32big(0xfafef8dcU),
                                           bswap_32big(0xe48ce96dU),
                                           bswap_32big(0x439b9c74U));
                        }
                        else
                        {
                            r_rsip_func101(bswap_32big(0xf6658087U),
                                           bswap_32big(0xb37b65d5U),
                                           bswap_32big(0x7075caa3U),
                                           bswap_32big(0xcb315b66U));
                        }

                        r_rsip_func100(bswap_32big(0x5d2ec926U),
                                       bswap_32big(0x8d5def3bU),
                                       bswap_32big(0x3b4c80d8U),
                                       bswap_32big(0x664332c0U));
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
                        r_rsip_func100(bswap_32big(0x3b8e26b9U),
                                       bswap_32big(0x3e614863U),
                                       bswap_32big(0x413018c4U),
                                       bswap_32big(0xc82a761eU));
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
                        r_rsip_func100(bswap_32big(0x46a3f728U),
                                       bswap_32big(0x45f8bc8aU),
                                       bswap_32big(0x7ae423a5U),
                                       bswap_32big(0xe45153bfU));
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
                        r_rsip_func102(bswap_32big(0xf0671d0fU),
                                       bswap_32big(0xcd159c7fU),
                                       bswap_32big(0x9f33c39eU),
                                       bswap_32big(0x70e25cecU));
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
                        r_rsip_func100(bswap_32big(0xb8e67f2aU),
                                       bswap_32big(0x4f97b560U),
                                       bswap_32big(0x5fa9782fU),
                                       bswap_32big(0x9ad13ad8U));
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
                            r_rsip_func101(bswap_32big(0x119ffb3fU),
                                           bswap_32big(0xcc26af99U),
                                           bswap_32big(0x0121343dU),
                                           bswap_32big(0x19f37a8bU));
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
                            r_rsip_func100(bswap_32big(0xf989d30fU),
                                           bswap_32big(0xb263f720U),
                                           bswap_32big(0x5999a8e4U),
                                           bswap_32big(0x40c0d72aU));
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
                                r_rsip_func101(bswap_32big(0x31ff0ceeU), bswap_32big(0x1e844d17U),
                                               bswap_32big(0x1543557aU), bswap_32big(0x425a62afU));
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
                                r_rsip_func101(bswap_32big(0x1022e90cU), bswap_32big(0x2b31d0e5U),
                                               bswap_32big(0x60e3d844U), bswap_32big(0x427e57daU));
                            }
                        }

                        r_rsip_func100(bswap_32big(0xb103a922U),
                                       bswap_32big(0xe3090237U),
                                       bswap_32big(0xe24c20e3U),
                                       bswap_32big(0x773178a1U));
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
                        r_rsip_func100(bswap_32big(0x870b064aU),
                                       bswap_32big(0x890f58f7U),
                                       bswap_32big(0x6d505f2bU),
                                       bswap_32big(0x189c2af3U));
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
                        r_rsip_func100(bswap_32big(0xb8c9a3a3U),
                                       bswap_32big(0x07bd00ccU),
                                       bswap_32big(0x47ba7cedU),
                                       bswap_32big(0xf7f21e1bU));
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
                        r_rsip_func102(bswap_32big(0x97410500U),
                                       bswap_32big(0x03e3a0a2U),
                                       bswap_32big(0xc66a9210U),
                                       bswap_32big(0xbdb97d42U));
                        WR1_PROG(REG_14B8H, 0x00000040U);
                        WAIT_STS(REG_142CH, 12U, 0U);

                        return RSIP_RET_PASS;
                    }
                }
            }
        }
    }
}
