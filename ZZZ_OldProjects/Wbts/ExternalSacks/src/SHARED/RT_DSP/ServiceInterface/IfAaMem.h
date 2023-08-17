/**
*******************************************************************************
* @file
* $HeadURL$
* $LastChangedRevision$
* $LastChangedDate$
* $Author$
*
* @brief                 BMM based AaMem pool implementation header file.
*
* Copyright 2016 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _RT_DSP_IFAAMEM_H_
#define _RT_DSP_IFAAMEM_H_

#include <CcsCommon.h>

#include "../../../COMMON/ServiceInterface/IfAaMem.h"

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

/** @brief Informs about availability of memory management service per EE. */
#define AAMEM_CONFIG_TAG_MEM_ONLINE "sys.mem.online"

/** @cond */
/** @brief Constant for AaMem memory block internal overhead set by AaMem implementation */
extern const i32 AaMemBlockInternalOverhead;
/** @brief Constant for AaMem MDM pool maximum allocation size set by AaMem implementation */
extern const i32 AaMemMdmMaxAllocSize;
/** @endcond */

#ifndef AAMEM_MAX_POOL_NAME_LENGTH
/** @brief Maximum length of a pool name */
# define AAMEM_MAX_POOL_NAME_LENGTH  64
#endif

#ifndef AAMEM_CURRENT_ALIGNMENT
/** @brief Current aligment of system pools (in bits) */
# define AAMEM_CURRENT_ALIGNMENT     32
#endif

/** @brief Internal overhead needed by AaMem per memory block in bytes */
#define AAMEM_MEM_BLOCK_INTERNAL_OVERHEAD AaMemBlockInternalOverhead

/** @brief End-mark for memory block */
#define AAMEM_MEM_BLOCK_ENDMARK 0x50

/** @brief End-mark lenght in bytes */
#define AAMEM_MEM_BLOCK_ENDMARK_LENGTH 4

/** @brief Maximum MDM allocation size */
#define AAMEM_MDM_MAX_ALLOC_SIZE AaMemMdmMaxAllocSize

/** @brief AaMem system pool ids in convenience textual representation */
#define EAAMEMSYSPOOLID_VALUES \
   { \
       "EAaMemSysPoolId_Private", \
       "EAaMemSysPoolId_Shared", \
       "EAaMemSysPoolId_Msg", \
       "EAaMemSysPoolId_NbrOf", \
   }

/** @brief AaMem pool category ids. */
typedef enum EAaMemPoolCid
{
    EAaMemPoolCid_System = 0,
    EAaMemPoolCid_Dynamic,
    EAaMemPoolCid_ApplicationCidStart
} EAaMemPoolCid;

/** @brief AaMem pool category ids in convenience textual representation */
#define EAAMEMPOOLCID_VALUES \
    { \
        "EAaMemPoolCid_System", \
        "EAaMemPoolCid_Dynamic", \
        "EAaMemPoolCid_ApplicationCidStart", \
    }

/** @brief AaMem pool operation mode */
typedef enum EAaMemPoolMode
{
    EAaMemPoolMode_Safe = 0, /**< Safe pool operation mode (i.e. QoS is guaranteed) */
    EAaMemPoolMode_Unsafe,   /**< Unsafe pool operation mode (i.e. QoS is best-effort) */
    EAaMemPoolMode_HwPool,   /**< Hw Pool mode (using Hw memory allocation, no reference avaliable) */

    EAaMemPoolMode_NbrOf     /**< Last one. And keep it that way! */

} EAaMemPoolMode;

/** @brief AaMem pool operation modes in convenience textual representation */
#define EAAMEMPOOLMODE_VALUES \
   { \
       "EAaMemPoolMode_Safe", \
       "EAaMemPoolMode_Unsafe", \
       "EAaMemPoolMode_NbrOf", \
   }

/** @brief Pool implementation trace modes */
typedef enum
{
    EAaMemPoolTraceMode_Off = 0, /**< No tracing enabled for pool */
    EAaMemPoolTraceMode_Minimal, /**< Minimal tracing enabled (only allocs) */
    EAaMemPoolTraceMode_Normal,  /**< Normal tracing enabled (allocs and unrefs) */

    EAaMemPoolTraceMode_All,     /**< All tracing enabled */

    EAaMemPoolTraceMode_NbrOf    /**< Keep always last and do not remove */

} EAaMemPoolTraceMode;

/** @brief AaMem pool trace modes in convenience textual representation */
#define EAAMEMPOOLTRACEMODE_VALUES \
   { \
       "EAaMemPoolTraceMode_Off", \
       "EAaMemPoolTraceMode_Minimal", \
       "EAaMemPoolTraceMode_Normal", \
       "EAaMemPoolTraceMode_All", \
       "EAaMemPoolTraceMode_NbrOf" \
   }

/** @brief AaMem return codes in convenience textual representation */
#define EAAMEMRET_VALUES \
   { \
       "EAaMemRet_Ok", \
       "EAaMemRet_NullParameter", \
       "EAaMemRet_UnexistentPoolId", \
       "EAaMemRet_RefCountMaxLimitExceeded", \
       "EAaMemRet_InvalidEndmark" \
       "EAaMemRet_InvalidOperationMode" \
       "EAaMemRet_InitializationFailure" \
       "EAaMemRet_OperationNotSupported" \
       "EAaMemRet_PoolNameConflict" \
       "EAaMemRet_InvalidPoolId" \
       "EAaMemRet_MaxAttachedPools" \
       "EAaMemRet_NbrOf" \
   }


/** @brief Structure for containing pool information data.
*
* Pool implementation does not need to provide all information.
* Optional members and members set by AaMem are marked and
* they should be set to 0 or in case of set by AaMem, left untouched.
*
* Member #SAaMemPoolInfo.largestFreeBuffer is optional but can be set to
* #SAaMemPoolInfo.maxAllocSize if pool implements fixed size blocks.
*
* @warning Do not put this struct into any message! Type size_t is not
*          constant in size instead it is 32bit in 32bit systems and
*          64bit in 64bit systems.
*
*/
typedef struct SAaMemPoolInfo
{
    EAaMemPoolMode      poolMode;             /**< The operation mode of the pool. Set by AaMem automatically. */
    EAaMemPoolTraceMode poolTraceMode;        /**< Pool trace mode. Set by AaMem automatically. */
    i32                 poolId;               /**< The id of the pool. Set by AaMem automatically. */
    size_t              size;                 /**< Total pool size in bytes quaranteed for allocations
                                                   (including internal house-keeping data).
                                                   Set by pool implementation. [Mandatory] */
    size_t              theoreticalMaxSize;   /**< Total theoretical maximum pool size in bytes.
                                                   This gives maximum size which in some circumstances can be
                                                   achieved but not quaranteed (e.g. Linux heap). AaMemAdapter
                                                   relies on this information while doing 'pool almost full'
                                                   checkings. May be equal to #size. Set by pool implementation. [Optional] */
    size_t              totalAllocs;          /**< Total number of allocations currently active.
                                                   Set by pool implementation. [Mandatory] */
    size_t              totalAllocSize;       /**< Total size of all allocations currently active
                                                   (including house-keeping data).
                                                   Set by pool implementation. [Mandatory] */
    size_t              maxAllocSize;         /**< Maximum allocation size for a memory block.
                                                   Abolute maximum block size which can be requested from the pool.
                                                   Set by pool implementation. [Optional] */
    size_t              largestFreeBuffer;    /**< Largest continuous allocation size. May vary during operation
                                                   and should always be <= maxAllocSize. [Optional] */
    size_t              reqByteCount;         /**< Total size of all allocations currently active
                                                   (excluding house-keeping data). [Optional] */
    size_t              peakAlloc;            /**< Peak total size of all active allocations
                                                   (including house-keeping data). [Optional] */
    char                poolName[AAMEM_MAX_POOL_NAME_LENGTH];   /**< Pool name. Set by AaMem automatically. */
} SAaMemPoolInfo;

/** @brief Structure for containing memory block information for inter-EE/EU communication. */
typedef struct SAaMemBlockObj
{
    i32 poolId; /**< Pool ID from where the memory block were originally allocated. */
    u32 offset; /**< Offset inside the pool from where allocation took place.
                     Offset is actually pool implementation specific and should not
                     be used directly by application. */

} SAaMemBlockObj;

/** @name Memory block object class related definitions
*
* @{
*/

/**
* @brief Type definitions for memory block object class destructor function
*
* Pointer to a function implementing memory block destructor, which shall be
* called when user calls AaMemUnRef and reference count will be descreased to zero.
* Parameter for the function pointer shall be the pointer of the memory block given
* to AaMemUnRef.
*
* @param[in] obj  Pointer to start of memory block payload
*/
typedef void TAaMemBlockObjDestr (void const * obj);

/** @brief Structure for containing memory block object class information. */
typedef struct SAaMemBlockObjClass
{
    TAaMemBlockObjDestr* destructor; /**< Pointer to memory object class destructor or GLO_NULL. */

} SAaMemBlockObjClass;
/**
* @}
*/

/**@name AaMem specific pool impl. function pointer definitions
* @{
*/

/** @brief Type definition for UNSAFE pool allocator function
* @param[in] opaque   Pool impl. specific data.
* @param[in] size     Total size of the allocation.
* @param[in] blockId  Id of the memory block to be set.
*
* @return Pointer to allocated memory block or in error GLO_NULL
*/
typedef void* TAaMemAllocator(void* const opaque, const u32 size, u32 const blockId);

/** @brief Type definition for SAFE pool allocator function
* @param[in] opaque   Pool impl. specific data.
* @param[in] size     Total size of the allocation.
* @param[in] blockId  Id of the memory block to be set.
*
* @return Pointer to allocated memory block (never GLO_NULL)
*/
typedef void* TAaMemSafeAllocator(void* const opaque, const u32 size, u32 const blockId);

/** @brief Type definition for pool unallocator function
* @param[in,out]  blockPtrPtr  Pointer to a pointer to a memory block to unallocate.
*                              Should be set to GLO_NULL by the implementation.
*
* @see AaMemPoolOpaqueGet
*/
typedef void TAaMemUnAllocator(void** blockPtrPtr);

/** @brief Type definition for pool info reader function
* @param[in]  opaque   Pool impl. specific data.
* @param[out] infoPtr  Pointer to a info struct which shall be filled.
*
* @return EAaMemRet_Ok in case of success
*/
typedef EAaMemRet TAaMemPoolInfoReader(void* const opaque, SAaMemPoolInfo* infoPtr);

/** @brief Type definition for memory block validity checker function
* @param[in] opaque    Pool impl. specific data.
* @param[in] blockPtr  Pointer to a memory block to be verified.
*
* @return EAaMemRet_Ok in case of success
*/
typedef EAaMemRet TAaMemBlockValidityChecker(void* const opaque, void* blockPtr);

/** @brief Type definition for memory block address to object converter function
* @param[in]  opaque    Pool impl. specific data.
* @param[in]  blockPtr  Pointer to a memory block to be converted.
* @param[out] blockObj  Pointer to a memory block object to be filled.
*
* @return EAaMemRet_Ok in case of success
*/
typedef EAaMemRet TAaMemAddr2ObjConv(void* const opaque, const void* const blockPtr, SAaMemBlockObj* blockObj);

/** @brief Type definition for memory block object to address converter function
* @param[in]  opaque       Pool impl. specific data.
* @param[in]  blockObj     Pointer to a memory block object to be converted.
* @param[out] blockPtrPtr  Pointer to a pointer to a memory block to be filled.
*
* @return EAaMemRet_Ok in case of success
*/
typedef EAaMemRet TAaMemObj2AddrConv(void* const opaque, const SAaMemBlockObj* const blockObj, void** blockPtrPtr);

/** @brief Type definition for pool access lock function
* @param[in]  opaque  Pool impl. specific data.
*/
typedef void TAaMemPoolLock(void* const opaque);

/** @brief Type definition for pool access unlock function
* @param[in]  opaque  Pool impl. specific data.
*/
typedef void TAaMemPoolUnlock(void* const opaque);

/** @brief Type definition for HW header invalidation callback function.
* Invalidates HwQueueMm and AaMem headers if cached.
* @param[in]  aaMemHeaderPtr  Header of memory block in question.
*/
typedef EAaMemRet TAaMemInvHwHeaderCallBack(void const * const aaMemHeaderPtr);

/**
* @}
*/

/** @brief Structure for containing pool implementation related information
           needed by AaMem when attaching new pool into the system.  */
typedef struct SAaMemPoolImpl
{
    TAaMemAllocator*            allocator;        /**< Pointer to a function implementing the pool memory
                                                       unsafe allocation interface function i.e. can return GLO_NULL.
                                                       Can be GLO_NULL if pool implementation does not support unsafe mode. */

    TAaMemSafeAllocator*        safeAllocator;    /**< Pointer to a function implementing the pool memory
                                                       unallocation interface function. Cannot be GLO_NULL. */

    TAaMemUnAllocator*          unallocator;      /**< Pointer to a function implementing the pool memory
                                                       allocation interface function. Cannot be GLO_NULL.
                                                       Should not return GLO_NULL in any circumstances. */

    TAaMemPoolInfoReader*       info;             /**< Pointer to a function implementing the pool
                                                       information reader interface function. Can be GLO_NULL. */

    TAaMemBlockValidityChecker* validityChecker;  /**< Pointer to a function implementing pool implementation specific
                                                       memory blocks validity check. Can be GLO_NULL. If GLO_NULL, no validity
                                                       checks are done for memory blocks allocated from a specific pool
                                                       not implementing this function. */

    TAaMemAddr2ObjConv*         addr2objConverter;/**< Pointer to a function implementing memory block address
                                                       to memory block object converter. Can be GLO_NULL, if pool
                                                       implementation does not support inter-EE communication. */

    TAaMemObj2AddrConv*         obj2addrConverter;/**< Pointer to a function implementing memory block object to memory
                                                       block address converter. Can be GLO_NULL, if pool implementation
                                                       does not support inter-EE communication. */

    TAaMemPoolLock*             locker;           /**< Pointer to a function implementing pool locking mechanism.
                                                       If the pool is not used between EEs/EUs, locking is not
                                                       needed thus pointer can be GLO_NULL */

    TAaMemPoolUnlock*           unlocker;         /**< Pointer to a function implementing pool unlocking mechanism.
                                                       If the pool is not used between EEs/EUs, unlocking is not
                                                       needed thus pointer can be GLO_NULL. */

    void*                       opaque;           /**< Pointer to a pool implementation specific data. Can be GLO_NULL. */

} SAaMemPoolImpl;

/** @brief Structure for containing pool implementation related information  */
typedef struct SAaMemPoolHandler
{
    EAaMemPoolMode               poolMode;         /**< The operation mode of the pool in error situation.
                                                        See chapters Memory pool and Error handling in CC&S SW Memory
                                                        Management Service API specification for more details. */

    EAaMemPoolTraceMode          poolTraceMode;    /**< The trace mode of the pool affects to runtime tracing.
                                                        For more details see chapter Pool trace in CC&S SW Memory
                                                        Management Service API specification */

    SAaMemPoolImpl               impl;             /**< Pool implementation */

} SAaMemPoolHandler;

/** @brief Helper macro for pool implementations for endmark writing */
#define AAMEM_WRITE_MEM_BLOCK_ENDMARK(__ptr) \
    *((u8*)__ptr) = AAMEM_MEM_BLOCK_ENDMARK

/** @brief Helper macro for pool implementations for endmark reading */
#define AAMEM_READ_MEM_BLOCK_ENDMARK(__ptr) \
    *((u8*)__ptr)

/** @brief Helper macro for pool implementations for endmark checking */
#define AAMEM_CHECK_MEM_BLOCK_ENDMARK(__ptr) \
    (AAMEM_MEM_BLOCK_ENDMARK == AAMEM_READ_MEM_BLOCK_ENDMARK(__ptr))

/** @brief Number of bits in pool category ID */
#define AAMEM_POOL_CID_BITS 16

/** @brief Macro for creating pool ID
* @param[in] __cid  Pool category identifier.
* @param[in] __sid  Pool sub identifier
*
* @return 32bit pool ID
*/
#ifndef AA_POOL_ID_CREATE
#define AA_POOL_ID_CREATE AAMEM_POOLID_CREATE
#endif
#define AAMEM_CCS_POOL_CID  0

/** @brief CID of invalid pool ID definition */
#define AAMEM_INVALID_CID 0xFFFF
/** @brief SID of invalid pool ID definition */
#define AAMEM_INVALID_SID 0xFFFF
/** @brief CID definition for dynamic pool IDs */
#define AAMEM_DYNAMIC_ID_CID 0x1
/** @brief Invalid pool ID definition */
#define AAMEM_INVALID_POOL_ID ((AAMEM_INVALID_CID << 16) | AAMEM_INVALID_SID)

/** @brief Returns CID of given pool ID
* @param[in] __poolId  Pool ID where CID is queried.
*
* @return CID of given pool ID
*/
#define AAMEM_GET_POOL_CID(__poolId) ((__poolId) >> 16)

/** @brief Returns SID of given pool ID
* @param[in] __poolId  Pool ID where SID is queried.
*
* @return SID of given pool ID
*/
#define AAMEM_GET_POOL_SID(__poolId) ((__poolId) & 0x0000FFFF)

/** @brief Sets CID to given pool ID
* @param[in] __poolId  Pool ID where CID is being set.
* @param[in] __cId     CID to set.
*
* @return Pool ID with new CID
*/
#define AAMEM_SET_POOL_CID(__poolId, __cId) (((__poolId) & 0x0000FFFF) | ((__cId) << 16))

/** @brief Sets SID to given pool ID
* @param[in] __poolId  Pool ID where SID is being set.
* @param[in] __sId     SID to set.
*
* @return Pool ID with new SID
*/
#define AAMEM_SET_POOL_SID(__poolId, __sId) (((__poolId) & 0xFFFF0000) | ((__sId) & 0x0000FFFF))


/**
*******************************************************************************
*
*   @brief    AaMemAllocSafeIdDbg allocates dynamic memory block from
*             a specific pool from safe pool and sets block id to an user
*             defined value.
*
*   @note <b>For safe pool operation mode only!</b>
*
*   @param[in] poolId  Identifier of a pool where allocation takes place.
*                      Identifier is:
*                         - Id of a system pool or target specific system pool.
*                         - Id of an application specific pool, attached with
*                           AaMemPoolAttach.
*   @param[in] size    Allocation size in bytes.
*   @param[in] blockId User defined id for allocated memory block (use 0 if not
*                      needed).
*   @param[in] filePtr __FILE__ or __FUNCTION__
*   @param[in] line    __LINE__
*
*   @return    Pointer to newly allocated memory block. GLO_NULL if NOK.
*
*   @par Description:
*   This function allocates a dynamic memory block from a specific pool and sets
*   the memory block reference counter to 1. If allocation faile's then GLO_NULL
*   is returned. Additionally the allocated memory block's identifier will be
*   set to passed user value. The address of an allocated memory block is always
*   aligned at least to a word (32 bits) or to a multiple of 32 bits. (Current
*   alignment is reflected by define directive AAMEM_CURRENT_ALIGNMENT.)
*   \n\n
*
*   @par Errors:
*   In case of failure a GLO_NULL is returned. Only If safeAllocator
*   isn't specified then fatal error handler is called.
*   If memory allocation is unsuccessful, following reasons may lead to that:
*      - There is no corresponding pool for defined pool id.
*      - Requested allocation size exceeds pool's current (continuous) free
*        space capacity.
*      - Pool does not support requested allocation size.
*
*   @par Restrictions:
*   Pool implementation:
*      - May limit maximum allocation size.
*      - May restrict the use of the allocated memory.
*      - Must be in safe mode.

*   @par Usage:
*   Use of this function straight is not recommended.
*   Used via AAMEM_ALLOC_SAFE or AAMEM_ALLOC_SAFE_ID -macros is preferred.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AAMEM_ALLOC_SAFE
*   @see AAMEM_ALLOC_SAFE_ID
*
******************************************************************************/
void* AaMemAllocSafeIdDbg( i32 const   poolId,
                           u32 const   size,
                           u32 const   blockId,
                           char const *filePtr,
                           u32 const   line );


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
*   @see AaMemAllocSafeId
*   @see AAMEM_ALLOC_SAFE
*   @see AAMEM_ALLOC_SAFE_ID
*   @see AaMemPoolAttach
*   @see AaMemUnRef
*
******************************************************************************/
void*
AaMemAllocSafe( i32 const poolId,
                u32 const size );


/**
*******************************************************************************
*
*   @brief    AAMEM_ALLOC_SAFE -macro allocates dynamic memory block from
*             a specific pool in safe manner.
*
*   @note <b>For safe pool operation mode only!</b>
*
*   @param[out] memoryPtrPtr Pointer to memory pointer where the address
*                          of the allocated memory block is stored.
*                          Never GLO_NULL is stored.
*
*   @param[in] poolId  Identifier of a pool where allocation takes place.
*                      Identifier is:
*                         - Id of a system pool or target specific system pool.
*                         - Id of an application specific pool, attached with
*                           AaMemPoolAttach.
*   @param[in] size    Allocation size in bytes.
*
*   @par Description:
*   This macro allocates a dynamic memory block from a specific pool and sets
*   the memory block reference counter to 1. If this macro returns it is
*   guaranteed that always a pointer to a valid memory block is returned. If an
*   unrecoverable exception occurs, this macro never returns. In this case it
*   is unspecified in what state the calling EE/EU will be afterwards.
*   \n\n
*   The address of an allocated memory block is always aligned at least to a
*   word (32 bits) or to a multiple of 32 bits. (Current aligment is reflected
*   by define directive AAMEM_CURRENT_ALIGNMENT.)
*   \n\n
*
*   @par Errors:
*   In case of failure a fatal exception is raised and handled by AaMem
*   internally.
*   If memory allocation is unsuccessful, following reasons may lead to that:
*      - There is no corresponding pool for passed pool id.
*      - Requested allocation size exceeds pool's current (continuous) free
*        space capacity.
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
*   u32* memoryPtr;
*
*   AAMEM_ALLOC_SAFE(&memoryPtr, EAaMemSysPoolId_Default, sizeof(u32));
*
*   memoryPtr points now to a valid memory block.
*   Since allocated in safe manner, it can be dereferenced without further
*   checks.
*
*   *memoryPtr = 123;
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
*   @see AAMEM_ALLOC_SAFE_ID
*   @see AaMemPoolAttach
*   @see AaMemUnRef
*
******************************************************************************/
#define AAMEM_ALLOC_SAFE(memoryPtrPtr, \
                         poolId, \
                         size) \
{\
    *memoryPtrPtr = AaMemAllocSafeIdDbg(poolId, \
                                    size, \
                                    0, \
                                    __FUNCTION__, \
                                    __LINE__); \
}\


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
*   @see AAMEM_ALLOC_SAFE
*   @see AAMEM_ALLOC_SAFE_ID
*   @see AaMemPoolAttach
*   @see AaMemUnRef
*
******************************************************************************/
void*
AaMemAllocSafeId(i32 const poolId,
                 u32 const size,
                 u32 const blockId );


/**
*******************************************************************************
*
*   @brief    AAMEM_ALLOC_SAFE_ID -macro allocates dynamic memory block from
*             a specific pool in safe manner.
*
*   @note <b>For safe pool operation mode only!</b>
*
*   @param[out] memoryPtrPtr Pointer to memory pointer where the address
*                          of the allocated memory block is stored.
*                          Never GLO_NULL is stored.
*
*   @param[in] poolId  Identifier of a pool where allocation takes place.
*                      Identifier is:
*                         - Id of a system pool or target specific system pool.
*                         - Id of an application specific pool, attached with
*                           AaMemPoolAttach.
*   @param[in] size    Allocation size in bytes.
*
*   @param[in] blockId User defined id for allocated memory block.
*
*   @par Description:
*   This macro allocates a dynamic memory block from a specific pool and sets
*   the memory block reference counter to 1. If this macro returns it is
*   guaranteed that always a pointer to a valid memory block is returned. If an
*   unrecoverable exception occurs, this macro never returns. In this case it
*   is unspecified in what state the calling EE/EU will be afterwards.
*   \n\n
*   The address of an allocated memory block is always aligned at least to a
*   word (32 bits) or to a multiple of 32 bits. (Current aligment is reflected
*   by define directive AAMEM_CURRENT_ALIGNMENT.)
*   \n\n
*
*   @par Errors:
*   In case of failure a fatal exception is raised and handled by AaMem
*   internally.
*   If memory allocation is unsuccessful, following reasons may lead to that:
*      - There is no corresponding pool for passed pool id.
*      - Requested allocation size exceeds pool's current (continuous) free
*        space capacity.
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
*   u32* memoryPtr;
*
*   AAMEM_ALLOC_SAFE_ID(&memoryPtr, EAaMemSysPoolId_Default, sizeof(u32),
*       0x10102020);
*
*   memoryPtr points now to a valid memory block.
*   Since allocated in safe manner, it can be dereferenced without further
*   checks.
*
*   *memoryPtr = 123;
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
*   @see AAMEM_ALLOC_SAFE
*   @see AaMemPoolAttach
*   @see AaMemUnRef
*
******************************************************************************/
#define AAMEM_ALLOC_SAFE_ID(memoryPtrPtr, \
                            poolId, \
                            size, \
                            blockId ) \
{\
    *memoryPtrPtr = AaMemAllocSafeIdDbg(poolId, \
                                    size, \
                                    blockId, \
                                    __FUNCTION__, \
                                    __LINE__); \
}\

/**
*******************************************************************************
*
*   @brief    Allocates dynamic memory block from specific pool and sets
*             block id UNSAFE manner
*
*   @param[in] poolId  Identifier of a pool where allocation takes place. Identifier is:
*                         - Id of a system pool or target specific system pool.
*                         - Id of an application specific pool, attached with AaMemPoolAttach.
*   @param[in] size    Size of an allocation in bytes.
*   @param[in] blockId User defined id for allocated memory block.
*
*   @return    Pointer to newly allocated memory block or in case of error,
*              GLO_NULL is returned.
*
*   @par Description:
*   This function allocates dynamic memory block from specific pool, sets memory
*   block id to user defined value and sets memory block reference counter to 1.
*   In failure, GLO_NULL value will be returned and it is caller's responsibility
*   to check return value.
*   \n\n
*   Address of an allocated memory block is always aligned atleast to 32 bits
*   (word) or multiple of 32 bits. Currently used aligment is set to AAMEM_CURRENT_ALIGNMENT.
*   \n\n
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
*   ptr = (u32*)AaMemAllocId(EAaMemSysPoolId_Private, sizeof(u32), 0x00001034);
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
*   @see AaMemMalloc
*   @see AaMemPoolAttach
*   @see AaMemUnRef
*
******************************************************************************/
void*
AaMemAllocId( i32 const poolId,
              u32 const size,
              u32 const blockId );

/**
*******************************************************************************
*
*   @brief    Increases refrerence counter of allocated memory block
*
*
*   @param[in] ptr  Pointer to allocated memory block.
*
*   @return    Pointer to the given memory block.
*
*   @par Description:
*   Allocation set number of references to one. With AaMemRef function,
*   caller can add reference to same memory block. Pointer to memory block,
*   the reference is added, is returned. Maximum reference count is specified by
*   AAMEM_MAX_REF_COUNT.
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
*   u32* somePointer2;
*
*   somePointer = (u32*)AaMemAlloc(EAaMemSysPoolId_Private, sizeof(u32));
*   somePointer2 = (u32*)AaMemRef(somePointer);
*
*   if (somePointer == somePointer2) {
*      // Pointers should point to same address
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
void*
AaMemRef( void* const ptr );

/*
**
*******************************************************************************
*
*   @brief    Attaches a memory pool implementation to AaMem
*
*   @param[in,out] poolId    Pointer to a pool id storage where new pool id is
*                            stored. If AaMem should allocate the ID, this must
*                            be set to AAMEM_INVALID_POOL_ID.
*   @param[in]     poolName  Pointer to a pool name string or GLO_NULL.
*   @param[in]     poolHndlr Pointer to pool handler struct filled by the caller.
*
*   @return EAaMemRet_Ok
*   @return EAaMemRet_NullParameter
*   @return EAaMemRet_PoolNameConflict
*
*   @par Description:
*   This function attach a memory pool implementation to AaMem service
*   and returns the ID of the newly attached pool. The pool implementation is attached
*   as application specific pool, thus it is available only in the context of
*   the EE, where attachment takes place.
*   \n\n
*   Argument poolId must be set to AAMEM_INVALID_POOL_ID or to some requested
*   value depending if the pool ID should be allocated by AaMem or it is defined
*   by the user:
*      - If AAMEM_INVALID_POOL_ID is used, AaMem tries to dynamically allocate
*        the pool ID.
*      - If AAMEM_INVALID_POOL_ID and name is used, AaMem tries first to find
*        existing attachment for the name and use its pool ID. If existing is
*        not found, new dynamic pool ID is reserved.
*      - If valid pool ID is given and name is used, AaMem tries to attach
*        the pool using the ID and the name. If existing pool with same name
*        and ID exist, content of the poolHndlr is replaced by the existing one.
*   \n\n
*   poolHndlr contains information about pool implementation including function
*   pointer to various pool operations. Not all operations must be implemented and
*   those operations not implemented must be set to GLO_NULL.
*   \n\n
*   If valid pool ID is given and name is used, AaMem tries to attach the pool
*   using the ID and the name. If existing pool with same name and ID exist,
*   content of the poolHndlr is replaced by the existing one.
*
*   @par Errors:
*   Following error conditions may occur:
*      - If valid pool ID and name is given but the name conflicts with already attached
*        pool with different pool ID, EAaMemRet_PoolNameConflict is returned and exception
*        EAaErrorCcs_AaMem_PoolAttachFailed is raised.
*
*   @par Restrictions:
*   In some systems pool name cannot be used to bind
*
*   @par Example:
*
*   @code
*
*   i32 poolId = AAMEM_INVALID_POOL_ID; // System allocates pool id
*   SAaMemPoolHandler poolHndlr;
*   EAaMemRet rc;
*   u32* somePointer;

*   // Fill poolHndlr fields
*   // poolHndlr.poolMode             =
*   // poolHndlr.allocator            =
*   // poolHndlr.impl.unallocator     =
*   // poolHndlr.impl.unSafeAllocator =
*   // poolHndlr.impl.info            =
*   // poolHndlr.impl.validityChecker =
*   // poolHndlr.impl.opaque          =
*   // ...
*
*   // Attach new pool
*   rc = AaMemPoolAttach(&poolId, "app.myapp.mypool", &poolHndlr);
*
*   // Memory allocation is using newly created pool
*   somePointer = (u32*)AaMemAlloc(poolId, sizeof(u32));
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
*   @see AaMemDetachPool
*
******************************************************************************/
EAaMemRet
AaMemPoolAttach( i32* poolId,
                 const char* poolName,
                 const SAaMemPoolHandler* poolHndlr );

/**
*******************************************************************************
*
*   @brief   Detach previously attached memory pool from AaMem
*
*
*   @param[in] poolId    Pointer to a pool id storage where new pool id is stored.
*
*   @return EAaMemRet_Ok
*   @return EAaMemRet_PoolNotFound
*
*   @par Description:
*   This function detach a memory pool implementation from AaMem service which
*   has beed attached earlier by AaMemPoolAttach. After detaching, it is illegal
*   to allocate memory using given pool id. If there are several attachments for
*   the same id (attached using static ID or name), the pool is detached from the
*   system when last attachment becomes detached i.e. pool must be detached as
*   many time it has been attached.
*
*   @par Errors:
*      - If there is no attached pool for given poolId, EAaMemRet_PoolNotFound
*        is returned.
*      - If system pool is tried to detach exception XYZ is raised and code
*        EAaMemRet_PoolNotFound is returned.
*
*   @par Restrictions:
*   It is not possible to detach system pools (BDM, SDM and MDM).
*
*   @par Example:
*
*   @code
*
*   i32 poolId = AAMEM_INVALID_POOL_ID; // System allocates pool id
*   SAaMemPoolHandler poolHndlr;
*   EAaMemRet rc;
*
*   // Fill poolHndlr fields
*   // poolHndlr.poolMode             =
*   // poolHndlr.allocator            =
*   // poolHndlr.impl.unallocator     =
*   // poolHndlr.impl.unSafeAllocator =
*   // poolHndlr.impl.info            =
*   // poolHndlr.impl.validityChecker =
*   // poolHndlr.impl.opaque          =
*   // ...
*
*   // Attach new pool
*   rc = AaMemPoolAttach(&poolId, "app.myapp.mypool", &poolHndlr);
*
*   // Detach the pool
*   rc = AaMemPoolDetach(poolId);
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
*   @see AaMemAttachPool
*
******************************************************************************/
EAaMemRet
AaMemPoolDetach( i32 const poolId );

/**
*******************************************************************************
*
*   @brief    Queries information about an attached pool
*
*
*   @param[in]  poolId   Id of the pool to query.
*   @param[out] poolInfo Pointer to a structure where pool info is stored.
*
*   @return EAaMemRet_Ok
*   @return EAaMemRet_PoolNotFound
*   @return EAaMemRet_NullParameter
*
*   @par Description:
*   This function queries pool information from attached pool.
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
*   i32 poolId = AAMEM_INVALID_POOL_ID; // System allocates pool id
*   SAaMemPoolHandler poolHndlr;
*   SAaMemPoolInfo poolInfo;
*   EAaMemRet rc;
*
*   // Fill poolHndlr fields
*   // poolHndlr.poolMode             =
*   // poolHndlr.allocator            =
*   // poolHndlr.impl.unallocator     =
*   // poolHndlr.impl.unSafeAllocator =
*   // poolHndlr.impl.info            =
*   // poolHndlr.impl.validityChecker =
*   // poolHndlr.impl.opaque          =
*   // ...
*
*   // Attach new pool
*   rc = AaMemPoolAttach(&poolId, "app.myapp.mypool", &poolHndlr);
*
*   // Get pool info
*   rc = AaMemPoolInfoGet(poolId, &poolInfo);
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
*   @see AaMemAttachPool
*
******************************************************************************/
EAaMemRet
AaMemPoolInfoGet(i32 const poolId, SAaMemPoolInfo * poolInfo);

/**
*******************************************************************************
*
*   @brief    Converts given memory block address to memory object.
*
*
*   @param[in]  ptr       Pointer to an allocated memory block address valid in current EE.
*   @param[out] blockObj  Pointer to a structure where block object is stored.
*
*   @return EAaMemRet_Ok
*   @return EAaMemRet_InvalidParameter
*   @return EAaMemRet_NullParameter
*
*   @par Description:
*   This function is for converting memory block address, valid in the current EE context,
*   to a form, which can be transferred between EEs. This is mainly needed in inter-EE
*   communication.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   Inter-CE communication is not supported instead only inter-EE communication
*   in the context of same CE.
*
*   @par Example:
*
*   @code
*
*   SAaMemBlockObj blockObj;
*   void* ptr;
*   EAaMemRet rc;
*
*   ptr = AaMemAlloc(AaMemSysPoolId_Msg, 64);
*
*   rc = AaMemBlockAddr2Obj(ptr, &blockObj);
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
*   @see AaMemBlockObj2Addr
*
******************************************************************************/
EAaMemRet
AaMemBlockAddr2Obj(const void* const ptr, SAaMemBlockObj* blockObj);

/**
*******************************************************************************
*
*   @brief    Converts given memory object to memory block address.
*
*
*   @param[in]  blockObj  Pointer to structure where block object is stored.
*   @param[out] ptr       Pointer to a pointer to an allocated memory block valid in current EE.
*
*   @return EAaMemRet_Ok
*   @return EAaMemRet_InvalidParameter
*   @return EAaMemRet_NullParameter
*
*   @par Description:
*   This function restores converted memory block address to an address, valid in
*   the context of current EE.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   Inter-CE communication is not supported instead only inter-EE communication
*   in the context of same CE.
*
*   @par Example:
*
*   @code
*
*  SAaMemBlockObj blockObj;
*  void* ptr;
*  void* ptr2;
*  EAaMemRet rc;
*
*  ptr = AaMemAlloc(EAaMemSysPoolId_Shared, 64);
*
*  // Convert block pointer to block object
*  rc = AaMemBlockAddr2Obj(ptr, &blockObj);
*
*  // Now instead of pointer, block object should be passed to another EE/EU via e.g. SIC message.
*
*  // ...
*
*  // Convert block object to block pointer in the receiving side
*  rc = AaMemBlockObj2Addr(&blockObj, &ptr2);
*
*  // Both pointers should now point to same memory block
*  if (ptr == ptr2) {
*      // OK
*  }
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
*   @see AaMemBlockAddr2Obj
*
******************************************************************************/
EAaMemRet
AaMemBlockObj2Addr(const SAaMemBlockObj* const blockObj, void** ptr);

/**
*******************************************************************************
*
*   @brief    Sets object class to memory block.
*
*
*   @param[in] ptr       Pointer to a memory block where object class is set.
*   @param[in] objClass  Pointer to an object class which shall be set.
*
*   @return none
*
*   @par Description:
*   This function sets memory block object class to allocated valid memory block.
*   Memory block object class contains pointer to destructor function, which is
*   called before last reference to the memory block is removed and the block
*   will be unallocated.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @see AaMemObjectClassGet
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
*   @see AaMemObjectClassGet
*
******************************************************************************/
void
AaMemObjectClassSet( void const * const ptr,
                     SAaMemBlockObjClass const * const objClass );

/**
*******************************************************************************
*
*   @brief Returns object class to memory block.
*
*
*   @param[in] ptr  Pointer to an allocated memory block where objct class is get.
*
*   @return Pointer to memory block object class or GLO_NULL.
*
*   @par Description:
*   This function returns previously set memory block object class, if any.
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
*   void* ptr = AaMemMalloc(100);
*   SAaMemBlockObjClass* objClass2;
*   SAaMemBlockObjClass* objClass = AaMemMalloc(sizeof(SAaMemBlockObjClass));
*   objClass->destructor = myOwnDestructor;
*
*   AaMemObjectClassSet(ptr, objClass);
*
*   objClass2 = AaMemObjectClassGet(ptr);
*
*   // Both pointers should now point to same memory block class object
*   if (objClass == objClass2) {
*      // OK
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
*   @see AaMemObjectClassSet
*
******************************************************************************/
SAaMemBlockObjClass*
AaMemObjectClassGet( void const *ptr );

/*----------------------- INTERNAL INTERFACES --------------------------------*/

/**@name AaMem internal API
* @{
*/

/**
*******************************************************************************
*
*   @brief    Return a pointer to a memory block base address.
*
*
*   @param[in] ptr  Pointer to allocated memory block.
*
*   @return Pointer to the memory block base address.
*
*   @par Description:
*   None
*
*   @par Errors:
*   If given paramter is invalid, GLO_NULL is returned and exception
*   EAaErrorCcs_AaMem_InvalidParameter is raised.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   void* somePointer;
*   void* blockBase;
*   u32* blockId;
*
*   // Allocate memory block and set block ID to 0xABBA
*   somePointer = AaMemAllocId(EAaMemSysPoolId_Private, 300, 0xABBA);
*
*   blockBase = AaMemBlockBaseGet(somePointer);
*
*   blockId = (u32*)blockBase;
*
*   if (*blockId == 0xABBA)
*   {
*       // blockId must be same as block ID given during alloc
*   }
*
*   @endcode
*
*   @par Usage:
*   This function can be used to access to block id (in the reserved field of memory block).
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaMemBlockPayloadGet
*
******************************************************************************/
void*
AaMemBlockBaseGet( const void *ptr );

/**
*******************************************************************************
*
*   @brief    Return a pointer to a start of user data in a memory block.
*
*
*   @param[in] ptr  Pointer to a allocate memory block base.
*
*   @return Pointer to the user data of memory block or GLO_NULL.
*
*   @par Description:
*   None
*
*   @par Errors:
*   If given paramter is invalid, GLO_NULL is returned and exception
*   EAaErrorCcs_AaMem_InvalidParameter is raised.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   void* somePointer;
*   void* blockBase;
*   void* userData;
*
*   somePointer = AaMemAlloc(EAaMemSysPoolId_Private, 300);
*   blockBase = AaMemBlockBaseGet(somePointer);
*
*   userData = AaMemBlockPayloadGet(blockBase);
*
*   if (somePointer == userData)
*       // AaMemAlloc returns same pointer than
*       // AaMemBlockPayloadGet returns
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
*   @see AaMemBlockBaseGet
*
******************************************************************************/
void*
AaMemBlockPayloadGet( const void *ptr );

/**
*******************************************************************************
*
*   @brief    Initializes AaMem service at EE level.
*
*
*   @return EAaMemRet_Ok
*
*   @par Description:
*   This function initializes AaMem service per EE basis. Therefore this function
*   must be called in every EE wishes to use AaMem services.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
*   @see
*
******************************************************************************/
EAaMemRet
AaMemEeInit(void);
/** @} */

/*----------------------- DEBUG INTERFACES ---------------------------------*/

/**@name AaMem debug API
* @{
* These API calls are debug versions of main API IF. They work as original
* API calls except they accept filename and line number as arguments.
*/
#ifdef AAMEM_DEBUG_API_ENABLE

/** @see AaMemSizeGet */
u32 AaMemSizeGetDbg(void const * const ptr, const char *file, const u32 line);

/** @see AaMemAllocSafe */
void* AaMemAllocSafeDbg(i32 const poolId, u32 const size,
                        const char *file, const u32 line);

/** @see AaMemAllocSafeId */
/*
* THIS IS MOVED TO THE BEGINNING OF THIS HEADER FILE
* AND THIS IS NOT BEHIND THIS AAMEM_DEBUG_API_ENABLE!
* void *AaMemAllocSafeIdDbg(i32 const poolId, u32 const size, u32 const blockId,
*                          const char *file, const u32 line);
*/

/** @see AaMemAlloc */
void* AaMemAllocDbg(i32 const poolId, u32 const size,
                    const char *file, const u32 line);

/** @see AaMemAllocId */
void* AaMemAllocIdDbg(i32 const poolId, u32 const size, u32 const blockId,
                      const char *file, const u32 line);

/** @see AaMemMalloc */
void* AaMemMallocDbg(u32 const size,
                     const char *file, const u32 line);

/** @see AaMemRef */
void* AaMemRefDbg(void * const ptr, const char *file, const u32 line);

/** @see AaMemUnRef */
void AaMemUnRefDbg(void const ** const ptr, const char *file, const u32 line);

/** @see AaMemObjectClassSet */
void AaMemObjectClassSetDbg(void const * const ptr, SAaMemBlockObjClass const * const objectClass,
                            const char *file, const u32 line);

/** @see AaMemGetObjectClass */
SAaMemBlockObjClass* AaMemGetObjectClassDbg(void const *ptr, const char *file, const u32 line);

/** @see AaMemPoolAttach */
EAaMemRet AaMemPoolAttachDbg(i32* poolId, const char* poolName, const SAaMemPoolHandler* poolHndlr,
                             const char *file, const u32 line);

/** @see AaMemPoolDetach */
EAaMemRet AaMemPoolDetachDbg(i32 const poolId, const char *file, const u32 line);

/** @see AaMemPoolInfoGet */
EAaMemRet AaMemPoolInfoGetDbg(i32 const poolId, SAaMemPoolInfo * poolInfo,
                              const char *file, const u32 line);

#ifdef AAMEM_LEGACY_API_ENABLE

/** @see AaMemSend */
void AaMemSendDbg(void const ** const sigbuf, const TEuId destpid,
                  const char *file, const u32 line);

/** @see AaMemSender */
TEuId AaMemSenderDbg(void const * const sigbuf, const char *file, const u32 line);

/** @see AaMemReceive */
void* AaMemReceiveDbg(TAaMemMsgSelect const * const sigselect,
                      const char *file, const u32 line);

/** @see AaMemReceiveWithTimeOut */
void* AaMemReceiveWithTimeOutDbg(TAaMemMsgSelect const * const sigselect, TAaSysTime const timeout,
                                 const char *file, const u32 line);

#endif /* AAMEM_LEGACY_API_ENABLE */

#define AaMemSizeGet(ptr) AaMemSizeGetDbg((ptr),__FILE__, __LINE__)

#define AaMemAllocSafe(poolId,size) AaMemAllocSafeDbg((poolId),(size),__FILE__, __LINE__)

#define AaMemAllocSafeId(poolId,size,id) AaMemAllocSafeIdDbg((poolId),(size),(id),__FILE__, __LINE__)

#define AaMemAlloc(poolId,size) AaMemAllocDbg((poolId),(size),__FILE__, __LINE__)

#define AaMemAllocId(poolId,size,id) AaMemAllocIdDbg((poolId),(size),(id),__FILE__, __LINE__)

#define AaMemMalloc(size) AaMemMallocDbg((size),__FILE__, __LINE__)

#define AaMemRef(ptr) AaMemRefDbg((ptr),__FILE__, __LINE__)

#define AaMemUnRef(ptr) AaMemUnRefDbg((ptr),__FILE__, __LINE__)

#define AaMemObjectClassSet(ptr,classPtr) AaMemObjectClassSetDbg((ptr),(classPtr),__FILE__, __LINE__)

#define AaMemGetObjectClass(ptr) AaMemGetObjectClassDbg((ptr),__FILE__, __LINE__)

#define AaMemPoolAttach(poolId, poolName, poolHndlr) AaMemPoolAttachDbg(poolId, poolName, poolHndlr, __FILE__, __LINE__)

#define AaMemPoolDetach(poolId) AaMemPoolDetachDbg(poolId, __FILE__, __LINE__)

#ifdef AAMEM_LEGACY_API_ENABLE

#define AaMemSend(sigbuf,destpid) AaMemSendDbg((sigbuf),(destpid),__FILE__, __LINE__)

#define AaMemSender(sigbuf) AaMemSenderDbg((sigbuf),__FILE__, __LINE__)

#define AaMemReceive(sigselect) AaMemReceiveDbg((sigselect),__FILE__, __LINE__)

#define AaMemReceiveWithTimeOut(sigselect,timeout) AaMemReceiveWithTimeOutDbg((sigselect),(timeout),__FILE__, __LINE__)

#endif /* AAMEM_LEGACY_API_ENABLE */

#endif /* AAMEM_DEBUG_API_ENABLE */
/** @} */

#ifdef __cplusplus
}
#endif

/** @} */   /* dgUpCcsRtDspAaMem */
/** @} */   /* dgUpCcsAaMem */
/** @} */   /* dgUpCcs */

#endif /* _RT_DSP_IFAAMEM_H_ */
