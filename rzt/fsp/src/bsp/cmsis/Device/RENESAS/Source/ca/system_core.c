/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <string.h>
#include "bsp_api.h"
#include "../../../../../mcu/all/bsp_compiler_support.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define ICC_SRE_EL3_BIT_Enable                  (1 << 3)
#define ICC_SRE_EL3_BIT_DIB                     (1 << 2)
#define ICC_SRE_EL3_BIT_DFB                     (1 << 1)
#define ICC_SRE_EL3_BIT_SRE                     (1 << 0)
#define ICC_SRE_EL1_BIT_SRE                     (1 << 0)
#define ICC_IGRPEN1_EL3_BIT_EnableGrp1S         (1 << 1)
#define ICC_IGRPEN1_EL3_BIT_EnableGrp1NS        (1 << 0)
#define ICC_PMR_EL1_VALID_INTERRUPT_PRIORITY    (0xFF)

#define GICD_CTLR_BIT_ARE_NS                    (1 << 5)
#define GICD_CTLR_BIT_ARE_S                     (1 << 4)

#define BSP_NON_CACHEABLE                       (0x0004) /* Normal-Memory: Non-Cacheable */
#define BSP_WRITE_BACK_TRANSIENT                (0x0007) /* Normal-Memory: Write-Back transient */
#define BSP_WRITE_BACK_NON_TRANSIENT            (0x000F) /* Normal-Memory: Write-Back non-transient. */

#define BSP_TYPE_NORMAL_MEMORY                  (0)
#define BSP_TYPE_DEVICE_MEMORY                  (1)

#define BSP_READ_ALLOCATE                       (0xFFFF) /* Read allocate (bit1=1, "1" mask except bit1) */
#define BSP_READ_NOT_ALLOCATE                   (0xFFFD) /* Read not allocate (bit1=0, "1" mask except bit1) */
#define BSP_WRITE_ALLOCATE                      (0xFFFF) /* Write allocate (bit0=1, "1" mask except bit0) */
#define BSP_WRITE_NOT_ALLOCATE                  (0xFFFE) /* Write not allocate (bit0=0, "1" mask except bit0) */

#define BSP_DEVICE_NGNRNE                       (0x0000) /* Device-nGnRnE memory */
#define BSP_DEVICE_NGNRE                        (0x0004) /* Device-nGnRE memory */
#define BSP_DEVICE_NGRE                         (0x0008) /* Device-nGRE memory */
#define BSP_DEVICE_GRE                          (0x000C) /* Device-GRE memory */

#define BSP_OFFSET_ATTR0_INNER                  (0)
#define BSP_OFFSET_ATTR0_OUTER                  (4)
#define BSP_OFFSET_ATTR0_DEVICE                 (0)
#define BSP_OFFSET_ATTR1_INNER                  (8)
#define BSP_OFFSET_ATTR1_OUTER                  (12)
#define BSP_OFFSET_ATTR1_DEVICE                 (8)

#define BSP_OFFSET_ATTR2_INNER                  (16)
#define BSP_OFFSET_ATTR2_OUTER                  (20)
#define BSP_OFFSET_ATTR2_DEVICE                 (16)
#define BSP_OFFSET_ATTR3_INNER                  (24)
#define BSP_OFFSET_ATTR3_OUTER                  (28)
#define BSP_OFFSET_ATTR3_DEVICE                 (24)

#define BSP_OFFSET_ATTR4_INNER                  (0)
#define BSP_OFFSET_ATTR4_OUTER                  (4)
#define BSP_OFFSET_ATTR4_DEVICE                 (0)
#define BSP_OFFSET_ATTR5_INNER                  (8)
#define BSP_OFFSET_ATTR5_OUTER                  (12)
#define BSP_OFFSET_ATTR5_DEVICE                 (8)

#define BSP_OFFSET_ATTR6_INNER                  (16)
#define BSP_OFFSET_ATTR6_OUTER                  (20)
#define BSP_OFFSET_ATTR6_DEVICE                 (16)
#define BSP_OFFSET_ATTR7_INNER                  (24)
#define BSP_OFFSET_ATTR7_OUTER                  (28)
#define BSP_OFFSET_ATTR7_DEVICE                 (24)

/* Attr0 */
#if BSP_CFG_CPU_MPU_ATTR0_TYPE == BSP_TYPE_DEVICE_MEMORY /* MEMORY TYPE == DEVICE */
 #define BSP_CFG_CPU_MPU_ATTR0                  (BSP_CFG_CPU_MPU_ATTR0_DEVICE_TYPE << BSP_OFFSET_ATTR0_DEVICE)
#else                                                    /* MEMORY TYPE == NORMAL MEMORY */
 #define BSP_CFG_CPU_MPU_ATTR0                  (((BSP_CFG_CPU_MPU_ATTR0_INNER &                                     \
                                                   (BSP_CFG_CPU_MPU_ATTR0_INNER_READ) &                              \
                                                   (BSP_CFG_CPU_MPU_ATTR0_INNER_WRITE)) << BSP_OFFSET_ATTR0_INNER) | \
                                                 ((BSP_CFG_CPU_MPU_ATTR0_OUTER &                                     \
                                                   (BSP_CFG_CPU_MPU_ATTR0_OUTER_READ) &                              \
                                                   (BSP_CFG_CPU_MPU_ATTR0_OUTER_WRITE)) << BSP_OFFSET_ATTR0_OUTER))
#endif                                                   /* BSP_CFG_CPU_MPU_ATTR0_TYPE */

/* Attr1 */
#if BSP_CFG_CPU_MPU_ATTR1_TYPE == BSP_TYPE_DEVICE_MEMORY /* MEMORY TYPE == DEVICE */
 #define BSP_CFG_CPU_MPU_ATTR1                  (BSP_CFG_CPU_MPU_ATTR1_DEVICE_TYPE << BSP_OFFSET_ATTR1_DEVICE)
#else                                                    /* MEMORY TYPE == NORMAL MEMORY */
 #define BSP_CFG_CPU_MPU_ATTR1                  (((BSP_CFG_CPU_MPU_ATTR1_INNER &                                     \
                                                   (BSP_CFG_CPU_MPU_ATTR1_INNER_READ) &                              \
                                                   (BSP_CFG_CPU_MPU_ATTR1_INNER_WRITE)) << BSP_OFFSET_ATTR1_INNER) | \
                                                 ((BSP_CFG_CPU_MPU_ATTR1_OUTER &                                     \
                                                   (BSP_CFG_CPU_MPU_ATTR1_OUTER_READ) &                              \
                                                   (BSP_CFG_CPU_MPU_ATTR1_OUTER_WRITE)) << BSP_OFFSET_ATTR1_OUTER))
#endif                                                   /* BSP_CFG_CPU_MPU_ATTR1_TYPE */

/* Attr2 */
#if BSP_CFG_CPU_MPU_ATTR2_TYPE == BSP_TYPE_DEVICE_MEMORY /* MEMORY TYPE == DEVICE */
 #define BSP_CFG_CPU_MPU_ATTR2                  (BSP_CFG_CPU_MPU_ATTR2_DEVICE_TYPE << BSP_OFFSET_ATTR2_DEVICE)
#else                                                    /* MEMORY TYPE == NORMAL MEMORY */
 #define BSP_CFG_CPU_MPU_ATTR2                  (((BSP_CFG_CPU_MPU_ATTR2_INNER &                                     \
                                                   (BSP_CFG_CPU_MPU_ATTR2_INNER_READ) &                              \
                                                   (BSP_CFG_CPU_MPU_ATTR2_INNER_WRITE)) << BSP_OFFSET_ATTR2_INNER) | \
                                                 ((BSP_CFG_CPU_MPU_ATTR2_OUTER &                                     \
                                                   (BSP_CFG_CPU_MPU_ATTR2_OUTER_READ) &                              \
                                                   (BSP_CFG_CPU_MPU_ATTR2_OUTER_WRITE)) << BSP_OFFSET_ATTR2_OUTER))
#endif                                                   /* BSP_CFG_CPU_MPU_ATTR2_TYPE */

/* Attr3 */
#if BSP_CFG_CPU_MPU_ATTR3_TYPE == BSP_TYPE_DEVICE_MEMORY /* MEMORY TYPE == DEVICE */
 #define BSP_CFG_CPU_MPU_ATTR3                  (BSP_CFG_CPU_MPU_ATTR3_DEVICE_TYPE << BSP_OFFSET_ATTR3_DEVICE)
#else                                                    /* MEMORY TYPE == NORMAL MEMORY */
 #define BSP_CFG_CPU_MPU_ATTR3                  (((BSP_CFG_CPU_MPU_ATTR3_INNER &                                     \
                                                   (BSP_CFG_CPU_MPU_ATTR3_INNER_READ) &                              \
                                                   (BSP_CFG_CPU_MPU_ATTR3_INNER_WRITE)) << BSP_OFFSET_ATTR3_INNER) | \
                                                 ((BSP_CFG_CPU_MPU_ATTR3_OUTER &                                     \
                                                   (BSP_CFG_CPU_MPU_ATTR3_OUTER_READ) &                              \
                                                   (BSP_CFG_CPU_MPU_ATTR3_OUTER_WRITE)) << BSP_OFFSET_ATTR3_OUTER))
#endif                                                   /* BSP_CFG_CPU_MPU_ATTR3_TYPE */

/* Attr4 */
#if BSP_CFG_CPU_MPU_ATTR4_TYPE == BSP_TYPE_DEVICE_MEMORY /* MEMORY TYPE == DEVICE */
 #define BSP_CFG_CPU_MPU_ATTR4                  (BSP_CFG_CPU_MPU_ATTR4_DEVICE_TYPE << BSP_OFFSET_ATTR4_DEVICE)
#else                                                    /* MEMORY TYPE == NORMAL MEMORY */
 #define BSP_CFG_CPU_MPU_ATTR4                  (((BSP_CFG_CPU_MPU_ATTR4_INNER &                                     \
                                                   (BSP_CFG_CPU_MPU_ATTR4_INNER_READ) &                              \
                                                   (BSP_CFG_CPU_MPU_ATTR4_INNER_WRITE)) << BSP_OFFSET_ATTR4_INNER) | \
                                                 ((BSP_CFG_CPU_MPU_ATTR4_OUTER &                                     \
                                                   (BSP_CFG_CPU_MPU_ATTR4_OUTER_READ) &                              \
                                                   (BSP_CFG_CPU_MPU_ATTR4_OUTER_WRITE)) << BSP_OFFSET_ATTR4_OUTER))
#endif                                                   /* BSP_CFG_CPU_MPU_ATTR4_TYPE */

/* Attr5 */
#if BSP_CFG_CPU_MPU_ATTR5_TYPE == BSP_TYPE_DEVICE_MEMORY /* MEMORY TYPE == DEVICE */
 #define BSP_CFG_CPU_MPU_ATTR5                  (BSP_CFG_CPU_MPU_ATTR5_DEVICE_TYPE << BSP_OFFSET_ATTR5_DEVICE)
#else                                                    /* MEMORY TYPE == NORMAL MEMORY */
 #define BSP_CFG_CPU_MPU_ATTR5                  (((BSP_CFG_CPU_MPU_ATTR5_INNER &                                     \
                                                   (BSP_CFG_CPU_MPU_ATTR5_INNER_READ) &                              \
                                                   (BSP_CFG_CPU_MPU_ATTR5_INNER_WRITE)) << BSP_OFFSET_ATTR5_INNER) | \
                                                 ((BSP_CFG_CPU_MPU_ATTR5_OUTER &                                     \
                                                   (BSP_CFG_CPU_MPU_ATTR5_OUTER_READ) &                              \
                                                   (BSP_CFG_CPU_MPU_ATTR5_OUTER_WRITE)) << BSP_OFFSET_ATTR5_OUTER))
#endif                                                   /* BSP_CFG_CPU_MPU_ATTR5_TYPE */

/* Attr6 */
#if BSP_CFG_CPU_MPU_ATTR6_TYPE == BSP_TYPE_DEVICE_MEMORY /* MEMORY TYPE == DEVICE */
 #define BSP_CFG_CPU_MPU_ATTR6                  (BSP_CFG_CPU_MPU_ATTR6_DEVICE_TYPE << BSP_OFFSET_ATTR6_DEVICE)
#else                                                    /* MEMORY TYPE == NORMAL MEMORY */
 #define BSP_CFG_CPU_MPU_ATTR6                  (((BSP_CFG_CPU_MPU_ATTR6_INNER &                                     \
                                                   (BSP_CFG_CPU_MPU_ATTR6_INNER_READ) &                              \
                                                   (BSP_CFG_CPU_MPU_ATTR6_INNER_WRITE)) << BSP_OFFSET_ATTR6_INNER) | \
                                                 ((BSP_CFG_CPU_MPU_ATTR6_OUTER &                                     \
                                                   (BSP_CFG_CPU_MPU_ATTR6_OUTER_READ) &                              \
                                                   (BSP_CFG_CPU_MPU_ATTR6_OUTER_WRITE)) << BSP_OFFSET_ATTR6_OUTER))
#endif                                                   /* BSP_CFG_CPU_MPU_ATTR6_TYPE */

/* Attr7 */
#if BSP_CFG_CPU_MPU_ATTR7_TYPE == BSP_TYPE_DEVICE_MEMORY /* MEMORY TYPE == DEVICE */
 #define BSP_CFG_CPU_MPU_ATTR7                  (BSP_CFG_CPU_MPU_ATTR7_DEVICE_TYPE << BSP_OFFSET_ATTR7_DEVICE)
#else                                                    /* MEMORY TYPE == NORMAL MEMORY */
 #define BSP_CFG_CPU_MPU_ATTR7                  (((BSP_CFG_CPU_MPU_ATTR7_INNER &                                     \
                                                   (BSP_CFG_CPU_MPU_ATTR7_INNER_READ) &                              \
                                                   (BSP_CFG_CPU_MPU_ATTR7_INNER_WRITE)) << BSP_OFFSET_ATTR7_INNER) | \
                                                 ((BSP_CFG_CPU_MPU_ATTR7_OUTER &                                     \
                                                   (BSP_CFG_CPU_MPU_ATTR7_OUTER_READ) &                              \
                                                   (BSP_CFG_CPU_MPU_ATTR7_OUTER_WRITE)) << BSP_OFFSET_ATTR7_OUTER))
#endif                                 /* BSP_CFG_CPU_MPU_ATTR7_TYPE */

#define ATTR_3_2_1_0                            (BSP_CFG_CPU_MPU_ATTR3 | BSP_CFG_CPU_MPU_ATTR2 | BSP_CFG_CPU_MPU_ATTR1 | \
                                                 BSP_CFG_CPU_MPU_ATTR0)
#define ATTR_7_6_5_4                            (BSP_CFG_CPU_MPU_ATTR7 | BSP_CFG_CPU_MPU_ATTR6 | BSP_CFG_CPU_MPU_ATTR5 | \
                                                 BSP_CFG_CPU_MPU_ATTR4)

#define BSP_UXN_EXECUTE_DISABLE                 (0x100000000 << 22)
#define BSP_UXN_EXECUTE_ENABLE                  (0x000000000 << 22)
#define BSP_PXN_EXECUTE_DISABLE                 (0x100000000 << 21)
#define BSP_PXN_EXECUTE_ENABLE                  (0x000000000 << 21)
#define BSP_AF_BLOCK_USED                       (1 << 10)
#define BSP_NON_SHAREABLE                       (0 << 8)
#define BSP_OUTER_SHAREABLE                     (2 << 8)
#define BSP_INNER_SHAREABLE                     (3 << 8)
#define BSP_EL321RW_EL0NO                       (0 << 6)
#define BSP_EL321RW_EL0RW                       (1 << 6)
#define BSP_EL321RO_EL0NO                       (2 << 6)
#define BSP_EL321RO_EL0RO                       (3 << 6)
#define BSP_NS_NON_SECURE                       (1 << 5)
#define BSP_NS_SECURE                           (0 << 5)
#define BSP_ATTRINDEX0                          (0 << 2)
#define BSP_ATTRINDEX1                          (1 << 2)
#define BSP_ATTRINDEX2                          (2 << 2)
#define BSP_ATTRINDEX3                          (3 << 2)
#define BSP_ATTRINDEX4                          (4 << 2)
#define BSP_ATTRINDEX5                          (5 << 2)
#define BSP_ATTRINDEX6                          (6 << 2)
#define BSP_ATTRINDEX7                          (7 << 2)

#define BSP_REGION_ENABLE                       (1 << 0)
#define BSP_REGION_DISABLE                      (0 << 0)

#define BSP_MMU_LEVEL2_TABLE_INDEX_MAX          (4)
#define BSP_MMU_TABLE_ENTRY                     (512)
#define BSP_MMU_TABLE_ALIGN                     (0x1000)

#define BSP_MMU_LEVEL1_TABLE_SIZE               (0x40000000)
#define BSP_MMU_PA_STRIDE_LEVEL_1               (0x40000000) /* 1GB */
#define BSP_MMU_PA_STRIDE_LEVEL_2               (0x00200000) /* 2MB */
#define BSP_MMU_PA_STRIDE_LEVEL_3               (0x00001000) /* 4KB */

#define BSP_MMU_PG_DESC_SIZE                    (8)

#define BSP_MMU_N1_TABLE_START_VADDR            (0x00000000)
#define BSP_MMU_N2_TABLE_START_VADDR            (0x40000000)
#define BSP_MMU_N3_TABLE_START_VADDR            (0x80000000)
#define BSP_MMU_N4_TABLE_START_VADDR            (0xC0000000)
#define BSP_MMU_N5_TABLE_START_VADDR            (0x100000000)

#define BSP_MMU_TOTAL_REGION                    (48U)

#define BSP_MMU_PG_ATTR_NEXT_TBL                (0x00000003)

#define BSP_MMU_TCR                             (0x8081351D)

#define BSP_MMU_DESCRIPTOR_VALID                (0x1)

#define EL3_MMU_REGIONXX_DATA(n)    (BSP_CFG_EL3_MMU_REGION ## n ## _UXN |       \
                                     BSP_CFG_EL3_MMU_REGION ## n ## _PXN |       \
                                     BSP_AF_BLOCK_USED |                         \
                                     BSP_CFG_EL3_MMU_REGION ## n ## _SH |        \
                                     BSP_CFG_EL3_MMU_REGION ## n ## _AP |        \
                                     BSP_CFG_EL3_MMU_REGION ## n ## _NS |        \
                                     BSP_CFG_EL3_MMU_REGION ## n ## _ATTRINDEX | \
                                     BSP_CFG_EL3_MMU_REGION ## n ## _ENABLE)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef enum e_bsp_mmu_talbe_level
{
    BSP_MMU_TABLE_LEVEL_0 = 0,
    BSP_MMU_TABLE_LEVEL_1 = 1,
    BSP_MMU_TABLE_LEVEL_2 = 2,
    BSP_MMU_TABLE_LEVEL_3 = 3,
} bsp_mmu_talbe_level_t;

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

uint64_t g_mmu_ttbr0_base[BSP_MMU_LEVEL2_TABLE_INDEX_MAX +
                          28] BSP_ALIGN_VARIABLE(BSP_MMU_TABLE_ALIGN) BSP_PLACE_IN_SECTION(BSP_SECTION_MMU_TABLE_SECTION);
uint64_t g_mmu_level2_table_1_base[BSP_MMU_TABLE_ENTRY]   BSP_ALIGN_VARIABLE(BSP_MMU_TABLE_ALIGN)
BSP_PLACE_IN_SECTION(BSP_SECTION_MMU_TABLE_SECTION);
uint64_t g_mmu_level2_table_2_base[BSP_MMU_TABLE_ENTRY]   BSP_ALIGN_VARIABLE(BSP_MMU_TABLE_ALIGN)
BSP_PLACE_IN_SECTION(BSP_SECTION_MMU_TABLE_SECTION);
uint64_t g_mmu_level2_table_3_base[BSP_MMU_TABLE_ENTRY]   BSP_ALIGN_VARIABLE(BSP_MMU_TABLE_ALIGN)
BSP_PLACE_IN_SECTION(BSP_SECTION_MMU_TABLE_SECTION);
uint64_t g_mmu_level2_table_4_base[BSP_MMU_TABLE_ENTRY]   BSP_ALIGN_VARIABLE(BSP_MMU_TABLE_ALIGN)
BSP_PLACE_IN_SECTION(BSP_SECTION_MMU_TABLE_SECTION);

r_mmu_pgtbl_cfg_t const g_mmu_pagetable_array[] =
{
    {BSP_CFG_EL3_MMU_REGION00_VADDR, BSP_CFG_EL3_MMU_REGION00_PADDR, BSP_CFG_EL3_MMU_REGION00_SIZE,
     EL3_MMU_REGIONXX_DATA(00)},       /* Region 00 */
    {BSP_CFG_EL3_MMU_REGION01_VADDR, BSP_CFG_EL3_MMU_REGION01_PADDR, BSP_CFG_EL3_MMU_REGION01_SIZE,
     EL3_MMU_REGIONXX_DATA(01)},       /* Region 01 */
    {BSP_CFG_EL3_MMU_REGION02_VADDR, BSP_CFG_EL3_MMU_REGION02_PADDR, BSP_CFG_EL3_MMU_REGION02_SIZE,
     EL3_MMU_REGIONXX_DATA(02)},       /* Region 02 */
    {BSP_CFG_EL3_MMU_REGION03_VADDR, BSP_CFG_EL3_MMU_REGION03_PADDR, BSP_CFG_EL3_MMU_REGION03_SIZE,
     EL3_MMU_REGIONXX_DATA(03)},       /* Region 03 */
    {BSP_CFG_EL3_MMU_REGION04_VADDR, BSP_CFG_EL3_MMU_REGION04_PADDR, BSP_CFG_EL3_MMU_REGION04_SIZE,
     EL3_MMU_REGIONXX_DATA(04)},       /* Region 04 */
    {BSP_CFG_EL3_MMU_REGION05_VADDR, BSP_CFG_EL3_MMU_REGION05_PADDR, BSP_CFG_EL3_MMU_REGION05_SIZE,
     EL3_MMU_REGIONXX_DATA(05)},       /* Region 05 */
    {BSP_CFG_EL3_MMU_REGION06_VADDR, BSP_CFG_EL3_MMU_REGION06_PADDR, BSP_CFG_EL3_MMU_REGION06_SIZE,
     EL3_MMU_REGIONXX_DATA(06)},       /* Region 06 */
    {BSP_CFG_EL3_MMU_REGION07_VADDR, BSP_CFG_EL3_MMU_REGION07_PADDR, BSP_CFG_EL3_MMU_REGION07_SIZE,
     EL3_MMU_REGIONXX_DATA(07)},       /* Region 07 */
    {BSP_CFG_EL3_MMU_REGION08_VADDR, BSP_CFG_EL3_MMU_REGION08_PADDR, BSP_CFG_EL3_MMU_REGION08_SIZE,
     EL3_MMU_REGIONXX_DATA(08)},       /* Region 08 */
    {BSP_CFG_EL3_MMU_REGION09_VADDR, BSP_CFG_EL3_MMU_REGION09_PADDR, BSP_CFG_EL3_MMU_REGION09_SIZE,
     EL3_MMU_REGIONXX_DATA(09)},       /* Region 09 */
    {BSP_CFG_EL3_MMU_REGION10_VADDR, BSP_CFG_EL3_MMU_REGION10_PADDR, BSP_CFG_EL3_MMU_REGION10_SIZE,
     EL3_MMU_REGIONXX_DATA(10)},       /* Region 10 */
    {BSP_CFG_EL3_MMU_REGION11_VADDR, BSP_CFG_EL3_MMU_REGION11_PADDR, BSP_CFG_EL3_MMU_REGION11_SIZE,
     EL3_MMU_REGIONXX_DATA(11)},       /* Region 11 */
    {BSP_CFG_EL3_MMU_REGION12_VADDR, BSP_CFG_EL3_MMU_REGION12_PADDR, BSP_CFG_EL3_MMU_REGION12_SIZE,
     EL3_MMU_REGIONXX_DATA(12)},       /* Region 12 */
    {BSP_CFG_EL3_MMU_REGION13_VADDR, BSP_CFG_EL3_MMU_REGION13_PADDR, BSP_CFG_EL3_MMU_REGION13_SIZE,
     EL3_MMU_REGIONXX_DATA(13)},       /* Region 13 */
    {BSP_CFG_EL3_MMU_REGION14_VADDR, BSP_CFG_EL3_MMU_REGION14_PADDR, BSP_CFG_EL3_MMU_REGION14_SIZE,
     EL3_MMU_REGIONXX_DATA(14)},       /* Region 14 */
    {BSP_CFG_EL3_MMU_REGION15_VADDR, BSP_CFG_EL3_MMU_REGION15_PADDR, BSP_CFG_EL3_MMU_REGION15_SIZE,
     EL3_MMU_REGIONXX_DATA(15)},       /* Region 15 */
    {BSP_CFG_EL3_MMU_REGION16_VADDR, BSP_CFG_EL3_MMU_REGION16_PADDR, BSP_CFG_EL3_MMU_REGION16_SIZE,
     EL3_MMU_REGIONXX_DATA(16)},       /* Region 16 */
    {BSP_CFG_EL3_MMU_REGION17_VADDR, BSP_CFG_EL3_MMU_REGION17_PADDR, BSP_CFG_EL3_MMU_REGION17_SIZE,
     EL3_MMU_REGIONXX_DATA(17)},       /* Region 17 */
    {BSP_CFG_EL3_MMU_REGION18_VADDR, BSP_CFG_EL3_MMU_REGION18_PADDR, BSP_CFG_EL3_MMU_REGION18_SIZE,
     EL3_MMU_REGIONXX_DATA(18)},       /* Region 18 */
    {BSP_CFG_EL3_MMU_REGION19_VADDR, BSP_CFG_EL3_MMU_REGION19_PADDR, BSP_CFG_EL3_MMU_REGION19_SIZE,
     EL3_MMU_REGIONXX_DATA(19)},       /* Region 19 */
    {BSP_CFG_EL3_MMU_REGION20_VADDR, BSP_CFG_EL3_MMU_REGION20_PADDR, BSP_CFG_EL3_MMU_REGION20_SIZE,
     EL3_MMU_REGIONXX_DATA(20)},       /* Region 20 */
    {BSP_CFG_EL3_MMU_REGION21_VADDR, BSP_CFG_EL3_MMU_REGION21_PADDR, BSP_CFG_EL3_MMU_REGION21_SIZE,
     EL3_MMU_REGIONXX_DATA(21)},       /* Region 21 */
    {BSP_CFG_EL3_MMU_REGION22_VADDR, BSP_CFG_EL3_MMU_REGION22_PADDR, BSP_CFG_EL3_MMU_REGION22_SIZE,
     EL3_MMU_REGIONXX_DATA(22)},       /* Region 22 */
    {BSP_CFG_EL3_MMU_REGION23_VADDR, BSP_CFG_EL3_MMU_REGION23_PADDR, BSP_CFG_EL3_MMU_REGION23_SIZE,
     EL3_MMU_REGIONXX_DATA(23)},       /* Region 23 */
    {BSP_CFG_EL3_MMU_REGION24_VADDR, BSP_CFG_EL3_MMU_REGION24_PADDR, BSP_CFG_EL3_MMU_REGION24_SIZE,
     EL3_MMU_REGIONXX_DATA(24)},       /* Region 24 */
    {BSP_CFG_EL3_MMU_REGION25_VADDR, BSP_CFG_EL3_MMU_REGION25_PADDR, BSP_CFG_EL3_MMU_REGION25_SIZE,
     EL3_MMU_REGIONXX_DATA(25)},       /* Region 25 */
    {BSP_CFG_EL3_MMU_REGION26_VADDR, BSP_CFG_EL3_MMU_REGION26_PADDR, BSP_CFG_EL3_MMU_REGION26_SIZE,
     EL3_MMU_REGIONXX_DATA(26)},       /* Region 26 */
    {BSP_CFG_EL3_MMU_REGION27_VADDR, BSP_CFG_EL3_MMU_REGION27_PADDR, BSP_CFG_EL3_MMU_REGION27_SIZE,
     EL3_MMU_REGIONXX_DATA(27)},       /* Region 27 */
    {BSP_CFG_EL3_MMU_REGION28_VADDR, BSP_CFG_EL3_MMU_REGION28_PADDR, BSP_CFG_EL3_MMU_REGION28_SIZE,
     EL3_MMU_REGIONXX_DATA(28)},       /* Region 28 */
    {BSP_CFG_EL3_MMU_REGION29_VADDR, BSP_CFG_EL3_MMU_REGION29_PADDR, BSP_CFG_EL3_MMU_REGION29_SIZE,
     EL3_MMU_REGIONXX_DATA(29)},       /* Region 29 */
    {BSP_CFG_EL3_MMU_REGION30_VADDR, BSP_CFG_EL3_MMU_REGION30_PADDR, BSP_CFG_EL3_MMU_REGION30_SIZE,
     EL3_MMU_REGIONXX_DATA(30)},       /* Region 30 */
    {BSP_CFG_EL3_MMU_REGION31_VADDR, BSP_CFG_EL3_MMU_REGION31_PADDR, BSP_CFG_EL3_MMU_REGION31_SIZE,
     EL3_MMU_REGIONXX_DATA(31)},       /* Region 31 */
    {BSP_CFG_EL3_MMU_REGION32_VADDR, BSP_CFG_EL3_MMU_REGION32_PADDR, BSP_CFG_EL3_MMU_REGION32_SIZE,
     EL3_MMU_REGIONXX_DATA(32)},       /* Region 32 */
    {BSP_CFG_EL3_MMU_REGION33_VADDR, BSP_CFG_EL3_MMU_REGION33_PADDR, BSP_CFG_EL3_MMU_REGION33_SIZE,
     EL3_MMU_REGIONXX_DATA(33)},       /* Region 33 */
    {BSP_CFG_EL3_MMU_REGION34_VADDR, BSP_CFG_EL3_MMU_REGION34_PADDR, BSP_CFG_EL3_MMU_REGION34_SIZE,
     EL3_MMU_REGIONXX_DATA(34)},       /* Region 34 */
    {BSP_CFG_EL3_MMU_REGION35_VADDR, BSP_CFG_EL3_MMU_REGION35_PADDR, BSP_CFG_EL3_MMU_REGION35_SIZE,
     EL3_MMU_REGIONXX_DATA(35)},       /* Region 35 */
    {BSP_CFG_EL3_MMU_REGION36_VADDR, BSP_CFG_EL3_MMU_REGION36_PADDR, BSP_CFG_EL3_MMU_REGION36_SIZE,
     EL3_MMU_REGIONXX_DATA(36)},       /* Region 36 */
    {BSP_CFG_EL3_MMU_REGION37_VADDR, BSP_CFG_EL3_MMU_REGION37_PADDR, BSP_CFG_EL3_MMU_REGION37_SIZE,
     EL3_MMU_REGIONXX_DATA(37)},       /* Region 37 */
    {BSP_CFG_EL3_MMU_REGION38_VADDR, BSP_CFG_EL3_MMU_REGION38_PADDR, BSP_CFG_EL3_MMU_REGION38_SIZE,
     EL3_MMU_REGIONXX_DATA(38)},       /* Region 38 */
    {BSP_CFG_EL3_MMU_REGION39_VADDR, BSP_CFG_EL3_MMU_REGION39_PADDR, BSP_CFG_EL3_MMU_REGION39_SIZE,
     EL3_MMU_REGIONXX_DATA(39)},       /* Region 39 */
    {BSP_CFG_EL3_MMU_REGION40_VADDR, BSP_CFG_EL3_MMU_REGION40_PADDR, BSP_CFG_EL3_MMU_REGION40_SIZE,
     EL3_MMU_REGIONXX_DATA(40)},       /* Region 40 */
    {BSP_CFG_EL3_MMU_REGION41_VADDR, BSP_CFG_EL3_MMU_REGION41_PADDR, BSP_CFG_EL3_MMU_REGION41_SIZE,
     EL3_MMU_REGIONXX_DATA(41)},       /* Region 41 */
    {BSP_CFG_EL3_MMU_REGION42_VADDR, BSP_CFG_EL3_MMU_REGION42_PADDR, BSP_CFG_EL3_MMU_REGION42_SIZE,
     EL3_MMU_REGIONXX_DATA(42)},       /* Region 42 */
    {BSP_CFG_EL3_MMU_REGION43_VADDR, BSP_CFG_EL3_MMU_REGION43_PADDR, BSP_CFG_EL3_MMU_REGION43_SIZE,
     EL3_MMU_REGIONXX_DATA(43)},       /* Region 43 */
    {BSP_CFG_EL3_MMU_REGION44_VADDR, BSP_CFG_EL3_MMU_REGION44_PADDR, BSP_CFG_EL3_MMU_REGION44_SIZE,
     EL3_MMU_REGIONXX_DATA(44)},       /* Region 44 */
    {BSP_CFG_EL3_MMU_REGION45_VADDR, BSP_CFG_EL3_MMU_REGION45_PADDR, BSP_CFG_EL3_MMU_REGION45_SIZE,
     EL3_MMU_REGIONXX_DATA(45)},       /* Region 45 */
    {BSP_CFG_EL3_MMU_REGION46_VADDR, BSP_CFG_EL3_MMU_REGION46_PADDR, BSP_CFG_EL3_MMU_REGION46_SIZE,
     EL3_MMU_REGIONXX_DATA(46)},       /* Region 46 */
    {BSP_CFG_EL3_MMU_REGION47_VADDR, BSP_CFG_EL3_MMU_REGION47_PADDR, BSP_CFG_EL3_MMU_REGION47_SIZE,
     EL3_MMU_REGIONXX_DATA(47)}        /* Region 47 */
};

/* This vector table is for SGI and PPI interrupts. */
BSP_DONT_REMOVE fsp_vector_t g_sgi_ppi_vector_table[BSP_CORTEX_VECTOR_TABLE_ENTRIES] =
{
    NULL,                              /* INTID0    : SOFTWARE_GENERATE_INT0                                 */
    NULL,                              /* INTID1    : SOFTWARE_GENERATE_INT1                                 */
    NULL,                              /* INTID2    : SOFTWARE_GENERATE_INT2                                 */
    NULL,                              /* INTID3    : SOFTWARE_GENERATE_INT3                                 */
    NULL,                              /* INTID4    : SOFTWARE_GENERATE_INT4                                 */
    NULL,                              /* INTID5    : SOFTWARE_GENERATE_INT5                                 */
    NULL,                              /* INTID6    : SOFTWARE_GENERATE_INT6                                 */
    NULL,                              /* INTID7    : SOFTWARE_GENERATE_INT7                                 */
    NULL,                              /* INTID8    : SOFTWARE_GENERATE_INT8                                 */
    NULL,                              /* INTID9    : SOFTWARE_GENERATE_INT9                                 */
    NULL,                              /* INTID10   : SOFTWARE_GENERATE_INT10                                */
    NULL,                              /* INTID11   : SOFTWARE_GENERATE_INT11                                */
    NULL,                              /* INTID12   : SOFTWARE_GENERATE_INT12                                */
    NULL,                              /* INTID13   : SOFTWARE_GENERATE_INT13                                */
    NULL,                              /* INTID14   : SOFTWARE_GENERATE_INT14                                */
    NULL,                              /* INTID15   : SOFTWARE_GENERATE_INT15                                */
    NULL,                              /* INTID16   : RESERVED                                               */
    NULL,                              /* INTID17   : RESERVED                                               */
    NULL,                              /* INTID18   : RESERVED                                               */
    NULL,                              /* INTID19   : RESERVED                                               */
    NULL,                              /* INTID20   : RESERVED                                               */
    NULL,                              /* INTID21   : RESERVED                                               */
    NULL,                              /* INTID22   : COMMS_CHANNEL_RECEIVE_OR_TRANSMIT_INTERRUPT_REQUEST    */
    NULL,                              /* INTID23   : PMU_INTERRUPT_REQUEST                                  */
    NULL,                              /* INTID24   : CTI_INTERRUPT                                          */
    NULL,                              /* INTID25   : VIRTUAL_CPU_INTERFACE_MAINTENANCE_INTERRUPT_PPI_OUTPUT */
    NULL,                              /* INTID26   : HYPERVISOR_PHYSICAL_TIMER_EVENT                        */
    NULL,                              /* INTID27   : VIRTUAL_TIMER_EVENT                                    */
    NULL,                              /* INTID28   : HYPERVISOR_VIRTUAL_TIMER_EVENT                         */
    NULL,                              /* INTID29   : SECURE_PHYSICAL_TIMER_EVENT                            */
    NULL,                              /* INTID30   : NON-SECURE_PHYSICAL_TIMER_EVENT                        */
    NULL,                              /* INTID31   : RESERVED                                               */
};

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
void bsp_memory_protect_setting(void);
void bsp_irq_cfg_common(void);

void bsp_mmu_configure(void);

void bsp_mmu_writetablelink(st_mmu_table_info_t * p_table_info, uint64_t vaddress, uint64_t next_table_base_ptr);
void bsp_mmu_writetable(st_mmu_table_info_t * p_table_info, r_mmu_pgtbl_cfg_t * p_section_info);

uint64_t bsp_mmu_addresssize_set(uint32_t cfg_index);
uint64_t bsp_mmu_vaddress_set(uint32_t cfg_index);

/*******************************************************************************************************************//**
 * Initialize memory protection settings.
 **********************************************************************************************************************/
void bsp_memory_protect_setting (void)
{
    bsp_mmu_configure();
    R_BSP_CacheInvalidateAll();

    R_BSP_CacheEnableMemoryProtect();
    R_BSP_CacheEnableInst();
    R_BSP_CacheEnableData();
}

/*******************************************************************************************************************//**
 * Initialize common configuration settings for interrupts
 **********************************************************************************************************************/
void bsp_irq_cfg_common (void)
{
    uint64_t reg_value = 0;

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_SYSTEM);

    R_BSP_SlaveStopRelease(BSP_BUS_SLAVE_GIC600);

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_SYSTEM);

    /* ICC_SRE_EL3 */
    reg_value  = 0;
    reg_value |= ICC_SRE_EL3_BIT_Enable;
    reg_value |= ICC_SRE_EL3_BIT_DIB;
    reg_value |= ICC_SRE_EL3_BIT_DFB;
    reg_value |= ICC_SRE_EL3_BIT_SRE;
    __set_CP(3, 6, reg_value, 12, 12, 5); // ICC_SRE_EL3

    /* ICC_SRE_EL1 */
    reg_value  = 0;
    reg_value |= ICC_SRE_EL1_BIT_SRE;
    __set_CP(3, 0, reg_value, 12, 12, 5); // ICC_SRE_EL1

    /* Separate interrupt priority value fields in Group0, Group1 */
    reg_value = 2;                        // Group priority [7:3], Sub priority [2:0]
    __set_CP(3, 0, reg_value, 12, 8, 3);  // ICC_BPR0_EL1
    __set_CP(3, 0, reg_value, 12, 12, 3); // ICC_BPR1_EL1

    /* Set None-secure and secure Affinity Routing Enable */
    reg_value = GICD_CTLR_BIT_ARE_NS | GICD_CTLR_BIT_ARE_S;
    R_BSP_GICD_AffinityRouteEnable((bsp_gicd_ctlr_bit_t) reg_value);

    R_BSP_GICR_Enable();

    R_BSP_GICR_SetSgiPpiSecurityLine(BSP_GIC_IGROUPR_G1NS);

    /* Set interrupt priority mask, priority from 0 to 255 is valid */
    reg_value = ICC_PMR_EL1_VALID_INTERRUPT_PRIORITY;
    __set_CP(3, 0, reg_value, 4, 6, 0); // ICC_PMR_EL1

    /* Set Group1 None-Secure to argument for SPI */
    R_BSP_GICD_SetSpiSecurityAll(BSP_GIC_IGROUPR_G1NS);

    /* Group1 None-secure and Secure are enabled */
    reg_value = ICC_IGRPEN1_EL3_BIT_EnableGrp1S | ICC_IGRPEN1_EL3_BIT_EnableGrp1NS;
    __set_CP(3, 6, reg_value, 12, 12, 7); // ICC_IGRPEN1_EL3
}

/*******************************************************************************************************************//**
 * Configure MMU settings.
 **********************************************************************************************************************/
void bsp_mmu_configure (void)
{
    uint32_t            cfg_index;
    st_mmu_table_info_t table_info;

    __set_TTBR0((uint32_t) (((uint64_t) &g_mmu_ttbr0_base) | 0x01));

    /* Set level1 table */
    table_info.table_level     = BSP_MMU_TABLE_LEVEL_1;
    table_info.table_base_ptr  = (uint64_t) &g_mmu_ttbr0_base;
    table_info.table_base_addr = 0x00000000;

    bsp_mmu_writetablelink(&table_info, BSP_MMU_N1_TABLE_START_VADDR, (uint64_t) &g_mmu_level2_table_1_base);
    bsp_mmu_writetablelink(&table_info, BSP_MMU_N2_TABLE_START_VADDR, (uint64_t) &g_mmu_level2_table_2_base);
    bsp_mmu_writetablelink(&table_info, BSP_MMU_N3_TABLE_START_VADDR, (uint64_t) &g_mmu_level2_table_3_base);
    bsp_mmu_writetablelink(&table_info, BSP_MMU_N4_TABLE_START_VADDR, (uint64_t) &g_mmu_level2_table_4_base);

    for (cfg_index = 0; cfg_index < BSP_MMU_TOTAL_REGION; cfg_index++)
    {
        r_mmu_pgtbl_cfg_t section_info;

        /* Set level2 tables */
        table_info.table_level = BSP_MMU_TABLE_LEVEL_2;

        section_info.vaddress  = g_mmu_pagetable_array[cfg_index].vaddress;
        section_info.paddress  = g_mmu_pagetable_array[cfg_index].paddress;
        section_info.size      = g_mmu_pagetable_array[cfg_index].size;
        section_info.attribute = g_mmu_pagetable_array[cfg_index].attribute;

        /* Set attribute */
        if (BSP_MMU_N2_TABLE_START_VADDR > section_info.vaddress)
        {
            if (BSP_MMU_N4_TABLE_START_VADDR < (section_info.vaddress + section_info.size))
            {
                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_1_base;
                table_info.table_base_addr = BSP_MMU_N1_TABLE_START_VADDR;
                section_info.size          = BSP_MMU_N2_TABLE_START_VADDR - section_info.vaddress;
                bsp_mmu_writetable(&table_info, &section_info);

                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_2_base;
                table_info.table_base_addr = BSP_MMU_N2_TABLE_START_VADDR;
                section_info.size          = BSP_MMU_LEVEL1_TABLE_SIZE;
                section_info.vaddress      = BSP_MMU_N2_TABLE_START_VADDR;
                bsp_mmu_writetable(&table_info, &section_info);

                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_3_base;
                table_info.table_base_addr = BSP_MMU_N3_TABLE_START_VADDR;
                section_info.vaddress      = BSP_MMU_N3_TABLE_START_VADDR;
                section_info.size          = BSP_MMU_LEVEL1_TABLE_SIZE;
                bsp_mmu_writetable(&table_info, &section_info);

                section_info.size     = bsp_mmu_addresssize_set(cfg_index);
                section_info.vaddress = bsp_mmu_vaddress_set(cfg_index);

                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_4_base;
                table_info.table_base_addr = BSP_MMU_N4_TABLE_START_VADDR;
                section_info.size          = section_info.vaddress + section_info.size - BSP_MMU_N4_TABLE_START_VADDR;
                section_info.vaddress      = BSP_MMU_N4_TABLE_START_VADDR;
                bsp_mmu_writetable(&table_info, &section_info);
            }
            else if (BSP_MMU_N3_TABLE_START_VADDR < (section_info.vaddress + section_info.size))
            {
                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_1_base;
                table_info.table_base_addr = BSP_MMU_N1_TABLE_START_VADDR;
                section_info.size          = BSP_MMU_N2_TABLE_START_VADDR - section_info.vaddress;
                bsp_mmu_writetable(&table_info, &section_info);

                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_2_base;
                table_info.table_base_addr = BSP_MMU_N2_TABLE_START_VADDR;
                section_info.size          = BSP_MMU_LEVEL1_TABLE_SIZE;
                section_info.vaddress      = BSP_MMU_N2_TABLE_START_VADDR;
                bsp_mmu_writetable(&table_info, &section_info);

                section_info.size     = bsp_mmu_addresssize_set(cfg_index);
                section_info.vaddress = bsp_mmu_vaddress_set(cfg_index);

                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_3_base;
                table_info.table_base_addr = BSP_MMU_N3_TABLE_START_VADDR;
                section_info.size          = section_info.vaddress + section_info.size - BSP_MMU_N2_TABLE_START_VADDR;
                section_info.vaddress      = BSP_MMU_N3_TABLE_START_VADDR;
                bsp_mmu_writetable(&table_info, &section_info);
            }
            else if (BSP_MMU_N2_TABLE_START_VADDR < (section_info.vaddress + section_info.size))
            {
                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_1_base;
                table_info.table_base_addr = BSP_MMU_N1_TABLE_START_VADDR;
                section_info.size          = BSP_MMU_N2_TABLE_START_VADDR - section_info.vaddress;
                bsp_mmu_writetable(&table_info, &section_info);

                section_info.size = bsp_mmu_addresssize_set(cfg_index);

                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_2_base;
                table_info.table_base_addr = BSP_MMU_N2_TABLE_START_VADDR;
                section_info.size          = section_info.vaddress + section_info.size - BSP_MMU_N2_TABLE_START_VADDR;
                section_info.vaddress      = BSP_MMU_N2_TABLE_START_VADDR;
                bsp_mmu_writetable(&table_info, &section_info);
            }
            else
            {
                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_1_base;
                table_info.table_base_addr = BSP_MMU_N1_TABLE_START_VADDR;
                bsp_mmu_writetable(&table_info, &section_info);
            }
        }
        else if (BSP_MMU_N3_TABLE_START_VADDR > section_info.vaddress)
        {
            if (BSP_MMU_N4_TABLE_START_VADDR < (section_info.vaddress + section_info.size))
            {
                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_2_base;
                table_info.table_base_addr = BSP_MMU_N2_TABLE_START_VADDR;
                section_info.size          = BSP_MMU_N3_TABLE_START_VADDR - section_info.vaddress;
                bsp_mmu_writetable(&table_info, &section_info);

                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_3_base;
                table_info.table_base_addr = BSP_MMU_N3_TABLE_START_VADDR;
                section_info.size          = BSP_MMU_LEVEL1_TABLE_SIZE;
                section_info.vaddress      = BSP_MMU_N3_TABLE_START_VADDR;
                bsp_mmu_writetable(&table_info, &section_info);

                section_info.size     = bsp_mmu_addresssize_set(cfg_index);
                section_info.vaddress = bsp_mmu_vaddress_set(cfg_index);

                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_4_base;
                table_info.table_base_addr = BSP_MMU_N4_TABLE_START_VADDR;
                section_info.size          = section_info.vaddress + section_info.size - BSP_MMU_N4_TABLE_START_VADDR;
                section_info.vaddress      = BSP_MMU_N4_TABLE_START_VADDR;
                bsp_mmu_writetable(&table_info, &section_info);
            }
            else if (BSP_MMU_N3_TABLE_START_VADDR < (section_info.vaddress + section_info.size))
            {
                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_2_base;
                table_info.table_base_addr = BSP_MMU_N2_TABLE_START_VADDR;
                section_info.size          = BSP_MMU_N3_TABLE_START_VADDR - section_info.vaddress;
                bsp_mmu_writetable(&table_info, &section_info);

                section_info.size = bsp_mmu_addresssize_set(cfg_index);

                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_3_base;
                table_info.table_base_addr = BSP_MMU_N3_TABLE_START_VADDR;
                section_info.size          = section_info.vaddress + section_info.size - BSP_MMU_N3_TABLE_START_VADDR;
                section_info.vaddress      = BSP_MMU_N3_TABLE_START_VADDR;
                bsp_mmu_writetable(&table_info, &section_info);
            }
            else
            {
                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_2_base;
                table_info.table_base_addr = BSP_MMU_N2_TABLE_START_VADDR;
                bsp_mmu_writetable(&table_info, &section_info);
            }
        }
        else if (BSP_MMU_N4_TABLE_START_VADDR > section_info.vaddress)
        {
            if (BSP_MMU_N4_TABLE_START_VADDR < (section_info.vaddress + section_info.size))
            {
                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_3_base;
                table_info.table_base_addr = BSP_MMU_N3_TABLE_START_VADDR;
                section_info.size          = BSP_MMU_N4_TABLE_START_VADDR - section_info.vaddress;
                bsp_mmu_writetable(&table_info, &section_info);

                section_info.size = bsp_mmu_addresssize_set(cfg_index);

                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_4_base;
                table_info.table_base_addr = BSP_MMU_N4_TABLE_START_VADDR;
                section_info.size          = section_info.vaddress + section_info.size - BSP_MMU_N4_TABLE_START_VADDR;
                section_info.vaddress      = BSP_MMU_N4_TABLE_START_VADDR;
                bsp_mmu_writetable(&table_info, &section_info);
            }
            else
            {
                table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_3_base;
                table_info.table_base_addr = BSP_MMU_N3_TABLE_START_VADDR;
                bsp_mmu_writetable(&table_info, &section_info);
            }
        }
        else if (BSP_MMU_N5_TABLE_START_VADDR > section_info.vaddress)
        {
            table_info.table_base_ptr  = (uint64_t) &g_mmu_level2_table_4_base;
            table_info.table_base_addr = BSP_MMU_N4_TABLE_START_VADDR;
            bsp_mmu_writetable(&table_info, &section_info);
        }
        else
        {
            table_info.table_level     = BSP_MMU_TABLE_LEVEL_1;
            table_info.table_base_ptr  = (uint64_t) &g_mmu_ttbr0_base[4];
            table_info.table_base_addr = BSP_MMU_N5_TABLE_START_VADDR;
            bsp_mmu_writetable(&table_info, &section_info);
        }
    }

    uint64_t mair = 0;
    mair = ((uint64_t) ATTR_3_2_1_0 | ((uint64_t) ATTR_7_6_5_4 << 32U));

    __set_MAIR(mair);

    __set_TCR((uint64_t) BSP_MMU_TCR);
}

/*******************************************************************************************************************//**
 * Set address size from mmu pagetable.
 *  @param[in]  cfg_index      The number of region number.
 *  @retval     adddress_size  The address size of the region.
 **********************************************************************************************************************/
uint64_t bsp_mmu_addresssize_set (uint32_t cfg_index)
{
    uint64_t address_size = g_mmu_pagetable_array[cfg_index].size;

    return address_size;
}

/*******************************************************************************************************************//**
 * Set virtual address from mmu pagetable.
 *  @param[in] cfg_index  The number of region number.
 *  @retval    vaddress   The beginning virtual address of the region.
 **********************************************************************************************************************/
uint64_t bsp_mmu_vaddress_set (uint32_t cfg_index)
{
    uint64_t vaddress = g_mmu_pagetable_array[cfg_index].vaddress;

    return vaddress;
}

/*******************************************************************************************************************//**
 * Write page table entries as next page table link.
 *  @param[in]     p_table_info  The table information to set a descriptor.
 *  @param[in]     vaddress  Starting address of level 1 table.
 *  @param[in]     next_table_base_ptr  Base address for level 2 table.
 **********************************************************************************************************************/
void bsp_mmu_writetablelink (st_mmu_table_info_t * p_table_info, uint64_t vaddress, uint64_t next_table_base_ptr)
{
    uint64_t offset     = 0;
    uint64_t descriptor = 0;

    /* Calculate page offset */
    if (BSP_MMU_TABLE_LEVEL_1 == p_table_info->table_level)
    {
        offset = ((vaddress - p_table_info->table_base_addr) / BSP_MMU_PA_STRIDE_LEVEL_1) * BSP_MMU_PG_DESC_SIZE;
    }
    else
    {
        offset = ((vaddress - p_table_info->table_base_addr) / BSP_MMU_PA_STRIDE_LEVEL_2) * BSP_MMU_PG_DESC_SIZE;
    }

    /* Make attribute bits */
    descriptor = (next_table_base_ptr | BSP_MMU_PG_ATTR_NEXT_TBL);

    /* Write Page Entry */
    *(uint64_t *) (p_table_info->table_base_ptr + offset) = descriptor;
}

/*******************************************************************************************************************//**
 * Fill page table entries.
 *  @param[in]     p_table_info  The table information to set a descriptor.
 *  @param[in]     p_section_info  The pagetable information.
 **********************************************************************************************************************/
void bsp_mmu_writetable (st_mmu_table_info_t * p_table_info, r_mmu_pgtbl_cfg_t * p_section_info)
{
    volatile int32_t i;
    int32_t          num_of_desc;
    int32_t          table_index;
    uint64_t       * pg_desc_ptr;
    uint32_t         pa_stride;

    if (BSP_MMU_TABLE_LEVEL_1 == p_table_info->table_level)
    {
        pa_stride = BSP_MMU_PA_STRIDE_LEVEL_1;
    }
    else if (BSP_MMU_TABLE_LEVEL_2 == p_table_info->table_level)
    {
        pa_stride = BSP_MMU_PA_STRIDE_LEVEL_2;
    }
    else                               /* BSP_MMU_TABLE_LEVEL_3 */
    {
        pa_stride = BSP_MMU_PA_STRIDE_LEVEL_3;
    }

    num_of_desc = (int32_t) (p_section_info->size / pa_stride);
    table_index = (int32_t) ((p_section_info->vaddress - p_table_info->table_base_addr) / pa_stride);
    pg_desc_ptr = (uint64_t *) (p_table_info->table_base_ptr + ((uint64_t) (table_index * BSP_MMU_PG_DESC_SIZE)));

    for (i = 0; i < num_of_desc; i++)
    {
        if ((p_section_info->attribute & BSP_MMU_DESCRIPTOR_VALID) == BSP_MMU_DESCRIPTOR_VALID)
        {
            *pg_desc_ptr++ = p_section_info->paddress | p_section_info->attribute;
        }
        else
        {
            *pg_desc_ptr++ = (uint64_t) 0U;
        }

        p_section_info->paddress += pa_stride;
    }
}
