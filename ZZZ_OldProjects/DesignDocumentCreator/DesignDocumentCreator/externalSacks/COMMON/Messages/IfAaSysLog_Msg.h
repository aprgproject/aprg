/** @file
*   @brief Contains AaSysLog Message interface
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: Copyright 2017 Nokia. All rights reserved.$
*/

#ifndef _IFAASYSLOG_MSG_H_
#define _IFAASYSLOG_MSG_H_

#include <CcsCommon.h>
#include <glo_def.h>
#include <IfAaSysLog_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @name Common API Message IDs.
 */
/*@{*/
#define AASYSLOG_CONTROLS_SET_REQ_MSG       0x085B  /* !- SIGNO(struct AaSysLogControlsSetReq) -!  */
#define AASYSLOG_CONTROLS_SET_RESP_MSG      0x085C  /* !- SIGNO(struct AaSysLogControlsSetResp) -!  */
#define AASYSLOG_CONTROLS_GET_REQ_MSG       0x085D  /* !- SIGNO(struct AaSysLogControlsGetReq) -!  */
#define AASYSLOG_CONTROLS_GET_RESP_MSG      0x085E  /* !- SIGNO(struct AaSysLogControlsGetResp) -!  */
#define AASYSLOG_PID_FILTER_SET_REQ_MSG     0x085F  /* !- SIGNO(struct AaSysLogPidFilterSetReq) -!  */
#define AASYSLOG_PID_FILTER_SET_RESP_MSG    0x08C9  /* !- SIGNO(struct AaSysLogPidFilterSetResp) -!  */
#define AASYSLOG_PID_FILTER_CLEAR_REQ_MSG   0x0860  /* !- SIGNO(struct AaSysLogPidFilterClearReq) -!  */
#define AASYSLOG_PID_FILTER_CLEAR_RESP_MSG  0x08CA  /* !- SIGNO(struct AaSysLogPidFilterClearResp) -!  */
#define AASYSLOG_RUNTIME_LOG_REQ_MSG        0x096F  /* !- SIGNO(struct AaSysLogRuntimeLogReq) -!  */
#define AASYSLOG_RUNTIME_LOG_RESP_MSG       0x0970  /* !- SIGNO(struct AaSysLogRuntimeLogResp) -!  */
#define AASYSLOG_HL_NOTIF_MSG               0x1F23  /* !- SIGNO(struct AaSysLogHlNotif) -!  */
/*@}*/

/**
*******************************************************************************
* @brief AaSysLog print dump indication message
*
* @par Description
* This message is used to forward log prints
*
* @par Message Id
* AASYSLOG_PRINT_DUMP_IND_MSG
*
* @par Restrictions:
* Message has to be byte-mode oriented. Endianness has to be specified by Apf flag.
* Endianness can be set using AaSysComMsgSetApf2B.
*
*******************************************************************************/
#define AASYSLOG_PRINT_DUMP_IND_MSG         0x0976  /* !- SIGNO(struct AaSysLogPrintDumpInd) -!  */

/*!
 *  @name Configuration API Message IDs.
 */
/*@{*/
#define AASYSLOG_CONFIG_GET_REQ_MSG     0x0861  /* !- SIGNO(struct AaSysLogConfigGetReq) -!  */
#define AASYSLOG_CONFIG_GET_RESP_MSG    0x0862  /* !- SIGNO(struct AaSysLogConfigGetResp) -!  */
/*@}*/

/**
 *  @brief  Message: Get configuration request.
 */
typedef struct AaSysLogConfigGetReq
{
    void* dummy;    /**< Dummy pointer */
}AaSysLogConfigGetReq;

/**
 *  @brief  Message: Get configuration reply.
 */
typedef struct AaSysLogConfigGetResp
{
    EAaSysLogConfigureRetVal status;       /**< Overall status of config get */
    SAaSysLogConfigParams    configParams; /**< Config parameters */
    SAaSysLogCtrlParams      ctrlParams;   /**< Control parameters */
}AaSysLogConfigGetResp;

/**
 *  @brief  Message: Set control parameters request
 */

typedef struct AaSysLogControlsSetReq
{
    SAaSysLogCtrlParams   ctrlParams;   /**< SAaSysLogCtrlParams structure */
}AaSysLogControlsSetReq;

/**
 *  @brief  Message: Set control parameters reply
 */
typedef struct AaSysLogControlsSetResp
{
    EAaSysLogConfigureRetVal status;     /**< Overall status of controls set */
    SAaSysLogCtrlParams      ctrlParams; /**< SAaSysLogCtrlParams structure */
}AaSysLogControlsSetResp;

/**
 *  @brief  Message: Get control parameters request
 */
typedef struct AaSysLogControlsGetReq
{
    void *dummy;    /**< Dummy pointer */
}AaSysLogControlsGetReq;

/**
 *  @brief Message: Get control parameters reply
 */
typedef struct AaSysLogControlsGetResp
{
    EAaSysLogConfigureRetVal status;     /**< Overall status of controls get */
    SAaSysLogCtrlParams      ctrlParams; /**< SAaSysLogCtrlParams structure */
}AaSysLogControlsGetResp;


/*!
 *  @brief  Message: Create runtime log response.
 */
typedef struct AaSysLogRuntimeLogResp
{
    /*!
     *  @brief  Overall status of runtime log generate.
     */
    EAaSysLogConfigureRetVal status;
}AaSysLogRuntimeLogResp;

/*!
 *  @brief  Message: Print dump indication.
 */
typedef struct AaSysLogPrintDumpInd
{
    /*!
     *  @brief String text data.
     *
     *  Prints are ended with "\r\n\0" line ends. There can be multiple prints
     *  in this message. To get print data length use AaSysComGetPayloadSize().
     */
    u8  data[1];
}AaSysLogPrintDumpInd;

/*!
 *  @brief  Message: High load notification.
 */
typedef struct AaSysLogHlNotif
{
    /*!
     *  @brief SysLog load level.
     *
     *  Load level value for SysLog is based on buffer fullness.
     */
    EAaSysLogBufferLoadLevel  sysLogLoadLevel;
    /*!
     *  @brief CPU load level.
     *
     *  CPU load level depends on current CPU load.
     *  Always zero for DSP.
     */
    EAaSysLogCPULoadLevel  cpuLoadLevel;
}AaSysLogHlNotif;

/**
*******************************************************************************
* @brief AaSysLog system print dump indication message
*
* @par Description
* This message is used to forward system log prints
*
* @par Message Id
* AASYSLOG_SYSTEM_PRINT_DUMP_IND_MSG
*
* @par Restrictions:
* Message has to be byte-mode oriented. Endianness has to be specified by Apf flag.
* Endianness can be set using AaSysComMsgSetApf2B.
*
*******************************************************************************/
#define AASYSLOG_SYSTEM_PRINT_DUMP_IND_MSG 0x11EE  /* !- SIGNO(struct AaSysLogSystemPrintDumpInd) -!  */

typedef struct AaSysLogSystemPrintDumpInd
{
    /*!
     *  @brief Single AaSysLog system formatted log line.
     */
    u8 text[1];
}AaSysLogSystemPrintDumpInd;

/**
*******************************************************************************
* @brief AaSysLog Configuration message
*
* @par Description
* Message is published, using AaSysMb in GLOBAL ZONE, by AaSysLog master in order to propagate the configuration among AaSysLog slaves.
* AaSysLog configurations in message are grouped in structures.
*
* @par Message Id
* AASYSLOG_CONFIGURATION_IND_MSG
*
* @par Restrictions:
* Message has to be byte-mode oriented. Endianness has to be specified by Apf flag.
* Endianness can be set using AaSysComMsgSetApf2B.
*
*******************************************************************************/
#define AASYSLOG_CONFIGURATION_IND_MSG 0x14E0  /* !- SIGNO(struct SAaSysLogConfigurationInd) -!  */

/*!
 *  @brief  Message: AaSysLog configuration indication message structure
 */
typedef struct SAaSysLogConfigurationInd
{
    /*!
     *  @brief Indication which structures have changed from the previous publication.
     *  To inform that structure was changed, the appropriate bit is turned on.
     *  Example values:
     *      1st structure changed -> value = 1
     *      2nd structure changed -> value = 2
     *      3rd structure changes -> value = 4
     *      1st and 2nd structure changed -> value = 3
     *
     *  For marking the structure as modified enum EAaSysLogConfigurationChangeInd can be used.
     *  It defines appropriate value for every structure contained in SAaSysLogConfigurationInd.
     *  NOTE: SAaSysLogConfigurationInd will be extended in the future - currently there is only one structure inside,
     *        so there are only two valid values for this variable (0 and 1).
     */
    u32 changeIndication;
    /*!
     *  @brief configuration of direct udp
     */
    SAaSysLogDirectUdpOutputConfiguration directUdpOutputConfiguration;
}SAaSysLogConfigurationInd;

#ifdef __cplusplus
}
#endif

#endif /* _IFAASYSLOG_MSG_H_*/
