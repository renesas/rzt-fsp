/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_MMU_CORE_H
#define BSP_MMU_CORE_H

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/** @} (end addtogroup BSP_MCU) */

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/*Table information*/
typedef struct st_bsp_mmu_table_info
{
    uint32_t table_level;
    uint64_t table_base_ptr;
    uint64_t table_base_addr;
} st_mmu_table_info_t;

/*Page table information*/
typedef struct mmu_pagetable_config
{
    uint64_t vaddress;
    uint64_t paddress;
    uint64_t size;
    uint64_t attribute;
} r_mmu_pgtbl_cfg_t;

/*Cache Flag*/
typedef enum e_bsp_mmu_conversion_flag
{
    BSP_MMU_CONVERSION_CACHE     = 0x00000000UL,
    BSP_MMU_CONVERSION_NON_CACHE = 0x00000001UL,
} bsp_mmu_conversion_flag_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

fsp_err_t R_BSP_MmuVatoPa(uint64_t vaddress, uint64_t * p_paddress);
fsp_err_t R_BSP_MmuPatoVa(uint64_t paddress, uint64_t * p_vaddress, bsp_mmu_conversion_flag_t cache_flag);

#endif                                 /* RZT_FSP_SRC_BSP_MCU_ALL_CA_BSP_MMU_H_ */
