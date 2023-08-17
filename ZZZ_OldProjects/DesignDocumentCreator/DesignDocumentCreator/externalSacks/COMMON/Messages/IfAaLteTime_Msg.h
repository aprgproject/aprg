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
* Copyright 2014, 2018 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _IFAALTETIME_MSG_H
#define _IFAALTETIME_MSG_H
#include "CcsCommon.h"
#include <glo_def.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <IfAaLteTime_Defs.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup dgAaLteTimeMessages Messages
* @ingroup dgAaLteTime
*/

/**
* @defgroup dgAaLteTimeMessagesCommon COMMON Messages
* @ingroup dgAaLteTimeMessages
*/

/*@{*/

/*----------------------- MESSAGES ID'S --------------------------------*/

/** Message ID for AALTETIME_TIMEOUT_IND_MSG for use in
           AaLteBtsTimeTimermCreate function. */
#define AALTETIME_TIMEOUT_IND_MSG 0x08E7 	/* !- SIGNO(struct AaLteTimeTimeoutInd) -!  */

/*----------------------- MESSAGES STRUCTURES ---------------------------*/

/** @brief  Message: Timeout message sent when timer created with
            AaLteBtsTimeTimermCreate. */
typedef struct AaLteTimeTimeoutInd
{
    TAaLteBtsHyperFrameNr currentHyperframe; /**< Current hyperframe */
    TAaLteBtsFrameNr      currentFrame;      /**< Current frame */
    TAaLteBtsSubframeNr   currentSubframe;   /**< Current subframe */
    TAaLteBtsSlotNr       currentSlot;       /**< Current slot */
    TAaLteBtsBasicTUNr    currentBasicTU;    /**< Current basic time unit */
    TAaLteTimerId         timerId;           /**< timerId */
}AaLteTimeTimeoutInd;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /*  _IFAALTETIME_MSG_H */
