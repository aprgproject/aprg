/**
*******************************************************************************
* @file
*
* @brief                 AaCpu inline functions implementation.
*
* Copyright 2016 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _RT_DSP_IFAACPU_INLINE_H
#define _RT_DSP_IFAACPU_INLINE_H

#include "CcsCommon.h"

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <glo_def.h>

/*----------------------- DOXYGEN GROUPS --------------------------------------*/
/**
* @addtogroup dgUpCcs U-Plane specific CC&S API
* @{
*/

/**
* @addtogroup dgUpCcsAaCpu AaCpu API
* @{
*/

/**
* @addtogroup dgUpCcsRtDspAaCpu AaCpu API for RT and OSECK DSP nodes
* @{
*/

/**
* @addtogroup dgUpCcsRtDspAaCpuInlineApi AaCpu Inline API
* @{
* This service provides inline implementation of certain Core Control services.
*
* Users should not include this header directly. Instead include the normal
* SysCom interface header file and indicate intention to use the inline
* implementations with a:
*
* -DAACPU_USE_INLINE_IMPL
*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PRIVATE DECLARATIONS -------------------------------*/

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/*----------------------- PUBLIC INTERFACES ----------------------------------*/

/**
* @name definitions for inline implementation functions
* @{
*/
#define AaCpuBitSwapByteOrder16 AaCpuBitSwapByteOrder16_inlineImpl
#define AaCpuBitSwapByteOrder32 AaCpuBitSwapByteOrder32_inlineImpl
#define AaCpuBitSwapByteOrder64 AaCpuBitSwapByteOrder64_inlineImpl
/** @} */

/**
********************************************************************************
*
* @brief      Changes 16bit value in given address to reversed byte order.
*
* @see        Respective function documentation in IfAaCpu.h
*
*******************************************************************************/
static __CCS_INLINE__ u16 AaCpuBitSwapByteOrder16_inlineImpl(u16 * valuePtr)
{
    const u16 temp = *valuePtr;
    *valuePtr = (u16) ((((u16) temp & (u16) 0x00FF) << 8) |
                       (((u16) temp & (u16) 0xFF00) >> 8));

    return temp;
}


/**
********************************************************************************
*
* @brief      Changes 32bit value in given address to reversed byte order.
*
* @see        Respective function documentation in IfAaCpu.h
*
*******************************************************************************/
static __CCS_INLINE__ u32 AaCpuBitSwapByteOrder32_inlineImpl(u32 * valuePtr)
{
    const u32 temp = *valuePtr;
    *valuePtr = (u32) ((((u32) temp & (u32) 0x000000FFUL) << 24) |
                       (((u32) temp & (u32) 0x0000FF00UL) << 8)  |
                       (((u32) temp & (u32) 0x00FF0000UL) >> 8)  |
                       (((u32) temp & (u32) 0xFF000000UL) >> 24));
    return temp;
}


/**
********************************************************************************
*
* @brief      Changes 64bit value in given address to reversed byte order.
*
* @see        Respective function documentation in IfAaCpu.h
*
*******************************************************************************/
static __CCS_INLINE__ u64 AaCpuBitSwapByteOrder64_inlineImpl (u64 * valuePtr)
{
    const u64 temp = *valuePtr;
    *valuePtr = (u64) ((((u64) temp & (u64) 0x00000000000000FFULL) << 56) |
                       (((u64) temp & (u64) 0x000000000000FF00ULL) << 40) |
                       (((u64) temp & (u64) 0x0000000000FF0000ULL) << 24) |
                       (((u64) temp & (u64) 0x00000000FF000000ULL) << 8)  |
                       (((u64) temp & (u64) 0x000000FF00000000ULL) >> 8)  |
                       (((u64) temp & (u64) 0x0000FF0000000000ULL) >> 24) |
                       (((u64) temp & (u64) 0x00FF000000000000ULL) >> 40) |
                       (((u64) temp & (u64) 0xFF00000000000000ULL) >> 56));
    return temp;
}


/** @} end: @defgroup dgAaCpuInlineApi AaCpu Inline API */

#ifdef __cplusplus
}
#endif
/** @} */   /* dgUpCcsRtDspAaCpuInlineApi */
/** @} */   /* dgUpCcsRtDspAaCpu */
/** @} */   /* dgUpCcsAaCpu */
/** @} */   /* dgUpCcs */

#endif /* _RT_DSP_IFAACPU_INLINE_H */
