/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/ 
#ifndef _MCU_RT_IFAAGPUCOMPRESSIONS_H
#define _MCU_RT_IFAAGPUCOMPRESSIONS_H

/*----------------------- INCLUDED FILES --------------------------------------*/

#include "CcsCommon.h"
#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
*@addtogroup dgCompressions 
*
* Common Computer and Support SW Compressions Service.
* 
* See Compressions Service Wiki for more container types: http://nwiki.nokia.com/CSSWiki/Compressions
*
* @par Terms:
*
* - <b>Chunk size:</b> Size of a temporary dynamically allocated buffer used for data storing during 
*   compression and decompression. Size of the chunk affects memory foot-print of (de)compression.
* - <b>Trimming:</b> Destination buffers are allocated wheter the size of worst case or multiple of
*   chunk size thus causing buffers to be usually oversized when compared to size of the data stored
*   to them. Trimming decreases the buffer sizes to match exactly to the size of the data but at the
*   same time decreasing performance. It is also a remotely possible to cause dynamic memory
*   fragmentation if trimming is enabled. This is of course up to allocator implementation
*   if fragmentation is significant.
* - <b>Allocator and unallocator:</b> User can provide own allocator, unallocator and memory block
*   size get implementations if feasible. However Compressions provides by default implementations 
*   which use AaMem. See #AaGpuCompressionsAllocator, #AaGpuCompressionsUnallocator and
*   #AaGpuCompressionsSizeGet. Size get implementation should return 0, if NULL pointer is given.
*
*/

/**
*@defgroup dgCompressionsFlags Compressions Compiling Flags and defines
*@ingroup dgCompressions
*
* Common Computer and Support SW zlib Compressions (AaGpuZlib) Service compiling flags and defines.
*
* Defines:
* - <code>TBD</code>
* 
* Compiling flags:
* - <code>AAGPUZLIB_CHUNK_SIZE</code> Chunk size for (de)compression. Affects dynamic 
*   memory allocation foot-print. Default is 0xFFF.
* - <code>AAGPUZLIB_TRIM_DST</code> Resize automatically allocated destination buffers 
*   in order to conserve some memory with the expence of performance.
* - <code>AACOMPRESSIONS_DEFAULT_POOL_ID</code> AaMem pool ID for default allocator 
*   implementation.
*
*/

/**
*@defgroup dgCompressionsApiMcu MCU API
*@ingroup  dgCompressions
*
* @{
*/


    
/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** @brief AaGpuCompressions stream handler internal states */
typedef enum EAaGpuCompressionsHndlrState
{
    EAaGpuCompressionsHndlrState_None = 0,
    EAaGpuCompressionsHndlrState_Init,
    EAaGpuCompressionsHndlrState_InUse,
    EAaGpuCompressionsHndlrState_Uninit,

    EAaGpuCompressionsHndlrState_NbrOf

} EAaGpuCompressionsHndlrState;

/** @brief AaGpuCompressions stream handler states in convenience textual representation */
#define EAAGPUCOMPRESSIONSHNDLRSTATE_VALUES \
   { \
       "EAaGpuCompressionsHndlrState_None", \
       "EAaGpuCompressionsHndlrState_Init", \
       "EAaGpuCompressionsHndlrState_InUse", \
       "EAaGpuCompressionsHndlrState_Uninit", \
       "EAaGpuCompressionsHndlrState_NbrOf", \
   }

/** @brief AaGpuCompressions trimming states */
typedef enum EAaGpuCompressionsTrimming
{
    EAaGpuCompressionsTrimming_Disabled = 0,
    EAaGpuCompressionsTrimming_Enabled,

    EAaGpuCompressionsTrimming_NbrOf

} EAaGpuCompressionsTrimming;

/** @brief AaGpuCompressions trimming states in convenience textual representation */
#define EAAGPUCOMPRESSIONSTRIMMING_VALUES \
   { \
       "EAaGpuCompressionsTrimming_Disabled", \
       "EAaGpuCompressionsTrimming_Enabled", \
       "EAaGpuCompressionsTrimming_NbrOf", \
   }


/** @brief AaGpuCompressions public return codes */
typedef enum EAaGpuCompressionsRet
{
    EAaGpuCompressionsRet_Ok = 0,                   /**< No errors occurred */
    EAaGpuCompressionsRet_InternalError,            /**< Unknown error occurred in algorithm implementation */
    EAaGpuCompressionsRet_InvalidParameter,         /**< Invalid parameter defined */
    EAaGpuCompressionsRet_InvalidOperationMode,     /**< Invalid operation mode */
    EAaGpuCompressionsRet_MemoryError,              /**< Failure occurred while doing dynamic memory operations */
    EAaGpuCompressionsRet_VersionIncompatibility,   /**< Version incompatibility detected */
    
    EAaGpuCompressionsRet_NbrOf                     /**< Keep always last and do not remove */
    
} EAaGpuCompressionsRet;

/** @brief AaGpuCompressions return codes in convenience textual representation */
#define EAAGPUCOMPRESSIONSRET_VALUES \
   { \
       "EAaGpuCompressionsRet_Ok", \
       "EAaGpuCompressionsRet_InternalError", \
       "EAaGpuCompressionsRet_InvalidParameter", \
       "EAaGpuCompressionsRet_InvalidOperationMode", \
       "EAaGpuCompressionsRet_MemoryError", \
       "EAaGpuCompressionsRet_VersionIncompatibility", \
       "EAaGpuCompressionsRet_NbrOf" \
   }

/** @brief AaGpuCompressions operating mode */
typedef enum EAaGpuCompressionsOpMode
{
    EAaGpuCompressionsOpMode_Unselected = 0,    /**< Operation mode not yet selected */
    EAaGpuCompressionsOpMode_Compression,       /**< Compression mode */
    EAaGpuCompressionsOpMode_Decompression,     /**< Decompression mode */
    
    EAaGpuCompressionsOpMode_NbrOf              /**< Keep always last and do not remove */
    
} EAaGpuCompressionsOpMode;

/** @brief AaGpuCompressions operation modes in convenience textual representation */
#define EAAGPUCOMPRESSIONSOPMODE_VALUES \
   { \
       "EAaGpuCompressionsOpMode_Unselected", \
       "EAaGpuCompressionsOpMode_Compression", \
       "EAaGpuCompressionsOpMode_Decompression", \
       "EAaGpuCompressionsOpMode_NbrOf" \
   }

/** @brief AaGpuCompressions compression rate */
typedef enum EAaGpuCompressionsCompressRate
{
    EAaGpuCompressionsCompressRate_NoCompress = 0,  /**< No compression (ultra fast) */
    EAaGpuCompressionsCompressRate_Default,         /**< Default rate (compromise between speed and rate) */
    EAaGpuCompressionsCompressRate_Best,            /**< Best compression rate (slowest) */
    EAaGpuCompressionsCompressRate_Worst,           /**< Worst compression rate (fastest) */
    
    EAaGpuCompressionsCompressRate_NbrOf            /**< Keep always last and do not remove */
    
} EAaGpuCompressionsCompressRate;

/** @brief AaGpuCompressions compression rates in convenience textual representation */
#define EAAGPUCOMPRESSIONSCOMPRESSRATE_VALUES \
   { \
       "EAaGpuCompressionsCompressRate_NoCompress", \
       "EAaGpuCompressionsCompressRate_Default", \
       "EAaGpuCompressionsCompressRate_Best", \
       "EAaGpuCompressionsCompressRate_Worst", \
       "EAaGpuCompressionsCompressRate_NbrOf" \
   }

/**@name Generic memory management function pointer definitions
 * @{
 */

/** @brief Memory block allocator funtion */
typedef void* TAaGpuCompressionsAlloc  (void* const opaque, const u32 size);
/** @brief Memory block unallocator funtion */
typedef void  TAaGpuCompressionsUnalloc(void* const opaque, void* const block);
/** @brief Memory block get size funtion */
typedef u32   TAaGpuCompressionsSizeGet(void* const opaque, const void* const block);

/**
 * @}
 */


/** @brief AaGpuCompressions general parameters */
typedef struct SAaGpuCompressionsParams
{
    EAaGpuCompressionsOpMode       opMode;     /**< Operation mode (compress/decompress) */
    EAaGpuCompressionsCompressRate rate;       /**< Compression rate */
    u32                            chunkSize;  /**< Size of a chunk used during (de)compression */
    EAaGpuCompressionsTrimming     trimming;   /**< Trimming state (enabled/disabled) */
    EAaGpuCompressionsHndlrState   state;      /**< State of the handler */
    void*                          opaque;     /**< Algorithm specific data */

    TAaGpuCompressionsAlloc*       allocator;   /**< Allocation operation implementation */
    TAaGpuCompressionsUnalloc*     unallocator; /**< Unallocation operation implementation */
    TAaGpuCompressionsSizeGet*     getSize;     /**< Get size operation implementation */
    void*                          memOpaque;   /**< (Un)allocator specific data */ 

} SAaGpuCompressionsParams;


/**@name Compressions algorithm impl. specific function pointer definitions
 * @{
 */

/** @brief Algorithm specific uninitialization function */
typedef EAaGpuCompressionsRet TAaGpuCompressionsUninit    (SAaGpuCompressionsParams* const params);
/** @brief Algorithm specific compression function */
typedef EAaGpuCompressionsRet TAaGpuCompressionsCompress  (SAaGpuCompressionsParams* const params, 
                                                           void const * const src, const u32 slen, 
                                                           void** dst, u32* dlen);
/** @brief Algorithm specific decompression function */
typedef EAaGpuCompressionsRet TAaGpuCompressionsDecompress(SAaGpuCompressionsParams* const params, 
                                                           void const * const src, const u32 slen, 
                                                           void** dst, u32* dlen);
/**
 * @}
 */


/** @brief AaGpuCompressions function pointers for operations */
typedef struct SAaGpuCompressionsOps
{
    TAaGpuCompressionsUninit*     uninit;     /**< Algorithm uninitialization operation */
    TAaGpuCompressionsCompress*   compress;   /**< Algorithm compression operation */
    TAaGpuCompressionsDecompress* decompress; /**< Algorithm decompression operation */

} SAaGpuCompressionsOps;

/** @brief AaGpuCompressions stream handler */
typedef struct SAaGpuCompressionsStream
{
    SAaGpuCompressionsOps          operations;  /**< Algorithm specific operations */
    SAaGpuCompressionsParams       parameters;  /**< Parameters of the stream */

} SAaGpuCompressionsStream;

/*----------------------- PUBLIC INTERFACES (MCU API) -----------------------------*/


/**@name dgCompressionsApiMcu public MCU API
 * @{
 */

/**@name AaGpuCompressions initialization API
 * @{
 */

/**
*******************************************************************************
*
*   @brief  AaGpuCompressionsUninit uninitializes stream handler
*
*
*   @param[out] handler  Pointer to a stream handler.
*
*   @return EAaGpuCompressionsRet_Ok  
*   @return EAaGpuCompressionsRet_InvalidParameter
*   @return EAaGpuCompressionsRet_InvalidOperationMode
*
*   @par Description:
*       This function uninitilizes earlier initilized stream handler. All 
*       dynamically allocated resources are released and the stream handler
*       can no longer be used for (de)compression. However it is possible to
*       reinitialize uninitialized handler by call of AaGpuCompressionsInit.
*
*   @par Errors:
*
*   @par Restrictions:
*       It is forbidden to call this function multiple times for same steam handler
*       without calling AaGpuCompressionsInit after every call to this function.
*
*   @par Example:
*
*   @code
*
*   SAaGpuCompressionsStream hndlr;
*   EAaGpuCompressionsRet rc;
*   
*   // Init using default allocator, unallocator and size get implementations
*   rc = AaGpuZlibInit(&hndlr, GLO_NULL, GLO_NULL, GLO_NULL, GLO_NULL);
*   rc = AaGpuCompressionsUninit(&hndlr);
*
*   // Init using default allocator, unallocator and size get implementations
*   rc = AaGpuZlibInit(&hndlr, GLO_NULL, GLO_NULL, GLO_NULL, GLO_NULL);
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
******************************************************************************/
EAaGpuCompressionsRet
AaGpuCompressionsUninit(SAaGpuCompressionsStream* const handler);


/**
*******************************************************************************
*
*   @brief  AaGpuCompressionsCompressRateSet sets compression rate for stream in compression mode
*
*   @param[in,out]  handler  Pointer to a stream handler.
*   @param[in]      rate     Compression rate to use.
*
*   @return EAaGpuCompressionsRet_Ok  
*   @return EAaGpuCompressionsRet_InvalidParameter
*   @return EAaGpuCompressionsRet_InvalidOperationMode
*
*   @par Description:
*
*   @par Errors:
*       If stream is in decompression mode, error code shall be returned.
*
*   @par Restrictions:
*       Must be called before actual compression is started. No effect if called
*       during compression thus error code shall be returned.
*
*   @par Example:
*
*   @code
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
******************************************************************************/
EAaGpuCompressionsRet
AaGpuCompressionsCompressRateSet(SAaGpuCompressionsStream* const handler, const EAaGpuCompressionsCompressRate rate);

/**
*******************************************************************************
*
*   @brief  AaGpuCompressionsChunkSizeSet sets chunk size
*
*
*   @param[in,out]  handler  Pointer to a stream handler.
*   @param[in]      size     Chunk size to use in bytes.
*
*   @return EAaGpuCompressionsRet_Ok  
*   @return EAaGpuCompressionsRet_InvalidParameter
*
*   @par Description:
*       Sets chunk size, used during dynamic memory allocations, to defined value.
*
*   @par Errors:
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
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
******************************************************************************/
EAaGpuCompressionsRet
AaGpuCompressionsChunkSizeSet(SAaGpuCompressionsStream* const handler, const u32 size);

/**
*******************************************************************************
*
*   @brief  AaGpuCompressionsTrimmingEnable enables or disables automatic buffer trimming
*
*
*   @param[in,out]  handler  Pointer to a stream handler.
*   @param[in]      state    Trimming state to use.
*
*   @return EAaGpuCompressionsRet_Ok  
*   @return EAaGpuCompressionsRet_InvalidParameter
*
*   @par Description:
*
*   @par Errors:
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
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
******************************************************************************/
EAaGpuCompressionsRet
AaGpuCompressionsTrimmingEnable(SAaGpuCompressionsStream* const handler, const EAaGpuCompressionsTrimming state);

/**
 * @}
 */

/**@name AaGpuCompressions compression API
 * @{
 */

 
/**
*******************************************************************************
*
*   @brief  AaGpuCompressionsCompress compress data in the given buffer
*
*   @param[in]  handler  Pointer to a stream handler.
*   @param[in]  src      Pointer to start of source data to compress.
*   @param[in]  slen     Length of the source data in bytes.
*   @param[out] dst      Pointer to a pointer to a destination buffer allocated automatically.
*   @param[out] dlen     Pointer to a buffer for length of the destination buffer in bytes.
*
*   @return EAaGpuCompressionsRet_Ok  
*   @return EAaGpuCompressionsRet_InvalidParameter
*   @return EAaGpuCompressionsRet_InvalidOperationMode
*
*   @par Description:
*       Previously initialized stream shall be set to compression mode.
*
*       All data in the given buffer is compressed at once and buffer for compressed data
*       is allocated automatically and returned to the caller. Compression is done as
*       a single pass.
*
*       User must provide pointer to a source data and the length of the source data.
*       Also placeholder for pointer to destination buffer (where compressed data is stored)
*       and placeholder for destination buffer length must be provided. They are set by this
*       function.
*
*       Destination buffer is allocated via AaMem, thus unallocation must be done using
*       AaMemUnRef call.
*
*
*   @par Errors:
*
*   @par Restrictions:
*       If a call is made to AaGpuCompressionsCompress function after algorithm
*       specific initilization, it is not possible to use the same stream for
*       decompression without uninitialization and initialization sequence
*       thus call to AaGpuCompressionsDecompress will fail.
*
*   @par Example:
*
*   @code
*
*   char* src = "1234567890";
*   char* dst;
*   u32 dstSize;
*   SAaGpuCompressionsStream hndlr;
*   EAaGpuCompressionsRet rc;
*   
*   // Init using default allocator, unallocator and size get implementations
*   rc = AaGpuZlibInit(&hndlr, GLO_NULL, GLO_NULL, GLO_NULL, GLO_NULL);
*   rc = AaGpuCompressionsCompress(&hndlr, src, strlen(src) + 1, (void**)&dst, &dstSize);
*   rc = AaGpuCompressionsUninit(&hndlr); // Uninit must be make to release resources
*
*   AaMemUnRef(&dst);
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
******************************************************************************/
EAaGpuCompressionsRet
AaGpuCompressionsCompress(SAaGpuCompressionsStream* const handler, void const * const src, 
                          const u32 slen, void** dst, u32* dlen);


/**
 * @}
 */

/**@name AaGpuCompressions decompression API
 * @{
 */

 
/**
*******************************************************************************
*
*   @brief  Decompress data in the given buffer and stores decompressed data to allocated buffer  
*
*   @param[in]  handler  Pointer to a stream handler.
*   @param[in]  src      Pointer to start of source data to decompress.
*   @param[in]  slen     Length of the source data in bytes.
*   @param[out] dst      Pointer to a pointer to a destination buffer allocated automatically.
*   @param[out] dlen     Pointer to a buffer for length of the destination buffer in bytes.
*
*   @return EAaGpuCompressionsRet_Ok
*   @return EAaGpuCompressionsRet_InvalidParameter  
*   @return EAaGpuCompressionsRet_InvalidOperationMode
*
*   @par Description:
*       Previously initialized stream shall be set to decompression mode.
*
*   @par Errors:
*
*   @par Restrictions:
*       If a call is made to AaGpuCompressionsDecompress function after algorithm
*       specific initilization, it is not possible to use the same stream for
*       compression without uninitialization and initialization sequence
*       thus call to AaGpuCompressionsCompress will fail.
*
*   @par Example:
*
*   @code
*
*   char* src = "1234567890";
*   char* cmprs;
*   u32 cmprsSize;
*   char* dst;
*   u32 dstSize;
*   SAaGpuCompressionsStream hndlr;
*   EAaGpuCompressionsRet rc;
*   
*   // Init using default allocator, unallocator and size get implementations
*   rc = AaGpuZlibInit(&hndlr, GLO_NULL, GLO_NULL, GLO_NULL, GLO_NULL);
*   rc = AaGpuCompressionsCompress(&hndlr, src, strlen(src) + 1, (void**)&cmprs, &cmprsSize);
*   rc = AaGpuCompressionsUninit(&hndlr);
*
*   // Stream uninit is now done so re-init can be done in order to use same
*   // stream handler for decompression.
*
*   // Init using default allocator, unallocator and size get implementations
*   rc = AaGpuZlibInit(&hndlr, GLO_NULL, GLO_NULL, GLO_NULL, GLO_NULL);
*   rc = AaGpuCompressionsDecompress(&hndlr, cmprs, cmprsSize, (void**)&dst, &dstSize);
*   rc = AaGpuCompressionsUninit(&hndlr);
*
*   // Since default allocator is in use, AaMemUnRef must be used for unallocations.
*   AaMemUnRef(&cmprs);
*   AaMemUnRef(&dst);
*   
*   AaSysLogPrint(EAaSysLogSeverityLevel_Debug, "Compress ratio: %.3f%\n", 
*                 ((double)(dstSize - cmprsSize) / (double)dstSize) * 100);
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
******************************************************************************/
EAaGpuCompressionsRet
AaGpuCompressionsDecompress(SAaGpuCompressionsStream* const handler, void const * const src, 
                            const u32 slen, void** dst, u32* dlen);

/**
 * @}
 */


/**@name AaGpuCompressions default allocator and unallocator API
 * @{
 */


/**
*******************************************************************************
*
*   @brief      Default allocator implementation
*
*   @param[in]  opaque  Pointer to unallocator implementation specific data.
*   @param[in]  size    Size of the memory block to allocate.
*
*   @return Pointer to an allocated memory block or GLO_NULL in case of error
*
*   @par Description:
*       Implementation of Compressions allocator to be used as a default when
*       user does not provide own implementation. Uses AaMem for allocation
*       and memory pool where the allocation takes place is EAaMemSysPoolId_Private.
*       This can be changed via compililing flag AACOMPRESSIONS_DEFAULT_POOL_ID.
*
*   @par Errors:
*       If allocation fails, GLO_NULL is returned.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
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
******************************************************************************/
void*
AaGpuCompressionsAllocator(void* const opaque, const u32 size);


/**
*******************************************************************************
*
*   @brief      Default unallocator implementation
*
*   @param[in]  opaque  Pointer to unallocator implementation specific data.
*   @param[in]  block   Pointer to a memory block to be unallocated.
*
*   @return None
*
*   @par Description:
*       Implementation of Compressions unallocator to be used as a default when
*       user does not provide own implementation. Uses AaMem for unallocation thus
*       allocator implementation should use AaMem for allocations.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
    None
*
*   @par Example:
*
*   @code
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
******************************************************************************/
void
AaGpuCompressionsUnallocator(void* const opaque, void* const block);

/**
*******************************************************************************
*
*   @brief      Default memory block size get implementation
*
*   @param[in]  opaque  Pointer to unallocator implementation specific data.
*   @param[in]  block   Pointer to a memory block (can be GLO_NULL).
*
*   @return Size of the memory block in bytes or 0 in case of error or #block
*           is GLO_NULL.
*
*   @par Description:
*       Implementation of Compressions memory block size get to be used as a 
*       default when user does not provide own implementation. Uses AaMem 
*       thus allocator implementation should use AaMem for allocations.
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
u32
AaGpuCompressionsSizeGet(void* const opaque, const void* const block);

/**
 * @}
 */


/**
 * AaGpuCompressions public MCU API
 * @}
 */


#ifdef __cplusplus
}
#endif

/* @} */

#endif /*  _MCU_IFAAGPUCOMPRESSIONS_H */
