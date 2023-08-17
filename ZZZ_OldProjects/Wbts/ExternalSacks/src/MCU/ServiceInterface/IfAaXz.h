/** @file
* @brief Functions for buffers compression and decompression with lzma.
* @copyright 2019 Nokia. All rights reserved.
*/

#ifndef _MCU_IF_AAXZ_H_
#define _MCU_IF_AAXZ_H_

#include <CcsCommon.h>
#include <glo_def.h>
#include <../Definitions/IfAaXz_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup dgAaXzMcu AaXz MCU API
* @ingroup  dgCompressions
*/

/** @{ */

/**
* @brief Compress data buffer with lzma algorithm.
*
* @param[in]  data               data to be compressed
* @param[in]  dataSize           data size
* @param[out] compressedData     buffer for compressed data,
*                                allocated in case of success compression,
*                                otherwise set to GLO_NULL
* @param[out] compressedDataSize size of compressed data, on failure it
*                                is set to 0
*
* @retval #EAaXzRet_Ok           operation was successful
* @retval #EAaXzRet_InvalidParam invalid parameter
* @retval #EAaXzRet_BufferError  memory allocation for compressed data failed
* @retval #EAaXzRet_Error        compression failed
*
* @par Description
* The function is used to compress data with lzma alghorithm,
* compression preset is set to 0 (preset 0 results in the fastest and least memory compression).
*
* @par Errors
* See Return values section.
*
* @par Restrictions
* - compressedData is allocated and must be freed by AaMemUnRef only when the function returns #EAaXzRet_Ok
*
* @par Example
* @code
*
* #include <IfAaXz.h>
* #include <IfAaMem.h>
* #include <string.h>
*
* const char* const data = "test data test data test data";
* const u32 dataSize = strlen(data) + 1;
* u8* compressedData = GLO_NULL;
* u32 compressedDataSize = 0;
*
* EAaXzRet xzRet = AaXzCompress((const u8*)data, dataSize, &compressedData, &compressedDataSize);
* if (GLO_NULL == compressedData) {
*   // handle compression failure
*   // log xzRet value
* }
* else {
*   // handle compressed data
*   AaMemUnRef((const void**)&compressedData);
* }
* @endcode
*
* @par Rationale
* 5GC001507, LTE4223-B-a
*
* @see AaXzDecompress()
*/
EAaXzRet AaXzCompress(const u8* data, const u32 dataSize, u8** compressedData, u32* compressedDataSize);

/**
* @brief Decompress data buffer with lzma algorithm.
*
* @param[in]  data                 compressed data
* @param[in]  dataSize             compressed data size
* @param[out] uncompressedData     buffer for decompressed data
*                                  allocated in case of success decompression,
*                                  otherwise set to GLO_NULL
* @param[out] uncompressedDataSize size of decompressed data, on failure it
*                                  is set to 0
*
* @retval #EAaXzRet_Ok           operation was successful
* @retval #EAaXzRet_InvalidParam invalid parameter
* @retval #EAaXzRet_BufferError  memory allocation for decompressed data failed
* @retval #EAaXzRet_Error        decompression failed
*
* @par Description
* The function is used to decompress data with lzma alghorithm.
*
* @par Errors
* See Return values section.
*
* @par Restrictions
* - uncompressedData is allocated and must be freed by AaMemUnRef only when the function returns #EAaXzRet_Ok
*
* @par Example
* @code
*
* #include <IfAaXz.h>
* #include <IfAaMem.h>
* #include <string.h>
*
* #define SIZE (u32)1024
*
* const u8 data[SIZE]; //filled with compressed data
* const u32 dataSize = SIZE;
* u8* decompressedData = GLO_NULL;
* u32* dempressedDataSize = 0;
*
* EAaXzRet xzRet = AaXzDecompress(data, dataSize, &decompressedData, &decompressedDataSize);
* if (GLO_NULL == decompressedData) {
*   // handle decompression failure
*   // log xzRet value
* }
* else {
*   // handle decompressed data
*   AaMemUnRef((const void**)&decompressedData);
* }
* @endcode
*
* @par Rationale
* 5GC001507, LTE4223-B-a
*
* @see AaXzCompress()
*/
EAaXzRet AaXzDecompress(const u8* data, const u32 dataSize, u8** uncompressedData, u32* uncompressedDataSize);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _MCU_IF_AAXZ_H_  */
