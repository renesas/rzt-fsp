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

rsip_ret_t r_rsip_pb3f (const uint32_t InData_TextBitLen[], const uint32_t InData_Text[], uint32_t OutData_Text[])
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
    WR1_PROG(REG_1444H, 0x000000c7U);
    WR1_PROG(REG_1608H, 0x80010000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_TextBitLen[0]);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x000037c0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00076bdeU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00026fdeU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000bffU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38008c00U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x0000007fU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00020020U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x3420a800U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x1000d3e0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x2000abc0U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000004U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x00000080U);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1600H, 0x38000fffU);
    WR1_PROG(REG_1458H, 0x00000000U);
    WR1_PROG(REG_1608H, 0x00000080U);
    WR1_PROG(REG_143CH, 0x00A60000U);
    r_rsip_func100(bswap_32big(0x7de824c4U),
                   bswap_32big(0x773e1754U),
                   bswap_32big(0x2c744eabU),
                   bswap_32big(0x200c47baU));
    WR1_PROG(REG_143CH, 0x00400000U);
    WR1_PROG(REG_1458H, 0x00000000U);
    if (CHCK_STS(REG_143CH, 22U, 1U))
    {
        r_rsip_func102(bswap_32big(0x72826003U), bswap_32big(0x1f521b1cU), bswap_32big(0xeb270b38U),
                       bswap_32big(0xb8e4675dU));
        WR1_PROG(REG_14BCH, 0x00000040U);
        WAIT_STS(REG_142CH, 12U, 0U);

        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func100(bswap_32big(0x615b5d68U), bswap_32big(0x80a1f412U), bswap_32big(0xc8a3c287U),
                       bswap_32big(0x4a593aa8U));
        WR1_PROG(REG_1608H, 0x810103c0U);
        WR1_PROG(REG_1458H, 0x00000000U);
        WR1_PROG(REG_1408H, 0x00005006U);
        WAIT_STS(REG_1408H, 30U, 1U);
        RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[0]);
        r_rsip_func100(bswap_32big(0xae000f82U), bswap_32big(0xee6d8bc3U), bswap_32big(0xa7935bebU),
                       bswap_32big(0x75e6a5d6U));
        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x00000020U);
        WR1_PROG(REG_1824H, 0x0d008906U);
        WR1_PROG(REG_1408H, 0x000c1000U);
        iLoop = 0;
        if (S_RAM[0] >= 4)
        {
            WAIT_STS(REG_1444H, 31U, 1U);
            WR1_ADDR(REG_1420H, &InData_Text[0]);
            WR1_ADDR(REG_1420H, &InData_Text[1]);
            WR1_ADDR(REG_1420H, &InData_Text[2]);
            WR1_ADDR(REG_1420H, &InData_Text[3]);
            for (iLoop = 4; iLoop < S_RAM[0]; iLoop = iLoop + 4)
            {
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_Text[iLoop + 0]);
                WR1_ADDR(REG_1420H, &InData_Text[iLoop + 1]);
                WR1_ADDR(REG_1420H, &InData_Text[iLoop + 2]);
                WR1_ADDR(REG_1420H, &InData_Text[iLoop + 3]);
                WAIT_STS(REG_1408H, 30U, 1U);
                RD1_ADDR(REG_1420H, &OutData_Text[iLoop - 4]);
                RD1_ADDR(REG_1420H, &OutData_Text[iLoop - 3]);
                RD1_ADDR(REG_1420H, &OutData_Text[iLoop - 2]);
                RD1_ADDR(REG_1420H, &OutData_Text[iLoop - 1]);
            }

            WAIT_STS(REG_1408H, 30U, 1U);
            RD1_ADDR(REG_1420H, &OutData_Text[iLoop - 4]);
            RD1_ADDR(REG_1420H, &OutData_Text[iLoop - 3]);
            RD1_ADDR(REG_1420H, &OutData_Text[iLoop - 2]);
            RD1_ADDR(REG_1420H, &OutData_Text[iLoop - 1]);
        }

        r_rsip_func206();
        r_rsip_func100(bswap_32big(0x5a019f7eU), bswap_32big(0x5f863d58U), bswap_32big(0xcb3a7d4eU),
                       bswap_32big(0x40a4fccaU));
        WR1_PROG(REG_143CH, 0x00400000U);
        WR1_PROG(REG_1458H, 0x00000000U);
        if (CHCK_STS(REG_143CH, 22U, 1U))
        {
            r_rsip_func102(bswap_32big(0x8c142fadU), bswap_32big(0x88259ebfU), bswap_32big(0xb384462cU),
                           bswap_32big(0x03739aacU));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_FAIL;
        }
        else
        {
            WR1_PROG(REG_1600H, 0x38008c00U);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1600H, 0x0000007fU);
            WR1_PROG(REG_1458H, 0x00000000U);
            WR1_PROG(REG_1608H, 0x00000080U);
            WR1_PROG(REG_143CH, 0x00A60000U);
            r_rsip_func100(bswap_32big(0xac7862d2U), bswap_32big(0x65d28b0cU), bswap_32big(0x5973513cU),
                           bswap_32big(0xe8677c90U));
            WR1_PROG(REG_143CH, 0x00400000U);
            WR1_PROG(REG_1458H, 0x00000000U);
            if (CHCK_STS(REG_143CH, 22U, 1U))
            {
                WR1_PROG(REG_1444H, 0x000003c1U);
                WR1_PROG(REG_182CH, 0x00000020U);
                WR1_PROG(REG_1824H, 0x0d008905U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_Text[iLoop + 0]);
                WR1_ADDR(REG_1420H, &InData_Text[iLoop + 1]);
                WR1_ADDR(REG_1420H, &InData_Text[iLoop + 2]);
                WR1_ADDR(REG_1420H, &InData_Text[iLoop + 3]);
                WR1_PROG(REG_1600H, 0x000008c6U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x80840006U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1400H, 0x03410011U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000010U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1444H, 0x000003c7U);
                WR1_PROG(REG_1608H, 0x80840007U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_Text[iLoop + 4]);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_Text[iLoop + 5]);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_Text[iLoop + 6]);
                WR1_PROG(REG_1458H, 0x00000000U);
                WAIT_STS(REG_1444H, 31U, 1U);
                WR1_ADDR(REG_1420H, &InData_Text[iLoop + 7]);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000b4a0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000004U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003500U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00036908U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00008d00U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000000cU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x000024c8U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x000024e8U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003826U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003847U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003460U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00008c60U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000001fU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000b480U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0xffffffffU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00004403U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00007484U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000c24U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00001484U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000c44U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00001041U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003c47U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x000037e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00008fe0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000007fU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x38008fe0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000001fU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x1000a7e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000020U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000b7c0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000080U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00002bdfU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00056bdeU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x0000353eU);
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func100(bswap_32big(0xcf0ae079U),
                               bswap_32big(0xa6e02c49U),
                               bswap_32big(0x68f3ffe2U),
                               bswap_32big(0x3fc9687aU));
                WR1_PROG(REG_1608H, 0x810103c0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1408H, 0x00005006U);
                WAIT_STS(REG_1408H, 30U, 1U);
                RD1_ADDR(bswap_32big(REG_1420H), &S_RAM[0]);
                for (jLoop = 0; jLoop < S_RAM[0]; jLoop = jLoop + 1)
                {
                    WR1_PROG(REG_1600H, 0x000024c5U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x000024e5U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00003ba6U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00003fa7U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x000033c0U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0xb7c4ff42U),
                                   bswap_32big(0x07d25088U),
                                   bswap_32big(0xf3dcc470U),
                                   bswap_32big(0x7c7cf77fU));
                }

                WR1_PROG(REG_1600H, 0x38000fdeU);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                r_rsip_func100(bswap_32big(0x256db8beU),
                               bswap_32big(0xfc06eec6U),
                               bswap_32big(0x0ae72861U),
                               bswap_32big(0x8c1f535aU));
                WR1_PROG(REG_1600H, 0x0000b4e0U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000010U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_182CH, 0x00000020U);
                WR1_PROG(REG_1824H, 0x0d008905U);
                WR1_PROG(REG_1608H, 0x81840007U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1400H, 0x00490011U);
                WAIT_STS(REG_1404H, 30U, 0U);
                WR1_PROG(REG_143CH, 0x00001800U);
                WR1_PROG(REG_1408H, 0x00001012U);
                WAIT_STS(REG_1408H, 30U, 1U);
                RD1_ADDR(REG_1420H, &OutData_Text[iLoop]);
                RD1_ADDR(REG_1420H, &OutData_Text[iLoop + 1]);
                RD1_ADDR(REG_1420H, &OutData_Text[iLoop + 2]);
                RD1_ADDR(REG_1420H, &OutData_Text[iLoop + 3]);
                WR1_PROG(REG_1600H, 0x000008c6U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x000024c8U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003826U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000c24U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00003c26U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x00000bffU);
                WR1_PROG(REG_1458H, 0x00000000U);
                for (jLoop = 0; jLoop < S_RAM[0]; jLoop = jLoop + 1)
                {
                    WR1_PROG(REG_1600H, 0x000024c5U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00003fe6U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    WR1_PROG(REG_1600H, 0x00003120U);
                    WR1_PROG(REG_1458H, 0x00000000U);
                    r_rsip_func101(bswap_32big(0xe381307dU),
                                   bswap_32big(0x2b375a38U),
                                   bswap_32big(0x03ec77baU),
                                   bswap_32big(0x2ac5fc81U));
                }

                r_rsip_func100(bswap_32big(0x0b402419U),
                               bswap_32big(0xc6ed7814U),
                               bswap_32big(0x0b087619U),
                               bswap_32big(0x6962277dU));
                WR1_PROG(REG_1600H, 0x38000d29U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x00000080U);
                WR1_PROG(REG_143CH, 0x00260000U);
                WR1_PROG(REG_143CH, 0x00402000U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1600H, 0x000008c6U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1608H, 0x81840006U);
                WR1_PROG(REG_1458H, 0x00000000U);
                WR1_PROG(REG_1408H, 0x00005012U);
                WAIT_STS(REG_1408H, 30U, 1U);
                RD1_ADDR(REG_1420H, &OutData_Text[iLoop + 4]);
                WAIT_STS(REG_1408H, 30U, 1U);
                RD1_ADDR(REG_1420H, &OutData_Text[iLoop + 5]);
                WAIT_STS(REG_1408H, 30U, 1U);
                RD1_ADDR(REG_1420H, &OutData_Text[iLoop + 6]);
                WAIT_STS(REG_1408H, 30U, 1U);
                RD1_ADDR(REG_1420H, &OutData_Text[iLoop + 7]);
                r_rsip_func101(bswap_32big(0x10fd3f30U),
                               bswap_32big(0x17912a62U),
                               bswap_32big(0xe65e3056U),
                               bswap_32big(0xba8c052bU));
            }

            r_rsip_func102(bswap_32big(0xde0487baU), bswap_32big(0xe6fbc516U), bswap_32big(0xb577fbe2U),
                           bswap_32big(0x2531d91aU));
            WR1_PROG(REG_14BCH, 0x00000040U);
            WAIT_STS(REG_142CH, 12U, 0U);

            return RSIP_RET_PASS;
        }
    }
}
