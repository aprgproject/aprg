/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaLteTime defintions header file
* @module                AaLteTime
*
* Copyright 2018 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _MCU_IFAALTETIME_MSG_H
#define _MCU_IFAALTETIME_MSG_H

#include <../../COMMON/Messages/IfAaLteTime_Msg.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @addtogroup dgAaLteTimeMessages
* @ingroup dgAaLteTime
*/

/**
* @defgroup dgAaLteTimeMessagesMcu MCU Messages
* @ingroup dgAaLteTimeMessages
*/

/*@{*/

/*----------------------- MESSAGES ID'S --------------------------------*/

/** CPID for AALTETIME_GET_SFN_REQ_MSG */
#define AALTETIME_SFN_SERVICE_CPID 0x062D

/** SIC message IDs for AaLteTimerGetSfn service
* @see AALTETIME_TAG_SFN_SENDER_ENABLED */
#define AALTETIME_GET_SFN_REQ_MSG       0x1F08   /* !- SIGNO(struct AaLteTimeGetSfnReq)  -! */
#define AALTETIME_GET_SFN_RESP_MSG      0x1F09   /* !- SIGNO(struct AaLteTimeGetSfnResp) -! */

/** Flags for messages for AaLteTimerGetSfn service */
#define AALTETIME_GET_SFN_FLAGS_WAIT_NEXT	0x0
#define AALTETIME_GET_SFN_FLAGS_GET_SFN   0x1

/*----------------------- MESSAGES STRUCTURES ---------------------------*/

/**   @brief SIC message struct AALTETIME_GET_SFN_REQ_MSG */
typedef struct AaLteTimeGetSfnReq
{
    u32 flags;
}AaLteTimeGetSfnReq;

/**  @brief SIC message struct for AALTETIME_GET_SFN_RESP_MSG */
typedef struct AaLteTimeGetSfnResp
{
    u32 sfn; /**< Current SFN */
    u32 ecode; /**< ecode */
}AaLteTimeGetSfnResp;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /*  _MCU_IFAALTETIME_MSG_H */
