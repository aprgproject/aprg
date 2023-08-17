/** @file
*   @brief AaSysTime interface header file
*   @copyright 2018, 2019 Nokia. All rights reserved.
*/

#ifndef _IFAASYSTIME_H
#define _IFAASYSTIME_H
#include "CcsCommon.h"

#include <IfAaSysTime_Defs.h>

/*----------------------- DOXYGEN GROUPS -------------------------------------*/

/**
*@defgroup dgAaSysTime System Time Service (AaSysTime)
*@ingroup dgBasicSysSw
*
* Common Computer and Support SW System Time Service.
*
*
* This service provides common system time and timeout services.
*
*
* CC&S Wiki:
* http://wikis.inside.nokiasiemensnetworks.com/bin/view/CSSWiki/AaSysTime
*
*/

/**
*@defgroup dgAaSysTimeAttributeTags Attribute tags
*@ingroup dgAaSysTime
*
* Runtime configuration can be divided into pre- and post-configuration phases.
* Pre-configuration takes place before CE startup has been done for a service.
* Post-configuration takes place after CE, EE and EU startup. Configuration is
* handled using so called configuration tags. Data and keys are variable
* width in size so they are quite flexible to use.
* \n\n
* Usually configuration tags are used for input direction i.e. feeding
* configuration to CC&S service. However some tags can also be used for output
* direction i.e. for advertising CC&S service state or capabilities.
* Configuration tag description should state wether the tag is inteded for
* feeding information (input) to the service or the service uses the tag for
* capability and state advertisement (output).
*
*
* @ref dsVariation "[CCSAPI_VARIABILITY]"
*
*
* @verbatim
*  Tag name:        ccs.service.aasystime.resolution
*
*  Direction:       input
*
*  Context:         EE
*
*  Description:     Told AaSysTime resolution of timebase in current system.
*                   AaSysTime use this to converts 64-bit time stamp to
*                   understantable form (seconds, minutes etc.)
*
*  Effect analysis: N/A
*
*  Restriction:     Not in use OSEck (DSP).
*
*  Value:           IE Type:     Size:     Range:
*                   number       u32       1 - 4294967295
*
*  Define:          AASYSTIME_CONFIG_TAG_RESOLUTION
*
*  See:             None
* @endverbatim
*
*/


/**
* @defgroup dpAaSysTimeErrors Exception codes
* @ingroup dgAaSysTime
*
* OSEck (DSP) AaSysTime implementation reports errors via local Fault Manager.
* Error codes can be found from DSP HWAPI ENV (EDspPlatErrCause.h and
* EDspPlatComp.h).
*
*/

/**
*@defgroup dgAaSysTimeApi API
*@ingroup dgAaSysTime
*
* Application Programming Interface.
*
* API specification (current): https://sharenet-ims.int.net.nokia.com/Overview/D-171095
*
*@{*/

/*----------------------- INCLUDED FILES ------------------------------------*/

#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PUBLIC DECLARATIONS -------------------------------*/


/*----------------------- PUBLIC INTERFACES ---------------------------------*/

/**
 * @defgroup dgAaSysTimeApiCommon AaSysTime COMMON API
 * @ingroup  dgAaSysTime
 */

/* @{ */

/**
*******************************************************************************
*
*   @brief    Offers the current time in unix seconds with microseconds
*
*
*   @param[out]  timePtr Pointer for the structure of the current unix
*                timestamp
*
*   @return     Function returns EAaSysTimeRetVal_NoError or
*               EAaSysTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   The current time in "seconds since Unix" January 1, 1970, 00:00:00 is
*   returned by this function.
*   The time fields are updated and returned.
*
*   @par Errors:
*   AaUnixTimeGet() function has fail if:
*   [EAaSysTimeRetVal_InvalidParamValue] The time pointer is NULL.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*      // Here is the usage example for the function.
*   @code
*
*   SAaBtsTimeval unixTime;
*   TAaSecond second;
*   TAaMicroSecond microsec;
*   AaUnixTimeGet( &unixTime );
*   second = unixTime.second;
*   microsec = unixTime.microsec;
*
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
*   @see AaUtcTimeSet
*   @see AaUtcTimeGet
*   @see AaUtcZoneSet
*   @see AaUtcZoneGet
*
******************************************************************************/
EAaSysTimeRetVal AaUnixTimeGet(SAaBtsTimeval * const timePtr);

/**
*******************************************************************************
*
*   @brief    Offers the current local time
*
*
*   @param[out]  timePtr Pointer for the structure of the current local time
*
*   @return     Function returns EAaSysTimeRetVal_NoError or
*               EAaSysTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   The current local time is returned by this function.
*   The time fields are updated and returned.
*
*   @par Errors:
*   AaLocalTimeGet() function has fail if:
*   [EAaSysTimeRetVal_InvalidParamValue] The time pointer is NULL.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*      // Here is the usage example for the function.
*   @code
*
*   SAaTime stime;
*   TAaSecond sec;
*   AaLocalTimeGet( &stime );
*   sec = stime.second;
*
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
*   @see AaUtcTimeSet
*   @see AaUtcTimeGet
*   @see AaUtcZoneSet
*   @see AaUtcZoneGet
*
******************************************************************************/
EAaSysTimeRetVal AaLocalTimeGet(SAaTime * const timePtr);

/**
*******************************************************************************
*
*   @brief    Offers a function callback after the given latency
*
*
*   @param[out]  timerIdPtr   Pointer for the identifier of this timer.
*   @param[in]   latency      Time in microseconds to be waited from moment of
*                             calling.
*   @param[in]   period       Period in microseconds.
*   @param[in]   priority     Priority of the callback (low, medium, high).
*   @param[in]   funcPtr      Pointer for the callback function.
*   @param[in]   funcParamPtr Pointer for the parameters of the callback
*                             function
*   @param[in]   sizeOfparam  Size of parameters behind funcParamPtr pointer
*
*   If microsecond resolution is not supported, latency and period is rounded
*   up to next supported resolution.
*
*   @return     Function returns EAaSysTimeRetVal_NoError,
*                                EAaSysTimeRetVal_Error or
*                                EAaSysTimeRetVal_InvalidParamValue
*
*   @par Description:
*   This function offers a function callback after the given latency.
*   Function creates and starts a timer (function callback on timeout).
*
*   Functionality that provides creating a system based timer with the latency
*   and period given in microseconds. The timer granularity is 4ms in Linux and
*   1ms in OSE environment. Please be informed you can only use multiple values of
*   granularity. For example on Linux you can set timers that would be triggered every
*   4ms, 8ms, 12ms and so on. A callback function is registered and will be called upon
*   the expiration of the timer. Please remember that Linux is not a Real Time OS thus
*   timers are not guaranteed to be accurate, the real time may vary due to interrupts,
*   system overload etc.
*
*   AaSysTime uses OS level timers, but provides own level of resource management
*   (maintaining list of active timers, allocating and freeing memory for them).
*
*   When the OS timer expires, a signal is sent to the AaTimerCallback thread which
*   receives the signal, finds the timer from the list and creates the new EU in the
*   context of which the registered timer callback function is executed.
*
*   A periodical timer is set up by setting the needed time period.
*   Setting the period parameter to zero sets up a one-time timeout.
*
*   Time Services offers three different priorities for the context of
*   the callback function. High priority uses the highest context
*   priority of the OS. Low priority uses the lowest context priority
*   of the OS and medium priority uses the implementation specific context
*   priority. Note that in OSEck (DSP), all callbacks are executed from
*   interrupt priority context regardless of given priority.
*
*   @par Errors:
*   AaSysTimercCreate() function has fail if:
*   [EAaSysTimeRetVal_Error] Internal timer error.
*   [EAaSysTimeRetVal_InvalidParamValue] Invalid parameter(s).
*
*   @par Restrictions:
*	Time Services will release any possibly dynamically allocated memory
*	for the parameters of the callback function.
*	Timer Services use AaPro Service to create EU for the callback function.
*	Callback function should not release the pointers of the dynamically allocated memory for the input parameters,
*	as they are released by the AaPro Service after callback EU finishes.
*
*	Note that in OSEck
*   (DSP), all callbacks are executed from interrupt priority context
*   regardless of given priority.
*
*   Note that in OSEck (DSP) if given period is shorter (not zero) than
*   configured TimeServices base tick period, error will be returned.
*
*   Note that is recommended to use message based timers.
*   The general programming paradigm in OSE and in CC&S also is
*   based on communicating tasks (i.e. messaging between EUs).
*
*   @par Usage:
*
*   If there is a dynamically allocated memory block for the parameters of the
*   callback function and if there is a possibility, that user is going to
*   cancel that function callback timeout request (one-time or periodic), user
*   have to take care of that pointer of the dynamically allocated memory and
*   free it, when needed.
*
*   The callback function will be executed in Eu created with
*   AaProCreateAndStart [AAPRO] method with the given priority. Note that in
*   OSEck (DSP), all callbacks are executed from interrupt priority context
*   regardless of given priority.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see EaaSysTimePriority
*
******************************************************************************/
EAaSysTimeRetVal AaSysTimercCreate(TAaSysTimerId * const timerIdPtr,
                                   const TAaMicroSecond latency,
                                   const TAaMicroSecond period,
                                   const EAaSysTimePriority priority,
                                   const TAaSysTimerFunctionPtr funcPtr,
                                   const void * const funcParamPtr,
                                   const u32   sizeOfparam);

/**
*******************************************************************************
*
*   @brief    Deletes a pending timer request.
*
*
*   @param[in]  timerId     The timer identifier.
*
*   @return     Function returns EAaSysTimeRetVal_NoError,
*                                EAaSysTimeRetVal_Error or
*                                EAaSysTimeRetVal_InvalidParamValue
*
*   @par Description:
*   Function deletes a pending timer request according the given timer
*   identifier. If the timer is not found (e.g. one-time timer has been
*   triggered already), the function returns an error value. If message timer
*   has elapsed, but the message is not yet handled (is in the user's message
*   queue), message is not released.
*
*   On CC&S-RT also one-time timer must be deleted after it is expired in order
*   to release its resources after the timer is expired.
*
*   @par Errors:
*   AaSysTimerDelete() function has fail if:
*   [EAaSysTimeRetVal_Error or EAaSysTimeRetVal_InvalidParamValue]
*   The requested timer has not been found and any timers has not been deleted.
*
*   @par Restrictions:
*   Identifier of deleted timer can be reused later, when new timers are
*   created. Identifier is not reused right away, but in same phase identifier
*   may be used again.
*
*   On CC&S-MCU there is mechanism which protects reusing ids by internally mapping
*   to u16 value. This means same id will not be given until 2^15 times of new
*   timer creation
*
*   On CC&S-RT also one-time timer must be deleted after it is expired in order
*   to release its resources after the timer is expired.
*
*   @par Example:
*   Following example ...
*   @code
*   RetVal = AaSysTimerDelete( timerId );
*   @endcode
*
*   @par Usage:
*   Any allocated memory blocks for the parameters of the callback function are
*   not released by this function. If message timer is deleted with using this
*   method, the message is released automatically by using the method of the
*   AaSysCom.
*
*   @par Rationale:
*   Disparity in CC&S-RT functionality is due to performance reasons.
*
*   @par Future directions:
*   None
*
*   @see AaSysTimermCreate
*   @see AaSysTimercCreate
*
******************************************************************************/
EAaSysTimeRetVal AaSysTimerDelete(const TAaSysTimerId timerId);

/**
*******************************************************************************
*
*   @brief      Deletes a pending timer request and returns the message of the
*               timer.
*
*
*   @param[in]  timerId     The timer identifier.
*
*   @return     Upon successful completion, function shall return the pointer
*               to the message of the message based timeout timer. Otherwise,
*               NULL shall be returned.
*
*   @par Description:
*   Function deletes a pending timer request according the given timer
*   identifier and returns the message pointer of the message-based timer. If
*   the timer is not found (e.g. one-time timer has been triggered already),
*   the function returns a NULL value. If timer has elapsed, but the message is
*   not yet handled (is in the user's message queue), message is not released.
*
*   On CC&S-RT also one-time timer must be deleted after it is expired in order
*   to release its resources after the timer is expired.
*
*   @par Errors:
*   AaSysTimermDelete() function has fail if:
*   - NULL has been returned. The requested timer has not been found,
*     any timers have not been deleted
*
*   @par Restrictions:
*   This function can be used only for the deleting a pending message-based
*   timer. Identifier of deleted timer can be reused later, when new timers are
*   created. Identifier is not reused right away, but in same phase identifier
*   may be used again.
*
*
*   On CC&S-MCU there is mechanism which protects reusing ids by internally mapping
*   to u16 value. This means same id will not be given until 2^15 times of new
*   timer creation
*
*   On CC&S-RT also one-time timer must be deleted after it is expired in order
*   to release its resources after the timer is expired.
*
*
*   @par Example:
*   Following example ...
*   @code
*   void *msgPtr;
*   msgPtr = AaSysTimermDelete( timerId );
*   @endcode
*
*   @par Usage:
*   This function returns the message pointer of the pending timer.
*   If the function AaSysTimerDelete is used instead, the message is released
*   automatically by using the method of the AaSysCom.
*
*   Usage of this function is recommended only, when the message is going to be
*   reused.
*
*   @par Rationale:
*   Disparity in CC&S-RT functionality is due to performance reasons.
*
*   @par Future directions:
*   None
*
*   @see AaSysTimermCreate
*   @see AaSysTimercCreate
*   @see AaSysTimerDelete
*
******************************************************************************/
void* AaSysTimermDelete(const TAaSysTimerId timerId);

/**
*******************************************************************************
*
*   @brief    Offers a message sending after the given latency.
*
*
*   @param[out]  timerIdPtr  Pointer for the timer identifier of this timer.
*   @param[in]   latency     Time in microseconds to be waited.
*   @param[in]   period      Period in microseconds.
*   @param[in]   messagePtr  Pointer for the message.
*
*   If microsecond resolution is not supported, latency and period is rounded
*   up to next supported resolution.
*
*   @return     Function returns EAaSysTimeRetVal_NoError,
*                                EAaSysTimeRetVal_Error or
*                                EAaSysTimeRetVal_InvalidParamValue
*
*   @par Description:
*   This function offers a message sending via Message Router after the given
*   latency. Function creates and starts a timer (message on timeout).
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
*   On CC&S-MCU the one-time timer the message is released by
*   Message Router and for the periodical timeout the message is released,
*   when the timer request is cancelled.
*
*   On CC&S-RT the one-time timer must be always deleted after timeout using
*   AaSysTimerDelete() or AaSysTimermDelete().
*
*   @par Errors:
*    AaSysTimermCreate() function has fail if:
*   [EAaSysTimeRetVal_Error] Internal timer error.
*   [EAaSysTimeRetVal_InvalidParamValue] Invalid parameter(s).
*
*   @par Restrictions:
*   Note that in OSEck (DSP) if given period is shorter (not zero) than
*   configured TimeServices base tick period, error will be returned.
*
*   On CC&S-RT the one-time timer must be deleted after timeout using
*   AaSysTimerDelete() or AaSysTimermDelete().
*
*   @par Example:
*   Following example ...
*   @code
*   TAaSysTimerId timerId;
*   void *message;
*   message = AaSysComMsgCreate( MessageId, size, recipient);
*   // A one-time timer request after the five second latency.
*   AaSysTimermCreate( &timerId, 5000000, 0, message);
*
*   @endcode
*
*   @par Usage:
*   For the periodical timer the message is copied before every sending.
*   When the timer is canceled, original message is released by Time Services.
*   When the one-time timer the message is sent to target, the receiver has
*   to release message and delete the timer.
*
*   @par Rationale:
*   The reason for different behavior in case of one-time timer between CC&S-MCU
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
EAaSysTimeRetVal AaSysTimermCreate(TAaSysTimerId * const timerIdPtr,
                                   const TAaMicroSecond latency,
                                   const TAaMicroSecond period,
                                   const void * const messagePtr);

EAaSysTimeRetVal AaSysTimermCreateLong(TAaSysTimerId * const timerIdPtr,
                                       const TAaSecond latency,
                                       const TAaSecond period,
                                       const void * const messagePtr);

/**
*******************************************************************************
*
*   @brief    Resetting the latency of the pending timer.
*
*
*   @param[in]   timerId     Pointer for the timer identifier.
*   @param[in]   latency     Time in microseconds to be waited.
*
*   @return     Function returns EAaSysTimeRetVal_NoError,
*                                EAaSysTimeRetVal_Error or
*                                EAaSysTimeRetVal_InvalidParamValue
*
*   @par Description: This function offers resetting the latency for the
*        pending timer
*
*   @par Errors:
*   AaSysTimerReset() function has fail if:
*   [EAaSysTimeRetVal_Error] Internal timer error.
*   [EAaSysTimeRetVal_InvalidParamValue] Invalid parameter(s).
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   Following example ...
*   @code
*   TAaSysTimerId timerId;
*   void *message;
*   message = AaSysComMessageCreate( MessageId, MsgSize, target_task);
*   // A one-time timer request after the five second latency.
*   AaSysTimermCreate( &timerId, 5000000, 0, message);
*   // Resetting the latency.
*   AaSysTimerReset( timerId, 10000);
*
*   @endcode
*
*   @par Usage:
*   This function can be used for the watchdog type timers. Timer is not needed
*   to be recreated, when the latency time is needed to be changed. Instead,
*   this function can be used to change the latency time.
*
*   This function can be used for one-time or periodic timers. For the periodic
*   timer only the latency to next timer is reset.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*
******************************************************************************/
EAaSysTimeRetVal AaSysTimerReset(const TAaSysTimerId timerId,
                                 const TAaMicroSecond latency);

/**
*******************************************************************************
*
*   @brief    Calculates the time since the reference time.
*
*
*   @param[in,out] timeref   A pointer to a TAaSysTime object that contains the
*                            reference time in ticks and where the function
*                            store a new reference time, the current system
*                            time, in ticks when returns.
*   @param[in]     scale     The time scale of function return value expressed
*                            as an EAaSysTimeScale object.
*
*   @return The time difference, in ticks, nanoseconds, microseconds,
*           milliseconds or seconds, between the current system time and the
*           reference time.
*
*   @par Description:
*   The function calculates the time difference between the current system time
*   and the reference time pointed to by timeref, which is by return updated to
*   the current system time. If the current system time is less than the
*   reference time, a system time counter reset is expected to have occurred.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   Note that maximum time which can be reliably calculated depends on ticks
*   resolution. Ticks resolution can be fetched with AaTickResolutionGet()
*   function. For example, if tick resolution is 1000000000 ticks/second and
*   maximum value in timeref is 2^32, maximum time to be calculated reliably
*   is about 4.29 seconds.
*
*   @par Example:
*   Following example ...
*   @code
*   TAaSysTime result, time;
*   time = AaTicksGet();
*   result = AaSysTimeSinceGet( &time, EAaSysTimeScale_Millisec );
*   ...
*   ...
*   result = AaSysTimeSinceGet( &time, EAaSysTimeScale_Millisec );
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
*   @see AaTicksGet
*   @see EAaSysTimeScale
*
******************************************************************************/
TAaSysTime AaSysTimeSinceGet(TAaSysTime * const timeref,
                             const EAaSysTimeScale scale);

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
*   AaSysTimeSleep() function has fail if:
*   [EAaSysTimeRetVal_ InvalidParamValue] Unknown scale.
*   [EAaSysTimeRetVal_Error] Internal timer error.
*
*   @par Restrictions:
*   Note that in OSEck (DSP) if sleep is shorter than 2000 clock cycles,
*   semaphore is not used and internal timer is not created --> context switch
*   is not done.
*
*   @par Example:
*   Following example ...
*   @code
*   // Delay of 5 microseconds
*   AaSysTimeSleep( 5, EAaSysTimeScale_Microsec );
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
EAaSysTimeRetVal AaSysTimeSleep(const TAaSysTime sleepTime,
                                const EAaSysTimeScale scale);

/**
*******************************************************************************
*
*   @brief    Offers the number of ticks per second.
*
*   @return Function returns the number of ticks per second
*
*   @par Description:
*   The tick resolution of the current system is returned by this function.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   Following example ...
*   @code
*   TAaTickRes tickPerSec;
*   tickPerSec = AaTickResolutionGet();
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
*   @see AaTicksGet
*
******************************************************************************/
TAaTickRes AaTickResolutionGet(void);

/**
*******************************************************************************
*
*   @brief    Offers the current system tick value.
*
*   @return   Function returns the current tick value
*
*   @par Description:
*   The current system tick value since last reset is returned by this function.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   Following example ...
*   @code
*   TAaSysTime tick;
*   tick = AaTicksGet();
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
*   @see AaTickResolutionGet
*   @see AaTicks64Get
*
******************************************************************************/
TAaSysTime AaTicksGet (void);

/**
*******************************************************************************
*
*   @brief    Offers the current system tick value.
*
*   @return   Function returns the current 64-bit tick value
*
*   @par Description:
*   The current system tick value since last reset is returned by this function
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   Following example ...
*   @code
*   // Here is the usage example for the function.
*   TAaSysTime64 tick;
*   tick = AaTicks64Get();
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
*   @see AaTickResolutionGet
*   @see AaTicksGet
*
******************************************************************************/
TAaSysTime64 AaTicks64Get (void);

/**
*******************************************************************************
*
*   @brief    Offers the current UTC time.
*
*   @param[out]   timePtr   Pointer to time structure.

*
*   @return Function returns EAaSysTimeRetVal_NoError or
*                            EAaSysTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   The current UTC time is returned by this function. The UTC time fields are
*   updated and returned.
*
*   @par Errors:
*   AaUtcTimeGet() function has fail if:
*   [EAaSysTimeRetVal_InvalidParamValue] Time pointer is NULL.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   Following example ...
*   @code
*
*     // Here is the usage example for the function.
*     SAaTime stime;
*     TAaSecond sec;
*     AaUtcTimeGet( &stime );
*     sec = stime.second;
*
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
*   @see AaUtcTimeSet
*
******************************************************************************/
EAaSysTimeRetVal AaUtcTimeGet(SAaTime * const timePtr);

/**
*******************************************************************************
*
*   @brief    Returns the UTC time at last PPS event.
*
*   @param[out]   timePtr   Pointer to time structure.

*
*   @return Function returns EAaSysTimeRetVal_NoError or
*                            EAaSysTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   The UTC time at last P=PS (Pulse Per Second) event is returned by this function. The UTC time fields are
*   updated and returned.
*
*   @par Errors:
*   AaUtcTimeGet() function has fail if:
*   [EAaSysTimeRetVal_InvalidParamValue] Time pointer is NULL.
*
*   @par Restrictions:
*   On MCU function available only on FSMr2
*
*   @par Example:
*   Following example ...
*   @code
*
*     // Here is the usage example for the function.
*     SAaTime stime;
*     TAaSecond sec;
*     AaUtcTimeAtPpsGet( &stime );
*     sec = stime.second;
*
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
*   @see AaUtcTimeSet
*
******************************************************************************/
EAaSysTimeRetVal AaUtcTimeAtPpsGet(SAaTime * const timePtr);


/**
*******************************************************************************
*
*   @brief    Sets the current UTC time.
*
*
*   @param[in]   timePtr   Pointer to time structure.

*
*   @return Function returns EAaSysTimeRetVal_NoError or
*                            EAaSysTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   Set the new UTC time.
*
*   @par Errors:
*   AaUtcTimeSet() function has fail if:
*   [EAaSysTimeRetVal_InvalidParamValue] Time pointer is NULL
*
*   @par Restrictions:
*   NOTE: Setting UTC time may cause problems because of UTC Synchronization.
*   NOTE: This interface is not available on RT nodes.
*
*   @par Example:
*   Following example ...
*   @code
*
*      // Here is the usage example for the function.
*     SAaTime stime;
*     stime.year = 2005;
*     stime.month = 4;
*     stime.day = 18;
*     stime.hour = 10;
*     stime.minute = 26;
*     stime.second = 0;
*     stime.millisec = 0;
*     AaUtcTimeSet( &stime );
*
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
*   @see AaUtcTimeGet
*
******************************************************************************/
EAaSysTimeRetVal AaUtcTimeSet (const SAaTime * const timePtr);

/**
*******************************************************************************
*
*   @brief Returns current timezone offset
*
*   @return Timezone offset
*
*   @par Description:
*   Function returns current timezone offset in number of minutes from UTC.
*   Timezone offset includes daylight saving time offset if DST is in use.
*
*   @par Errors:
*   None
*   @par Restrictions:
*   This function has undefined behaviour before timezone is set using
*   AaSysTimeTimezoneSetByOffset or AaSysTimeTimezoneSetByName
*
*   @par Example:
*   Following example ...
*   @code
*   TAaUtcZone utcTimeZone = AaSysTimeTimezoneGetOffset();
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
*   @see AaSysTimeTimezoneSetByOffset
*   @see AaSysTimeTimezoneSetByName
*
******************************************************************************/
TAaUtcZone AaSysTimeTimezoneGetOffset(void);

/**
*******************************************************************************
*
*   @brief Sets timezone using offset.
*
*
*   @param[in] zone Timezone offset given in number of minutes from UTC.
*
*   @return Function returns EAaSysTimeRetVal_NoError or
*                            EAaSysTimeRetVal_Error.
*
*   @par Description:
*   Function sets fixed timezone offset passed by zone parameter
*   representing number of minutes from UTC. Timezone set by this
*   function has no daylight saving time changes.
*
*   @par Errors:
*   [EAaSysTimeRetVal_Error] Internal error.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   Following example ...
*   @code
*   AaSysTimeTimezoneSetByOffset( 2*60 );
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
*   @see AaSysTimeTimezoneGetOffset
*
******************************************************************************/
EAaSysTimeRetVal AaSysTimeTimezoneSetByOffset(TAaUtcZone zone);

/**
*******************************************************************************
*
*   @brief      Offers current BTS level time stamp (BCN).
*
*   @return     Current BCN value.
*               Function returns 0 if BCN not synchronized. Exception is the
*               master or reference node which has always valid BCN.
*
*   @par Description:
*   Function AaSysTimeBcnGet() offers current BTS level time stamp (BCN).
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   On CC&S MCU return value is undefined before BCN synchronization.
*
*   @par Example:
*   @code
*     #include <IfAaSysTime.h>
*
*     TAaSysTime64 bcn;
*     bcn = AaSysTimeBcnGet();
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
*
******************************************************************************/
TAaSysTime64 AaSysTimeBcnGet(void);

/**
*******************************************************************************
*
* @brief Scales 64 bit system tick time to 64 bit logical time
*
* @param[in] sysTime:   System time in ticks
* @param[in] scale:     Time scale of return system time value
*
* @return    Scaled system time (ticks/ns/us/ms/s)
*
*
* @par Description:
* Scales 64-bit timestamp value to the wanted logical time value
* (ticks/ns/us/ms/s).
*
* @par Errors:
* AaSysTime64ScaleToLogicalTime() function has fail if:
* [EAaSysTimeRetVal_ InvalidParamValue] Unknown scale.
* [EAaSysTimeRetVal_Error] Internal timer error.
*
* @par Restrictions:
*
* @par Example:
* Following example ...
* @code
* TAaSysTime64 ticksNow = AaTicks64Get();
*
* AaSysTimeSleep( 5, EAaSysTimeScale_Microsec );
*
* TAaSysTime64 ticksLater = AaTicks64Get();
*
* //Time spend
* u32 timeSpend = AaSysTime64ScaleToLogicalTime(ticksLater-ticksNow,
*                                               EAaSysTimeScale_Microsec)
* @endcode
*
* @par Usage:
* None
*
* @par Rationale:
* None
*
* @par Future directions:
* None
*
* @see EAaSysTimeScale
*
******************************************************************************/
TAaSysTime64 AaSysTime64ScaleToLogicalTime(TAaSysTime64 sysTime,
                                           EAaSysTimeScale scale);

/**
*******************************************************************************
*
* @brief Scales 64 bit logical time to 64 bit system tick time.
*
* @param[in] sysTime:   System time
* @param[in] scale:     Time scale of input system time
*
* @return    Scaled system time (ticks/ns/us/ms/s)
*
*
* @par Description:
* Scales 64 bit logical time to 64 bit system tick time.
*
* @par Errors:
*
* @par Restrictions:
*
* @par Example:
* Following example ...
* @code
*
* TAaSysTime64 timeToWaitInUS = 2;
*
* timeToWaitInTicks = AaSysTime64ScaleLogicalTimeToTicks(timeToWaitInUS,
*                                                       EAaSysTimeScale_Microsec);
* @endcode
*
* @par Usage:
* None
*
* @par Rationale:
* None
*
* @par Future directions:
* None
*
* @see EAaSysTimeScale
*
******************************************************************************/
TAaSysTime64 AaSysTime64ScaleLogicalTimeToTicks(TAaSysTime64 sysTime,
                                                EAaSysTimeScale scale);



/**
*******************************************************************************
*
*   @brief  Function returns the used CDMA2000 synchronization mode.
*
*   @return EAaCdmaTimeSyncMode_Sync
*           EAaCdmaTimeSyncMode_Async
*
*   @par Description:   Function returns EAaCdmaTimeSyncMode_Sync, when the
*                       CDMA2000 frame time is synchronous with LTE 10ms frame
*                       border. EAaCdmaTimeSyncMode_Async is returned when the
*                       CDMA2000 frame time is NOT synchronous with LTE 10ms
*                       frame border.
*
*   @par Errors:
*
*   @par Restrictions:
*
*   @par Example:
*   Following example ...
*   @code
*   EAaSysTimeSyncMode mode;
*
*   mode = AaCdmaSyncModeGet();
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
******************************************************************************/
EAaSysTimeSyncMode AaCdmaSyncModeGet(void);


/**
 * @}
 */

/*----------------------- INTERNAL INTERFACES -------------------------------*/

#ifdef __cplusplus
}
#endif

/**@}*/

#endif /*  _IFAASYSTIME_H */

