/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_mmu_core.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BSP_PRV_MMU_CONVERSION_SUCCESS                              (0ULL)
#define BSP_PRV_MMU_CONVERSION_FAULT                                (1ULL)
#define BSP_PRV_MMU_CONVERSION_FAULT_MASK                           (1ULL << 0)
#define BSP_PRV_MMU_LOWER_PHYSICAL_ADDRESS_MASK                     (0x0000000000000FFFULL)
#define BSP_PRV_MMU_UPPER_PHYSICAL_ADDRESS_MASK                     (0x000FFFFFFFFFF000ULL)

#define BSP_PRV_MMU_TABLE_TOTAL_REGION                              (48UL)
#define BSP_PRV_MMU_TABLE_REGION_MASK                               (1ULL << 0)
#define BSP_PRV_MMU_TABLE_ATTRINDX_MASK                             (7ULL << 2)
#define BSP_PRV_MMU_TABLE_ATTRINDX_SHIFT                            (2)
#define BSP_PRV_MMU_MAIR_ATTR_OFFSET                                (8ULL)
#define BSP_PRV_MMU_MAIR_ATTR_MASK                                  (0xFFULL)
#define BSP_PRV_MMU_MAIR_ATTR_UPPER_MASK                            (0xF0ULL)
#define BSP_PRV_MMU_MAIR_ATTR_LOWER_MASK                            (0x0FULL)
#define BSP_PRV_MMU_MAIR_DEVICE_MEMORY                              (0x00ULL)
#define BSP_PRV_MMU_MAIR_NORMAL_MEMORY_OUTER_INNER_NON_CACHEABLE    (0x4ULL << 4 | 0x4ULL << 0)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/
extern r_mmu_pgtbl_cfg_t g_mmu_pagetable_array[];

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Convert virtual address into physical address.
 *
 * @param[in]  vaddress          Virtual address to convert.
 * @param[out] p_paddress        Pointer to store physical address.
 * @retval FSP_SUCCESS           Successful
 * @retval FSP_ERR_INVALID_ADDRESS         Virtual address is invalid address.
 **********************************************************************************************************************/
fsp_err_t R_BSP_MmuVatoPa (uint64_t vaddress, uint64_t * p_paddress)
{
    fsp_err_t err = FSP_SUCCESS;

    uint64_t par_el1_r = 0;
    uint64_t par_el1_w = 0;

    /* Get the physical address from bit47 to bit12. */
    __asm volatile (
        "AT S1E3R, %1 \n"
        "MRS %0, PAR_EL1"
        : "=r" (par_el1_r)
        : "r"  (vaddress)
        : "memory");

    __asm volatile (
        "AT S1E3W, %1 \n"
        "MRS %0, PAR_EL1"
        : "=r" (par_el1_w)
        : "r"  (vaddress)
        : "memory");

    /* Get the physical address from bit11 to bit0 and combines it with the physical address of the upper bits.  */
    if (BSP_PRV_MMU_CONVERSION_SUCCESS == (par_el1_r & BSP_PRV_MMU_CONVERSION_FAULT_MASK))
    {
        *p_paddress = (par_el1_r & BSP_PRV_MMU_UPPER_PHYSICAL_ADDRESS_MASK) +
                      (vaddress & BSP_PRV_MMU_LOWER_PHYSICAL_ADDRESS_MASK);
    }
    else if (BSP_PRV_MMU_CONVERSION_SUCCESS == (par_el1_w & BSP_PRV_MMU_CONVERSION_FAULT_MASK))
    {
        *p_paddress = (par_el1_w & BSP_PRV_MMU_UPPER_PHYSICAL_ADDRESS_MASK) +
                      (vaddress & BSP_PRV_MMU_LOWER_PHYSICAL_ADDRESS_MASK);
    }
    else
    {
        err = FSP_ERR_INVALID_ADDRESS;
    }

    return err;
}

/*******************************************************************************************************************//**
 * Convert physical address into virtual address.
 *
 * @param[in]  paddress          Physical address to convert.
 * @param[out] p_vaddress        Pointer to store virtual address.
 * @param[in]  cache_flag        Cache flag to select VA.
 * @retval FSP_SUCCESS           Successful
 * @retval FSP_ERR_INVALID_ADDRESS         Physical address is invalid address.
 **********************************************************************************************************************/
fsp_err_t R_BSP_MmuPatoVa (uint64_t paddress, uint64_t * p_vaddress, bsp_mmu_conversion_flag_t cache_flag)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  cfg_index;

    /* Search for the gegion number of the address to be converted */
    for (cfg_index = 0; cfg_index < BSP_PRV_MMU_TABLE_TOTAL_REGION; cfg_index++)
    {
        r_mmu_pgtbl_cfg_t section_info;

        /* Get attribute on the region from the MMU table. */
        section_info.attribute = g_mmu_pagetable_array[cfg_index].attribute;

        /* Check the region enable. */
        if (BSP_PRV_MMU_TABLE_REGION_MASK & section_info.attribute)
        {
            /* Get address information on the region from the MMU table. */
            section_info.vaddress = g_mmu_pagetable_array[cfg_index].vaddress;
            section_info.paddress = g_mmu_pagetable_array[cfg_index].paddress;
            section_info.size     = g_mmu_pagetable_array[cfg_index].size;

            /* Check if the specified physical address is included in the target region. */
            if ((section_info.paddress <= paddress) && ((section_info.paddress + section_info.size) > paddress))
            {
                /* Get the attributes for that region. */
                uint64_t mair    = __get_MAIR();
                uint64_t attr_no =
                    ((section_info.attribute & BSP_PRV_MMU_TABLE_ATTRINDX_MASK) >> BSP_PRV_MMU_TABLE_ATTRINDX_SHIFT);
                uint64_t mair_shift  = (attr_no * BSP_PRV_MMU_MAIR_ATTR_OFFSET);
                uint64_t region_mair = (mair >> mair_shift) & BSP_PRV_MMU_MAIR_ATTR_MASK;

                /* If the cache attribute for that region matches the cache attribute set in cache_flag,
                 * the for statement loop branches. */
                if ((BSP_PRV_MMU_MAIR_DEVICE_MEMORY != (region_mair & BSP_PRV_MMU_MAIR_ATTR_UPPER_MASK)) &&
                    (BSP_PRV_MMU_MAIR_DEVICE_MEMORY != (region_mair & BSP_PRV_MMU_MAIR_ATTR_LOWER_MASK)))
                {
                    if (BSP_PRV_MMU_MAIR_NORMAL_MEMORY_OUTER_INNER_NON_CACHEABLE == region_mair)
                    {
                        if (BSP_MMU_CONVERSION_NON_CACHE == cache_flag)
                        {
                            break;
                        }
                        else
                        {
                            /* Do nothing. */
                        }
                    }
                    else
                    {
                        if (BSP_MMU_CONVERSION_CACHE == cache_flag)
                        {
                            break;
                        }
                        else
                        {
                            /* Do nothing. */
                        }
                    }
                }
            }
        }
    }

    /* If the search is successful, address translation is performed. */
    if (BSP_PRV_MMU_TABLE_TOTAL_REGION != cfg_index)
    {
        uint64_t region_vaddress = g_mmu_pagetable_array[cfg_index].vaddress;
        uint64_t region_paddress = g_mmu_pagetable_array[cfg_index].paddress;

        *p_vaddress = region_vaddress + (paddress - region_paddress);
    }
    else
    {
        err = FSP_ERR_INVALID_ADDRESS;
    }

    return err;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup BSP_MCU)
 **********************************************************************************************************************/
