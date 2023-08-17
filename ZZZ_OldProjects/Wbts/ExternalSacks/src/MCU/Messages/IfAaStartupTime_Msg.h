/** @file
*   @brief Contains MCU AaStarupTime messages
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: Copyright 2018 Nokia. All rights reserved.$
*/

#ifndef _MCU_IF_AASTARTUPTIME_MSG_H_
#define _MCU_IF_AASTARTUPTIME_MSG_H_

#include <glo_def.h>
#include <CcsCommon.h>
#include <IfAaSysCom_Defs.h>
#include <../Definitions/IfAaStartupTime_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined (CCS_LITTLE_ENDIAN) && defined (CCS_BIG_ENDIAN)
  #error "Ambiguous endianness."
#elif !defined (CCS_LITTLE_ENDIAN) && !defined (CCS_BIG_ENDIAN)
  #error "No endianness defined."
#endif

/**
 * @defgroup dgAaStartupTimeMsg AaStartupTime messages
 * @ingroup dgAaStartupTime
 */

/**
 * @defgroup dgAaStartupTimeMsgMcu AaStartupTime MCU messages
 * @ingroup dgAaStartupTimeMsg
 */

/*@{*/

/** Request for list of checkpoints and their timestamps */
#define AASTARTUPTIME_CHECKPOINTS_LIST_GET_REQ_MSG 0x1533       /* !- SIGNO(struct SAaStartupTimeGetCheckpointsReq) -!  */

/** Indication message providing list of checkpoints and their timestamps */
#define AASTARTUPTIME_CHECKPOINTS_LIST_GET_IND_MSG 0x156A       /* !- SIGNO(struct SAaStartupTimeGetCheckpointsInd) -!  */

/** Response message providing summary of checkpoints and status */
#define AASTARTUPTIME_CHECKPOINTS_LIST_GET_RESP_MSG 0x1534      /* !- SIGNO(struct SAaStartupTimeGetCheckpointsResp) -!  */

/** Message provides service location and availability notification which is used by application client to locate all Startup Time services.
 * Message is published by CC&S using AaSysMb service. Requires application client subscription. */
#define AASTARTUPTIME_REGISTER_IND_MSG 0x1535                   /* !- SIGNO(struct SAaStartupRegisterInd) -!  */

/** Message notifies application client, that Startup Time service location and availability should be removed from application client database.
 * Message is published by CC&S using AaSysMb service. Requires application client subscription. */
#define AASTARTUPTIME_UNREGISTER_IND_MSG 0x1536                 /* !- SIGNO(struct SAaStartupUnregisterInd) -!  */

/**  Type describing BCN for checkpoint. Values describes BCN before synchronization ( for checkpoints reported before BCN is set in system )
 * and after BCN synchronization ( for checkpoints reported after BCN is set in system ) .*/
typedef SAaStartupU64 SAaStartupTimeBCN;

/**  Type describing monotonic counter in milliseconds. Counting from 0 since BTS startup */
typedef SAaStartupU64 SAaStartupTimeMsCounter;

/**  Structure describing data sent when CC&S notifies application client about AaStartupTime service location */
typedef struct SAaStartupRegisterInd
{
  TAaSysComSicad      sicad;                        /**< Sicad address of AaStartupTime service */
} SAaStartupRegisterInd;

/**  Structure describing data sent when CC&S notifies application client, that AaStartupTime service location should be removed from database */
typedef struct SAaStartupUnregisterInd
{
  TAaSysComSicad      sicad;                        /**< Static sicad address of AaStartupTime service */
} SAaStartupUnregisterInd;

/**  Structure describing timestamp for checkpoint occurrence */
typedef struct SAaStartupTimeTimestamp
{
  SAaStartupTimeMsCounter   msCounter;              /**< Counter in milliseconds. Counting from 0 since start */
  SAaStartupTimeBCN         bcn;                    /**< Describes BCN for checkpoint */
} SAaStartupTimeTimestamp;

/**  Structure describing checkpoint */
typedef struct SAaStartupTimeCheckpoint
{
  TAaStartupCheckpointId    checkpointId;           /**< ID describing checkpoint type */
  SAaStartupTimeTimestamp   timestamp;              /**< Describes timestamp for checkpoint occurrence */
#if defined (CCS_LITTLE_ENDIAN)
  TAaSysComNid              nodeId;                 /**< Node ID describing node where checkpoint occurred */
  u16                       attributesCount;        /**< Describes number of attributes */
#else
  u16                       attributesCount;        /**< Describes number of attributes */
  TAaSysComNid              nodeId;                 /**< Node ID describing node where checkpoint occurred */
#endif
  u32                       attributes[1];          /**< Attributes related to checkpoints */
} SAaStartupTimeCheckpoint;

/**  Structure describing checkpoints data. Contains data collected in current BTS run.
 * refBcnMsCounter struct should be used to calculate common timestamp (e.g. BCN) for checkpoints.
 * Moreover refBcnMsCounter is valid only when report is requested after BCN synchronization */
typedef struct SAaStartupTimeCheckpointsList
{
#if defined (CCS_LITTLE_ENDIAN)
  u16                       checkpointsCount;       /**< Number of checkpoints */
  u16                       padding;                /**< Padding for 32-bit alignment */
#else
  u16                       padding;                /**< Padding for 32-bit alignment */
  u16                       checkpointsCount;       /**< Number of checkpoints */
#endif
  SAaStartupTimeCheckpoint  checkpoints[1];         /**< Checkpoints data */
} SAaStartupTimeCheckpointsList;

/**  Structure used to request checkpoint data report */
typedef struct SAaStartupTimeGetCheckpointsReq
{
  u32      transactionId;                           /**< To identify request, indication and response message belonging to same procedure */
} SAaStartupTimeGetCheckpointsReq;

/**
 * @brief Structure describing checkpoints data in indication message provided from specific node
 *
 * @par Description:
 * Application receives this message as response to @ref AASTARTUPTIME_CHECKPOINTS_LIST_GET_REQ_MSG
 * CC&S provides all checkpoints data stored currently in CC&S in single report procedure.
 * If data size is bigger than maximum payload message size, then remaining data are sent via another @ref AASTARTUPTIME_CHECKPOINTS_LIST_GET_IND_MSG messages.
 * Report procedure is finished when @ref AASTARTUPTIME_CHECKPOINTS_LIST_GET_RESP_MSG message is received by application.
 *
 * @par Restrictions:
 * Not supported on FSMr2
 *
 * @par Examples:
 *
 * @code
 * #define RECEIVE_TIMEOUT 2000000
 * const u32 transactionId = 100;
 * u16 checkpointsSum = 0;
 * //  send checkpoints get request using transactionId=100
 * while(GLO_TRUE)
 * {
 *   TAaSysComMsgId msgIdFilter[] = {2, AASTARTUPTIME_CHECKPOINTS_LIST_GET_RESP_MSG
 *                                    , AASTARTUPTIME_CHECKPOINTS_LIST_GET_IND_MSG};
 *   void* msg = AaSysComMsgReceiveSelective(RECEIVE_TIMEOUT, msgIdFilter);
 *
 *   if(GLO_NULL != msg)
 *   {
 *     if(AASTARTUPTIME_CHECKPOINTS_LIST_GET_IND_MSG == AaSysComMsgGetId(msg))
 *     {
 *       SAaStartupTimeGetCheckpointsInd* getInd =
 *              (SAaStartupTimeGetCheckpointsInd*) AaSysComMsgGetPayload(msg);
 *       if(transactionId == getInd->transactionId)
 *       {
 *         TAaSysComNid node = getInd->nodeId;
 *         const SAaStartupTimeCheckpointsList* checkpointsList = &getInd->checkpointsList;
 *         checkpointsSum += checkpointsList->checkpointsCount;
 *
 *         //  get list of checkpoints
 *         const SAaStartupTimeCheckpoint* checkpoint = checkpointsList->checkpoints;
 *         for(u16 i = 0;i<checkpointsList->checkpointsCount;i++)
 *         {
 *            //  handle each checkpoint data
 *            for(u16 index = 0;index<checkpoint->attributesCount;index++)
 *            {
 *              //  handle each checkpoint attributes
 *            }
 *            checkpoint = (const SAaStartupTimeCheckpoint*)
 *                      &checkpoint->attributes[checkpoint->attributesCount];
 *         }
 *         AaSysComMsgDestroy(&msg);
 *         continue;
 *       }
 *       //  errors handling
 *     }
 *     else if(AASTARTUPTIME_CHECKPOINTS_LIST_GET_RESP_MSG == AaSysComMsgGetId(msg))
 *     {
 *       SAaStartupTimeGetCheckpointsResp* getResp =
 *             (SAaStartupTimeGetCheckpointsResp*) AaSysComMsgGetPayload(msg);
 *
 *       if(EAaStartupTimeRet_Ok == getResp->status
 *          && checkpointsSum == getResp->allCheckpointsCount
 *          && transactionId == getResp->transactionId)
 *       {
 *         //  handle rest of data
 *       }
 *       else
 *       {
 *         //  errors handling
 *       }
 *     }
 *     else
 *     {
 *       //  errors handling
 *     }
 *     AaSysComMsgDestroy(&msg);
 *     break;
 *   }
 *   else
 *   {
 *     //  errors handling
 *     break;
 *   }
 * }
 *
 * @endcode
 *
 * @par Usage:
 * Application gets this message from AaStartupTime service to provide list of checkpoints.
 *
 * @par Rationale:
 * Message allows applications to obtain list of checkpoints.
 *
 * @par Future directions:
 * None
 */
typedef struct SAaStartupTimeGetCheckpointsInd
{
  u32                               transactionId;          /**< To identify request, indication and response message belonging to same procedure */
#if defined (CCS_LITTLE_ENDIAN)
  TAaSysComNid                      nodeId;                 /**< Node ID from which checkpoints list is provided */
  u16                               padding;                /**< Padding for 32-bit alignment */
#else
  u16                               padding;                /**< Padding for 32-bit alignment */
  TAaSysComNid                      nodeId;                 /**< Node ID from which checkpoints list is provided */
#endif
  SAaStartupTimeCheckpointsList     checkpointsList;        /**< Collected checkpoints data */
} SAaStartupTimeGetCheckpointsInd;

/**
 * @brief Structure describing checkpoints data in response message for specific node ID
 *
 * @par Description:
 * Application receives this message as indication, that report procedure is finished and all CC&S data should have been delivered to application.
 * In addition message provides information about sum of all checkpoints which should have been sent via @ref AASTARTUPTIME_CHECKPOINTS_LIST_GET_IND_MSG
 * Checkpoints list is cleared inside CC&S after message is sent to application.
 *
 * @par Errors:
 * - @ref EAaStartupTimeRet_NotSupported
 * - @ref EAaStartupTimeRet_Error
 *
 * @par Restrictions:
 * Not supported on FSMr2
 *
 * @par Examples:
 * See @ref SAaStartupTimeGetCheckpointsInd
 *
 * @par Rationale:
 * Message allows applications to obtain list of checkpoints.
 *
 * @par Future directions:
 * None
 */
typedef struct SAaStartupTimeGetCheckpointsResp
{
  u32                               transactionId;          /**< To identify request, indication and response message belonging to same procedure */
  EAaStartupTimeRet                 status;                 /**< Get checkpoints status */
#if defined (CCS_LITTLE_ENDIAN)
  TAaSysComNid                      nodeId;                 /**< Node ID from which checkpoints list is provided */
  u16                               allCheckpointsCount;    /**< Number of all checkpoints which should have been provided via indication messages */
#else
  u16                               allCheckpointsCount;    /**< Number of all checkpoints which should have been provided via indication messages */
  TAaSysComNid                      nodeId;                 /**< Node ID from which checkpoints list is provided */
#endif
  SAaStartupTimeTimestamp           refBcnMsCounter;        /**< Reference time pair ( counter in milliseconds and BCN ) for checkpoint collected in current run. Collected when get response is sent to client */
} SAaStartupTimeGetCheckpointsResp;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* _MCU_IF_AASTARTUPTIME_MSG_H_ */
