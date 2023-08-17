/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 Memory Management Service API header file
* @module                AaMem
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/
#ifndef _IFAAMEM_H
#define _IFAAMEM_H

/*----------------------- INCLUDED FILES --------------------------------------*/
#include <CcsCommon.h>
#include <AaMemCcsPoolDefinitions.h>
#include <glo_def.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <../Definitions/IfAaMem_Defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*------------------- PUBLIC INTERFACES (COMMON API) -------------------------*/

/**
 * @defgroup dgAaMem AaMem API
 */

/**
 * @defgroup dgAaMemApiCommon AaMem COMMON API
 * @ingroup dgAaMem
 */

/* @{ */

/**
*******************************************************************************
*
*   @brief    Allocates dynamic memory block from a specific pool in safe manner
*
*   @note <b>For safe pool operation mode only!</b>
*
*   @param[in] poolId  Identifier of a pool where allocation takes place. Identifier is:
*                         - Id of a system pool or target specific system pool.
*                         - Id of an application specific pool, attached with AaMemPoolAttach.
*   @param[in] size    Allocation size in bytes.
*
*   @return    Pointer to newly allocated memory block. Never GLO_NULL.
*
*   @par Description:
*   This function allocates a dynamic memory block from a specific pool and sets the
*   memory block reference counter to 1. If this function returns it is guaranteed that
*   always a pointer to a valid memory block is returned. If an unrecoverable exception
*   occurs, this function never returns. In this case it is unspecified in what state
*   the calling EE/EU will be afterwards.
*   \n\n
*   The address of an allocated memory block is always aligned at least to a word (32 bits)
*   or to a multiple of 32 bits. (Current aligment is reflected by define directive
*   AAMEM_CURRENT_ALIGNMENT.)
*   \n\n
*   For more details see @variation
*
*   @par Errors:
*   In case of failure a fatal exception is raised and handled by AaMem internally.
*   If memory allocation is uncussessful, following reasons may lead to that:
*      - There is no corresponding pool for passed pool id.
*      - Requested allocation size exceeds pool's current (continuous) free space capacity.
*      - Pool does not support requested allocation size.
*
*   @par Restrictions:
*   Pool implementation:
*      - May limit maximum allocation size.
*      - May restrict the use of the allocated memory.
*      - Must be in safe mode.
*
*   @par Example:
*
*   @code
*
*   u32* somePointer;
*
*   somePointer = (u32*)AaMemAllocSafe(EAaMemSysPoolId_Private, sizeof(u32));
*
*   // somePointer points now to a valid memory block.
*   // Since allocated in safe manner, it can be dereferenced without further checks.
*
*   *somePointer = 123;
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   AAMEM_ALLOC_SAFE is preferred in DSP environment to get debug data.
*
*   @see AaMemUnRef
*
******************************************************************************/
void* AaMemAllocSafe( i32 const poolId, u32 const size );

/**
*******************************************************************************
*
*   @brief    Allocates dynamic memory block UNSAFE manner
*
*   @param[in] poolId  Identifier of a pool where allocation takes place. Identifier is:
*                         - Id of a system pool or target specific system pool.
*                         - Id of an application specific pool, attached with AaMemPoolAttach.
*   @param[in] size    Size of an allocation in bytes.
*
*   @return    Pointer to newly allocated memory block or in case of error,
*              GLO_NULL is returned.
*
*   @par Description:
*   Allocates dynamic memory block from specific pool and sets memory block
*   reference counter to 1. In failure, GLO_NULL value will be returned and it is
*   caller's responsibility to check return value.
*   \n\n
*   Address of an allocated memory block is always aligned atleast to 32 bits
*   (word) or multiple of 32 bits. Currently used aligment is set to AAMEM_CURRENT_ALIGNMENT.
*   \n\n
*   For more details see @variation.
*
*   @par Errors:
*   In case of failure, fatal exception is raised and handled by AaMem internally.
*   If memory allocation is uncussessful, following reasons may be lead to that:
*      - There is no corresponding pool for defined pool id.
*      - Requested allocation size exceeds pool's current (continuous) free space capacity.
*      - Pool does not support requested allocation size.
*
*   @par Restrictions:
*   Pool implementation:
*      - May limit maximum allocation size.
*      - May restrict the use of the allocated memory.
*
*   @par Example:
*
*   @code
*
*   u32* ptr;
*
*   ptr = (u32*)AaMemAlloc(EAaMemSysPoolId_Private, sizeof(u32));
*
*   // Check return value validity
*   if (ptr != GLO_NULL) {
*     // OK
*   } else {
*     // Error
*   }
*
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
*   @see AaMemMalloc
*   @see AaMemUnRef
*
******************************************************************************/
void* AaMemAlloc( i32 const poolId, u32 const size );

/**
*******************************************************************************
*
*   @brief    Allocates dynamic memory block from BDM pool UNSAFE manner
*
*
*   @param[in] size  Size of an allocation in bytes.
*
*   @return    Pointer to newly allocated memory block or in case of error,
*              GLO_NULL is returned.
*
*   @par Description:
*   Allocates dynamic memory block from EAaMemSysPoolId_Private (BDM) and sets
*   memory block reference counter to 1. In failure, GLO_NULL value will be
*   returned and it is caller's responsibility to check return value.
*   \n\n
*   Address of an allocated memory block is always aligned atleast to 32 bits
*   (word) or multiple of 32 bits. Currently used aligment is set to AAMEM_CURRENT_ALIGNMENT.
*   \n\n
*   For more details see @variation.
*
*   @par Errors:
*   In case of failure, fatal exception is raised and handled by AaMem internally.
*   If memory allocation is uncussessful, following reasons may be lead to that:
*      - Requested allocation size exceeds pool's current (continuous) free space capacity.
*      - Pool does not support requested allocation size.
*
*   @par Restrictions:
*   Pool implementation:
*      - May limit maximum allocation size.
*      - May restrict the use of the allocated memory.
*
*   @par Example:
*   Following example ...
*   @code
*
*   u32* ptr;
*
*   ptr = (u32*)AaMemMalloc(sizeof(u32));
*
*   // Check return value validity
*   if (ptr != GLO_NULL) {
*     // OK
*   } else {
*     // Error
*   }
*
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
*   @see AaMemAlloc
*   @see AaMemUnRef
*
******************************************************************************/
void* AaMemMalloc( u32 const size );


/**
*******************************************************************************
*
*   @brief    Removes refrerence from allocated memory block
*
*
*   @param[in] ptr  Pointer to a pointer to allocated memory block (Note: will be NULLed).
*
*   @return    None
*
*   @par Description:
*   If number of references gets to zero (0), the block is automatically freed.
*   By setting correct number of references by using AaMemRef function, and
*   removing references when memory is not needed, the block will be released
*   after the last reference is removed. Given pointer is set to GLO_NULL.
*   \n\n
*   If user has set memory block object class to the allocated memory block with
*   destructor function pointer, the function shall be called if references gets
*   to zero (0) before the given memory block is freed.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   u32* somePointer;
*
*   somePointer = (u32*)AaMemAlloc(EAaMemSysPoolId_Private, sizeof(u32));
*   AaMemUnRef(&somePointer); // Memory gets released
*
*   // second example:
*
*   u32* somePointer;
*   u32* somePointer2;
*
*   somePointer = (u32*)AaMemAlloc(EAaMemSysPoolId_Private, sizeof(u32));
*   somePointer2 = somePointer;
*
*   AaMemRef(somePointer); // Add reference
*
*   AaMemUnRef(&somePointer); // Reference counter is updated and pointer is nulled
*   AaMemUnRef(&somePointer2); // Memory gets released and pointer is nulled
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   This is useful for cases where to asynchronous events refer to same memory block.
*
*   @par Future directions:
*   None
*
*   @see AaMemAlloc
*   @see AaMemRef
*
******************************************************************************/
void AaMemUnRef( void const** const ptr );

/**
*******************************************************************************
*
*   @brief   Returns a size of an allocated memory block
*
*
*   @param[in] ptr  Pointer to allocated memory block.
*
*   @return    Size of allocated memory block in bytes
*
*   @par Description:
*   This function returns the size of the given memory block in bytes. In
*   practise, the returned size corresponds the size requested via AaMemAlloc and
*   its variants.
*
*   @par Errors:
*
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
*   void* somePointer;
*   u32  size;
*
*   somePointer = AaMemAlloc(EAaMemSysPoolId_Private, 300);
*
*   size = AaMemSizeGet(somePointer);
*
*   // size is now 300
*
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
*   @see AaMemAlloc
*
******************************************************************************/
u32 AaMemSizeGet( void const* const ptr );

/**
*******************************************************************************
*
*   @brief    Allocates dynamic memory block from a specific pool in safe manner
*             and sets block id to an user defined value
*
*   @note <b>For safe pool operation mode only!</b>
*
*   @param[in] poolId  Identifier of a pool where allocation takes place. Identifier is:
*                         - Id of a system pool or target specific system pool.
*                         - Id of an application specific pool, attached with AaMemPoolAttach.
*   @param[in] size    Allocation size in bytes.
*   @param[in] blockId User defined id for allocated memory block.
*
*   @return    Pointer to newly allocated memory block. Never GLO_NULL.
*
*   @par Description:
*   This function allocates a dynamic memory block from a specific pool and sets the
*   memory block reference counter to 1.
*   Additionally the allocated memory block's identifier will be set to passed user value.
*   If this function returns it is guaranteed that always a pointer to a valid memory block
*   is returned. If an unrecoverable exception occurs, this function never returns. It this
*   case it is unspecified in what state the calling EE/EU will be afterwards.
*   \n\n
*   The address of an allocated memory block is always aligned at least to a word (32 bits)
*   or to a multiple of 32 bits. (Current aligment is reflected by define directive
*   AAMEM_CURRENT_ALIGNMENT.)
*   \n\n
*   For more details see @variation.
*
*   @par Errors:
*   In case of failure a fatal exception is raised and handled by AaMem internally.
*   If memory allocation is uncussessful, following reasons may lead to that:
*      - There is no corresponding pool for defined pool id.
*      - Requested allocation size exceeds pool's current (continuous) free space capacity.
*      - Pool does not support requested allocation size.
*
*   @par Restrictions:
*   Pool implementation:
*      - May limit maximum allocation size.
*      - May restrict the use of the allocated memory.
*      - Must be in safe mode.
*
*   @par Example:
*
*   @code
*
*   void* somePointer;
*
*   somePointer = AaMemAllocSafeId(EAaMemSysPoolId_Private, 300, 0x10102020);
*
*   // somePointer points to valid memory block.
*   // Since allocated in safe manner, it can be used without further checks.
*
*   memset(somePointer, 0, 300);
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   AAMEM_ALLOC_SAFE_ID is preferred in DSP environment to get debug data.
*
*   @see AaMemAllocSafe
*   @see AaMemUnRef
*
******************************************************************************/
void* AaMemAllocSafeId( i32 const poolId, u32 const size, u32 const blockId );

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /*  _IFAAMEM_H */
