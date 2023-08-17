/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaFile header for gzip compression services.
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IF_AAFILECOMPRESSIONGZ_H_
#define _MCU_RT_IF_AAFILECOMPRESSIONGZ_H_

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

/** @brief Type for AaFile gzip stream. */
typedef struct TAaGzFile TAaGzFile;

/**
*******************************************************************************
*
*   @brief    AaFileGzOpen() opens a gzip file and returns an associated gzip
*                            stream. (Predefined size for internal buffer.)
*
*   @param[in]  fileName   File path for gzip file to be opened.
*                          (given in AaFile notation: [ volume ] + path)
*   @param[in]  mode       Pattern for opening mode.
*
*   @return                gzip stream pointer if successfully opened,
*                          otherwise GLO_NULL is returned.
*
*   @par Description:
*
*   AaFileGzOpen() opens a gzip file from underlaying filesystem, allocates and
*   returns a gzip stream object which has to be used for further file access.
*   Internal buffer is allocated by default with 16384 bytes.
*
*   Only two modes are allowed for opening gzip files:
*
*   @code
*         r    Open gzip file for reading.
*         w    Truncate to zero length or create gzip file for writing.
*   @endcode
*
*   @note
*   Legacy mode 'b' is allowed as well, even if not used internally.
*   So in principle also mode strings 'rb' and 'wb' would be accepted.
*
*   @par Errors:
*
*   If opening a gzip file fails, because the file is not found or given mode is not applicable,
*   AaFileGzOpen() fails without raising an exception.
*
*   It raises exeptions analogous to AaFileOpen() (since internally reused for opening the file
*   or similarly implemented).
*
*   Additionally to that it raises exception
*   #EAaErrorCcs_AaFile_Exception when initialization of internal zlib stream fails.
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
*    TAaGzFile *gzstream;
*    char *fileName = "/ram/testfile.gz";
*
*    if ( GLO_NULL == (gzstream = AaFileGzOpen( fileName, "r")) ) {
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
TAaGzFile* AaFileGzOpen(const char* fileName, const char *mode);

/**
*******************************************************************************
*
*   @brief    AaFileGzOpenExt() opens a gzip file and returns an associated gzip
*                               stream with specified size for internal buffer.
*
*   @param[in]  fileName   File path for gzip file to be opened.
*                          (given in AaFile notation: [ volume ] + path)
*   @param[in]  mode       Pattern for opening mode.
*   @param[in]  bufferSize size to be allocated for internal buffer
*
*   @return                gzip stream pointer if successfully opened,
*                          otherwise GLO_NULL is returned.
*
*   @par Description:
*
*   AaFileGzOpenExt() opens a gzip file from underlaying filesystem, allocates and
*   returna a gzip stream object which has to be used for further file access.
*   The internal buffer is allocated with the value specified by the caller.
*
*   Only two modes are allowed for opening gzip files:
*
*   @code
*         r    Open gzip file for reading.
*         w    Truncate to zero length or create gzip file for writing.
*   @endcode
*
*   @note
*   Legacy mode 'b' is allowed as well, even if not used internally.
*   So in principle also mode strings 'rb' and 'wb' would be accepted.
*
*   @par Errors:
*
*   If opening a gzip file fails because the file is not found or given mode is not applicable
*   AaFileGzOpenExt() fails without raising an exception.
*
*   It raises exeptions analogous to AaFileOpen() (since internally reused for opening the file
*   or similarly implemented).
*
*   Additionally to that it raises exception
*   #EAaErrorCcs_AaFile_Exception when initialization of internal zlib stream fails.
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
*    TAaGzFile *gzstream;
*    char *fileName = "/ram/testfile.gz";
*
*    if ( GLO_NULL == (gzstream = AaFileGzOpenExt( fileName, "r", 65536)) ) {
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
TAaGzFile* AaFileGzOpenExt(const char* fileName, const char *mode, u32 bufferSize);

/**
*******************************************************************************
*
*   @brief    AaFileGzClose() closes a gzip stream.
*
*   @param[in]  gzstream   gzip stream pointer
*
*   @return     #EAaFileRet_Ok on success, otherwise #EAaFileRet_Error
*
*   @par Description:
*
*   This function unallocates the stream and closes the associated gzip file.
*   Be aware that in case of writing gzip streams the last portion of compressed
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
*    TAaFile *gzstream;
*    char *fileName = "/ram/testfile.gz";
*    if ( GLO_NULL == (gzstream = AaFileGzOpen( fileName, "w")) ) {
*        // Error handling
*        ...
*    }
*    ...
*
*    if ( EAaFileRet_Ok != AaFileGzClose(gzstream) ) {
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
EAaFileRet AaFileGzClose(TAaGzFile* gzstream);

/**
*******************************************************************************
*
*   @brief     AaFileGzRead() reads data from a gzip stream decompresses it
*              puts decompressed data in passed user buffer.
*
*   @param[in]  outbuf     pointer to user buffer where decompressed output
*                          will be copied.
*   @param[in]  outlen     size of user buffer
*   @param[in]  gzstream   gzip stream pointer
*
*   @return amount of successfully decompressed data in user buffer,
*           otherwise (if an error occured) 0 is returned.
*
*   @par Description:
*
*   The function reads from given gzip stream the required data amount (or less if no more available)
*   and copies it into the user buffer. Be aware that the data amount that is really read from the
*   related gzip file might be different, according to internal optimization and buffer sizes for
*   decompression.
*
*   @par Errors:
*
*   If associated stream is not related to a valid gzip file (if no valid gzip header was found) or
*   if there was a decompression error, then 0 is returned.
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
*    TAaGzFile *gzstream;
*    u32 ret;
*    char buf[MY_BUFSIZE];
*
*    if ( GLO_NULL == (gzstream = AaFileGzOpen( "testfile.gz", "r")) ) {
*        // Error handling
*        ...
*    }
*
*    if ( 0 == (ret = AaFileGzRead( buf, MY_BUFSIZE, gzstream)) ) {
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
u32 AaFileGzRead(void *outbuf, u32 outlen, TAaGzFile* gzstream);

/**
*******************************************************************************
*
*   @brief    AaFileGzWrite() compresses user data and writes it to the
*                             stream.
*
*   @param[in]  inbuf     pointer to user buffer with uncompressed input
*   @param[in]  inlen     size of user buffer
*   @param[in]  gzstream  gzip stream pointer
*
*   @return 0 in case of error, and inlen (that was passed as in parameter) in case of
*           success
*
*   @par Description:
*
*   The function compresses given amount of data and writes it to the stream related output file.
*   Be aware that the data amount that is passed is different to really written data, according to
*   compression factor, internal optimization and buffer sizes for compression.
*   There always might be a compressed rest, hold by the internal output buffer, that either is
*   written to the file with next call of AaFileGzWrite() or finally with AaFileGzClose().
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
*    TAaGzFile *gzstream;
*    char buf[MY_BUFSIZE];
*
*    // fill buf somehow
*    ...
*
*    if ( GLO_NULL == (gzstream = AaFileGzOpen( "testfile.gz", "w")) ) {
*        // Error handling
*        ...
*    }
*
*    if ( 0 == AaFileGzWrite( buf, MY_BUFSIZE, gzstream)) ) {
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
u32 AaFileGzWrite(void *inbuf, u32 inlen, TAaGzFile* gzstream);

/**
*******************************************************************************
*
*   @brief    AaFileGzCompress() compresses given source file to given gzip
*                                destination file. (Predefined size for internal
*                                buffer.)
*
*   @param[in]  srcFileName    File path for source file to be compressed
*                              (given in AaFile notation: [ volume ] + path)
*   @param[in]  destFileName   File path for gzip destination file
*                              (given in AaFile notation: [ volume ] + path)
*
*   @return     #EAaFileRet_Ok on success, otherwise #EAaFileRet_Error
*
*   @par Description:
*
*   The function compresses passed source file to a new gzip destination file.
*   It internally uses AaFileOpen(), AaFileGzOpen(), AaFileRead(), AaFileGzWrite(),
*   AaFileClose(), AaFileGzClose() and allocates an additional transfer buffer with
*   a fixed size. Internal buffer is allocated by default with 16384 bytes.
*
*   @par Errors:
*
*   Errors and exceptions are the superset of internally used functions AaFileOpen(),
*   AaFileGzOpen(), AaFileRead(), AaFileGzWrite(), AaFileClose() and AaFileGzClose().
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
*    char dest = "testfile.gz";
*
*    if ( EAaFileRet_Ok != AaFileGzCompress(src, dest) ) {
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
EAaFileRet AaFileGzCompress(const char* srcFileName, const char* destFileName);

/**
*******************************************************************************
*
*   @brief    AaFileGzCompressExt() compresses given source file to given gzip
*                                   destination file with specified size for
*                                   internal buffer.
*
*   @param[in]  srcFileName    File path for source file to be compressed
*                              (given in AaFile notation: [ volume ] + path)
*   @param[in]  destFileName   File path for gzip destination file
*                              (given in AaFile notation: [ volume ] + path)
*   @param[in]  bufferSize     size to be allocated for internal buffer
*
*   @return     #EAaFileRet_Ok on success, otherwise #EAaFileRet_Error
*
*   @par Description:
*
*   The function compresses passed source file to a new gzip destination file.
*   It internally uses AaFileOpen(), AaFileGzOpenExt(), AaFileRead(), AaFileGzWrite(),
*   AaFileClose(), AaFileGzClose() and allocates an additional transfer buffer with
*   a fixed size. The internal buffer is allocated with the value specified by the
*   caller.
*
*   @par Errors:
*
*   Errors and exceptions are the superset of internally used functions AaFileOpen(),
*   AaFileGzOpenExt(), AaFileRead(), AaFileGzWrite(), AaFileClose() and AaFileGzClose().
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
*    char dest = "testfile.gz";
*
*    if ( EAaFileRet_Ok != AaFileGzCompressExt(src, dest, 65536) ) {
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
EAaFileRet AaFileGzCompressExt(const char* srcFileName, const char* destFileName, u32 bufferSize);

/**
*******************************************************************************
*
*   @brief    AaFileGzDecompress() decompresses given gzip source file to given
*             destination file. (Predefined size for internal buffer.)
*
*   @param[in]  srcFileName    File path for gzip source file to be decompressed
*                              (given in AaFile notation: [ volume ] + path)
*   @param[in]  destFileName   File path for destination file
*                              (given in AaFile notation: [ volume ] + path)
*
*   @return     #EAaFileRet_Ok on success, otherwise #EAaFileRet_Error
*
*   @par Description:
*
*   The function decompresses passed gzip source file to a new destination file.
*   It internally uses AaFileOpen(), AaFileGzOpen(), AaFileGzRead, AaFileWrite(),
*   AaFileClose(), AaFileGzClose() and allocates an additional transfer buffer with
*   a fixed size. Internal buffer is allocated by default with 16384 bytes.
*
*   @par Errors:
*
*   Errors and exceptions are the superset of internally used functions AaFileOpen(),
*   AaFileGzOpen(), AaFileGzRead(), AaFileWrite(), AaFileClose() and AaFileGzClose().
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*    char src  = "testfile.gz";
*    char dest = "testfile.txt";
*
*    if ( EAaFileRet_Ok != AaFileGzDecompress(src, dest) ) {
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
EAaFileRet AaFileGzDecompress(const char* srcFileName, const char* destFileName);

/**
*******************************************************************************
*
*   @brief    AaFileGzDecompress() decompresses given gzip source file to given
*                                  destination file with specified size for
*                                  internal buffer.
*
*   @param[in]  srcFileName    File path for gzip source file to be decompressed
*                              (given in AaFile notation: [ volume ] + path)
*   @param[in]  destFileName   File path for destination file
*                              (given in AaFile notation: [ volume ] + path)
*   @param[in]  bufferSize     size to be allocated for internal buffer
*
*   @return     #EAaFileRet_Ok on success, otherwise #EAaFileRet_Error
*
*   @par Description:
*
*   The function decompresses passed gzip source file to a new destination file.
*   It internally uses AaFileOpen(), AaFileGzOpenExt(), AaFileGzRead, AaFileWrite(),
*   AaFileClose(), AaFileGzClose() and allocates an additional transfer buffer with
*   a fixed size. The internal buffer is allocated with the value specified by the
*   caller.
*
*   @par Errors:
*
*   Errors and exceptions are the superset of internally used functions AaFileOpen(),
*   AaFileGzOpenExt(), AaFileGzRead(), AaFileWrite(), AaFileClose() and AaFileGzClose().
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*    char src  = "testfile.gz";
*    char dest = "testfile.txt";
*
*    if ( EAaFileRet_Ok != AaFileGzDecompressExt(src, dest, 65536) ) {
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
EAaFileRet AaFileGzDecompressExt(const char* srcFileName, const char* destFileName, u32 bufferSize);

/**
*******************************************************************************
*
*   @brief    AaFileIsGz() Checks if a file is gzip compressed
*
*   @param[in]  fileName    File path for file to be checked
*                           (given in AaFile notation: [ volume ] + path)
*
*   @return   GLO_TRUE if file is gzip compressed, otherwise GLO_FALSE
*
*   @par Description:
*
*   The file is checked if it contains at least the gzip magic header in the
*   first two bytes of the file.
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
*    TAaGzFile* gzstream;
*    char gzPath  = "/ram/archive.gz";   // this is a gzip file
*
*    if ( AaFileIsGz(gzPath) ) {
*        if ( GLO_NULL == (gzstream = AaFileGzOpen(gzPath, "r")) ) {
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
TBoolean AaFileIsGz(const char* fileName);

/**
*******************************************************************************
*
*   @brief    AaFileIsGzOffset() Checks if a file contains a gzip compressed
*                                archive at given offset.
*
*   @param[in]  fileName    File path for file to be checked
*                           (given in AaFile notation: [ volume ] + path)
*   @param[in]  offset      Offset to be tested for gzip archive containement
*
*   @return   GLO_TRUE if file is gzip compressed, otherwise GLO_FALSE
*
*   @par Description:
*
*   The file is checked if it contains at least the gzip magic header at the
*   given offset. (The gzip magic header has 2 bytes.)
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
*    #include <IfAaFileCompressionGz.h>
*    #include <IfAaFileTar.h>
*
*    char filePath  = "/ram/binary_file.bin"; // this is a file which contains a gzip archive
*                                             // at postion 120
*
*    if ( AaFileIsGzOffset(filePath, 120) ) {
*        if ( EAaFileRet_Ok != AaFileTarGzipExtractOffset(filePath, GLO_NULL, 120) {
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
TBoolean AaFileIsGzOffset(const char* fileName, u32 offset);

/** @} */


#ifdef __cplusplus
}
#endif

#endif  /* _MCU_RT_IF_AAFILECOMPRESSIONGZ_H_ */
