/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaFile SICFTP interface header
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _COMMON_IF_AAFILESICFTP_H_
#define _COMMON_IF_AAFILESICFTP_H_

#include <glo_def.h>
#include <CcsCommon.h>
#include <IfAaSysCom_Defs.h>     /* for TAaSysComNid */

#ifdef CCS_NEW_IF_STRUCTURE
#include <../../COMMON/Definitions/IfAaFileSicFtp_Defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaFileApiCommon
 * @ingroup    dgAaFile
 */

/** @{ */

/**
 * @name AaFileSicFtp common operations
 * @brief Client SICFTP functions available
 */

/** @{ */

/**
******************************************************************************
*
*   @brief    Store transmitted file-data on remote node's local file storage
*
*   @param[in]  remoteNode   Node-Id of remote (destination) node
*   @param[in]  srcFilePath  Pointer to string that contains the source filepath
*   @param[in]  destFilePath Pointer to string that contains the destination filepath
*
*   @return     #EAaFileSicFtpRet_Ok on success, specific error value otherwise (see below)
*
*   @par Description:
*   This command causes the SICFTP server process to accept the data
*   transferred via the SIC-data connection and to store the data as
*   a file at the server's storage area.  If the file specified in the
*   pathname exists at the server site, then its contents shall NOT
*   be replaced by the data being transferred and an error-code should
*   be returned.
*   A new file is created at the server site if the file specified in the
*   pathname does not already exist.
*
*   @note Timeout:
*   A timeout value will be given per default to indicate the time the server will
*   wait for the client to send SIC-messages or the client will wait for the server to send
*   SIC-messages. Server timeout value is set in config tag ccs.service.aafile.sicftp.server.timeout
*   and client timeout value is set in config tag ccs.service.aafile.sicftp.client.timeout.
*
*   @note Blocking:
*   This function will block until either the file was successfully sent to the
*   remote side or the timeout will be achieved. If you want to send more than
*   one file to the remote side in parallel you have to launch separate threads
*   (EUs) for this purpose.
*
*   @par Errors:
*      - #EAaFileSicFtpRet_Ok                   AaFileSicFtpPut() has succeeded
*      - #EAaFileSicFtpRet_FileNotFound         The source file was not found on local node. Also source
*                                               or destination file path might have been NULL or empty.
*      - #EAaFileSicFtpRet_FileAlreadyExists    Destination file on remote node already exists. (It has to
*                                               be removed before.)
*      - #EAaFileSicFtpRet_Timeout              Operation was aborted due to timeout. SICFTP server did
*                                               not respond in time.
*      - #EAaFileSicFtpRet_NoMemory             Operation was aborted due to lack of temporary memory
*                                               for execution at SICFTP server.
*      - #EAaFileSicFtpRet_FileNotWritable      A conflicting SICFTP operation was ongoing for destination
*                                               file. Additionally it might be that the destination file
*                                               path is wrong on SICFTP server.
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
*      - #EAaFileSicFtpRet_NoTransferInProgress An already ongoing SICFTP-transfer was detected. Perhaps
*                                               the previous transfer was aborted due to timeout.
*      - #EAaFileSicFtpRet_RenameError          Renaming temporary destination file to target destination file
*                                               failed after completed transfer. (Internal call of AaFileRename()
*                                               returned an error.)
*
*   @par Restrictions:
*
*      - Length of the file name cannot exceed #AAFILE_FILENAME_MAX.
*      - The file path can only include portable characters, defined in AaFile
*        API documentation.
*
*   @par Example:
*
*   @code
*
*    TAaSysComNid remoteNode = 0x1011;
*    char* srcFilePath = "/ram/myfile.txt"
*    char* destFilePath = "/ram/yourfile.txt"
*    EAaFileSicFtpRet retval = EAaFileRet_LocalError;
*
*    if ( EAaFileSicFtpRet_Ok != (retval = AaFileSicFtpPut(remoteNode, srcFilePath, destFilePath)) ) {
*        switch (retval) {
*        case EAaFileSicFtpRet_Timeout :
*            printf("Timeout of remote node"); break;
*        case EAaFileSicFtpRet_AccessViolation :
*            printf("Could not access file on local and/or remote side due to wrong permissions"); break;
*        case EAaFileSicFtpRet_FileNotFound :
*            printf("Source file not found"); break;
*        case EAaFileSicFtpRet_NoMemory :
*            printf("Memory allocation failed"); break;
*        case EAaFileSicFtpRet_MessageFailure :
*            printf("SIC-messaging failure"); break;
*        case EAaFileSicFtpRet_ReadError :
*            printf("Cannot write destination file; write error"); break;
*        case EAaFileSicFtpRet_FileNotWritable :
*            printf("Ongoing SICFTP-transfer. Retry later."); break;
*        case EAaFileSicFtpRet_FileAlreadyExists :
*            printf("Destination file already exists"); break;
*        case EAaFileSicFtpRet_NoTransferInProgress :
*            printf("Ongoing SICFTP-transfer requeste, but not found. Perhaps timeout achieved."); break;
*        case EAaFileSicFtpRet_SeekError :
*            printf("Seek error, perhaps offset wrong"); break;
*        case EAaFileSicFtpRet_WriteError :
*            printf("Cannot write destination file; write error"); break;
*        case EAaFileSicFtpRet_RenameError :
*            printf("Cannot rename temporary file to destination file"); break;
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
EAaFileSicFtpRet AaFileSicFtpPut( TAaSysComNid remoteNode, const char* srcFilePath, const char* destFilePath);

/**
******************************************************************************
*
*   @brief    Transfer remote file-data to local node
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
*   local node's storage area. The status and contents of the file at
*   the server site shall be unaffected.
*
*   @note Timeout:
*   A timeout value will be given per default to indicate the time the server will
*   wait for the client to send SIC-messages or the client will wait for the server to send
*   SIC-messages. Server timeout value is set in config tag ccs.service.aafile.sicftp.server.timeout
*   and client timeout value is set in config tag ccs.service.aafile.sicftp.client.timeout.
*
*   @note Blocking:
*   This function will block until either the file was successfully received from the
*   remote side or the timeout will be achieved. If you want to receive more than
*   one file from the remote side in parallel you have to launch separate threads
*   (EUs) for this purpose.
*
*   @par Errors:
*      - #EAaFileSicFtpRet_Ok                AaFileSicFtpGet() has succeeded
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
*   @par Example:
*
*   @code
*
*    TAaSysComNid remoteNode = 0x1011;
*    char* srcFilePath = "/ram/yourfile.txt"
*    char* destFilePath = "/ram/myfile.txt"
*    EAaFileSicFtpRet retval = EAaFileRet_LocalError;
*
*    if ( EAaFileSicFtpRet_Ok != (retval = AaFileSicFtpGet(remoteNode, srcFilePath, destFilePath)) ) {
*        switch (retval) {
*        case EAaFileSicFtpRet_Timeout :
*            printf("Timeout of remote node"); break;
*        case EAaFileSicFtpRet_AccessViolation :
*            printf("Could not access file on local and/or remote side due to wrong permissions"); break;
*        case EAaFileSicFtpRet_FileAlreadyExists :
*            printf("Destination file already exists"); break;
*        case EAaFileSicFtpRet_FileNotFound :
*            printf("Source file not found"); break;
*        case EAaFileSicFtpRet_MessageFailure :
*            printf("SIC-messaging failure"); break;
*        case EAaFileSicFtpRet_WriteError :
*            printf("Cannot write destination file; write error"); break;
*        case EAaFileSicFtpRet_RenameError :
*            printf("Cannot rename temporary file to destination file"); break;
*        case EAaFileSicFtpRet_FileNotReadable :
*            printf("Ongoing write-SICFTP-transfer. Retry later."); break;
*        case EAaFileSicFtpRet_NoMemory :
*            printf("Memory allocation failed"); break;
*        case EAaFileSicFtpRet_SeekError :
*            printf("Seek error, perhaps offset wrong"); break;
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
EAaFileSicFtpRet AaFileSicFtpGet( TAaSysComNid remoteNode, const char* srcFilePath, const char* destFilePath);

/**
******************************************************************************
*
*   @brief    Execute a remote file copying
*
*   @param[in]  remoteNode   Node-Id of remote node
*   @param[in]  srcFilePath  Pointer to string that contains the source filepath on remote node
*   @param[in]  destFilePath Pointer to string that contains the destination filepath on remote node
*
*   @return     #EAaFileSicFtpRet_Ok on success, specific error value otherwise (see below)
*
*   @par Description:
*   This command causes the SICFTP server to execute a file copy on the server's storage
*   area. Specified source and destination pathname both are related to the remote (server's)
*   storage area.
*
*   @note Timeout:
*   A timeout value will be given per default to indicate the time the server is expected
*   to perform the file copy.
*   (Currently the time is hardcoded set to 3 min., but will be made configurable in the future.)
*
*   @note Blocking:
*   This function will block until either the file was successfully copied on server side or
*   the timeout elapsed. If you want to do several SICFTP actions in parallel, you have to
*   launch separate threads (EUs) for this purpose.
*
*   @par Errors:
*      - #EAaFileSicFtpRet_Ok                        AaFileSicFtpCopy() has succeeded.
*      - #EAaFileSicFtpRet_FileCopyError             File copying failed at SICFTP server.
*      - #EAaFileSicFtpRet_CopyError_NonPortableFile Source file has non-portable characters.
*      - #EAaFileSicFtpRet_FileNotFound              Source or destination file path was NULL or empty.
*      - #EAaFileSicFtpRet_FileNotReadable           A conflicting SICFTP operation was ongoing for source file.
*      - #EAaFileSicFtpRet_FileNotWritable           A conflicting SICFTP operation was ongoing for destination
*                                                    file.
*      - #EAaFileSicFtpRet_AddressFailure            SIC-messaging registration failed.
*      - #EAaFileSicFtpRet_MessageFailure            SIC-messaging failure. Either the SIC-message couldn't
*                                                    be created, waiting for response failed before timeout
*                                                    or the payload or response couldn't be extracted.
*      - #EAaFileSicFtpRet_Timeout                   Operation was aborted due to timeout. SICFTP server
*                                                    did not respond in time.
*      - #EAaFileSicFtpRet_NoMemory                  Operation was aborted due to lack of temporary memory
*                                                    for execution at SICFTP server.
*
*   @par Restrictions:
*
*      - Length of source and destination file name cannot exceed #AAFILE_FILENAME_MAX
*      - Source and destination file path has to include portable characters only.
*        (For the set of allowed characters see AaFile API documentation.)
*
*   @par Example:
*
*   @code
*
*       TAaSysComNid remoteNode = 0x1011;
*       char* srcFilePath = "/ram/fileA.txt"; // remote source
*       char* destFilePath = "/ram/fileB.txt"; // remote destination
*
*       if ( AaFileSicFtpRet_Ok != AaFileSicFtpCopy(remoteNode, srcFilePath, destFilePath) ) {
*           // handle error
*           ...
*       }
*       ...
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
******************************************************************************/
EAaFileSicFtpRet AaFileSicFtpCopy( TAaSysComNid remoteNode, const char* srcFilePath, const char* destFilePath);

/**
******************************************************************************
*
*   @brief    Execute a remote directory creation
*
*   @param[in]  remoteNode   Node-Id of remote node
*   @param[in]  dirPath      Pointer to string that contains the directory name on remote node
*
*   @return     #EAaFileSicFtpRet_Ok on success, specific error value otherwise (see below)
*
*   @par Description:
*   This command causes the SICFTP server to execute a directory creation on the server's storage
*   area. Specified directory pathname is related to the remote (server's) storage area.
*
*   @note Timeout:
*   A timeout value will be given per default to indicate the time the server is expected
*   to perform the directory creation.
*
*   @note Blocking:
*   This function will block until directory was created on server side or a timeout elapsed.
*   If you want to do several SICFTP actions in parallel, you have to launch separate threads (EUs)
*   for this purpose.
*
*   @par Errors:
*      - #EAaFileSicFtpRet_Ok             AaFileSicFtpCreateDir() has succeeded.
*      - #EAaFileSicFtpRet_DirNotFound    Path for new directory is not valid (e.g. non-existing base
*                                         directory or volume).
*      - #EAaFileSicFtpRet_DirNotWritable A conflicting SICFTP operation was ongoing for directory.
*      - #EAaFileSicFtpRet_DirNotReadable Directory creation failed.
*      - #EAaFileSicFtpRet_AddressFailure SIC-messaging registration failed.
*      - #EAaFileSicFtpRet_MessageFailure SIC-messaging failure. Either the SIC-message couldn't
*                                         be created, waiting for response failed before timeout
*                                         or the payload or response couldn't be extracted.
*      - #EAaFileSicFtpRet_Timeout        Operation was aborted due to timeout. SICFTP server
*                                         did not respond in time.
*
*   @par Restrictions:
*
*      - Length of directory name cannot exceed #AAFILE_FILENAME_MAX
*      - Directoy path has to include portable characters only.
*        (For the set of allowed characters see AaFile API documentation.)
*
*   @par Example:
*
*   @code
*
*       TAaSysComNid remoteNode = 0x1011;
*       char* dirPath = "/ram/myDir"; // remote directory
*
*       if ( AaFileSicFtpRet_Ok != AaFileSicFtpCreateDir(remoteNode, dirPath) ) {
*           // handle error
*           ...
*       }
*       ...
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
******************************************************************************/
EAaFileSicFtpRet AaFileSicFtpCreateDir( TAaSysComNid remoteNode, const char* dirPath);

/**
******************************************************************************
*
*   @brief    Execute a remote directory removal. The removal will
*             be recursive (also contained directories are removed)
*             and forced (even directories still containing files
*             are removed).
*
*   @param[in]  remoteNode Node-Id of remote node
*   @param[in]  dirPath    Pointer to string that contains the directory path on remote node
*
*   @return     #EAaFileSicFtpRet_Ok on success, specific error value otherwise (see below)
*
*   @par Description:
*   This command causes the SICFTP server to execute a directory removal on the server's storage
*   area. Specified pathname is related to a a remote (server's) storage directory.
*
*   @note Symbolic Links:
*   Symbolic links are implicitly removed. (If a symbolic link is contained in the directory, it will
*   be implicitly removed as well.)
*
*   @note Non-portable Files:
*   Files with non-portable file names are implicitly removed. (If a file with a non-portable file name
*   is contained in the directory, it will be implicitly removed as well.)
*
*   @note Timeout:
*   A timeout value will be given per default to indicate the time the server
*   is expected to perform the directory removal.
*
*   @note Blocking:
*   This function will block until either the directory was successfully removed on server side
*   or the timout elapsed. If you want to do several SICFTP actions in paralles, you have to
*   launch separate threads (EUs) for this purpose.
*
*   @par Errors:
*      - #EAaFileSicFtpRet_Ok             AaFileSicFtpRemoveDir() has succeeded.
*      - #EAaFileSicFtpRet_FileNotFound   Directory path was NULL or empty.
*      - #EAaFileSicFtpRet_DirNotFound    Directory was not existing at SICFTP server.
*      - #EAaFileSicFtpRet_DirNotWritable A conflicting SICFTP operation was ongoing for directory.
*      - #EAaFileSicFtpRet_DirNotReadable Directory removal failed on SICFTP server. (Internal call
*                                         of AaFileRemoveDir() returned an error.)
*      - #EAaFileSicFtpRet_AddressFailure SIC-messaging registration failed.
*      - #EAaFileSicFtpRet_MessageFailure SIC-messaging failure. Either the SIC-message couldn't
*                                         be created, waiting for response failed before timeout
*                                         or the payload or response couldn't be extracted.
*      - #EAaFileSicFtpRet_Timeout        Operation was aborted due to timeout. SICFTP server
*
*   @par Restrictions:
*
*      - Length of directory name cannot exceed #AAFILE_FILENAME_MAX
*      - Directory path has to include portable characters only.
*        (For the set of allowed characters see AaFile API documentation.)
*
*   @par Example:
*
*   @code
*
*       TAaSysComNid remoteNode = 0x1011;
*       char dirPath = "/ram/dirA"; // remote directory
*
*       if ( AaFileSicFtpRet_Ok != AaFileSicFtpRemoveDir(remoteNode, dirPath) ) {
*           // handle error
*           ...
*       }
*       ...
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
******************************************************************************/
EAaFileSicFtpRet AaFileSicFtpRemoveDir( TAaSysComNid remoteNode, const char* dirPath);

/**
******************************************************************************
*
*   @brief    Execute a remote directory copying. Copying will be
*             recursive (all contained subdirectories are copied as well).
*
*   @param[in]  remoteNode  Node-Id of remote node
*   @param[in]  srcDirPath  Pointer to string that contains the source directory on remote node
*   @param[in]  destDirPath Pointer to string that contains the destination directory on remote node
*
*   @return     #EAaFileSicFtpRet_Ok on success, specific error value otherwise (see below)
*
*   @par Description:
*   This command causes the SICFTP server to execute a directory copy on the server's storage
*   area. Specified source and destination pathname both are related to the remote (server's)
*   storage area.
*
*   @note Symbolic Links:
*   Symbolic links are ignored. (If a symbolic link is contained anywhere under the source directory,
*   it will not be copied.)
*
*   @note Non-portable Files:
*   If the source directory contains files with non-portable file names, then directory copy is not stopped,
*   the files with illegal names (in context of AaFile path notation) are ignored and not copied.
*   For each skipped file a warning will be logged and AaFileSicFtpCopyDir() returns error code
*   #EAaFileSicFtpRet_CopyError_NonPortableFile (see below).
*
*   @note Timeout:
*   A timeout value will be given per default to indicate the time the server is expected
*   to perform the directory copy.
*   (Currently the time is hardcoded set to 20 min., but will be made configurable in the future.)
*
*   @note Blocking:
*   This function will block until either the directory was successfully copied on server side or
*   the timeout elapsed. If you want to do several SICFTP actions in parallel, you have to
*   launch separate threads (EUs) for this purpose.
*
*   @par Errors:
*      - #EAaFileSicFtpRet_Ok                        AaFileSicFtpCopyDir() has succeeded.
*      - #EAaFileSicFtpRet_DirCopyError              Directory copying failed at SICFTP server.
*      - #EAaFileSicFtpRet_CopyError_NonPortableFile Source directory contained files with non-portable characters.
*                                                    Copying was finished, but the files with non-portable names were not
*                                                    copied to destination directory.
*      - #EAaFileSicFtpRet_FileNotFound              Source or destination file path was NULL or empty.
*      - #EAaFileSicFtpRet_DirNotReadable            A conflicting SICFTP operation was ongoing for source directory.
*      - #EAaFileSicFtpRet_DirNotWritable            A conflicting SICFTP operation was ongoing for destaination
*                                                    directory.
*      - #EAaFileSicFtpRet_AddressFailure            SIC-messaging registration failed.
*      - #EAaFileSicFtpRet_MessageFailure            SIC-messaging failure. Either the SIC-message couldn't
*                                                    be created, waiting for response failed before timeout
*                                                    or the payload or response couldn't be extracted.
*      - #EAaFileSicFtpRet_Timeout                   Operation was aborted due to timeout. SICFTP server
*                                                    did not respond in time.
*      - #EAaFileSicFtpRet_NoMemory                  Operation was aborted due to lack of temporary memory
*                                                    for execution at SICFTP server.
*
*   @par Restrictions:
*
*      - Length of source and destination directory name cannod exceed #AAFILE_FILENAME_MAX
*      - Source and destination directory path has to include portable characters only.
*        (For the set of allowed characters see AaFile API documentation.)
*
*   @par Example:
*
*   @code
*
*       TAaSysComNid remoteNode = 0x1011;
*       char* srcDirPath = "/ram/dirA"; // remote source directory
*       char* destDirPath = "/ram/dirB"; // remote destination directory
*
*       if ( AaFileSicFtpRet_Ok != AaFileSicFtpCopyDir(remoteNode, srcDirPath, destDirPath) ) {
*           // handle error
*           ...
*       }
*       ...
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
******************************************************************************/
EAaFileSicFtpRet AaFileSicFtpCopyDir( TAaSysComNid remoteNode, const char* srcDirPath, const char* destDirPath);

/**
******************************************************************************
*
*   @brief    Get a flat (non-recursive) listing of items in destination directory
*             on remoteNode.
*
*   @param[in]  remoteNode   Node-Id of remote (destination) node
*
*   @param[in]  path         Pointer to string that contains the remote directory path
*                            to be listed
*
*   @param[in,out] fileList  Pointer to #TAaFileListing-struct. AaFileSicFtpList
*                            will allocate all neccessary buffer-space to hold
*                            the listing (see 'files' part of #TAaFileListing)
*
*   @return     #EAaFileSicFtpRet_Ok on success, specific error code otherwise (see below)
*
*   @par Description:
*
*   This function sends a list request message from client side to SICFTP server.
*   The pathname specifies a directory or volume path and the SICFTP server should
*   transfer a list of items contained in the specified volume or directory.
*   The resulting listing will be flat, this means: only the contained items of
*   specified directory are listed. The pathes of listed items are relative.
*   Directory items in the listing are marked with trailing slashes ('/').
*
*   @note Symbolic Links:
*   Symbolic links are ignored. (If a symbolic link is contained in the directory, it will
*   not be listed in fileList.)
*
*   @note Non-portable Files:
*   If the listed directory contains files with non-portable file names, then these files are ignored.
*   (If a file with a non-portable file name is contained somewhere, it will not be listed in fileList.)
*
*   @note Ownership
*   The API-function will allocate adequate memory space for all listing elements.
*   Ownership is passed to the caller of the function, who has to free the space after
*   processing.
*
*   @note Timeout:
*   A timeout value will be given per default to indicate the time the server will
*   wait for the client to send next request message or the client will wait for
*   SICFTP server's response message on it.
*   Server timeout value is set in config tag ccs.service.aafile.sicftp.server.timeout
*   and client timeout value is set in config tag ccs.service.aafile.sicftp.client.timeout.
*
*   @note Blocking:
*   This function will block until the list was either successfully received from the
*   remote side or the timeout will elapse. If you want to receive more than
*   one list from the remote side in parallel, you have to launch separate threads
*   (EUs) for this purpose.
*
*   @note Freeing:
*   Reference argument fileList is allocated and filled by calling this function.
*   The caller has to free this buffer afterwards.
*   In case of errors there might be no memory allocated, therefore null pointer checks
*   have to be done by the user.
*
*   @par Errors:
*      - #EAaFileSicFtpRet_Ok             AaFileSicFtpList() has succeeded.
*      - #EAaFileSicFtpRet_FileNotFound   The directory path was NULL or empty.
*      - #EAaFileSicFtpRet_DirNotFound    Directory was not found on SICFTP server.
*      - #EAaFileSicFtpRet_DirNotReadable A conflicting SICFTP operation was ongoing for directory.
*      - #EAaFileSicFtpRet_DirNotWritable Listing failed.
*      - #EAaFileSicFtpRet_AddressFailure SIC-messaging registration failed.
*      - #EAaFileSicFtpRet_MessageFailure SIC-messaging failure. Either the SIC-message couldn't
*                                         be created, waiting for response failed before timeout
*                                         or the payload or response couldn't be extracted.
*      - #EAaFileSicFtpRet_Timeout        Operation was aborted due to timeout. SICFTP server
*                                         did not respond in time.
*      - #EAaFileSicFtpRet_OutOfRange     Offset error in listing response message of SICFTP server.
*      - #EAaFileSicFtpRet_NoMemory       Operation was aborted due to lack of temporary memory
*                                         for execution at SICFTP server or at client side.
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*   TAaSysComNid remoteNode = 0x1011;
*   TAaFileListing fileList;
*   char* destVolumeName = "/ram";
*   EAaFileSicFtpRet retval;
*
*   if (EAaFileSicFtpRet_Ok != (retval = AaFileSicFtpList(remoteNode, destVolumeName, &fileList)) ) {
*       switch (retval) {
*       case EAaFileSicFtpRet_Timeout :
*           printf("Timeout of remote node"); break;
*       case EAaFileSicFtpRet_MessageFailure :
*           printf("SIC-messaging failure"); break;
*       case EAaFileSicFtpRet_AccessViolation :
*           printf("Could not access volume on remote side due to wrong permissions"); break;
*       case EAaFileSicFtpRet_OutOfRange :
*           printf("Offset wrong"); break;
*       case EAaFileSicFtpRet_NoMemory :
*           printf("Memory allocation failed"); break;
*       case EAaFileSicFtpRet_FileNotFound :
*           printf("Source file not found"); break;
*   }
*
*   int i = 1;
*   char *last;
*   char *token;
*   char *separator = "\n";
*   if (NULL != (token = strtok_r( fileList.files, separator, &last))) {
*       do {
*           printf("%d. file: '%s' ", i, token);
*           if (NULL == (token = strtok_r( NULL, separator, &last))) {
*               fprintf( stderr, "token not available but number of file-entries not exhausted\n");
*               break;
*           }
*           i++;
*       } while (i <= fileList.entries);
*   }
*
*   AaMemUnRef((void const **)&(fileList.files));  //<== Important due to passed ownership
*   ...
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
******************************************************************************/
EAaFileSicFtpRet AaFileSicFtpList( TAaSysComNid remoteNode, const char* path, TAaFileListing *fileList);

/**
******************************************************************************
*
*   @brief    Get a recursive listing of items in destination directory on
*             remoteNode.
*
*   @param[in]  remoteNode    Node-Id of remote (destination) node
*
*   @param[in]  path          Pointer to string that contains the remote directory path
*                             to be listed recursively
*
*   @param[in,out] fileList   Pointer to #TAaFileListing-struct. AaFileSicFtpListRecursive
*                             will allocate the neccessary buffer-space to hold the
*                             listing (see 'files' part of #TAaFileListing)
*
*   @return     #EAaFileSicFtpRet_Ok on success, specific error code otherwise (see below)
*
*   @par Description:
*
*   This function sends a recursive list request message from client side to SICFTP server.
*   The pathname specifies a directory or volume path and the SICFTP server should
*   transfer a list of items contained in specified volume or directory and all its subdirectories.
*   The pathes of listed items are absolute.
*   Directory items in the listing are marked with trailing slashes ('/').
*
*   @note Symbolic Links:
*   Symbolic links are ignored. (If a symbolic link is contained somewhere, it
*   will not be listed in fileList.)
*
*   @note Non-portable Files:
*   If the listed directory contains files with non-portable file names, then these files are ignored.
*   (If a file with a non-portable file name is contained somewhere, it will not be listed in fileList.)
*
*   @note Ownership
*   The API function will allocate adequate memory space for all listing elements.
*   Ownership is passed to the caller of the function, who has to free the space after processing.
*
*   @note Timeout:
*   A timeout value will be given per default to indicate the time the server will
*   wait for the client to send next request message or the client will wait for
*   SICFTP server's response message on it.
*   Server timeout value is set in config tag ccs.service.aafile.sicftp.server.timeout
*   and client timeout value is set in config tag ccs.service.aafile.sicftp.client.timeout.
*
*   @note Blocking:
*   This function will block until the list was either successfully received from the
*   remote side or the timeout will elapse. If you want to receive more than
*   one list from the remote side in parallel, you have to launch separate threads
*   (EUs) for this purpose.
*
*   @note Freeing:
*   Reference argument fileList is allocated and filled by calling this function.
*   The caller has to free this buffer afterwards.
*   In case of errors ther might be no memory allocated, therefore null pointer checks
*   have to be done by the user.
*
*   @par Errors:
*      - #EAaFileSicFtpRet_Ok             AaFileSicFtpListRecursive() has succeeded.
*      - #EAaFileSicFtpRet_FileNotFound   The directory path was NULL or empty.
*      - #EAaFileSicFtpRet_DirNotFound    Directory was not found on SICFTP server.
*      - #EAaFileSicFtpRet_DirNotReadable A conflicting SICFTP operation was ongoing for directory.
*      - #EAaFileSicFtpRet_DirNotWritable Recursive listing failed.
*      - #EAaFileSicFtpRet_AddressFailure SIC-messaging registration failed.
*      - #EAaFileSicFtpRet_MessageFailure SIC-messaging failure. Either the SIC-message couldn't
*                                         be created, waiting for response failed before timeout
*                                         or the payload or response couldn't be extracted.
*      - #EAaFileSicFtpRet_Timeout        Operation was aborted due to timeout. SICFTP server
*                                         did not respond in time.
*      - #EAaFileSicFtpRet_OutOfRange     Offset error in listing response message of SICFTP server.
*      - #EAaFileSicFtpRet_NoMemory       Operation was aborted due to lack of temporary memory
*                                         for execution at SICFTP server or at client side.
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*   TAaSysComNid remoteNode = 0x1011;
*   TAaFileListing fileList;
*   char* destDir = "/ram/myDir";
*   char* last;
*   char* token;
*   int i;
*
*   if ( EAaFileSicFtpRet_Ok != AaFileSicFtpListRecursive( remoteNode, destDir, &fileList) ) {
*       // Error handling
*   }
*
*   if (GLO_NULL != fileList.files) {
*       for ( i = 1, token = strtok_r(fileList.files, "\n", &last);
*             token;
*             i++, token = strtok_r(NULL, "\n", &last)) {
*           AaSysLogPrint(EAaSysLogSeverityLevel_Info, "%i: %s", i, token);
*       }
*       AaMemUnRef((void const **)&(fileList.files));  //<== Important due to passed ownership
*   }
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
******************************************************************************/
EAaFileSicFtpRet AaFileSicFtpListRecursive( TAaSysComNid remoteNode, const char* path, TAaFileListing *fileList);

/**
******************************************************************************
*
*   @brief    Remove file from remote node
*
*   @param[in]  remoteNode   Node-Id of remote (destination) node
*
*   @param[in]  destFilePath Pointer to string that contains the file to remove
*
*   @return     #EAaFileSicFtpRet_Ok on success, specific error value otherwise (see below)
*
*   @par Description:
*   This command causes the file specified in the pathname to be
*   deleted at the remote node site.
*
*   @note Blocking:
*   This function will block until the remove was either successfully made on the
*   remote side or the timeout will be achieved. If you want to remove more than
*   one file from the remote side in parallel you have to launch separate threads
*   (EUs) for this purpose. Otherwise you have to remove one file after the
*   other.
*
*   @par Errors:
*      - #EAaFileSicFtpRet_Ok              AaFileSicFtpRemove() has succeeded
*      - #EAaFileSicFtpRet_FileNotFound    File was not found on remote node.
*                                          Also file path might have been NULL or empty.
*      - #EAaFileSicFtpRet_FileNotWritable A conflicting SICFTP operation was ongoing for file.
*      - #EAaFileSicFtpRet_WriteError      File removal failed on SICFTP server. (Internal call
*                                          of AaFileRemove() returned an error.)
*      - #EAaFileSicFtpRet_AddressFailure  SIC-messaging registration failed.
*      - #EAaFileSicFtpRet_MessageFailure  SIC-messaging failure. Either the SIC-message couldn't
*                                          be created, waiting for response failed before timeout
*                                          or the payload or response couldn't be extracted.
*      - #EAaFileSicFtpRet_Timeout         Operation was aborted due to timeout. SICFTP server
*
*   @par Restrictions:
*
*      - The file path can only include portable characters, defined in AaFile
*        API documentation.
*
*   @par Example:
*
*   @code
*
*    TAaSysComNid remoteNode = 0x1011;
*    char* destFilePath = "/ram/yourfile.txt"
*    EAaFileSicFtpRet retval = EAaFileRet_LocalError;
*
*    if ( EAaFileSicFtpRet_Ok != (retval
*           = AaFileSicFtpRemove(remoteNode, srcFilePath, destFilePath)) ) {
*        switch (retval) {
*        case EAaFileSicFtpRet_Timeout :
*            printf("Timeout of remote node"); break;
*        case EAaFileSicFtpRet_MessageFailure :
*            printf("SIC-messaging failure"); break;
*        case EAaFileSicFtpRet_FileNotFound :
*            printf("Source file not found"); break;
*        case EAaFileSicFtpRet_FileNotWritable :
*            printf("Ongoing SICFTP-transfer. Retry later."); break;
*        case EAaFileSicFtpRet_WriteError :
*            printf("Cannot remove file; write error"); break;
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
EAaFileSicFtpRet AaFileSicFtpRemove( TAaSysComNid remoteNode, const char* destFilePath);

/**
******************************************************************************
*
*   @brief    Execute a remote item existence check
*
*   @param[in]  remoteNode   Node-Id of remote node
*   @param[in]  path         Pointer to string that contains the path on remote node
*   @param[out] type         If item exists: the type of the item (file or directory)
                             If item does not exist: undefined
*
*   @return     #EAaFileSicFtpRet_Ok if item exists,
*               #EAaFileSicFtpRet_FileNotFound if item does not exist,
                specific error value otherwise (see below)
*
*   @par Description:
*   This command causes the SICFTP server to execute item existence check.
*   Specified item pathname is related to the remote (server's) storage area.
*   In case of existing items the type of the item, which is either file or directory,
*   is referenced.
*
*   @note Timeout:
*   A timeout value will be given per default to indicate the time the server
*   is expected to perform the item existence check.
*
*   @note Blocking:
*   This function will block until the existence check wad done on server side or a timeout elapsed.
*   If you want to do several SICFTP actions in parallel, you have to launch separate threads (EUs)
*   for this purpose.
*
*   @par Errors:
*      - #EAaFileSicFtpRet_Ok             Item with given path exists on remote server.
*      - #EAaFileSicFtpRet_FileNotFound   There is no item with given path on remote server.
*      - #EAaFileSicFtpRet_AddressFailure SIC-messaging registration failed.
*      - #EAaFileSicFtpRet_MessageFailure SIC-messaging failure. Either the SIC-message couldn't
*                                         be created, waiting for response failed before timeout
*                                         or the payload or response couldn't be extracted.
*      - #EAaFileSicFtpRet_Timeout        Operation was aborted due to timeout. SICFTP server
*                                         did not respond in time.
*
*   @par Restrictions:
*
*      - Length of itme path cannot exceed #AAFILE_FILENAME_MAX
*      - Item path has to include portable characters only.
*        (For the set of allowed characters see AaFile API documentation.)
*
*   @par Example:
*
*   @code
*
*       TAaSysComNid remoteNode = 0x1011;
*       EAaFileSicFtpItemType itemType = EAaFileSicFtpItemType_Undefined;
*       char* remotePath = "/ram/myDir"; // remote directory
*
*       if ( AaFileSicFtpRet_Ok != (rc = AaFileSicFtpExists(remoteNode, remotePath, &itemType)) ) {
*           // item does not exist or error
*           if ( EAaFileSicFtpItemType_FileNotFound == rc ) {
*               ...
*           } else {
*               // handle error
*               ...
*           }
*           ...
*       } else {
*           if ( EAaFileSicFtpItemType_Dir == itemType) {
*               // handle directory
*               ...
*           } else if ( EAaFileSicFtpItemType_File == itemType) {
*               // handle file
*               ...
*           } else {
*               // handle error
*               ...
*           }
*       }
*       ...
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
******************************************************************************/
EAaFileSicFtpRet AaFileSicFtpExists( TAaSysComNid remoteNode, const char* path, EAaFileSicFtpItemType* type);

/**
******************************************************************************
*
*   @brief    Initialize task for SICFTP server
*
*   @return     -1 on error, 0 otherwise
*
*   @par Description:
*   Calling this function will instantiate a SICFTP server-EE/EU running indefinitely.
*   Only in case of error the forver-loop will return.
*
*   @par Errors:
*
*   If the server could either not be created or crashes during operation,
*   -1 will be returned.
*
*   @par Restrictions:
*
*   @par Example:
*
*   None
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
int AaFileSicFtpInit(void);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _COMMON_IF_AAFILESICFTP_H_ */
