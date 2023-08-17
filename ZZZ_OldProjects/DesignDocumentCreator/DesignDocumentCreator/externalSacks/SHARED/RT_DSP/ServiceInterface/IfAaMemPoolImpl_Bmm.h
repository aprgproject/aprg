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

#ifndef _RT_DSP_IFAAMEMPOOLIMPL_BMM_H_
#define _RT_DSP_IFAAMEMPOOLIMPL_BMM_H_

#include <CcsCommon.h>
#include <IfAaMem.h>
#include <IfAaError.h>

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

/*----------------------- PUBLIC STRUCTURES ----------------------------------*/

#define BMM_MAX_NUMBER_OF_SAVED_ALLOC_SIZES ((u32) 64)
#define BMM_MAX_NUMBER_OF_SIZE_RANGES 22

/** @name Structures for pool information and statistics
* @{
*/
typedef struct SBmmAllocSizeInfo     SBmmAllocSizeInfo;
typedef struct SBmmAllocSizes        SBmmAllocSizes;
typedef struct SBmmPoolStatusInfo    SBmmPoolStatusInfo;
typedef struct SBmmPoolInformation   SBmmPoolInformation;

struct SBmmAllocSizeInfo
{
    u32 size;
    u16 currentAllocs;
    u16 maxAllocs;
};

struct SBmmAllocSizes
{
    u32  items;
    SBmmAllocSizeInfo  info[BMM_MAX_NUMBER_OF_SAVED_ALLOC_SIZES];
};

struct SBmmPoolStatusInfo
{
    void          * address;
    u32           size;
    u32           maxUsed;
    u32           unUsed;
    u32           released;
    u32           maxAllocSize;
};

struct SBmmPoolInformation
{
    SBmmPoolStatusInfo statusInfo;
    u32                blockSizes[BMM_MAX_NUMBER_OF_SIZE_RANGES];
    SBmmAllocSizes     sizeInfo;
};
/**
* @}
*/

/**
*******************************************************************************
*
*   @brief Initialisation function of BMM Pool implementation.
*
*   @param[in,out]  poolPtrPtr    Address of user memory block as input.<BR>
*                                 Address of pool memory pointer as output.<BR>
*                                 <B>Note:</B><BR>
*                                 Pool memory pointer will be aligned to an 8-byte border!
*                                 (Keep original input pointer, if you need it later for releasing
*                                 the user memory block.)
*   @param[in]      totalSize     Size of the user memory block for usage of pool implementation.
*   @param[in]      maxBlockSize  Maximum allocation size for a single memoru block.
*
*   @return GLO_TRUE if successful, GLO_FALSE otherwise
*
*   @par Description:
*   Given user memory block is used as pool memory for a BMM Pool.
*   It is initialized according to related allocator layout structure.
*   (Memory mainly is split to BMM header and master blocks.)
*   The pointer to the user memory block is aligned to an 8-byte border.
*   By this the pool memory pointer might be different to passed user memory pointer.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   Maximum allocation size has to be bigger than 512 bytes.
*
*   @par Example:
*   None
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
TBoolean AaMemPoolInit_Bmm(void** poolPtrPtr, u32 totalSize, u32 maxBlockSize);

/**
*******************************************************************************
*
*   @brief Space addition function for BMM Pool implementation.
*
*   @param[in]  poolPtr      Pool memory pointer.
*   @param[in]  newSpacePtr  Pointer to memory space which is added to pool.
*   @param[in]  incSize      Size of memory space, which is added to pool.
*
*   @return GLO_TRUE if successful, GLO_FALSE otherwise
*
*   @par Description:
*   Adds memory to initialized BMM pool memory, to have more master blocks available.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
TBoolean AaMemAddMasterBlocks_Bmm(const void*    poolPtr,
                                  void*          newSpacePtr,
                                  u32            incSize);

/**
*******************************************************************************
*
*   @brief Unsafe allocator of BMM Pool implementation.
*
*   @param[in]  poolPtr  Pool memory pointer.
*   @param[in]  size     Requested allocation size in bytes.
*   @param[in]  blockId  User specific identifier.
*
*   @return pointer to allocated memory or GLO_NULL, if allocation fails.
*
*   @par Description:
*   Allocates memory in given BMM Pool in unsafe manner.
*   If no memory can be allocated, then a null pointer is returned, which
*   has to be checked by the user.<BR>
*   The user specific identifier might be used for identifying the block
*   with a certain pattern within memory dumps. (The pattern is stored
*   where the user space begins.)
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
void* AaMemAllocator_Bmm(void* const poolPtr, const u32 size, const u32 blockId);


/**
*******************************************************************************
*
*   @brief Safe allocator of BMM Pool implementation.
*
*   @param[in]  poolPtr  Pool memory pointer.
*   @param[in]  size     Requested allocation size in bytes.
*   @param[in]  blockId  User specific identifier.
*
*   @return pointer to allocated memory.
*
*   @par Description:
*   Allocates memory in given BMM Pool in safe manner.
*   If no memory can be allocated then a fatal error is raised.
*   By this the user doesn't need to implement a null pointer check.<BR>
*   The user specific identifier might be used for identifying the block
*   with a certain pattern within memory dumps. (The pattern is stored
*   where the user space begins.)
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
void* AaMemSafeAllocator_Bmm(void* const poolPtr, const u32 size, const u32 blockId);


/**
*******************************************************************************
*
*   @brief Unallocator of BMM Pool implementation.
*
*   @param[in,out] blockPtrPtr  Address of user memory block pointer to be freed.
*
*   @return None
*
*   @par Description:
*   Checks the endmark of the block and frees it.
*   The memory block pointer is set to GLO_NULL afterwards.
*
*   @par Errors:
*   A fatal error is raised in case of a corrupted endmark.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
void AaMemUnAllocator_Bmm(void** blockPtrPtr);


/**
*******************************************************************************
*
*   @brief Validity checker of BMM Pool implementation.
*
*   @param[in]  poolPtr   Pool memory pointer.
*   @param[in]  blockPtr  Pointer to memory block to be checked.
*
*   @return
*       - EAaMemRet_Ok: check was successful
*       - EAaMemRet_NullParameter: pointer to memory block is NULL
*       - EAaMemRet_UnexistentPoolId: pointer to memory block and pool memory pointer don't match
*       - EAaMemRet_InvalidEndmark: endmark is corrupted
*
*   @par Description:
*   Checks validity of the memory block.
*   The criterias are: block has a plausible header and its endmark is not corrupt.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
EAaMemRet AaMemValidityChecker_Bmm(void* const poolPtr, void* blockPtr);


/**
*******************************************************************************
*
*   @brief Pool info reader of BMM Pool implementation.
*
*   @param[in]  poolPtr  Pool memory pointer.
*   @param[out] infoPtr  Pointer to info buffer to be filled.
*
*   @return
*       - EAaMemRet_Ok: success
*       - EAaMemRet_NullParameter: user passed NULL pointer to poolPtr or infoPtr
*
*   @par Description:
*   Sets info structure with current values of given BMM Pool.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
EAaMemRet AaMemPoolInfoReader_Bmm(void* const poolPtr, SAaMemPoolInfo* infoPtr);


/**
*******************************************************************************
*
*   @brief Internal Pool info reader of Offset BMM Pool implementaton.
*
*   @param[in]  poolPtr  Pool memory pointer.
*   @param[out] infoPtr  Pointer to info buffer to be filled.
*
*   @return
*       - EAaMemRet_Ok: success
*       - EAaMemRet_NullParameter: user passed NULL pointer to poolPtr or infoPtr
*
*   @par Description:
*   Sets info structure with current values of given BMM Pool.
*   (Information is foreseen AaMem internal investigation.)
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
EAaMemRet AaMemIntPoolInfoReader_Bmm(void* const poolPtr,
                                     SBmmPoolInformation * infoPtr);


/**
*******************************************************************************
*
*   @brief Internal pool status reader of BMM Pool implementation.
*
*   @param[in]  poolPtr    Pool memory pointer.
*   @param[out] statusPtr  Pointer to status buffer to be filled.
*   @param[in]  maxReset   If GLO_TRUE, then peak level of used master blocks (maxUsedMBs)
*                          in pool header is set to current amount of used master blocks (usedMBs).
*
*   @return
*       - EAaMemRet_Ok: success
*       - EAaMemRet_NullParameter: user passed NULL pointer to PoolPtr or statusPtr
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
EAaMemRet AaMemIntPoolStatusReader_Bmm(void * const poolPtr,
                                       SBmmPoolStatusInfo * statusPtr,
                                       const TBoolean maxReset);


/**
*******************************************************************************
*
*   @brief Error handler installer of BMM Pool implementation.
*
*   @param[in] errorHandler  Pointer to error handler function.
*
*   @return None
*
*   @par Description:
*   Installs the error handler function, which has to be of type TAaErrorHandler.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
void AaMemSetErrorHandler_Bmm(TAaErrorHandler * const errorHandler);


#ifdef __cplusplus
}
#endif

/** @} */   /* dgUpCcsRtDspAaMem */
/** @} */   /* dgUpCcsAaMem */
/** @} */   /* dgUpCcs */

#endif /*_RT_DSP_IFAAMEMPOOLIMPL_BMM_H_*/
