/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/
#ifndef _MCU_IF_AAFILETFTP_H_
#define _MCU_IF_AAFILETFTP_H_
#include "CcsCommon.h"

#ifdef CCS_NEW_IF_STRUCTURE
#include <../../SHARED/MCU_RT/ServiceInterface/IfAaFileTftp.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*------------------- PUBLIC INTERFACES (MCU API) ---------------------------*/

/**
 * @addtogroup dgAaFileApiMcu
 * @ingroup    dgAaFile
 */

/** @{ */

/**
*******************************************************************************
*
*   @brief AaFileTftpGetWithPort() performs TFTP GET from a remote unit.
*
*   @param[in] ipAddress     Target IP address (dotted decimal notation).
*   @param[in] serverPort    Server port.
*   @param[in] srcFileName   Source file name.
*   @param[in] dstFileName   Destination file name.
*
*   @return                  AaFile TFTP return code.
*
*   @par Description:
*   Fetch a file from a remote unit.
*   The function works in the similar way as AaFileTftpGet().
*   Server port number is set via input parameter serverPort,
*   tag AAFILE_TFTP_CONFIG_TAG_CLIENT_PORT is ignored.
*
*   @par Errors:
*   The same as AaFileTftpGet().
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*   #include <IfAaFileTftp.h>
*
*   char* address = "192.168.255.25";
*   char* remoteFileName = "/ram/testfile.txt";
*   char* localFileName = "/ram/temp.txt";
*   u32   serverPort = 12345;
*   EAaFileTftpErrorCode ret = EAaFileTftpErrorCode_NoError;
*
*   // Copy the file from remote unit to different name in this unit:
*   ret = AaFileTftpGetWithPort(address, serverPort, remoteFileName, localFileName);
*   if (ret != EAaFileTftpErrorCode_NoError) {
*      // Error or timeout.
*      ...
*   }
*   ...
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
*   @see AaFileTftpGet()
*   @see AaFileTftpGetExt()
*   @see AaFileTftpGetExt2()
*
*******************************************************************************/
EAaFileTftpErrorCode AaFileTftpGetWithPort(const char* ipAddress,
                                           u32         serverPort,
                                           const char* srcFileName,
                                           const char* dstFileName);

/**
*******************************************************************************
*
*   @brief AaFileTftpGetWithPortExt() performs TFTP GET from a remote unit on
*          a specified port. Function accepts additional arguments for timeout
*          and number of retries.
*
*   @param[in] ipAddress     Target IP address (dotted decimal notation).
*   @param[in] serverPort    Server port.
*   @param[in] srcFileName   Source file name.
*   @param[in] dstFileName   Destination file name.
*   @param[in] timeout       Timeout for sending/receiving one packet in seconds.
*   @param[in] retries       Number of retries made in case of timeout.
*
*   @return                  AaFile TFTP return code.
*
*   @par Description:
*   Fetch a file from a remote unit.
*   The function works in the similar way as AaFileTftpGetExt().
*   Server port number is set via input parameter serverPort,
*   tag AAFILE_TFTP_CONFIG_TAG_CLIENT_PORT is ignored.
*
*   @par Errors:
*   The same as AaFileTftpGetExt().
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*   #include <IfAaFileTftp.h>
*
*   char* address = "192.168.255.25";
*   char* remoteFileName = "/ram/testfile.txt";
*   char* localFileName = "/ram/temp.txt";
*   u32   serverPort = 18731;
*   u32   timeout = 7;
*   u32   retries = 5;
*   EAaFileTftpErrorCode ret = EAaFileTftpErrorCode_NoError;
*
*   // Copy the file from remote unit to different name on this unit:
*   ret = AaFileTftpGetWithPortExt(ipAddress, serverPort, remoteFileName, localFileName, timeout, retries);
*   if (ret != EAaFileTftpErrorCode_NoError) {
*      // Error or timeout.
*      ...
*   }
*   ...
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
*   @see AaFileTftpGetExt()
*   @see AaFileTftpGetWithPort()
*
*******************************************************************************/
EAaFileTftpErrorCode AaFileTftpGetWithPortExt(const char* ipAddress,
                                              const u32   serverPort,
                                              const char* srcFileName,
                                              const char* dstFileName,
                                              const u32   timeout,
                                              const u32   retries);

/** @} */

#ifdef __cplusplus
}
#endif
#endif /* _MCU_IF_AAFILETFTP_H_ */
