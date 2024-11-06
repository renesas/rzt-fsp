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

void r_rsip_pb6u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
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
    r_rsip_func100(bswap_32big(0x82cec4c2U),
                   bswap_32big(0x149f1d5cU),
                   bswap_32big(0xdfbde369U),
                   bswap_32big(0x94cf468fU));
    WR1_PROG(REG_1444H, 0x00020061U);
    WR1_PROG(REG_182CH, 0x00000020U);
    WR1_PROG(REG_1824H, 0x0d00890eU);
    WR1_PROG(REG_1408H, 0x000c1000U);
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
    RD1_ADDR(REG_1420H, &OutData_Text[iLoop - 4]);
    RD1_ADDR(REG_1420H, &OutData_Text[iLoop - 3]);
    RD1_ADDR(REG_1420H, &OutData_Text[iLoop - 2]);
    RD1_ADDR(REG_1420H, &OutData_Text[iLoop - 1]);
    r_rsip_func206();
    r_rsip_func101(bswap_32big(0x136f6223U),
                   bswap_32big(0xa03bc87eU),
                   bswap_32big(0x6173c672U),
                   bswap_32big(0x77ad4a1cU));
}
