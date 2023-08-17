/** @file
*   @brief This file contains AaTrace definitions
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: 2018 Nokia. All rights reserved.$
*/
#ifndef _IFAATRACE_DEFS_H
#define _IFAATRACE_DEFS_H
#include <CcsCommon.h>
#include <glo_def.h>
#include <glo_msg.h>
#include <EMonitorMode.h>
#include <EMonitorType.h>
#include <TAaSysComSicad.h>
#include <SMessageHeader.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup dgAaTraceDefinitions AaTrace Definitions
 *  @ingroup dgAaTrace
 *  This chapter describe definitions used in AaTrace API.
 */
///@{


/** @name AaTrace configuration tags.
 */
///@{

/** Time window size in microseconds to slow down trace traffic. A choke
 *  allows then 10 traced messages in the user-defined time window. For
 *  example, the time window 1000us limits maximum trace traffic to 10000
 *  messages/s. If you want to use AaTrace without time window, set time window
 *  size to 0.
 */
#define AATRACE_CONFIG_TAG_TIMEWINDOWSIZE  "ccs.service.aatrace.timewindowsize"


/** Parameter to enable or disable trace recording.
 *  Possible values 0...100, 0 means recording is off (disabled),
 *  value > 0 mean recording is on and define max size of recorded file.
 */
#define AATRACE_CONFIG_TAG_MAXFILESIZE     "ccs.service.aatrace.maxfilesize"

/** Size of a buffer used for buffering monitored messages before
 *  they are sent to the test tool as a single aggregated monitor message.
 *  Default value for the parameter is 4kB (equals to the SRIO packet size).
 */
#define AATRACE_CONFIG_TAG_AGG_BUFFER_SIZE "ccs.service.aatrace.aggregated.buffer.size"

/** Maximum delay in milliseconds for buffering monitored messages before
 *  they are sent to the test tool as a single aggregated monitor message.
 *  Default value for the parameter is 200 ms.
 */
#define AATRACE_CONFIG_TAG_AGG_TIMEOUT     "ccs.service.aatrace.aggregated.timeout"

/** Restrict possible tracing message target to own domain. Domain is
 *  first HEX digit on node ID
 */
#define AATRACE_CONFIG_TAG_RESTRICT_TARGET_TO_OWN_DOMAIN  "ccs.service.aatrace.restrict_target_to_own_domain"

///@}

/** @name AaTrace constants for configuration.
 */
///@{

#define AATRACE_TIMEWINDOWSIZE_DAFAULT     (0)

#define AATRACE_AGG_TIMEOUT_DEFAULT        (200)
#define AATRACE_AGG_TIMEOUT_MIN            (20)
#define AATRACE_AGG_TIMEOUT_MAX            (20000)

#define AATRACE_AGG_BUFFER_SIZE_DEFAULT    (4000)
#define AATRACE_AGG_BUFFER_SIZE_MIN        (512)
#define AATRACE_AGG_BUFFER_SIZE_MAX        (64000)

/// Due to memory limitations, separate aggregation buffer max size is defined for DSP
#define AATRACE_DSP_AGG_BUFFER_SIZE_MAX    (4000)

#define AATRACE_MAX_CLIENTS_COUNT          (4)
///@}


/** @name AaTrace defined CPIDs
 */
///@{

#define AATRACE_CONTROLLER_CPID           (0x060A)
#define AATRACE_LOG_COLLECTOR_CPID        (0x0639)

///@}

/** @name AaTrace defined but not used CPIDs
 */
///@{

#define AATRACE_ANALYZER_CPID             (0x060B)

#define AATRACE_MULTI_EE_CPID1            (0x061A)
#define AATRACE_MULTI_EE_CPID2            (0x061B)
#define AATRACE_MULTI_EE_CPID3            (0x061C)
#define AATRACE_MULTI_EE_CPID4            (0x061D)
#define AATRACE_MULTI_EE_CPID5            (0x061E)
#define AATRACE_MULTI_EE_CPID6            (0x061F)
#define AATRACE_MULTI_EE_CPID7            (0x0620)
#define AATRACE_MULTI_EE_CPID8            (0x0621)
#define AATRACE_MULTI_EE_CPID9            (0x0622)
#define AATRACE_MULTI_EE_CPID10           (0x0623)
#define AATRACE_MULTI_EE_CPID11           (0x0624)
#define AATRACE_MULTI_EE_CPID12           (0x0625)
#define AATRACE_MULTI_EE_CPID13           (0x0626)
#define AATRACE_MULTI_EE_CPID14           (0x0627)
#define AATRACE_MULTI_EE_CPID15           (0x0628)
#define AATRACE_MULTI_EE_CPID16           (0x0629)

///@}


/** AaTrace public return codes.
 */
typedef enum
{
    EAaTraceRet_Ok                = 0,  ///< No errors occurred
    EAaTraceRet_Nok               = 1,  ///< Errors occurred
    EAaTraceRet_UnknownAction     = 5,  ///< Unknown action
    EAaTraceRet_IllegalMonTarget  = 17, ///< Illegal monitor target SIC address
    EAaTraceRet_MonitorTypeNotSet = 18, ///< Monitor mode is wrong
    EAaTraceRet_IllegalMsgParams  = 19, ///< Wrong parameters
    EAaTraceRet_NoFreeSlot        = 20  ///< No avaliable free instance slot
} EAaTraceRetVal;

/** AaTrace tracing format.
 */
typedef enum
{
    EAaTraceFormat_Single     = 0, ///< One trace contain one traced message.
    EAaTraceFormat_Aggregated = 1, ///< One trace contain several traced messages.
    EAaTraceFormat_SysLog     = 2, ///< Trace to AaSysLog.
    EAaTraceFormat_NbrOf           ///< Keep always last and do not remove.
} EAaTraceFormat;



/** Used by message `AATRACE_SESSION_STATE_CHANGE_NOTIF_MSG` to notify state changing
 */
typedef enum
{
    EAaTraceSessionStateChange_Suspended = 0, ///< Session suspended.
    EAaTraceSessionStateChange_Resumed   = 1, ///< Session resumed.
    EAaTraceSessionStateChange_NbrOf          ///< Keep always last and do not remove.
} EAaTraceSessionStateChange;


/** @name Defines used in messages
 */
///@{

/** Number of filter ranges which can be configured.
 */
#define AATRACE_FILTER_RANGE_COUNT           (64)

/** Number of heavy load filters which can be configured.
 */
#define AATRACE_HEAVY_FILTER_SIZE            (8)

/** If this bit set to 1 AaTrace is in suspended mode.
 */
#define AATRACE_STATUS_SUSPENDED_MASK        (1<<0)

/** If this bit is 0 Each message traced only once.
 */
#define AATRACE_STATUS_TRACING_MODE_MASK     (1<<1)

/** Support SysCom messages to suspend/resume message tracing.
 */
#define AATRACE_FEATURE_SUSPEND_MASK         (1<<0)

/** Support of SW event tracing.
 */
#define AATRACE_FEATURE_SW_EVENTS_MASK       (1<<1)
///@}

/** Message ID filters for monitoring.
 */
typedef struct
{
    u32 msgId[AATRACE_FILTER_RANGE_COUNT * 2];   ///< Message IDs.
    u8  msgIdRange[AATRACE_FILTER_RANGE_COUNT];  /**< Message ID range:
                                                  *  0 = no range, non-zero = use range
                                                  *  1st, range between msgId[0] and msgId[1]
                                                  *  2nd, range between msgId[2] and msgId[3]
                                                  *  etc.
                                                  */
} SAaTraceMsgIdFilter;



/** Heavy loaded message filters for monitoring.
 */
typedef struct
{
    u32 msgId2[AATRACE_HEAVY_FILTER_SIZE];       ///< Frequenly repeated message IDs.
    u32 extraFilter[AATRACE_HEAVY_FILTER_SIZE];  ///< Trace only first per VALUE messages
} SAaTraceMsgIdHeavyLoadFilter;

/** @brief Monitor control message parameters.
 *  EMonitorType_None: with EMonitorMode_None stops all monitor activities,
 *  EMonitorType_ApiHeader: NMAP based monitoring, but filtering by message ID
 *                          only, no other NMAP monitoring.
 *  EMonitorType_DscBus: monitor SW events, filtering by event ID.
 *  Both of flags can also be set (EMonitorType_ApiHeader and EMonitorType_DscBus).
 *
 */
typedef struct
{
    EMonitorMode                 mode;                         ///< See EMonitorMode.h
    EMonitorType                 type;                         ///< See EMonitorType.h
    SAaTraceMsgIdFilter          sAaTraceMsgIdFilter;          ///< Trace filters
    SAaTraceMsgIdHeavyLoadFilter sAaTraceMsgIdHeavyLoadFilter; ///< Heavy load filters
    SMessageAddress              routingTarget;                ///< To where monitored message is send
    EAaTraceFormat               ifFormat;                     ///< Trace format
} SAaTraceMonCtrlParams;

typedef struct
{
  SAaTraceMonCtrlParams ctrlParams; ///< filters configuration
  TAaSysComSicad        hostSicad;  ///< assigned AaTestPort sicad
  u32                   status;     ///< AATRACE_STATUS_SUSPENDED_MASK and AATRACE_STATUS_TRACING_MODE_MASK
} SAaTraceMonStatusParams;

/** This structure contains additional information (target and sender queue ids) of traced SW event.
 */
typedef struct
{
    u32 targetQueueHi;
    u32 targetQueueLo;
    u32 senderQueueHi;
    u32 senderQueueLo;
} SAaTraceMonIndSwEventQueues;

///@}
#ifdef __cplusplus
}
#endif
#endif //_IFAATRACE_DEFS_H
