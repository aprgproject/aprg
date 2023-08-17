/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 File Service API / TFTP interface header
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IF_AAFILETFTP_H_
#define _MCU_RT_IF_AAFILETFTP_H_

#include <glo_def.h>
#include <CcsCommon.h>

#include "../Definitions/IfAaFileTftp_Defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @verbatim
*  Tag name:        ccs.service.aafile.tftp.server.putwhitelist
*
*  Direction:       input
*
*  Description:     List of IP-addresses that TFTP server allows to perform
*                   a PUT operation (send a file to the server). The addresses
*                   must be presented using dotted-decimal notation and
*                   separated with spaces. If any of the listed addresses are
*                   replaced with string "any", PUT operation will be allowed
*                   from any address.
*
*  Effect analysis: If the client trying to perform a PUT operation is not found
*                   on this list, TFTP error code 2 "Access violation" described in
*                   RFC 1350 is sent to the client.
*
*  Restriction:     None
*
*  Value:           IE Type:                   Size:             Range:
*                   zero-terminated string     N/A               N/A
*
*  Define:          AAFILE_TFTP_CONFIG_TAG_PUT_WHITELIST
*
*  Example:         const char* ipfilt = "127.0.0.1 192.168.255.5";
*                   AaConfigTagSetString(AAFILE_TFTP_CONFIG_TAG_PUT_WHITELIST, ipfilt);
*
*  Example:         const char* ipfilt = "any";
*                   AaConfigTagSetString(AAFILE_TFTP_CONFIG_TAG_PUT_WHITELIST, ipfilt);
*
*  See:             None
* @endverbatim
*
*
* @verbatim
*  Tag name:        ccs.service.aafile.tftp.server.getwhitelist
*
*  Direction:       input
*
*  Description:     List of IP-addresses that TFTP server allows to perform
*                   a GET operation (receive a file from the server). The addresses
*                   must be presented using dotted-decimal notation and
*                   separated with spaces. If any of the listed addresses are
*                   replaced with string "any", GET operation will be allowed
*                   from any address.
*
*  Effect analysis: If the client trying to perform a GET operation is not found
*                   on this list, TFTP error code 2 "Access violation" described in
*                   RFC 1350 is sent to the client.
*
*  Restriction:     None
*
*  Value:           IE Type:                   Size:             Range:
*                   zero-terminated string     N/A               N/A
*
*  Define:          AAFILE_TFTP_CONFIG_TAG_GET_WHITELIST
*
*  Example:         const char* ipfilt = "127.0.0.1 192.168.255.5";
*                   AaConfigTagSetString(AAFILE_TFTP_CONFIG_TAG_GET_WHITELIST, ipfilt);
*
*  Example:         const char* ipfilt = "any";
*                   AaConfigTagSetString(AAFILE_TFTP_CONFIG_TAG_GET_WHITELIST, ipfilt);
*
*  See:             None
* @endverbatim
*
*
* @verbatim
*  Tag name:        ccs.service.aafile.tftp.client.timeout
*
*  Direction:       input
*
*  Description:     Maximum number of seconds tftp client waits for a packet
*                   during a file transfer.
*
*  Effect analysis: If this tag is not set, a default value for client timeout is used.
*
*  Restriction:     None
*
*  Value:           IE Type:     Size:     Range:
*                   number       u32       >= 1
*
*  Define:          AAFILE_TFTP_CONFIG_TAG_CLIENT_TIMEOUT
*
*  See:             None
* @endverbatim
*
*
* @verbatim
*  Tag name:        ccs.service.aafile.tftp.server.timeout
*
*  Direction:       input
*
*  Description:     Maximum number of seconds tftp server waits for a packet
*                   during a file transfer.
*
*  Effect analysis: If this tag is not set, a default value for server timeout is used.
*
*  Restriction:     None
*
*  Value:           IE Type:     Size:     Range:
*                   number       u32       >= 1
*
*  Define:          AAFILE_TFTP_CONFIG_TAG_SERVER_TIMEOUT
*
*  See:             None
* @endverbatim
*
*
* @verbatim
*  Tag name:        ccs.service.aafile.tftp.client.port
*
*  Direction:       input
*
*  Description:     Port number (on server-side) the client connects to.
*
*  Effect analysis: If this tag is not set, port number 69 is used as default.
*
*  Restriction:     None
*
*  Value:           IE Type:     Size:     Range:
*                   number       u32       1-65535
*
*  Define:          AAFILE_TFTP_CONFIG_TAG_CLIENT_PORT
*
*  See:             None
* @endverbatim
*
*
* @verbatim
*  Tag name:        ccs.service.aafile.tftp.client.blocksize
*
*  Direction:       input
*
*  Description:     Data blocksize.
*
*  Effect analysis: If this tag is not set, then blocksize negotiation according to
*                   RFC 2348 will be done with default blocksize 1428 bytes. (If the
*                   server doesn't implement RFC 2348 and doesn't answer with proper
*                   OACK, then the client uses 512 bytes as in regular TFTP according
*                   to RFC 1350.)
*                   If the tag is set to 512 bytes, then the client doesn't set
*                   the blksize option and a regular TFTP transfer without negotiation
*                   is performend.
*
*  Restriction:     None
*
*  Value:           IE Type:     Size:     Range:
*                   number       u32       >= 1
*
*  Define:          AAFILE_TFTP_CONFIG_TAG_CLIENT_BLOCKSIZE
*
*  See:             None
* @endverbatim
*
*
* @verbatim
*  Tag name:        ccs.service.aafile.tftp.server.rfc2348.disabled
*
*  Direction:       input
*
*  Description:     Disable blocksize negotiation capablility according to RFC 2348.
*
*  Effect analysis: If this tag is not set (or set to 0) then blocksize negotiation capability
*                   is enabled, otherwise it is disabled.
*
*  Restriction:     None
*
*  Value:           IE Type:     Size:     Range:
*                   number       u32       >= 1
*
*  Define:          AAFILE_TFTP_CONFIG_TAG_SERVER_RFC2348_DISABLED
*
*  See:             None
*
*
* @verbatim
*  Tag name:        ccs.service.aafile.tftp.server.port
*
*  Direction:       input
*
*  Description:     Port number on which the server listens for connections.
*
*  Effect analysis: If this tag is not set, port number 69 is used as default.
*                   Value of this tag has no effect after TFTP server has been initialized.
*
*  Restriction:     None
*
*  Value:           IE Type:     Size:     Range:
*                   number       u32       1-65535
*
*  Define:          AAFILE_TFTP_CONFIG_TAG_SERVER_PORT
*
*  See:             None
* @endverbatim
*
* @verbatim
*  Tag name:        ccs.service.aafile.tftp.server.ipaddress
*
*  Direction:       input
*
*  Description:     IP address of server.
*
*  Effect analysis: If this tag is not set, the server's IP address 0.0.0.0 is used as default.
*                   Value of this tag has no effect after TFTP server has been initialized.
*
*  Restriction:     None
*
*  Value:           IE Type:                   Size:             Range:
*                   zero-terminated string     N/A               N/A
*
*  Define:          AAFILE_TFTP_CONFIG_TAG_SERVER_IP_ADDRESS
*
*  See:             None
* @endverbatim
*/

/**
 * @addtogroup dgAaFileApiMcu
 * @ingroup    dgAaFile
 */

/** @{ */


/*----------------------- PUBLIC INTERFACES --------------------------------*/

/**
*******************************************************************************
*
*   @brief AaFileTftpGet() copies a file from a remote unit.
*          (Function signature has standard arguments.)
*
*   @param[in] ipAddress     Target IP address (dotted decimal notation).
*   @param[in] srcFileName   Source file name.
*   @param[in] dstFileName   Destination file name.
*
*   @return                  AaFile TFTP return code.
*
*   @par Description:
*
*   Fetch a file from a remote unit.
*   The source file name is sent to the server as it is. (On contrary to other AaFile
*   interfaces, this path doesn't follow the rules of AaFile Path Notation, since the
*   remote unit might not have that convention.)
*   If not set through config tag ccs.service.aafile.tftp.client.blocksize otherwise,
*   then by default a blocksize negotiation for 1428 bytes according to RFC 2348 is
*   initiated by this call.
*   For saving the destination file AaFile common API is used. (Therefore the
*   AaFile naming rules, the AaFile Path Notation, are valid for the local file at
*   client side.)
*   If a file with the same name exists, the file is replaced.
*   The function blocks the calling EU until the operation is complete.
*
*   @par Errors:
*
*   See definition of #EAaFileTftpErrorCode, which is the AaFile specific return code.
*   Not to be mistaken with the RFC 1350 error code, sent back through the error packet
*   from server side in case of server sided errors.
*   This function doesn't reflect the RFC 1350 error code at all.
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaFileTftp.h>
*
*   char* address = "192.168.255.25";
*   char* remoteFileName = "/ram/testfile.txt";
*   char* localFileName = "/ram/temp.txt";
*   char* fileName2 = "/ram/testfile2.txt";
*   EAaFileTftpErrorCode ret;
*
*   // Copy the file from remote unit to different name in this unit:
*   ret = AaFileTftpGet(address, remoteFileName, localFileName);
*   if (ret != EAaFileTftpErrorCode_NoError) {
*      // Error or timeout.
*      ...
*   }
*   ...
*
*   // Copy the file from remote unit to same location in this unit:
*   ret = AaFileTftpGet(address, fileName2, fileName2);
*   if (ret != EAaFileTftpErrorCode_NoError) {
*      // Error or timeout.
*      ...
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
*   @see AaFileTftpGetExt()
*   @see AaFileTftpGetExt2()
*
*******************************************************************************/
EAaFileTftpErrorCode AaFileTftpGet(const char* ipAddress,
                                   const char* srcFileName,
                                   const char* dstFileName);

/**
*******************************************************************************
*
*   @brief AaFileTftpGet2() copies a file from a remote unit.
*          (Function signature has standard arguments, but references also - in case of
*           server sided errors - the RFC 1350 error code and error message of received
*           error packet.)
*
*   @param[in]  ipAddress        Target IP address (dotted decimal notation).
*   @param[in]  srcFileName      Source file name.
*   @param[in]  dstFileName      Destination file name.
*   @param[out] rfc1350ErrorCode References the RFC 1350 error code when the server on
*                                remote unit sent back an error opcode.
*   @param[out] errorMessage     References the error message sent back by server on
*                                remote unit.
*   @param[in]  errorMessageSize Size of the user buffer that was passed for the error
*                                message reference.
*
*   @return                  AaFile TFTP return code.
*
*   @par Description:
*
*   Fetch a file from a remote unit.
*   For handling the source and destination file and blocksize negotiation see the
*   description of AaFileTftpGet().
*   Additionally this function reflects the RFC 1350 error code and the error message
*   filled by the server side in case of server sided errors. (E.g. 'File not found'.)
*
*   @par Errors:
*
*   For the returned error code see definition of #EAaFileTftpErrorCode, which is the
*   AaFile specific return code. Not to be mistaken with the RFC 1350 error code, sent back
*   through the error packet from server side in case of server sided errors.
*   This function reflects the RFC 1350 error code and the additional error message,
*   filled by the server, in its reference parameters rfc1350ErrorCode and errorMessage.
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaFileTftp.h>
*
*   char* address = "192.168.255.129";
*   char* remoteFileName = "/ram/testfile.txt";
*   char* localFileName = "/ram/temp.txt";
*   EAaFileTftpErrorCode ret;
*   EAaFileRfc1350ErrorCode rfc1350ErrCode;
*   char errMsg[128];
*
*   // Get the file from the remote unit with a different name at local unit:
*   ret = AaFileTftpGet2( address, remoteFileName, localFileName,
*                         &rfc1350ErrCode, errMsg, sizeof(errMsg));
*   if (ret != EAaFileTftpErrorCode_NoError) {
*       if ( rfc1350ErrCode == EAaFileRfc1350ErrorCode_undefined) {
*           if ( errMsg != GLO_NULL ) {
*               // special handling according to string
*               ...
*           }
*       ...
*       }
*   }
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
*   @see AaFileTftpGet()
*
*******************************************************************************/
EAaFileTftpErrorCode AaFileTftpGet2(const char* ipAddress,
                                    const char* srcFileName,
                                    const char* dstFileName,
                                    EAaFileRfc1350ErrorCode *rfc1350ErrorCode,
                                    char* errorMessage,
                                    u32 errorMessageSize);

/**
*******************************************************************************
*
*   @brief AaFileTftpGetExt() copies a file from a remote unit.
*          (Function signature has extended arguments for timeout and number
*           of retries.)
*
*   @param[in] ipAddress     Target IP address (dotted decimal notation).
*   @param[in] srcFileName   Source file name.
*   @param[in] dstFileName   Destination file name.
*   @param[in] timeout       Timeout for sending/receiving one packet in seconds.
*   @param[in] retries       Number of retries made in case of timeout.
*
*   @return                  AaFile TFTP return code.
*
*   @par Description:
*
*   Fetch a file from a remote unit.
*   For handling the source and destination file and blocksize negotiation see the
*   description of AaFileTftpGet().
*   Additionally the user can specify the number of retrials and the timeout for the
*   case that the remote server doesn't answer with data packets (neither on read request
*   nor on acknowledgement.)
*
*   @par Errors:
*
*   See definition of #EAaFileTftpErrorCode, which is the AaFile specific return
*   code. Not to be mistaken with the RFC 1350 error code, sent back through the error
*   packet from server side in case of server sided errors.
*   This function doesn't reflect the RFC 1350 error code at all.
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaFileTftp.h>
*
*   char* address = "192.168.255.25";
*   char* remoteFileName = "/ram/testfile.txt";
*   char* localFileName = "/ram/temp.txt";
*   char* fileName2 = "/ram/testfile2.txt";
*   u32 timeout = 5;
*   u32 retries = 3;
*   EAaFileTftpErrorCode ret;
*
*   // Get the file from the remote unit with a different name at local unit:
*   ret = AaFileTftpGetExt( address, remoteFileName, localFileName, timeout, retries);
*   if (ret != EAaFileTftpErrorCode_NoError) {
*      // Error or timeout.
*      ...
*   }
*   ...
*
*   // Copy the file from remote unit to same location in this unit:
*   ret = AaFileTftpGetExt( address, fileName2, fileName2, timeout, retries);
*   if (ret != EAaFileTftpErrorCode_NoError) {
*      // Error or timeout.
*      ...
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
*   @see AaFileTftpGet()
*   @see AaFileTftpGetExt2()
*
*******************************************************************************/
EAaFileTftpErrorCode AaFileTftpGetExt(const char* ipAddress,
                                      const char* srcFileName,
                                      const char* dstFileName,
                                      u32 timeout,
                                      u32 retries);
/**
*******************************************************************************
*
*   @brief AaFileTftpGetExt2() copies a file from a remote unit.
*          (Function signature has extended arguments for timeout and number
*           of retries. The function references also - in case of server sided
*           errors - the RFC 1350 error code and error message of received
*           error packet.)
*
*   @param[in]  ipAddress        Target IP address (dotted decimal notation).
*   @param[in]  srcFileName      Source file name.
*   @param[in]  dstFileName      Destination file name.
*   @param[in]  timeout          Timeout for sending/receiving one packet in seconds.
*   @param[in]  retries          Number of retries made in case of timeout.
*   @param[out] rfc1350ErrorCode References the RFC 1350 error code when the server on
*                                remote unit sent back an error opcode.
*   @param[out] errorMessage     References the error message sent back by server on
*                                remote unit.
*   @param[in]  errorMessageSize Size of the user buffer that was passed for the error
*                                message reference.
*
*   @return                      AaFile TFTP return code.
*
*   Fetch a file from a remote unit.
*   For handling the source and destination file and blocksize negotiation see the
*   description of AaFileTftpGet().
*   For a description of timeout and number of retrials see AaFileTftpGetExt().
*   Additionally this function reflects the RFC 1350 error code and the error message
*   filled by the server side in case of server sided errors. (E.g. 'File not found'.)
*
*   @par Errors:
*
*   For the returned error code see definition of #EAaFileTftpErrorCode, which is the
*   AaFile specific return code. Not to be mistaken with the RFC 1350 error code, sent back
*   through the error packet from server side in case of server sided errors.
*   This function reflects the RFC 1350 error code and the additional error message,
*   filled by the server, in its reference parameters rfc1350ErrorCode and errorMessage.
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaFileTftp.h>
*
*   char* address = "192.168.255.25";
*   char* remoteFileName = "/ram/testfile.txt";
*   char* localFileName = "/ram/temp.txt";
*   u32 timeout = 5;
*   u32 retries = 3;
*   EAaFileTftpErrorCode ret;
*   EAaFileRfc1350ErrorCode rfc1350ErrCode;
*   char errMsg[128];
*
*   // Get the file from the remote unit with a different name at local unit:
*   ret = AaFileTftpGetExt2( address, remoteFileName, localFileName,
*                            timeout, retries,
*                            &rfc1350ErrCode, errMsg, sizeof(errMsg));
*   if (ret != EAaFileTftpErrorCode_NoError) {
*       if ( rfc1350ErrCode == EAaFileRfc1350ErrorCode_undefined) {
*           if ( errMsg != GLO_NULL ) {
*               // special handling according to string
*               ...
*           }
*       ...
*       }
*   }
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
*   @see AaFileTftpGet()
*   @see AaFileTftpGetExt()
*
*******************************************************************************/
EAaFileTftpErrorCode AaFileTftpGetExt2(const char* ipAddress,
                                       const char* srcFileName,
                                       const char* dstFileName,
                                       u32 timeout,
                                       u32 retries,
                                       EAaFileRfc1350ErrorCode *rfc1350ErrorCode,
                                       char* errorMessage,
                                       u32 errorMessageSize);

/**
*******************************************************************************
*
*   @brief AaFileTftpGetExt3() copies a file from a remote unit.
*          (Function signature has extended arguments for timeout, number of
*           of retries and data block size according to RFC2348. The function
*           references also - in case of server sided errors - the RFC 1350
*           error code and error message of received error packet.)
*
*   @param[in]  ipAddress        Target IP address (dotted decimal notation).
*   @param[in]  srcFileName      Source file name.
*   @param[in]  dstFileName      Destination file name.
*   @param[in]  blksize          Size of data block (according to RFC 2348).
*   @param[in]  timeout          Timeout for sending/receiving one packet in seconds.
*   @param[in]  retries          Number of retries made in case of timeout.
*   @param[out] rfc1350ErrorCode References the RFC 1350 error code when the server on
*                                remote unit sent back an error opcode.
*   @param[out] errorMessage     References the error message sent back by server on
*                                remote unit.
*   @param[in]  errorMessageSize Size of the user buffer that was passed for the error
*                                message reference.
*
*   @return                      AaFile TFTP return code.
*
*   Fetch a file from a remote unit.
*   For handling the source and destination file see the description of AaFileTftpGet().
*   For a description of timeout and number of retrials see AaFileTftpGetExt().
*   Additionally this function triggers block size negotiation (for given blksize) with
*   the addressed TFTP server according to RFC 2348. If the server is not implemented
*   according to RFC 2348 or it doesn't accept proposed data block size, then the default
*   data block size of 512 bytes is used.
*   Further this function reflects the RFC 1350 error code and the error message
*   filled by the server side in case of server sided errors. (E.g. 'File not found'.)
*
*   @par Errors:
*
*   For the returned error code see definition of #EAaFileTftpErrorCode, which is the
*   AaFile specific return code. Not to be mistaken with the RFC 1350 error code, sent back
*   through the error packet from server side in case of server sided errors.
*   This function reflects the RFC 1350 error code and the additional error message,
*   filled by the server, in its reference parameters rfc1350ErrorCode and errorMessage.
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaFileTftp.h>
*
*   char* address = "192.168.255.25";
*   char* remoteFileName = "/ram/testfile.txt";
*   char* localFileName = "/ram/temp.txt";
*   u32 blksize = 4096;
*   u32 timeout = 5;
*   u32 retries = 3;
*   EAaFileTftpErrorCode ret;
*   EAaFileRfc1350ErrorCode rfc1350ErrCode;
*   char errMsg[128];
*
*   // Get the file from the remote unit with a different name at local unit:
*   ret = AaFileTftpGetExt3( address, remoteFileName, localFileName,
*                            blksize, timeout, retries,
*                            &rfc1350ErrCode, errMsg, sizeof(errMsg));
*   if (ret != EAaFileTftpErrorCode_NoError) {
*       if ( rfc1350ErrCode == EAaFileRfc1350ErrorCode_undefined) {
*           if ( errMsg != GLO_NULL ) {
*               // special handling according to string
*               ...
*           }
*       ...
*       }
*   }
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
*   @see AaFileTftpGet()
*   @see AaFileTftpGetExt()
*
*******************************************************************************/
EAaFileTftpErrorCode AaFileTftpGetExt3(const char* ipAddress,
                                       const char* srcFileName,
                                       const char* dstFileName,
                                       u32 blksize,
                                       u32 timeout,
                                       u32 retries,
                                       EAaFileRfc1350ErrorCode* rfc1350ErrorCode,
                                       char *errorMessage,
                                       u32 errorMessageSize);

/**
*******************************************************************************
*
*   @brief AaFileTftpPut() copies a file to a remote unit.
*          (Function signature has standard arguments.)
*
*   @param[in] ipAddress     Target IP address (dotted decimal notation).
*   @param[in] srcFileName   Source file name.
*   @param[in] dstFileName   Destination file name.
*
*   @return                  AaFile TFTP return code.
*
*   @par Description:
*
*   Send a file to a remote unit.
*   For reading the source file, AaFile common API is used. (Therefore the AaFile
*   naming rules, the AaFile Path Notation, are valid for the local file at client
*   side.)
*   The destination file name is sent to the server as it is. (On contrary to other
*   AaFile interfaces, this path doesn't follow the rules of AaFile Path Notation,
*   since the remote unit might not have that convention.)
*   If not set through config tag ccs.service.aafile.tftp.client.blocksize otherwise,
*   then by default a blocksize negotiation for 1428 bytes according to RFC 2348 is
*   initiated by this call.
*   The function blocks the calling EU until the operation is complete.
*
*   @par Errors:
*
*   See definition of #EAaFileTftpErrorCode, which is the AaFile specific return
*   code. Not to be mistaken with the RFC 1350 error code, sent back through the error
*   packet from server side in case of server sided errors.
*   This function doesn't reflect the RFC 1350 error code at all.
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaFileTftp.h>
*
*   char* address = "192.168.255.25";
*   char* localFileName = "/ram/temp.txt";
*   char* remoteFileName = "/ram/testfile.txt";
*   EAaFileTftpErrorCode ret;
*
*   // Copy the file from this unit to different name in remote unit:
*   ret = AaFileTftpPut( address, localFileName, remoteFileName);
*   if (ret != EAaFileTftpErrorCode_NoError) {
*      // Error or timeout.
*      ...
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
*   @see AaFileTftpPutExt()
*
*******************************************************************************/
EAaFileTftpErrorCode AaFileTftpPut(const char* ipAddress,
                                   const char* srcFileName,
                                   const char* dstFileName);

/**
*******************************************************************************
*
*   @brief AaFileTftpPut2() copies a file to a remote unit.
*          (Function signature has standard arguments, but references also - in case of
*           server sided errors - the RFC 1350 error code and error message of received
*           error packet.)
*
*   @param[in]  ipAddress        Target IP address (dotted decimal notation).
*   @param[in]  srcFileName      Source file name.
*   @param[in]  dstFileName      Destination file name.
*   @param[out] rfc1350ErrorCode References the RFC 1350 error code when the server on
*                                remote unit sent back an error opcode.
*   @param[out] errorMessage     References the error message sent back by server on
*                                remote unit.
*   @param[in]  errorMessageSize Size of the user buffer that was passed for the error
*                                message reference.

*
*   @return                  AaFile TFTP return code.
*
*   @par Description:
*
*   Send a file to a remote unit.
*   For handling the source and destination file and blocksize negotiation see the
*   description of AaFileTftpPut().
*   Additionally this function reflects the RFC 1350 error code and the error message
*   filled by the server side in case of server sided errors. (E.g. 'No space left on device'.)
*
*   @par Errors:
*
*   See definition of #EAaFileTftpErrorCode, which is the AaFile specific return
*   code. Not to be mistaken with the RFC 1350 error code, sent back through the error
*   packet from server side in case of server sided errors.
*   This function doesn't reflect the RFC 1350 error code at all.
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaFileTftp.h>
*
*   char* address = "192.168.255.25";
*   char* localFileName = "/ram/temp.txt";
*   char* remoteFileName = "/ram/testfile.txt";
*   EAaFileTftpErrorCode ret;
*   EAaFileRfc1350ErrorCode rfc1350ErrCode;
*   char errMsg[128];
*
*   // Copy the file from this unit to different name in remote unit:
*   ret = AaFileTftpPut2( address, localFileName, remoteFileName);
*   if (ret != EAaFileTftpErrorCode_NoError) {
*       if ( rfc1350ErrCode == EAaFileRfc1350ErrorCode_undefined) {
*           if ( errMsg != GLO_NULL ) {
*               // special handling according to string
*               ...
*           }
*       ...
*       }
*   }
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
*   @see AaFileTftpPutExt()
*
*******************************************************************************/
EAaFileTftpErrorCode AaFileTftpPut2(const char* ipAddress,
                                    const char* srcFileName,
                                    const char* dstFileName,
                                    EAaFileRfc1350ErrorCode* rfc1350ErrorCode,
                                    char* errorMessage,
                                    u32 errorMessageSize);

/**
*******************************************************************************
*
*   @brief AaFileTftpPutExt() copies a file to a remote unit.
*          (Function signature has extended arguments for timeout and number
*           of retries.)
*
*   @param[in] ipAddress     Target IP address (dotted decimal notation).
*   @param[in] srcFileName   Source file name.
*   @param[in] dstFileName   Destination file name.
*   @param[in] timeout       Timeout for sending/receiving one packet in seconds
*   @param[in] retries       Number of retries made in case of timeout
*
*   @return                  AaFile Tftp return code.
*
*   @par Description:
*
*   Send a file to a remote unit.
*   For handling the source and destination file and blocksize negotiation see the
*   description of AaFileTftpPut().
*   Additionally the user can specify the number of retrials and the timeout for the
*   case that the remote server doesn't answer with acknowledgments on data packets.
*
*   @par Errors:
*
*   See definition of #EAaFileTftpErrorCode, which is the AaFile specific return
*   code. Not to be mistaken with the RFC 1350 error code, sent back through the error
*   packet from server side in case of server sided errors.
*   This function doesn't reflect the RFC 1350 error code at all.
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaFileTftp.h>
*
*   char* address = "192.168.255.25";
*   char* localFileName = "/ram/temp.txt";
*   char* remoteFileName = "/ram/testfile.txt";
*   u32 timeout = 255;
*   u32 retries = 5;
*   EAaFileTftpErrorCode ret;
*
*   // Copy the file from this unit to different name in remote unit:
*   ret = AaFileTftpPutExt( address, localFileName, remoteFileName, timeout, retries);
*   if (ret != EAaFileTftpErrorCode_NoError) {
*      // Error or timeout.
*      ...
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
*   @see AaFileTftpPut()
*
*******************************************************************************/
EAaFileTftpErrorCode AaFileTftpPutExt(const char* ipAddress,
                                      const char* srcFileName,
                                      const char* dstFileName,
                                      u32 timeout,
                                      u32 retries);

/**
*******************************************************************************
*
*   @brief AaFileTftpPutExt2() copies a file to a remote unit.
*          (Function signature has extended arguments for timeout and number
*           of retries. The function references also - in case of server sided
*           errors - the RFC 1350 error code and error message of received
*           error packet.)
*
*   @param[in]  ipAddress        Target IP address (dotted decimal notation).
*   @param[in]  srcFileName      Source file name.
*   @param[in]  dstFileName      Destination file name.
*   @param[in]  timeout          Timeout for sending/receiving one packet in seconds
*   @param[in]  retries          Number of retries made in case of timeout
*   @param[out] rfc1350ErrorCode References the RFC 1350 error code when the server on
*                                remote unit sent back an error opcode.
*   @param[out] errorMessage     References the error message sent back by server on
*                                remote unit.
*   @param[in]  errorMessageSize Size of the user buffer that was passed for the error
*                                message reference.
*
*   @return                      AaFile Tftp return code.
*
*   @par Description:
*
*   Send a file to a remote unit.
*   For handling the source and destination file and blocksize negotiation see the
*   description of AaFileTftpPut().
*   For a description of timeout and number of retrials see AaFileTftpPutExt().
*   Additionally this function reflects the RFC 1350 error code and the error message
*   filled by the server side in case of server sided errors. (E.g. 'No space left on device'.)
*
*   @par Errors:
*
*   See definition of #EAaFileTftpErrorCode, which is the AaFile specific return
*   code. Not to be mistaken with the RFC 1350 error code, sent back through the error
*   packet from server side in case of server sided errors.
*   This function doesn't reflect the RFC 1350 error code at all.
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaFileTftp.h>
*
*   char* address = "192.168.255.25";
*   char* localFileName = "/ram/temp.txt";
*   char* remoteFileName = "/ram/testfile.txt";
*   u32 timeout = 255;
*   u32 retries = 5;
*   EAaFileTftpErrorCode ret;
*   EAaFileTftpErrorCode ret;
*   EAaFileRfc1350ErrorCode rfc1350ErrCode;
*   char errMsg[128];
*
*   // Copy the file from this unit to different name in remote unit:
*   ret = AaFileTftpPutExt2( address, localFileName, remoteFileName,
*                            timeout, retries,
*                            &rfc1350ErrCode, errMsg, sizeof(errMsg));
*   if (ret != EAaFileTftpErrorCode_NoError) {
*       if ( rfc1350ErrCode == EAaFileRfc1350ErrorCode_undefined) {
*           if ( errMsg != GLO_NULL ) {
*               // special handling according to string
*               ...
*           }
*       ...
*       }
*   }
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
*   @see AaFileTftpPut()
*
*******************************************************************************/
EAaFileTftpErrorCode AaFileTftpPutExt2(const char* ipAddress,
                                       const char* srcFileName,
                                       const char* dstFileName,
                                       u32 timeout,
                                       u32 retries,
                                       EAaFileRfc1350ErrorCode* rfc1350ErrorCode,
                                       char* errorMessage,
                                       u32 errorMessageSize);

/**
*******************************************************************************
*
*   @brief AaFileTftpPutExt3() copies a file to a remote unit.
*          (Function signature has extended arguments for timeout, number of
*           of retries and data block size according to RFC2348. The function
*           references also - in case of server sided errors - the RFC 1350
*           error code and error message of received error packet.)
*
*   @param[in]  ipAddress        Target IP address (dotted decimal notation).
*   @param[in]  srcFileName      Source file name.
*   @param[in]  dstFileName      Destination file name.
*   @param[in]  blksize          Size of data block (according to RFC 2348).
*   @param[in]  timeout          Timeout for sending/receiving one packet in seconds
*   @param[in]  retries          Number of retries made in case of timeout
*   @param[out] rfc1350ErrorCode References the RFC 1350 error code when the server on
*                                remote unit sent back an error opcode.
*   @param[out] errorMessage     References the error message sent back by server on
*                                remote unit.
*   @param[in]  errorMessageSize Size of the user buffer that was passed for the error
*                                message reference.
*
*   @return                      AaFile Tftp return code.
*
*   @par Description:
*
*   Send a file to a remote unit.
*   For handling the source and destination file see the description of AaFileTftpPut().
*   For a description of timeout and number of retrials see AaFileTftpPutExt().
*   Additionally this function triggers block size negotiation (for given blksize) with
*   the addressed TFTP server according to RFC 2348. If the server is not implemented
*   according to RFC 2348 or it doesn't accept proposed data block size, then the default
*   data block size of 512 bytes is used.
*   Further this function reflects the RFC 1350 error code and the error message
*   filled by the server side in case of server sided errors. (E.g. 'No space left on device'.)
*
*   @par Errors:
*
*   See definition of #EAaFileTftpErrorCode, which is the AaFile specific return
*   code. Not to be mistaken with the RFC 1350 error code, sent back through the error
*   packet from server side in case of server sided errors.
*   This function doesn't reflect the RFC 1350 error code at all.
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaFileTftp.h>
*
*   char* address = "192.168.255.25";
*   char* localFileName = "/ram/temp.txt";
*   char* remoteFileName = "/ram/testfile.txt";
*   u32 blksize = 4096;
*   u32 timeout = 255;
*   u32 retries = 5;
*   EAaFileTftpErrorCode ret;
*   EAaFileTftpErrorCode ret;
*   EAaFileRfc1350ErrorCode rfc1350ErrCode;
*   char errMsg[128];
*
*   // Copy the file from this unit to different name in remote unit:
*   ret = AaFileTftpPutExt3( address, localFileName, remoteFileName,
*                            blksize, timeout, retries,
*                            &rfc1350ErrCode, errMsg, sizeof(errMsg));
*   if (ret != EAaFileTftpErrorCode_NoError) {
*       if ( rfc1350ErrCode == EAaFileRfc1350ErrorCode_undefined) {
*           if ( errMsg != GLO_NULL ) {
*               // special handling according to string
*               ...
*           }
*       ...
*       }
*   }
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
*   @see AaFileTftpPut()
*
*******************************************************************************/
EAaFileTftpErrorCode AaFileTftpPutExt3(const char* ipAddress,
                                       const char* srcFileName,
                                       const char* dstFileName,
                                       u32 blksize,
                                       u32 timeout,
                                       u32 retries,
                                       EAaFileRfc1350ErrorCode* rfc1350ErrorCode,
                                       char* errorMessage,
                                       u32 errorMessageSize);

/** @} */

/** @name TFTP private API
 *  @brief Functions to setup TFTP service
 */

/** @{ */

/**
*******************************************************************************
*
*   @brief AaFileTftpInit initializes TFTP server.
*
*   @return -1 on error, 0 otherwise.
*
*   @par Description:
*
*   Initializes TFTP server.
*
*   @par Errors:
*
*   If the server process creation fails, -1 is returned.
*
*   @par Restrictions:
*
*   None
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
*******************************************************************************/
int AaFileTftpInit(void);

/** @} */


#ifdef __cplusplus
}
#endif

#endif  /* _MCU_RT_IF_AAFILETFTP_H_ */
