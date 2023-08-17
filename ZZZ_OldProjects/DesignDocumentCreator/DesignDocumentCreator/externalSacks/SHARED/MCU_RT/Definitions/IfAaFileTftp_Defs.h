/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaFile MCU_RT TFTP definitions
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IF_AAFILETFTP_DEFS_H_
#define _MCU_RT_IF_AAFILETFTP_DEFS_H_

#include <glo_def.h>
#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaFileApiMcu
 * @ingroup    dgAaFile
 */

/** @{ */

/**
 * @brief Attribute tag:
 * List of IP addresses that TFTP server will allow to perform PUT operation.
 */
#define AAFILE_TFTP_CONFIG_TAG_PUT_WHITELIST     "ccs.service.aafile.tftp.server.putwhitelist"

/**
 * @brief Attribute tag:
 * List of IP addresses that TFTP server will allow to perform GET operation.
 */
#define AAFILE_TFTP_CONFIG_TAG_GET_WHITELIST     "ccs.service.aafile.tftp.server.getwhitelist"

/**
 * @brief Attribute tag: TFTP client timeout.
 */
#define AAFILE_TFTP_CONFIG_TAG_CLIENT_TIMEOUT    "ccs.service.aafile.tftp.client.timeout"

/**
 * @brief Attribute tag: TFTP client blocksize (for negotiation according to RFC 2348)
 */
#define AAFILE_TFTP_CONFIG_TAG_CLIENT_BLOCKSIZE  "ccs.service.aafile.tftp.client.blocksize"

/**
 * @brief Attribute tag: TFTP server disable blocksize negotiation according to RFC 2348
 */
#define AAFILE_TFTP_CONFIG_TAG_SERVER_RFC2348_DISABLED "ccs.service.aafile.tftp.server.rfc2348.disabled"

/**
 * @brief Attribute tag: TFTP server timeout.
 */
#define AAFILE_TFTP_CONFIG_TAG_SERVER_TIMEOUT    "ccs.service.aafile.tftp.server.timeout"

/**
 * @brief Attribute tag: TFTP client target port.
 */
#define AAFILE_TFTP_CONFIG_TAG_CLIENT_PORT       "ccs.service.aafile.tftp.client.port"

/**
 * @brief Attribute tag: TFTP server listening port.
 */
#define AAFILE_TFTP_CONFIG_TAG_SERVER_PORT       "ccs.service.aafile.tftp.server.port"

/**
 * @brief Attribute tag: TFTP server IP address.
 */
#define AAFILE_TFTP_CONFIG_TAG_SERVER_IP_ADDRESS "ccs.service.aafile.tftp.server.ipaddress"

/**
 * @brief RFC 1350 error codes.
 */
typedef enum EAaFileRfc1350ErrorCode {
    EAaFileRfc1350ErrorCode_Undefined           = 0,
    EAaFileRfc1350ErrorCode_FileNotFound        = 1,
    EAaFileRfc1350ErrorCode_AccessViolation     = 2,
    EAaFileRfc1350ErrorCode_DiskFull            = 3,
    EAaFileRfc1350ErrorCode_IllegalOp           = 4,
    EAaFileRfc1350ErrorCode_UnknownTransferID   = 5,
    EAaFileRfc1350ErrorCode_FileAlreadyExists   = 6,
    EAaFileRfc1350ErrorCode_NoSuchUser          = 7,
    EAaFileRfc1350ErrorCode_RejectOAck          = 8 /* this error code is defined in RFC 2348 */
} EAaFileRfc1350ErrorCode;

/**
 * @brief AaFile TFTP return codes for client functions.
 */
typedef enum EAaFileTftpErrorCode {
    EAaFileTftpErrorCode_NoError,           /**< No error */
    EAaFileTftpErrorCode_ReadError,         /**< File was not found, could not be read or permission was denied. */
    EAaFileTftpErrorCode_WriteError,        /**< Creating or writing the file failed or permission was denied. */
    EAaFileTftpErrorCode_Timeout,           /**< Timeout occurred. */
    EAaFileTftpErrorCode_UndefinedError     /**< Reason for the error is undefined. See the log for details. */
} EAaFileTftpErrorCode;                     /**< Type definition for the client return code. */

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* _MCU_RT_IF_AAFILETFTP_DEFS_H_ */
