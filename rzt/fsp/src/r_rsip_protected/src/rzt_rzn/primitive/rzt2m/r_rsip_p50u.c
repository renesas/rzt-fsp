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

void r_rsip_p50u (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT)
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
        r_rsip_func100(bswap_32big(0x5e33e5f3U), bswap_32big(0xd6d7a6eeU), bswap_32big(0xb6d197d1U),
                       bswap_32big(0x439df20dU));
        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x0a008106U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (0x00000001U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0xf72862a5U), bswap_32big(0x67394e5aU), bswap_32big(0x0278c50aU),
                       bswap_32big(0x7fdc5b58U));
        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x0a00810eU);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (0x00000002U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0x1ee6126cU), bswap_32big(0xaf7f95b3U), bswap_32big(0x4612c7d4U),
                       bswap_32big(0x667646f8U));
        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x0e008506U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (0x00000003U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0x7d142184U), bswap_32big(0x5cfbf217U), bswap_32big(0x02ceb4ceU),
                       bswap_32big(0x7932eda6U));
        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x0900890eU);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (0x00000004U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        r_rsip_func100(bswap_32big(0x80fd4c74U), bswap_32big(0x5d6ec395U), bswap_32big(0x39d26032U),
                       bswap_32big(0x9f0b9a85U));
        WR1_PROG(REG_1444H, 0x00020061U);
        WR1_PROG(REG_182CH, 0x40000000U);
        WR1_PROG(REG_1824H, 0x07008d06U);
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
        r_rsip_func101(bswap_32big(0xba9912ccU), bswap_32big(0xa73e76e1U), bswap_32big(0x459e7102U),
                       bswap_32big(0x7d59145eU));
    }
    else if (0x00000001U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        r_rsip_func206();
        r_rsip_func101(bswap_32big(0x9b2f9f10U), bswap_32big(0x8013c7ddU), bswap_32big(0x62945707U),
                       bswap_32big(0x61074b08U));
    }
    else if (0x00000002U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        r_rsip_func206();
        r_rsip_func101(bswap_32big(0xe6a5f1d6U), bswap_32big(0xf0ffc69fU), bswap_32big(0x2f98fb4cU),
                       bswap_32big(0xd8725072U));
    }
    else if (0x00000003U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        r_rsip_func206();
        r_rsip_func101(bswap_32big(0x04fff151U), bswap_32big(0x49046ab1U), bswap_32big(0x5d1d070dU),
                       bswap_32big(0xe9204392U));
    }
    else if (0x00000004U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        r_rsip_func206();
        r_rsip_func101(bswap_32big(0xef326329U), bswap_32big(0x49b165a4U), bswap_32big(0x3b8a2093U),
                       bswap_32big(0x61f9500bU));
    }
}
