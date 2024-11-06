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

rsip_ret_t r_rsip_pe1 (const uint32_t InData_Sel_KeyType[],
                       const uint32_t InData_HashType[],
                       const uint32_t InData_Certificate[],
                       const uint32_t InData_CertificateLength[],
                       const uint32_t InData_CertificatePubKey[],
                       const uint32_t InData_EncCertificateInfo[],
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
    if (0x0U != RD1_MASK(REG_14BCH, 0x1fU))
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_1B00H, 0x00e10002U);
    WR1_PROG(REG_144CH, 0x00000000U);
    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x800101e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_Sel_KeyType[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000bffU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000defU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x1000d3e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x380089e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000003U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x1000d3e1U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000fffU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    r_rsip_func100(bswap_32big(0x8fea61afU),
                   bswap_32big(0xaefb0109U),
                   bswap_32big(0x0bc9a0c5U),
                   bswap_32big(0x67cdace1U));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0xd72ff155U), bswap_32big(0x35ec3075U), bswap_32big(0x7072b330U),
                       bswap_32big(0x0d5cc7aaU));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12U, 0U);

        return RSIP_RET_FAIL;
    }
    else
    {
        WR1_PROG(REG_1444H, 0x000003c7U);
        WR1_PROG(REG_1608H, 0x80040000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[0]);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[1]);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[2]);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[3]);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e101U));
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func101(bswap_32big(0xb95f9e8aU), bswap_32big(0xbd444a99U), bswap_32big(0x45409e07U),
                       bswap_32big(0xd8162bc3U));
        r_rsip_func045();
        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x01989c0aU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1444H, 0x000000a7U);
        WR1_PROG(REG_1608H, 0x800103a0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_PROG(REG_1420H, bswap_32big(0x0000e101U));
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func101(bswap_32big(0x883379c7U), bswap_32big(0x07aa41d0U), bswap_32big(0x2e73a643U),
                       bswap_32big(0x4cb3702cU));
        r_rsip_func046();
        WR1_PROG(REG_1444H, 0x000007c2U);
        WR1_PROG(REG_1A2CH, 0x40000100U);
        WR1_PROG(REG_1A24H, 0xf7009d07U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[4]);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[5]);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[6]);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[7]);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[8]);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[9]);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[10]);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[11]);
        WR1_PROG(REG_1824H, 0x08000045U);
        WR1_PROG(REG_1400H, 0x00420011U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1824H, 0x08000055U);
        WR1_PROG(REG_1400H, 0x00420011U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[12]);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[13]);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[14]);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[15]);
        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00820011U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        r_rsip_func100(bswap_32big(0x29651106U), bswap_32big(0xf70b56c7U), bswap_32big(0xdc830f7dU),
                       bswap_32big(0x3199b064U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func102(bswap_32big(0xa1834fe2U), bswap_32big(0xe63725ffU), bswap_32big(0x68678153U),
                           bswap_32big(0xd5b8062cU));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_1444H, 0x000000c7U);
            WR1_PROG(REG_1608H, 0x800102c0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_CertificateLength[0]);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000003c7U);
            WR1_PROG(REG_1608H, 0x800402e0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_CertificatePubKey[0]);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_CertificatePubKey[1]);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_CertificatePubKey[2]);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_CertificatePubKey[3]);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_2000H, 0x00000001U);
            WR1_PROG(REG_1600H, 0x00000bffU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x38000defU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);
            r_rsip_func100(bswap_32big(0xf9cefab0U), bswap_32big(0x3d3c9098U), bswap_32big(0x4f272634U),
                           bswap_32big(0xb00ef964U));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                r_rsip_func100(bswap_32big(0x6a0bd9f9U),
                               bswap_32big(0xff268307U),
                               bswap_32big(0x3af1ecaeU),
                               bswap_32big(0xebc1349dU));
                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x80010080U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_HashType[0]);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x3420a880U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000006U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x2000b480U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000005U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00007c04U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_143CH, 0x00600000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (0x00000000U == RD1_MASK(REG_1440H, 0xffffffffU))
                {
                    WR1_PROG(REG_2004H, 0x00000040U);
                    r_rsip_func101(bswap_32big(0x4ec901c7U),
                                   bswap_32big(0x66cbb449U),
                                   bswap_32big(0x6f51d942U),
                                   bswap_32big(0x6de38ea4U));
                }
                else if (0x00000001U == RD1_MASK(REG_1440H, 0xffffffffU))
                {
                    WR1_PROG(REG_2004H, 0x00000050U);
                    r_rsip_func101(bswap_32big(0x3ada317fU),
                                   bswap_32big(0x368962f8U),
                                   bswap_32big(0x6a1e080aU),
                                   bswap_32big(0x9b8a4c67U));
                }
                else if (0x00000002U == RD1_MASK(REG_1440H, 0xffffffffU))
                {
                    WR1_PROG(REG_2004H, 0x00000080U);
                    r_rsip_func101(bswap_32big(0x8b4d3133U),
                                   bswap_32big(0xd938283aU),
                                   bswap_32big(0x90cf366dU),
                                   bswap_32big(0x593652f3U));
                }
                else if (0x00000003U == RD1_MASK(REG_1440H, 0xffffffffU))
                {
                    WR1_PROG(REG_2004H, 0x00000090U);
                    r_rsip_func101(bswap_32big(0xc89c6037U),
                                   bswap_32big(0x2f501f85U),
                                   bswap_32big(0xe36b28c1U),
                                   bswap_32big(0xa4fd5c81U));
                }
                else if (0x00000004U == RD1_MASK(REG_1440H, 0xffffffffU))
                {
                    WR1_PROG(REG_2004H, 0x000000a0U);
                    r_rsip_func101(bswap_32big(0x8292faa7U),
                                   bswap_32big(0x9c8c3f4fU),
                                   bswap_32big(0x79be4118U),
                                   bswap_32big(0x0d273409U));
                }
                else if (0x00000005U == RD1_MASK(REG_1440H, 0xffffffffU))
                {
                    WR1_PROG(REG_2004H, 0x000000b0U);
                    r_rsip_func101(bswap_32big(0x3739970aU),
                                   bswap_32big(0xd73e7903U),
                                   bswap_32big(0xd4344b7dU),
                                   bswap_32big(0xb7eef445U));
                }

                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x000000ffU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000b420U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000003U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x3c002b59U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x2000d3e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00002439U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x3c00283aU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x2000d3e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000b760U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000040U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x01e09ffdU);
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x050e7885U),
                               bswap_32big(0x7f1757d5U),
                               bswap_32big(0x433484acU),
                               bswap_32big(0xc74adcfeU));
            }
            else
            {
                WR1_PROG(REG_1600H, 0x0000b480U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000001U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_2004H, 0x00000050U);
                WR1_PROG(REG_1600H, 0x0000b400U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000001fU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000b420U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000001fU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x3c002b3aU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x1000d3e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00002439U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0800283aU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x2000d3e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000b760U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000000cU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0172e641U);
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x2a821cffU),
                               bswap_32big(0xa28f30a3U),
                               bswap_32big(0x538bda95U),
                               bswap_32big(0x95830924U));
            }

            WR1_PROG(REG_1600H, 0x3c002af8U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x1000d3e0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x3c002b19U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x1000d3e0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00002417U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x08002818U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x2000d3e0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x3c002b56U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x1000d3e0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x38000fffU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00A60000U);
            r_rsip_func100(bswap_32big(0x1eabca69U), bswap_32big(0xb2dfa9b9U), bswap_32big(0x96b40e5bU),
                           bswap_32big(0xd8b17f1dU));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                r_rsip_func102(bswap_32big(0x014e2a17U),
                               bswap_32big(0x42913d7eU),
                               bswap_32big(0x65fb5305U),
                               bswap_32big(0x698d80f4U));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12U, 0U);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0xd4747f31U),
                               bswap_32big(0x0c9c60b9U),
                               bswap_32big(0x5e6dd7b2U),
                               bswap_32big(0x40572392U));
                WR1_PROG(REG_1600H, 0x00000800U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003436U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x01836c01U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00036c21U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x81020000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1408H, 0x0000500aU);
                WAIT_STS(REG_1408H, 30U, 1U);
                RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[0]);
                WAIT_STS(REG_1408H, 30U, 1U);
                RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[1]);
                r_rsip_func100(bswap_32big(0x3ca42153U),
                               bswap_32big(0xb8a21d82U),
                               bswap_32big(0x828b9785U),
                               bswap_32big(0x9d5de9b1U));
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_ADDR(REG_2014H, &S_RAM[0]);
                WR1_PROG(REG_1444H, 0x00000040U);
                WR1_ADDR(REG_2010H, &S_RAM[1]);
                WR1_PROG(REG_1600H, 0x00003417U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00046800U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00026c00U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x81010000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1408H, 0x00005006U);
                WAIT_STS(REG_1408H, 30U, 1U);
                RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[0]);
                WR1_PROG(REG_1600H, 0x000008a5U);
                WR1_PROG(REG_1458H, 0x00000000U);
                for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 4)
                {
                    WR1_PROG(REG_1444H, 0x000003c4U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_ADDR(REG_1420H, &InData_Certificate[iLoop + 0]);
                    WR1_ADDR(REG_1420H, &InData_Certificate[iLoop + 1]);
                    WR1_ADDR(REG_1420H, &InData_Certificate[iLoop + 2]);
                    WR1_ADDR(REG_1420H, &InData_Certificate[iLoop + 3]);
                    WR1_PROG(REG_1600H, 0x0000a4a0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00000004U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0xd75e4cafU),
                                   bswap_32big(0x362cbaf0U),
                                   bswap_32big(0x7d809502U),
                                   bswap_32big(0xeb603fc7U));
                }

                r_rsip_func100(bswap_32big(0xbf4459d1U),
                               bswap_32big(0x090c9638U),
                               bswap_32big(0xbdfd53bcU),
                               bswap_32big(0xa6010795U));
                WR1_PROG(REG_1600H, 0x38000805U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1000H, 0x00010000U);
                WR1_PROG(REG_1404H, 0x10000000U);
                WR1_PROG(REG_1600H, 0x00003416U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000a400U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000003U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00026800U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x81010000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1408H, 0x00005006U);
                WAIT_STS(REG_1408H, 30U, 1U);
                RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[0]);
                WR1_PROG(REG_1600H, 0x00003445U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00026c42U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x000034d6U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x000030c0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                for ( ; iLoop < S_RAM[0]; iLoop = iLoop + 1)
                {
                    WR1_PROG(REG_1444H, 0x000000c7U);
                    WR1_PROG(REG_1608H, 0x80010120U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_ADDR(REG_1420H, &InData_Certificate[iLoop + 0]);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00000821U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    for (jLoop = 0; jLoop < 4; jLoop = jLoop + 1)
                    {
                        WR1_PROG(REG_1600H, 0x00002c20U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x01886d09U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00086d29U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00000863U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x3c002859U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x3c002b42U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x38000c63U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);
                        r_rsip_func100(bswap_32big(0x3e2c13f3U),
                                       bswap_32big(0x29485979U),
                                       bswap_32big(0x274d0430U),
                                       bswap_32big(0x077f9da9U));
                        WR1_PROG(REG_143CH, 0x00400000U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        if (CHCK_STS(REG_143CH, 22U, 1U))
                        {
                            WR1_PROG(REG_1600H, 0x38000defU);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1608H, 0x00000080U);
                            WR1_PROG(REG_143CH, 0x00260000U);
                            r_rsip_func100(bswap_32big(0x7cdb21bdU),
                                           bswap_32big(0x54695714U),
                                           bswap_32big(0x7aa81d2aU),
                                           bswap_32big(0x5fb677e8U));
                            WR1_PROG(REG_143CH, 0x00400000U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            if (CHCK_STS(REG_143CH, 22U, 1U))
                            {
                                WR1_PROG(REG_1600H, 0x00186d08U);
                                WR1_PROG(REG_1458H, 0x00000000U);
                                WR1_PROG(REG_1600H, 0x01886e88U);
                                WR1_PROG(REG_1458H, 0x00000000U);
                                WR1_PROG(REG_1600H, 0x00186908U);
                                WR1_PROG(REG_1458H, 0x00000000U);
                                r_rsip_func101(bswap_32big(0xfd4bcd92U), bswap_32big(0x5be30410U),
                                               bswap_32big(0x5a353ae3U), bswap_32big(0xafacb1eeU));
                            }
                            else
                            {
                                WR1_PROG(REG_1608H, 0x81010100U);
                                WR1_PROG(REG_1458H, 0x00000000U);
                                WR1_PROG(REG_1400H, 0x1009000dU);
                                WAIT_STS(REG_1404H, 30U, 0U);
                                WR1_PROG(REG_143CH, 0x00001800U);
                                WR1_PROG(REG_1400H, 0x10c90005U);
                                WAIT_STS(REG_1404H, 30U, 0U);
                                WR1_PROG(REG_143CH, 0x00001800U);
                                r_rsip_func101(bswap_32big(0xe0a581a9U), bswap_32big(0x691a567bU),
                                               bswap_32big(0xc5900b91U), bswap_32big(0xd6a67738U));
                            }
                        }

                        WR1_PROG(REG_1600H, 0x00000863U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x3c002857U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x3c002b02U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x38000c63U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);
                        r_rsip_func100(bswap_32big(0x368aa7abU),
                                       bswap_32big(0x8072c3bdU),
                                       bswap_32big(0x495dee9dU),
                                       bswap_32big(0xffaeabc9U));
                        WR1_PROG(REG_143CH, 0x00400000U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        if (CHCK_STS(REG_143CH, 22U, 1U))
                        {
                            WR1_PROG(REG_1608H, 0x81010100U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1400H, 0x1009000dU);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1400H, 0x10c90005U);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            r_rsip_func101(bswap_32big(0x9f00acc8U),
                                           bswap_32big(0xe8a1b688U),
                                           bswap_32big(0xe1f7f68aU),
                                           bswap_32big(0x6b595f48U));
                        }

                        WR1_PROG(REG_1600H, 0x00000863U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x3c0028c2U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x38000c63U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);
                        r_rsip_func100(bswap_32big(0x9154368cU),
                                       bswap_32big(0x1131b659U),
                                       bswap_32big(0x0d65aa3fU),
                                       bswap_32big(0x641cc17cU));
                        WR1_PROG(REG_143CH, 0x00400000U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        if (CHCK_STS(REG_143CH, 22U, 1U))
                        {
                            WR1_PROG(REG_1608H, 0x81010100U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1400H, 0x1009000dU);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1400H, 0x11490005U);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            r_rsip_func101(bswap_32big(0x9662cd42U),
                                           bswap_32big(0x7e35b673U),
                                           bswap_32big(0xc4ba9425U),
                                           bswap_32big(0xaf34b8a1U));
                        }

                        WR1_PROG(REG_1600H, 0x00002c40U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        r_rsip_func101(bswap_32big(0x4ebcfaddU),
                                       bswap_32big(0x42528fd4U),
                                       bswap_32big(0xc2862ad5U),
                                       bswap_32big(0xfebc1a0cU));
                    }

                    WR1_PROG(REG_1600H, 0x38008820U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00000004U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);
                    WR1_PROG(REG_143CH, 0x00402000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00002ca0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0x097d596fU),
                                   bswap_32big(0x464ba1b2U),
                                   bswap_32big(0x926065a6U),
                                   bswap_32big(0x38bca35cU));
                }

                WR1_PROG(REG_1600H, 0x38000805U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func100(bswap_32big(0x08b01312U),
                               bswap_32big(0x4a3b91c8U),
                               bswap_32big(0x37bfb8ddU),
                               bswap_32big(0x1029636bU));
                WR1_PROG(REG_1600H, 0x00003416U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00008c00U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000003U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000b440U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000004U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00002840U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00008c40U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000003U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x81010040U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1408H, 0x00005006U);
                WAIT_STS(REG_1408H, 30U, 1U);
                RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[0]);
                WR1_PROG(REG_1600H, 0x000008a5U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000863U);
                WR1_PROG(REG_1458H, 0x00000000U);
                for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
                {
                    WR1_PROG(REG_1608H, 0x81010060U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1400H, 0x11490005U);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x1009000dU);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1600H, 0x00086c63U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00002ca0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0xe8f74f56U),
                                   bswap_32big(0x37696b34U),
                                   bswap_32big(0xb4123785U),
                                   bswap_32big(0xfebae55aU));
                }

                WR1_PROG(REG_1600H, 0x38000845U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_2030H, 4U, 1U);
                WR1_PROG(REG_1600H, 0x00000800U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x38000c84U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_1600H, 0x38008880U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000002U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                r_rsip_func100(bswap_32big(0x1750f1d9U),
                               bswap_32big(0x4b07cc11U),
                               bswap_32big(0x6d04b99dU),
                               bswap_32big(0xa9ddd0b0U));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    WR1_PROG(REG_1608H, 0x80880000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1400H, 0x0345001dU);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x03400005U);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    r_rsip_func101(bswap_32big(0x1d59a474U),
                                   bswap_32big(0x5252f653U),
                                   bswap_32big(0x263fabd7U),
                                   bswap_32big(0xd4c7638eU));
                }
                else
                {
                    WR1_PROG(REG_1608H, 0x80880000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1400H, 0x03450021U);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    r_rsip_func101(bswap_32big(0x231495f1U),
                                   bswap_32big(0xcae1791bU),
                                   bswap_32big(0x99b98399U),
                                   bswap_32big(0x3310809eU));
                }

                WR1_PROG(REG_1608H, 0x81880000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1824H, 0x9c000005U);
                WR1_PROG(REG_1400H, 0x00490011U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1824H, 0x9c100005U);
                WR1_PROG(REG_1400H, 0x00490011U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                r_rsip_func100(bswap_32big(0x89e16fa6U),
                               bswap_32big(0x0f98d5e4U),
                               bswap_32big(0xee53c2dfU),
                               bswap_32big(0x13ec19c4U));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    r_rsip_func102(bswap_32big(0x1cb9175fU),
                                   bswap_32big(0x3884fc50U),
                                   bswap_32big(0xfd068ce2U),
                                   bswap_32big(0xe4afb609U));
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12U, 0U);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    r_rsip_func100(bswap_32big(0xec029ae8U),
                                   bswap_32big(0xfb68b487U),
                                   bswap_32big(0x64d3d81fU),
                                   bswap_32big(0xab7cfbbaU));
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
                    WR1_PROG(REG_1420H, bswap_32big(0x0000e102U));
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0x58cfaed5U),
                                   bswap_32big(0x512ae641U),
                                   bswap_32big(0xfdaa51d9U),
                                   bswap_32big(0xbefc363aU));
                    r_rsip_func045();
                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x800103a0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_PROG(REG_1420H, bswap_32big(0x0000e102U));
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0x5f6df9baU),
                                   bswap_32big(0x2a871b3aU),
                                   bswap_32big(0xd9e14c37U),
                                   bswap_32big(0x4fabe0e4U));
                    r_rsip_func046();
                    r_rsip_func100(bswap_32big(0x90f96e9bU),
                                   bswap_32big(0x4df1b3c9U),
                                   bswap_32big(0x59f344cdU),
                                   bswap_32big(0x6d08b763U));
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x08000044U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x08000054U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
                    WR1_PROG(REG_1608H, 0x81010360U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1408H, 0x00005006U);
                    WAIT_STS(REG_1408H, 30U, 1U);
                    RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[0]);
                    WR1_PROG(REG_1600H, 0x00000884U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x000008a5U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1404H, 0x10000000U);
                    for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 4)
                    {
                        WR1_PROG(REG_1600H, 0x342028bbU);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x2000d080U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00007c04U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_143CH, 0x00602000U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        r_rsip_func100(bswap_32big(0xe65ae458U),
                                       bswap_32big(0x6e8fb15cU),
                                       bswap_32big(0xbec4dc8cU),
                                       bswap_32big(0x4955c4e5U));
                        WR1_PROG(REG_1A2CH, 0x40000000U);
                        WR1_PROG(REG_1A24H, 0xe8008105U);
                        WR1_PROG(REG_1400H, 0x00830011U);
                        WAIT_STS(REG_1404H, 30U, 0U);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1408H, 0x00002012U);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 4]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 5]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 6]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 7]);
                        WR1_PROG(REG_1600H, 0x0000a4a0U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00000004U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        r_rsip_func101(bswap_32big(0xb272346eU),
                                       bswap_32big(0x743a9bedU),
                                       bswap_32big(0x0bb8b7a7U),
                                       bswap_32big(0x9294164bU));
                    }

                    r_rsip_func100(bswap_32big(0xb4e686e3U),
                                   bswap_32big(0x8a90a399U),
                                   bswap_32big(0xd06e1bd8U),
                                   bswap_32big(0x61a4c52eU));
                    WR1_PROG(REG_1600H, 0x380008bbU);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);
                    WR1_PROG(REG_143CH, 0x00402000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A2CH, 0x40000000U);
                    WR1_PROG(REG_1A24H, 0x49108054U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
                    WR1_PROG(REG_1600H, 0x00007c0fU);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_143CH, 0x00600000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    if (0x00000000U == RD1_MASK(REG_1440H, 0xffffffffU))
                    {
                        r_rsip_func100(bswap_32big(0xbf9ab5adU),
                                       bswap_32big(0xadfa1568U),
                                       bswap_32big(0xf78d3fc9U),
                                       bswap_32big(0x75e3d415U));
                        WR1_PROG(REG_1A2CH, 0x40000000U);
                        WR1_PROG(REG_1A24H, 0xe8008104U);
                        WR1_PROG(REG_1608H, 0x81010280U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1400H, 0x00890005U);
                        WAIT_STS(REG_1404H, 30U, 0U);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1408H, 0x00002012U);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 4]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 5]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 6]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 7]);
                        r_rsip_func101(bswap_32big(0xb749d3c3U),
                                       bswap_32big(0xfd5bed36U),
                                       bswap_32big(0x1dc4b14aU),
                                       bswap_32big(0xeccc655cU));
                    }
                    else if (0x00000003U == RD1_MASK(REG_1440H, 0xffffffffU))
                    {
                        r_rsip_func100(bswap_32big(0xd29ce72cU),
                                       bswap_32big(0x0f2e7f89U),
                                       bswap_32big(0x4d00a09eU),
                                       bswap_32big(0xa2dc589eU));
                        WR1_PROG(REG_1A2CH, 0x40000000U);
                        WR1_PROG(REG_1A24H, 0xe8008105U);
                        WR1_PROG(REG_1400H, 0x00830011U);
                        WAIT_STS(REG_1404H, 30U, 0U);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1408H, 0x00002012U);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 4]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 5]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 6]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 7]);
                        r_rsip_func101(bswap_32big(0x0b265f2eU),
                                       bswap_32big(0xad15fb6fU),
                                       bswap_32big(0x16b2dffbU),
                                       bswap_32big(0xee76d3a9U));
                    }

                    r_rsip_func100(bswap_32big(0x34aeea93U),
                                   bswap_32big(0xd4129e55U),
                                   bswap_32big(0xb5028635U),
                                   bswap_32big(0xc31f8539U));
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x0c100104U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
                    WR1_PROG(REG_1408H, 0x00002012U);
                    WAIT_STS(REG_1408H, 30U, 1U);
                    RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 8]);
                    RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 9]);
                    RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 10]);
                    RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 11]);
                    r_rsip_func100(bswap_32big(0xb0282c08U),
                                   bswap_32big(0x1efbc398U),
                                   bswap_32big(0xf1fb4538U),
                                   bswap_32big(0xe0302f4cU));
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
                    r_rsip_func102(bswap_32big(0xbfb5692aU),
                                   bswap_32big(0x96c8a092U),
                                   bswap_32big(0x115724caU),
                                   bswap_32big(0xd1a6715aU));
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12U, 0U);

                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
