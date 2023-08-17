/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaSysTime interface header file
* @module                AaSysTime
* @owner                 Mariusz Laczynski
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _RT_DSP_LITE_IFAALTETIME_H
#define _RT_DSP_LITE_IFAALTETIME_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup dgAaLteTimeApiDsp AaLteTime DSP API
 * @ingroup  dgAaLteTime
 */

/* @{ */

/** @brief Enumerations for the callback priority. */
typedef enum _EAaLteTimer {
    EAaLteTimer_Match,    /**< Enum. for the low callback priority. */
    EAaLteTimer_MatchMsg,
    EAaLteTimer_Sync, /**< Enum. for the medium callback priority. */
    EAaLteTimer_SyncMsg,
    EAaLteTimer_NumOfTimers /**< The number of priorities. */
}EAaLteTimer;

/** @brief LTE timer parameters */
typedef struct AaLteTimerAgrs
{
    void                  *messagePtr;
    TAaLteTimeFunctionPtr functionPtr;
    void*                 funcParamPtr;
    u32                   sizeOfparam;
}AaLteTimerAgrs;

typedef struct AaLteTimeTimerParam
{
    /* Sync create spec params */
    TAaLteBtsFrameNr      periodFrame;
    TAaLteBtsSlotNr       periodSlot;
    TAaLteBtsBasicTUNr    periodBasicTU;
    /* Match create spec params */
    EAaLteMatchLevel      matchLevel;
    /* General callback params */
    EAaLteTimePriority    priority;
    AaLteTimerAgrs timerArgs;

}AaLteTimeTimerParam;

/**
*******************************************************************************
*
*   @brief      Offers a function callback/message after synchronization to the given
*               LTE time and (optionally) after that at the given period.
*
*   @param[out] timerIdPtr          Pointer for the identifier of this timer.
*   @param[in]  waitUntilHyperFrame A specific hyper frame value to be waited.
*   @param[in]  waitUntilFrame      A specific frame value to be waited.
*   @param[in]  waitUntilSlot       A specific slot value to be waited.
*   @param[in]  waitUntilBasicTU    A specific chip value to be waited.
*   @param[in]  timer               A specific timer type.
*   @param[in]  paramPtr               Pointer for the time configuration structure.
*
*   @return     #EAaLteTimeRetVal_NoError,
*               #EAaLteTimeRetVal_Error or
*               #EAaLteTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   This function offers a function callback/message sending after
*   synchronization to the given LTE time. A periodical timer is set up by
*   setting the needed LTE time period. Setting the input parameters for the
*   period to zero a one-shot timeout is set up. LTE Time Services offers
*    four different priorities for the callback function, see #EAaLteTimePriority.
*
*   If there is a dynamically allocated memory block for the parameters of the
*   callback function for the one-shot timer, user or the callback function has
*   to release the memory pointed by the parameter pointer.
*
*   If there is a dynamically allocated memory block for the parameters of the
*   callback function and if there is a possibility, that user is going to
*   cancel that function callback timeout request (one-shot or periodic), user
*   have to take care of that pointer of the dynamically allocated memory and
*   free it, when needed.
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
*   The value ranges for the given synchronization value are:
*   Hyperframe (0-3), Frame (0-1023), slot (0-19) and
*   basic time unit (0-15359). The value ranges for the given period values
*   are: Frame (0-4096), slot (0-20) and basic time unit (0-15360). Maximum
*   period is one superframe (4096 frames).
*
*   Calling of blocking functions from given callback function is not allowed.
*   In addition, callback function must be executed very fast.
*
*   Note that in OSEck (DSP):
*   - All callbacks are executed from interrupt priority context regardless of
*     given priority.
*   - If given period is shorter (not zero) than configured TimeServices base
*     tick period, error will be returned.
*   - If non-periodic base tick, seven ticks in LTE slot
*     (1x276 + 6x274 WCDMA chips) is used as a base tick and timeout is wanted
*     for every tick, there is no need to create seven different timeouts. This
*     can be done by setting period as frame:0, slot:0 and bTU: 2194.
*
*   Note that in MCU environment:
*   - On MCU environment only hyperframes and frames are used i.e.
*     if only slots or basicTUs are given, #EAaLteTimeRetVal_InvalidParamValue
*     will be returned. But validity of the slot and basicTU ranges are checked.
*   - If timeout is requested to happen in the same frame the timer is created,
*     the expiration will occur (earliest) on the next frame.
*
*   @par Example:
*   @code
*   // Here is the usage example for this function.
*   // Sync timer witch Callback function
*   void* callbackFunction( void *param )
*   {
*       AaMemUnref(param);
*       return true;
*   }
*   // Main function
*   TAaLteTimerId timerId;
*   AaLteTimeTimerParam timerParam;
*   u32*  param = AaMemMalloc(300);
*
*   timerParam.timerArgs.functionPtr = (TAaLteTimerFunctionPtr) callbackFunction; // functionPtr
*   timerParam.timerArgs.sizeOfparam = sizeof(u32);
*   timerParam.timerArgs.funcParamPtr = param; // funcParamPtr
*   timerParam.periodBasicTU = 0;
*   timerParam.periodFrame = 0;
*   timerParam.periodSlot = 0;
*
*   if( AaLteTimerCreate(
*          &timerId,
*          DAALTETIME_VALID_NEXT_HYPERFRAME, //Valid at next possible hyperframe,
*          5, // waitUntilFrame,
*          4, // waitUntilSlots,
*          1, // waitUntilBasicTU
*          EAaLteTimer_Sync,
*          &timerParam) != EAaLteTimeRetVal_NoError )
*   {
*       //Error
*       AaMemUnref(param);
*   }
*
*   @code
*   // Sync timer witch message sending
*   TAaLteTimerId timerId;
*   AaLteTimeTimerParam timerParam;
    void *msgPtr;
*
*   timerParam.timerArgs.messagePtr = msgPtr;
*   timerParam.periodBasicTU = 0;
*   timerParam.periodFrame = 0;
*   timerParam.periodSlot = 0;
*
*   if( AaLteTimerCreate(
*          &timerId,
*          DAALTETIME_VALID_NEXT_HYPERFRAME, //Valid at next possible hyperframe,
*          5, // waitUntilFrame,
*          4, // waitUntilSlots,
*          1, // waitUntilBasicTU
*          EAaLteTimer_SyncMsg,
*          &timerParam) != EAaLteTimeRetVal_NoError )
*   {
*       //Error
*       AaMemUnref(param);
*   }
*
*   @code
*   // Match timer witch Callback function
*   void* callbackFunction( void *param )
*   {
*       AaMemUnref(param);
*       return true;
*   }
*   // Main function
*   TAaLteTimerId timerId;
*   AaLteTimeTimerParam timerParam;
*   u32*  param = AaMemMalloc(300);
*
*   timerParam.timerArgs.functionPtr = (TAaLteTimerFunctionPtr) callbackFunction; // functionPtr
*   timerParam.timerArgs.sizeOfparam = sizeof(u32);
*   timerParam.timerArgs.funcParamPtr = param; // funcParamPtr
*   timerParam.matchLevel = EAaLteMatchLevel_PeriodicSlot;
*   timerParam.priority = priority;
*
*   if( AaLteTimerCreate(
*          &timerId,
*          0, //Valid at next possible hyperframe,
*          0, // waitUntilFrame,
*          4, // waitUntilSlots,
*          0, // waitUntilBasicTU
*          EAaLteTimer_Match,
*          &timerParam) != EAaLteTimeRetVal_NoError )
*   {
*       //Error
*       AaMemUnref(param);
*   }
*
*   @code
*   // Match timer witch message sending
*   TAaLteTimerId timerId;
*   AaLteTimeTimerParam timerParam;
    void *msgPtr;
*
*   timerParam.timerArgs.messagePtr = msgPtr;
*   timerParam.matchLevel = EAaLteMatchLevel_PeriodicSlot;
*
*   if( AaLteTimerCreate(
*          &timerId,
*          0, //Valid at next possible hyperframe,
*          0, // waitUntilFrame,
*          4, // waitUntilSlots,
*          0, // waitUntilBasicTU
*          EAaLteTimer_SyncMsg,
*          &timerParam) != EAaLteTimeRetVal_NoError )
*   {
*       //Error
*       AaMemUnref(param);
*   }
*
*   return;
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
*   AaLteTimerDelete(), #EAaLteTimePriority
*
*******************************************************************************/
EAaLteTimeRetVal AaLteTimerCreate(
        TAaLteTimerId *const        timerIdPtr,
        const TAaLteBtsHyperFrameNr hyperFrame,
        const TAaLteBtsFrameNr      frame,
              TAaLteBtsSlotNr       slot,
              TAaLteBtsBasicTUNr    basicTU,
        const EAaLteTimer           timer,
        AaLteTimeTimerParam *paramPtr);

/**
*******************************************************************************
*
*   @brief      Offers a function callback/message after synchronization to the
*               given Narrow band (Nb = 60ms) LTE frame time and (optionally)
*               after that at the given period. NB frame structure is described
*               below:
*
*   NbBTU = 0 - 15359, duration of NbBTU is 195,3nSec
*   NbSlot = 0 - 19, duration of NbSlot is 15360 BTUs = 3mSec
*   NbSubframe = 0 - 9, duration of NbSubframe is 2 slots = 6mSec
*   NbFrame = 0 -1023, duration of NbFrame is 10 subframes = 60mSec
*   NbHyperframe = 0 - 3, duration of NbHyperframe is 1024 frames = 61,44Sec
*   NbSuperFrame contains 4 NbHyperframes,  4096 Nbframes, duration is 245,76sec
*
*   @param[out] nbTimerIdPtr          Pointer for the identifier of this timer.
*   @param[in]  nbHyperFrame          A specific hyper frame value to be waited.
*   @param[in]  nbFrame               A specific frame value to be waited.
*   @param[in]  nbSlot                A specific slot value to be waited.
*   @param[in]  nbBasicTU             A specific chip value to be waited.
*   @param[in]  timer                 A specific timer type.
*   @param[in]  paramPtr              Pointer for the time configuration structure.
*
*   @return     #EAaLteTimeRetVal_NoError,
*               #EAaLteTimeRetVal_Error or
*               #EAaLteTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   This API is identical to AaLteTimerCreate(), only difference is frame
*   structure which is 60ms instead of 10ms. When API is called, 10ms
*   LTE frame time is read from HW and converted to 60ms frame format.
*   Corresponding timeout time is calculated and timer triggered.
*
*   @par Errors:
*   [#EAaLteTimeRetVal_Error] Internal error of LTE Time Services.
*   [#EAaLteTimeRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The value ranges for the given synchronization value are:
*   Hyperframe (0-3), Frame (0-1023), slot (0-19) and
*   basic time unit (0-15359). The value ranges for the given period values
*   are: Frame (0-4096), slot (0-20) and basic time unit (0-15360). Maximum
*   period is one superframe (4096 frames).
*
*
*
*   @par Example:
*   see more form AaLteTimerCreate() definition.
*   return;
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
*   AaLteTimeGetNb()
*
*******************************************************************************/
EAaLteTimeRetVal AaLteTimerCreateNb(
        TAaLteTimerId *const        nbTimerIdPtr,
        const TAaLteBtsHyperFrameNr nbHyperFrame,
        const TAaLteBtsFrameNr      nbFrame,
              TAaLteBtsSlotNr       nbSlot,
              TAaLteBtsBasicTUNr    nbBasicTU,
        const EAaLteTimer           nbTimer,
        AaLteTimeTimerParam         *nbParamPtr);

/* @} */


#ifdef __cplusplus
}
#endif

/**@}*/

#endif /* _RT_DSP_LITE_IFAALTETIME_H */

