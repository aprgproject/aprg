/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaWcdmaTime definitions header file
* @module                AaWcdmaTime
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _IFAAWCDMATIME_DEFS_H
#define _IFAAWCDMATIME_DEFS_H
#include "CcsCommon.h"
#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
*@defgroup dgAaWcdmaTimeApi Definitions
*@ingroup dgAaWcdmaTime
*
* Application Programming Interface.
*
* Definitions
*
* API specification (current): https://sharenet-ims.int.net.nokia.com/Open/D-171133
*
*@{*/

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/**< @brief When requested delay is bigger than limit, OS can change context. */
#define DAAWCDMA_TIME_SERVICES_SLEEP_LIMIT_CHIPS_FOR_CONTEXT_CHANGE (8)

/** @brief WCDMA hyperframe cycle */
#define DAAWCDMA_HYPERFRAME_CYCLE (1)

/** @brief Frames in hyperframe. */
#define DAAWCDMA_FRAMES_IN_HYPERFRAME (4096)

/** @brief Slots in WCDMA frame. */
#define DAAWCDMA_SLOTS_IN_FRAME (15)

/** @brief Chips in WCDMA slot */
#define DAAWCDMA_CHIPS_IN_SLOT (2560)

/** @brief Don't care hyperframe number. */
#define DAAWCDMATIME_VALID_NEXT_HYPERFRAME (0xFF)

/**< @brief Type for the 64-bit system time */
typedef u64 TAaWcdmaTime64;

/**< @brief Type for the BTS frame number (BFN). */
typedef u32 TAaBtsFrameNr;

/**< @brief Type for the BTS subframe number, which is length of 1/5 frame. */
typedef u32 TAaBtsSubframeNr;

/**< @brief Type for the BTS slot number. */
typedef u32 TAaBtsSlotNr;

/**< @brief Type for the BTS subslot number, which is length of 1/20 slot. */
typedef u32 TAaBtsSubslotNr;

/**< @brief Type for the BTS chip number. */
typedef u32 TAaBtsChipNr;

/**< @brief Type for the number of timers. */
typedef u32 TAaWcdmaTimerNumOfTimers;

/**< @brief Type for the timer identifier. */
typedef u32 TAaWcdmaTimerId;

/** @brief Type for the BTS hyper frame number. Duration of hyper frame is
           1024 frames, 10240 ms. */
typedef u32 TAaWcdmaBtsHyperFrameNr;

/** @brief Type for the BTS frame number. Duration of frame is 10 ms. */
typedef u32 TAaWcdmaBtsFrameNr;

/** @brief Type for the BTS subframe number, which is length of 1/10 frame. */
typedef u32 TAaWcdmaBtsSubframeNr;

/** @brief Type for the BTS slot number. */
typedef u32 TAaWcdmaBtsSlotNr;

/** @brief Type for the BTS basic time unit number.*/
typedef u32 TAaWcdmaBtsBasicTUNr;

/** @brief Type for the callback function. Used in callback based timeout
 *         requests.
 * 
 * @return None.
 */
typedef void (*TAaWcdmaTimeFunctionPtr) (void*);

/**   @brief Enumerations for the WCDMA time match level. */
typedef enum _EAaWcdmaMatchLevel {
    EAaWcdmaMatchLevel_Frame,           /**< Enum. for the frame level. */
    EAaWcdmaMatchLevel_Slot,            /**< Enum. for the slot level. */
    EAaWcdmaMatchLevel_Chip,            /**< Enum. for the chip level. */
    EAaWcdmaMatchLevel_PeriodicFrame,   /**< Enum. for the periodic frame
                                         *   level. */
    EAaWcdmaMatchLevel_PeriodicSlot,    /**< Enum. for the periodic slot 
                                         *   level. */
    EAaWcdmaMatchLevel_PeriodicChip,    /**< Enum. for the periodic chip
                                         *   level. */
    EAaWcdmaMatchLevel_NumOfMatchLevels /**< The number of match levels. */
}EAaWcdmaMatchLevel;

/**   @brief Enumerations for the callback priority. */
typedef enum _EAaWcdmaTimePriority {
    EAaWcdmaTimePriority_Low,    /**< Enum. for the low callback priority. */
    EAaWcdmaTimePriority_Medium, /**< Enum. for the medium callback priority.*/
    EAaWcdmaTimePriority_High,   /**< Enum. for the high callback priority. */
    EAaWcdmaTimePriority_Interrupt,   /**< Enum. for the callback that will be
                                      performed during the interrupt. */
    EAaWcdmaTimePriority_NumOfPriorities /**< The number of priorities. */
}EAaWcdmaTimePriority;

/**   @brief Enumerations for the function return values. */
typedef enum _EAaWcdmaTimeRetVal {
    EAaWcdmaTimeRetVal_NoError,           /**< Enum. for the function return
                                            *  value, when no error. */
    EAaWcdmaTimeRetVal_Error,             /**< Enum. for the function return
                                            *  value, when an error exists. */
    EAaWcdmaTimeRetVal_InvalidParamValue, /**< Enum. for the function return
                                            *  value  when invalid input param */
    EAaWcdmaTimeRetVal_NotInitialized,    /**< Enum. for the function return
                                            *  value, when not initialized */
    EAaWcdmaTimeRetVal_HwDriverNotReady,  /**< Enum. for the function return
                                            *  value, when not driver not ready */
    EAaWcdmaTimeRetVal_TimerAllocFailed,  /**< Enum. for the function return
                                            *  value, when Timer alloc problem */
    EAaWcdmaTimeRetVal_SyscomeAllocFailed,/**< Enum. for the function return
                                            *  value, when SysCome alloc problem */
    EAaWcdmaTimeRetVal_PeriodTooShort,
    EAaWcdmaTimeRetVal_NumOfRetVals       /**< The number of available return
                                            *  values*/
}EAaWcdmaTimeRetVal;

/** @brief Enumerations for sync options used in AaWcdmaBtsTimeTimermCreate */
typedef enum _EAaWcdmaTimeSync {
    EAaWcdmaTimeSync_SpecificWcdmaTime,       /**<Enum. for sync to specific WCDMA
                                            * time */
    EAaWcdmaTimeSync_StartOfNextHyperframe, /**<Enum. for sync to start of next
                                            * hyperframe */
    EAaWcdmaTimeSync_StartOfNextFrame,      /**<Enum. for sync to start of next
                                            * frame */
    EAaWcdmaTimeSync_StartOfNextSubframe,   /**<Enum. for sync to start of next
                                            * subframe */
    EAaWcdmaTimeSync_StartOfNextSlot,       /**<Enum. for sync to start of next
                                            * slot */
    EAaWcdmaTimeSync_NumOfSyncs             /**< The number of syncs */
}EAaWcdmaTimeSync;

#ifdef __cplusplus
}
#endif

/**@}*/

#endif /*  _IFAAWCDMATIME_DEFS_H */

