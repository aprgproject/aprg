/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/ 
#ifndef _MCU_RT_IFAAGPUZLIB_H
#define _MCU_RT_IFAAGPUZLIB_H
#include "CcsCommon.h"

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
*@defgroup AaGpuZlibApi Zlib
*@ingroup dgCompressionsApi
*
* @{ 
*/


/*----------------------- INCLUDED FILES --------------------------------------*/

#include <glo_def.h>
    
#include <IfAaGpuCompressions.h>


#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

#ifndef AAGPUZLIB_CHUNK_SIZE
  #define AAGPUZLIB_CHUNK_SIZE 0xFFF
#endif


/*----------------------- PUBLIC INTERFACES --------------------------------*/

/**
*******************************************************************************
*
*   @brief  Initializes zlib stream handler to be used for (de)compression    
*
*
*   @param[out] handler      Pointer to a zlib data stream handler.
*   @param[in]  allocator    Pointer to allocator implemetation or GLO_NULL.
*   @param[in]  unallocator  Pointer to unallocator implemetation or GLO_NULL.
*   @param[in]  sizeGet      Pointer to memory block size get implementation or GLO_NULL. 
*   @param[in]  opaque       Pointer to allocator and/or unallocator specific data or GLO_NULL.
*
*   @return EAaGpuCompressionsRet_Ok  
*   @return EAaGpuCompressionsRet_InvalidParameter
*
*   @par Description:
*       This function prepares zlib stream handler to operate in compression or
*       decompression mode. Actual operation mode is determined by call to
*       AaGpuCompressionsCompress or AaGpuCompressionsDecompress after initialization. 
*
*       Memory block allocator, unallocator and size get implementation functions can be 
*       provided or they can be set to GLO_NULL in which case default implementations 
*       shall be used. If implementations need some implementation specific data, the data 
*       can be passed via #opaque parameter. 
*
*       Compression rate shall be EAaGpuCompressionCompressRate_Default by default and 
*       chunk size shall be set to AAGPUZLIB_CHUNK_SIZE and trimming according to 
*       AAGPUZLIB_TRIM_DST.
*
*       Since some resources are allocated dynamically when calling this function, 
*       it is important call AaGpuCompressionsUninit after (de)compression operation is 
*       finalized and there is no more need for the stream. Also if operation mode is
*       changed, the stream must be first uninitialized and the initialized again.
*
*   @par Errors:
*
*   @par Restrictions:
*       It is forbidden to call this function multiple times for same steam handler
*       without calling AaGpuCompressionsUninit after every call to this function.
*
*       Stream handler cannot be shared between EEs/EUs even if it allocated from
*       AaMem pool like EAaMemSysPoolId_Shared since internal zlib stream 
*       and algorithms are not synchronized.
*
*       First call to AaGpuCompressionsCompress or AaGpuCompressionsDecompress after
*       initialization determines in which operation mode the stream shall be set to. 
*       After that the operation mode cannot be changed without doing 
*       AaGpuCompressionsUninit and AaGpuZlibInit before new call to 
*       AaGpuCompressionsCompress or AaGpuCompressionsDecompress.
*
*   @par Example:
*
*   @code
*
*   SAaGpuCompressionsStream hndlr;
*   EAaGpuCompressionsRet rc;
*   
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
AaGpuZlibInit(SAaGpuCompressionsStream* const handler, 
              const TAaGpuCompressionsAlloc* const allocator,
              const TAaGpuCompressionsUnalloc* const unallocator,
              const TAaGpuCompressionsSizeGet* const sizeGet, 
              void* const opaque);


#ifdef __cplusplus
}
#endif

/** @} */

#endif /*  _MCU_IFAAGPUZLIB_H */
