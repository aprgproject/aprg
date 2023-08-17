/** @file
*   @brief AaFile Remote Ftp Client function prototypes.
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright 2016, 2018 Nokia. All rights reserved.$
*/

#ifndef _MCU_IF_AAFILE_FTP_REMOTE_CLIENT_H_
#define _MCU_IF_AAFILE_FTP_REMOTE_CLIENT_H_

#include <glo_def.h>
#include <CcsCommon.h>
#include <IfAaSysCom_Defs.h>
#include <../../MCU/Definitions/IfAaFileFtpRemoteClient_Defs.h>

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
*   @brief Establish FTP connection on a remote node using explicitly given server port.
*
*   @param[out] sessionId Pointer to a session ID returned if connection is established.
*   @param[in]  server    Pointer to a null-terminated string containing the IP address of FTP server.
*   @param[in]  port      The listening port of the FTP server.
*   @param[in]  user      Pointer to a null-terminated string containing user name for FTP server.
*   @param[in]  password  Pointer to a null-terminated string containing password for FTP server.
*   @param[in]  mode      Specifies active or passive transfer mode for FTP session.
*   @param[in]  nid       Node ID of the node where FTP client proxy resides.
*
*   @return     #EAaFileFtpClientRet_Ok and #TAaFileFtpClientSessionId on success,
*               appropriate #EAaFileFtpClientRet values on error.
*
*   @par Description:
*   This function causes AaFileFtpClientProxy running on the node specified by \p nid to
*   establish a connection with the desired FTP server on a given \p port using provided login
*   credentials. \p server argument can be either IPv4 or IPv6 address. If \p port is 0 then
*   the listening port of FTP server is read from #AAFILE_FTP_CLIENT_CONFIG_TAG_SERVER_PORT
*   configuration tag. The function returns a session ID that must be used for all further
*   operations on this connection.
*
*   @note
*   - When \p nid is set to own nid, the behavior is equivalent to AaFileFtpClientOpenWithPort().
*   - When \p port is set to 0 and \p nid to own nid, the behavior is equivalent to AaFileFtpClientOpen().
*
*   @par Errors:
*   - #EAaFileFtpClientRet_AlreadyOpen            There is already an existing FTP connection established with this session ID.
*   - #EAaFileFtpClientRet_MaxNumOfFtpSessions    Maximum number of parallel FTP sessions achieved.
*   - #EAaFileFtpClientRet_CurlInitError          Error during initialization of \c curl library.
*   - #EAaFileFtpClientRet_InvalidTransferMode    Given transfer mode is invalid.
*   - #EAaFileFtpClientRet_ServerNotGiven         The FTP server address given is invalid.
*   - #EAaFileFtpClientRet_AddressTooLong         Given URL exceeds internal buffer size.
*   - #EAaFileFtpClientRet_CurlError              \c curl library error, see AaSysLog output for details.
*   - #EAaFileFtpClientRet_NoAnonymousAccess      Anonymous FTP server access is not allowed.
*   - #EAaFileFtpClientRet_UserPwdLenTooLong      Concatenated string length and password length exceeds the size of internal buffer.
*   - #EAaFileFtpClientRet_InvalidPointer         Invalid pointer.
*   - #EAaFileFtpClientRet_InvalidPort            Invalid port.
*
*   @par Restrictions:
*   The length of \p server argument must not exceed #AAFILE_FTP_CLIENT_URL_LEN bytes.
*   IPv6 addresses must not contain zone ID suffix (e.g. \%eth0). In these cases the
*   function will return #EAaFileFtpClientRet_ServerNotGiven.
*   AaFileFtpClientProxy must be active on the node specified by \p nid.
*
*   @par Example:
*   @code
    EAaFileFtpClientRet retval = EAaFileRet_UndefinedError;
    TAaFileFtpClientSessionId sessionId;
    char* ftpserver = "172.16.8.136";
    TAaSysComNid fhnetNid = 0x1018;
    u32 port = 15400;
    char* user = "ftpuser";
    char* password = "ftppassword";

    retval = AaFileFtpRemoteClientOpenWithPort( &sessionId,
                                                ftpserver, port,
                                                user, password,
                                                EAaFileFtpClientTransferModePassive,
                                                fhnetNid );
    if( EAaFileFtpClientRet_Ok != retval ) {
        // handle errors
    }
    ...
    @endcode
*
*   @par Rationale:
*   LTE3266, LTE4537-B-k5
*
*   @see AAFILE_FTP_CLIENT_URL_LEN
*   @see AAFILE_FTP_CLIENT_CONFIG_TAG_SERVER_PORT
*   @see EAaFileFtpClientTransferMode
*   @see AaFileFtpClientOpen()
*   @see AaFileFtpClientSetOpts()
******************************************************************************/
EAaFileFtpClientRet AaFileFtpRemoteClientOpenWithPort( TAaFileFtpClientSessionId* sessionId,
                                                       const char* server,
                                                       u32 port,
                                                       const char* user,
                                                       const char* password,
                                                       EAaFileFtpClientTransferMode mode,
                                                       TAaSysComNid nid );

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* _MCU_IF_AAFILE_FTP_REMOTE_CLIENT_H_ */
