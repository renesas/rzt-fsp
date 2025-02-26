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

rsip_ret_t r_rsip_p48f (void)
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
        r_rsip_func101(bswap_32big(0x707f05f9U), bswap_32big(0x17a01b8dU), bswap_32big(0x6c4ad904U),
                       bswap_32big(0x6e8cad0fU));
    }
    else if (0x00000001U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        r_rsip_func101(bswap_32big(0x878bd4a3U), bswap_32big(0xa937c3c3U), bswap_32big(0x9f393514U),
                       bswap_32big(0x60591508U));
    }
    else if (0x00000002U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        r_rsip_func101(bswap_32big(0x3e363a60U), bswap_32big(0xb5d2ff57U), bswap_32big(0xbb82022cU),
                       bswap_32big(0x8626e90aU));
    }
    else if (0x00000003U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        r_rsip_func101(bswap_32big(0xe43a8485U), bswap_32big(0x7dc86329U), bswap_32big(0x0bb3f58dU),
                       bswap_32big(0x5beaa731U));
    }
    else if (0x00000004U == RD1_MASK(REG_1440H, 0xffffffffU))
    {
        r_rsip_func101(bswap_32big(0x933ceac9U), bswap_32big(0x56745bf9U), bswap_32big(0x664eecf1U),
                       bswap_32big(0xfefc3cb2U));
    }

    r_rsip_func102(bswap_32big(0xeb54ce94U),
                   bswap_32big(0xe4876cc2U),
                   bswap_32big(0x27cb1bceU),
                   bswap_32big(0xaf13815cU));
    WR1_PROG(REG_14BCH, 0x00000040U);
    WAIT_STS(REG_142CH, 12U, 0U);

    return RSIP_RET_PASS;
}
