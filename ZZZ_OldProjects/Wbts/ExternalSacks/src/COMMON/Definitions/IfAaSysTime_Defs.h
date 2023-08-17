/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaSysTime defintions header file
* @module                AaSysTime
* @owner                 Matija Buskovic
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _IFAASYSTIME_DEFS_H
#define _IFAASYSTIME_DEFS_H
#include "CcsCommon.h"
#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif
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

/** @brief Sets resolution for AaSysTime service.  */
#define AASYSTIME_CONFIG_TAG_RESOLUTION "ccs.service.aasystime.resolution"

/** @brief AaSysTime minimal supported timezone offset (in minutes) */
#define DMIN_UTC_TIME_ZONE_VALUE    (-720)

/** @brief AaSysTime maximal supported timezone offset (in minutes) */
#define DMAX_UTC_TIME_ZONE_VALUE    (840)

/** @brief AaSysTime BCN Sync CP ID */
#define AASYSTIME_BCN_SYNC_CPID   0x0617

/** @brief AaSysTime BCN Poll CP ID */
#define AASYSTIME_BCN_POLL_CPID	0x062E

/** @brief Type for the year */
typedef u32 TAaYear;

/**< @brief Type for the month */
typedef u32 TAaMonth;

/**< @brief Type for the day */
typedef u32 TAaDay;

/**< @brief Type for the hour */
typedef u32 TAaHour;

/**< @brief Type for the minute */
typedef u32 TAaMinute;

/**< @brief Type for the second */
typedef u32 TAaSecond;

/**< @brief Type for the milli second */
typedef u32 TAaMilliSecond;

/**< @brief Type for the micro second */
typedef u32 TAaMicroSecond;

/**< @brief Type for the system time */
typedef u32 TAaSysTime;

/**< @brief Type for the 64-bit system time */
typedef u64 TAaSysTime64;

/**< @brief Type for the number of timers */
typedef u32 TAaSysTimerCount;

/** @brief Type for the callback function. Used in callback based timeout
 *         requests.
 *
 * @return None.
 */
typedef void(*TAaSysTimerFunctionPtr)(void *);

/**< @brief Type for the system timer identifier */
typedef u32 TAaSysTimerId;

/**< @brief Type for the tick resolution */
typedef u32 TAaTickRes;

/**< @brief Type for the UTC time zone */
typedef i16 TAaUtcZone;

/**< @brief Type for the UTC time zone in the message*/
typedef i32 TAaUtcZone32;




/**< @brief Type for the time structure */
typedef struct SAaTime{

  TAaYear      year;  /**< Type for the year */
  TAaMonth     month; /**< Type for the month */
  TAaDay       day;   /**< Type for the day */
  TAaHour      hour;  /**< Type for the hour */
  TAaMinute    minute;  /**< Type for the minute */
  TAaSecond    second;  /**< Type for the second */
  TAaMilliSecond millisec; /**< Type for the millisecond */
} SAaTime;

/**< @brief Type for the unix timestamp*/
typedef struct SAaBtsTimeval{
  TAaSecond      second;   /**< Type for the second */
  TAaMicroSecond microsec; /**< Type for the microsecond */
} SAaBtsTimeval;

/** @brief AaSysTime priorities for callbacks */
typedef enum EAaSysTimePriority
{
  EAaSysTimePriority_Low = 0,         /**< Low callback priority */
  EAaSysTimePriority_Medium,          /**< Medium callback priority */
  EAaSysTimePriority_High,            /**< High callback priority */
  EAaSysTimePriority_Interrupt,       /**< Interrupt callback priority */
  EAaSysTimePriority_NumOfPriorities  /**< Number of available priorities */

} EAaSysTimePriority;

/** @brief AaSysTime public function return values */
typedef enum EAaSysTimeRetVal
{
  EAaSysTimeRetVal_NoError = 0,       /**< Return value when no errors */
  EAaSysTimeRetVal_Error,             /**< Return values when errors exists */
  EAaSysTimeRetVal_InvalidParamValue, /**< Invalid parameter value */
  EAaSysTimeRetVal_TimeNotIntialized, /**< Time is not initialized by GPS or NTP */
  EAaSysTimeRetVal_InvalidCdmaTime,   /**< Cdma system time is invalid */
  EAaSysTimeRetVal_HwDriverNotReady,  /**< HW driver not ready */
  EAaSysTimeRetVal_TimerAllocFailed,  /**< Timer alloc problem */
  EAaSysTimeRetVal_SyscomeAllocFailed,/**< SysCome alloc problem */
  EAaSysTimeRetVal_PeriodTooShort,    /**< Period is to short */
  EAaSysTimeRetVal_NumOfRetVals       /**< Number of available return values */

} EAaSysTimeRetVal;

/** @brief AaSysTime scales */
typedef enum EAaSysTimeScale
{
  EAaSysTimeScale_Ticks = 0,  /**< Scale of ticks. */
  EAaSysTimeScale_Nanosec,    /**< Scale of nanoseconds. */
  EAaSysTimeScale_Microsec,   /**< Scale of microseconds. */
  EAaSysTimeScale_Millisec,   /**< Scale of milliseconds. */
  EAaSysTimeScale_Sec,        /**< Scale of seconds. */
  EAaSysTimeScale_NumOfScales /**< The number of system time resolutions. */

} EAaSysTimeScale;


/** @brief AaSysTime interrupt event type */
typedef enum
{
  EAaSysTimeIntType_PPS = 0,
  EAaSysTimeIntType_SlaveFrame,
  EAaSysTimeIntType_MasterFrame,
  EAaSysTimeIntType_SFNatPPS
} EAaSysTimeIntType;

/** @brief BCN sync node statuses */
typedef enum
{
  EAaSysTimeNodeStatus_NoError = 0,
  EAaSysTimeNodeStatus_BcnSyncError,
  EAaSysTimeNodeStatus_UndefinedError,
  EAaSysTimeNodeStatus_TimeoutError
} EAaSysTimeNodeStatus;

/** @brief BCN sync application statuses */
typedef enum
{
  EAaSysTimeNodeAppStatus_NoError = 0,
  EAaSysTimeNodeAppStatus_Error
} EAaSysTimeNodeAppStatus;

/** @brief AaCdmaTime sync mode values */
typedef enum
{
  EAaCdmaTimeSyncMode_Sync = 0,/**< Value when synchronous mode is used */
  EAaCdmaTimeSyncMode_Async    /**< Value when asynchronous mode is used */
} EAaSysTimeSyncMode;


#ifdef __cplusplus
}
#endif

/**@}*/

#endif /*  _IFAASYSTIME_DEFS_H */

