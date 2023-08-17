/**
*******************************************************************************
* @file
*
* @brief                 AaWcdmaTime interface header file
*
* Copyright 2016 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _RT_DSP_IFAAWCDMATIME_H
#define _RT_DSP_IFAAWCDMATIME_H

/*----------------------- DOXYGEN GROUPS --------------------------------------*/
/**
* @addtogroup dgUpCcs U-Plane specific CC&S API
* @{
*/

/**
* @addtogroup dgUpCcsAaWcdmaTime AaWcdmaTime API
* @{
*/

/**
* @addtogroup dgUpCcsRtDspAaWcdmaTime AaWcdmaTime API for RT and OSECK DSP nodes
* @{
*/

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Enumerations for the callback priority. */
typedef enum _EAaWcdmaTimer {
    EAaWcdmaTimer_Match,    /**< Enum. for the low callback priority. */
    EAaWcdmaTimer_MatchMsg,
    EAaWcdmaTimer_Sync, /**< Enum. for the medium callback priority. */
    EAaWcdmaTimer_SyncMsg,
    EAaWcdmaTimer_NumOfTimers /**< The number of priorities. */
}EAaWcdmaTimer;

/** @brief WCDMA timer parameters */
typedef struct AaWcdmaTimerAgrs
{
    void                  *messagePtr;
    TAaWcdmaTimeFunctionPtr functionPtr;
    void*                 funcParamPtr;
    u32                   sizeOfparam;
}AaWcdmaTimerAgrs;

/** @brief  AaWCDMATimeTimerParam. */
typedef struct AaWcdmaTimeTimerParam
{
    /* Sync create spec params */
    TAaBtsFrameNr      periodFrame;
    TAaBtsSlotNr       periodSlot;
    TAaBtsChipNr    periodChip;
    /* Match create spec params */
    EAaWcdmaMatchLevel      matchLevel;
    /* General callback params */
    EAaWcdmaTimePriority    priority;
    AaWcdmaTimerAgrs timerArgs;
}AaWcdmaTimeTimerParam;

/**
*******************************************************************************
*
*   @brief      Offers the current BTS WCDMA time
*
*   @param[out]   framePtr  Pointer for the current frame of the WCDMA time
*                           (BFN).
*   @param[out]   slotPtr   Pointer for the current slot of the WCDMA time.
*   @param[out]   chipPtr   Pointer for the current chip of the WCDMA time.
*
*   @return     EAaWcdmaTimeRetVal_NoError,
*               EAaWcdmaTimeRetVal_Error or
*               EAaWcdmaTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   The current BTS WCDMA time is returned by this function. Function updates
*   variables for the current BTS frame, slot and chip. Also function can be
*   used to get one or two of offered values by setting not wanted pointers to
*   NULL.
*
*   @par Errors:
*   AaWcdmaTimeGet () function has failed if:
*   [EAaWcdmaTimeRetVal_Error] Internal timer error.
*   [EAaWcdmaTimeRetVal_InvalidParamValue] All pointers are NULL.
*
*   @par Restrictions:
*   Note that in CCS-RT this function is not supported under Event Machine
*   environment.
*
*   @par Example:
*   @code
*   // Here is the usage example for the function.
*   // Fetching the current BTS frame (BFN)
*   TAaBtsFrameNr frame;
*   AaWcdmaTimeGet( &frame, GLO_NULL, GLO_NULL );
*   @endcode
*
*   @par Usage:
*   It is possible to fetch only one or few of offered values by using NULL to
*   the pointers of not needed values.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*   AaWcdmaTimehGet
*
*******************************************************************************/
EAaWcdmaTimeRetVal AaWcdmaTimeGet(
    TAaBtsFrameNr * const framePtr,
    TAaBtsSlotNr * const slotPtr,
    TAaBtsChipNr * const chipPtr );

/**
*******************************************************************************
*
*   @brief      Offers the current BTS WCDMA time with subtimes (subframe and
*               subslot).
*
*   @param[out]  framePtr    Pointer for the current frame of the WCDMA time
*                             (BFN).
*   @param[out]  subframePtr Pointer for the current subframe of the WCDMA time.
*   @param[out]  slotPtr     Pointer for the current slot of the WCDMA time.
*   @param[out]  subslotPtr  Pointer for the current subslot of the WCDMA time.
*   @param[out]  chipPtr     Pointer for the current chip of the WCDMA time.
*
*   @return     EAaWcdmaTimeRetVal_NoError,
*               EAaWcdmaTimeRetVal_Error or
*               EAaWcdmaTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   The current time is updated to the variables pointed by the pointers of the
*   input parameters. Subframe is a 2ms frame. Subslot is 1/20 of slot.
*
*   Also function can be used to get one or few of offered values (see example).
*
*   @par Errors:
*   AaWcdmaTimehGet () function has failed if:
*   [EAaWcdmaTimeRetVal_Error] Internal timer error.
*   [EAaWcdmaTimeRetVal_InvalidParamValue] All pointers are NULL.
*
*   @par Restrictions:
*   Note that in CCS-RT this function is not supported under Event Machine
*   environment.
*
*   @par Example:
*   @code
*   TAaBtsFrameNr frame;
*   TAaBtsSubslotNr subslot;
*   AaWcdmaTimehGet( &frame, NULL, NULL, &subslot, NULL );
*   @endcode
*
*   @par Usage:
*   It is possible to fetch only one or few of offered values by using NULL to
*   the pointers of not needed values.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*   AaWcdmaTimeGet
*
*******************************************************************************/
EAaWcdmaTimeRetVal AaWcdmaTimehGet(
    TAaBtsFrameNr * const framePtr,
    TAaBtsSubframeNr * const subframePtr,
    TAaBtsSlotNr * const slotPtr,
    TAaBtsSubslotNr * const subslotPtr,
    TAaBtsChipNr * const chipPtr );

/**
*******************************************************************************
*
*   @brief   Calculates the time since the reference time to the current
*            WCDMA time including subtimes (subframe and subslot).
*
*   @param[in,out]  refFramePtr    Pointer for the reference frame time and it
*                                  is by return updated to current frame time.
*   @param[in,out]  refSubframePtr Pointer for the reference subframe time and
*                                  it is by return updated to current subframe
*                                  time.
*   @param[in,out]  refSlotPtr     Pointer for the reference slot time and it
*                                  is by return updated to current slot time.
*   @param[in,out]  refSubslotPtr  Pointer for the reference subslot time and
*                                  it is by return updated to current subslot
*                                  time.
*   @param[in,out]  refChipPtr     Pointer for the reference chip time and it
*                                  is by return updated to current chip time.
*   @param[out] resultFramePtr      Pointer for the result frame time.
*   @param[out] resultSubframePtr   Pointer for the result subframe time.
*   @param[out] resultSlotPtr       Pointer for the result slot time.
*   @param[out] resultSubslotPtr    Pointer for the result subslot time.
*   @param[out] resultChipPtr       Pointer for the result chip time.
*
*   @return     EAaWcdmaTimeRetVal_NoError,
*               EAaWcdmaTimeRetVal_Error or
*               EAaWcdmaTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   The function calculates the time difference between the current WCDMA time
*   and the reference time pointed to by input parameters refFramePtr,
*   refSubframePtr, refSlotPtr, refSubslotPtr and refChipPtr, which are by
*   return updated to the current WCDMA time.
*
*   @par Errors:
*   AaWcdmaTimehSinceGet () function has failed if:
*   [EAaWcdmaTimeRetVal_Error] Internal timer error.
*   [EAaWcdmaTimeRetVal_InvalidParamValue] All pointers are NULL.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*   // Here is the usage example for the function.
*   TAaBtsFrameNr refFrame, resultFrame;
*   TAaBtsSubframeNr refSubframe, resultSubframe;
*   TAaBtsSlotNr  refSlot, resultSlot;
*   TAaBtsSubslotNr  refSubslot, resultSubslot;
*   TAaBtsChipNr  refChip, resultChip;
*
*   //Getting time1
*   AaWcdmaTimehGet(&refFrame, &refSubframe, &refSlot, &refSubslot, &refChip);
*   ...
*   ...
*   AaWcdmaTimehSinceGet( &refFrame, &refSubframe, &refSlot, &refSubslot,
*       &refChip, &resultFrame, &resultSubframe, &resultSlot, &resultSubslot,
*       &resultChip); //Calculating time since time1 and getting time2.
*   ...
*   ...
*   AaWcdmaTimehSinceGet( &refFrame, &refSubframe, &refSlot, &refSubslot,
*       &refChip, &resultFrame, &resultSubframe, &resultSlot, &resultSubslot,
*       &resultChip); //Calculating time since time2 and getting time3.
*   @endcode
*
*   @par Usage:
*   It is possible to fetch only one or few of offered values by using NULL to
*   the pointers of not needed values.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*   AaWcdmaTimehGet, AaWcdmaTimeSinceGet
*
*******************************************************************************/
EAaWcdmaTimeRetVal AaWcdmaTimehSinceGet(
    TAaBtsFrameNr * const refFramePtr,
    TAaBtsSubframeNr * const refSubframePtr,
    TAaBtsSlotNr * const refSlotPtr,
    TAaBtsSubslotNr * const refSubslotPtr,
    TAaBtsChipNr * const refChipPtr,
    TAaBtsFrameNr * const resultFramePtr,
    TAaBtsSubframeNr * const resultSubframePtr,
    TAaBtsSlotNr * const resultSlotPtr,
    TAaBtsSubslotNr * const resultSubslotPtr,
    TAaBtsChipNr * const resultChipPtr );

/**
*******************************************************************************
*
*   @brief      Offers a function callback after the given WCDMA time delay.
*
*   @param[out] timerIdPtr   Pointer for the identifier of this timer.
*   @param[in]  waitFrames   Frames to be waited from moment of calling.
*   @param[in]  waitSlots    Slots to be waited from moment of calling.
*   @param[in]  waitChips    Chips to be waited from moment of calling.
*   @param[in]  periodFrame  Frames for the periodical timer.
*   @param[in]  periodSlot   Slots for the periodical timer.
*   @param[in]  periodChip   Chips for the periodical timer.
*   @param[in]  priority     Priority for the callback (low, medium, high).
*   @param[in]  functionPtr  Pointer for the callback function.
*   @param[in]  funcParamPtr Pointer for the parameters of the callback function
*   @param[in]  sizeOfparam  Size of parameters behind of funcParamPtr pointer.
*
*   @return     EAaWcdmaTimeRetVal_NoError,
*               EAaWcdmaTimeRetVal_Error or
*               EAaWcdmaTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   This function offers a function callback after the given WCDMA time delay.
*
*   A periodical timer is set up by setting the needed WCDMA time period.
*   Setting the input parameters for the period to zero a one-shot timeout is
*   set up.
*
*   Valid range for latency and period parameters are:
*   frame (0?096), slot (0?5) and chip (0?560).
*   Maximum latency and period time is one super frame (4096 frames).
*
*   @par Errors:
*   AaWcdmaTimercCreate() function has fail if:
*   [EAaWcdmaTimeRetVal_Error] Internal timer error.
*   [EAaWcdmaTimeRetVal_InvalidParamValue] Invalid parameter(s).
*
*   @par Restrictions:
*   Time Services will not release any possibly dynamically allocated memory for
*   the parameters of the callback function in any case (e.g. canceling the
*   request).
*
*   Calling of blocking functions from given callback function is not allowed.
*   In addition, callback function must be executed very fast.
*
*   Note that in OSEck (DSP):
*   - All callbacks are executed from interrupt priority context regardless of
*     given priority.
*   - If given period is shorter (not zero) than configured TimeServices base
*     tick period, error will be returned.
*
*   Note that in CCS-RT this function is not supported under Event Machine
*   environment.
*
*   @par Example:
*   @code
*   // Here is the usage example for the function.
*
*   // Callback function
*   void* callbackFunction( void *param )
*   {
*      ...
*      AaMemUnref(param);
*      return true;
*   }
*
*   // Main function
*   ...
*   TAaWcdmaTimerId timerId;
*   u32* param = AaMemMalloc(300);
*   EAaWcdmaTimeRetVal retVal = EAaWcdmaTimeRetVal_NoError;
*
*   if( AaWcdmaTimercCreate(
*           &timerId, // timerIdPtr
*           2,        // waitFrames
*           0,        // waitSlots
*           0,        // waitChips
*           40,       // periodFrame
*           0,        // periodSlot
*           0,        // periodChip
*           EAaWcdmaTimePriority_High,                  // priority
*          (TAaWcdmaTimerFunctionPtr) callbackFunction, // functionPtr
*          (void *)param,                               // funcParamPtr
*          sizeof(u32)                                  // sizeOfparam
*          ) != EAaWcdmaTimeRetVal_NoError )
*   {
*       retVal = EAaWcdmaTimeRetVal_NoError;
*   }
*   else
*   {
*       // Error
*   }
*
*   AaMemUnref(param);
*   return(retVal);
*
*   } // End Main
*   @endcode
*
*   @par Usage:
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
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*   AaWcdmaTimerDelete, EAaWcdmaTimePriority
*
*******************************************************************************/
EAaWcdmaTimeRetVal AaWcdmaTimercCreate(
    TAaWcdmaTimerId * const timerIdPtr,
    const TAaBtsFrameNr waitFrames,
    const TAaBtsSlotNr waitSlots,
    const TAaBtsChipNr waitChips,
    const TAaBtsFrameNr periodFrame,
    const TAaBtsSlotNr periodSlot,
    const TAaBtsChipNr periodChip,
    const EAaWcdmaTimePriority priority,
    const TAaWcdmaTimeFunctionPtr functionPtr,
    const void * const funcParamPtr,
    const u32 sizeOfparam );

/**
*******************************************************************************
*
*   @brief      Offers a function callback/message after synchronization to the
*               givenWCDMA time and (optionally) after that at the given period.
*
*   @param[out] timerIdPtr   Pointer for the identifier of this timer.
*   @param[in]  frameMask    Frame mask to be matched.
*   @param[in]  slotMask     Slot mask to be matched.
*   @param[in]  chipMask     Chip mask to be matched.
*   @param[in]  timer        A specific timer type.
*   @param[in]  paramPtr        Pointer for the time configuration structure.
*
*   @return     EAaWcdmaTimeRetVal_NoError,
*               EAaWcdmaTimeRetVal_Error,
*               EAaWcdmaTimeRetVal_InvalidParamValue or
*               EAaWcdmaTimeRetVal_NotInitialized
*
*   @par Description:
*   This function offers a function callback/message sending after synchronization
*   to the given WCDMA time. A periodical timer is set up by setting the needed
*   WCDMA time period. Setting the input parameters for the period to zero a
*   one-shot timeout is set up. WCDMA Time Services offers four different priorities
*   for the callback function, see EAaWcdmaTimePriority.
*
*   If there is a dynamically allocated memory block for the parameters of the
*   callback function for the one-shot timer, user or the callback function has to
*   release the memory pointed by the parameter pointer.
*
*   If there is a dynamically allocated memory block for the parameters of the
*   callback function and if there is a possibility, that user is going to cancel
*   that function callback timeout request (one-shot or periodic), user have to take
*   care of that pointer of the dynamically allocated memory and free it, when needed.
*
*   The value ranges for the given synchronization value are:
*   Frame (0-4096), slot (0-15) and chip (0-2560).
*
*   Maximum period time is one super frame (4096 frames).
*
*   @par Errors:
*   AaWcdmaTimercMatchCreate() function has fail if:
*   [EAaWcdmaTimeRetVal_Error] Internal timer error.
*   [EAaWcdmaTimeRetVal_InvalidParamValue] Invalid parameter(s).
*
*   @par Restrictions:
*   Time Services will not release any possibly dynamically allocated memory for
*   the parameters of the callback function in any case (e.g. canceling the
*   request).
*
*   Calling of blocking functions from given callback function is not allowed.
*   In addition, callback function must be executed very fast.
*
*   Note that in OSEck (DSP):
*   - All callbacks are executed from interrupt priority context regardless of
*     given priority.
*
*   Note that in CCS-RT this function is not supported under Event Machine
*   environment.
*
*   @par Example:
*   @code
*   // Match timer witch callback executing
*   // Here is the usage example for this function.
*   // Periodic timer request at the beginning of the fifth slot (slot number 4)
*   // with high priority.  slotMask = 4, chipMask = 0 and the match level is
*   // slot. Because a periodic timer is requested, the match level must be
*   // EAaWcdmaMatchLevel_PeriodicSlot for the slot level.
*
*   // Callback function
*   void* callbackFunction( void *param )
*   {
*       AaMemUnref(param);
*       return true;
*   }

*   // Main function
*   TAaWcdmaTimerId timerId;
*   AaWcdmaTimeTimerParam timerParam;
*   u32*  param = AaMemMalloc(300);

*   timerParam.timerArgs.functionPtr = (TAaWcdmaTimerFunctionPtr) callbackFunction; // functionPtr
*   timerParam.timerArgs.sizeOfparam = sizeof(u32);
*   timerParam.timerArgs.funcParamPtr = param; // funcParamPtr
*   timerParam.matchLevel = EAaWcdmaMatchLevel_PeriodicSlot;
*   timerParam.priority = EAaWcdmaTimePriority_High;
*
*   AaWcdmaTimerCreate(
*     &timerId,
*     0, // waitUntilFrame,
*     4, // waitUntilSlots,
*     0, // waitUntilChip
*     EAaWcdmaTimer_Match,
*     &timerParam);
*
*   AaMemUnref(param);
*   return(retVal);
*
*   // End Main
*
*   // Match timer witch message sending
*   // Here is the usage example for this function.
*   // Periodic timer request at the beginning of the fifth slot (slot number 4)
*   // with high priority.  slotMask = 4, chipMask = 0 and the match level is
*   // slot. Because a periodic timer is requested, the match level must be
*   // EAaWcdmaMatchLevel_PeriodicSlot for the slot level.
*
*   // Main function
*   TAaWcdmaTimerId timerId;
*   AaWcdmaTimeTimerParam timerParam;
*   void *msgPtr;
*
*   msgPtr = AaSysComMsgCreate( MessageId, size, recipient);
*   timerParam.timerArgs.messagePtr = msgPtr;
*   timerParam.matchLevel = EAaWcdmaMatchLevel_PeriodicSlot;
*
*   AaWcdmaTimerCreate(
*     &timerId,
*     0, // waitUntilFrame,
*     4, // waitUntilSlots,
*     0, // waitUntilChip
*     EAaWcdmaTimer_MatchMsg,
*     &timerParam);
*
*   AaMemUnref(param);
*   return(retVal);
*
*   // End Main
*
*   // Sync timer witch callback executing
*   // Here is the usage example for this function.
*   // Timer is configured to synchronized to the frame = 1, slot = 1, chip = 0
*   // (waitUntilFrame = 1, waitUntilSlot = 1, waitUntilChip = 0)
*   // Period is defined as one frame, three slots and two chips
*   // (periodFrame = 1, periodSlot = 3, periodChip = 2).
*
*   // Callback function
*   void* callbackFunction( void *param )
*   {
*       AaMemUnref(param);
*       return true;
*   }

*   // Main function
*   TAaWcdmaTimerId timerId;
*   AaWcdmaTimeTimerParam timerParam;
*   u32*  param = AaMemMalloc(300);

*   timerParam.timerArgs.functionPtr = (TAaWcdmaTimerFunctionPtr) callbackFunction; // functionPtr
*   timerParam.timerArgs.sizeOfparam = sizeof(u32);
*   timerParam.timerArgs.funcParamPtr = param; // funcParamPtr
*   timerParam.priority = EAaWcdmaTimePriority_High;
*   timerParam.periodFrame = 1;
*   timerParam.periodSlot =  3;
*   timerParam.periodChip =  2;
*
*   AaWcdmaTimerCreate(
*     &timerId,
*     1, // waitUntilFrame,
*     1, // waitUntilSlots,
*     0, // waitUntilChip
*     EAaWcdmaTimer_Sync,
*     &timerParam);
*
*   AaMemUnref(param);
*   return(retVal);
*
*   // End Main
*
*   // Sync timer witch message sending
*   // Here is the usage example for this function.
*   // Timer is configured to synchronized to the frame = 1, slot = 1, chip = 0
*   // (waitUntilFrame = 1, waitUntilSlot = 1, waitUntilChip = 0)
*   // Period is defined as one frame, three slots and two chips
*   // (periodFrame = 1, periodSlot = 3, periodChip = 2).
*
*   // Main function
*   TAaWcdmaTimerId timerId;
*   AaWcdmaTimeTimerParam timerParam;
*   void *msgPtr;
*
*   msgPtr = AaSysComMsgCreate( MessageId, size, recipient);
*   timerParam.timerArgs.messagePtr = msgPtr;
*   timerParam.periodFrame = 1;
*   timerParam.periodSlot =  3;
*   timerParam.periodChip =  2;
*
*   AaWcdmaTimerCreate(
*     &timerId,
*     1, // waitUntilFrame,
*     1, // waitUntilSlots,
*     0, // waitUntilChip
*     EAaWcdmaTimer_SyncMsg,
*     &timerParam);
*
*   AaMemUnref(param);
*   return(retVal);
*
*   // End Main
*
*   @endcode
*
*   @par Usage:
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
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*   AaWcdmaTimerDelete, EAaWcdmaMatchLevel, EAaWcdmaTimePriority, EAaWcdmaTimer,
*   AaWcdmaTimeTimerParam
*
*******************************************************************************/
EAaWcdmaTimeRetVal AaWcdmaTimerCreate(
        TAaWcdmaTimerId *const  timerIdPtr,
        const TAaBtsFrameNr     frameMask,
        const TAaBtsSlotNr      slotMask,
        const TAaBtsChipNr      chipMask,
        const EAaWcdmaTimer     timer,
        AaWcdmaTimeTimerParam   *paramPtr);

/**
*******************************************************************************
*
*   @brief      Offers a function callback at the matching WCDMA time mask.
*
*   @param[out] timerIdPtr   Pointer for the identifier of this timer.
*   @param[in]  frameMask    Frame mask to be matched.
*   @param[in]  slotMask     Slot mask to be matched.
*   @param[in]  chipMask     Chip mask to be matched.
*   @param[in]  matchLevel   Match level for time.
*   @param[in]  priority     Priority for the callback (low, medium, high).
*   @param[in]  functionPtr  Pointer for the callback function.
*   @param[in]  funcParamPtr Pointer for the parameters of the callback function
*   @param[in]  sizeOfparam  Size of parameters behind of funcParamPtr pointer.
*
*   @return     EAaWcdmaTimeRetVal_NoError,
*               EAaWcdmaTimeRetVal_Error or
*               EAaWcdmaTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   Match timeout occurs when the WCDMA time mask matches.
*
*   When the match level is slot, the frame mask value is not used. When the
*   match level is chip, the frame and slot masks are not used. A periodical or
*   one-shot timer is set up by setting the match level, see EAaWcdmaMatchLevel.
*
*   @par Errors:
*   AaWcdmaTimercMatchCreate() function has fail if:
*   [EAaWcdmaTimeRetVal_Error] Internal timer error.
*   [EAaWcdmaTimeRetVal_InvalidParamValue] Invalid parameter(s).
*
*   @par Restrictions:
*   Time Services will not release any possibly dynamically allocated memory for
*   the parameters of the callback function in any case (e.g. canceling the
*   request).
*
*   Calling of blocking functions from given callback function is not allowed.
*   In addition, callback function must be executed very fast.
*
*   Note that in OSEck (DSP):
*   - All callbacks are executed from interrupt priority context regardless of
*     given priority.
*
*   @par Example:
*   @code
*   // Here is the usage example for this function.
*   // Periodic timer request at the beginning of the fifth slot (slot number 4)
*   // with high priority.  slotMask = 4, chipMask = 0 and the match level is
*   // slot. Because a periodic timer is requested, the match level must be
*   // EAaWcdmaMatchLevel_PeriodicSlot for the slot level.
*
*   // Callback function
*   void* callbackFunction( void *param )
*   {
*       ...
*       AaMemUnref(param);
*       return true;
*   }
*
*   // Main function
*   TAaWcdmaTimerId timerId;
*   u32* param = AaMemMalloc(300);
*   EAaWcdmaTimeRetVal retVal = EAaWcdmaTimeRetVal_NoError;
*
*   if( AaWcdmaTimercMatchCreate(
*       &timerId,   // timerIdPtr
*       0,          // frameMask
*       4,          // slotMask
*       0,          // chipMask
*       EAaWcdmaMatchLevel_PeriodicSlot,             // matchLevel
*       EAaWcdmaTimePriority_High,                   // priority
*       (TAaWcdmaTimerFunctionPtr) callbackFunction, // functionPtr
*       (void *)param,                               // funcParamPtr
*       sizeof(u32)                                  // sizeOfparam
*     ) != EAaWcdmaTimeRetVal_NoError )
*   {
*       retVal = EAaWcdmaTimeRetVal_NoError;
*   }
*   else
*   {
*       // Error
*   }
*
*   AaMemUnref(param);
*   return(retVal);
*
*   } // End Main
*   @endcode
*
*   @par Usage:
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
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*   AaWcdmaTimerDelete, EAaWcdmaMatchLevel, EAaWcdmaTimePriority
*
*******************************************************************************/

EAaWcdmaTimeRetVal AaWcdmaTimercMatchCreate(
    TAaWcdmaTimerId * const timerIdPtr,
    const TAaBtsFrameNr frameMask,
    const TAaBtsSlotNr slotMask,
    const TAaBtsChipNr chipMask,
    const EAaWcdmaMatchLevel matchLevel,
    const EAaWcdmaTimePriority priority,
    const TAaWcdmaTimeFunctionPtr functionPtr,
    const void * const funcParamPtr,
    const u32 sizeOfparam );

/**
*******************************************************************************
*
*   @brief      Offers a function callback after synchronization to the given
*               WCDMA time and after that at the given period.
*
*   @param[out] timerIdPtr      Pointer for the identifier of this timer.
*   @param[in]  waitUntilFrame  A specific frame value to be waited.
*   @param[in]  waitUntilSlot   A specific slot value to be waited.
*   @param[in]  waitUntilChip   A specific chip value to be waited.
*   @param[in]  periodFrame     Frames for the periodical timer.
*   @param[in]  periodSlot      Slots for the periodical timer.
*   @param[in]  periodChip      Chips for the periodical timer.
*   @param[in]  priority        Priority for the callback (low, medium, high).
*   @param[in]  functionPtr     Pointer for the callback function.
*   @param[in]  funcParamPtr    Pointer for the parameters of the callback
*                               function.
*   @param[in]  sizeOfparam     Size of parameters behind of funcParamPtr
*                               pointer.
*
*   @return     EAaWcdmaTimeRetVal_NoError,
*               EAaWcdmaTimeRetVal_Error or
*               EAaWcdmaTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   This function offers a function callback after synchronization to the given
*   WCDMA time.
*
*   A periodical timer is set up by setting the needed WCDMA time period.
*   Setting the input parameters for the period to zero a one-shot timeout is
*   sets up.
*
*   Valid range for period parameters are:
*   frame (0?096), slot (0?5) and chip (0?560).
*   Maximum period time is one super frame (4096 frames).
*
*   @par Errors:
*   AaWcdmaTimercSyncCreate() function has fail if:
*   [EAaWcdmaTimeRetVal_Error] Internal timer error.
*   [EAaWcdmaTimeRetVal_InvalidParamValue] Invalid parameter(s).
*
*   @par Restrictions:
*   Time Services will not release any possibly dynamically allocated memory for
*   the parameters of the callback function in any case (e.g. canceling the
*   request).
*
*   Calling of blocking functions from given callback function is not allowed.
*   In addition, callback function must be executed very fast.
*
*   Note that in OSEck (DSP):
*   - All callbacks are executed from interrupt priority context regardless of
*     given priority.
*   - If given period is shorter (not zero) than configured TimeServices base
*     tick period, error will be returned.
*
*   Note that in CCS-RT this function is not supported under Event Machine
*   environment.
*
*   @par Example:
*   @code
*   // Here is the usage example for this function.
*   // Callback function
*   void* callbackFunction( void *param )
*   {
*       ...
*       AaMemUnref(param);
*       return true;
*   }
*
*   // Main function
*   TAaWcdmaTimerId timerId;
*   u32* param = AaMemMalloc(300);
*   EAaWcdmaTimeRetVal retVal = EAaWcdmaTimeRetVal_NoError;
*
*   if( AaWcdmaTimercSyncCreate(
*       &timerId,           // timerIdPtr
*       5,                  // waitUntilFrame
*       4,                  // waitUntilSlots
*       1,                  // waitUntilChips
*       0,                  // periodFrame
*       0,                  // periodSlot
*       0,                  // periodChip
*       EAaWcdmaTimePriority_High,                    // priority
*       (TAaWcdmaTimerFunctionPtr) callbackFunction,  // functionPtr
*       (void *)param,                                // funcParamPtr
*       sizeof(u32)                                   // sizeOfparam
*     ) != EAaWcdmaTimeRetVal_NoError )
*   {
*       retVal = EAaWcdmaTimeRetVal_NoError;
*   }
*   else
*   {
*       // Error
*   }
*
*   AaMemUnref(param);
*   return(retVal);
*
*   } // End Main
*   @endcode
*
*   @par Usage:
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
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*   AaWcdmaTimerDelete, EAaWcdmaTimePriority
*
*******************************************************************************/
EAaWcdmaTimeRetVal AaWcdmaTimercSyncCreate(
    TAaWcdmaTimerId *const timerIdPtr,
    const TAaBtsFrameNr waitUntilFrame,
    const TAaBtsSlotNr waitUntilSlot,
    const TAaBtsChipNr waitUntilChip,
    const TAaBtsFrameNr periodFrame,
    const TAaBtsSlotNr periodSlot,
    const TAaBtsChipNr periodChip,
    const EAaWcdmaTimePriority priority,
    const TAaWcdmaTimeFunctionPtr functionPtr,
    const void * const funcParamPtr,
    const u32 sizeOfparam );

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
*   identifier and returns the message pointer of the message-based timer. If
*   the timer is not found (e.g. one-time timer has been triggered already) or
*   timer was not message-based timer, the function returns a NULL value. If
*   timer has elapsed, but the message is not yet handled (is in the user's
*   message queue), message is not released.
*
*   @par Errors:
*   AaWcdmaTimermDelete() function has fail if:
*   - NULL has been returned. The requested timer has not been found and any
*     timers have not been deleted.
*
*   @par Restrictions:
*   This function can be used only for the deleting a pending message-based
*   timer. Identifier of deleted timer can be reused later, when new timers are
*   created. Identifier is not reused right away, but in some phase identifier
*   may be used again.
*
*   Note that in CCS-RT this function is not supported under Event Machine
*   environment.
*
*   @par Example:
*   @code
*   // Here is the usage example for the function.
*   void *msgPtr;
*   msgPtr = AaWcdmaTimermDelete( timerId );
*   @endcode
*
*   @par Usage:
*   Any allocated memory blocks for the parameters of the callback or recovery
*   function are not released by this function.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*   AaWcdmaTimermCreate, AaWcdmaTimermMatchCreate, AaWcdmaTimermSyncCreate,
*   AaWcdmaTimercCreate, AaWcdmaTimercMatchCreate, AaWcdmaTimercSyncCreate,
*   AaWcdmaTimermDelete
*
*******************************************************************************/
void *AaWcdmaTimermDelete (const TAaWcdmaTimerId timerId);

/**
*******************************************************************************
*
*   @brief      Offers a message sending after the given WCDMA time delay.
*
*   @param[out] timerIdPtr  Pointer for the identifier of this timer.
*   @param[in]  waitFrames  Frames to be waited from moment of calling.
*   @param[in]  waitSlots   Slots to be waited from moment of calling.
*   @param[in]  waitChips   Chips to be waited from moment of calling.
*   @param[in]  periodFrame Frames for the periodical timer.
*   @param[in]  periodSlot  Slots for the periodical timer.
*   @param[in]  periodChip  Chips for the periodical timer.
*   @param[in]  messagePtr  Pointer for the message.
*
*   @return     EAaWcdmaTimeRetVal_NoError,
*               EAaWcdmaTimeRetVal_Error or
*               EAaWcdmaTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   This function offers a message sending by using AaSysCom services after the
*   given WCDMA time delay.
*
*   A periodical timer is set up by setting the needed WCDMA time period.
*   Setting the input parameters for the period to zero a one-shot timeout is
*   set up.
*
*   Message has to be fulfilled and ready for the sending via AaSysCom. When
*   timeout is triggered the receiver has to release the message. When the
*   pending one-shot or periodic timer request is cancelled, the message shall
*   be released by the timer deletion function, see descriptions of the timer
*   deletion functions.
*
*   Valid range for latency and period parameters are:
*   frame (0?096), slot (0?5) and chip (0?560).
*   Maximum latency and period time is one super frame (4096 frames).
*
*   @par Errors:
*   AaWcdmaTimermCreate() function has fail if:
*   [EAaWcdmaTimeRetVal_Error] Internal timer error.
*   [EAaWcdmaTimeRetVal_InvalidParamValue] Invalid parameter(s).
*
*   @par Restrictions:
*   Note that in OSEck (DSP):
*   - If given period is shorter (not zero) than configured TimeServices base
*     tick period, error will be returned.
*
*   @par Example:
*   @code
*   TAaWcdmaTimerId timerId;
*   void *msgPtr;
*
*   msgPtr = AaSysComMsgCreate( myMsgId, myMsgSize, myMsgReceiver );
*
*   // A one-shot timer request after 24 frames.
*   AaWcdmaTimermCreate( &timerId, 24, 0, 0, 0, 0, 0, msgPtr );
*
*   @endcode
*
*   @par Usage:
*   For the periodical timer the message is copied before every sending. When
*   the timer is canceled with AaWcdmaTimerDelete function, the original message
*   is released by WCDMA Time Services using the SysCom component. For the
*   one-shot timer the message is sent to target, the receiver has to release
*   message.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*   AaWcdmaTimerDelete, AaWcdmaTimermDelete
*
*******************************************************************************/

EAaWcdmaTimeRetVal AaWcdmaTimermCreate(
    TAaWcdmaTimerId *const timerIdPtr,
    const TAaBtsFrameNr waitFrames,
    const TAaBtsSlotNr waitSlots,
    const TAaBtsChipNr waitChips,
    const TAaBtsFrameNr periodFrame,
    const TAaBtsSlotNr periodSlot,
    const TAaBtsChipNr periodChip,
    const void * const messagePtr );

/**
*******************************************************************************
*
*   @brief      Offers a message sending at the matching WCDMA time mask.
*
*   @param[out] timerIdPtr  Pointer for the identifier of this timer.
*   @param[in]  frameMask   Frame mask to be matched.
*   @param[in]  slotMask    Slot mask to be matched.
*   @param[in]  chipMask    Chip mask to be matched.
*   @param[in]  matchLevel  Match level for time.
*   @param[in]  messagePtr  Pointer for the message.
*
*   @return     EAaWcdmaTimeRetVal_NoError,
*               EAaWcdmaTimeRetVal_Error or
*               EAaWcdmaTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   Match timeout occurs when the WCDMA time mask matches with the given time
*   and according the given match level. When the match level is slot, the frame
*   mask value is not used. When the match level is chip, the frame and slot
*   masks are not used.
*
*   A periodical or one-shot timer is set up by setting the match level, see
*   EAaWcdmaMatchLevel.
*
*   This function offers a message sending by using AaSysCom services. Message
*   has to be fulfilled and ready for the sending via AaSysCom. When timeout is
*   triggered the receiver has to release the message. When the pending one-shot
*   or periodic timer request is cancelled, the message shall be released by the
*   timer deletion function, see descriptions of the timer deletion functions.
*
*   @par Errors:
*   AaWcdmaTimermMatchCreate() function has fail if:
*   [EAaWcdmaTimeRetVal_Error] Internal timer error.
*   [EAaWcdmaTimeRetVal_InvalidParamValue] Invalid parameter(s).
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*   TAaWcdmaTimerId timerId;
*   void *msgPtr;
*
*   msgPtr = AaSysComMsgCreate( myMsgId, myMsgSize, myMsgReceiver );
*
*   // Periodic timer request at the beginning of the second slot.
*   // (slotMask = 1, chipMask = 0), the match level is slot.
*   // Because a periodic timer is requested, the match level must be
*   // EAaWcdmaMatchLevel_PeriodicSlot for the slot level.
*   AaWcdmaTimermMatchCreate( &timerId, 0, 1, 0,
*       EAaWcdmaMatchLevel_PeriodicSlot, msgPtr );
*   @endcode
*
*   @par Usage:
*   For the periodical timer the message is copied before every sending. When
*   the timer is canceled with AaWcdmaTimerDelete function, the original message
*   is released by WCDMA Time Services using the SysCom component. For the
*   one-shot timer the message is sent to target, the receiver has to release
*   message.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*   AaWcdmaTimerDelete, AaWcdmaTimermDelete, EAaWcdmaMatchLevel
*
*******************************************************************************/
EAaWcdmaTimeRetVal AaWcdmaTimermMatchCreate(
    TAaWcdmaTimerId *const timerIdPtr,
    const TAaBtsFrameNr frameMask,
    const TAaBtsSlotNr slotMask,
    const TAaBtsChipNr chipMask,
    const EAaWcdmaMatchLevel matchLevel,
    const void * const messagePtr );

/**
*******************************************************************************
*
*   @brief      Offers a message sending at the given WCDMA time and after that
*               at the given period.
*
*   @param[out] timerIdPtr      Pointer for the identifier of this timer.
*   @param[in]  waitUntilFrame  A specific frame value to be synchronized.
*   @param[in]  waitUntilSlot   A specific slot value to be synchronized.
*   @param[in]  waitUntilChip   A specific chip value to be synchronized.
*   @param[in]  periodFrame     Frames for the periodical timer.
*   @param[in]  periodSlot      Slots for the periodical timer.
*   @param[in]  periodChip      Chips for the periodical timer.
*   @param[in]  messagePtr      Pointer for the message.
*
*   @return     EAaWcdmaTimeRetVal_NoError,
*               EAaWcdmaTimeRetVal_Error or
*               EAaWcdmaTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   This function offers a message sending after synchronization to the given
*   WCDMA time and after that according the given period.
*
*   A periodical timer is set up by setting the needed WCDMA time period.
*   Setting the input parameters for the period to zero a one-shot timeout is
*   set up.
*
*   This function offers a message sending by using AaSysCom services. Message
*   has to be fulfilled and ready for the sending via AaSysCom. When timeout is
*   triggered the receiver has to release the message. When the pending one-shot
*   or periodic timer request is cancelled, the message shall be released by the
*   timer deletion function, see descriptions of the timer deletion functions.
*
*   Valid range for period parameters are:
*   frame (0?096), slot (0?5) and chip (0?560).
*   Maximum period time is one super frame (4096 frames).
*
*   @par Errors:
*   AaWcdmaTimermSyncCreate() function has fail if:
*   [EAaWcdmaTimeRetVal_Error] Internal timer error.
*   [EAaWcdmaTimeRetVal_InvalidParamValue] Invalid parameters.
*
*   @par Restrictions:
*   Note that in OSEck (DSP):
*   - If given period is shorter (not zero) than configured TimeServices base
*     tick period, error will be returned.
*
*   @par Example:
*   @code
*   TAaWcdmaTimerId timerId;
*   void *msgPtr;
*
*   msgPtr = AaSysComMsgCreate( myMsgId, myMsgSize, myMsgReceiver );
*
*   // Timer is configured to synchronized to the frame = 1, slot = 1, chip = 0
*   // (waitUntilFrame = 1, waitUntilSlot = 1, waitUntilChip = 0)
*   // Period is defined as one frame, three slots and two chips
*   // (periodFrame = 1, periodSlot = 3, periodChip = 2).
*   AaWcdmaTimermSyncCreate( &timerId, 1, 1, 0, 1, 3, 2, msgPtr );
*   @endcode
*
*   @par Usage:
*   For the periodical timer the message is copied before every sending. When
*   the timer is canceled with AaWcdmaTimerDelete function, the original message
*   is released by WCDMA Time Services using the SysCom component. For the
*   one-shot timer the message is sent to target, the receiver has to release
*   message.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*   AaWcdmaTimerDelete, AaWcdmaTimermDelete
*
*******************************************************************************/
EAaWcdmaTimeRetVal AaWcdmaTimermSyncCreate(
    TAaWcdmaTimerId * const timerIdPtr,
    const TAaBtsFrameNr waitUntilFrame,
    const TAaBtsSlotNr waitUntilSlot,
    const TAaBtsChipNr waitUntilChip,
    const TAaBtsFrameNr periodFrame,
    const TAaBtsSlotNr periodSlot,
    const TAaBtsChipNr periodChip,
    const void * const messagePtr );

/**
*******************************************************************************
*
*   @brief      Calculates the time since the reference time to the current
*               WCDMA time.
*
*   @param[in,out] refFramePtr  Pointer for the reference frame time and it is
*                               by return updated to current frame time.
*   @param[in,out] refSlotPtr   Pointer for the reference slot time and it is
*                               by return updated to current slot time.
*   @param[in,out] refChipPtr   Pointer for the reference chip time and it is
*                               by return updated to current chip time.
*   @param[out]    resultFramePtr  Pointer for the result frame time.
*   @param[out]    resultSlotPtr   Pointer for the result slot time.
*   @param[out]    resultChipPtr   Pointer for the result chip time.
*
*   @return     EAaWcdmaTimeRetVal_NoError,
*               EAaWcdmaTimeRetVal_Error or
*               EAaWcdmaTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   The function calculates the time difference between the current BTS WCDMA
*   time and the reference time pointed to by input parameters refFramePtr,
*   refSlotPtr and refChipPtr, which are by return updated to the current BTS
*   WCDMA time.
*
*   @par Errors:
*   AaWcdmaTimeSinceGet () function has failed if:
*   [EAaWcdmaTimeRetVal_Error] Internal timer error.
*   [EAaWcdmaTimeRetVal_InvalidParamValue] All pointers are NULL.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*   // Here is the usage example for the function.
*   TAaBtsFrameNr refFrame, resultFrame;
*   TAaBtsSlotNr  refSlot, resultSlot;
*   TAaBtsChipNr  refChip, resultChip;
*
*   //Getting time1
*   AaWcdmaTimeGet( &refFrame, &refSlot, &refChip );
*   ...
*   ...
*   //Calculating time since time1 and getting time2.
*   AaWcdmaTimeSinceGet( &refFrame, &refSlot, &refChip, &resultFrame,
*       &resultSlot, &resultChip );
*   ...
*   ...
*   //Calculating time since time2 and getting time3.
*   AaWcdmaTimeSinceGet( &refFrame, &refSlot, &refChip, &resultFrame,
*       &resultSlot, &resultChip );
*   @endcode
*
*   @par Usage:
*   It is possible to use only one or few of offered values by using NULL to the
*   pointers of not needed values.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaWcdmaTimeGet
*
*******************************************************************************/
EAaWcdmaTimeRetVal AaWcdmaTimeSinceGet(
    TAaBtsFrameNr * const refFramePtr,
    TAaBtsSlotNr * const refSlotPtr,
    TAaBtsChipNr * const refChipPtr,
    TAaBtsFrameNr * const resultFramePtr,
    TAaBtsSlotNr * const resultSlotPtr,
    TAaBtsChipNr * const resultChipPtr );

/**
*******************************************************************************
*
*   @brief      Offers a WCDMA time based delay.
*
*   @param[in]  waitFrames  Frame interval for the sleep.
*   @param[in]  waitSlots   Slot interval for the sleep.
*   @param[in]  waitChips   Chip interval for the sleep.
*   @return     EAaWcdmaTimeRetVal_NoError,EAaWcdmaTimeRetVal_InvalidParamValue
*               or EAaWcdmaTimeRetVal_Error
*
*   @par Description:
*   Blocks the caller for the duration of the delay depends on the given WCDMA
*   time (frames, slots and chips).
*
*   A limit has been defined for the context change. If the requested sleep time
*   is less or equal than the limit, the function reads free running timer until
*   time has been spent. If the requested sleep time is more than the limit;
*   a semaphore is set, a timer is requested to release it and the control has
*   been given to OS for a while. 8 chips limit is used in the definition:
*   DAAWCDMA_TIME_SERVICES_SLEEP_LIMIT_CHIPS_FOR_CONTEXT_CHANGE.
*
*   Valid range for input parameters are:
*   frame (0?096), slot (0?5) and chip (0?560).
*   Maximum sleep time is one super frame (4096 frames).
*
*   @par Errors:
*   AaWcdmaTimeSleep() function has fail if:
*   [EAaWcdmaTimeRetVal_Error] Internal timer error.
*   [EAaWcdmaTimeRetVal_InvalidParamValue] Invalid parameter(s).
*
*   @par Restrictions:
*   AaWcdmaTimeSleep function cannot be use from interrupt routine,
*   because function uses semaphores.
*
*   Note that in CCS-RT this function is not supported under Event Machine
*   environment.
*
*   @par Example:
*   @code
*   // Here is the usage example for the function.
*   // A delay for one slot and 15 chips.
*   AaWcdmaTimeSleep( 0, 1, 15 );
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
*   DAAWCDMA_TIME_SERVICES_SLEEP_LIMIT_CHIPS_FOR_CONTEXT_CHANGE
*
*******************************************************************************/
EAaWcdmaTimeRetVal AaWcdmaTimeSleep(
    const TAaBtsFrameNr waitFrames,
    const TAaBtsSlotNr waitSlots,
    const TAaBtsChipNr waitChips );

#ifdef __cplusplus
}
#endif

/** @} */   /* dgUpCcsRtDspAaWcdmaTime*/
/** @} */   /* dgUpCcsAaWcdmaTime */
/** @} */   /* dgUpCcs */

#endif /*  _RT_DSP_IFAAWCDMATIME_H */
