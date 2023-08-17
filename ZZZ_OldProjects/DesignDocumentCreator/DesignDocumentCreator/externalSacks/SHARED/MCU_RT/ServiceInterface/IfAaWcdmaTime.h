/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaWcdmaTime interface header file
* @module                AaWcdmaTime
* @owner                 Lovre Bosnjak
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAAWCDMATIME_H
#define _MCU_RT_IFAAWCDMATIME_H
#include "CcsCommon.h"

#ifdef CCS_NEW_IF_STRUCTURE
#include <../../COMMON/Messages/IfAaWcdmaTime_Msg.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @defgroup dgAaWcdmaTimeApiMcu AaWcdmaTime MCU API
 * @ingroup  dgAaWcdmaTime
 */

/* @{ */


/**
*******************************************************************************
*
*   @brief      Creates timer which sends specific message with WCDMA BTS time.
*
*   @param[out] timerIdPtr          Pointer for the identifier of this timer.
*   @param[in]  targetSicAddress    Address of target task.
*   @param[in]  syncTo              Enumeration how to synchronize timer.
*   @param[in]  waitUntilFrame      A specific frame value to be synchronized.
*   @param[in]  waitUntilSlot       A specific slot value to be synchronized.
*   @param[in]  waitUntilBasicTU    A specific chip value to be synchronized.
*   @param[in]  periodFrame         Frames for the periodical timer.
*   @param[in]  periodSlot          Slots for the periodical timer.
*   @param[in]  periodBasicTU       Basic time units for the periodical timer.
*
*   @return     #EAaWcdmaTimeRetVal_NoError or
*               #EAaWcdmaTimeRetVal_Error or
*               #EAaWcdmaTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   This function offers a message sending after synchronization to the given
*   WCDMA time and after that according the given period. Synchronization is done
*   either to the beginning of next frame, subframe or slot or to the specific
*   WCDMA time given as parameter.  WaitUntil values are used only when
*   synchronizing to the specific WCDMA time.
*
*   A periodical timer is set up by setting the needed WCDMA time period. Setting
*   the input parameters for the period to zero a one-shot timeout is set up.
*
*   When the timeout occurs, WCDMA Time Services sends the
*   #AAWCDMATIME_TIMEOUT_IND_MSG message with current WCDMA time information.
*
*   @par Errors:
*   [#EAaWcdmaTimeRetVal_Error] Internal error of WCDMA Time Services.
*   [#EAaWcdmaTimeRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   Timer has to be deleted with AaWcdmaTimerDelete() function.
*   AaWcdmaTimermDelete() function must not be used because there is no message
*   allocated by user.
*
*   If given period is shorter (not zero) than supported accuracy or resolution
*   of the WCDMA Time Services in the environment,
*   #EAaWcdmaTimeRetVal_InvalidParamValue will be returned.
*
*   The value ranges for the given specific synchronization value are:
*   Frame (0-4095), slot (0-19) and
*   basic time unit (0-15359). The value ranges for the given period values
*   are: Frame (0-4096), slot (0-20) and basic time unit (0-15360).
*   Maximum period is 4096 frames.
*
*   Not supported in OSEck (DSP).
*
*   Note that in MCU environment:
*   - On MCU environment only Frames are used i.e. if only slots
*     or basicTUs are given, #EAaWcdmaTimeRetVal_InvalidParamValue will be
*     returned. But validity of the slot and basicTU ranges are checked.
*     Exception for the before mentioned is a situation where
*     frames are zero and slots or basicTUs not zero and syncTo is
*     frame - then invalid param value is not returned.
*   - #EAaWcdmaTimeSync_StartOfNextSlot and #EAaWcdmaTimeSync_StartOfNextSubFrame as
*     syncTo parameter will return #EAaWcdmaTimeRetVal_InvalidParamValue.
*   - If timeout is requested to happen in the same frame the timer is created,
*     the expiration will occur (earliest) on the next frame.
*   - Slot and basic TUs in timeout ind message are not given.
*
*   @par Example:
*   @code
*   // Synchronization to start of next frame and period one frame
*   //waitUntil values are not used because not specific WCDMA time
*   EAaWcdmaTimeRetVal retval;
*   TAaWcdmaTimerId timerId;
*
*   retval = AaWcdmaBtsTimeTimermCreate(
*                                   &timerId,
*                                     target,
*          EAaWcdmaTimeSync_StartOfNextFrame,
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
*   AaWcdmaTimerDelete(), #EAaWcdmaTimeSync, #AaWcdmaTimeTimeoutInd
*
*******************************************************************************/
EAaWcdmaTimeRetVal AaWcdmaBtsTimeTimermCreate(
    TAaWcdmaTimerId *const timerIdPtr,
    const u32 targetSicAddress,
    const EAaWcdmaTimeSync syncTo,
    const TAaWcdmaBtsFrameNr waitUntilFrame,
    const TAaWcdmaBtsSlotNr waitUntilSlot,
    const TAaWcdmaBtsBasicTUNr waitUntilBasicTU,
    const TAaWcdmaBtsFrameNr periodFrame,
    const TAaWcdmaBtsSlotNr periodSlot,
    const TAaWcdmaBtsBasicTUNr periodBasicTU );


/* @} */


#ifdef __cplusplus
}
#endif

/**@}*/

#endif /*  _MCU_RT_IFAAWCDMATIME_H */

