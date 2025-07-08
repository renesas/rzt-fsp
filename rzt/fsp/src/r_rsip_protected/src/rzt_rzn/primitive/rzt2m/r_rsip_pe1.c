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

rsip_ret_t r_rsip_pe1 (const uint32_t InData_Sel_KeyType[],
                       const uint32_t InData_HashType[],
                       const uint32_t InData_Certificate[],
                       const uint32_t InData_CertificateLength[],
                       const uint32_t InData_CertificatePubKey[],
                       const uint32_t InData_EncCertificateInfo[],
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
    r_rsip_func100(bswap_32big(0xdae21f03U),
                   bswap_32big(0xd6071619U),
                   bswap_32big(0x2c4be634U),
                   bswap_32big(0x434b42c6U));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0xaa31f778U), bswap_32big(0x5de32edbU), bswap_32big(0x57c60accU),
                       bswap_32big(0xc72a34c9U));
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
        r_rsip_subfunc009(bswap_32big(0x0000e101U));
        r_rsip_func101(bswap_32big(0x80d2a534U), bswap_32big(0x39cc3380U), bswap_32big(0xce5293edU),
                       bswap_32big(0x705e80dcU));
        r_rsip_func045();
        WR1_PROG(REG_1600H, 0x0000b4e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x010f6caaU);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_subfunc009(bswap_32big(0x0000e101U));
        r_rsip_func101(bswap_32big(0x5d9d7fdeU), bswap_32big(0xd7e1600aU), bswap_32big(0xe2ee1e00U),
                       bswap_32big(0x97078b2cU));
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
        r_rsip_subfunc003(0x00420011U);
        WR1_PROG(REG_1824H, 0x08000055U);
        r_rsip_subfunc003(0x00420011U);
        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A2CH, 0x40000000U);
        WR1_PROG(REG_1A24H, 0x07008d05U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[12]);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[13]);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[14]);
        WR1_ADDR(REG_1420H, &InData_EncCertificateInfo[15]);
        WR1_PROG(REG_1A24H, 0x9c100005U);
        r_rsip_subfunc003(0x00820011U);
        r_rsip_func100(bswap_32big(0x8861e705U), bswap_32big(0xbfbf2acaU), bswap_32big(0x181bf764U),
                       bswap_32big(0xad268ed4U));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func102(bswap_32big(0x1cddcf0aU), bswap_32big(0x56445201U), bswap_32big(0x8ea48c41U),
                           bswap_32big(0x83d99d67U));
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
            r_rsip_func100(bswap_32big(0x3f160cf2U), bswap_32big(0x942ef464U), bswap_32big(0xfe2a576fU),
                           bswap_32big(0x37775385U));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                r_rsip_func100(bswap_32big(0x9b4761efU),
                               bswap_32big(0x1e437e1dU),
                               bswap_32big(0xdd5f84b9U),
                               bswap_32big(0x653ce7beU));
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
                    r_rsip_func101(bswap_32big(0x4af334e2U),
                                   bswap_32big(0x46b5a970U),
                                   bswap_32big(0xf5228b8eU),
                                   bswap_32big(0xa6dff17fU));
                }
                else if (0x00000001U == RD1_MASK(REG_1440H, 0xffffffffU))
                {
                    WR1_PROG(REG_2004H, 0x00000050U);
                    r_rsip_func101(bswap_32big(0x99117004U),
                                   bswap_32big(0x010179a7U),
                                   bswap_32big(0xed79e346U),
                                   bswap_32big(0xc3f62ea2U));
                }
                else if (0x00000002U == RD1_MASK(REG_1440H, 0xffffffffU))
                {
                    WR1_PROG(REG_2004H, 0x00000080U);
                    r_rsip_func101(bswap_32big(0x334e550eU),
                                   bswap_32big(0xf0bc2f44U),
                                   bswap_32big(0xc8040922U),
                                   bswap_32big(0xc6d531fcU));
                }
                else if (0x00000003U == RD1_MASK(REG_1440H, 0xffffffffU))
                {
                    WR1_PROG(REG_2004H, 0x00000090U);
                    r_rsip_func101(bswap_32big(0x36f283e0U),
                                   bswap_32big(0xfbd49ae2U),
                                   bswap_32big(0xef7e1de6U),
                                   bswap_32big(0x59d0ed3eU));
                }
                else if (0x00000004U == RD1_MASK(REG_1440H, 0xffffffffU))
                {
                    WR1_PROG(REG_2004H, 0x000000a0U);
                    r_rsip_func101(bswap_32big(0xa2ad4fcaU),
                                   bswap_32big(0xba22888eU),
                                   bswap_32big(0x66a2f00eU),
                                   bswap_32big(0x801a923bU));
                }
                else if (0x00000005U == RD1_MASK(REG_1440H, 0xffffffffU))
                {
                    WR1_PROG(REG_2004H, 0x000000b0U);
                    r_rsip_func101(bswap_32big(0x68d87231U),
                                   bswap_32big(0x31db4272U),
                                   bswap_32big(0x2b6844deU),
                                   bswap_32big(0x5eb69f8eU));
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
                WR1_PROG(REG_1600H, 0x01fbca6dU);
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0x833ad675U),
                               bswap_32big(0xe155a4beU),
                               bswap_32big(0xd0216a51U),
                               bswap_32big(0x2807a0a3U));
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
                WR1_PROG(REG_1600H, 0x01f709d1U);
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xb150b654U),
                               bswap_32big(0x66bcd082U),
                               bswap_32big(0x7e742addU),
                               bswap_32big(0x248f562cU));
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
            r_rsip_func100(bswap_32big(0x60bf2a99U), bswap_32big(0x68e8b4efU), bswap_32big(0x32caed28U),
                           bswap_32big(0x38a65aa8U));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                r_rsip_func102(bswap_32big(0x76feb438U),
                               bswap_32big(0x54ecd4b5U),
                               bswap_32big(0x5fa0a2ddU),
                               bswap_32big(0x9cd7d953U));
                WR1_PROG(REG_14BCH, 0x00000040U);
                WAIT_STS(REG_142CH, 12U, 0U);

                return RSIP_RET_FAIL;
            }
            else
            {
                r_rsip_func100(bswap_32big(0x11ae4c14U),
                               bswap_32big(0xd18ef200U),
                               bswap_32big(0xd77795dfU),
                               bswap_32big(0x203d8699U));
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
                r_rsip_func100(bswap_32big(0x13a263f8U),
                               bswap_32big(0x4fdedd26U),
                               bswap_32big(0xf6a1ad5aU),
                               bswap_32big(0x1af6cf8fU));
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
                    r_rsip_func101(bswap_32big(0x32acbcefU),
                                   bswap_32big(0x8ec65f5aU),
                                   bswap_32big(0xa5850080U),
                                   bswap_32big(0x2c5d94ceU));
                }

                r_rsip_func100(bswap_32big(0xb92f9d2eU),
                               bswap_32big(0x7529818bU),
                               bswap_32big(0x8aa08e85U),
                               bswap_32big(0x6731dd97U));
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
                        r_rsip_func100(bswap_32big(0x84a1a778U),
                                       bswap_32big(0x3ca25067U),
                                       bswap_32big(0x6dde37aaU),
                                       bswap_32big(0x21edb9e4U));
                        WR1_PROG(REG_143CH, 0x00400000U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        if (CHCK_STS(REG_143CH, 22U, 1U))
                        {
                            WR1_PROG(REG_1600H, 0x38000defU);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1608H, 0x00000080U);
                            WR1_PROG(REG_143CH, 0x00260000U);
                            r_rsip_func100(bswap_32big(0x1af96524U),
                                           bswap_32big(0x8a733eb0U),
                                           bswap_32big(0x261ea05fU),
                                           bswap_32big(0xcc4b7055U));
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
                                r_rsip_func101(bswap_32big(0xcd7ada7aU), bswap_32big(0x0d0e6b72U),
                                               bswap_32big(0x08de6b60U), bswap_32big(0xcd5e37c3U));
                            }
                            else
                            {
                                WR1_PROG(REG_1608H, 0x81010100U);
                                WR1_PROG(REG_1458H, 0x00000000U);
                                r_rsip_subfunc003(0x1009000dU);
                                r_rsip_subfunc003(0x10c90005U);
                                r_rsip_func101(bswap_32big(0xbeb9dce3U), bswap_32big(0x08cc9e52U),
                                               bswap_32big(0x70d61dd1U), bswap_32big(0x970554b3U));
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
                        r_rsip_func100(bswap_32big(0x7b070b2bU),
                                       bswap_32big(0x7751eb35U),
                                       bswap_32big(0x8bc13534U),
                                       bswap_32big(0xd6197424U));
                        WR1_PROG(REG_143CH, 0x00400000U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        if (CHCK_STS(REG_143CH, 22U, 1U))
                        {
                            WR1_PROG(REG_1608H, 0x81010100U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            r_rsip_subfunc003(0x1009000dU);
                            r_rsip_subfunc003(0x10c90005U);
                            r_rsip_func101(bswap_32big(0xd00367ebU),
                                           bswap_32big(0x2eaee7c9U),
                                           bswap_32big(0xd0d28ca5U),
                                           bswap_32big(0x334dd36bU));
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
                        r_rsip_func100(bswap_32big(0xecd6d3a7U),
                                       bswap_32big(0xc99923f9U),
                                       bswap_32big(0xe34066a8U),
                                       bswap_32big(0x0b688873U));
                        WR1_PROG(REG_143CH, 0x00400000U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        if (CHCK_STS(REG_143CH, 22U, 1U))
                        {
                            WR1_PROG(REG_1608H, 0x81010100U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            r_rsip_subfunc003(0x1009000dU);
                            r_rsip_subfunc003(0x11490005U);
                            r_rsip_func101(bswap_32big(0xba8282f5U),
                                           bswap_32big(0x647d602fU),
                                           bswap_32big(0x9ebca7f6U),
                                           bswap_32big(0x03114b90U));
                        }

                        WR1_PROG(REG_1600H, 0x00002c40U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        r_rsip_func101(bswap_32big(0x5af40a10U),
                                       bswap_32big(0xb35f5a59U),
                                       bswap_32big(0x7cb1c09cU),
                                       bswap_32big(0x038dc8a1U));
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
                    r_rsip_func101(bswap_32big(0xa45a2403U),
                                   bswap_32big(0x2ef52936U),
                                   bswap_32big(0xb5625595U),
                                   bswap_32big(0xc1ceb202U));
                }

                WR1_PROG(REG_1600H, 0x38000805U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func100(bswap_32big(0xbbb94b14U),
                               bswap_32big(0x7c65bd82U),
                               bswap_32big(0x6a04a886U),
                               bswap_32big(0x9defa0b5U));
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
                    r_rsip_subfunc003(0x11490005U);
                    r_rsip_subfunc003(0x1009000dU);
                    WR1_PROG(REG_1600H, 0x00086c63U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00002ca0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0x9bb6b902U),
                                   bswap_32big(0xeb519d52U),
                                   bswap_32big(0x5c51efcfU),
                                   bswap_32big(0xb5e6b541U));
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
                r_rsip_func100(bswap_32big(0x4c7712b8U),
                               bswap_32big(0xdc50f51fU),
                               bswap_32big(0xc9931de8U),
                               bswap_32big(0x824ec040U));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    WR1_PROG(REG_1608H, 0x80880000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_subfunc003(0x0345001dU);
                    r_rsip_subfunc003(0x03400005U);
                    r_rsip_func101(bswap_32big(0x18938218U),
                                   bswap_32big(0xdc59b316U),
                                   bswap_32big(0xbfb4b967U),
                                   bswap_32big(0xa974870fU));
                }
                else
                {
                    WR1_PROG(REG_1608H, 0x80880000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_subfunc003(0x03450021U);
                    r_rsip_func101(bswap_32big(0xd08558fbU),
                                   bswap_32big(0x68752a64U),
                                   bswap_32big(0x61a58407U),
                                   bswap_32big(0xca1e55e1U));
                }

                WR1_PROG(REG_1608H, 0x81880000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1824H, 0x9c000005U);
                r_rsip_subfunc003(0x00490011U);
                WR1_PROG(REG_1824H, 0x9c100005U);
                r_rsip_subfunc003(0x00490011U);
                r_rsip_func100(bswap_32big(0x68ca3af7U),
                               bswap_32big(0x9f9ecc7cU),
                               bswap_32big(0xb716f2c4U),
                               bswap_32big(0x551db93eU));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    r_rsip_func102(bswap_32big(0x6bb407c5U),
                                   bswap_32big(0xae07aa72U),
                                   bswap_32big(0x1e1a999bU),
                                   bswap_32big(0x9e7b0cd3U));
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12U, 0U);

                    return RSIP_RET_FAIL;
                }
                else
                {
                    r_rsip_func100(bswap_32big(0x57e297fbU),
                                   bswap_32big(0x329b81faU),
                                   bswap_32big(0x9155e269U),
                                   bswap_32big(0x376a0c03U));
                    r_rsip_func103();
                    WR1_PROG(REG_1444H, 0x000000a2U);
                    WR1_PROG(REG_1A24H, 0x0c200104U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_PROG(REG_1420H, bswap_32big(0x00000000U));
                    WR1_PROG(REG_1608H, 0x80040000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_subfunc003(0x03420011U);
                    r_rsip_subfunc009(bswap_32big(0x0000e102U));
                    r_rsip_func101(bswap_32big(0xa5051575U),
                                   bswap_32big(0x7b36b214U),
                                   bswap_32big(0x08bf443bU),
                                   bswap_32big(0xa799834fU));
                    r_rsip_func045();
                    r_rsip_subfunc009(bswap_32big(0x0000e102U));
                    r_rsip_func101(bswap_32big(0x00503068U),
                                   bswap_32big(0x4ae73799U),
                                   bswap_32big(0xb0ca2e14U),
                                   bswap_32big(0x3676f52cU));
                    r_rsip_func046();
                    r_rsip_func100(bswap_32big(0xb3da09dbU),
                                   bswap_32big(0x94c731b9U),
                                   bswap_32big(0x3d09a90aU),
                                   bswap_32big(0x275e8cd3U));
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
                        r_rsip_func100(bswap_32big(0x4fe0ee57U),
                                       bswap_32big(0xb5387a16U),
                                       bswap_32big(0xbc96dc11U),
                                       bswap_32big(0xab186007U));
                        WR1_PROG(REG_1A2CH, 0x40000000U);
                        WR1_PROG(REG_1A24H, 0xe8008105U);
                        r_rsip_subfunc003(0x00830011U);
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
                        r_rsip_func101(bswap_32big(0xa05d6763U),
                                       bswap_32big(0xe63b57a3U),
                                       bswap_32big(0xe115b11eU),
                                       bswap_32big(0x19345317U));
                    }

                    r_rsip_func100(bswap_32big(0xb9725e7cU),
                                   bswap_32big(0x24f61eebU),
                                   bswap_32big(0x1037493eU),
                                   bswap_32big(0x5b022fcaU));
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
                        r_rsip_func100(bswap_32big(0x53acdc8bU),
                                       bswap_32big(0x6a80eacbU),
                                       bswap_32big(0x74eebe29U),
                                       bswap_32big(0x5aecccc3U));
                        WR1_PROG(REG_1A2CH, 0x40000000U);
                        WR1_PROG(REG_1A24H, 0xe8008104U);
                        WR1_PROG(REG_1608H, 0x81010280U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        r_rsip_subfunc003(0x00890005U);
                        WR1_PROG(REG_1408H, 0x00002012U);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 4]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 5]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 6]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 7]);
                        r_rsip_func101(bswap_32big(0x313a24c7U),
                                       bswap_32big(0x8bd39ffdU),
                                       bswap_32big(0x4d3e1511U),
                                       bswap_32big(0xf30fb0ecU));
                    }
                    else if (0x00000003U == RD1_MASK(REG_1440H, 0xffffffffU))
                    {
                        r_rsip_func100(bswap_32big(0x2926f915U),
                                       bswap_32big(0x22e057cfU),
                                       bswap_32big(0x160d31e2U),
                                       bswap_32big(0x26856415U));
                        WR1_PROG(REG_1A2CH, 0x40000000U);
                        WR1_PROG(REG_1A24H, 0xe8008105U);
                        r_rsip_subfunc003(0x00830011U);
                        WR1_PROG(REG_1408H, 0x00002012U);
                        WAIT_STS(REG_1408H, 30U, 1U);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 4]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 5]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 6]);
                        RD1_ADDR(REG_1420H, &OutData_KeyIndex[iLoop + 7]);
                        r_rsip_func101(bswap_32big(0x903bf31eU),
                                       bswap_32big(0xf9eb4460U),
                                       bswap_32big(0x05a465b2U),
                                       bswap_32big(0xe1edaaaeU));
                    }

                    r_rsip_func100(bswap_32big(0x0031276eU),
                                   bswap_32big(0x9dac56a5U),
                                   bswap_32big(0x23507ebcU),
                                   bswap_32big(0x41f61d22U));
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
                    r_rsip_func100(bswap_32big(0x9fa7afa8U),
                                   bswap_32big(0x641cf17cU),
                                   bswap_32big(0xc7a19378U),
                                   bswap_32big(0x0e7d9f31U));
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
                    r_rsip_func102(bswap_32big(0x5e408121U),
                                   bswap_32big(0x29a5b9c1U),
                                   bswap_32big(0xecfc6e30U),
                                   bswap_32big(0x7e3ee403U));
                    WR1_PROG(REG_14BCH, 0x00000040U);
                    WAIT_STS(REG_142CH, 12U, 0U);

                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
