/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaLteTime defintions header file
* @module                AaLteTime
*
* Copyright 2014, 2018 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _IFAALTETIME_DEFS_H
#define _IFAALTETIME_DEFS_H
#include "CcsCommon.h"
#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup dgAaLteTimeDefinitions Definitions
* @ingroup dgAaLteTime
*/

/**
* @defgroup dgAaLteTimeDefinitionsCommon COMMON Definitions
* @ingroup dgAaLteTimeDefinitions
*/

/*@{*/

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** Limit for context switch in basic time units. */
#define DAALTE_TIME_SERVICES_SLEEP_LIMIT_FOR_CONTEXT_CHANGE 64

/** LTE hyperframe cycle */
#define DAALTE_HYPERFRAME_CYCLE 1024

/** Frames in hyperframe. */
#define DAALTE_FRAMES_IN_HYPERFRAME 1024

/** Slots in LTE frame. */
#define DAALTE_SLOTS_IN_FRAME 20

/** Subframes in LTE frame. */
#define DAALTE_SUBFRAMES_IN_FRAME 10

/** Basic time units in LTE slot. */
#define DAALTE_BASIC_TIME_UNITS_IN_SLOT 15360

/** Don't care hyperframe number. */
#define DAALTETIME_VALID_NEXT_HYPERFRAME 0xFFFF

/** @brief Type for the BTS hyper frame number. Duration of hyper frame is
           1024 frames, 10240 ms. */
typedef u32 TAaLteBtsHyperFrameNr;

/** @brief Type for the BTS frame number. Duration of frame is 10 ms. */
typedef u32 TAaLteBtsFrameNr;

/** @brief Type for the BTS subframe number, which is length of 1/10 frame. */
typedef u32 TAaLteBtsSubframeNr;

/** @brief Type for the BTS slot number. */
typedef u32 TAaLteBtsSlotNr;

/** @brief Type for the BTS basic time unit number.*/
typedef u32 TAaLteBtsBasicTUNr;

/** @brief Type for the timer identifier. */
typedef u32 TAaLteTimerId;

/** @brief Type for the callback function. Used in callback based timeout
 *         requests.
 *
 * @return None.
 */
typedef void (*TAaLteTimeFunctionPtr) (void*);

/** @brief Enumerations for the LTE time match level. */
typedef enum _EAaLteMatchLevel {
    EAaLteMatchLevel_HyperFrame,    /**< Enum. for the hyper frame level. */
    EAaLteMatchLevel_Frame,         /**< Enum. for the frame level. */
    EAaLteMatchLevel_Slot,          /**< Enum. for the slot level. */
    EAaLteMatchLevel_BasicTU,       /**< Enum. for the basic time unit level. */
    EAaLteMatchLevel_PeriodicHyperFrame, /**< Enum. for the periodic hyper
                                              frame level. */
    EAaLteMatchLevel_PeriodicFrame, /**< Enum. for the periodic frame level. */
    EAaLteMatchLevel_PeriodicSlot,  /**< Enum. for the periodic slot level. */
    EAaLteMatchLevel_PeriodicBasicTU,  /**< Enum. for the periodic basic time
                                        *   unit level. */
    EAaLteMatchLevel_NumOfMatchLevels  /**< The number of match levels. */
}EAaLteMatchLevel;

/** @brief Enumerations for the callback priority. */
typedef enum _EAaLteTimePriority {
    EAaLteTimePriority_Low,    /**< Enum. for the low callback priority. */
    EAaLteTimePriority_Medium, /**< Enum. for the medium callback priority. */
    EAaLteTimePriority_High,   /**< Enum. for the high callback priority. */
    EAaLteTimePriority_Interrupt,   /**< Enum. for the callback that will be
                                         performed during the interrupt. */
    EAaLteTimePriority_NumOfPriorities /**< The number of priorities. */
}EAaLteTimePriority;

/** @brief Enumerations for the function return values. */
typedef enum _EAaLteTimeRetVal {
    EAaLteTimeRetVal_NoError,           /**< Enum. for the function return
                                          *  value, when no error. */
    EAaLteTimeRetVal_Error,             /**< Enum. for the function return
                                          *  value, when an error exists. */
    EAaLteTimeRetVal_InvalidParamValue, /**< Enum. for the function return
                                          *  value  when invalid input param */
    EAaLteTimeRetVal_NotInitialized,    /**< Enum. for the function return
                                          *  value, when not initialized */
    EAaLteTimeRetVal_HwDriverNotReady,  /**< Enum. for the function return
                                          *  value, when not driver not ready */
    EAaLteTimeRetVal_TimerAllocFailed,  /**< Enum. for the function return
                                          *  value, when Timer alloc problem */
    EAaLteTimeRetVal_SyscomeAllocFailed,/**< Enum. for the function return
                                          *  value, when SysCome alloc problem */
    EAaLteTimeRetVal_PeriodTooShort,    /**< Enum. for the function return
                                         *  value, when period too short */
    EAaLteTimeRetVal_NumOfRetVals       /**< The number of available return
                                          *  values*/
}EAaLteTimeRetVal;

/** @brief Enumerations for sync options used in AaLteBtsTimeTimermCreate */
typedef enum _EAaLteTimeSync {
    EAaLteTimeSync_SpecificLteTime,       /**<Enum. for sync to specific LTE
                                            * time */
    EAaLteTimeSync_StartOfNextHyperframe, /**<Enum. for sync to start of next
                                            * hyperframe */
    EAaLteTimeSync_StartOfNextFrame,      /**<Enum. for sync to start of next
                                            * frame */
    EAaLteTimeSync_StartOfNextSubframe,   /**<Enum. for sync to start of next
                                            * subframe */
    EAaLteTimeSync_StartOfNextSlot,       /**<Enum. for sync to start of next
                                            * slot */
    EAaLteTimeSync_NumOfSyncs             /**< The number of syncs */
}EAaLteTimeSync;

/**   @brief Enumerations for the Aif Radio offset type configuration. */
typedef enum _EAaLteOffsetType
{
    EAaLteOffsetType_None = 0,
    EAaLteOffsetType_Dl,
    EAaLteOffsetType_Ul
} EAaLteOffsetType;

#ifdef __cplusplus
}
#endif

/**@}*/

#endif /*  _IFAALTETIME_DEFS_H */

