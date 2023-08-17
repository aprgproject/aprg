/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaLteTime interface header file
* @module                AaLteTime
* @owner                 Lovre Bosnjak 
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAALTETIME_H
#define _MCU_RT_IFAALTETIME_H
#include "CcsCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup dgAaLteTimeFunctionsShared Shared functions
* @ingroup dgAaLteTimeFunctions
*/

/**
* @defgroup dgAaLteTimeFunctionsSharedMcuRt Linux (shared MCU & RT) functions
* @ingroup dgAaLteTimeFunctionsShared
*/

/*@{*/

/**
*******************************************************************************
*
*   @brief      Creates timer which sends specific message with LTE BTS time.
*
*   @param[out] timerIdPtr          Pointer for the identifier of this timer.
*   @param[in]  targetSicAddress    Address of target task.
*   @param[in]  syncTo              Enumeration how to synchronize timer.
*   @param[in]  waitUntilHyperFrame A specific hyperframe value to be
*                                   synchronized.
*   @param[in]  waitUntilFrame      A specific frame value to be synchronized.
*   @param[in]  waitUntilSlot       A specific slot value to be synchronized.
*   @param[in]  waitUntilBasicTU    A specific chip value to be synchronized.
*   @param[in]  periodFrame         Frames for the periodical timer.
*   @param[in]  periodSlot          Slots for the periodical timer.
*   @param[in]  periodBasicTU       Basic time units for the periodical timer.
*
*   @return     #EAaLteTimeRetVal_NoError or
*               #EAaLteTimeRetVal_Error or
*               #EAaLteTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   This function offers a message sending after synchronization to the given
*   LTE time and after that according the given period. Synchronization is done
*   either to the beginning of next frame, subframe or slot or to the specific
*   LTE time given as parameter.  WaitUntil values are used only when
*   synchronizing to the specific LTE time.
*
*   A periodical timer is set up by setting the needed LTE time period. Setting
*   the input parameters for the period to zero a one-shot timeout is set up.
*
*   When the timeout occurs, LTE Time Services sends the
*   #AALTETIME_TIMEOUT_IND_MSG message with current LTE time information.
*
*   #DAALTETIME_VALID_NEXT_HYPERFRAME can be used as waitUntilHyperFrame
*   parameter. When used, waitUntilHyperFrame is treated as don't care and
*   timeout is triggered at next possible frame value.
*
*   @par Errors:
*   [#EAaLteTimeRetVal_Error] Internal error of LTE Time Services.
*   [#EAaLteTimeRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   Timer has to be deleted with AaLteTimerDelete() function.
*   AaLteTimermDelete() function must not be used because there is no message
*   allocated by user.
*
*   If given period is shorter (not zero) than supported accuracy or resolution
*   of the LTE Time Services in the environment,
*   #EAaLteTimeRetVal_InvalidParamValue will be returned.
*
*   The value ranges for the given specific synchronization value are:
*   Hyperframe (0-3), frame (0-1023), slot (0-19) and
*   basic time unit (0-15359). The value ranges for the given period values
*   are: Frame (0-4096), slot (0-20) and basic time unit (0-15360).
*   Maximum period is 4096 frames.
*
*   Not supported in OSEck (DSP).
*
*   Note that in MCU environment:
*   - On MCU environment only hyperframes and frames are used i.e. if only slots
*     or basicTUs are given, #EAaLteTimeRetVal_InvalidParamValue will be
*     returned. But validity of the slot and basicTU ranges are checked.
*     Exception for the before mentioned is a situation where hyperframes and
*     frames are zero and slots or basicTUs not zero and syncTo is
*     hyperframe or frame - then invalid param value is not returned.
*   - #EAaLteTimeSync_StartOfNextSlot and #EAaLteTimeSync_StartOfNextSubFrame as
*     syncTo parameter will return #EAaLteTimeRetVal_InvalidParamValue.
*   - If timeout is requested to happen in the same frame the timer is created,
*     the expiration will occur (earliest) on the next frame.
*   - Slot and basic TUs in timeout ind message are not given.
*
*   @par Example:
*   @code
*   // Synchronization to start of next frame and period one frame
*   //waitUntil values are not used because not specific LTE time
*   EAaLteTimeRetVal retval;
*   TAaLteTimerId timerId;
*
*   retval = AaLteTimermBtsTimeCreate(
*                                   &timerId,
*                                     target,
*            EAaLteTimeSync_StartOfNextFrame,
*           DAALTETIME_VALID_NEXT_HYPERFRAME, //waitUntilHyperFrame, don't care
*                                          0, //waitUntilFrame, don't care
*                                          0, //waitUntilSlot, don't care
*                                          0, //waitUntilBasicTU, don't care
*                                          1, //periodFrame
*                                          0, //periodSlot
*                                          0 ); //periodBasicTU
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*   AaLteTimerDelete(), #EAaLteTimeSync, #AaLteTimeTimeoutInd
*
*******************************************************************************/
EAaLteTimeRetVal AaLteBtsTimeTimermCreate(
    TAaLteTimerId *const timerIdPtr,
    const u32 targetSicAddress,
    const EAaLteTimeSync syncTo,
    const TAaLteBtsHyperFrameNr waitUntilHyperFrame,
    const TAaLteBtsFrameNr waitUntilFrame,
    const TAaLteBtsSlotNr waitUntilSlot,
    const TAaLteBtsBasicTUNr waitUntilBasicTU,
    const TAaLteBtsFrameNr periodFrame,
    const TAaLteBtsSlotNr periodSlot,
    const TAaLteBtsBasicTUNr periodBasicTU );

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /*  _MCU_RT_IFAALTETIME_H */

