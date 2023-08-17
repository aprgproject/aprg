/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaWcdmaTime messages header file
* @module                AaWcdmaTime
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _IFAAWCDMATIME_MSG_H
#define _IFAAWCDMATIME_MSG_H
#include "CcsCommon.h"
#include <glo_def.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <IfAaWcdmaTime_Defs.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

/**
*@defgroup dgAaWcdmaTimeApi Messages API
*@ingroup dgAaWcdmaTime
*
* Application Programming Interface.
*
* External Messages
*
* API specification (current): https://sharenet-ims.int.net.nokia.com/Open/D-171133
*@{*/

/*----------------------- MESSAGES ID'S --------------------------------*/

/** @brief Message ID for AAWCDMATIME_TIMEOUT_IND_MSG for use in
           AaWcdmaBtsTimeTimermCreate function. */
#define AAWCDMATIME_TIMEOUT_IND_MSG (0x0BE8) /* !- SIGNO(struct AaWcdmaTimeTimeoutInd) -!  */

/*----------------------- MESSAGES STRUCTURES ---------------------------*/

/** @brief  Message: Timeout message sent when timer created with
            AaWcdmaBtsTimeTimermCreate. */
typedef struct AaWcdmaTimeTimeoutInd
{
    TAaWcdmaBtsHyperFrameNr currentHyperframe; /**< Current hyperframe */
    TAaWcdmaBtsFrameNr      currentFrame;      /**< Current frame */
    TAaWcdmaBtsSubframeNr   currentSubframe;   /**< Current subframe */
    TAaWcdmaBtsSlotNr       currentSlot;       /**< Current slot */
    TAaWcdmaBtsBasicTUNr    currentBasicTU;    /**< Current basic time unit */
    TAaWcdmaTimerId         timerId;           /**< timerId */
}AaWcdmaTimeTimeoutInd;

#ifdef __cplusplus
}
#endif

/**@}*/

#endif /*  _IFAAWCDMATIME_MSG_H */
