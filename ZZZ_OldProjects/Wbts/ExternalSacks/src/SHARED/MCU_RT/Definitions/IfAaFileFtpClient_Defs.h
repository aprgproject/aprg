/** @file
*   @brief AaFileFtpClient shared MCU/RT definitions.
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright 2017, 2018 Nokia. All rights reserved.$
*/

#ifndef _MCU_RT_IF_AAFILEFTPCLIENT_DEFS_H_
#define _MCU_RT_IF_AAFILEFTPCLIENT_DEFS_H_

#include <CcsCommon.h>
#include <IfAaSysComGw_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaFileApiMcu
 * @ingroup dgAaFile
 */

/** @{ */

/**
******************************************************************************
* @verbatim
*  Tag name:        ccs.service.aafile.ftpclient.timeout
*
*  Direction:       input
*
*  Description:     Maximum number of seconds FTP client waits for a FTP-server
*                   response.
*
*  Effect analysis: If this tag is not set, a default value for client timeout is used.
*
*  Restriction:     None
*
*  Value:           IE Type:     Size:     Range:
*                   number       u32       >= 1
*
*  Define:          AAFILE_FTP_CLIENT_CONFIG_TAG_TIMEOUT
*
*  See:             None
* @endverbatim
******************************************************************************/
#define AAFILE_FTP_CLIENT_CONFIG_TAG_TIMEOUT "ccs.service.aafile.ftpclient.timeout"

/**
******************************************************************************
* @verbatim
*  Tag name:        ccs.service.aafile.ftpclient.server.port
*
*  Direction:       input
*
*  Description:     Number of port that should be used to access FTP-server
*                   Default-value is 21 for ftp-service
*
*  Effect analysis: If this tag is not set, the default value for ftp-server-port
*
*  Restriction:     None
*
*  Value:           IE Type:     Size:     Range:
*                   number       u32       >= 1
*
*  Define:          AAFILE_FTP_CONFIG_TAG_SERVER_PORT
*
*  See:             None
* @endverbatim
******************************************************************************/
#define AAFILE_FTP_CLIENT_CONFIG_TAG_SERVER_PORT "ccs.service.aafile.ftpclient.server.port"

/**
 * @brief Maximum number of parallel FTP-sessions
 * @note The FtpClient-implementation will handle up to this number of
 * open CURL-sessions in parallel. This does not mean that under all circum-
 * stances this amount of sessions is allowed, possible, or feasible. It
 * heavily depends on your personal environment.
 */
#define AAFILE_FTP_CLIENT_MAX_SESSIONS 100

/**
 * @brief Default for server response time: 2 min
 * @see AAFILE_FTP_CLIENT_CONFIG_TAG_TIMEOUT config-tag
 */
#define AAFILE_FTP_CLIENT_TIMEOUT_DEFAULT 120

/**
 * @brief Standard ftp port used as default
 * @see AAFILE_FTP_CLIENT_CONFIG_TAG_SERVER_PORT config-tag
 */
#define AAFILE_FTP_CLIENT_SERVER_PORT_DEFAULT 21

/**
 * @brief Begin number scheme of FTP-client return codes
 * @see #EAaFileFtpClientRet enumerator
 */
#define AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN 0

/**
 * @brief Maximum size of server-URL
 * The URL of the FTP-server will be a concatenated value of the server IP address
 * and the path to the dedicated file (either for writing or reading).
 * If for example the IP address would be 192.168.255.1 and
 * the file-path would be 'mydirectory/myfile.txt' then the resulting URL
 * will be "ftp://192.168.255.1/mydirectory/myfile.txt"
 * Be aware that if the file path contains a hashmark ('#'), then it has to be
 * replaced by string "%23" in the url. (This is done in AaFileFtpClientGet() and
 * AaFileFtpClientPut() implicitly.)
 *
 * @note
 * The given URL will address a file-path beneath the FTP-user's home-directory!
 * Using an URL like "ftp://192.168.255.1/mydirectory/myfile.txt"
 * by user "joe" will result into access to a real file-path on the FTP-server-side:
 * "/home/joe/mydirectory/myfile.txt" or whatelse the FTP-server will use as home-directory
 * for each user
 */
#define AAFILE_FTP_CLIENT_URL_LEN 255

/**
 * @brief Overall string length of given user-name and user-password.
 * @note Keep that in mind for your user-management.
 */
#define AAFILE_FTP_CLIENT_USERPWD_LEN 128

/** @brief AaFileFtpClientTransferMode */
typedef enum EAaFileFtpClientTransferMode {
    EAaFileFtpClientTransferModePassive,    /**< Requested transfer will be made using extended passive mode (EPSV) */
    EAaFileFtpClientTransferModeActive      /**< Requested transfer will be made using active mode (PORT) */
} EAaFileFtpClientTransferMode;

/** @brief AaFileFtpClientTransferType */
typedef enum EAaFileFtpClientTransferType {
    EAaFileFtpClientTransferTypeBinary,     /**< Requested transfer will be made using FTP's BINARY-type */
    EAaFileFtpClientTransferTypeAscii       /**< Requested transfer will be made using FTP's ASCII-type */
} EAaFileFtpClientTransferType;

/** @brief AaFileFtpClient return values */
typedef enum EAaFileFtpClientRet {
    EAaFileFtpClientRet_Ok                  = AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN,             /**< No error */

    EAaFileFtpClientRet_InitError           = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 1),      /**< FTP client has not been initialized */
    EAaFileFtpClientRet_AlreadyOpen         = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 2),      /**< FTP client was already opened, must be closed first */
    EAaFileFtpClientRet_CurlInitError       = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 3),      /**< curl initialization failed */
    EAaFileFtpClientRet_CurlPerformError    = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 4),      /**< curl perform failed */
    EAaFileFtpClientRet_ServerNotGiven      = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 5),      /**< The server address given is invalid */
    EAaFileFtpClientRet_NoAnonymousAccess   = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 6),      /**< No anonymous access available */
    EAaFileFtpClientRet_Timeout             = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 7),      /**< Timeout */
    EAaFileFtpClientRet_FileAlreadyExists   = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 8),      /**< Destination file exists and must first be removed */
    EAaFileFtpClientRet_FileNotFound        = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 9),      /**< File could not be found */
    EAaFileFtpClientRet_AddressTooLong      = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 10),     /**< Given address too long */
    EAaFileFtpClientRet_CurlError           = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 11),     /**< CURL-library error */
    EAaFileFtpClientRet_FileOpenError       = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 12),     /**< Cannot open file */
    EAaFileFtpClientRet_MaxNumOfFtpSessions = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 13),     /**< Maximum number of FTP sessions achieved */
    EAaFileFtpClientRet_InvalidSession      = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 14),     /**< Invalid session id given */
    EAaFileFtpClientRet_UserPwdLenTooLong   = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 15),     /**< Length of concatenated username and password exceeds internal buffer size */
    EAaFileFtpClientRet_InvalidPath         = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 16),     /**< Given path name for current directory is wrong, most probably a not allowed relative path was given */
    EAaFileFtpClientRet_PathTooLong         = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 17),     /**< Given path name for current directory exceeds internal buffer size */
    EAaFileFtpClientRet_InvalidPointer      = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 18),     /**< Invalid pointer given */
    EAaFileFtpClientRet_InvalidTransferMode = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 19),     /**< Invalid transfer mode given */
    EAaFileFtpClientRet_InvalidNode         = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 20),     /**< Invalid node ID */
    EAaFileFtpClientRet_InvalidPort         = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 21),     /**< Invalid port */
    EAaFileFtpClientRet_InvalidClientOpt    = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 22),     /**< Invalid client options */

    EAaFileFtpClientRet_UndefinedError      = -(AAFILE_FTP_CLIENT_RETURN_VALUE_BEGIN + 99),     /**< Undefined error, should not happen. Regularly a meaningful return code should be available. */

    EaFileFtpClientRet_End
} EAaFileFtpClientRet;

/** @brief AaFileFtpClient session ID */
typedef int TAaFileFtpClientSessionId;

/** @brief
 *  Additional options that can be set on an already opened FTP session.
 *  The names in brackets are the corresponding curl library options.
 */
typedef enum EAaFileFtpClientOpt {
    EAaFileFtpClientOpt_SourceIP = 0x1, /**< change source IP address for outgoing traffic (CURLOPT_INTERFACE) */
    EAaFileFtpClientOpt_End
} EAaFileFtpClientOpt;

/** @brief Values for AaFileFtpClientSetOpts */
typedef struct SAaFileFtpClientOpt {
    char sourceIP[AASYSCOM_GW_IP_ADDRESS_MAX_STR_LEN];  /**< Source IP address, can be either IPv4 or IPv6. */
} SAaFileFtpClientOpt;

/** @brief AaFileFtpSession types */
typedef enum EAaFileFtpClientSessionType {
    EAaFileFtpClientSessionType_Local   = 0,    /**< FTP client session established on own nid. */
    EAaFileFtpClientSessionType_Remote  = 1,    /**< FTP client session established on remote nid. */
    EAaFileFtpClientSessionType_End
} EAaFileFtpClientSessionType;

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _MCU_RT_IF_AAFILEFTPCLIENT_DEFS_H_ */
