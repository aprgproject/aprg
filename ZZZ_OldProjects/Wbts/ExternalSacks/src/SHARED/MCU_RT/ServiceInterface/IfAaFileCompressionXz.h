/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaFile header for xz compression services.
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IF_AAFILECOMPRESSIONXZ_H_
#define _MCU_RT_IF_AAFILECOMPRESSIONXZ_H_

#include <CcsCommon.h>
#include <IfAaFile.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @addtogroup dgAaFileApiMcu
 * @ingroup    dgAaFile
 */

/** @{ */

/** @brief Type for AaFile xz stream. */
typedef struct TAaXzFile TAaXzFile;

/**
*******************************************************************************
*
*   @brief    AaFileXzOpen() opens an xz file and returns an associated xz
*                            stream. (Predefined preset and size for internal
*                            buffer.)
*
*   @param[in]  fileName   File path for xz file to be opened.
*                          (given in AaFile notation: [ volume ] + path)
*   @param[in]  mode       Pattern for opening mode.
*
*   @return                xz stream pointer if successfully opened,
*                          otherwise GLO_NULL is returned.
*
*   @par Description:
*
*   AaFileXzOpen() opens a xz file from underlaying filesystem, allocates and
*   returns an xz stream object which has to be used for further file access.
*   Preset 5 is used and internal buffer is allocated by default with 16384 bytes.
*
*   Only two modes are allowed for opening xz files:
*
*   @code
*         r    Open xz file for reading.
*         w    Truncate to zero length or create xz file for writing.
*   @endcode
*
*   @note
*   Legacy mode 'b' is allowed as well, even if not used internally.
*   So in principle also mode strings 'rb' and 'wb' would be accepted.
*
*   @par Errors:
*
*   If opening an xz file fails, because the file is not found or given mode is not applicable,
*   AaFileXzOpen() fails without raising an exception.
*
*   It raises exeptions analogous to AaFileOpen() (since internally reused for opening the file
*   or similarly implemented).
*
*   Additionally to that it raises exception
*   #EAaErrorCcs_AaFile_Exception when initialization of internal lzma stream fails.
*
*   @par Restrictions:
*      - Length of the file name cannot exceed #AAFILE_FILENAME_MAX
*      - The file path can only include portable characteres, as defined in AaFile
*        API documentation.
*
*   @par Example:
*
*   @code
*
*    TAaXzFile *xzstream;
*    char *fileName = "/ram/testfile.xz";
*
*    if ( GLO_NULL == (xzstream = AaFileXzOpen( fileName, "r")) ) {
*        // Error handling
*        ...
*    }
*    ...
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   None
*
*   @par Future directions:
*
*   None
*
*   @see
*
******************************************************************************/
TAaXzFile* AaFileXzOpen(const char* fileName, const char *mode);

/**
*******************************************************************************
*
*   @brief    AaFileXzOpenExt() opens an xz file and returns an associated xz
*                               stream with specified preset and size for internal
*                               buffer.
*
*   @param[in]  fileName   File path for xz file to be opened.
*                          (given in AaFile notation: [ volume ] + path)
*   @param[in]  mode       Pattern for opening mode.
*   @param[in]  bufferSize size to be allocated for internal buffer
*   @param[in]  preset     xz preset (Range: [0..9])
*
*   @return                xz stream pointer if successfully opened,
*                          otherwise GLO_NULL is returned.
*
*   @par Description:
*
*   AaFileXzOpenExt() opens an xz file from underlaying filesystem, allocates and
*   returna an xz stream object which has to be used for further file access.
*   Preset and internal buffer size is specified by the caller.
*
*   Only two modes are allowed for opening xz files:
*
*   @code
*         r    Open xz file for reading.
*         w    Truncate to zero length or create xz file for writing.
*   @endcode
*
*   @note
*   Legacy mode 'b' is allowed as well, even if not used internally.
*   So in principle also mode strings 'rb' and 'wb' would be accepted.
*
*   @par Errors:
*
*   If opening an xz file fails, because the file is not found or given mode is not applicable,
*   AaFileXzOpenExt() fails without raising an exception.
*
*   It raises exeptions analogous to AaFileOpen() (since internally reused for opening the file
*   or similarly implemented).
*
*   Additionally to that it raises exception
*   #EAaErrorCcs_AaFile_Exception when initialization of internal lzma stream fails.
*
*   @par Restrictions:
*      - Length of the file name cannot exceed #AAFILE_FILENAME_MAX
*      - The file path can only include portable characteres, as defined in AaFile
*        API documentation.
*
*   @par Example:
*
*   @code
*
*    TAaXzFile *xzstream;
*    char *fileName = "/ram/testfile.xz";
*
*    if ( GLO_NULL == (xzstream = AaFileXzOpenExt( fileName, "r", 65536, 0)) ) {
*        // Error handling
*        ...
*    }
*    ...
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   None
*
*   @par Future directions:
*
*   None
*
*   @see
*
******************************************************************************/
TAaXzFile* AaFileXzOpenExt(const char* fileName, const char *mode, u32 bufferSize, u8 preset);

/**
*******************************************************************************
*
*   @brief    AaFileXzClose() closes an xz stream.
*
*   @param[in]  xzstream   xz stream pointer
*
*   @return     #EAaFileRet_Ok on success, otherwise #EAaFileRet_Error
*
*   @par Description:
*
*   This function unallocates the stream and closes the associated xz file.
*   Be aware that in case of writing on xz streams the last portion of compressed
*   data will be written by this function.
*
*   @par Errors:
*
*   Errors and exceptions are analogous to AaFileClose() (since internally reused for closing the file
*   or similarly implemented).
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*    TAaFile *xzstream;
*    char *fileName = "/ram/testfile.xz";
*    if ( GLO_NULL == (xzstream = AaFileXzOpen( fileName, "w")) ) {
*        // Error handling
*        ...
*    }
*    ...
*
*    if ( EAaFileRet_Ok != AaFileXzClose(xzstream) ) {
*        // Error handling
*        ...
*    }
*    ...
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   None
*
*   @par Future directions:
*
*   None
*
*   @see
*
******************************************************************************/
EAaFileRet AaFileXzClose(TAaXzFile* xzstream);

/**
*******************************************************************************
*
*   @brief     AaFileXzRead() reads data from an xz stream decompresses it
*              puts decompressed data in passed user buffer.
*
*   @param[in]  outbuf     pointer to user buffer where decompressed output
*                          will be copied.
*   @param[in]  outlen     size of user buffer
*   @param[in]  xzstream   xz stream pointer
*
*   @return amount of successfully decompressed data in user buffer,
*           otherwise (if an error occured) 0 is returned.
*
*   @par Description:
*
*   The function reads from given xz stream the required data amount (or less if no more available)
*   and copies it into the user buffer. Be aware that the data amount that is really read from the
*   related xz file might be different, according to internal optimization and buffer sizes for
*   decompression.
*
*   @par Errors:
*
*   If associated stream is not related to a valid xz file, e.g. if there was a decompression error,
*   then 0 is returned.
*
*   Exception #EAaErrorCcs_AaFile_Exception is raised, when given stream was not opened in read
*   mode before.
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*    TAaXzFile *xzstream;
*    u32 ret;
*    char buf[MY_BUFSIZE];
*
*    if ( GLO_NULL == (xzstream = AaFileXzOpen( "testfile.xz", "r")) ) {
*        // Error handling
*        ...
*    }
*
*    if ( 0 == (ret = AaFileXzRead( buf, MY_BUFSIZE, xzstream)) ) {
*        // Error handling
*        ...
*    }
*    ...
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   None
*
*   @par Future directions:
*
*   None
*
*   @see
*
******************************************************************************/
u32 AaFileXzRead(void *outbuf, u32 outlen, TAaXzFile* xzstream);

/**
*******************************************************************************
*
*   @brief    AaFileXzWrite() compresses user data and writes it to the
*                             stream.
*
*   @param[in]  inbuf     pointer to user buffer with uncompressed input
*   @param[in]  inlen     size of user buffer
*   @param[in]  xzstream  xz stream pointer
*
*   @return amount of successfully compressed data (be aware that this might
*           be different to amount of uncompressed data that was passed.)
*
*   @par Description:
*
*   The function compresses given amount of data and writes it to the stream related output file.
*   Be aware that the data amount that is passed is different to really written data, according to
*   compression factor, internal optimization and buffer sizes for compression.
*   There always might be a compressed rest, hold by the internal output buffer, that either is
*   written to the file with next call of AaFileXzWrite() or finally with AaFileXzClose().
*
*   @par Errors:
*
*   I there was a compression error, then 0 is returned.
*
*   Exception #EAaErrorCcs_AaFile_Exception is raised, when given stream was not opened in write
*   mode before.
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*    TAaXzFile *xzstream;
*    char buf[MY_BUFSIZE];
*
*    // fill buf somehow
*    ...
*
*    if ( GLO_NULL == (xzstream = AaFileXzOpen( "testfile.xz", "w")) ) {
*        // Error handling
*        ...
*    }
*
*    if ( 0 == AaFileXzWrite( buf, MY_BUFSIZE, xzstream)) ) {
*        // Error handling
*        ...
*    }
*    ...
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   None
*
*   @par Future directions:
*
*   None
*
*   @see
*
******************************************************************************/
u32 AaFileXzWrite(void *inbuf, u32 inlen, TAaXzFile* xzstream);

/**
*******************************************************************************
*
*   @brief    AaFileXzCompress() compresses given source file to given xz
*                                destination file. (Predefined preset and size
*                                for internal buffer.)
*
*   @param[in]  srcFileName    File path for source file to be compressed
*                              (given in AaFile notation: [ volume ] + path)
*   @param[in]  destFileName   File path for xz destination file
*                              (given in AaFile notation: [ volume ] + path)
*
*   @return     #EAaFileRet_Ok on success, otherwise #EAaFileRet_Error
*
*   @par Description:
*
*   The function compresses passed source file to a new xz destination file.
*   It internally uses AaFileOpen(), AaFileXzOpen(), AaFileRead(), AaFileXzWrite(),
*   AaFileClose(), AaFileXzClose() and allocates an additional transfer buffer with
*   a fixed size. Preset 5 is used and internal buffer is allocated by default with
*   16384 bytes.
*
*   @par Errors:
*
*   Errors and exceptions are the superset of internally used functions AaFileOpen(),
*   AaFileXzOpen(), AaFileRead(), AaFileXzWrite(), AaFileClose() and AaFileXzClose().
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*    char src  = "testfile.txt";
*    char dest = "testfile.xz";
*
*    if ( EAaFileRet_Ok != AaFileXzCompress(src, dest) ) {
*        // Error handling
*        ...
*    }
*    ...
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   None
*
*   @par Future directions:
*
*   None
*
*   @see
*
******************************************************************************/
EAaFileRet AaFileXzCompress(const char* srcFileName, const char* destFileName);

/**
*******************************************************************************
*
*   @brief    AaFileXzCompressExt() compresses given source file to given xz
*                                   destination file with specified preset and
*                                   size for internal buffer.
*
*   @param[in]  srcFileName    File path for source file to be compressed
*                              (given in AaFile notation: [ volume ] + path)
*   @param[in]  destFileName   File path for xz destination file
*                              (given in AaFile notation: [ volume ] + path)
*   @param[in]  bufferSize     size to be allocated for internal buffer
*   @param[in]  preset         xz preset (Range: [0..9])
*
*   @return     #EAaFileRet_Ok on success, otherwise #EAaFileRet_Error
*
*   @par Description:
*
*   The function compresses passed source file to a new xz destination file.
*   It internally uses AaFileOpen(), AaFileXzOpenExt(), AaFileRead(), AaFileXzWrite(),
*   AaFileClose(), AaFileXzClose() and allocates an additional transfer buffer with
*   a fixed size. Preset and internal buffer size is specified by the caller.
*
*   @par Errors:
*
*   Errors and exceptions are the superset of internally used functions AaFileOpen(),
*   AaFileXzOpenExt(), AaFileRead(), AaFileXzWrite(), AaFileClose() and AaFileXzClose().
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*    char src  = "testfile.txt";
*    char dest = "testfile.xz";
*
*    if ( EAaFileRet_Ok != AaFileXzCompressExt(src, dest, 65536, 2) ) {
*        // Error handling
*        ...
*    }
*    ...
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   None
*
*   @par Future directions:
*
*   None
*
*   @see
*
******************************************************************************/
EAaFileRet AaFileXzCompressExt(const char* srcFileName, const char* destFileName, u32 bufferSize, u8 preset);

/**
*******************************************************************************
*
*   @brief    AaFileXzDecompress() decompresses given xz source file to given
*                                  destination file. (Predefined preset and size
*                                  for internal buffer.)
*
*   @param[in]  srcFileName    File path for xz source file to be decompressed
*                              (given in AaFile notation: [ volume ] + path)
*   @param[in]  destFileName   File path for destination file
*                              (given in AaFile notation: [ volume ] + path)
*
*   @return     #EAaFileRet_Ok on success, otherwise #EAaFileRet_Error
*
*   @par Description:
*
*   The function decompresses passed xz source file to a new destination file.
*   It internally uses AaFileOpen(), AaFileXzOpen(), AaFileXzRead, AaFileWrite(),
*   AaFileClose(), AaFileXzClose() and allocates an additional transfer buffer with
*   a fixed size. Preset 5 is used and internal buffer is allocated by default with
*   16384 bytes.
*
*   @par Errors:
*
*   Errors and exceptions are the superset of internally used functions AaFileOpen(),
*   AaFileXzOpen(), AaFileXzRead(), AaFileWrite(), AaFileClose() and AaFileXzClose().
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*    char src  = "testfile.xz";
*    char dest = "testfile.txt";
*
*    if ( EAaFileRet_Ok != AaFileXzDecompress(src, dest) ) {
*        // Error handling
*        ...
*    }
*    ...
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   None
*
*   @par Future directions:
*
*   None
*
*   @see
*
******************************************************************************/
EAaFileRet AaFileXzDecompress(const char* srcFileName, const char* destFileName);

/**
*******************************************************************************
*
*   @brief    AaFileXzDecompress() decompresses given xz source file to given
*                                  destination file with specified size for
*                                  internal buffer.
*
*   @param[in]  srcFileName    File path for xz source file to be decompressed
*                              (given in AaFile notation: [ volume ] + path)
*   @param[in]  destFileName   File path for destination file
*                              (given in AaFile notation: [ volume ] + path)
*   @param[in]  bufferSize     size to be allocated for internal buffer
*
*   @return     #EAaFileRet_Ok on success, otherwise #EAaFileRet_Error
*
*   @par Description:
*
*   The function decompresses passed xz source file to a new destination file.
*   It internally uses AaFileOpen(), AaFileXzOpenExt(), AaFileXzRead, AaFileWrite(),
*   AaFileClose(), AaFileXzClose() and allocates an additional transfer buffer with
*   a fixed size. The internal buffer is allocated with the value specified by the
*   caller.
*
*   @par Errors:
*
*   Errors and exceptions are the superset of internally used functions AaFileOpen(),
*   AaFileXzOpenExt(), AaFileXzRead(), AaFileWrite(), AaFileClose() and AaFileXzClose().
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*    char src  = "testfile.xz";
*    char dest = "testfile.txt";
*
*    if ( EAaFileRet_Ok != AaFileXzDecompressExt(src, dest, 65536) ) {
*        // Error handling
*        ...
*    }
*    ...
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   None
*
*   @par Future directions:
*
*   None
*
*   @see
*
******************************************************************************/
EAaFileRet AaFileXzDecompressExt(const char* srcFileName, const char* destFileName, u32 bufferSize);

/**
*******************************************************************************
*
*   @brief    AaFileIsXz() Checks if a file is xz compressed
*
*   @param[in]  fileName    File path for file to be checked
*                           (given in AaFile notation: [ volume ] + path)
*
*   @return   GLO_TRUE if file is xz compressed, otherwise GLO_FALSE
*
*   @par Description:
*
*   The file is checked if it contains at least the xz magic header in the
*   first six bytes of the file.
*
*   @par Errors:
*
*   Errors and exceptions are similar to internally used function AaFileOpen().
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*    TAaXzFile* xzstream;
*    char xzPath  = "/ram/archive.xz";   // this is an xz file
*
*    if ( AaFileIsXz(xzPath) ) {
*        if ( GLO_NULL == (xzstream = AaFileXzOpen(xzPath, "r")) ) {
*           // Error handling
*           ...
*        }
*    }
*    ...
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   None
*
*   @par Future directions:
*
*   None
*
*   @see
*
******************************************************************************/
TBoolean AaFileIsXz(const char* fileName);

/** @} */


#ifdef __cplusplus
}
#endif

#endif  /* _MCU_RT_IF_AAFILECOMPRESSIONXZ_H_ */
