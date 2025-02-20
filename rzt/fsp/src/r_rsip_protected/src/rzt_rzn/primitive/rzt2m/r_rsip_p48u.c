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

void r_rsip_p48u (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT)
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
    if (0x00000000U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0x23212095U), bswap_32big(0xa98b8d04U), bswap_32big(0xdda0b434U),
                       bswap_32big(0x46d22c5eU));
        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_1824H, 0x0a000106U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (0x00000001U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0x3ed66e94U), bswap_32big(0xd009a2d9U), bswap_32big(0x423f8bcdU),
                       bswap_32big(0xd5003ef9U));
        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_1824H, 0x0a00010eU);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (0x00000002U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0x4b003acfU), bswap_32big(0x7bf361feU), bswap_32big(0xd242ed04U),
                       bswap_32big(0xde78394bU));
        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_1824H, 0x0e000506U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (0x00000003U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0x4d926c55U), bswap_32big(0xce24a64aU), bswap_32big(0xef9a035aU),
                       bswap_32big(0xf1565f88U));
        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_1824H, 0x0900090eU);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (0x00000004U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0x86b5749fU), bswap_32big(0x9db7e8bbU), bswap_32big(0x7c7100b8U),
                       bswap_32big(0x7c77ed5fU));
        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_1824H, 0x07000d06U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }

    WAIT_STS(REG_1444H, 31U, 1U);
    WR1_ADDR(REG_1420H, &InData_Text[0]);
    WR1_ADDR(REG_1420H, &InData_Text[1]);
    WR1_ADDR(REG_1420H, &InData_Text[2]);
    WR1_ADDR(REG_1420H, &InData_Text[3]);
    for (iLoop = 4; iLoop < MAX_CNT; iLoop = iLoop + 4)
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
    RD1_ADDR(REG_1420H, &OutData_Text[MAX_CNT - 4]);
    RD1_ADDR(REG_1420H, &OutData_Text[MAX_CNT - 3]);
    RD1_ADDR(REG_1420H, &OutData_Text[MAX_CNT - 2]);
    RD1_ADDR(REG_1420H, &OutData_Text[MAX_CNT - 1]);
    if (0x00000000U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        r_rsip_func206();
        r_rsip_func101(bswap_32big(0x1a7352fdU), bswap_32big(0xf5c0a992U), bswap_32big(0x75a4bba5U),
                       bswap_32big(0xdf82dec2U));
    }
    else if (0x00000001U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        r_rsip_func206();
        r_rsip_func101(bswap_32big(0xc5ee1e94U), bswap_32big(0xe30f2b51U), bswap_32big(0x2f9fe6daU),
                       bswap_32big(0xe741b522U));
    }
    else if (0x00000002U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        r_rsip_func206();
        r_rsip_func101(bswap_32big(0xd619bf77U), bswap_32big(0xb7728dc8U), bswap_32big(0x9761ddf8U),
                       bswap_32big(0xc59bf2c4U));
    }
    else if (0x00000003U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        r_rsip_func206();
        r_rsip_func101(bswap_32big(0x75c28e81U), bswap_32big(0x49f7a9d8U), bswap_32big(0x1d5b7c9aU),
                       bswap_32big(0xa4052f3bU));
    }
    else if (0x00000004U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        r_rsip_func206();
        r_rsip_func101(bswap_32big(0xd1901408U), bswap_32big(0x46cd4afaU), bswap_32big(0x801035ecU),
                       bswap_32big(0x99c7a108U));
    }
}
