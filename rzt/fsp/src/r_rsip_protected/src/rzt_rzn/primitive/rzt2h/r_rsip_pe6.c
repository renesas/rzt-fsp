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

rsip_ret_t r_rsip_pe6 (const uint32_t InData_HashType[],
                       const uint32_t InData_KDFInfo[],
                       const uint32_t InData_KDFInfo_Count[],
                       const uint32_t InData_OutDataLength[],
                       uint32_t       OutData_KeyIndex[])
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
    r_rsip_func100(bswap_32big(0xe01f0024U),
                   bswap_32big(0xbf9239c2U),
                   bswap_32big(0xaaa269f3U),
                   bswap_32big(0xf727c3ceU));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0xb5c03c8eU), bswap_32big(0x6b3b1da1U), bswap_32big(0xe28d0c33U),
                       bswap_32big(0x59524f7aU));
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
        r_rsip_func100(bswap_32big(0xe2ceba88U), bswap_32big(0xacd8a824U), bswap_32big(0x8e52164aU),
                       bswap_32big(0x3be4e000U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func102(bswap_32big(0x4a49e916U), bswap_32big(0xa00e3c71U), bswap_32big(0xc02d068dU),
                           bswap_32big(0xacb5187dU));
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
            r_rsip_func100(bswap_32big(0xe7f106d8U), bswap_32big(0x37cb7fedU), bswap_32big(0x80ac0b09U),
                           bswap_32big(0x38c5c74bU));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                r_rsip_func102(bswap_32big(0x911eaa4eU),
                               bswap_32big(0x1c7c6fd1U),
                               bswap_32big(0x32a57a1aU),
                               bswap_32big(0xf680a058U));
                WR1_PROG(REG_14B8H, 0x00000040U);
                WAIT_STS(REG_142CH, 12U, 0U);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0xc0db12d3U),
                               bswap_32big(0x5a14e5bfU),
                               bswap_32big(0x59f890cbU),
                               bswap_32big(0xc4dede61U));
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
                    r_rsip_subfunc009(bswap_32big(0x0000e601U));
                    r_rsip_func101(bswap_32big(0xc27a6d3dU),
                                   bswap_32big(0x33722acdU),
                                   bswap_32big(0xbf9bf2d4U),
                                   bswap_32big(0x0fdf5f6bU));
                    r_rsip_func045();
                    WR1_PROG(REG_1600H, 0x0000b4e0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x018f1cdcU);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_subfunc009(bswap_32big(0x0000e601U));
                    r_rsip_func101(bswap_32big(0x81e71492U),
                                   bswap_32big(0x518b441eU),
                                   bswap_32big(0xc0e7fc02U),
                                   bswap_32big(0x2eaca0baU));
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
                    r_rsip_subfunc003(0x03420021U);
                    WR1_PROG(REG_1444H, 0x000003c2U);
                    WR1_PROG(REG_1A2CH, 0x40000000U);
                    WR1_PROG(REG_1A24H, 0x07008d05U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 12]);
                    WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 13]);
                    WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 14]);
                    WR1_ADDR(REG_1420H, &InData_KDFInfo[iLoop * 16 + 15]);
                    WR1_PROG(REG_1A24H, 0x9c100005U);
                    r_rsip_subfunc003(0x00820011U);
                    WR1_PROG(REG_1600H, 0x00002d00U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x0000a520U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00000020U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func100(bswap_32big(0x97e28c6fU),
                                   bswap_32big(0x652e0d8eU),
                                   bswap_32big(0x7901105fU),
                                   bswap_32big(0xd4c76909U));
                    WR1_PROG(REG_143CH, 0x00400000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    if (CHCK_STS(REG_143CH, 22U, 1U))
                    {
                        WR1_PROG(REG_1600H, 0x0000d1c0U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        r_rsip_func101(bswap_32big(0x25d87d88U),
                                       bswap_32big(0x57f56402U),
                                       bswap_32big(0x96b64f8bU),
                                       bswap_32big(0x36ad0dadU));
                    }
                    else
                    {
                        r_rsip_func101(bswap_32big(0xa8bcf870U),
                                       bswap_32big(0xe568494fU),
                                       bswap_32big(0x8dd193e5U),
                                       bswap_32big(0x820763e1U));
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
                r_rsip_func100(bswap_32big(0x31227191U),
                               bswap_32big(0xc9a9991bU),
                               bswap_32big(0xbe47a7f1U),
                               bswap_32big(0x44ed1b4cU));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    r_rsip_func102(bswap_32big(0xe7120701U),
                                   bswap_32big(0xe79ce7bfU),
                                   bswap_32big(0x46303f01U),
                                   bswap_32big(0xc7c034edU));
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12U, 0U);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    r_rsip_func100(bswap_32big(0x14657a31U),
                                   bswap_32big(0xb45ea4f4U),
                                   bswap_32big(0xba5738f9U),
                                   bswap_32big(0x3770573eU));
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
                        r_rsip_func101(bswap_32big(0xdfd1bc20U),
                                       bswap_32big(0xe1cb6d4fU),
                                       bswap_32big(0x22e55f2fU),
                                       bswap_32big(0x1f9a9324U));
                    }

                    WR1_PROG(REG_1600H, 0x3800090bU);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);
                    WR1_PROG(REG_143CH, 0x00402000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func100(bswap_32big(0xfd7e67fdU),
                                   bswap_32big(0x6c0c7957U),
                                   bswap_32big(0x5deeaacfU),
                                   bswap_32big(0x7ea0528aU));
                    r_rsip_func103();
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x0c200104U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
                    WR1_PROG(REG_1608H, 0x80040000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_subfunc003(0x03420011U);
                    r_rsip_subfunc009(bswap_32big(0x0000e602U));
                    r_rsip_func101(bswap_32big(0x09a3e701U),
                                   bswap_32big(0xc8109f97U),
                                   bswap_32big(0x4b9381a5U),
                                   bswap_32big(0x5534e68cU));
                    r_rsip_func045();
                    WR1_PROG(REG_1600H, 0x0000b4e0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x01a5a796U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_subfunc009(bswap_32big(0x0000e602U));
                    r_rsip_func101(bswap_32big(0x13e551bcU),
                                   bswap_32big(0x0247086dU),
                                   bswap_32big(0x66151677U),
                                   bswap_32big(0xaf3a6d6aU));
                    r_rsip_func046();
                    r_rsip_func100(bswap_32big(0x40ed53a6U),
                                   bswap_32big(0xc2423653U),
                                   bswap_32big(0x4b10e946U),
                                   bswap_32big(0x58685df3U));
                    WR1_PROG(REG_1600H, 0x00000929U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1A2CH, 0x40000100U);
                    WR1_PROG(REG_1A24H, 0xe7009d07U);
                    WR1_PROG(REG_1608H, 0x81900009U);
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
                    r_rsip_func100(bswap_32big(0xcff5cd4cU),
                                   bswap_32big(0x07d28dfbU),
                                   bswap_32big(0xe0de2cd5U),
                                   bswap_32big(0x39d649aaU));
                    WR1_PROG(REG_1A2CH, 0x40000100U);
                    WR1_PROG(REG_1A24H, 0xe7008d07U);
                    r_rsip_subfunc003(0x00890021U);
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
                    r_rsip_func100(bswap_32big(0xa0de4046U),
                                   bswap_32big(0x2d1a66b9U),
                                   bswap_32big(0x620ed2fbU),
                                   bswap_32big(0xd9de6eb4U));
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
                    r_rsip_func100(bswap_32big(0xd2c04a2dU),
                                   bswap_32big(0xc4d05ddaU),
                                   bswap_32big(0xd61342a5U),
                                   bswap_32big(0x4a6dacf4U));
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
                    r_rsip_func102(bswap_32big(0x729ba9ecU),
                                   bswap_32big(0x4676756cU),
                                   bswap_32big(0xf64979f0U),
                                   bswap_32big(0x8d544975U));
                    WR1_PROG(REG_14B8H, 0x00000040U);
                    WAIT_STS(REG_142CH, 12U, 0U);

                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
