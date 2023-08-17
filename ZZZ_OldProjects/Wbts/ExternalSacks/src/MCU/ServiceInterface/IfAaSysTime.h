/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/
#ifndef _MCU_IFAASYSTIME_H
#define _MCU_IFAASYSTIME_H
#include "CcsCommon.h"
#ifdef CCS_NEW_IF_STRUCTURE
#include <../../COMMON/ServiceInterface/IfAaSysTime.h>
#include <../../SHARED/MCU_RT/ServiceInterface/IfAaSysTime.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
*   @defgroup dgAaSysTimeApiMcu AaSysTime MCU API
*   @ingroup  dgAaSysTime
*
*   Common Computer and Support SW System Time Service.
*
*   This service provides MCU system time and timeout services.
*
*/
/* @{ */
/**
*******************************************************************************
*
*   @brief    Offers a function callback after the given latency in seconds
*
*
*   @param[out]  timerIdPtr       Pointer for the identifier of this timer.
*   @param[in]   latencySec       Time in seconds to be waited from moment of
*                                 calling.
*   @param[in]   periodSec        Period in seconds.
*   @param[in]   priority         Priority of the callback (low, medium, high).
*   @param[in]   funcPtr          Pointer for the callback function.
*   @param[in]   funcParamPtr     Pointer for the parameters of the callback
*                                 function
*   @param[in]   sizeOfparam      Size of parameters behind funcParamPtr pointer
*
*   @return      Function returns EAaSysTimeRetVal_NoError,
*                                 EAaSysTimeRetVal_Error or
*                                 EAaSysTimeRetVal_InvalidParamValue
*
*   @par Description:
*   This function offers a function callback after the given latency in seconds,
*   allowing to create long timeouts. Function creates and starts a timer
*   (function callback on timeout).
*
*   Functionality that provides creating a system based timer with the latency
*   and period given in seconds. The timer granularity is 4ms in Linux environment.
*   Please be informed you can only use multiple values of granularity. On Linux you
*   can set timers that would be triggered every 4ms, 8ms, 12ms and so on. A callback
*   function is registered and will be called upon the expiration of the timer. Please
*   remember that Linux is not a Real Time OS thus timers are not guaranteed to be accurate,
*   the real time may vary due to interrupts, system overload etc.
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
*   priority.
*
*   @par Errors:
*   AaSysTimercCreateLong() function has fail if:
*   [EAaSysTimeRetVal_Error] Internal timer error.
*   [EAaSysTimeRetVal_InvalidParamValue] Invalid parameter(s).
*
*   @par Restrictions:
*   Time Services will release any possibly dynamically allocated memory
*   for the parameters of the callback function.
*   Timer Services use AaPro Service to create EU for the callback function.
*   Callback function should not release the pointers of the dynamically allocated memory for the input parameters,
*   as they are released by the AaPro Service after callback EU finishes.
*
*   Note that is recommended to use message based timers.
*   The general programming paradigm in CC&S also is
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
*   AaProCreateAndStart [AAPRO] method with the given priority.
*
*   @par Rationale:
*   Functionality introduced in CNI6073
*
*   @par Future directions:
*   None
*
*   @see EAaSysTimePriority
*
******************************************************************************/
EAaSysTimeRetVal AaSysTimercCreateLong(TAaSysTimerId * const timerIdPtr,
                                   const TAaSecond latencySec,
                                   const TAaSecond periodSec,
                                   const EAaSysTimePriority priority,
                                   const TAaSysTimerFunctionPtr funcPtr,
                                   const void * const funcParamPtr,
                                   const u32   sizeOfparam);

/**
*******************************************************************************
*
*   @brief    Sets timezone based on timezone name.
*
*   @param[in] utcTimeZoneName Name of timezone that should be set.
*
*   @return EAaSysTimeRetVal_InvalidParamValue,
*           EAaSysTimeRetVal_Error or
*           EAaSysTimeRetVal_NoError.
*
*   @par Description:
*   Function sets timezone in system based on given name.
*
*   @par Errors:
*   [EAaSysTimeRetVal_InvalidParamValue] when timezone name is GLO_NULL.
*   [EAaSysTimeRetVal_Error] in case of internal error.
*
*   @par Example:
*   @code
*   AaSysTimeTimezoneSetByName("Europe/Warsaw");
*   @endcode
*
*   @see AaUtcZoneGet
*   @see AaUtcZoneSet
*
******************************************************************************/
EAaSysTimeRetVal AaSysTimeTimezoneSetByName(const char* utcTimeZoneName);


/**
*******************************************************************************
*
*   @brief  Returns daylight saving time offset
*
*   @return Daylight saving time offset given in minutes.
*
*   @par Description:
*   Function returns current daylight saving time offset in minutes.
*
*   @par Restrictions:
*   Function return value is undefined before timezone is set.
*
*   @par Errors:
*   N/A
*
*   @par Example:
*   Let's assume in this exaple that it is summer time (for example 07.07.RRRR)
*   @code
*   AaSysTimeTimezoneSetByName("Europe/Warsaw");
*   TAaUtcZone utc_offset = 0;
*   AaUtcZoneGet(&utc_offset);
*   i32 dst_offset = AaSysTimeGetDstOffset();
*   assert(dst_offset == 60);
*   assert(utc_offset == 120); //+1h timezone offset and +1h DST offset
*   @endcode
*
*   @see AaSysTimeTimezoneSetByName
*   @see AaUtcZoneGet
******************************************************************************/
i32 AaSysTimeGetDstOffset(void);

/**
*******************************************************************************
*
*   @brief  Function notifies CC&S that BTS RTC reference values has been
*   set in LFS / ddal
*
*   @return
*   EAaSysTimeRetVal_NoError
*   EAaSysTimeRetVal_Error
*
*   @par Description:
*   Function indicates point since when ddal can be called for BTS RTC
*
*   @par Restrictions:
*   For Lionfish use, on other releases does nothing.
*
*   @par Errors:
*   EAaSysTimeRetVal_Error when internal issue
*
*   @par Example:
*   After BTS RTC reference values passed to ddal, function should be simply called
*   @code
*   AaSysTimeBTSRtcRefValuesAreSet();
*   @endcode
*
******************************************************************************/
EAaSysTimeRetVal AaSysTimeBTSRtcRefValuesAreSet(void);

/**
*******************************************************************************
*
*   @brief  Function sets the Pps timing offset.
*
*   @param[in]  offsetInNanosec  Parameter tells the pps timing offset in nano
*                                seconds scale.

*   @return Function returns #EAaSysTimeRetVal_NoError or
*           #EAaSysTimeRetVal_Error
*
*   @par Description:
*   With this function call application sets the used Pps timing offset value
*   which is used in CDMA2000 async system time calculation.
*
*   @par Errors:
*
*   @par Restrictions:
*   On MCU function available only for FSMr2 and FZM
*
*   @par Example:
*   Following example ...
*   @code
*
*   EAaSysTimeRetVal ret;
*   TAaSysTime offset = 86000;
*
*   ret = AaCdmaTimePpsTimingOffset( offset );
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
EAaSysTimeRetVal AaCdmaTimePpsTimingOffset(i32 offsetInNanosec);

/**
*******************************************************************************
*
*   @brief      Signals the invalidity of the CDMA time
*
*
*
*   @return     EAaSysTimeRetVal_NoError
*               EAaSysTimeRetVal_Error
*
*   @par Description:
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   On MCU function available only for FSMr2 and FZM
*
*   @par Example:
*   @code
*     #include <IfAaSysTime.h>
*
*
*   @endcode
*
*   @par Usage:
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
EAaSysTimeRetVal AaCdmaTimeInvalid(void);

/**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif /*  _MCU_IFAASYSTIME_H */
