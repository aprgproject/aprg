/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaSysTime message header file.
* @module                AaSysTime
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _IFAASYSTIME_MSG_H
#define _IFAASYSTIME_MSG_H
/*----------------------- LaTeX INLINE DOCUMENTATION --------------------------*/

/* -> see ccs_api_spec_body.tex */

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <glo_def.h>
#include "CcsCommon.h"
#include <IfAaSysTime_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/**
* @defgroup dgAaSysTime AaSysTime API
*
* Common Computer and Support System Time (AaSysTime) service API.
*
*/

/**
* @gAaSysTimeMsg AaSysTime Messages
* @ingroup  dgBasicSysSw
*
* System Time related messages.
*
*/

/**
* @defgroup dgAaSysTimeMsgExt AaSysTime External message API
* @ingroup  dgBasicSysSw
*
* These messages are available for application.
*
*/
/*@{*/

/** @brief AaSysTime BCN Sync message ids */
#define SYNC_NODE_REQ_MSG         0x0AA1	/* !- SIGNO(struct SSyncNodeReqMsg) -! */
#define SYNC_NODE_RESP_MSG        0x0AA2	/* !- SIGNO(struct SSyncNodeRespMsg) -! */
#define SYSTEM_TIME_SYNC_REQ_MSG  0x0A9F	/* !- SIGNO(struct SSystemTimeSyncReqMsg) -! */
#define SYSTEM_TIME_SYNC_RESP_MSG 0x0AA0	/* !- SIGNO(struct SSystemTimeSyncRespMsg) -! */


/*@}*/

typedef struct SSyncNodeReqMsg
{
  TBoolean      syncBcn;                /**< GLO_TRUE if node BCN is to be syncrhonized. GLO_FALSE if node BCN is polled */
  u32           bcnHigh;                /**< High part of the BCN valid at the next frame boundary */
  u32           bcnLow;                 /**< Low part of the BCN valid at the next frame boundary */
  SAaTime       utcTime;                /**< UTC time valid at the next frame boundary */
  u32           transactionId;          /**< To identify request and response message belonging to same procedure */
  TAaUtcZone32  utcZone;                /**< UTC time zone */
  TAaSysTime    cdmaTimeOffsetHigh;
  TAaSysTime    cdmaTimeOffsetLow;      /**< Offset for the CDMA Time to the current BCN */
  TBoolean      cdmaTimeInvalid;        /**< Indicates the CDMA time validity */
  EAaSysTimeSyncMode cdmaSyncMode;      /**< Indicates the CDMA sync mode */
  i32           cdmaPpsOffsetInNanosec; /**< Pps timing offset for async CDMA time calculation*/
} SSyncNodeReqMsg;

/** @brief Node synchronization response message. CC&S internal message */
typedef struct SSyncNodeRespMsg
{
  u32 reqRecBcnHigh;    /**< High part of the BCN at the receiving time of
                             request */
  u32 reqRecBcnLow;     /**< Low part of the BCN at the receiving time of
                             request */
  u32 respSendBcnHigh;  /**< High part of the BCN at the sending time of
                             response */
  u32 respSendBcnLow;   /**< Low part of the BCN at the sending time of
                             response */
  u32 cpuFreq;          /**< CPU frequency (clock cycles in the second) */
  EAaSysTimeNodeStatus nodeStatus;    /**< Node status info */
  EAaSysTimeNodeAppStatus appStatus;  /**< Application keep-alive status info */
  u32 transactionId;    /**< Transaction Id to identify request and response
                             message belonging to same procedure */
} SSyncNodeRespMsg;

/** @brief Synchronization request message */
typedef struct SSystemTimeSyncReqMsg
{
  TBoolean syncBcn;         /**< GLO_TRUE if node BCN is to be synchronized.
                                 GLO_FALSE if node BCN is polled */
  u32 transactionId;        /**< To identify request and response message
                                 belonging to same procedure */
  u32 targetNid;            /**< Nid address of slave node to be polled /
                                 synchronized */
} SSystemTimeSyncReqMsg;

/** @brief Synchronization response message */
typedef struct SSystemTimeSyncRespMsg
{
  EAaSysTimeNodeStatus nodeStatus;   /**< Node status info */
  EAaSysTimeNodeAppStatus appStatus; /**< application keep-alive status info */
  u32 transactionId;                 /**< To identify request and response
                                         message belonging to same procedure */
  u32 targetNid;                     /**< NID address of slave node to be
                                          polled/synchronized */
} SSystemTimeSyncRespMsg;

#ifdef __cplusplus
}
#endif

#endif /* _IFAASYSTIME_MSG_H */
