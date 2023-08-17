/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaFile SICFTP interface header
* @module                AaFile
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IF_AAFILESICFTP_H_
#define _MCU_RT_IF_AAFILESICFTP_H_


/*----------------------- INCLUDED FILES --------------------------------------*/
#include <CcsCommon.h>

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/************************** PUBLIC INTERFACES *********************************/

/**
 * @addtogroup dgAaFileApiMcu
 * @ingroup    dgAaFile
 */

/** @{ */

/**
******************************************************************************
*
*   @brief    Transfer remote file-data to local node compressing it on-the-fly
*
*   @param[in]  remoteNode   Node-Id of remote (destination) node
*   @param[in]  srcFilePath  Pointer to string that contains the source filepath
*   @param[in]  destFilePath Pointer to string that contains the destination filepath
*
*   @return     #EAaFileSicFtpRet_Ok on success, specific error value otherwise (see below)
*
*   @par Description:
*   This command causes the SICFTP server to transfer a copy of the
*   file in the server's storage area, specified in the pathname, to the
*   local node's storage area. File will be stored in compressed form - XZ compression algorithm is used.
*   The status and contents of the file at the server site shall be unaffected.
*
*   @note Default values
*   Default values utilized by xz compression are: 0 for preset and
*   16384 for internal buffer size.
*
*   @note Timeout:
*   A timeout value will be given per default to indicate the time the server will
*   wait for the client to send SIC-messages or the client will wait for the server to send
*   SIC-messages. For further details see @ref dgAaFileAttributeTags
*
*   @note Blocking:
*   This function will block until either the file was successfully received from the
*   remote side or the timeout will be achieved. If you want to receive more than
*   one file from the remote side in parallel you have to launch separate threads
*   (EUs) for this purpose.
*
*   @par Errors:
*      - #EAaFileSicFtpRet_FileNotFound      The source file could not be found on remote local node. Also
*                                            source or destination file path might have been NULL or empty.
*      - #EAaFileSicFtpRet_FileAlreadyExists Destination file on local node already exists. (It has to
*                                            be removed before.)
*      - #EAaFileSicFtpRet_Timeout           Operation was aborted due to timeout. SICFTP server did
*                                            not respond in time.
*      - #EAaFileSicFtpRet_NoMemory          Operation was aborted due to lack of temporary memory
*                                            for execution at SICFTP server.
*      - #EAaFileSicFtpRet_FileNotReadable   A conflicting SICFTP operation was ongoing for source file.
*                                            Additionally it might be that the source file path is wrong
*                                            on SICFTP server.
*      - #EAaFileSicFtpRet_AddressFailure    SIC-messaging registration failed.
*      - #EAaFileSicFtpRet_MessageFailure    SIC-messaging failure. Either the SIC-message couldn't
*                                            be created, waiting for response failed before timeout
*                                            or the payload or response couldn't be extracted.
*      - #EAaFileSicFtpRet_SeekError         Seek in stream for source file failed.
*      - #EAaFileSicFtpRet_ReadError         Read error on source file. (Internal call of AaFileRead()
*                                            returned an error.)
*      - #EAaFileSicFtpRet_WriteError        Write error on destination file. (Internal call of AaFileWrite()
*                                            returned an error.)
*      - #EAaFileSicFtpRet_AccessViolation   Destination file could not be opened in write mode.
*      - #EAaFileSicFtpRet_RenameError       Renaming temporary destination file to target destination file
*                                            failed after completed transfer. (Internal call of AaFileRename()
*                                            returned an error.)
*
*   @par Restrictions:
*
*      - Length of the file name cannot exceed #AAFILE_FILENAME_MAX.
*      - The file path can only include portable characters, defined in AaFile
*        API documentation.
*
*   @see AaFileSicFtpGetXzExt()
*
*   @par Example:
*
*   @code
*
*    TAaSysComNid remoteNode = 0x1011;
*    char* srcFilePath = "/ram/yourfile.txt"
*    char* destFilePath = "/ram/myfile.txt.xz"
*    EAaFileSicFtpRet retval = EAaFileRet_LocalError;
*
*    if ( EAaFileSicFtpRet_Ok !=
*         (retval = AaFileSicFtpGetXz(remoteNode, srcFilePath, destFilePath)) ) {
*
*        // Error Handling
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
EAaFileSicFtpRet AaFileSicFtpGetXz( TAaSysComNid remoteNode,
                                    const char*  srcFilePath,
                                    const char*  destFilePath );


/**
******************************************************************************
*
*   @brief    Transfer remote file-data to local node compressing it on-the-fly
*
*   @param[in]  remoteNode    Node-Id of remote (destination) node
*   @param[in]  srcFilePath   Pointer to string that contains the source file path
*   @param[in]  destFilePath  Pointer to string that contains the destination file path
*   @param[in]  bufferSize    Size to be allocated for internal buffer
*   @param[in]  xzPreset      xz preset (Range: [0..9])
*
*   @return     #EAaFileSicFtpRet_Ok on success, specific error value otherwise (see below)
*
*   @par Description:
*   This command causes the SICFTP server to transfer a copy of the
*   file in the server's storage area, specified in the pathname, to the
*   local node's storage area. File will be stored in compressed form - XZ compression algorithm is used.
*   The status and contents of the file at the server site shall be unaffected.
*
*   @note Timeout:
*   A timeout value will be given per default to indicate the time the server will
*   wait for the client to send SIC-messages or the client will wait for the server to send
*   SIC-messages. For further details see @ref dgAaFileAttributeTags
*
*   @note Blocking:
*   This function will block until either the file was successfully received from the
*   remote side or the timeout will be achieved. If you want to receive more than
*   one file from the remote side in parallel you have to launch separate threads
*   (EUs) for this purpose.
*
*   @par Errors:
*      - #EAaFileSicFtpRet_FileNotFound         The source file could not be found on remote local node. Also
*                                               source or destination file path might have been NULL or empty.
*      - #EAaFileSicFtpRet_FileAlreadyExists    Destination file on local node already exists. (It has to
*                                               be removed before.)
*      - #EAaFileSicFtpRet_Timeout              Operation was aborted due to timeout. SICFTP server did
*                                               not respond in time.
*      - #EAaFileSicFtpRet_NoMemory             Operation was aborted due to lack of temporary memory
*                                               for execution at SICFTP server.
*      - #EAaFileSicFtpRet_FileNotReadable      A conflicting SICFTP operation was ongoing for source file.
*                                               Additionally it might be that the source file path is wrong
*                                               on SICFTP server.
*      - #EAaFileSicFtpRet_AddressFailure       SIC-messaging registration failed.
*      - #EAaFileSicFtpRet_MessageFailure       SIC-messaging failure. Either the SIC-message couldn't
*                                               be created, waiting for response failed before timeout
*                                               or the payload or response couldn't be extracted.
*      - #EAaFileSicFtpRet_SeekError            Seek in stream for source file failed.
*      - #EAaFileSicFtpRet_ReadError            Read error on source file. (Internal call of AaFileRead()
*                                               returned an error.)
*      - #EAaFileSicFtpRet_WriteError           Write error on destination file. (Internal call of AaFileWrite()
*                                               returned an error.)
*      - #EAaFileSicFtpRet_AccessViolation      Destination file could not be opened in write mode.
*      - #EAaFileSicFtpRet_RenameError          Renaming temporary destination file to target destination file
*                                               failed after completed transfer. (Internal call of AaFileRename()
*                                               returned an error.)
*      - #EAaFileSicFtpRet_WrongInputParameter  Incorrect input parameters: preset or internal buffer size
*                                               (Internal call of AaFileOpenXzExt)
*
*
*   @par Restrictions:
*
*      - Length of the file name cannot exceed #AAFILE_FILENAME_MAX.
*      - The file path can only include portable characters, defined in AaFile
*        API documentation.
*
*   @see AaFileSicFtpGetXz()
*
*   @par Example:
*
*   @code
*
*    TAaSysComNid remoteNode = 0x1011;
*    char* srcFilePath = "/ram/yourfile.txt"
*    char* destFilePath = "/ram/myfile.txt.xz"
*    EAaFileSicFtpRet retval = EAaFileRet_LocalError;
*    u8  preset     = 0;
*    u32 bufferSize = 16384;
*
*    if ( EAaFileSicFtpRet_Ok !=
*         (retval = AaFileSicFtpGetXzExt(remoteNode, srcFilePath, destFilePath, bufferSize, preset)) ) {
*
*        // Error Handling
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
EAaFileSicFtpRet AaFileSicFtpGetXzExt( TAaSysComNid remoteNode,   const char*  srcFilePath,
                                       const char*  destFilePath, u32          bufferSize,
                                       u8           xzPreset );

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _MCU_RT_IF_AAFILESICFTP_H_ */
