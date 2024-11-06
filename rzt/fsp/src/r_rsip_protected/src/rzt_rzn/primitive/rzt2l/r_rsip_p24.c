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

rsip_ret_t r_rsip_p24 (const uint32_t InData_Cmd[],
                       const uint32_t InData_KeyCertificate[],
                       const uint32_t InData_KeyCertificateLength[],
                       const uint32_t InData_KeyCertificateSignature[],
                       const uint32_t InData_KeyCertificatePubKey[],
                       const uint32_t InData_ImgPkHash[],
                       const uint32_t InData_OemRootPkHash[],
                       const uint32_t InData_CodeCertificate[],
                       const uint32_t InData_CodeCertificateLength[],
                       const uint32_t InData_CodeCertificateSignature[],
                       const uint32_t InData_CodeCertificatePubKey[],
                       const uint32_t InData_ImageHash[],
                       const uint32_t InData_Image[],
                       uint32_t       MAX_CNT)

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

    WR1_PROG(REG_1B00H, 0x00240001U);
    WR1_PROG(REG_144CH, 0x00000000U);
    WR1_PROG(REG_1444H, 0x000005c7U);
    WR1_PROG(REG_1608H, 0x800601c0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_Cmd[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_CodeCertificateLength[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    for (iLoop = 0; iLoop < 4; iLoop = iLoop + 1)
    {
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_CodeCertificatePubKey[iLoop + 0]);
        WR1_PROG(REG_1458H, 0x00000000U);
    }

    WR1_PROG(REG_1600H, 0x38000dceU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);
    r_rsip_func100(bswap_32big(0xb0f32c08U),
                   bswap_32big(0xc4964c18U),
                   bswap_32big(0x539499d9U),
                   bswap_32big(0xabfa4294U));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        WR1_PROG(REG_1444H, 0x000001c7U);
        WR1_PROG(REG_1608H, 0x80020280U);
        WR1_PROG(REG_1458H, 0x00000000U);
        for (iLoop = 0; iLoop < 2; iLoop = iLoop + 1)
        {
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_ImageHash[iLoop + 0]);
            WR1_PROG(REG_1458H, 0x00000000U);
        }

        r_rsip_func101(bswap_32big(0x3f1a8a26U), bswap_32big(0x73ae250eU), bswap_32big(0x7b63ff59U),
                       bswap_32big(0x2591b811U));
    }

    WR1_PROG(REG_1444H, 0x000006c7U);
    WR1_PROG(REG_1608H, 0x800702c0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_KeyCertificateLength[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    for (iLoop = 0; iLoop < 4; iLoop = iLoop + 1)
    {
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_KeyCertificatePubKey[iLoop + 0]);
        WR1_PROG(REG_1458H, 0x00000000U);
    }

    for (iLoop = 0; iLoop < 2; iLoop = iLoop + 1)
    {
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_ImgPkHash[iLoop + 0]);
        WR1_PROG(REG_1458H, 0x00000000U);
    }

    WR1_PROG(REG_1600H, 0x00000bffU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x3c002af8U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x1000d3e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x3c002b19U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x1000d3e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x3c002b3aU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x1000d3e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x3c002b5bU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x1000d3e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x3c002b7cU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x1000d3e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x3c002b96U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x1000d3e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00003417U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000a400U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000001fU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x08002818U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x2000d3e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00003419U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000a400U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000001fU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0800281aU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x2000d3e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000341bU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000a400U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000001fU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0800281cU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x2000d3e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000dceU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00260000U);
    r_rsip_func100(bswap_32big(0x2cb2e81cU),
                   bswap_32big(0x68c4a1daU),
                   bswap_32big(0x600090d8U),
                   bswap_32big(0xff4ed76bU));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        WR1_PROG(REG_1600H, 0x3c002a11U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x3c002a32U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x3c002a53U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x3c002a6fU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00003410U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000a400U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000001fU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x08002811U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x2000d3e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00003412U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000a400U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000001fU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x08002813U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x2000d3e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func101(bswap_32big(0xd3c6ef09U), bswap_32big(0x6274fb37U), bswap_32big(0xe4ea444aU),
                       bswap_32big(0x1e5878a7U));
    }
    else
    {
        WR1_PROG(REG_1600H, 0x3c002a11U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x3c002a32U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x3c002a53U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x3c002a74U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x3c002a95U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x3c002aafU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x1000d3e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00003410U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000a400U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000001fU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x08002811U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x2000d3e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00003412U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000a400U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000001fU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x08002813U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x2000d3e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00003414U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000a400U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x0000001fU);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x08002815U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x2000d3e0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func101(bswap_32big(0xd28e1fe8U), bswap_32big(0x9abffdc0U), bswap_32big(0x1f6d4db1U),
                       bswap_32big(0xeeeb0351U));
    }

    WR1_PROG(REG_1600H, 0x38000fffU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);
    r_rsip_func100(bswap_32big(0x2989c43bU),
                   bswap_32big(0xda917307U),
                   bswap_32big(0x559d7e28U),
                   bswap_32big(0xc0200ebfU));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        WR1_PROG(REG_14BCH, 0x00000020U);
        WAIT_STS(REG_142CH, 12U, 0U);

        return RSIP_RET_PARAM_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0xef1eac4dU), bswap_32big(0x0ef574eeU), bswap_32big(0xc9fc5703U),
                       bswap_32big(0x284561afU));
        WR1_PROG(REG_2000H, 0x00000001U);
        WR1_PROG(REG_2004H, 0x00000050U);
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
        r_rsip_func100(bswap_32big(0x9cd242bdU), bswap_32big(0x768ac59cU), bswap_32big(0x873e5a1cU),
                       bswap_32big(0x0b354b41U));
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
            WR1_ADDR(REG_1420H, &InData_KeyCertificate[iLoop + 0]);
            WR1_ADDR(REG_1420H, &InData_KeyCertificate[iLoop + 1]);
            WR1_ADDR(REG_1420H, &InData_KeyCertificate[iLoop + 2]);
            WR1_ADDR(REG_1420H, &InData_KeyCertificate[iLoop + 3]);
            WR1_PROG(REG_1600H, 0x0000a4a0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00000004U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x869b7f9cU), bswap_32big(0x8a709d7aU), bswap_32big(0x93fbeb3fU),
                           bswap_32big(0xb7d560b1U));
        }

        r_rsip_func100(bswap_32big(0x47cbc193U), bswap_32big(0xe46ada41U), bswap_32big(0x9311e64eU),
                       bswap_32big(0xb96dc055U));
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
        WR1_PROG(REG_1600H, 0x00026800U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x38008ec0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000003U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x20002c00U);
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
        WR1_PROG(REG_1600H, 0x0000b520U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1600H, 0x00000180U);
        WR1_PROG(REG_1458H, 0x00000000U);
        for ( ; iLoop < S_RAM[0]; iLoop = iLoop + 1)
        {
            WR1_PROG(REG_1444H, 0x000000c7U);
            WR1_PROG(REG_1608H, 0x80010100U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_KeyCertificate[iLoop + 0]);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x0000b420U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00000004U);
            WR1_PROG(REG_1458H, 0x00000000U);
            for (jLoop = 0; jLoop < 4; jLoop = jLoop + 1)
            {
                WR1_PROG(REG_1600H, 0x00003020U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x01886ce8U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00086d08U);
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
                r_rsip_func100(bswap_32big(0x7b0e6d4cU),
                               bswap_32big(0xa3972a4eU),
                               bswap_32big(0x09de0460U),
                               bswap_32big(0xc5252e4cU));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    WR1_PROG(REG_1608H, 0x810100e0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1400H, 0x1009000dU);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x10c90005U);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    r_rsip_func101(bswap_32big(0x29a0a469U),
                                   bswap_32big(0xdf3ad926U),
                                   bswap_32big(0x347f27f9U),
                                   bswap_32big(0xddfb2d4eU));
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
                r_rsip_func100(bswap_32big(0xef521106U),
                               bswap_32big(0x15ac7d1bU),
                               bswap_32big(0x0f81eac6U),
                               bswap_32big(0xab47009bU));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    WR1_PROG(REG_1608H, 0x810100e0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1400H, 0x1009000dU);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x10c90005U);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    r_rsip_func101(bswap_32big(0x71d0a370U),
                                   bswap_32big(0xfb634ae6U),
                                   bswap_32big(0x0c7da214U),
                                   bswap_32big(0x34b81915U));
                }

                WR1_PROG(REG_1600H, 0x00000863U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x3c00285bU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x20002c60U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x3c002b82U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x20002c60U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x38000c63U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                r_rsip_func100(bswap_32big(0x8d4ebf49U),
                               bswap_32big(0xf3d67444U),
                               bswap_32big(0x4b4fa255U),
                               bswap_32big(0xd764b6adU));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    WR1_PROG(REG_1600H, 0x02003ce9U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00002d20U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0x6f010e3bU),
                                   bswap_32big(0x73b3b2d4U),
                                   bswap_32big(0x79656042U),
                                   bswap_32big(0xd38de857U));
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
                r_rsip_func100(bswap_32big(0xfc73c109U),
                               bswap_32big(0xad9ab29cU),
                               bswap_32big(0x55e6d79cU),
                               bswap_32big(0x10ea9de1U));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    WR1_PROG(REG_1608H, 0x810100e0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1400H, 0x1009000dU);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1400H, 0x11490005U);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    r_rsip_func101(bswap_32big(0x73aeb09eU),
                                   bswap_32big(0x45e9342fU),
                                   bswap_32big(0xa1600bfcU),
                                   bswap_32big(0x7206e7ecU));
                }

                WR1_PROG(REG_1600H, 0x00002c40U);
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func101(bswap_32big(0xdc8b6cddU),
                               bswap_32big(0xeb6804e1U),
                               bswap_32big(0x64bfeb35U),
                               bswap_32big(0xa6d0cdfcU));
            }

            WR1_PROG(REG_1600H, 0x08000c21U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00260000U);
            WR1_PROG(REG_143CH, 0x00402000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00002ca0U);
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x4a4e0315U), bswap_32big(0xf10528d9U), bswap_32big(0xb9308e4fU),
                           bswap_32big(0x79b7e9edU));
        }

        WR1_PROG(REG_1600H, 0x38000805U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        r_rsip_func100(bswap_32big(0x8e3f5981U), bswap_32big(0x6302baa4U), bswap_32big(0xe2e4e896U),
                       bswap_32big(0xaece1081U));
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
            r_rsip_func101(bswap_32big(0x9adf351bU), bswap_32big(0x68999105U), bswap_32big(0x0f95b94aU),
                           bswap_32big(0xf6651636U));
        }

        WR1_PROG(REG_1600H, 0x38000845U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x00000080U);
        WR1_PROG(REG_143CH, 0x00260000U);
        WR1_PROG(REG_143CH, 0x00402000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WAIT_STS(REG_2030H, 4U, 1U);
        WR1_PROG(REG_1600H, 0x00000929U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1608H, 0x80880009U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1400H, 0x03450021U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_2000H, 0x00000001U);
        WR1_PROG(REG_2004H, 0x00000050U);
        WR1_PROG(REG_2014H, 0x00000000U);
        WR1_PROG(REG_2010H, 0x00000200U);
        WR1_PROG(REG_1404H, 0x10000000U);
        WR1_PROG(REG_1400H, 0x01430041U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WAIT_STS(REG_2030H, 4U, 1U);
        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A24H, 0x08000055U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_OemRootPkHash[0]);
        WR1_ADDR(REG_1420H, &InData_OemRootPkHash[1]);
        WR1_ADDR(REG_1420H, &InData_OemRootPkHash[2]);
        WR1_ADDR(REG_1420H, &InData_OemRootPkHash[3]);
        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00850011U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        WR1_PROG(REG_1444H, 0x000003c2U);
        WR1_PROG(REG_1A24H, 0x08000055U);
        WAIT_STS(REG_1444H, 31U, 1U);
        WR1_ADDR(REG_1420H, &InData_OemRootPkHash[4]);
        WR1_ADDR(REG_1420H, &InData_OemRootPkHash[5]);
        WR1_ADDR(REG_1420H, &InData_OemRootPkHash[6]);
        WR1_ADDR(REG_1420H, &InData_OemRootPkHash[7]);
        WR1_PROG(REG_1A24H, 0x9c100005U);
        WR1_PROG(REG_1400H, 0x00850011U);
        WAIT_STS(REG_1404H, 30U, 0U);
        WR1_PROG(REG_143CH, 0x00001800U);
        r_rsip_func100(bswap_32big(0xe69c9af9U), bswap_32big(0xbd3ef66eU), bswap_32big(0xbbd5e13dU),
                       bswap_32big(0x8223e93dU));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            WR1_PROG(REG_14BCH, 0x00000020U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_VERIFICATION_FAIL;
        }
        else
        {
            WR1_PROG(REG_1404H, 0x10000000U);
            WR1_PROG(REG_1600H, 0x0000b420U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x00000060U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x80900001U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1400H, 0x03430041U);
            WAIT_STS(REG_1404H, 30U, 0U);
            WR1_PROG(REG_143CH, 0x00001800U);
            WR1_PROG(REG_1600H, 0x00000b9cU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1444H, 0x000000a7U);
            WR1_PROG(REG_1608H, 0x80010360U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_PROG(REG_1420H, bswap_32big(0x000000e2U));
            WR1_PROG(REG_1458H, 0x00000000U);
            r_rsip_func101(bswap_32big(0x9023b9d1U), bswap_32big(0xc8fc4896U), bswap_32big(0x233d4762U),
                           bswap_32big(0xcd6af04eU));
            r_rsip_func400(InData_KeyCertificateSignature);
            r_rsip_func100(bswap_32big(0xb953b8a7U), bswap_32big(0xab949b4cU), bswap_32big(0x6beba32bU),
                           bswap_32big(0xbfcd3558U));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                WR1_PROG(REG_14BCH, 0x00000020U);
                WAIT_STS(REG_142CH, 12U, 0U);

                return RSIP_RET_VERIFICATION_FAIL;
            }
            else
            {
                WR1_PROG(REG_1600H, 0x000036cfU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x000036f0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003711U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003732U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003753U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003774U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003795U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_2000H, 0x00000001U);
                WR1_PROG(REG_2004H, 0x00000050U);
                WR1_PROG(REG_1444H, 0x000000c7U);
                WR1_PROG(REG_1608H, 0x80010160U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &MAX_CNT);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x38000dceU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                r_rsip_func100(bswap_32big(0xcf9ea94cU),
                               bswap_32big(0x5ad646e6U),
                               bswap_32big(0x148dd7d0U),
                               bswap_32big(0x67d27bb7U));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    WR1_PROG(REG_1600H, 0x00000800U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x0000342bU);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x01826c01U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00026c21U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x000008c6U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x0c002436U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00802406U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x01836c01U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00036c21U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0xb58d66adU),
                                   bswap_32big(0x339ba95fU),
                                   bswap_32big(0xbffb66d3U),
                                   bswap_32big(0xa9f4b9e3U));
                }
                else
                {
                    WR1_PROG(REG_1600H, 0x00000800U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00003436U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x01836c01U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00036c21U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0x9d210b5aU),
                                   bswap_32big(0x3f1430c4U),
                                   bswap_32big(0x71e40447U),
                                   bswap_32big(0x06d78ea9U));
                }

                r_rsip_func100(bswap_32big(0xe864d971U),
                               bswap_32big(0x8501f68bU),
                               bswap_32big(0x366d0fdeU),
                               bswap_32big(0xbdee7ed8U));
                WR1_PROG(REG_1608H, 0x81020000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1408H, 0x0000500aU);
                WAIT_STS(REG_1408H, 30U, 1U);
                RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[0]);
                WAIT_STS(REG_1408H, 30U, 1U);
                RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[1]);
                r_rsip_func100(bswap_32big(0x37aecaabU),
                               bswap_32big(0xe63d78a8U),
                               bswap_32big(0x128c910bU),
                               bswap_32big(0xc63ed7c2U));
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
                    WR1_ADDR(REG_1420H, &InData_CodeCertificate[iLoop + 0]);
                    WR1_ADDR(REG_1420H, &InData_CodeCertificate[iLoop + 1]);
                    WR1_ADDR(REG_1420H, &InData_CodeCertificate[iLoop + 2]);
                    WR1_ADDR(REG_1420H, &InData_CodeCertificate[iLoop + 3]);
                    WR1_PROG(REG_1600H, 0x0000a4a0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00000004U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0x6804bb1cU),
                                   bswap_32big(0xc9b6eb85U),
                                   bswap_32big(0x253936b7U),
                                   bswap_32big(0xd933909cU));
                }

                r_rsip_func100(bswap_32big(0xfca26eb6U),
                               bswap_32big(0x8ec351b6U),
                               bswap_32big(0xa8836ac3U),
                               bswap_32big(0x9532c1b5U));
                WR1_PROG(REG_1600H, 0x38000805U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1404H, 0x10000000U);
                WR1_PROG(REG_1600H, 0x00003416U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00026800U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x38008ec0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000003U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x20002c00U);
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
                WR1_PROG(REG_1600H, 0x0000b520U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x000001a0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                for ( ; iLoop < S_RAM[0]; iLoop = iLoop + 1)
                {
                    WR1_PROG(REG_1444H, 0x000000c7U);
                    WR1_PROG(REG_1608H, 0x80010100U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_ADDR(REG_1420H, &InData_CodeCertificate[iLoop + 0]);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x0000b420U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00000004U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    for (jLoop = 0; jLoop < 4; jLoop = jLoop + 1)
                    {
                        WR1_PROG(REG_1600H, 0x00003020U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x01886ce8U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00086d08U);
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
                        r_rsip_func100(bswap_32big(0x0bfe6c9eU),
                                       bswap_32big(0x5871144bU),
                                       bswap_32big(0x51830adcU),
                                       bswap_32big(0x7b5eee79U));
                        WR1_PROG(REG_143CH, 0x00400000U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        if (CHCK_STS(REG_143CH, 22U, 1U))
                        {
                            WR1_PROG(REG_1608H, 0x810100e0U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1400H, 0x1009000dU);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1400H, 0x10c90005U);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            r_rsip_func101(bswap_32big(0x520cd252U),
                                           bswap_32big(0xdf15f5ddU),
                                           bswap_32big(0xfedeba6fU),
                                           bswap_32big(0x6d10831eU));
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
                        r_rsip_func100(bswap_32big(0x8273ff65U),
                                       bswap_32big(0x140fdbc6U),
                                       bswap_32big(0xe3591b6dU),
                                       bswap_32big(0x9f3d7eecU));
                        WR1_PROG(REG_143CH, 0x00400000U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        if (CHCK_STS(REG_143CH, 22U, 1U))
                        {
                            WR1_PROG(REG_1608H, 0x810100e0U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1400H, 0x1009000dU);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1400H, 0x10c90005U);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            r_rsip_func101(bswap_32big(0x4ccdecadU),
                                           bswap_32big(0xa309ae47U),
                                           bswap_32big(0xb559d2e0U),
                                           bswap_32big(0x5702a666U));
                        }

                        WR1_PROG(REG_1600H, 0x00000863U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x38000dceU);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00020020U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x3c00285bU);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x3c002b82U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x20002c60U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00000060U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00002c60U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00000080U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x38000c63U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);
                        r_rsip_func100(bswap_32big(0x64bffa22U),
                                       bswap_32big(0x6aa6b54dU),
                                       bswap_32big(0x8f21945fU),
                                       bswap_32big(0x71e39b15U));
                        WR1_PROG(REG_143CH, 0x00400000U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        if (CHCK_STS(REG_143CH, 22U, 1U))
                        {
                            WR1_PROG(REG_1600H, 0x02003ce9U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x00002d20U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            r_rsip_func101(bswap_32big(0xa980c268U),
                                           bswap_32big(0xe4aa01e4U),
                                           bswap_32big(0x5de9092dU),
                                           bswap_32big(0xbf6969b3U));
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
                        r_rsip_func100(bswap_32big(0x83832c33U),
                                       bswap_32big(0x40ec33a9U),
                                       bswap_32big(0x665c49d8U),
                                       bswap_32big(0xa9718520U));
                        WR1_PROG(REG_143CH, 0x00400000U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        if (CHCK_STS(REG_143CH, 22U, 1U))
                        {
                            WR1_PROG(REG_1608H, 0x810100e0U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1400H, 0x1009000dU);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1400H, 0x11490005U);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            r_rsip_func101(bswap_32big(0xa6c8944eU),
                                           bswap_32big(0xa58978abU),
                                           bswap_32big(0x6146669cU),
                                           bswap_32big(0x9877e191U));
                        }

                        WR1_PROG(REG_1600H, 0x00002c40U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        r_rsip_func101(bswap_32big(0x9ab79e7fU),
                                       bswap_32big(0x11c71759U),
                                       bswap_32big(0x62a30a52U),
                                       bswap_32big(0x9cff01f7U));
                    }

                    WR1_PROG(REG_1600H, 0x08000c21U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);
                    WR1_PROG(REG_143CH, 0x00402000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00002ca0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0x706c312bU),
                                   bswap_32big(0x89e84a68U),
                                   bswap_32big(0x95cbfc07U),
                                   bswap_32big(0x9c0ce9d7U));
                }

                WR1_PROG(REG_1600H, 0x38000805U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x38000dceU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                r_rsip_func100(bswap_32big(0x30f3c708U),
                               bswap_32big(0x9955f7baU),
                               bswap_32big(0x39050959U),
                               bswap_32big(0x3d3bb396U));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    r_rsip_func100(bswap_32big(0xe8925147U),
                                   bswap_32big(0x1fe1704bU),
                                   bswap_32big(0x692308f9U),
                                   bswap_32big(0xc5e59c5aU));
                    WR1_PROG(REG_1444H, 0x000000c7U);
                    WR1_PROG(REG_1608H, 0x800100c0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_ADDR(REG_1420H, &InData_Image[0]);
                    WR1_PROG(REG_1458H, 0x00000000U);
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
                    WR1_PROG(REG_1608H, 0x81010040U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1408H, 0x00005006U);
                    WAIT_STS(REG_1408H, 30U, 1U);
                    RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[0]);
                    WR1_PROG(REG_1600H, 0x000008a5U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00003466U);
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
                        r_rsip_func101(bswap_32big(0xc5c491c0U),
                                       bswap_32big(0xfed3874dU),
                                       bswap_32big(0x44372073U),
                                       bswap_32big(0xc9daa83eU));
                    }

                    WR1_PROG(REG_1600H, 0x38000845U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);
                    WR1_PROG(REG_143CH, 0x00402000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func100(bswap_32big(0xfae6c118U),
                                   bswap_32big(0x0aa511edU),
                                   bswap_32big(0xd84225ceU),
                                   bswap_32big(0xbc395b07U));
                    WR1_PROG(REG_1600H, 0x000034e6U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00036c00U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00004400U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1608H, 0x81010160U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1408H, 0x00005006U);
                    WAIT_STS(REG_1408H, 30U, 1U);
                    RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[0]);
                    WR1_PROG(REG_1600H, 0x0000b4a0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00000001U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    for (iLoop = 1; iLoop < S_RAM[0]; iLoop = iLoop + 1)
                    {
                        WR1_PROG(REG_1444H, 0x000000c7U);
                        WR1_PROG(REG_1608H, 0x800100c0U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WAIT_STS(REG_1444H, 31U, 1U);
                        WR1_ADDR(REG_1420H, &InData_Image[iLoop + 0]);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00003506U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x01807507U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1608H, 0x81010100U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1400H, 0x01490005U);
                        WAIT_STS(REG_1404H, 30U, 0U);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        WR1_PROG(REG_1600H, 0x000034e6U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x00002ca0U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        r_rsip_func101(bswap_32big(0x877ac269U),
                                       bswap_32big(0x8b503587U),
                                       bswap_32big(0x363aeb91U),
                                       bswap_32big(0x6836bbceU));
                    }

                    WR1_PROG(REG_1600H, 0x38000965U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);
                    WR1_PROG(REG_143CH, 0x00402000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x38008ec0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00000003U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00A60000U);
                    r_rsip_func100(bswap_32big(0xc104f22dU),
                                   bswap_32big(0x0fd13c77U),
                                   bswap_32big(0xa2f08f34U),
                                   bswap_32big(0x7b720c70U));
                    WR1_PROG(REG_143CH, 0x00400000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    if (CHCK_STS(REG_143CH, 22U, 1U))
                    {
                        WR1_PROG(REG_1600H, 0x00000908U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1600H, 0x01807507U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1608H, 0x81010100U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1400H, 0x01490005U);
                        WAIT_STS(REG_1404H, 30U, 0U);
                        WR1_PROG(REG_143CH, 0x00001800U);
                        r_rsip_func101(bswap_32big(0xf4da8b14U),
                                       bswap_32big(0x19fcbe47U),
                                       bswap_32big(0x3b8caf0bU),
                                       bswap_32big(0x6f159372U));
                    }

                    WAIT_STS(REG_2030H, 4U, 1U);
                    r_rsip_func101(bswap_32big(0x3cb31b78U),
                                   bswap_32big(0x0523f1c5U),
                                   bswap_32big(0xaab6199aU),
                                   bswap_32big(0x51048b28U));
                }
                else
                {
                    r_rsip_func100(bswap_32big(0x65642762U),
                                   bswap_32big(0x8f3c3afbU),
                                   bswap_32big(0xf48cf779U),
                                   bswap_32big(0xefcd64feU));
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
                        r_rsip_func101(bswap_32big(0x67584ed4U),
                                       bswap_32big(0x6014f758U),
                                       bswap_32big(0x37524adbU),
                                       bswap_32big(0xc133d905U));
                    }

                    WR1_PROG(REG_1600H, 0x38000845U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1608H, 0x00000080U);
                    WR1_PROG(REG_143CH, 0x00260000U);
                    WR1_PROG(REG_143CH, 0x00402000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WAIT_STS(REG_2030H, 4U, 1U);
                    r_rsip_func101(bswap_32big(0x2fa60dcdU),
                                   bswap_32big(0x4ec6d4c7U),
                                   bswap_32big(0x00e1ceb1U),
                                   bswap_32big(0xe78a03f2U));
                }

                WR1_PROG(REG_1600H, 0x00000929U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x80880009U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1400H, 0x03450021U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_2000H, 0x00000001U);
                WR1_PROG(REG_2004H, 0x00000050U);
                WR1_PROG(REG_2014H, 0x00000000U);
                WR1_PROG(REG_2010H, 0x00000200U);
                WR1_PROG(REG_1404H, 0x10000000U);
                WR1_PROG(REG_1400H, 0x01430041U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WAIT_STS(REG_2030H, 4U, 1U);
                WR1_PROG(REG_1600H, 0x0000b520U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000180U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1A24H, 0x08000045U);
                WR1_PROG(REG_1608H, 0x81840009U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1400H, 0x00890011U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1A24H, 0x9c000005U);
                WR1_PROG(REG_1400H, 0x00850011U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1600H, 0x0000a520U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000010U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1A24H, 0x08000045U);
                WR1_PROG(REG_1608H, 0x81840009U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1400H, 0x00890011U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1A24H, 0x9c000005U);
                WR1_PROG(REG_1400H, 0x00850011U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                r_rsip_func100(bswap_32big(0xe24aa5eeU),
                               bswap_32big(0x3593df98U),
                               bswap_32big(0xebb695f3U),
                               bswap_32big(0x2a5172c8U));
                WR1_PROG(REG_143CH, 0x00400000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                if (CHCK_STS(REG_143CH, 22U, 1U))
                {
                    WR1_PROG(REG_14BCH, 0x00000020U);
                    WAIT_STS(REG_142CH, 12U, 0U);

                    return RSIP_RET_VERIFICATION_FAIL;
                }
                else
                {
                    WR1_PROG(REG_1404H, 0x10000000U);
                    WR1_PROG(REG_1600H, 0x0000b420U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00000060U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1608H, 0x80900001U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1400H, 0x03430041U);
                    WAIT_STS(REG_1404H, 30U, 0U);
                    WR1_PROG(REG_143CH, 0x00001800U);
                    WR1_PROG(REG_1600H, 0x00000b9cU);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1444H, 0x000000a7U);
                    WR1_PROG(REG_1608H, 0x80010360U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WAIT_STS(REG_1444H, 31U, 1U);
                    WR1_PROG(REG_1420H, bswap_32big(0x000000e3U));
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0x34faefb6U),
                                   bswap_32big(0x9f909cbeU),
                                   bswap_32big(0x8b9ecdaeU),
                                   bswap_32big(0x40842ceaU));
                    r_rsip_func400(InData_CodeCertificateSignature);
                    r_rsip_func100(bswap_32big(0xcb389a06U),
                                   bswap_32big(0xde488e50U),
                                   bswap_32big(0x9daab272U),
                                   bswap_32big(0xc356ac1eU));
                    WR1_PROG(REG_143CH, 0x00400000U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    if (CHCK_STS(REG_143CH, 22U, 1U))
                    {
                        WR1_PROG(REG_14BCH, 0x00000020U);
                        WAIT_STS(REG_142CH, 12U, 0U);

                        return RSIP_RET_VERIFICATION_FAIL;
                    }
                    else
                    {
                        WR1_PROG(REG_1600H, 0x38000dceU);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        WR1_PROG(REG_1608H, 0x00000080U);
                        WR1_PROG(REG_143CH, 0x00260000U);
                        r_rsip_func100(bswap_32big(0x77b69809U),
                                       bswap_32big(0x3f47a2b3U),
                                       bswap_32big(0x56af5bb4U),
                                       bswap_32big(0xc1f7ea05U));
                        WR1_PROG(REG_143CH, 0x00400000U);
                        WR1_PROG(REG_1458H, 0x00000000U);
                        if (CHCK_STS(REG_143CH, 22U, 1U))
                        {
                            r_rsip_func102(bswap_32big(0x5d4b8ae7U),
                                           bswap_32big(0xfea68d7fU),
                                           bswap_32big(0x15dbe600U),
                                           bswap_32big(0xdef202b0U));
                            WR1_PROG(REG_14BCH, 0x00000040U);
                            WAIT_STS(REG_142CH, 12U, 0U);

                            return RSIP_RET_PASS;
                        }
                        else
                        {
                            r_rsip_func100(bswap_32big(0x3304ceabU),
                                           bswap_32big(0x7a1760dcU),
                                           bswap_32big(0x26ed3215U),
                                           bswap_32big(0x8977c58eU));
                            WR1_PROG(REG_2000H, 0x00000001U);
                            WR1_PROG(REG_2004H, 0x00000050U);
                            WR1_PROG(REG_1600H, 0x00000800U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x0000342bU);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x01856c01U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x00056c21U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1608H, 0x81020000U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1408H, 0x0000500aU);
                            WAIT_STS(REG_1408H, 30U, 1U);
                            RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[0]);
                            WAIT_STS(REG_1408H, 30U, 1U);
                            RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[1]);
                            r_rsip_func100(bswap_32big(0x3cf5342fU),
                                           bswap_32big(0x8c26018cU),
                                           bswap_32big(0x3339a6d0U),
                                           bswap_32big(0xc0f22ca7U));
                            WR1_PROG(REG_1444H, 0x00000040U);
                            WR1_ADDR(REG_2014H, &S_RAM[0]);
                            WR1_PROG(REG_1444H, 0x00000040U);
                            WR1_ADDR(REG_2010H, &S_RAM[1]);
                            WR1_PROG(REG_1608H, 0x81010160U);
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
                                WR1_ADDR(REG_1420H, &InData_Image[iLoop + 0]);
                                WR1_ADDR(REG_1420H, &InData_Image[iLoop + 1]);
                                WR1_ADDR(REG_1420H, &InData_Image[iLoop + 2]);
                                WR1_ADDR(REG_1420H, &InData_Image[iLoop + 3]);
                                WR1_PROG(REG_1600H, 0x0000a4a0U);
                                WR1_PROG(REG_1458H, 0x00000000U);
                                WR1_PROG(REG_1600H, 0x00000004U);
                                WR1_PROG(REG_1458H, 0x00000000U);
                                r_rsip_func101(bswap_32big(0xd3af9973U), bswap_32big(0x5d0f7063U),
                                               bswap_32big(0x7a46529aU), bswap_32big(0xcb6b1b53U));
                            }

                            WR1_PROG(REG_1600H, 0x38000965U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1608H, 0x00000080U);
                            WR1_PROG(REG_143CH, 0x00260000U);
                            WR1_PROG(REG_143CH, 0x00402000U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WAIT_STS(REG_2030H, 4U, 1U);
                            WR1_PROG(REG_1600H, 0x0000b520U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x000001a0U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1A24H, 0x08000045U);
                            WR1_PROG(REG_1608H, 0x81840009U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1400H, 0x00890011U);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1A24H, 0x9c000005U);
                            WR1_PROG(REG_1400H, 0x00850011U);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1600H, 0x0000a520U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1600H, 0x00000010U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1A24H, 0x08000045U);
                            WR1_PROG(REG_1608H, 0x81840009U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            WR1_PROG(REG_1400H, 0x00890011U);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            WR1_PROG(REG_1A24H, 0x9c000005U);
                            WR1_PROG(REG_1400H, 0x00850011U);
                            WAIT_STS(REG_1404H, 30U, 0U);
                            WR1_PROG(REG_143CH, 0x00001800U);
                            r_rsip_func100(bswap_32big(0x181f4f84U),
                                           bswap_32big(0x30c1b8c7U),
                                           bswap_32big(0xf2fb6879U),
                                           bswap_32big(0xe7a4188fU));
                            WR1_PROG(REG_143CH, 0x00400000U);
                            WR1_PROG(REG_1458H, 0x00000000U);
                            if (CHCK_STS(REG_143CH, 22U, 1U))
                            {
                                WR1_PROG(REG_14BCH, 0x00000020U);
                                WAIT_STS(REG_142CH, 12U, 0U);

                                return RSIP_RET_VERIFICATION_FAIL;
                            }
                            else
                            {
                                r_rsip_func102(bswap_32big(0x57d10172U), bswap_32big(0xf1e9976fU),
                                               bswap_32big(0x48002bbbU), bswap_32big(0x4c2fe7b2U));
                                WR1_PROG(REG_14BCH, 0x00000040U);
                                WAIT_STS(REG_142CH, 12U, 0U);

                                return RSIP_RET_PASS;
                            }
                        }
                    }
                }
            }
        }
    }
}
