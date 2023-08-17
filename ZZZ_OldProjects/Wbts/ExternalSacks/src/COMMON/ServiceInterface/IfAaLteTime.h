/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaLteTime interface header file
* @module                AaLteTime
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _IFAALTETIME_H
#define _IFAALTETIME_H
#include "CcsCommon.h"

#ifdef CCS_NEW_IF_STRUCTURE
#include <IfAaLteTime_Defs.h>
#endif

#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup dgAaLteTime AaLteTime API
*/

/**
* @defgroup dgAaLteTimeFunctions Functions
* @ingroup dgAaLteTime
*/

/**
* @defgroup dgAaLteTimeErrors Exception codes
* @ingroup dgAaLteTime
*
* OSEck (DSP) AaLteTime implementation reports errors via local Fault Manager.
* Error codes can be found from DSP HWAPI ENV (EDspPlatErrCause.h and
* EDspPlatComp.h).
*
* Exception codes are used with Error Management Service (AaError) and they
* describe various error situations a service may have and report. Important
* part of exception is the severity. Usually it is non-fatal thus execution
* of application continues after the exception reporting but in some special
* case execution is prohibited and the application is eventually terminated.
*
*
* @ref dsVariation "[CCSAPI_VARIABILITY]"
*
* @verbatim
*  Error code:       EAaErrorCcs_AaLteTime_MemAllocFailure
*
*  Severity:         Non-fatal
*
*  Description:      Internal memory allocation failed.
*                    This is a serious error that usually causes AaLteTime to
*                    abort whatever it was trying to do.
*
*  Extra code:       None
*
*  Recovery actions: None
*
*  See:              None
* @endverbatim
*/

/**
* @defgroup dgAaLteTimeFunctionsCOMMON COMMON functions
* @ingroup dgAaLteTimeFunctions
*/

/*@{*/

/**
*******************************************************************************
*
*   @brief      Offers the current BTS LTE time
*
*   @param[out]  hyperFramePtr Pointer for the curent hyper frame of LTE time.
*   @param[out]  framePtr      Pointer for the current frame of the LTE time.
*   @param[out]  subframePtr   Pointer for the current subframe of the LTE time.
*   @param[out]  slotPtr       Pointer for the current slot of the LTE time.
*   @param[out]  basicTUPtr    Pointer for the current basic time unit of the
*                              LTE time.
*
*   @return     #EAaLteTimeRetVal_NoError,
*               #EAaLteTimeRetVal_Error or
*               #EAaLteTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   The current BTS LTE time is returned by this function. Function updates
*   variables for the current BTS frame, subframe, slot and basic time unit.
*   It is possible to fetch only one or few of offered values by using NULL to
*   the pointers of not needed values.
*
*   @par Errors:
*   [#EAaLteTimeRetVal_Error] Internal error of LTE Time Services.
*   [#EAaLteTimeRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   On MCU environment only hyperframes, frames and subframes are used i.e.
*   if only slots or basicTUs are tried to get,
*   #EAaLteTimeRetVal_InvalidParamValue will be returned.
*
*   @par Example:
*   @code
*   EAaLteTimeRetVal retval;
*   TAaLteBtsFrameNr frame;
*
*   retval = AaLteTimeGet(GLO_NULL, &frame, GLO_NULL, GLO_NULL, GLO_NULL);
*   @endcode
*
*   @par Usage:
*   None.
*
*   @par Rationale:
*   None.
*
*   @par Future directions:
*   None.
*
*   @see
*   None
*
*******************************************************************************/
EAaLteTimeRetVal AaLteTimeGet(
    TAaLteBtsHyperFrameNr *const hyperFramePtr,
    TAaLteBtsFrameNr      *const framePtr,
    TAaLteBtsSubframeNr   *const subframePtr,
    TAaLteBtsSlotNr       *const slotPtr,
    TAaLteBtsBasicTUNr    *const basicTUPtr );

/**
*******************************************************************************
*
*   @brief      Offers the current BTS LTE time with offset
*
*   @param[in]   offsetType    Type of offset.
*   @param[out]  hyperFramePtr Pointer for the current hyper frame of LTE time.
*   @param[out]  framePtr      Pointer for the current frame of the LTE time.
*   @param[out]  subframePtr   Pointer for the current subframe of the LTE time.
*   @param[out]  slotPtr       Pointer for the current slot of the LTE time.
*   @param[out]  basicTUPtr    Pointer for the current basic time unit of the
*                              LTE time.
*
*   @return     #EAaLteTimeRetVal_NoError,
*               #EAaLteTimeRetVal_Error or
*               #EAaLteTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   The current BTS LTE time with down/up/none offset is returned by this function. Function updates
*   variables for the current BTS hyperframe, frame, subframe, slot and basic time unit.
*   It is possible to fetch only one or few of offered values by using NULL to
*   the pointers of not needed values.
*
*   @par Errors:
*   [#EAaLteTimeRetVal_Error] Internal error of LTE Time Services.
*   [#EAaLteTimeRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*
*   @par Example:
*   @code
*   EAaLteTimeRetVal retval;
*
*   TAaLteBtsHyperFrameNr hyperframePtr;
*   TAaLteBtsFrameNr framePtr;
*   TAaLteBtsSubframeNr subframePtr;
*   TAaLteBtsSlotNr slotPtr;
*   TAaLteBtsBasicTUNr basicTUPtr;
*   EAaLteOffsetType offsetType = EAtOffsetType_None;

*
*   retval = AaLteTimeGetWithOffsetType(offsetType,
*                                       &hyperframePtr,
*                                       &framePtr,
*                                       &subframePtr,
*                                       &slotPtr,
*                                       &basicTUPtr);
*   @endcode
*
*   @par Usage:
*   None.
*
*   @par Rationale:
*   None.
*
*   @par Future directions:
*   None.
*
*   @see
*   None
*
*******************************************************************************/
EAaLteTimeRetVal AaLteTimeGetWithOffsetType(
    EAaLteOffsetType offsetType,
    TAaLteBtsHyperFrameNr *const hyperFramePtr,
    TAaLteBtsFrameNr *const framePtr,
    TAaLteBtsSubframeNr *const subframePtr,
    TAaLteBtsSlotNr *const slotPtr,
    TAaLteBtsBasicTUNr *const basicTUPtr );


/**
*******************************************************************************
*
*   @brief      Calculates the time since the reference time to the current
*               LTE time.
*
*   @param[in,out] refHyperFramePtr Pointer for the reference hyper frame time
*                                   and it is by return updated to current
*                                   hyper frame time.
*   @param[in,out] refFramePtr      Pointer for the reference frame time and it
*                                   is by return updated to current frame time.
*   @param[in,out] refSubframePtr   Pointer for the reference subframe time
*                                   and it is by return updated to current
*                                   subframe time.
*   @param[in,out] refSlotPtr   Pointer for the reference slot time and it is
*                               by return updated to current slot time.
*   @param[in,out] refBasicTUPtr   Pointer for the reference basic time unit
*                                  time and it is by return updated to current
*                                  basic time unit time.
*   @param[out] resultHyperFramePtr Pointer for the result hyper frame time.
*   @param[out] resultFramePtr      Pointer for the result frame time.
*   @param[out] resultSubframePtr   Pointer for the result subframe time.
*   @param[out] resultSlotPtr       Pointer for the result slot time.
*   @param[out] resultBasicTUPtr    Pointer for the result basic time unit time.
*
*   @return     #EAaLteTimeRetVal_NoError or
*               #EAaLteTimeRetVal_Error or
*               #EAaLteTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   The function calculates the time difference between the current BTS LTE
*   time and the reference time pointed to by input parameters refHyperFramePtr,
*   refFramePtr, refSubframePtr, refSlotPtr and refBasicTUPtr, which are by
*   return updated to the current BTS LTE time.
*
*   If needed accuracy for time difference is hyperFrame, only refHyperFramePtr
*   and resultHyperFramePtr must be given and all other parameters are NULL.
*
*   If needed accuracy for time difference is frame, refHyperFramePtr,
*   refFramePtr, resultHyperFramePtr and resultFramePtr must be given and all
*   other parameters are NULL.
*
*   If needed accuracy for time difference is subframe, refHyperFramePtr,
*   refFramePtr, refSubframePtr, resultHyperFramePtr, resultFramePtr and
*   resultSubframePtr must be given and all other parameters are NULL.
*
*   If needed accuracy for time difference is slot, refHyperFramePtr,
*   refFramePtr, refSubframePtr, refSlotPtr, resultHyperFramePtr,
*   resultFramePtr, resultSubframePtr and resultSlotPtr must be given and
*   basic time unit parameters are NULL.
*
*   If needed accuracy is basic time unit, none of the parameters must be NULL.
*
*   @par Errors:
*   [#EAaLteTimeRetVal_Error] Internal error of LTE Time Services.
*   [#EAaLteTimeRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   On MCU environment only hyperframes, frames and subframes are used i.e.
*   if only slots or basicTUs are tried to get,
*   #EAaLteTimeRetVal_InvalidParamValue will be returned.
*
*   @par Example:
*   @code
*   // Here is the usage example for the function.
*   // Getting time1
*   EAaLteTimeRetVal retval;
*   TAaLteBtsHyperFrameNr refHyperFrame, resultHyperFrame;
*   TAaLteBtsFrameNr refFrame, resultFrame;
*   TAaLteBtdSubframeNr refSubframe, resultSubframe;
*
*   retval = AaLteTimeGet(&refHyperFrame, &refFrame, &refSubframe,
*                         GLO_NULL, GLO_NULL);
*
*   // Calculating time since time1 and getting time2 with subframe accuracy.
*   retval = AaLteTimeSinceGet(&refHyperFrame, &refFrame, &refSubframe,
*                              GLO_NULL, GLO_NULL,
*                              resultHyperFrame, &resultFrame, &resultSubframe,
*                              GLO_NULL, GLO_NULL);
*
*   // Calculating time since time2 and getting time 3 with subframe accuracy.
*   retval = AaLteTimeSinceGet( &refHyperFrame, &refFrame, &refSubframe,
*                              GLO_NULL, GLO_NULL,
*                              resultHyperFrame, &resultFrame, &resultSubframe,
*                              GLO_NULL, GLO_NULL);
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
*   @see None
*
*******************************************************************************/
EAaLteTimeRetVal AaLteTimeSinceGet(
    TAaLteBtsHyperFrameNr *const refHyperFramePtr,
    TAaLteBtsFrameNr      *const refFramePtr,
    TAaLteBtsSubframeNr   *const refSubframePtr,
    TAaLteBtsSlotNr       *const refSlotPtr,
    TAaLteBtsBasicTUNr    *const refBasicTUPtr,
    TAaLteBtsHyperFrameNr *const resultHyperFramePtr,
    TAaLteBtsFrameNr      *const resultFramePtr,
    TAaLteBtsSubframeNr   *const resultSubframePtr,
    TAaLteBtsSlotNr       *const resultSlotPtr,
    TAaLteBtsBasicTUNr    *const resultBasicTUPtr );


/**
*******************************************************************************
*
*   @brief      Offers a function callback after the given LTE time delay.
*
*   @param[out] timerIdPtr    Pointer for the identifier of this timer.
*   @param[in]  waitFrames    Frames to be waited from moment of calling.
*   @param[in]  waitSlots     Slots to be waited from moment of calling.
*   @param[in]  waitBasicTUs  Basic time units to be waited from moment of
*                             calling.
*   @param[in]  periodFrame   Frames for the periodical timer.
*   @param[in]  periodSlot    Slots for the periodical timer.
*   @param[in]  periodBasicTU Basic time units for the periodical timer.
*   @param[in]  priority      Priority for the callback.
*   @param[in]  functionPtr   Pointer for the callback function.
*   @param[in]  funcParamPtr  Pointer for the parameters of the callback
*                             function
*   @param[in]  sizeOfparam   Size of parameters behind of funcParamPtr pointer.
*
*   @return     #EAaLteTimeRetVal_NoError,
*               #EAaLteTimeRetVal_Error or
*               #EAaLteTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   This function offers a function callback after the given LTE time latency
*   from the moment of calling this function. A periodical timer is set up by
*   setting the needed LTE time period. Setting the input parameters for the
*   period to zero a one-shot timeout is set up. LTE Time Services offers four
*   different priorities for the callback function, see #EAaLteTimePriority.
*
*   Following below description is valid only for CCS DSP Faraday hardware,
*   otherwise see @ref dgAaLteTimeCallbackParameters
*
*   If there is a dynamically allocated memory block for the parameters of the
*   callback function for the one-shot timer, user or the callback function has
*   to release the memory pointed by the parameter pointer.
*
*   If there is a dynamically allocated memory block for the parameters of the
*   callback function and if there is a possibility, that user is going to
*   cancel that function callback timeout request (one-shot or periodic),
*   user have to take care of that pointer of the dynamically allocated memory
*   and free it, when needed.
*
*   @see dgAaLteTimeCallbackParameters
*
*   @par Errors:
*   [#EAaLteTimeRetVal_Error] Internal error of LTE Time Services.
*   [#EAaLteTimeRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   Maximum latency and period is 1048576 frames and the value ranges for the
*   given latency and period are: Frame (0-1048576), slot (0-20) and basic time
*   unit (0-15360).
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
*   - Function is not supported for Keystone DSP and all RT nodes.
*
*   Note that in MCU environment:
*   - On MCU environment only hyperframes and frames are used i.e.
*     if only slots or basicTUs are given, #EAaLteTimeRetVal_InvalidParamValue
*     will be returned. But validity of the ranges is checked.
*   - If timeout is requested to happen in the same frame the timer is created,
*     the expiration will occur (earliest) on the next frame.
*
*   @par Example:
*   @code
*   //Here is the usage example for the function.
*   // Callback function
*   void* callbackFunction( void *param )
*   {
*      AaMemUnRef(&param);
*      return GLO_NULL;
*   }
*   // Main function
*   TAaLteTimerId timerId;
*   u32*  param = AaMemMalloc(300);
*
*   if( AaLteTimercCreate( &timerId,
*                                 2, // waitFrames
*                                 0, // waitSlots
*                                 0, // waitBasicTUs
*                                40, // periodFrame
*                                 0, // periodSlot
*                                 0, // periodBasicTU
*           EAaLteTimePriority_High, // priority
*   (TAaLteTimerFunctionPtr) callbackFunction, // functionPtr
*                     (void *)param, // funcParamPtr
*                                 0) // sizeOfparam
*                      != EAaLteTimeRetVal_NoError )
*   {
*    //Error
*    AaMemUnRef(&param);
*   }
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
EAaLteTimeRetVal AaLteTimercCreate(
    TAaLteTimerId *const timerIdPtr,
    const TAaLteBtsFrameNr waitFrames,
    const TAaLteBtsSlotNr waitSlots,
    const TAaLteBtsBasicTUNr waitBasicTUs,
    const TAaLteBtsFrameNr periodFrame,
    const TAaLteBtsSlotNr periodSlot,
    const TAaLteBtsBasicTUNr periodBasicTU,
    const EAaLteTimePriority priority,
    const TAaLteTimeFunctionPtr functionPtr,
    const void *const funcParamPtr,
    const u32 sizeOfparam );

/**
*******************************************************************************
*
*   @brief      Offers a function callback at the matching LTE time mask.
*
*   @param[out] timerIdPtr     Pointer for the identifier of this timer.
*   @param[in]  hyperFrameMask Hyperframe mask to be matched.
*   @param[in]  frameMask      Frame mask to be matched.
*   @param[in]  slotMask       Slot mask to be matched.
*   @param[in]  basicTUMask    Basic time unit mask to be matched.
*   @param[in]  matchLevel     Match level for time.
*   @param[in]  priority       Priority for the callback.
*   @param[in]  functionPtr    Pointer for the callback function.
*   @param[in]  funcParamPtr   Pointer for the parameters of the callback
*                              function.
*   @param[in]  sizeOfparam    Size of parameters behind of funcParamPtr
*                              pointer.
*
*   @return     #EAaLteTimeRetVal_NoError,
*               #EAaLteTimeRetVal_Error or
*               #EAaLteTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   Match timeout occurs when the given LTE time mask matches with current LTE
*   BTS time. When the match level is hyper frame, all mask values are used.
*   When the match level is frame, hyper frame mask value is not used.
*   When the match level is slot, the hyper frame and frame mask values are not
*   used. When the match level is basic time unit, the frame and slot masks are
*   not used. A periodical or one-shot timer is set up by setting the periodical
*   match level, see #EAaLteMatchLevel. LTE Time Services offers four different
*   priorities for callback function, see #EAaLteTimePriority.
*
*   Following below description is valid only for CCS DSP Faraday hardware,
*   otherwise see @ref dgAaLteTimeCallbackParameters
*
*   If there is a dynamically allocated memory block for the parameters of the
*   callback function for the one-shot timer, user or the callback function has
*   to release the memory pointed by the parameter pointer.
*
*   If there is a dynamically allocated memory block for the parameters of the
*   callback function and if there is a possibility, that user is going to
*   cancel that function callback timeout request (one-shot or periodic),
*   user have to take care of that pointer of the dynamically allocated memory
*   and free it, when needed.
*
*   @see dgAaLteTimeCallbackParameters
*
*   @par Errors:
*   [#EAaLteTimeRetVal_Error] Internal error of LTE Time Services.
*   [#EAaLteTimeRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The value ranges for the given match value are: Hyperframe (0-1023),
*   frame (0-1023), slot (0-19) and basic time unit (0-15359).
*
*   Calling of blocking functions from given callback function is not allowed.
*   In addition, callback function must be executed very fast.
*
*   Note that in OSEck (DSP):
*   - All callbacks are executed from interrupt priority context regardless of
*     given priority.
*   - Function is not supported for Keystone DSP and all RT nodes.
*
*   Note that in MCU environment:
*   - On MCU environment only hyperframes and frames are used i.e.
*     if only slot or basicTU masks are given or if match level is not based on
*     hyperframe or frame, #EAaLteTimeRetVal_InvalidParamValue will be returned.
*     But validity of the slot and basicTU ranges are checked. Exception for
*     the before mentioned is a situation where hyperframe and frame
*     masks are zero and slot or basicTU masks not zero and match level is
*     hyperframe or frame - then invalid param value is not returned.
*   - If timeout is requested to happen in the same frame the timer is created,
*     the expiration will occur (earliest) on the next frame.
*
*   @par Example:
*   @code
*   //Here is the usage example for this function.
*   //Periodic timer request at the beginning of the fifth slot (slot number 4)
*   //with high priority.  slotMask = 4, BasicTUMask = 0 and the match level
*   //is slot. Because a periodic timer is requested, the match level must be
*   //EAaLteMatchLevel_PeriodicSlot for the slot level
*
*   // Callback function
*   void* callbackFunction( void *param )
*   {
*      AaMemUnRef(&param);
*      return GLO_NULL;
*    }
*   // Main function
*   TAaLteTimerId timerId;
*   u32*  param = AaMemMalloc(300);
*
*   if(AaLteTimercMatchCreate( &timerId,
*                                     0, // hyperframeMask
*                                     0, // frameMask
*                                     4, // slotMask
*                                     0, // basicTUMask
*         EAaLteMatchLevel_PeriodicSlot, // matchLevel
*               EAaLteTimePriority_High, // priority
*     (TAaLteTimerFunctionPtr) callbackFunction, // functionPtr
*                         (void *)param, // funcParamPtr
*                                     0) // sizeOfparam
*                        != EAaLteTimeRetVal_NoError )
*   {
*       //Error
*       AaMemUnRef(&param);
*   }
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
*   AaLteTimerDelete(), #EAaLteMatchLevel, #EAaLteTimePriority
*
*******************************************************************************/
EAaLteTimeRetVal AaLteTimercMatchCreate(
    TAaLteTimerId *const timerIdPtr,
    const TAaLteBtsHyperFrameNr hyperFrameMask,
    const TAaLteBtsFrameNr frameMask,
    const TAaLteBtsSlotNr slotMask,
    const TAaLteBtsBasicTUNr basicTUMask,
    const EAaLteMatchLevel matchLevel,
    const EAaLteTimePriority priority,
    const TAaLteTimeFunctionPtr functionPtr,
    const void *const funcParamPtr,
    const u32 sizeOfparam );

/**
*******************************************************************************
*
*   @brief      Offers a function callback after synchronization to the given
*               LTE time and after that at the given period.
*
*   @param[out] timerIdPtr          Pointer for the identifier of this timer.
*   @param[in]  waitUntilHyperFrame A specific hyper frame value to be waited.
*   @param[in]  waitUntilFrame      A specific frame value to be waited.
*   @param[in]  waitUntilSlot       A specific slot value to be waited.
*   @param[in]  waitUntilBasicTU    A specific chip value to be waited.
*   @param[in]  periodFrame         Frames for the periodical timer.
*   @param[in]  periodSlot          Slots for the periodical timer.
*   @param[in]  periodBasicTU       Chips for the periodical timer.
*   @param[in]  priority            Priority for the callback.
*   @param[in]  functionPtr         Pointer for the callback function.
*   @param[in]  funcParamPtr        Pointer for the parameters of the callback
*                                   function.
*   @param[in]  sizeOfparam         Size of parameters behind of funcParamPtr
*                                   pointer.
*
*   @return     #EAaLteTimeRetVal_NoError,
*               #EAaLteTimeRetVal_Error or
*               #EAaLteTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   This function offers a function callback after synchronization to the given
*   LTE time. A periodical timer is set up by setting the needed LTE time
*   period. Setting the input parameters for the period to zero a one-shot
*   timeout is set up. LTE Time Services offers four different priorities for
*   the callback function, see #EAaLteTimePriority.
*
*   #DAALTETIME_VALID_NEXT_HYPERFRAME can be used as waitUntilHyperFrame
*   parameter. When used, waitUntilHyperFrame is treated as don't care and
*   timeout is triggered at next possible frame value.
*
*   Following below description is valid only for CCS DSP Faraday hardware,
*   otherwise see @ref dgAaLteTimeCallbackParameters
*
*   If there is a dynamically allocated memory block for the parameters of the
*   callback function for the one-shot timer, user or the callback function has
*   to release the memory pointed by the parameter pointer.
*
*   If there is a dynamically allocated memory block for the parameters of the
*   callback function and if there is a possibility, that user is going to
*   cancel that function callback timeout request (one-shot or periodic),
*   user have to take care of that pointer of the dynamically allocated memory
*   and free it, when needed.
*
*   @see dgAaLteTimeCallbackParameters
*
*   @par Errors:
*   [#EAaLteTimeRetVal_Error] Internal error of LTE Time Services.
*   [#EAaLteTimeRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The value ranges for the given synchronization value are:
*   Hyperframe (0-1023), Frame (0-1023), slot (0-19) and
*   basic time unit (0-15359). The value ranges for the given period values
*   are: Frame (0-1048576), slot (0-20) and basic time unit (0-15360). Maximum
*   period is one superframe (1048576 frames).
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
*   - Function is not supported for Keystone DSP and all RT nodes.
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
*   // Callback function
*   void* callbackFunction( void *param )
*   {
*       AaMemUnRef(&param);
*       return GLO_NULL;
*   }
*   // Main function
*   TAaLteTimerId timerId;
*   u32*  param = AaMemMalloc(300);
*
*   if( AaLteTimercSyncCreate( &timerId,
*      DAALTETIME_VALID_NEXT_HYPERFRAME, //Valid at next possible hyperframe
*                                     5, // waitUntilFrame
*                                     4, // waitUntilSlots
*                                     1, // waitUntilBasicTU
*                                     0, // periodFrame
*                                     0, // periodSlot
*                                     0, // periodBasicTU
*               EAaLteTimePriority_High, // priority
*     (TAaLteTimerFunctionPtr) callbackFunction, // functionPtr
*                         (void *)param, // funcParamPtr
*                                     0) // sizeOfparam
*                                        != EAaLteTimeRetVal_NoError )
*   {
*       //Error
*       AaMemUnRef(&param);
*   }
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
EAaLteTimeRetVal AaLteTimercSyncCreate(
    TAaLteTimerId *const timerIdPtr,
    const TAaLteBtsHyperFrameNr waitUntilHyperFrame,
    const TAaLteBtsFrameNr waitUntilFrame,
    const TAaLteBtsSlotNr waitUntilSlot,
    const TAaLteBtsBasicTUNr waitUntilBasicTU,
    const TAaLteBtsFrameNr periodFrame,
    const TAaLteBtsSlotNr periodSlot,
    const TAaLteBtsBasicTUNr periodBasicTU,
    const EAaLteTimePriority priority,
    const TAaLteTimeFunctionPtr functionPtr,
    const void *const funcParamPtr,
    const u32 sizeOfparam );

/**
*******************************************************************************
*
*   @brief      Offers a message sending after the given LTE time delay.
*
*   @param[out] timerIdPtr     Pointer for the identifier of this timer.
*   @param[in]  waitFrames     Frames to be waited from moment of calling.
*   @param[in]  waitSlots      Slots to be waited from moment of calling.
*   @param[in]  waitBasicTUs   Basic time units to be waited from moment of
*                              calling.
*   @param[in]  periodFrame    Frames for the periodical timer.
*   @param[in]  periodSlot     Slots for the periodical timer.
*   @param[in]  periodBasicTU  Basic time units for the periodical timer.
*   @param[in]  messagePtr     Pointer for the message.
*
*   @return     #EAaLteTimeRetVal_NoError,
*               #EAaLteTimeRetVal_Error or
*               #EAaLteTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   This function offers a message sending by using AaSysCom services after the
*   given LTE time latency from the moment of calling this function.
*   A periodical timer is set up by setting the needed LTE time period. Setting
*   the input parameters for the period to zero a one-shot timeout is set up.
*
*   Message has to be fulfilled and ready for the sending via AaSysCom. When
*   timeout is triggered the receiver has to release the message. For the
*   periodical timer the message is copied before every sending. For the
*   one-shot timer the message is sent to target, the receiver has to release
*    message.
*
*   When the pending one-shot or periodic timer request is cancelled, the
*   message is released by the timer deletion function (AaLteTimerDelete()) or
*   returned to user (AaLteTimermDelete()), see descriptions of the timer
*   deletion functions.
*
*   @par Errors:
*   [#EAaLteTimeRetVal_Error] Internal error of LTE Time Services.
*   [#EAaLteTimeRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   - Maximum latency and period is 1048576 frames and the value
*     ranges for the given latency and period: Frame (0-1048576), slot (0-20) and
*     basic time unit (0-15360).
*
*   Note that in OSEck (DSP):
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
*     will be returned. But validity of the ranges is checked.
*   - If timeout is requested to happen in the same frame the timer is created,
*     the expiration will occur (earliest) on the next frame.
*
*   @par Example:
*   @code
*   // Here is the usage example for the function.
*   EAaLteTimeRetVal retval;
*   TAaLteTimerId timerId;
*   void *msgPtr;
*
*   // Create AaSysCom message and fill the payload information
*
*   // A one-shot timer request after 24 frames
*   retval = AaLteTimermCreate( &timerId, 24, 0, 0, 0, 0, 0, msgPtr );
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
*   AaLteTimerDelete(), AaLteTimermDelete()
*
*******************************************************************************/
EAaLteTimeRetVal AaLteTimermCreate(
    TAaLteTimerId *const timerIdPtr,
    const TAaLteBtsFrameNr waitFrames,
    const TAaLteBtsSlotNr waitSlots,
    const TAaLteBtsBasicTUNr waitBasicTUs,
    const TAaLteBtsFrameNr periodFrame,
    const TAaLteBtsSlotNr periodSlot,
    const TAaLteBtsBasicTUNr periodBasicTU,
    const void *const messagePtr );

/**
*******************************************************************************
*
*   @brief      Offers a message sending at the matching LTE time mask.
*
*   @param[out] timerIdPtr     Pointer for the identifier of this timer.
*   @param[in]  hyperFrameMask Hyperframe mask to be matched.
*   @param[in]  frameMask      Frame mask to be matched.
*   @param[in]  slotMask       Slot mask to be matched.
*   @param[in]  basicTUMask    Basic time unit mask to be matched.
*   @param[in]  matchLevel     Match level for time.
*   @param[in]  messagePtr     Pointer for the message.
*
*   @return     #EAaLteTimeRetVal_NoError,
*               #EAaLteTimeRetVal_Error or
*               #EAaLteTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   Match timeout occurs when the LTE time mask matches with the given time
*   and according the given match level. When the match level is slot, the frame
*   mask value is not used. When the match level is chip, the frame and slot
*   masks are not used.
*
*   A periodical or one-shot timer is set up by setting the match level, see
*   #EAaLteMatchLevel.
*
*   This function offers a message sending by using AaSysCom services. Message
*   has to be fulfilled and ready for the sending via AaSysCom. When timeout is
*   triggered the receiver has to release the message. When the pending one-shot
*   or periodic timer request is cancelled, the message shall be released by the
*   timer deletion function, see descriptions of the timer deletion functions.
*
*   @par Errors:
*   [#EAaLteTimeRetVal_Error] Internal error of LTE Time Services.
*   [#EAaLteTimeRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The value ranges for the given match value are: Hyperframe (0-1023),
*   frame (0-1023), slot (0-19) and basic time unit (0-15359).
*
*   Note that in MCU environment:
*   - On MCU environment only hyperframes and frames are used i.e.
*     if only slot or basicTU masks are given or if match level is not based on
*     hyperframe or frame, #EAaLteTimeRetVal_InvalidParamValue will be returned.
*     But validity of the slot and basicTU ranges are checked. Exception for
*     the before mentioned is a situation where hyperframe and frame
*     masks are zero and slot or basicTU masks not zero and match level is
*     hyperframe or frame - then invalid param value is not returned.
*   - If timeout is requested to happen in the same frame the timer is created,
*     the expiration will occur (earliest) on the next frame.
*
*   @par Example:
*   @code
*   // Here is the usage example for the function.
*   EAaLteTimeRetVal retval;
*   TAaLteTimerId timerId;
*   void *msgPtr;
*
*   // Create AaSysCom message and fill the payload information
*
*   // Periodic timer request at the beginning of the second slot.
*   // (slotMask = 1, basicTUMask = 0), the match level is slot.
*   // Because a periodic timer is requested, the match level must be
*   // EAaLteMatchLevel_PeriodicSlot for the slot level.
*
*   retval = AaLteTimermMatchCreate( &timerId, 0, 0, 1, 0,
*                                    EAaLteMatchLevel_PeriodicSlot, msgPtr );
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
*   AaLteTimerDelete(), AaLteTimermDelete(), #EAaLteMatchLevel
*
*******************************************************************************/
EAaLteTimeRetVal AaLteTimermMatchCreate(
    TAaLteTimerId *const timerIdPtr,
    const TAaLteBtsHyperFrameNr hyperFrameMask,
    const TAaLteBtsFrameNr frameMask,
    const TAaLteBtsSlotNr slotMask,
    const TAaLteBtsBasicTUNr basicTUMask,
    const EAaLteMatchLevel matchLevel,
    const void *const messagePtr );

/**
*******************************************************************************
*
*   @brief      Offers a message sending at the given LTE time and after that
*               at the given period.
*
*   @param[out] timerIdPtr          Pointer for the identifier of this timer.
*   @param[in]  waitUntilHyperFrame A specific hyper frame value to be waited.
*   @param[in]  waitUntilFrame      A specific frame value to be synchronized.
*   @param[in]  waitUntilSlot       A specific slot value to be synchronized.
*   @param[in]  waitUntilBasicTU    A specific chip value to be synchronized.
*   @param[in]  periodFrame         Frames for the periodical timer.
*   @param[in]  periodSlot          Slots for the periodical timer.
*   @param[in]  periodBasicTU       Basic time units for the periodical timer.
*   @param[in]  messagePtr          Pointer for the message.
*
*   @return     #EAaLteTimeRetVal_NoError or
*               #EAaLteTimeRetVal_Error or
*               #EAaLteTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   This function offers a message sending after synchronization to the given
*   LTE time and after that according the given period.
*
*   A periodical timer is set up by setting the needed LTE time period. Setting
*   the input parameters for the period to zero a one-shot timeout is set up.
*
*   Message has to be fulfilled and ready for the sending via AaSysCom. When
*   timeout is triggered the receiver has to release the message. For the
*   periodical timer the message is copied before every sending. For the
*   one-shot timer the message is sent to target, the receiver has to release
*   message.
*
*   When the pending one-shot or periodic timer request is cancelled, the
*   message is released by the timer deletion function (AaLteTimerDelete()) or
*   returned to user (AaLteTimermDelete()), see descriptions of the timer
*   deletion functions.
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
*   Hyperframe (0-1023), Frame (0-1023), slot (0-19) and
*   basic time unit (0-15359). The value ranges for the given period values
*   are: Frame (0-1048576), slot (0-20) and basic time unit (0-15360). Maximum
*   period is one superframe (1048576 frames).
*
*   Note that in OSEck (DSP):
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
*   // Here is the usage example for the function.
*   TAaLteTimerId timerId;
*   void *msgPtr;
*   EAaLteTimeRetVal retval;
*
*   // Create AaSysCom message and fill the payload information.
*
*   // Timer is configured at the first hyperframe, second frame and beginning
*   // of the second slot
*   // (waitUntilHyperFrame = 0, waitUntilFrame = 1, waitUntilSlot = 1,
*   // waitUntilBasicTU = 0)
*   // Period is defined as one frame, three slots and two basic TUs
*   // (periodFrame = 1, periodSlot = 3, periodBasicTU = 0).
*
*   retval =  AaLteTimermSyncCreate(&timerId, 0, 1, 1, 0, 1, 3, 0, msgPtr);
*   @endcode
*
*   @par Usage:
*   None.
*
*   @par Rationale:
*   None.
*
*   @par Future directions:
*   None.
*
*   @see
*   AaLteTimerDelete(), AaLteTimermDelete()
*
*******************************************************************************/
EAaLteTimeRetVal AaLteTimermSyncCreate(
    TAaLteTimerId *const timerIdPtr,
    const TAaLteBtsHyperFrameNr waitUntilHyperFrame,
    const TAaLteBtsFrameNr waitUntilFrame,
    const TAaLteBtsSlotNr waitUntilSlot,
    const TAaLteBtsBasicTUNr waitUntilBasicTU,
    const TAaLteBtsFrameNr periodFrame,
    const TAaLteBtsSlotNr periodSlot,
    const TAaLteBtsBasicTUNr periodBasicTU,
    const void *const messagePtr );

/**
*******************************************************************************
*
*   @brief      Offers a LTE time based delay.
*
*   @param[in]  waitFrames     Frame interval for the sleep.
*   @param[in]  waitSlots      Slot interval for the sleep.
*   @param[in]  waitBasicTUs   Chip interval for the sleep.
*
*   @return     #EAaLteTimeRetVal_NoError,
*               #EAaLteTimeRetVal_Error or
*               #EAaLteTimeRetVal_InvalidParamValue
*
*   @par Description:
*   Blocks the caller for the duration of the given LTE time delay.
*
*   A limit has been defined for the context change. If the requested sleep
*   time is less or equal than the limit, the function reads free running timer
*   until time has been spent. If the requested sleep time is more than the
*   limit; a semaphore is set, a timer is requested to release it and the
*   control has been given to OS for a while. 64 basic time units is the limit
*   used in the definition:
*   #DAALTE_TIME_SERVICES_SLEEP_LIMIT_FOR_ CONTEXT_CHANGE.
*
*   @par Errors:
*   [#EAaLteTimeRetVal_Error] Internal error of LTE Time Services.
*   [#EAaLteTimeRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   AaLteTimeSleep() function cannot be use from interrupt routine, because
*   function uses semaphores.
*   The value ranges for the given delay are: Frame (0-1048576), slot (0-20) and
*   basic time unit (0-15360). Maximum period is 1048576 frames.
*
*   Note that in MCU environment:
*   - Always a context change, accuracy is frame. Slots and BasicTUs are
*     ignored.
*
*   @par Example:
*   @code
*   // Here is the usage example for the function.
*   // A delay for one slot and 256 basic time units.
*   EAaLteTimeRetVal retval;
*
*   retval = AaLteTimeSleep( 0, 1, 256 );
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
*   #DAALTE_TIME_SERVICES_SLEEP_LIMIT_FOR_CONTEXT_CHANGE
*
*******************************************************************************/
EAaLteTimeRetVal AaLteTimeSleep(
    const TAaLteBtsFrameNr waitFrames,
    const TAaLteBtsSlotNr waitSlots,
    const TAaLteBtsBasicTUNr waitBasicTUs );

/**
*******************************************************************************
*
*   @brief      Deletes the pending timer request.
*
*   @param[in]  timerId     The timer identifier.
*
*   @return     #EAaLteTimeRetVal_NoError or
*               #EAaLteTimeRetVal_Error
*
*   @par Description:
*   Function deletes a pending timer request according the given timer
*   identifier. If the timer is not found (e.g. one-shot timer has been
*   triggered already), the function returns an error value. If message timer
*   has elapsed, but the message is not yet handled (is in the user's message
*   queue), message is not released.
*
*   Any allocated memory blocks for the parameters of the callback are not
*   released by this function. If message timer is deleted with using this
*   method, the message is released automatically by using the method of the
*   AaSysCom.
*
*   @par Errors:
*   [#EAaLteTimeRetVal_Error] If timer not found or wrong type of timer is tried
*   to delete.
*
*   @par Restrictions:
*   Identifier of deleted timer can be reused later, when new timers are
*   created. Identifier is not reused right away, but in some phase identifier
*   may be used again.
*
*   @par Example:
*   @code
*   // Here is the usage example for the function.
*   AaLteTimerDelete( timerId );
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
*   AaLteTimermCreate(), AaLteTimermMatchCreate(), AaLteTimermSyncCreate(),
*   AaLteTimercCreate(), AaLteTimercMatchCreate(), AaLteTimercSyncCreate(),
*   AaLteBtsTimeTimermCreate(), AaLteTimermDelete()
*
*******************************************************************************/
EAaLteTimeRetVal AaLteTimerDelete(const TAaLteTimerId timerId);

/**
*******************************************************************************
*
*   @brief      Deletes a pending timer request and returns the message of the
*               timer.
*
*   @param[in]  timerId     The timer identifier.
*
*   @return     Upon successful completion, function shall return the pointer to
*               the message of the message based timeout timer. Otherwise, NULL
*               shall be returned.
*
*   @par Description:
*   Function deletes a pending timer request according the given timer
*   identifier and returns the message pointer of the message-based timer.
*   If the timer is not found (e.g. one-shot timer has been triggered already)
*   or timer was not message-based timer, the function returns a NULL value.
*
*   @par Errors:
*   [NULL] If timer not found or wrong type of timer is tried to delete.
*
*   @par Restrictions:
*   This function can be used only for the deleting a pending message-based
*   timer. Identifier of deleted timer can be reused later, when new timers are
*   created. Identifier is not reused right away, but in some phase identifier
*   may be used again.
*
*   @par Example:
*   @code
*   // Here is the usage example for the function.
*   void *msgPtr;
*   msgPtr = AaLteTimermDelete( timerId );
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
*   AaLteTimermCreate(), AaLteTimermMatchCreate(), AaLteTimermSyncCreate(),
*   AaLteTimerDelete()
*
*******************************************************************************/
void *AaLteTimermDelete (const TAaLteTimerId timerId);


/**
*******************************************************************************
*
*   @brief      Offers the current BTS Narrow Band (NB) LTE time
*
*   @param[out]  nbHyperFramePtr Pointer for the current hyper frame of LTE time.
*   @param[out]  nbFramePtr      Pointer for the current frame of the LTE time.
*   @param[out]  nbSubframePtr   Pointer for the current subframe of the LTE time.
*   @param[out]  nbSlotPtr       Pointer for the current slot of the LTE time.
*   @param[out]  nbBasicTUPtr    Pointer for the current basic time unit of the
*                                LTE time.
*
*   @return     #EAaLteTimeRetVal_NoError,
*               #EAaLteTimeRetVal_Error or
*               #EAaLteTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   The current 60ms Nb LTE frame time is returned by this function. Function
*   updates variables for the current LTE Nb frame, subframe, slot and basic
*   time unit. It is possible to fetch only one or few of offered values by
*   using NULL to the pointers of not needed values.
*   NB frame structure is described below:
*
*   NbBTU = 0 - 15359, duration of NbBTU is 195,3nSec
*   NbSlot = 0 - 19, duration of NbSlot is 15360 BTUs = 3mSec
*   NbSubframe = 0 - 9, duration of NbSubframe is 2 slots = 6mSec
*   NbFrame = 0 - 1023, duration of NbFrame is 10 subframes = 60mSec
*   NbHyperframe = 0 - 1023, duration of NbHyperframe is 1024 frames = 61.44Sec
*   NbSuperFrame contains 1024 NbHyperframes = 1048576 Nbframes = ~17.47h
*
*   @par Errors:
*   [#EAaLteTimeRetVal_Error] Internal error of LTE Time Services.
*   [#EAaLteTimeRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*
*   @par Example:
*   @code
*   EAaLteTimeRetVal retval;
*   TAaLteBtsFrameNr frame;
*
*   retval = AaLteTimeGetNb(GLO_NULL, &frame, GLO_NULL, GLO_NULL, GLO_NULL);
*   @endcode
*
*   @par Usage:
*   None.
*
*   @par Rationale:
*   None.
*
*   @par Future directions:
*   None.
*
*   @see
*   AaLteTimeGetNb()
*
*******************************************************************************/
EAaLteTimeRetVal AaLteTimeGetNb(
    TAaLteBtsHyperFrameNr *const nbHyperFramePtr,
    TAaLteBtsFrameNr      *const nbFramePtr,
    TAaLteBtsSubframeNr   *const nbSubframePtr,
    TAaLteBtsSlotNr       *const nbSlotPtr,
    TAaLteBtsBasicTUNr    *const nbBasicTUPtr);

/*@}*/

/**
 *   @defgroup dgAaLteTimeCallbackParameters Additional documentation for callback timers parameters
 *   @ingroup dgAaLteTimeFunctionsCOMMON
 *
 *   If sizeOfparam is not 0 then that amount of memory will be allocated,
 *   memory pointed by funcParamPtr will be copied into new memory block and
 *   pointer to new memory block will be passed to callback function.
 *   Memory pointed by funcParamPtr can be freed right after timer
 *   creating function returns.
 *   User is responsible for releasing memory pointed by funcParamPtr.
 *
 *   If sizeOfparam is 0 then funcParamPtr will be passed to callback function.
 *   This implies that user is not allowed to free memory pointed by
 *   funcParamPtr until oneshot timer expires or timer is cancelled.
 *   User is responsible for releasing memory pointed by funcParamPtr.
 *
 *   @par Example 1:
 *   Size of param is 0, funcParamPtr is allocated by caller on heap
 *   @code
 *   // Callback function
 *   void* callbackFunction(void *param)
 *   {
 *      doSomething(param);
 *      AaMemUnRef(&param);
 *      return GLO_NULL;
 *   }
 *   // Timer creating function
 *   void ccsUserFunction(u32 size)
 *   {
 *      TAaLteTimerId timerId;
 *      u32* param = AaMemMalloc(size*sizeof(u32));
 *      fillParams(param, size);
 *      EAaLteTimeRetVal ret = AaLteTimercCreate(&timerId, 2, 0, 0, 40, 0, 0, EAaLteTimePriority_High, (TAaLteTimerFunctionPtr) callbackFunction, (void *)param, 0);
 *      if(ret != EAaLteTimeRetVal_NoError)
 *      {
 *         //report error, cleanup and exit
 *      }
 *      doSomethingIfTimerCreated();
 *   }
 *   @endcode
 *
 *   @par Example 2:
 *   Size of param is 0, funcParamPtr is allocated by caller on stack
 *   @code
 *   // Callback function
 *   void* callbackFunction(void *param)
 *   {
 *      doSomething(param);
 *      //inform that param is no longer needed
 *      return GLO_NULL;
 *   }
 *   // Timer creating function
 *   void ccsUserFunction(u32 size)
 *   {
 *      u32 param[size];
 *      fillParams(param, size);
 *      TAaLteTimerId timerId;
 *      EAaLteTimeRetVal ret = AaLteTimercCreate(&timerId, 2, 0, 0, 40, 0, 0, EAaLteTimePriority_High, (TAaLteTimerFunctionPtr) callbackFunction, (void *)param, 0);
 *      if(ret != EAaLteTimeRetVal_NoError)
 *      {
 *          //report error, cleanup and exit
 *      }
 *      //wait for signal from callback
 *      doSomethingIfTimerCreated();
 *   }
 *   @endcode
 *
 *   @par Example 3:
 *   Size of param is not 0, funcParamPtr is allocated by caller on heap
 *   @code
 *   // Callback function
 *   void* callbackFunction(void *param)
 *   {
 *      doSomething(param);
 *      return GLO_NULL;
 *   }
 *   // Timer creating function
 *   void ccsUserFunction(u32 size)
 *   {
 *      TAaLteTimerId timerId;
 *      u32* param = AaMemMalloc(size*sizeof(u32));
 *      fillParams(param, size);
 *      EAaLteTimeRetVal ret = AaLteTimercCreate(&timerId, 2, 0, 0, 40, 0, 0, EAaLteTimePriority_High, (TAaLteTimerFunctionPtr) callbackFunction, (void *)param, size*sizeof(u32));
 *      if(ret != EAaLteTimeRetVal_NoError)
 *      {
 *          //report error, cleanup and exit
 *      }
 *      AaMemUnRef(&param);
 *      doSomethingIfTimerCreated();
 *   }
 *   @endcode
 *
 *   @par Example 4:
 *   Size of param is not 0, funcParamPtr is allocated by caller on stack
 *   @code
 *   // Callback function
 *   void* callbackFunction(void *param)
 *   {
 *      doSomething(param);
 *      return GLO_NULL;
 *   }
 *   // Timer creating function
 *   void ccsUserFunction(u32 size)
 *   {
 *      TAaLteTimerId timerId;
 *      u32 param[size];
 *      fillParams(param, size);
 *      EAaLteTimeRetVal ret = AaLteTimercCreate(&timerId, 2, 0, 0, 40, 0, 0, EAaLteTimePriority_High, (TAaLteTimerFunctionPtr) callbackFunction, (void *)param, size*sizeof(u32));
 *      if(ret != EAaLteTimeRetVal_NoError)
 *      {
 *          //report error, cleanup and exit
 *      }
 *      doSomethingIfTimerCreated();
 *   }
 *   @endcode
 *
 */

#ifdef __cplusplus
}
#endif

#endif /*  _IFAALTETIME_H */

