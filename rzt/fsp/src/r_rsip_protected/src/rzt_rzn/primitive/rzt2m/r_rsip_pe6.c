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

rsip_ret_t r_rsip_pe6 (const uint32_t InData_HashType[],
                       const uint32_t InData_KDFInfo[],
                       const uint32_t InData_KDFInfo_Count[],
                       const uint32_t InData_OutDataLength[],
                       uint32_t       OutData_KeyIndex[])
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

    WR1_PROG(REG_1B00H, 0x00e60002U);
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
    WR1_ADDR(REG_1420H, &InData_OutDataLength[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000c84U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);
    r_rsip_func100(bswap_32big(0x5f937800U),
                   bswap_32big(0x56251d62U),
                   bswap_32big(0xb144663cU),
                   bswap_32big(0xebe64cc6U));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0xb73fe9cbU), bswap_32big(0xcd59c779U), bswap_32big(0x297707edU),
                       bswap_32big(0xe61f8b07U));
        WR1_PROG(REG_14B8H, 0x00000040U);
        WAIT_STS(REG_142CH, 12U, 0U);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1600H, 0x00000bffU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x380088a0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000001U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x380088a0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000002U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x38000fffU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        r_rsip_func100(bswap_32big(0xfa6a4f94U), bswap_32big(0xe567d55eU), bswap_32big(0x9f03e9f5U),
                       bswap_32big(0x171ff2f5U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func102(bswap_32big(0xa160756dU), bswap_32big(0x37e3c21eU), bswap_32big(0x3b91ae4fU),
                           bswap_32big(0xa264b2baU));
            WR1_PROG(REG_14B8H, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_1600H, 0x00003545U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00056d4aU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x3420a8c0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00000020U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);
            WR1_PROG(REG_1600H, 0x34202946U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);
            r_rsip_func100(bswap_32big(0x2a0d55cfU), bswap_32big(0x513e811bU), bswap_32big(0xfb20c6b4U),
                           bswap_32big(0x6638f43aU));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                r_rsip_func102(bswap_32big(0x188bf83fU),
                               bswap_32big(0xb39b9581U),
                               bswap_32big(0xa803708eU),
                               bswap_32big(0xf7400678U));
                WR1_PROG(REG_14B8H, 0x00000040U);
                WAIT_STS(REG_142CH, 12U, 0U);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0xa1662d6cU),
                               bswap_32big(0x96cfac59U),
                               bswap_32big(0x3b0d4aabU),
                               bswap_32big(0x39651d47U));
                WR1_PROG(REG_1608H, 0x810100a0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1408H, 0x00005006U);
                WAIT_STS(REG_1408H, 30U, 1U);
                RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[0]);
                WR1_PROG(REG_1600H, 0x00000908U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000929U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x000009ceU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x000009efU);
                WR1_PROG(REG_1458H, 0x00000000U);
                for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
                {
                    WR1_PROG(REG_1600H, 0x34202905U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x2000d1e0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00007c0fU);
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
                    WR1_PROG(REG_1420H, bswap_32big(0x0000e601U));
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0x3aec0842U),
                                   bswap_32big(0x02c61a45U),
                                   bswap_32big(0x83411a26U),
                                   bswap_32big(0x3f9a4804U));
                    r_rsip_func045();
                    WR1_PROG(REG_1600H, 0x0000b4e0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x01799093U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_PROG(REG_1420H, bswap_32big(0x0000e601U));
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0x957698dcU),
                                   bswap_32big(0x560289e6U),
                                   bswap_32big(0x0143246eU),
                                   bswap_32big(0xbd608a2fU));
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
                    WR1_PROG(REG_1608H, 0x80880009U);
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
                    WR1_PROG(REG_1600H, 0x00002d00U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x0000a520U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00000020U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func100(bswap_32big(0x895e2cfdU),
                                   bswap_32big(0x871f4da3U),
                                   bswap_32big(0x52b3738cU),
                                   bswap_32big(0xa2c54936U));
                    WR1_PROG(REG_143CH, 0x00400000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    if (CHCK_STS(REG_143CH, 22U, 1U))
                    {
                        WR1_PROG(REG_1600H, 0x0000d1c0U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        r_rsip_func101(bswap_32big(0x884c3818U),
                                       bswap_32big(0x525ce60eU),
                                       bswap_32big(0x3a4ea553U),
                                       bswap_32big(0xbe7bcc20U));
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0xa0006129U),
                                       bswap_32big(0xf8379b19U),
                                       bswap_32big(0x60110630U),
                                       bswap_32big(0x060777baU));
                    }
                }

                WR1_PROG(REG_1600H, 0x38000905U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x38000dceU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00A60000U);
                r_rsip_func100(bswap_32big(0x390c6524U),
                               bswap_32big(0xa04d2ecdU),
                               bswap_32big(0x3f780c25U),
                               bswap_32big(0x593573baU));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    r_rsip_func102(bswap_32big(0xee941eb0U),
                                   bswap_32big(0x7a1aab1fU),
                                   bswap_32big(0xc9f0aaccU),
                                   bswap_32big(0xae3958f2U));
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12U, 0U);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    r_rsip_func100(bswap_32big(0xac209520U),
                                   bswap_32big(0x92f5c0cdU),
                                   bswap_32big(0x0d615871U),
                                   bswap_32big(0x538be355U));
                    WR1_PROG(REG_1608H, 0x810100c0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1408H, 0x00005006U);
                    WAIT_STS(REG_1408H, 30U, 1U);
                    RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[0]);
                    WR1_PROG(REG_1600H, 0x0000094aU);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x0000b560U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00000040U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00002966U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00000908U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00003526U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    for (iLoop = S_RAM[0]; iLoop < 64; iLoop = iLoop + 1)
                    {
                        WR1_PROG(REG_1600H, 0x02003d49U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00002d00U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00002d20U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        r_rsip_func101(bswap_32big(0x844d3e22U),
                                       bswap_32big(0x2621bc50U),
                                       bswap_32big(0x70a196e3U),
                                       bswap_32big(0x7860469cU));
                    }

                    WR1_PROG(REG_1600H, 0x3800090bU);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);
                    WR1_PROG(REG_143CH, 0x00402000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func100(bswap_32big(0xf0048816U),
                                   bswap_32big(0x91d1a078U),
                                   bswap_32big(0x02f35bd0U),
                                   bswap_32big(0x2442bdbaU));
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
                    WR1_PROG(REG_1420H, bswap_32big(0x0000e602U));
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0x71c58425U),
                                   bswap_32big(0xf6536cd9U),
                                   bswap_32big(0x8020fd04U),
                                   bswap_32big(0x4aca6789U));
                    r_rsip_func045();
                    WR1_PROG(REG_1600H, 0x0000b4e0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x01b41ce9U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_PROG(REG_1420H, bswap_32big(0x0000e602U));
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0x8b7b1843U),
                                   bswap_32big(0x576cfdcfU),
                                   bswap_32big(0x46bdecebU),
                                   bswap_32big(0x9ae482cbU));
                    r_rsip_func046();
                    r_rsip_func100(bswap_32big(0x99d7cdb5U),
                                   bswap_32big(0xb9f8a71aU),
                                   bswap_32big(0x7ccb4205U),
                                   bswap_32big(0xa9371530U));
                    WR1_PROG(REG_1600H, 0x00000929U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1A2CH, 0x40000100U);
                    WR1_PROG(REG_1A24H, 0xe7009d07U);
                    WR1_PROG(REG_1608H, 0x81900009U);
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
                    r_rsip_func100(bswap_32big(0x05a9a712U),
                                   bswap_32big(0xeb077c15U),
                                   bswap_32big(0x7128a394U),
                                   bswap_32big(0xb02eb775U));
                    WR1_PROG(REG_1A2CH, 0x40000100U);
                    WR1_PROG(REG_1A24H, 0xe7008d07U);
                    WR1_PROG(REG_1400H, 0x00890021U);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
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
                    r_rsip_func100(bswap_32big(0xc9bb2c96U),
                                   bswap_32big(0x5550ad2cU),
                                   bswap_32big(0x809465daU),
                                   bswap_32big(0xb7dca381U));
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
                    RD1_ADDR(REG_1420H, &OutData_KeyIndex[20]);
                    RD1_ADDR(REG_1420H, &OutData_KeyIndex[21]);
                    RD1_ADDR(REG_1420H, &OutData_KeyIndex[22]);
                    RD1_ADDR(REG_1420H, &OutData_KeyIndex[23]);
                    r_rsip_func100(bswap_32big(0x13b05984U),
                                   bswap_32big(0x1b8f2a92U),
                                   bswap_32big(0x6ded8a14U),
                                   bswap_32big(0xd45877eaU));
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
                    r_rsip_func102(bswap_32big(0xe41147f2U),
                                   bswap_32big(0x0547091fU),
                                   bswap_32big(0x0a15bf32U),
                                   bswap_32big(0xd98df234U));
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12U, 0U);

                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
