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
    r_rsip_func100(bswap_32big(0x8c5f7dd0U),
                   bswap_32big(0x65f9e2c2U),
                   bswap_32big(0xebb55913U),
                   bswap_32big(0xaf7f1e24U));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0xb871bc22U), bswap_32big(0x33d0127cU), bswap_32big(0x42a098d4U),
                       bswap_32big(0xe2272fdbU));
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
        r_rsip_func100(bswap_32big(0x585db598U), bswap_32big(0x36a4e87aU), bswap_32big(0x829b7680U),
                       bswap_32big(0x3e78470eU));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func102(bswap_32big(0xe433750bU), bswap_32big(0x4b7e8896U), bswap_32big(0x44d4a163U),
                           bswap_32big(0x4809a0deU));
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
            r_rsip_func100(bswap_32big(0xfa131e79U), bswap_32big(0xc6f89a56U), bswap_32big(0x0a4b4aa9U),
                           bswap_32big(0x24cc133eU));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                r_rsip_func102(bswap_32big(0x1679f518U),
                               bswap_32big(0x1787eebdU),
                               bswap_32big(0xb05df50dU),
                               bswap_32big(0x9321bbaaU));
                WR1_PROG(REG_14B8H, 0x00000040U);
                WAIT_STS(REG_142CH, 12U, 0U);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0x6afdd791U),
                               bswap_32big(0x98102b0eU),
                               bswap_32big(0x4d2325d8U),
                               bswap_32big(0x3db2e8ccU));
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
                    r_rsip_func101(bswap_32big(0xb90eb6bcU),
                                   bswap_32big(0x77f459e4U),
                                   bswap_32big(0xfbe3d495U),
                                   bswap_32big(0x6c758560U));
                    r_rsip_func045();
                    WR1_PROG(REG_1600H, 0x0000b4e0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x01d083dcU);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_PROG(REG_1420H, bswap_32big(0x0000e601U));
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0x73d4d52fU),
                                   bswap_32big(0x08b5293bU),
                                   bswap_32big(0x7ab0f321U),
                                   bswap_32big(0xbb550a6aU));
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
                    r_rsip_func100(bswap_32big(0x99603f87U),
                                   bswap_32big(0x5d0cefefU),
                                   bswap_32big(0x74c977a2U),
                                   bswap_32big(0x12532c19U));
                    WR1_PROG(REG_143CH, 0x00400000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    if (CHCK_STS(REG_143CH, 22U, 1U))
                    {
                        WR1_PROG(REG_1600H, 0x0000d1c0U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        r_rsip_func101(bswap_32big(0x8e73b355U),
                                       bswap_32big(0x96eedbf9U),
                                       bswap_32big(0xe7b15748U),
                                       bswap_32big(0xcab135deU));
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0xc841e14bU),
                                       bswap_32big(0xd1cfa64fU),
                                       bswap_32big(0xbc2da79bU),
                                       bswap_32big(0x374f3b71U));
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
                r_rsip_func100(bswap_32big(0xb3e1ce0cU),
                               bswap_32big(0xbc7d760eU),
                               bswap_32big(0xd9a3a7f1U),
                               bswap_32big(0xadef1758U));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    r_rsip_func102(bswap_32big(0xd3677534U),
                                   bswap_32big(0xe9268c8dU),
                                   bswap_32big(0x14665a04U),
                                   bswap_32big(0xed864168U));
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12U, 0U);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    r_rsip_func100(bswap_32big(0xbe6667acU),
                                   bswap_32big(0x70888ad0U),
                                   bswap_32big(0x4181eb5fU),
                                   bswap_32big(0xd8807eb8U));
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
                        r_rsip_func101(bswap_32big(0x63949a8dU),
                                       bswap_32big(0xefdc881bU),
                                       bswap_32big(0x1ecb0f3bU),
                                       bswap_32big(0x7d28eb40U));
                    }

                    WR1_PROG(REG_1600H, 0x3800090bU);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);
                    WR1_PROG(REG_143CH, 0x00402000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func100(bswap_32big(0x9ce7e116U),
                                   bswap_32big(0xdac5fea0U),
                                   bswap_32big(0x85eb1ebaU),
                                   bswap_32big(0x3c646852U));
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
                    r_rsip_func101(bswap_32big(0xad215b92U),
                                   bswap_32big(0xa004e9edU),
                                   bswap_32big(0x25f1e9ccU),
                                   bswap_32big(0x2ab69421U));
                    r_rsip_func045();
                    WR1_PROG(REG_1600H, 0x0000b4e0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x01b7bbf3U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_PROG(REG_1420H, bswap_32big(0x0000e602U));
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0x6e33d78bU),
                                   bswap_32big(0xd020eb1cU),
                                   bswap_32big(0x10bb04eeU),
                                   bswap_32big(0x17ab210dU));
                    r_rsip_func046();
                    r_rsip_func100(bswap_32big(0x6a8ca833U),
                                   bswap_32big(0x23f50d5eU),
                                   bswap_32big(0xb0b254cfU),
                                   bswap_32big(0x28a2f618U));
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
                    r_rsip_func100(bswap_32big(0x713b0929U),
                                   bswap_32big(0xb15931bdU),
                                   bswap_32big(0xa918437dU),
                                   bswap_32big(0x4de6e66dU));
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
                    r_rsip_func100(bswap_32big(0xe82c67dcU),
                                   bswap_32big(0x4ab2984dU),
                                   bswap_32big(0x69f30661U),
                                   bswap_32big(0x17cfb898U));
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
                    r_rsip_func100(bswap_32big(0xd886beb1U),
                                   bswap_32big(0x9a8a4ef7U),
                                   bswap_32big(0xf8f80307U),
                                   bswap_32big(0x9c79f297U));
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
                    r_rsip_func102(bswap_32big(0x1ff49e32U),
                                   bswap_32big(0x6a01b85eU),
                                   bswap_32big(0xd4705b31U),
                                   bswap_32big(0x8c836078U));
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12U, 0U);

                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
