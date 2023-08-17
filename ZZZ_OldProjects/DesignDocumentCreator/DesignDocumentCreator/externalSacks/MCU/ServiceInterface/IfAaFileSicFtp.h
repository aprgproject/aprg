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

#ifndef _MCU_IF_AAFILESICFTP_H_
#define _MCU_IF_AAFILESICFTP_H_

#include "CcsCommon.h"

#ifdef CCS_NEW_IF_STRUCTURE
#include <../../COMMON/ServiceInterface/IfAaFileSicFtp.h>
#include <../../SHARED/MCU_RT/ServiceInterface/IfAaFileSicFtp.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaFileApiMcu
 * @ingroup    dgAaFile
 */

/** @{ */

/**
******************************************************************************
*
*   @brief    Execute a remote item size check
*
*   @param[in]  remoteNode   Remote node ID
*   @param[in]  path         Pointer to string that contains remote node path
*   @param[out] size         Size of the item in bytes.
*
*   @return     #EAaFileSicFtpRet_Ok on success, specific error value otherwise (see below)
*
*   @par Description:
*   Function to check item size via SICFTP interface.
*   Specified item pathname is related to the remote (server's) storage area.
*   In case of non-existing items -1 is assigned to 'size' param, otherwise the size of the item
*   which is either file or directory being referenced.
*
*   @note Timeout:
*   A timeout value will be given per default to indicate the time the server
*   is expected to perform the item size check.
*
*   @note Blocking:
*   This function will block until the size check was done on server side or a timeout elapsed.
*   If you want to do several SICFTP actions in parallel, you have to launch separate threads (EUs)
*   for this purpose.
*
*   @par Errors:
*      - #EAaFileSicFtpRet_Ok              Item with given path exists on remote server.
*      - #EAaFileSicFtpRet_FileNotFound    There is no file with given path on remote server.
*      - #EAaFileSicFtpRet_DirNotFound     There is no directory with given path on remote server.
*      - #EAaFileSicFtpRet_AddressFailure  SIC-messaging registration failed.
*      - #EAaFileSicFtpRet_MessageFailure  SIC-messaging failure. Either the SIC-message couldn't
*                                          be created, waiting for response failed before timeout
*                                          or the payload or response couldn't be extracted.
*      - #EAaFileSicFtpRet_StatError            Failure in calling stat-function on remote server.
*      - #EAaFileSicFtpRet_WrongInputParameter  One or more input parameters are incorrect
*      - #EAaFileSicFtpRet_AccessViolation      Wrong permission on remote node
*      - #EAaFileSicFtpRet_Timeout              Operation was aborted due to timeout. SICFTP server
*                                               did not respond in time.
*
*   @par Restrictions:
*       - Length of item path cannot exceed #AAFILE_FILENAME_MAX
*       - Function allows to check only MCU items size
*
*   @par Example:
*
*   @code
*
*       TAaSysComNid remoteNode = 0x1011;
*       char* remotePath = "/ram/myDir"; // remote directory
*       long itemSize = -1;
*
*       if ( AaFileSicFtpRet_Ok != (rc = AaFileSicFtpGetSize(remoteNode, remotePath, &itemSize)) ) {
*
*           // handle error
*           ...
*       }
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   RAN2657
*
*   @par Future directions:
*
*   None
*
******************************************************************************/
EAaFileSicFtpRet AaFileSicFtpGetSize( TAaSysComNid remoteNode, const char* path, long* size );

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _MCU_IF_AAFILESICFTP_H_ */
