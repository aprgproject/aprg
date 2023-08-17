/**
*******************************************************************************
* @brief                 AaSysCom messages header
* @module                AaSysCom
*
* Copyright 2015 Nokia Networks. All rights reserved.
* Copyright 2019 Nokia. All rights reserved.
*******************************************************************************/

#ifndef IF_COMMON_AASYSCOM_MSGS_H
#define IF_COMMON_AASYSCOM_MSGS_H

#include <CcsCommon.h>
#include <glo_def.h>
#include <IfAaSysCom_Defs.h>
#include <TAaSysComSicad.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaSysComCommon AaSysCom Common
 * @ingroup dgAaSysCom
 * @{
 */

/** Message ID for internal communication error report. */
#ifndef AASYSCOM_ERROR_REPORT_MSG
# define AASYSCOM_ERROR_REPORT_MSG       0x0BD0  /* !- SIGNO(struct AaSysComErrorReport) -! */
#endif /* AASYSCOM_ERROR_REPORT_MSG */



/**
 * @name Message IDs in AaSysComControl.
 *
 * @{
 */
#define AASYSCOM_ECHO_ROUTE_REQ_MSG             0x0AD6    /* !- SIGNO(struct SAaSysComEchoRouteReq) -! */
#define AASYSCOM_USERS_IN_NODE_REQ_MSG          0x0AD7    /* !- SIGNO(struct SAaSysComUsersInNodeReq) -! */
#define AASYSCOM_USERS_IN_NODE_RESP_MSG         0x0AD8    /* !- SIGNO(struct SAaSysComUsersInNodeResp) -! */
#define AASYSCOM_CONTROL_SCHED_CHANGE_REQ_MSG   0x0B04    /* !- SIGNO(struct SAaSysComSchedChangeReq) -! */
#define AASYSCOM_CONTROL_SCHED_CHANGE_RESP_MSG  0x0B05    /* !- SIGNO(struct SAaSysComSchedChangeResp) -! */

#define AASYSCOM_USER_REGISTER_REQ_MSG          0x0BD1    /* !- SIGNO(struct SAaSysComUserRegisterReq) -! */
#define AASYSCOM_USER_REGISTER_RESP_MSG         0x0BD2    /* !- SIGNO(struct SAaSysComUserRegisterResp) -! */
#define AASYSCOM_USER_DEREGISTER_REQ_MSG        0x0BD3    /* !- SIGNO(struct SAaSysComUserDeregisterReq) -! */
#define AASYSCOM_USER_DEREGISTER_RESP_MSG       0x0BD4    /* !- SIGNO(struct SAaSysComUserDeregisterResp) -! */

#define AASYSCOM_HOP_REGISTER_REQ_MSG           0x0BDC  /* !- SIGNO(struct SAaSysComHopRegisterReq) -! */
#define AASYSCOM_HOP_REGISTER_RESP_MSG          0x0BDD  /* !- SIGNO(struct SAaSysComHopRegisterResp) -! */
#define AASYSCOM_HOP_DEREGISTER_REQ_MSG         0x0BDE  /* !- SIGNO(struct SAaSysComHopDeregisterReq) -! */
#define AASYSCOM_HOP_DEREGISTER_RESP_MSG        0x0BDF  /* !- SIGNO(struct SAaSysComHopDeregisterResp) -! */
/** @} */

/**
 * @name Message structures used in AaSysComControl.
 *
 * @{
 */

/**
 ********************************************************************************
 * @brief Message structure used for reporting internal communication failure.
 * @{
 * @par Description:
 * This message should be sent to applications registered for receiving
 * communication failure notifications.
 *
 * Applications can register or deregister from receiving this notification via
 * function API: AaSysComRegisterForErrors, AaSysComDeregisterForErrors.
 * Links should use function API AaSysComReportCommError for reporting detected
 * communication errors (message delivery failures) to registered applications.
 *
 * @see  AaSysComRegisterForErrors, AaSysComDeregisterForErrors,
 *       AaSysComReportCommError, ERadCcs_AaSysComCommErrNotifyDisabled
 *******************************************************************************/
typedef struct AaSysComErrorReport
{
    TAaSysComSicad reporter; /**< Communication error reporter SICAD. */
    u32 errorType; /**< Type of error. */
    u32 msgId; /**< Undelivered message ID. */
    TAaSysComSicad msgReceiver; /**< Undelivered message intended receiver. */
    TAaSysComSicad msgSender; /**< Undelivered message sender. */
    u32 msgSize; /**< Undelivered message size. */
} AaSysComErrorReport;

/** @brief SysCom Users in Node Request message structure. */
typedef struct SAaSysComUsersInNodeReq
{
    SAaSysComControlNode node; /**< nodeId */
} SAaSysComUsersInNodeReq;


/** @brief SysCom Users in Node Response message structure. */
typedef struct SAaSysComUsersInNodeResp
{
    SAaSysComControlNode node; /**< nodeId */
    u32 numOfCpIds; /**< number of CPIDs in below dynamic array */
    u32 cpId[1]; /**< dynamic array of CPIDs */
} SAaSysComUsersInNodeResp;

/** @brief SysCom Control Scheduling Change Request message structure. */
typedef struct SAaSysComSchedChangeReq
{
    /** Requested scheduler */
    ESchedulerType scheduler;
    /** Priority requested for EU. If FIFO requested must be between 0...99. If
     * (niceness) SCHED_OTHER -20...19. */
    i32 priority;
} SAaSysComSchedChangeReq;

/** @brief SysCom Control Scheduling Change Response message structure. */
typedef struct SAaSysComSchedChangeResp
{
    ESchedulerType scheduler; /**< Requested scheduler */
    i32 priority; /**< Requested priority */
    EStatus operationStatus; /**< Operation success status */
} SAaSysComSchedChangeResp;

/**
 * @brief SysCom User Register Request message structure.
 * @see AaSysComUserRegister
 */
typedef struct SAaSysComUserRegisterReq
{
    u32 cpid; /**< Specifies communication point ID to be registered. */
    u32 targetCpid; /**< Specifies target communication point ID (optional).
     If unspecified, sender's cpid is used. */
} SAaSysComUserRegisterReq;

/** @brief SysCom User Register Response message structure. */
typedef struct SAaSysComUserRegisterResp
{
    u32 cpid; /**< Copied from request. */
    u32 targetCpid; /**< Copied from request. */
    u32 registeredCpid; /**< Specifies registered communication point ID. */
    u32 status; /**< Operation success status. */
} SAaSysComUserRegisterResp;

/** @brief SysCom User Deregister Request message structure.
 *   @see   AaSysComUserDeregister
 */
typedef struct SAaSysComUserDeregisterReq
{
    u32 cpid; /**< Specifies communication point ID to be deregistered. */
} SAaSysComUserDeregisterReq;

/** @brief SysCom User Deregister Response message structure. */
typedef struct SAaSysComUserDeregisterResp
{
    u32 cpid; /**< Copied from request. */
    u32 deregisteredCpid; /**< Specifies deregistered communication point ID. */
    u32 status; /**< Operation success status. */
} SAaSysComUserDeregisterResp;

/** @brief SysCom hop register request message structure.
 *   @see   AaSysComHopRegister
 */
typedef struct SAaSysComHopRegisterReq
{
    TAaSysComSicad destinationAddress; /**< Specifies estination address for which the hop is registered. */
    u32 metric; /**< Specifies the relative preference of the hop for the destination in question. */
    TAaSysComLinkId linkId; /**< Specifies the link associated with the hop. */
} SAaSysComHopRegisterReq;

/** @brief SysCom hop register response message structure. */
typedef struct SAaSysComHopRegisterResp
{
    TAaSysComSicad destinationAddress; /**< Copied from request. */
    u32 metric; /**< Copied from request. */
    TAaSysComLinkId linkId; /**< Copied from request. */
    TAaSysComHopId hopId; /**< Identifier of the hop that was registered. Zero if register failed. */
    u32 status; /**< Status of the operation. */
} SAaSysComHopRegisterResp;

/** @brief SysCom hop deregister request message structure.
 *   @see   AaSysComHopDeregister
 */
typedef struct SAaSysComHopDeregisterReq
{
    TAaSysComHopId hopId; /**< Specifies the identifier of the hop to be deregistered. */
} SAaSysComHopDeregisterReq;

/** @brief SysCom hop deregister response message structure. */
typedef struct SAaSysComHopDeregisterResp
{
    TAaSysComHopId hopId; /**< Copied from request. */
    u32 status; /**< Status of the operation. */
} SAaSysComHopDeregisterResp;

/** @} */
/** @} end: @addtogroup dgAaSysComCommon AaSysCom Common */

#ifdef __cplusplus
}
#endif

#endif /* IF_COMMON_AASYSCOM_MSGS_H */
