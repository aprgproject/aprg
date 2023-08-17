/** @file
*   @brief Contains AaSysLog Message interface
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: Copyright 2018 Nokia. All rights reserved.$
*/

#ifndef _MCU_IFAASYSLOG_MSG_H_
#define _MCU_IFAASYSLOG_MSG_H_

#include <CcsCommon.h>
#include <ESysLogSwDomain.h>
#include <IfAaSysLog_Defs.h>
#include <IfAaSysComGw_Defs.h>
#include "../../COMMON/Messages/IfAaSysLog_Msg.h"
#include "../../SHARED/MCU_RT/Messages/IfAaSysLog_Msg.h"

#define AASYSLOG_SUBSTRING_SEARCH_MAX_STRING_SIZE 80

#ifdef __cplusplus
extern "C" {
#endif

/**
************************************************************************************************
* @defgroup dgAaSysLogMsg AaSysLog Messages
* @ingroup  dgAaSysLog
*/
/*@{*/
/**
* @brief AaSysLog substring search register message
*
* @par Description
* This message is used for starting substring search.
*
* @par Message Id
* AASYSLOG_SUBSTRING_SEARCH_REGISTER_REQ_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AASYSLOG_SUBSTRING_SEARCH_REGISTER_REQ_MSG 0x112E /* !- SIGNO(struct SAaSysLogSubstringSearchRegisterReq) -!  */

/**
************************************************************************************************
* @defgroup dgAaSysLogMsg AaSysLog Messages
* @ingroup  dgAaSysLog
*/
/*@{*/
/**
* @brief AaSysLog substring search unregister message
*
* @par Description
* This message is used for stopping substring search.
*
* @par Message Id
* AASYSLOG_SUBSTRING_SEARCH_UNREGISTER_REQ_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AASYSLOG_SUBSTRING_SEARCH_UNREGISTER_REQ_MSG 0x112F /* !- SIGNO(struct SAaSysLogSubstringSearchUnRegisterReq) -!  */

/**
************************************************************************************************
* @defgroup dgAaSysLogMsg AaSysLog Messages
* @ingroup  dgAaSysLog
*/
/*@{*/
/**
* @brief AaSysLog substring search response message
*
* @par Description
* This message is used by AaSysLog to respond on AASYSLOG_SUBSTRING_SEARCH_REGISTER_REQ or AASYSLOG_SUBSTRING_SEARCH_UNREGISTER_REQ.
*
* @par Message Id
* AASYSLOG_SUBSTRING_SEARCH_RESP_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AASYSLOG_SUBSTRING_SEARCH_RESP_MSG 0x1130 /* !- SIGNO(struct SAaSysLogSubstringSearchResp) -!  */

/**
************************************************************************************************
* @defgroup dgAaSysLogMsg AaSysLog Messages
* @ingroup  dgAaSysLog
*/
/*@{*/
/**
* @brief AaSysLog substring search found indication message
*
* @par Description
* This message is used to inform that the string was found.
*
* @par Message Id
* AASYSLOG_SUBSTRING_SEARCH_FOUND_IND_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AASYSLOG_SUBSTRING_SEARCH_FOUND_IND_MSG 0x1131 /* !- SIGNO(struct SAaSysLogSubstringSearchFoundInd) -!  */

/**
************************************************************************************************
* @defgroup dgAaSysLogMsg AaSysLog Messages
* @ingroup  dgAaSysLog
*/
/*@{*/
/**
* @brief AaSysLog runtime freeze request message
*
* @par Description
* This message is used internally to request AaSysLog runtime log freeze.
*
* @par Message Id
* AASYSLOG_RUNTIME_FREEZE_REQ_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AASYSLOG_RUNTIME_FREEZE_REQ_MSG 0x1147 /* !- SIGNO(struct SAaSysLogRuntimeFreezeReq) -!  */

/**
************************************************************************************************
* @defgroup dgAaSysLogMsg AaSysLog Messages
* @ingroup  dgAaSysLog
*/
/*@{*/
/**
* @brief AaSysLog runtime unfreeze request message
*
* @par Description
* This message is used internally to request AaSysLog runtime log unfreeze.
*
* @par Message Id
* AASYSLOG_RUNTIME_UNFREEZE_REQ_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AASYSLOG_RUNTIME_UNFREEZE_REQ_MSG 0x1148 /* !- SIGNO(struct SAaSysLogRuntimeUnfreezeReq) -!  */

/**
 *  @name MCU Linux API Message IDs.
 */
/*@{*/
#define AASYSLOG_START_RAMDISK_REQ_MSG                  0x0C28  /* !- SIGNO(struct AaSysLogStartRamdiskReq) -!  */
#define AASYSLOG_START_RAMDISK_RESP_MSG                 0x0C29  /* !- SIGNO(struct AaSysLogStartRamdiskResp) -!  */
#define AASYSLOG_STOP_RAMDISK_REQ_MSG                   0x0C2A  /* !- SIGNO(struct AaSysLogStopRamdiskReq) -!  */
#define AASYSLOG_STOP_RAMDISK_RESP_MSG                  0x0C2B  /* !- SIGNO(struct AaSysLogStopRamdiskResp) -!  */
#define AASYSLOG_REMOTE_SYSLOG_STREAMING_START_REQ_MSG  0x0F6B  /* !- SIGNO(struct AaSysLogRemoteSyslogStartReq) -!  */
#define AASYSLOG_REMOTE_SYSLOG_STREAMING_START_RESP_MSG 0x0F6C  /* !- SIGNO(struct AaSysLogRemoteSyslogStartResp) -!  */
#define AASYSLOG_REMOTE_SYSLOG_STREAMING_STOP_REQ_MSG   0x0F6D  /* !- SIGNO(struct AaSysLogRemoteSyslogStopReq) -!  */
#define AASYSLOG_REMOTE_SYSLOG_STREAMING_STOP_RESP_MSG  0x0F6E  /* !- SIGNO(struct AaSysLogRemoteSyslogStopResp) -!  */

/** @brief: Extended message (with TLS support).
 *  @par Restrictions: TLS is supported by CC&S-MCU on RCP only, other platforms do not support TLS.
 */
#define AASYSLOG_REMOTE_SYSLOG_TLS_STREAMING_START_REQ_MSG      0xD105  /* !- SIGNO(struct AaSysLogRemoteSyslogStartReq) -!  */
/** @brief: Extended message (with TLS support).
 *  @par Restrictions: TLS is supported by CC&S-MCU on RCP only, other platforms do not support TLS.
 */
#define AASYSLOG_REMOTE_SYSLOG_TLS_STREAMING_START_RESP_MSG     0xD106  /* !- SIGNO(struct AaSysLogRemoteSyslogStartResp) -!  */
/** @brief: Extended message (with TLS support).
 *  @par Restrictions: TLS is supported by CC&S-MCU on RCP only, other platforms do not support TLS.
 */
#define AASYSLOG_REMOTE_SYSLOG_TLS_STREAMING_STOP_REQ_MSG       0xD107  /* !- SIGNO(struct AaSysLogRemoteSyslogStopReq) -!  */
/** @brief: Extended message (with TLS support).
 *  @par Restrictions: TLS is supported by CC&S-MCU on RCP only, other platforms do not support TLS.
 */
#define AASYSLOG_REMOTE_SYSLOG_TLS_STREAMING_STOP_RESP_MSG      0xD108  /* !- SIGNO(struct AaSysLogRemoteSyslogStopResp) -!  */
/*@}*/

/**
*******************************************************************************
* @brief AaSysLog LZ4 compressed print dump indication message
*
* @par Description
* This message is used to forward compressed log prints
*
* @par Message Id
* AASYSLOG_PRINT_LZ4_DUMP_IND_MSG
*
* @par Restrictions:
* Message has to be byte-mode oriented. Endianness has to be specified by Apf flag.
* Endianness can be set using AaSysComMsgSetApf2B.
* Word field (u32) should have endianness manually fixed.
*
*******************************************************************************/
#define AASYSLOG_PRINT_LZ4_DUMP_IND_MSG                 0x102D  /* !- SIGNO(struct AaSysLogPrintLz4DumpInd) -!  */

/**
 * @defgroup dgAaSysLogMsg AaSysLog Messages
 * @ingroup dgAaSysLog
 */
/*@{*/

/**
 *  @brief  Message: Create runtime log request.
 */
typedef struct AaSysLogRuntimeLogReq
{
    /**
     *  @brief  Maximum size of runtime log.
     *
     *  If zero is given, all data that are available are stored.
     *
     *  If file is compressed this parameters does not limit the compressed
     *  file size, it limits the ASCII log size inside compressed file.
     *
     *  NOTE: in case of compression mode (enabled by configuration tag
     *        "ccs.service.aasyslog.compression.enabled") it is recomended
     *        to collect always full available content of the runtime buffer
     *        i.e. size parameter equals 0. Otherwise i.e. when size is given
     *        in the request procedure which collects runtime log is expensive
     *        in therms of time and CPU utilization.
     */
    u32 size;
    /**
     *  @brief  Name of runtime log file.
     *
     *  If name is not given (NULL), "runtime.log" name is used for file prefix
     *  and file is compressed. Example Unit1_Runtime.xz file is saved to
     *  temporary disk.
     *
     *  If name contains file extension ".zip" or ".xz" then file is compressed,
     *  otherwise it is ASCII log file.
     *
     *  For EAaSysLogRuntimeLogDomainCoverage_Full files are created in ".zip"
     *  archive containing ".xz" compressed runtime logs. If name is not given
     *  (NULL), "runtime.zip" name is used.
     */
    u8  name[AASYSLOG_MAX_FILE_NAME_LENGTH];

    /**
     *  @brief  runtime log domain coverage.
     *
     *  If EAaSysLogRuntimeLogDomainCoverage_Partial is used
     *  runtime log is only requested from specified log domain in the logSwDomain
     *  parameter.
     *
     *  For EAaSysLogRuntimeLogDomainCoverage_Full runtime log is requested from
     *  all registered log domain buffers, logSwDomain parameter is ignored.
     */
    EAaSysLogRuntimeLogDomainCoverage logDomainCoverage;

    /**
     *  @brief  SW log domain ID
     *
     *  Specifies from which log domain runtime log is requested.
     *  This parameter only used with EAaSysLogRuntimeLogDomainCoverage_Partial
     */
    ESysLogSwDomain logSwDomain;
}AaSysLogRuntimeLogReq;

/**
 *  @brief  Message:  to CC&S to start streaming AaSysLog prints into ramdisk
 */
typedef struct AaSysLogStartRamdiskReq
{
   /**
    *  @brief  Maximum size of RamDisk space available for logs.
    */
   u32 size;
}AaSysLogStartRamdiskReq;

/**
 *  @brief  Message: CC&S starts streaming and saving prints into ramdisk and replies
 */
typedef struct AaSysLogStartRamdiskResp
{
   /**
    *  @brief  Overall status of the start procedure.
    */
    EAaSysLogConfigureRetVal status;
}AaSysLogStartRamdiskResp;

/**
 *  @brief  Message:  to CC&S to stop streaming AaSysLog prints into ramdisk
 */
typedef struct AaSysLogStopRamdiskReq
{
    void *dummy;  /**< Dummy pointer */
}AaSysLogStopRamdiskReq;

/**
 *  @brief  Message:  CC&S stop streaming and saving prints into ramdisk and replies
 */
typedef struct AaSysLogStopRamdiskResp
{
    EAaSysLogConfigureRetVal status;  /**< Dummy pointer */
}AaSysLogStopRamdiskResp;

/**
 *  @brief  Message: request to start streaming of logs to remote syslog server
 */
typedef struct AaSysLogRemoteSyslogStartReq
{
    EAaSysLogLogFormat      logFormat;               /**< Overall status of controls set */
    TAaSysComGwIpAddressStr destinationIpAddress;    /**< syslog server IP address given as null-terminated string*/
    u32                     destinationPort;         /**< destination port number */
    u32                     mrBtsId;                 /**< MRBTS id */
    u32                     dscp;                    /**< DSCP value */
    TAaSysComGwIpAddressStr sourceIpAddress;         /**< BTS public IP address given as null-terminated string */
} AaSysLogRemoteSyslogStartReq;

/**
 *  @brief  Message: request to start streaming of logs to remote syslog server
 */
typedef struct AaSysLogRemoteSyslogStartResp
{
    EAaSysLogRemoteSyslogStartStatus status; /**< Overall status of request */

} AaSysLogRemoteSyslogStartResp;

/**
 *  @brief  Message: request to start streaming of logs to remote syslog server
 */
typedef struct AaSysLogRemoteSyslogStopReq
{
    void *dummy; /**< Dummy pointer */

} AaSysLogRemoteSyslogStopReq;

/**
 *  @brief  Message: request to start streaming of logs to remote syslog server
 */
typedef struct AaSysLogRemoteSyslogStopResp
{
    EAaSysLogRemoteSyslogStopStatus status; /**< Overall status of request */

} AaSysLogRemoteSyslogStopResp;

/*!
 *  @brief  Message: Print dump indication with compressed logs.
 */
typedef struct AaSysLogPrintLz4DumpInd
{
    /*!
     *  @brief  Uncompressed packet size.
     */
    u32 uncompressedSize;
    /*!
     *  @brief  Compressed packet size.
     */
    u32 compressedSize;
    /*!
     *  @brief String text data.
     *
     *  There can be multiple prints in this message. After decompressing each print ends with "\r\n\0" line ends.
     *  To get print data length use AaSysComGetPayloadSize() - sizeof(uncompressedSize) - sizeof(compressedSize)
     */
    u8  data[1];

}AaSysLogPrintLz4DumpInd;

/*!
 *  @brief  Message: Data container for sending logs outside of the BTS using
 *          EAaSysLogOutputMode_CompressedLocal output mode (UDP)
 */
typedef struct AaSysLogLz4UdpData
{
    /*!
     *  @brief Packet identifier used for identyfication whether datagram
     *         is plain UDP log packet or LZ4 compressed data packet.
     *         Id is equal to AASYSLOG_PRINT_LZ4_DUMP_IND_MSG
     *  @see   AASYSLOG_PRINT_LZ4_DUMP_IND_MSG
     */
    u32 id;
    /*!
     *  @brief Compressed logs data container
     *  @see   AaSysLogPrintLz4DumpInd
     */
    AaSysLogPrintLz4DumpInd data;
}AaSysLogLz4UdpData;

/**
************************************************************************************************
* @brief AaSysLog substring search registration message structure
* @param substring which has to be searched in logs
*
* @par Description
* This message is used for starting substring search.
*
* @par Message Id
* AASYSLOG_SUBSTRING_SEARCH_REGISTER_REQ_MSG
***********************************************************************************************/
typedef struct SAaSysLogSubstringSearchRegisterReq
{
    char substring[AASYSLOG_SUBSTRING_SEARCH_MAX_STRING_SIZE];
}SAaSysLogSubstringSearchRegisterReq;

/**
************************************************************************************************
* @brief AaSysLog substring search unregistration message structure
* @param id of the search
*
* @par Description
* This message is used for stopping substring search.
*
* @par Message Id
* AASYSLOG_SUBSTRING_SEARCH_UNREGISTER_REQ_MSG
***********************************************************************************************/
typedef struct SAaSysLogSubstringSearchUnRegisterReq
{
    u32 id;
}SAaSysLogSubstringSearchUnRegisterReq;

/**
************************************************************************************************
* @brief AaSysLog substring search registration response message structure
* @param status
* @param id of the search
*
* @par Description
* This message is used by AaSysLog to respond on AASYSLOG_SUBSTRING_SEARCH_REGISTER_REQ or AASYSLOG_SUBSTRING_SEARCH_UNREGISTER_REQ.
*
* @par Message Id
* AASYSLOG_SUBSTRING_SEARCH_RESP_MSG
***********************************************************************************************/
typedef struct SAaSysLogSubstringSearchResp
{
    EAaSysLogSubstringSearchStatus status;
    u32 id;
}SAaSysLogSubstringSearchResp;

/**
************************************************************************************************
* @brief AaSysLog substring search registration message structure
* @param id of the search
*
* @par Description
* This message is used to inform that the string was found.
*
* @par Message Id
* AASYSLOG_SUBSTRING_SEARCH_FOUND_IND_MSG
***********************************************************************************************/
typedef struct SAaSysLogSubstringSearchFoundInd
{
    u32 id;
}SAaSysLogSubstringSearchFoundInd;

/**
************************************************************************************************
* @brief AaSysLog runtime freeze message structure
* @param empty
*
* @par Description
* This message is used to request AaSysLog Runtime freeze.
*
* @par Message Id
* AASYSLOG_RUNTIME_FREEZE_REQ_MSG
***********************************************************************************************/
typedef struct SAaSysLogRuntimeFreezeReq
{
    u32 empty;
}SAaSysLogRuntimeFreezeReq;

/**
************************************************************************************************
* @brief AaSysLog runtime unfreeze message structure
* @param empty
*
* @par Description
* This message is used to request AaSysLog Runtime unfreeze.
*
* @par Message Id
* AASYSLOG_RUNTIME_UNFREEZE_REQ_MSG
***********************************************************************************************/
typedef struct SAaSysLogRuntimeUnfreezeReq
{
    u32 empty;
}SAaSysLogRuntimeUnfreezeReq;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* _MCU_IFAASYSLOG_MSG_H_ */

