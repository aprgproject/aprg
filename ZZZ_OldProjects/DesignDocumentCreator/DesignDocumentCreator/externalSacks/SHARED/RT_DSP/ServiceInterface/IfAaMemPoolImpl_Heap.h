/**
*******************************************************************************
* @file
* $HeadURL$
* $LastChangedRevision$
* $LastChangedDate$
* $Author$
*
* @brief                 Heap based AaMem pool implementation header file.
*
* Copyright 2016 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _RT_DSP_IFAAMEMPOOLIMPL_HEAP_H_
#define _RT_DSP_IFAAMEMPOOLIMPL_HEAP_H_

#include <glo_def.h>
#include <IfAaMem.h>

/*----------------------- DOXYGEN GROUPS --------------------------------------*/
/**
* @addtogroup dgUpCcs U-Plane specific CC&S API
* @{
*/

/**
* @addtogroup dgUpCcsAaMem AaMem API
* @{
*/

/**
* @addtogroup dgUpCcsRtDspAaMem AaMem API for RT and OSECK DSP nodes
* @{
*/

#ifdef __cplusplus
extern "C" {
#endif

/*------------------- PUBLIC INTERFACES (COMMON API) -------------------------*/

/**
*******************************************************************************
*
*   @brief    AaMemHeapSafeAllocator is AaMem pool implementation SAFE allocator
*             for heap.
*
*
*   @param[in]      opaque   Pool impl. specific data - don't care.
*   @param[in]      size     Size of an allocation in bytes.
*   @param[in]      blockId  Wanted memory block id - don't care
*
*   @return         Pointer to the allocated memory block.
*
*   @par Description:
*
*   @par Errors:
*
*   @par Restrictions:
*
*   @par Example:
*   Following example ...
*   @code
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
******************************************************************************/
void* AaMemHeapSafeAllocator(void* opaque, const u32 size, const u32 blockId);


/**
*******************************************************************************
*
*   @brief    AaMemHeapSafeAllocator is AaMem pool implementation UNSAFE
*             allocator for heap.
*
*
*   @param[in]      opaque   Pool impl. specific data - don't care.
*   @param[in]      size     Size of an allocation in bytes.
*   @param[in]      blockId  Wanted memory block id - don't care
*
*   @return         Pointer to the allocated memory block.
*
*   @par Description:
*
*   @par Errors:
*
*   @par Restrictions:
*
*   @par Example:
*   Following example ...
*   @code
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
******************************************************************************/
void* AaMemHeapAllocator(void* opaque, const u32 size, const u32 blockId);

/**
*******************************************************************************
*
*   @brief    AaMemHeapUnAllocator is AaMem pool implementation unallocator
*             for heap.
*
*   @param[in]  blockPtr    Pointer to the pointer of a buffer which will be
*                           unallocated.
*
*   @return
*
*   @par Description:
*
*   @par Errors:
*
*   @par Restrictions:
*
*   @par Example:
*   Following example ...
*   @code
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
******************************************************************************/
void AaMemHeapUnAllocator(void** blockPtr);

#ifdef __cplusplus
}
#endif

/** @} */   /* dgUpCcsRtDspAaMem */
/** @} */   /* dgUpCcsAaMem */
/** @} */   /* dgUpCcs */

#endif /*_RT_DSP_IFAAMEMPOOLIMPL_HEAP_H_*/
