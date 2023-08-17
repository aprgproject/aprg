/**
*******************************************************************************
* @file
*
* @brief
*
* @copyright 2017 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _RT_DSP_AASYSTIME_DEFS_H
#define _RT_DSP_AASYSTIME_DEFS_H

#include <glo_def.h>

#include "../../COMMON/Definitions/IfAaSysTime_Defs.h"

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

/** @brief Optimized structure storing UTC time. */
typedef struct SAaTimeOptimized{
    u16 year;
    u8  month;
    u8  day;
    u8  hour;
    u8  minute;
    u8  second;
    u32 microsecond;
} SAaTimeOptimized;

/** @brief Type for hardware time. In Lionfish environment it is Axxia time. */
typedef u64 TAaTimeHw;

/** @brief Type for BCN time. */
typedef u64 TAaTimeBcn;

/** @brief Structure of synchronization event.
 *
 * Synchronization event is used to synchronize the time on CEVA cores of
 * Lionfish. ARM RT core sends synchronization events to CEVA cores.
 * The event contains a 'snapshot' of several system time related values,
 * collected in the same time. Those values can be used for example to compute
 * the offset between BCN and Axxia time values.
 * Structure is used for payload of event CCS_ARM_EVENT_TIME_SYNC. */
typedef struct SAaSysTimeEventTimeSync {
    TAaTimeHw        timestamp;         /**< Axxia time for Lionfish */
    TAaTimeBcn       bcnTime;           /**< Bcn time in raw format */
    u64              epochMicrosecond;  /**<  */
    u64              frameMicrosecond;  /**<  */
    SAaTimeOptimized utcTime;           /**<  */
} SAaSysTimeEventTimeSync;

/** @} */   /* dgUpCcsRtDspAaSysTime*/
/** @} */   /* dgUpCcsAaSysTime */
/** @} */   /* dgUpCcs */

#endif  /* _RT_DSP_AASYSTIME_DEFS_H */
