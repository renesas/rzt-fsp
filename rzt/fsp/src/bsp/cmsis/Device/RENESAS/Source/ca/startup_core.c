/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define SCR_EL3_BIT_ST                   (1 << 11)
#define SCR_EL3_BIT_RW                   (1 << 10)
#define SCR_EL3_BIT_EA                   (1 << 3)
#define SCR_EL3_BIT_FIQ                  (1 << 2)
#define SCR_EL3_BIT_IRQ                  (1 << 1)
#define HCR_EL2_BIT_RW                   ((uint64_t) 1 << 31)

#define R_BSP_GIC_INTID_1020             (1020)
#define R_BSP_GIC_INTID_1023             (1023)

#define BSP_PRV_PRCR_KEY                 (0xA500U)
#define BSP_PRV_PRCR_SYSTEM_UNLOCK       ((BSP_PRV_PRCR_KEY) | 0x8U)
#define BSP_PRV_PRCR_LOCK                ((BSP_PRV_PRCR_KEY) | 0x0U)

#if defined(__GNUC__)
 #define BSP_STACK_LIMIT                 &__AArch64StackLimit
 #define BSP_SYSTEMINIT_B_INSTRUCTION \
    {                                 \
        __asm volatile (              \
            "b SystemInit   \n"       \
            ::: "memory");            \
    }                                 \

#elif defined(__ICCARM__)
 #define BSP_STACK_LIMIT                 __section_end(BSP_SECTION_AARCH64_STACK)
 #define BSP_SYSTEMINIT_B_INSTRUCTION    SystemInit();

#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/
#if VECTOR_DATA_IRQ_COUNT > 0
extern fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES];
#endif
extern fsp_vector_t g_sgi_ppi_vector_table[BSP_CORTEX_VECTOR_TABLE_ENTRIES];

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
void system_init(void) BSP_PLACE_IN_SECTION(".loader_text");
void bsp_reset_vector_address_setting(void);

void Default_Handler(void);

/*******************************************************************************************************************//**
 * Default exception handler.
 **********************************************************************************************************************/
void Default_Handler (void)
{
    /** A error has occurred. The user will need to investigate the cause. Common problems are stack corruption
     *  or use of an invalid pointer. Use the Fault Status window in e2 studio or manually check the fault status
     *  registers for more information.
     */
    BSP_CFG_HANDLE_UNRECOVERABLE_ERROR(0);
}

#define WEAK_REF_ATTRIBUTE    __attribute__((weak, alias("Default_Handler")))

void SyncSp0_Handler(void) WEAK_REF_ATTRIBUTE;
void SerrSp0_Handler(void) WEAK_REF_ATTRIBUTE;
void SyncSpx_Handler(void) WEAK_REF_ATTRIBUTE;
void SerrSpx_Handler(void) WEAK_REF_ATTRIBUTE;
void SyncLowEl64_Handler(void) WEAK_REF_ATTRIBUTE;
void IrqLowEl64_Handler(void) WEAK_REF_ATTRIBUTE;
void FiqLowEl64_Handler(void) WEAK_REF_ATTRIBUTE;
void SerrorLowEl64_Handler(void) WEAK_REF_ATTRIBUTE;
void SyncLowEl32_Handler(void) WEAK_REF_ATTRIBUTE;
void IrqLowEl32_Handler(void) WEAK_REF_ATTRIBUTE;
void FiqLowEl32_Handler(void) WEAK_REF_ATTRIBUTE;
void SerrorLowEl32_Handler(void) WEAK_REF_ATTRIBUTE;

void __Vectors(void)                       BSP_PLACE_IN_SECTION(".intvec"); /* branch_to_SyncSp0_Handler */
void branch_to_IrqSp0_Handler(void)        BSP_PLACE_IN_SECTION(".intvec_0x080");
void branch_to_FiqSp0_Handler(void)        BSP_PLACE_IN_SECTION(".intvec_0x100");
void branch_to_SerrSp0_Handler(void)       BSP_PLACE_IN_SECTION(".intvec_0x180");
void branch_to_SyncSpx_Handler(void)       BSP_PLACE_IN_SECTION(".intvec_0x200");
void branch_to_IrqSpx_Handler(void)        BSP_PLACE_IN_SECTION(".intvec_0x280");
void branch_to_FiqSpx_Handler(void)        BSP_PLACE_IN_SECTION(".intvec_0x300");
void branch_to_SerrSpx_Handler(void)       BSP_PLACE_IN_SECTION(".intvec_0x380");
void branch_to_SyncLowEl64_Handler(void)   BSP_PLACE_IN_SECTION(".intvec_0x400");
void branch_to_IrqLowEl64_Handler(void)    BSP_PLACE_IN_SECTION(".intvec_0x480");
void branch_to_FiqLowEl64_Handler(void)    BSP_PLACE_IN_SECTION(".intvec_0x500");
void branch_to_SerrorLowEl64_Handler(void) BSP_PLACE_IN_SECTION(".intvec_0x580");
void branch_to_SyncLowEl32_Handler(void)   BSP_PLACE_IN_SECTION(".intvec_0x600");
void branch_to_IrqLowEl32_Handler(void)    BSP_PLACE_IN_SECTION(".intvec_0x680");
void branch_to_FiqLowEl32_Handler(void)    BSP_PLACE_IN_SECTION(".intvec_0x700");
void branch_to_SerrorLowEl32_Handler(void) BSP_PLACE_IN_SECTION(".intvec_0x780");

__WEAK void FIQ_Handler(void);
__WEAK void IRQ_Handler(void);
void        FIQ_ExecuteHandler(void);
void        IRQ_ExecuteHandler(void);

/* Stacks */
BSP_DONT_REMOVE static uint8_t g_stack[BSP_CFG_STACK_AARCH64_BYTES] BSP_ALIGN_VARIABLE(BSP_STACK_ALIGNMENT)
BSP_PLACE_IN_SECTION(BSP_SECTION_AARCH64_STACK);

/* Heap */
#if (BSP_CFG_HEAP_BYTES > 0)

BSP_DONT_REMOVE static uint8_t g_heap[BSP_CFG_HEAP_BYTES] BSP_ALIGN_VARIABLE(BSP_STACK_ALIGNMENT)
BSP_PLACE_IN_SECTION(BSP_SECTION_HEAP);
#endif

#if defined(__GNUC__)
extern uint64_t __AArch64StackLimit;

#elif defined(__ICCARM__)
 #pragma section=BSP_SECTION_AARCH64_STACK

#endif

/*******************************************************************************************************************//**
 * Vectore table
 *********************************************************************************************************************/

BSP_ATTRIBUTE_STACKLESS void __Vectors (void) /* branch_to_SyncSp0_Handler */
{
    __asm volatile (
        "SyncSp0:                       \n"
        "    B SyncSp0_Handler          \n"
        ::: "memory");
}

BSP_ATTRIBUTE_STACKLESS void branch_to_SerrSp0_Handler (void)
{
    __asm volatile (
        "SerrSp0:                       \n"
        "    WFI                        \n"
        "    B SerrSp0_Handler          \n"
        ::: "memory");
}

BSP_ATTRIBUTE_STACKLESS void branch_to_IrqSp0_Handler (void)
{
    __asm volatile (
        "IrqSp0:                        \n"
        "    B IRQ_Handler              \n"
        ::: "memory");
}

BSP_ATTRIBUTE_STACKLESS void branch_to_FiqSp0_Handler (void)
{
    __asm volatile (
        "FiqSp0:                        \n"
        "    B FIQ_Handler              \n"
        ::: "memory");
}

BSP_ATTRIBUTE_STACKLESS void branch_to_SyncSpx_Handler (void)
{
    __asm volatile (
        "SyncSpx:                       \n"
        "    B SyncSpx_Handler          \n"
        ::: "memory");
}

BSP_ATTRIBUTE_STACKLESS void branch_to_SerrSpx_Handler (void)
{
    __asm volatile (
        "SerrSpx:                       \n"
        "    WFI                        \n"
        "    B SerrSpx_Handler          \n"
        ::: "memory");
}

BSP_ATTRIBUTE_STACKLESS void branch_to_IrqSpx_Handler (void)
{
    __asm volatile (
        "IrqSpx:                        \n"
        "    B IRQ_Handler              \n"
        ::: "memory");
}

BSP_ATTRIBUTE_STACKLESS void branch_to_FiqSpx_Handler (void)
{
    __asm volatile (
        "FiqSpx:                        \n"
        "    B FIQ_Handler              \n"
        ::: "memory");
}

BSP_ATTRIBUTE_STACKLESS void branch_to_SyncLowEl64_Handler (void)
{
    __asm volatile (
        "SyncLowEl64:                   \n"
        "    WFI                        \n"
        "    B SyncLowEl64_Handler      \n"
        ::: "memory");
}

BSP_ATTRIBUTE_STACKLESS void branch_to_IrqLowEl64_Handler (void)
{
    __asm volatile (
        "IrqLowEl64:                    \n"
        "    WFI                        \n"
        "    B IrqLowEl64_Handler       \n"
        ::: "memory");
}

BSP_ATTRIBUTE_STACKLESS void branch_to_FiqLowEl64_Handler (void)
{
    __asm volatile (
        "FiqLowEl64:                    \n"
        "    WFI                        \n"
        "    B FiqLowEl64_Handler       \n"
        ::: "memory");
}

BSP_ATTRIBUTE_STACKLESS void branch_to_SerrorLowEl64_Handler (void)
{
    __asm volatile (
        "SerrorLowEl64:                 \n"
        "    WFI                        \n"
        "    B SerrorLowEl64_Handler    \n"
        ::: "memory");
}

BSP_ATTRIBUTE_STACKLESS void branch_to_SyncLowEl32_Handler (void)
{
    __asm volatile (
        "SyncLowEl32:                   \n"
        "    WFI                        \n"
        "    B SyncLowEl32_Handler      \n"
        ::: "memory");
}

BSP_ATTRIBUTE_STACKLESS void branch_to_IrqLowEl32_Handler (void)
{
    __asm volatile (
        "IrqLowEl32:                    \n"
        "    WFI                        \n"
        "    B IrqLowEl32_Handler       \n"
        ::: "memory");
}

BSP_ATTRIBUTE_STACKLESS void branch_to_FiqLowEl32_Handler (void)
{
    __asm volatile (
        "FiqLowEl32:                    \n"
        "    WFI                        \n"
        "    B FiqLowEl32_Handler       \n"
        ::: "memory");
}

BSP_ATTRIBUTE_STACKLESS void branch_to_SerrorLowEl32_Handler (void)
{
    __asm volatile (
        "SerrorLowEl32:                 \n"
        "    WFI                        \n"
        "    B SerrorLowEl32_Handler    \n"
        ::: "memory");
}

/*******************************************************************************************************************//**
 * After boot processing, LSI starts executing here.
 **********************************************************************************************************************/
BSP_ATTRIBUTE_STACKLESS void system_init (void)
{
    /* Set Vector Base Address Register (VBAR) to point to initializer routine */
    __asm volatile (
        "LDR  x0, =__Vectors                    \n"
        "MSR  VBAR_EL3, x0                      \n"
        "MSR  VBAR_EL2, x0                      \n"
        "MSR  VBAR_EL1, x0                      \n"
        ::: "memory");

    /* Top of level system control init at each EL level
     *  Stop the following systems
     *  MMU, cache, and some memory control system, Tag check fault, pointer authentication */
    __asm volatile (
        "MOV  x0, #0                            \n"
        "MSR  SCTLR_EL3, x0                     \n"
        "MSR  SCTLR_EL2, x0                     \n"
        "MSR  SCTLR_EL1, x0                     \n"
        ::: "memory");

    /* Setting up Stack Area (EL3) */
    __asm volatile (
        "MOV  x1, %0 \n"
        "MOV  sp, x1 \n"
        ::"r" (BSP_STACK_LIMIT) : "memory");

    /* Stop trapping to EL3 or EL2 for low EL level tracing,
     *  activity monitoring, SVE, and access to SIMD and floating point features */
    __asm volatile (
        "MOV  x0, #0                            \n"
        "MSR  CPTR_EL3, x0                      \n"
        "MSR  CPTR_EL2, x0                      \n"
        ::: "memory");

    /* Secure configuration */
    __asm volatile (
        "MSR  SCR_EL3, xzr                      \n"
        "ISB                                    \n"
        "MOV  w1, #0                            \n"
        "ORR  w1, w1, %[scr_el3_bit_st]         \n"
        "ORR  w1, w1, %[scr_el3_bit_rw]         \n"
        "ORR  w1, w1, %[scr_el3_bit_ea]         \n"
        "ORR  w1, w1, %[scr_el3_bit_fiq]        \n"
        "ORR  w1, w1, %[scr_el3_bit_irq]        \n"
        "MSR  SCR_EL3, x1                       \n"
        "ISB                                    \n"
        ::[scr_el3_bit_st] "i" (SCR_EL3_BIT_ST),
        [scr_el3_bit_rw] "i" (SCR_EL3_BIT_RW),
        [scr_el3_bit_ea] "i" (SCR_EL3_BIT_EA),
        [scr_el3_bit_fiq] "i" (SCR_EL3_BIT_FIQ),
        [scr_el3_bit_irq] "i" (SCR_EL3_BIT_IRQ) : "memory");

    /* Set EL1 to execute with Aarch64 */
    __asm volatile (
        "MOV  x2, %[hcr_el2_bit_rw]             \n"
        "MSR  HCR_EL2, x2                       \n"
        ::[hcr_el2_bit_rw] "i" (HCR_EL2_BIT_RW) : "memory");

    /* Copy the multiprocessor ID information to the virtual multiprocessor ID register */
    __asm volatile (
        "MRS  x0, MPIDR_EL1                     \n"
        "MSR  VMPIDR_EL2, x0                    \n"
        ::: "memory");

    /* Copy processing element information to the virtual processor ID register */
    __asm volatile (
        "MRS  x0, MIDR_EL1                      \n"
        "MSR  VPIDR_EL2, x0                     \n"
        ::: "memory");

    /* Set 0 to Virtual Translation Table Address */
    __asm volatile (
        "MSR  VTTBR_EL2, xzr                    \n"
        ::: "memory");

    /* Set system counter frequency */
    __asm volatile (
        "MOV  x0, %0                            \n"
        "MSR  CNTFRQ_EL0, x0                    \n"
        ::"r" (BSP_GLOBAL_SYSTEM_COUNTER_CLOCK_HZ) : "memory");

    /* TLB maintenance, Invalidate Data and Instruction TLBs */
    __asm volatile (
        "TLBI ALLE3                             \n" /* Cortex-A55 I-TLB and D-TLB invalidation (TLBIALL) */
        ::: "memory");

    /* Invalidate instruction cache, also flushes BTAC */
    __asm volatile (
        "IC IALLUIS                             \n" /* ICIALLUIS - Instruction Cache Invalidate All to PoU */
        ::: "memory");

    __asm volatile (
        "b bsp_reset_vector_address_setting     \n"
        ::: "memory");
}

void bsp_reset_vector_address_setting (void)
{
    R_RWP_S->PRCRS = (uint16_t) BSP_PRV_PRCR_SYSTEM_UNLOCK;

#if (0 == BSP_CFG_CORE_CA55)
    R_CA55->RVBA[0].L = (uint32_t) ((uintptr_t) &system_init);
#elif (1 == BSP_CFG_CORE_CA55)
    R_CA55->RVBA[1].L = (uint32_t) ((uintptr_t) &system_init);
#elif (2 == BSP_CFG_CORE_CA55)
    R_CA55->RVBA[2].L = (uint32_t) ((uintptr_t) &system_init);
#elif (3 == BSP_CFG_CORE_CA55)
    R_CA55->RVBA[3].L = (uint32_t) ((uintptr_t) &system_init);
#endif

    R_RWP_S->PRCRS = (uint16_t) BSP_PRV_PRCR_LOCK;

    BSP_SYSTEMINIT_B_INSTRUCTION
}

/*******************************************************************************************************************//**
 * FIQ handler Function.
 *********************************************************************************************************************/
__WEAK void FIQ_Handler (void)
{
    __asm volatile (
        "STP  x29, x30, [SP, #-0x10]!           \n"
        "STP  x18, x19, [SP, #-0x10]!           \n"
        "STP  x16, x17, [SP, #-0x10]!           \n"
        "STP  x14, x15, [SP, #-0x10]!           \n"
        "STP  x12, x13, [SP, #-0x10]!           \n"
        "STP  x10, x11, [SP, #-0x10]!           \n"
        "STP  x8, x9, [SP, #-0x10]!             \n"
        "STP  x6, x7, [SP, #-0x10]!             \n"
        "STP  x4, x5, [SP, #-0x10]!             \n"
        "STP  x2, x3, [SP, #-0x10]!             \n"
        "STP  x0, x1, [SP, #-0x10]!             \n"

#if __FPU_USED
        "STP  d30, d31, [SP, #-0x10]!           \n"
        "STP  d28, d29, [SP, #-0x10]!           \n"
        "STP  d26, d27, [SP, #-0x10]!           \n"
        "STP  d24, d25, [SP, #-0x10]!           \n"
        "STP  d22, d23, [SP, #-0x10]!           \n"
        "STP  d20, d21, [SP, #-0x10]!           \n"
        "STP  d18, d19, [SP, #-0x10]!           \n"
        "STP  d16, d17, [SP, #-0x10]!           \n"
        "STP  d6, d7, [SP, #-0x10]!             \n"
        "STP  d4, d5, [SP, #-0x10]!             \n"
        "STP  d2, d3, [SP, #-0x10]!             \n"
        "STP  d0, d1, [SP, #-0x10]!             \n"
#endif

        /* Save the SPSR and ELR. */
        "MRS  x3, SPSR_EL3                      \n"
        "MRS  x2, ELR_EL3                       \n"
        "STP  x2, x3, [sp, #-0x10]!             \n"

        "BL   FIQ_ExecuteHandler                \n"

        /* Restore volatile registers. */
        "LDP  x4, x5, [sp], #0x10               \n" /* SPSR and ELR. */

        "MSR  SPSR_EL3, x5                      \n"
        "MSR  ELR_EL3, x4                       \n"
        "DSB  SY                                \n"
        "ISB  SY                                \n"

#if __FPU_USED
        "LDP  d0, d1, [sp], #0x10               \n"
        "LDP  d2, d3, [sp], #0x10               \n"
        "LDP  d4, d5, [sp], #0x10               \n"
        "LDP  d6, d7, [sp], #0x10               \n"
        "LDP  d16, d17, [sp], #0x10             \n"
        "LDP  d18, d19, [sp], #0x10             \n"
        "LDP  d20, d21, [sp], #0x10             \n"
        "LDP  d22, d23, [sp], #0x10             \n"
        "LDP  d24, d25, [sp], #0x10             \n"
        "LDP  d26, d27, [sp], #0x10             \n"
        "LDP  d28, d29, [sp], #0x10             \n"
        "LDP  d30, d31, [sp], #0x10             \n"
#endif

        "LDP  x0, x1, [sp], #0x10               \n"
        "LDP  x2, x3, [sp], #0x10               \n"
        "LDP  x4, x5, [sp], #0x10               \n"
        "LDP  x6, x7, [sp], #0x10               \n"
        "LDP  x8, x9, [sp], #0x10               \n"
        "LDP  x10, x11, [sp], #0x10             \n"
        "LDP  x12, x13, [sp], #0x10             \n"
        "LDP  x14, x15, [sp], #0x10             \n"
        "LDP  x16, x17, [sp], #0x10             \n"
        "LDP  x18, x19, [sp], #0x10             \n"
        "LDP  x29, x30, [sp], #0x10             \n"

        "ERET                                   \n"
        ::: "memory");
}

/*******************************************************************************************************************//**
 * IRQ handler Function.
 *********************************************************************************************************************/
__WEAK void IRQ_Handler (void)
{
    __asm volatile (
        "MSR  SPSEL, #0                         \n"
        "STP  x0, x1, [sp, #-0x10]!             \n"
        "STP  x2, x3, [sp, #-0x10]!             \n"
        "STP  x4, x5, [sp, #-0x10]!             \n"
        "STP  x6, x7, [sp, #-0x10]!             \n"
        "STP  x8, x9, [sp, #-0x10]!             \n"
        "STP  x10, x11, [sp, #-0x10]!           \n"
        "STP  x12, x13, [sp, #-0x10]!           \n"
        "STP  x14, x15, [sp, #-0x10]!           \n"
        "STP  x16, x17, [sp, #-0x10]!           \n"
        "STP  x18, x19, [sp, #-0x10]!           \n"
        "STP  x29, x30, [sp, #-0x10]!           \n"
        "BL   IRQ_ExecuteHandler                \n"
        "LDP  x29, x30, [sp], #0x10             \n"
        "LDP  x18, x19, [sp], #0x10             \n"
        "LDP  x16, x17, [sp], #0x10             \n"
        "LDP  x14, x15, [sp], #0x10             \n"
        "LDP  x12, x13, [sp], #0x10             \n"
        "LDP  x10, x11, [sp], #0x10             \n"
        "LDP  x8, x9, [sp], #0x10               \n"
        "LDP  x6, x7, [sp], #0x10               \n"
        "LDP  x4, x5, [sp], #0x10               \n"
        "LDP  x2, x3, [sp], #0x10               \n"
        "LDP  x0, x1, [sp], #0x10               \n"
        "ERET                                   \n"
        ::: "memory");
}

/*******************************************************************************************************************//**
 * IRQ handler Function.
 * This function calls the interrupt function registered in the vector table.
 *********************************************************************************************************************/
void IRQ_ExecuteHandler (void)
{
    uint32_t       int_id;
    fsp_vector_t * p_vector;
    IRQn_Type      irq;

    int_id = R_BSP_GICC_Get_IntIdGrp1();

    irq = (IRQn_Type) (int_id - BSP_CORTEX_VECTOR_TABLE_ENTRIES);

#if VECTOR_DATA_IRQ_COUNT > 0
    if (BSP_CORTEX_VECTOR_TABLE_ENTRIES <= int_id)
    {
        p_vector = &g_vector_table[irq];
    }
    else
#endif
    {
        p_vector = &g_sgi_ppi_vector_table[int_id];
    }

    if (p_vector)
    {
        g_current_interrupt_num[g_current_interrupt_pointer++] = irq;
        __asm volatile ("dmb sy");

        (*p_vector)();
    }

    R_BSP_GICC_SetEoiGrp1(irq);
}

/*******************************************************************************************************************//**
 * FIQ handler Function.
 * This function calls the interrupt function registered in the vector table.
 *********************************************************************************************************************/
void FIQ_ExecuteHandler (void)
{
    uint32_t  int_id[2];
    uint32_t  aliased = 0;
    uint32_t  target_int_id;
    IRQn_Type irq;

    int_id[0]     = R_BSP_GICC_Get_IntIdGrp0();
    target_int_id = int_id[0];

    if ((R_BSP_GIC_INTID_1020 <= int_id[0]) && (int_id[0] <= R_BSP_GIC_INTID_1023))
    {
        int_id[1]     = R_BSP_GICC_Get_IntIdGrp1();
        aliased       = 1;
        target_int_id = int_id[1];

        if ((R_BSP_GIC_INTID_1020 <= int_id[1]) && (int_id[1] <= R_BSP_GIC_INTID_1023))
        {
            return;
        }
    }

    irq = (IRQn_Type) (target_int_id - BSP_CORTEX_VECTOR_TABLE_ENTRIES);

    g_current_interrupt_num[g_current_interrupt_pointer++] = irq;
    __asm volatile ("dmb sy");

    /* Enable nested interrupts */
    BSP_INTERRUPT_ENABLE;

#if VECTOR_DATA_IRQ_COUNT > 0
    if (BSP_CORTEX_VECTOR_TABLE_ENTRIES <= target_int_id)
    {
        g_vector_table[irq]();
    }
    else
#endif
    {
        g_sgi_ppi_vector_table[target_int_id]();
    }

    /* Disable nested interrupts */
    BSP_INTERRUPT_DISABLE;

    g_current_interrupt_pointer--;

    if (0 == aliased)
    {
        R_BSP_GICC_SetEoiGrp0(irq);
    }
    else
    {
        R_BSP_GICC_SetEoiGrp1(irq);
    }
}
