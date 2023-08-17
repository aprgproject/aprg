/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaSysTime interface header file
* @module                AaSysTime
*
* Copyright 2018 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAASYSTIME_H
#define _MCU_RT_IFAASYSTIME_H

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaSysTimeApiMcu AaSysTime MCU API
 * @ingroup  dgAaSysTime
 */

/* @{ */

/**
*******************************************************************************
*
*   @brief      Offers the BTS level time stamp value at latest GPS PPS signal.
*
*   @return     BCN value at latest GPS PPS signal.
*               Function returns 0 always if GPS PPS signal has not occurred.
*               This function is supported only by processor receiving the PPS
*               signals.
*
*   @par Description:
*   Function AaSysTimeBcnAtPpsGet() offers the BTS level time stamp (BCN)
*   value at latest GPS PPS signal.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   Function is supported only by master node(s) in the system only on FSMr2.
*
*   @par Example:
*   @code
*     #include <IfAaSysTime.h>
*
*     TAaSysTime64 bcnAtPps;
*     bcnAtPps = AaSysTimeBcnAtPpsGet();
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
TAaSysTime64 AaSysTimeBcnAtPpsGet(void);

/**
*******************************************************************************
*
*   @brief  Function sets the used CDMA2000 synchronization mode.
*
*   @param[in]  syncMode       Parameter tells the used sync mode.
*
*   @return Function returns #EAaSysTimeRetVal_NoError or
*           #EAaSysTimeRetVal_Error
*
*   @par Description:
*   With this function call application sets the used CDMA2000 synchronisation
*   value.
*
*   @par Errors:
*
*   @par Restrictions:
*
*   @par Example:
*   Following example ...
*   @code
*   AaCdmaSyncModeSet( EAaCdmaTimeSyncMode_Sync );
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
EAaSysTimeRetVal AaCdmaSyncModeSet(EAaSysTimeSyncMode syncMode);

/**
*******************************************************************************
*
*   @brief      Set valid UTC time for BTS.
*
*
*   @param[in]  ntpUsed       This parameter tells if NTP is used.
*   @param[in]  utcPtr        Pointer to SAaTime structure which tells the
*                             valid UTC time at given BCN.
*   @param[in]  utcValidAtBcn BCN value when the given UTC time is valid.
*
*   @return     Function returns #EAaSysTimeRetVal_NoError or
*               #EAaSysTimeRetVal_Error
*
*   @par Description:
*   With this function call application sets valid UTC time for whole BTS. This
*   UTC time is synchronized to all nodes of BTS via synchronization messages.
*   If NTP is used (GLO_TRUE), BTS RTC is synchronized to OS RTC which is kept
*   in time via NTP. BTS RTC is supervised regularly by CC&S.
*   If NTP is not used (GLO_FALSE), valid BTS RTC is set by giving the UTC
*   time and the BCN when this UTC time is valid. BCN must be the at frame
*   boundary (bits 0-23 must be 0).
*   Given BCN/UTC pair can be also in the past.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   Function is supported only by master node(s) in the system, only on FSMr2 and FZM.
*   If NTP is used, utcPtr and utcValidAtBcn values are ignored. If NTP is not
*   used, utcValidAtBcn value must be at the frame boundary (bits 0-23 must
*   be 0).
*
*   @par Example:
*   @code
*     #include <IfAaSysTime.h>
*
*     if( AaSysTimeRtcSync(GLO_TRUE, GLO_NULL, 0)
*         != EAaSysTimeRetVal_NoError )
*     {
*       //Error handling
*     }
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
*   @see AaSNTP
*
******************************************************************************/
EAaSysTimeRetVal AaSysTimeRtcSync(TBoolean ntpUsed,
                                  SAaTime *utcPtr,
                                  TAaSysTime64 utcValidAtBcn);


/**
*******************************************************************************
*
*   @brief      Set hardware RTC time.
*
*
*   @param[in]  timePtr        Pointer to SAaTime structure with time to set.
*
*   @return     Function returns #EAaSysTimeRetVal_NoError, #EAaSysTimeRetVal_Error or
*               #EAaSysTimeRetVal_InvalidParamValue
*
*   @par Description:
*   With this function call application sets the hardware RTC time to a desired value.
*
*   @par Errors:
*   AaSysTimeSetHwClock() function fails if:
*   [EAaSysTimeRetVal_InvalidParamValue] The provided time pointer is NULL.
*
*   @par Restrictions:
*   On MCU function available only on FSMr2 and FZM
*
*   @par Example:
*   @code
*       #include <IfAaSysTime.h>
*
*       SAaTime time;
*
*       time.year = 2013;
*       time.month = 2;
*       time.day = 5;
*       time.hour = 12;
*       time.minute = 30;
*       time.second = 20;
*       time.millisec = 10;
*
*       if( AaSysTimeSetHwClock(&time)
*           != EAaSysTimeRetVal_NoError )
*       {
*           //Error handling
*       }
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
EAaSysTimeRetVal AaSysTimeSetHwClock(SAaTime *timePtr);


/**
*******************************************************************************
*
*   @brief      Inform CC&S about occurred event.
*
*
*   @param[in]  cbType      Type of the callback. Possible values are:
*                           #EAaSysTimeIntType_PPS,
*                           #EAaSysTimeIntType_SlaveFrame or
*                           #EAaSysTimeIntType_MasterFrame.
*   @param[in]  frameNumber Number of current frame. This is used only when
*                           cbType is #EAaSysTimeIntType_MasterFrame and
*                           ignored with other interrupt types.
*
*   @return     Function returns current BCN. Returns 0 if not synchronized.
*
*   @par Description:
*   This function is called by MCU HWAPI in PPS interrupt or in frame interrupt
*   to inform CC&S about occurred event.
*   CC&S will save the time of occurred event and later this time is used to
*   calculate the BCN and the BCN at PPS values.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   Function is valid only on MCU on FSMr2
*
*   @par Example:
*   @code
*     #include <IfAaSysTime.h>
*
*     AaSysTimeSyncCb(EAaSysTimeIntType_PPS,0);
*   @endcode
*
*   @par Usage:
*   #EAaSysTimeIntType_MasterFrame  Is used on master node. frameNumber is
*                                   always valid.
*   #EAaSysTimeIntType_SlaveFrame   Is used on slave node. frameNumber is
*                                   ignored.
*   #EAaSysTimeIntType_PPS          Is used to inform CC&S about GPS PPS
*                                   interrupt. frameNumber is ignored.
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
TAaSysTime64 AaSysTimeSyncCb(EAaSysTimeIntType cbType,
                             u32 frameNumber);

/**
*******************************************************************************
*
*   @brief    Calculates the time since the reference time.
*
*
*   @param[in,out] timeref   A pointer to a TAaSysTime object that contains the
*                            reference time in 64 bit ticks and where the
*                            function store a new reference time, the current
*                            system time, in ticks when returns.
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
*   function.
*
*   Note that this function is not supported in OSEck (DSP).
*
*   @par Example:
*   Following example ...
*   @code
*   TAaSysTime64 result, time;
*   time = AaTicks64Get();
*   result = AaSysTime64SinceGet( &time, EAaSysTimeScale_Millisec );
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
TAaSysTime64 AaSysTime64SinceGet(TAaSysTime64 * timeref,
                                 const EAaSysTimeScale scale);

/**
*******************************************************************************
*
*   @brief      Returns the remaining time of the timer
*
*
*   @param[in]  timerId     ID of the timer
*
*   @param[out] latency Remaining time of the timer in microseconds
*
*   @return     0 - success
*
*   @par Description:
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   Function is valid only on MCU.
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
EAaSysTimeRetVal AaSysTimerGetTime(TAaSysTimerId timerId, TAaMicroSecond* latency);

/**
*******************************************************************************
*
*   @brief      Sets the CDMA time offset
*
*
*   @param[in]  utcPtr          UTC part of the UTC-BCN pair
*
*   @param[in]  utcValidAtBcn    BCN part of the UTC-BCN pair
*
*   @return     EAaSysTimeRetVal_NoError
*               EAaSysTimeRetVal_Error
*               EAaSysTimeRetVal_InvalidParamValue
*
*   @par Description:   Sets the offset between CDMA time and the BCN where the CDMA time
*                       is represented by 39-bit count of 10 ms ticks since the GPS Epoch.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*
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
EAaSysTimeRetVal AaCdmaTimeOffset(SAaTime *utcPtr, TAaSysTime64 utcValidAtBcn);

/**
*******************************************************************************
*
*   @brief    Returns the GPS time based on BCN the current BCN.
*
*   @param[out]   timePtr   Pointer to time structure.
*
*
*   @return Function returns EAaSysTimeRetVal_NoError or
*                            EAaSysTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   Calculates GPS time stamp from from current BCN which is synchronized so it should be
*   accurate, providing NTP client is well aligned to UTC. BCN on the other hand is derived
*   from BFN which is aligned to GPS.
*
*   @par Errors:
*   AaGpsFromBcnTimeGet() function has fail if:
*   [EAaSysTimeRetVal_InvalidParamValue] Time pointer is NULL.
*
*   @par Restrictions:
*   On MCU function available only on FSMr2 and FZM
*
*   @par Example:
*   Following example ...
*   @code
*
*     // Here is the usage example for the function.
*     SAaTime stime;
*     TAaSecond sec;
*     AaGpsFromBcnTimeGet( &stime );
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
*   @see
*
******************************************************************************/
EAaSysTimeRetVal AaGpsFromBcnTimeGet(SAaTime * const timePtr) CCS_DEPRECATED("Please do not use it anymore. This functionality is obsolete.");



/**
*******************************************************************************
*
*   @brief    Returns the current UTC - BCN pair.
*
*   @param[out]   timePtr   Pointer to the time structure.
*   @param[out]   bcn       Pointer to the bcn value
*
*   @return Function returns EAaSysTimeRetVal_NoError
*                            EAaSysTimeRetVal_InvalidParamValue
*                            EAaSysTimeRetVal_TimeNotIntialized
*
*   @par Description:
*   Returns the UTC - BCN pair valid at the time of calling.
*
*   @par Errors:
*   AaSysTimeUtcBcnGet() function has fail if:
*   [EAaSysTimeRetVal_InvalidParamValue] timePtr os bcn pointer is NULL.
*   [EAaSysTimeRetVal_TimeNotIntialized] time is not initialized by GPS or NTP.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   Following example ...
*   @code
*
*     // Here is the usage example for the function.
*     SAaTime time;
*     TAaSysTime64 bcn;
*     AaSysTimeUtcBcnGet( &time, &bcn );
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
*   @see
*
******************************************************************************/
EAaSysTimeRetVal AaSysTimeUtcBcnGet(SAaTime * const timePtr, TAaSysTime64* bcn);


/**
*******************************************************************************
*
*   @brief    Returns the current Localtime(UTC + timezone) - BCN pair.
*
*   @param[out]   timePtr   Pointer to the time structure.
*   @param[out]   bcn       Pointer to the bcn value
*
*   @return Function returns EAaSysTimeRetVal_NoError
*                            EAaSysTimeRetVal_InvalidParamValue
*                            EAaSysTimeRetVal_TimeNotIntialized
*
*   @par Description:
*   Returns the Localtime(UTC + timezone) - BCN pair valid at the time of calling.
*
*   @par Errors:
*   AaSysTimeLocaltimeBcnGet() function has fail if:
*   [EAaSysTimeRetVal_InvalidParamValue] timePtr os bcn pointer is NULL.
*   [EAaSysTimeRetVal_TimeNotIntialized] time is not initialized by GPS or NTP.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   Following example ...
*   @code
*
*     // Here is the usage example for the function.
*     SAaTime time;
*     TAaSysTime64 bcn;
*     AaSysTimeLocaltimeBcnGet( &time, &bcn );
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
*   @see
*
******************************************************************************/
EAaSysTimeRetVal AaSysTimeLocaltimeBcnGet(SAaTime * const timePtr, TAaSysTime64* bcn);


/**
*******************************************************************************
*
*   @brief    Returns SFN initialization time
*
*
*
*   @return Function returns SFN initialization time
*
*
*   @par Description:
*   Returns SFN initialization time - calculated from BCN and fixed offset betwen
*   GPS epoch and 1900. Time is in seconds relative to 00:00:00 on 1 January  1900
*   (calculated as continuous time without leap seconds and traceable to a common
*   time reference) where binary encoding of the integer part is in the first 32
*   bits and binary encoding of the fraction part in the last 32 bits.
*   The fraction part is expressed with a granularity of 1 /2**32 second.
*
*   @par Errors:
*   Function will always return a value in respect to current BCN, thus cannot fail
*
*   @par Restrictions:
*
*   @par Example:
*   Following example ...
*   @code
*
*     // Here is the usage example for the function.
*     TAaSysTime64 sfnInitTime;
*     sfnInitTime = AaSysTimeSfnInitializationTimeGet();
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
*   @see
*
******************************************************************************/
TAaSysTime64 AaSysTimeSfnInitializationTimeGet(void);


/* @} */

/*----------------------- INTERNAL INTERFACES -------------------------------*/

#ifdef __cplusplus
}
#endif

/**@}*/

#endif /*  _MCU_RT_IFAASYSTIME_H */

