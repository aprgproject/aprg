/** @file
*   @brief AaFile Http Client MCU function prototypes.
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright 2017 Nokia. All rights reserved.$
*/

#ifndef _MCU_IF_AAFILEHTTPCLIENT_H_
#define _MCU_IF_AAFILEHTTPCLIENT_H_

#include <CcsCommon.h>
#include <glo_def.h>
#include <../../MCU/Definitions/IfAaFileHttpClient_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaFileApiMcu
 * @ingroup    dgAaFile
 */

/** @{ */

/**
 ********************************************************************************
 * @brief Performs http(s) get from the remote server.
 *
 * @param[in]   serverIp        IP address of the http server, in dotted decimal notation
 * @param[in]   serverPort      listen port of the http server
 * @param[in]   username        http server login
 * @param[in]   password        http server password
 * @param[in]   srcPath         file location on the http server side
 * @param[in]   destPath        destination path on client side
 * @param[in]   securityMode    security mode (plain text or TLS enabled)
 *
 * @returns #EAaFileHttpClientRet_Ok in case of successful transfer, appropriate error otherwise.
 *
 * @par Description
 * This function downloads the file from the http server. If port number is 0, the default port is
 * used (80 for unencrypted, 443 for TLS connections).
 *
 * @par Errors:
 *  - #EAaFileHttpClientRet_ParamError      Invalid parameters (NULL pointers, etc.) were passed to the function.
 *  - #EAaFileHttpClientRet_AccessDenied    Failed to log in to http server using provided credentials.
 *  - #EAaFileHttpClientRet_FileNotFound    File not found on server side.
 *  - #EAaFileHttpClientRet_Timeout         Transfer timeout.
 * TODO More error codes will be added as necessary.
 *
 * @par Restrictions:
 *  - Source file path is relative to the root directory of http server.
 *  - Destination file path is expressed in AaFile path notation.
 *
 * @par Example
 * @code
   // http server is running, and user account is configured appropriately

   EAaFileHttpClientRet result;
   result = AaFileHttpClientGet( "192.168.255.1", 443,
                                 "httpUser", "httpPasswd",
                                 "swpool/OAM/BTSOMexe", "/ram/BTSOMexe",
                                 EAaFileHttpClientSecurityMode_Tls );

   if( EAaFileHttpClientRet_Ok != result ) {
       // handle error
   }
   @endcode
 *
 * @see EAaFileHttpClientSecurityMode
 *
 *******************************************************************************/
EAaFileHttpClientRet AaFileHttpClientGet( const char *serverIp,
                                          u32 serverPort,
                                          const char *username,
                                          const char *password,
                                          const char *srcPath,
                                          const char *destPath,
                                          EAaFileHttpClientSecurityMode securityMode );

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* _MCU_IF_AAFILEHTTPCLIENT_H_ */
