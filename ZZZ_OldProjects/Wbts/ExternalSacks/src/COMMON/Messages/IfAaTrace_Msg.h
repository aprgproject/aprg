/** @file
*   @brief This file contains AaTrace message definitions
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: 2018 Nokia. All rights reserved.$
*/
#ifndef _IFAATRACE_MSG_H
#define _IFAATRACE_MSG_H

#include <IfAaTrace_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup dgAaTraceMessages AaTrace Messages
 *  @ingroup dgAaTrace
 *  This chapter describe messages used in AaTrace API and their data structures.
 */
///@{

/** @name AaTrace interface message IDs.
 */
///@{

/** @brief This message contain `struct AaTraceMonCtrlRespMsg`
 *
 *  This message contain response code for `AATRACE_MON_CTRL_REQ_MSG` request.
 */
#define AATRACE_MON_CTRL_RESP_MSG              (0x1813) /* !- SIGNO(struct AaTraceMonCtrlRespMsg) -! */

/** @brief This message contain `struct AaTraceMonCtrlReqMsg`
 *
 *  This message configure tracing of SysCom messages. It contain AaTrace filters configuration.
 *  AaTrace respond with `AATRACE_MON_CTRL_RESP_MSG` which contain status code.
 */
#define AATRACE_MON_CTRL_REQ_MSG               (0x1819) /* !- SIGNO(struct AaTraceMonCtrlReqMsg) -! */

/** @brief This message contain `struct AaTraceMonIndMsg`
 *
 *  This message contain traced message with some additional information related to traced message.
 */
#define AATRACE_MON_IND_MSG                    (0x2991) /* !- SIGNO(struct AaTraceMonIndMsg) -! */

/** @brief This message contain `struct AaTraceAggregatedMonIndMsg`
 *
 *  This message contain several traced messages. Contain array of `AATRACE_MON_IND_MSG` messages.
 */
#define AATRACE_AGGREGATED_MON_IND_MSG         (0x0BF9) /* !- SIGNO(struct AaTraceAggregatedMonIndMsg) -! */

/** @brief This message has no content
 *
 *  This message used to force sending of `AATRACE_AGGREGATED_MON_IND_MSG` message
 */
#define AATRACE_AGGREGATED_TIMEOUT_IND_MSG     (0x0C3D) /* !- SIGNO(struct void) -! */

/** @brief This message has no content
 *
 *  This message suspends tracing of SysCom messages. After message is received
 *  AaTrace sends `AATRACE_SESSION_STATE_CHANGE_NOTIF_MSG` message to the sender
 *  of request message and to AaTrace client if tracing is configured to send data to external tool.
 *  Tracing remains suspended until `AATRACE_RESUME_TRACING_REQ_MSG` message is received.
 */
#define AATRACE_SUSPEND_TRACING_REQ_MSG        (0x1232) /* !- SIGNO(struct void) -! */

/** @brief This message has no content
 *
 *  This message resumes tracing of SysCom messages.
 *  After message is received AaTrace sends `AATRACE_SESSION_STATE_CHANGE_NOTIF_MSG`
 *  message to the sender of request message and to AaTrace client
 *  if tracing is configured to send data to external tool.
 */
#define AATRACE_RESUME_TRACING_REQ_MSG         (0x1233) /* !- SIGNO(struct void) -! */

/** @brief This message message contain `struct AaTraceSessionStateChangeNotifMsg`
 *
 *  This message notifies about session state change. It is sent when session is
 *  suspended or resumed to sender of `AATRACE_SUSPEND_TRACING_REQ_MSG`
 *  or `AATRACE_RESUME_TRACING_REQ_MSG` messages and to AaTrace client
 *  if tracing is configured to send data to external tool. It is also send to AaTrace client
 *  in case there is request to enable tracing via message `AATRACE_MON_CTRL_REQ_MSG`
 *  while tracing is suspended.
 */
#define AATRACE_SESSION_STATE_CHANGE_NOTIF_MSG (0x1234) /* !- SIGNO(struct AaTraceSessionStateChangeNotifMsg) -! */

/** @brief This message has no content
 *
 *  This message request AaTrace to stop tracing for all active instances.
 *  AaTrace will send `AATRACE_STOP_ALL_INSTANCES_IND_MSG` message to all active instances.
 */
#define AATRACE_STOP_ALL_INSTANCES_REQ_MSG     (0x1466) /* !- SIGNO(struct void) -! */

/** @brief This message has no content
 *
 *  This message inform that AaTrace stops tracing for all active instances.
 *  Each active client receive message after `AATRACE_STOP_ALL_INSTANCES_REQ_MSG` was send.
 */
#define AATRACE_STOP_ALL_INSTANCES_IND_MSG     (0x1467) /* !- SIGNO(struct void) -! */

/** @brief This message has no content
 *
 *  This message request AaTrace to reply with `AATRACE_STATUS_RESP_MSG` message
 *  which contain current AaTrace configuration for all active instances.
 */
#define AATRACE_STATUS_REQ_MSG                 (0x1468) /* !- SIGNO(struct void) -! */

/** @brief This message message contain `struct AaTraceStatusRespMsg`
 *
 *  This message contain current AaTrace configuration for all active clients.
 *  AaTrace sends this message as reply for `AATRACE_STATUS_REQ_MSG` message.
 */
#define AATRACE_STATUS_RESP_MSG                (0x1469) /* !- SIGNO(struct AaTraceStatusRespMsg) -! */

///@}

#define AATRACE_AGG_MON_MSG_HEADER_SIZE (sizeof(AaTraceAggregatedMonIndMsg) - sizeof(AaTraceMonIndMsg))
#define AATRACE_MON_MSG_HEADER_SIZE     (sizeof(AaTraceMonIndMsg) - sizeof(u32))
#define AATRACE_MAX_MONITOR_EXTRA       (4)

/** Response message for monitor control messages.
 */
typedef struct
{
    EAaTraceRetVal successCode;     ///< Success code
} AaTraceMonCtrlRespMsg;

/** Monitor control request message.
 */
typedef struct
{
    SAaTraceMonCtrlParams sAaTraceMonCtrlParams;  ///< Monitor control message parameters.
} AaTraceMonCtrlReqMsg;

/** Message to transport monitored data.
 */
typedef struct
{
    EMonitorType type;                    ///< See EMonitorType.h
    EMonitorMode mode;                    ///< See EMonitorMode.h
    u32 sequence;                         ///< Running number for a monitoring instance (point)
    u32 extra[AATRACE_MAX_MONITOR_EXTRA]; ///< [0..1] - microseconds from UTC midnight, [2] - BCN, [3] - 0
    u32 dataLen;                          ///< Number of octets appended
    u32 data[1];                          ///< Monitored data
} AaTraceMonIndMsg;

/** Used by Message to transport monitored SIC messages to BTSlog.
 *  Can contain multiple monitored messages.
 */
typedef struct
{
    u32 monMsgCount;                ///< Number of aggregated monitored messages
    u32 totalDataLen;               ///< Total number of bytes appended
    AaTraceMonIndMsg monMsgData[1]; ///< Monitored messages' data
} AaTraceAggregatedMonIndMsg;

/** Notification message for changed session state.
 */
typedef struct
{
    EAaTraceSessionStateChange sessionStateChange;     ///< Session state change
} AaTraceSessionStateChangeNotifMsg;

typedef struct
{
    u32 features;                                       ///< supported features (bitfieald of AATRACE_FEATURE_..._MASK)
    u32 numOfInst;                                      ///< number of active configurations
    SAaTraceMonStatusParams sAaTraceMonStatusParams[1]; ///< array of active configurations
} AaTraceStatusRespMsg;



/** Structure used in `API_OM_TEST_MSG` (0x2B83). This message used for ping functionality.
 *  AaTrace will reply with `API_OM_TEST_RESP_MSG` message if `loop_type` equal to
 *  `SW_API_LOOP` (0x69). Reply message contain same content as request.
 */
typedef struct
{
    u32 loop_type;   ///< Support only SW_API_LOOP (0x69)
    u32 data[1];     ///< Place holder for test data
} SAaTraceApiOamTest;

typedef SAaTraceApiOamTest SAaTraceApiOamTestResp;
typedef SAaTraceApiOamTest SAaTraceApiOamTestReq;

/**@}*/

#ifdef __cplusplus
}
#endif

#endif //_IFAATRACE_MSG_H
