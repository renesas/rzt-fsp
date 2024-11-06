/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_RSIP_UTIL_H
#define R_RSIP_UTIL_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdint.h>

#if defined(__ICCARM__)
 #include "iccarm_builtin.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Byte swapping macro */
#define RSIP_PRV_BSWAP_32_C(data)    ((((data) & 0xff000000U) >> 24) | (((data) & 0x00ff0000U) >> 8) | \
                                      (((data) & 0x0000ff00U) << 8) | (((data) & 0x000000ffU) << 24))

/* Endianness */
#if defined(__ARM_ARCH)
 #define RSIP_PRV_LITTLE_ENDIAN    !__ARM_BIG_ENDIAN
#else
 #error Unsupported architecture.
#endif

/* Changes data endianness to big-endian. */
#if RSIP_PRV_LITTLE_ENDIAN
 #define BSWAP_32BIG_C(data)        RSIP_PRV_BSWAP_32_C(data)
#else
 #define BSWAP_32BIG_C(data)        (data)
#endif

/* Built-in byte swapping function */
#if defined(__GNUC__)
 #define RSIP_PRV_BSWAP_32(data)    __builtin_bswap32(data)
#elif defined(__ICCARM__)
 #define RSIP_PRV_BSWAP_32(data)    __iar_builtin_REV(data)
#else
 #define RSIP_PRV_BSWAP_32(data)    RSIP_PRV_BSWAP_32_C(data)
#endif

/* Static inline */
#if defined(__GNUC__)
 #define RSIP_PRV_STATIC_INLINE     __attribute__((always_inline)) static inline
#elif defined(__ICCARM__)
 #define RSIP_PRV_STATIC_INLINE     _Pragma("inline=forced") static inline
#else
 #define RSIP_PRV_STATIC_INLINE     static inline
#endif

/*
 * Set compiler optimization option for primitive functions.
 * GNU Toolchain: "Os"
 * IAR Embedded Workbench: "size" (enabled only if default optimization level is "high")
 * Other toolchains: no change
 */
#if defined(__GNUC__)
 #define RSIP_PRV_PRIMITIVE_FUNC    __attribute__((optimize("Os")))
#elif defined(__ICCARM__)
 #define RSIP_PRV_PRIMITIVE_FUNC    _Pragma("optimize = size")
#else
 #define RSIP_PRV_PRIMITIVE_FUNC
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Changes data endianness to big-endian.
 *
 * bswap_32big(): For other than const variable. This inline function directly uses ISA.
 *
 * BSWAP_32BIG_C(): For const variable. This macro uses bit shift operation.
 *
 * @param[in] data 32-bit data
 *
 * @return big-endian data
 **********************************************************************************************************************/
RSIP_PRV_STATIC_INLINE uint32_t bswap_32big (uint32_t data)
{
#if RSIP_PRV_LITTLE_ENDIAN
    return RSIP_PRV_BSWAP_32(data);
#else
    return data;
#endif
}

#endif                                 /* R_RSIP_UTIL_H */
