/**
*******************************************************************************
* @file
*
* @brief                 AaSysTime interface header file
*
* Copyright 2016 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _RT_DSP_IFAASYSTIME_H
#define _RT_DSP_IFAASYSTIME_H

#include <IfAaSysTime_Defs.h>

/*----------------------- DOXYGEN GROUPS --------------------------------------*/
/**
* @addtogroup dgUpCcs U-Plane specific CC&S API
* @{
*/

/**
* @addtogroup dgUpCcsAaSysTime AaSysTime API
* @{
*/

/**
* @addtogroup dgUpCcsRtDspAaSysTime AaSysTime API for RT and OSECK DSP nodes
* @{
*/

#ifdef __cplusplus
extern "C" {
#endif

/** @brief AaSysTime consts to app timers create purposes */
#define DFRAME_DURATION_IN_MICROSECS         (10000)
#define DLTE_SLOTS_IN_FRAME                     (20)

/** @brief AaSysTime arguments for callbacks */
typedef struct AaSysTimeCbArgs{
    EAaSysTimePriority     priority;
    TAaSysTimerFunctionPtr functionPtr;
    void*                  funcParamPtr;
    u32                    sizeOfparam;
}AaSysTimeCbArgs;

/** @brief AaSysTime types for timers */
typedef enum _EAaSysTimeTimerType{
    EAaSysTimerType_Callback = 0,
    EAaSysTimerType_Message,
    EAaSysTimerType_NumOfTypes
}EAaSysTimeTimerType;

/**
*******************************************************************************
*
*   @brief    Offers a system time based delay.
*
*
*   @param[in] sleepTime Interval for the sleep.
*   @param[in] scale     Resolution of the given sleep time.
*
*   @return Function returns EAaSysTimeRetVal_NoError,
*                            EAaSysTimeRetVal_Error or
*                            EAaSysTimeRetVal_InvalidParamValue
*
*   @par Description:
*   Blocks the caller for the duration of the delay depends on the interval and
*   its scale. The scale defines the resolution for the sleep interval (tick,
*   nanosec, microsec, millisec or seconds).
*
*   @par Errors:
*   AaSysTime64Sleep() function has fail if:
*   [EAaSysTimeRetVal_ InvalidParamValue] Unknown scale.
*   [EAaSysTimeRetVal_Error] Internal timer error.
*
*   @par Restrictions:
*   Note that in OSEck (DSP) if sleep is shorter than 2000 clock cycles,
*   semaphore is not used and internal timer is not created --> context switch
*   is not done.
*
*   Note that in CCS-RT this function is not supported under Event Machine
*   environment.
*
*   @par Example:
*   Following example ...
*   @code
*   // Delay of 5 microseconds
*   AaSysTime64Sleep( 5, EAaSysTimeScale_Microsec );
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
*   @see EAaSysTimeScale
*
******************************************************************************/
EAaSysTimeRetVal AaSysTime64Sleep(const TAaSysTime64 sleepTime,
                                const EAaSysTimeScale scale);


/**
*******************************************************************************
*
*   @brief    Offers a message sending/callback executing after the given latency.
*
*
*   @param[out]  timerIdPtr  Pointer for the timer identifier of this timer.
*   @param[in]   latency     Time in microseconds to be waited.
*   @param[in]   period      Period in microseconds.
*   @param[in]   type        Type of timer.
*   @param[in]   listOfArgs  Pointer for the message/configuration structure.
*
*   If microsecond resolution is not supported, latency and period is rounded
*   up to next supported resolution.
*
*   @return     Function returns EAaSysTimeRetVal_NoError,
*                                EAaSysTimeRetVal_Error or
*                                EAaSysTimeRetVal_InvalidParamValue
*
*   @par Description:
*   This function offers a message sending via Message Router or callback
*   executing after the given latency. Function creates and starts a timer
*   (message on timeout)/(callback on timeout).
*   *
*   Functionality that provides creating a system based timer with the latency
*   and period given in microseconds. The timer granularity is 4ms in Linux and
*   1ms in OSE environment. Please be informed you can only use multiple values of
*   granularity. For example on Linux you can set timers that would be triggered every
*   4ms, 8ms, 12ms and so on. Please remember that Linux is not a Real Time OS thus
*   timers are not guaranteed to be accurate, the real time may vary due to interrupts,
*   system overload etc.
*
*   A periodical timer is set up by setting the needed time period.
*   Setting the input parameter for the period to zero sets up a one-time
*   timeout.
*
*   Message Router message have to be fulfilled and ready for the sending via
*   the Message Router.
*
*   On CC&S-DSP the one-time timer the message is released by
*   Message Router and for the periodical timeout the message is released,
*   when the timer request is cancelled.
*
*   On CC&S-RT the one-time timer must be always deleted after timeout using
*   AaSysTimerDelete() or AaSysTimermDelete(). On Event Machine and RT environment
*   callback timers are NOT supported at all.
*
*   @par Errors:
*    AaSysTimermCreate() function has fail if:
*   [EAaSysTimeRetVal_Error] Internal timer error.
*   [EAaSysTimeRetVal_InvalidParamValue] Invalid parameter(s).
*
*   @par Restrictions:
*   Note that in OSEck (CC&S-DSP) if given period is shorter (not zero) than
*   configured TimeServices base tick period, error will be returned.
*
*   On CC&S-RT the one-time timer must be deleted after timeout using
*   AaSysTimerDelete() or AaSysTimermDelete().
*
*   @par Example:
*   Following example ...
*   @code
*   TAaSysTimerId timerId;
*   //Message based timer
*   void *message;
*   message = AaSysComMsgCreate( MessageId, size, recipient);
*   // A one-time timer request after the five second latency.
*   AaSysTimerCreate( &timerId, 5000000, 0, EAaSysTimerType_Message, message);
*
*   //Callback based timer
*   void callbackFunction( void *param )
*   {
*       AaMemUnref(param);
*       return true;
*   }
*   AaSysTimeCbArgs cbArgs;
*   u32*  param = AaMemMalloc(300);
*   cbArgs.priority = EAaSysTimePriority_Medium;
*   cbArgs.functionPtr = (TAaSysTimerFunctionPtr)callbackFunction;
*   cbArgs.funcParamPtr = param;
*   cbArgs.sizeOfparam =  sizeof(u32);
*   // A one-time timer request after the five second latency.
*   AaSysTimerCreate(&timerId, 5000000, 0, EAaSysTimerType_Callback, &cbArgs);
*
*   @endcode
*
*   @par Usage:
*   For the periodical timer the message is copied before every sending.
*   When the timer is cancelled, original message is released by Time Services.
*   When the one-time timer the message is sent to target, the receiver has
*   to release message.
*
*   @par Rationale:
*   The reason for different behavior in case of one-time timer between CC&S-DSP
*   and CC&S-RT is performance.
*
*   @par Future directions:
*   None
*
*   @see AaSysTimercCreate
*   @see AaSysTimerDelete
*   @see AaSysTimermDelete
*
******************************************************************************/
EAaSysTimeRetVal AaSysTimerCreate(TAaSysTimerId * const timerIdPtr,
                                   const TAaMicroSecond latency,
                                   const TAaMicroSecond period,
                                   EAaSysTimeTimerType type,
                                   const void * const listOfArgs);


/**
*******************************************************************************
*
*   @brief    Offers the current timezone offset in minutes.
*
*   @return Function returns current timezone offset given in minutes.
*
*   @par Description:
*   Current UTC timezone offset given in minutes is returned by this function.
*   Timezone value is updated and returned.
*
*   @par Errors:
*    None
*
*   @par Restrictions:
*    None
*
*   @par Example:
*   @code
*   TAaUtcZone utcTimeZoneOffset = AaSysTimeTimezoneGetOffset();
*   @endcode
*
*   @see AaSysTimeTimezoneSetByOffset
*
******************************************************************************/
TAaUtcZone AaSysTimeTimezoneGetOffset(void);

/**
*******************************************************************************
*
*   @brief    Sets timezone based on offset.
*
*   @param[in] utcTimeZoneOffset Timezone offset to be set given in minutes.
*
*   @return EAaSysTimeRetVal_InvalidParamValue,
*           EAaSysTimeRetVal_Error or
*           EAaSysTimeRetVal_NoError.
*
*   @par Description:
*   Function sets timezone in system based on given utcTimeZoneOffset value.
*
*   @par Errors:
*   [EAaSysTimeRetVal_InvalidParamValue] when timezone offset is out of range.
*   [EAaSysTimeRetVal_Error] in case of internal error.
*
*   @par Restrictions:
*   utcTimeZoneOffset should be given as an offset in minutes from UTC and
*   accepted values range is <-720;840>
*
*   @par Example:
*   @code
*   AaSysTimeTimezoneSetByOffset(60);
*   @endcode
*
*   @see AaSysTimeTimezoneGetOffset
*
******************************************************************************/
EAaSysTimeRetVal AaSysTimeTimezoneSetByOffset(TAaUtcZone utcTimeZoneOffset);

/**
*******************************************************************************
*
*   @brief    Gets UTC time with microseconds resolution.
*
*   @param[out] timePtr Pointer to the returned structure storing the current
*                       time.
*
*   @return EAaSysTimeRetVal_InvalidParamValue, EAaSysTimeRetVal_NoError.
*
*   @par Description:
*   Function gets current UTC time with microseconds resolution. Function is
*   supported in EM context.
*
*   @par Errors:
*   [EAaSysTimeRetVal_InvalidParamValue] when GLO_NULL is given as a parameter.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*   SAaTimeOptimized time;
*   EAaSysTimeRetVal ret;
*
*   if(EAaSysTimeRetVal_NoError != (ret = (AaUtcTimeGetWithMicroseconds(&time)))
*   {
*       // Error handler raising 'ret'
*   }
*   @endcode
*
*   @see AaUtcTimeGet
*
******************************************************************************/
EAaSysTimeRetVal AaUtcTimeGetWithMicroseconds(SAaTimeOptimized * const timePtr);

#ifdef __cplusplus
}
#endif

/** @} */   /* dgUpCcsRtDspAaSysTime*/
/** @} */   /* dgUpCcsAaSysTime */
/** @} */   /* dgUpCcs */

#endif /*  _IFAASYSTIME_H */
