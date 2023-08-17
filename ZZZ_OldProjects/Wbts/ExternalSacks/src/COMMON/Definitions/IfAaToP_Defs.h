/**
 * *******************************************************************************
 *  @file                 $HeadURL$
 *  @version              $LastChangedRevision$
 *  @date                 $LastChangedDate$
 *  @author               $Author$
 *
 *  @brief                AaToP definitions header file
 *  @module               AaToP
 *
 *  Copyright 2017 Nokia. All rights reserved.
 * *******************************************************************************/
#ifndef _IFAATOP_DEFS_H
#define _IFAATOP_DEFS_H

#include "CcsCommon.h"
#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaToPApi Definitions
 * @ingroup dgAaToP
 *
 *  Application Programming Interface, only supported in RCP.
 *
 *  Definitions
 *
 *  API specification (current): https://sharenet-ims.int.net.nokia.com/Overview/D551332685
 *
 * @{*/

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** @brief total support master clock */
#define DAATOP_NUM_OF_MASTER_CLOCK 4

/** @brief total accepted ToP master clock class by slave */
#define DAATOP_NUM_OF_ACCEPTED_CLOCK_CLASS 32

/** @brief max master clock ip address length */
#define DAATOP_IP_ADDRESS_LENGTH 64

/** @brief clock identity length */
#define DAATOP_CLOCK_IDENTITY_LENGTH 8


/** @brief synchronization status of the ToP slave clock   */
typedef enum EAaToPSlaveClockStatus
{
    EAaToPSlaveClockStatus_Locked   = 0,    /**< The ToP slave clock is synchronized */
    EAaToPSlaveClockStatus_UnLocked = 1     /**< The ToP slave clock is not synchronized */
} EAaToPSlaveClockStatus;

/** @brief The status of the ToP master clock   */
typedef enum EAaToPMasterClockStatus
{
    EAaToPMasterClockStatus_OK       = 0,    /**< The ToP master clock status is OK */
    EAaToPMasterClockStatus_Unknown  = 1,    /**< The ToP master clock status is unknown */
    EAaToPMasterClockStatus_Disabled = 2,    /**< The ToP master clock status is disabled */
    EAaToPMasterClockStatus_NOK      = 3     /**< The ToP master clock status is NOK */
} EAaToPMasterClockStatus;

/** @brief The profile type of the ToP master  */
typedef enum EAaTopStandardProfile
{
    EAaTopProfile_Telecom2008 = 0,           /**< Generic unicast profile for telecom */
    EAaTopProfile_ITU_G8275_2 = 1,           /**< ITU-T G.8275.2 profile */
    EAaTopProfile_Default     = 2,           /**< Not Specified, use RCP default profile */
    EAaTopProfile_NotSupport                 /**< Not support PTP profile */
} EAaTopStandardProfile;

/** @brief Enumerations for the function return values */
typedef enum EAaToPRetVal {
    EAaToPRetVal_NoError,           /**< Enum. for the function return value, when no error */
    EAaToPRetVal_Error,             /**< Enum. for the function return value, when an error exists */
    EAaToPRetVal_InvalidParamValue, /**< Enum. for the function return value  when invalid input param */
    EAaToPRetVal_NotInitialized,    /**< Enum. for the function retur value, when not initialized */
    EAaToPRetVal_StatusUnavailable, /**< Enum. for the function retur value, when ToP status is unavailable */
    EAaToPRetVal_NumOfRetVals       /**< The number of available return values */
} EAaToPRetVal;

/** @brief the counter type of ToP */
typedef enum EAaToPCounterId
{
    EAaToPCounter_RxSyncMsgNum = 0, /**< The number of received PTP sync event messages in the latest 1 minute */
    EAaToPCounter_MinPhaseError,    /**< The minimum estimated phase error over the latest 1 minute */
    EAaToPCounter_AvgPhaseError,    /**< The average estimated phase error over the latest 1 minute */
    EAaToPCounter_MaxPhaseError,    /**< The maximum estimated phase error over the latest 1 minute */
    EAaToPCounter_LockedSec         /**< The number of seconds during this interval while the Timing over Packet
                                                                 phase synchronization service was in locked state */
} EAaToPCounterId;

/** @brief Enumerations for the status of ToP counter */
typedef enum EAaToPCounterStatus
{
    EAaToPCounterStatus_Success = 0, /**< Status of the counter: a valid counter value is obtained */
    EAaToPCounterStatus_Failed  = 1  /**< Status of the counter: fail to obtain counter data */
} EAaToPCounterStatus;

/**  @brief struct for configurable top parameters per master */
typedef struct SAaToPMasterConfig
{
    char topMasterIpAddr[DAATOP_IP_ADDRESS_LENGTH]; /**< ToP master clock IP address */
    i32  topLocalPriority;                          /**< Only valid for ITU-T G.8275.2 profile */
} SAaToPMasterConfig;

/**  @brief struct for application configure top parameters */
typedef struct SAaToPConfigure
{
    i32                   topSyncMsgRate;         /**< Number of sync messages expected to be received in second */
    EAaTopStandardProfile topProfile;
    u8                    topDscp;                /**< DSCP value of PTP message IP header */
    u8                    topDomainNumber;        /**< Defines the scope of PTP messaging  */
    u8                    topNumberofMaster;      /**< Number of ToP master clock */
    u8                    topNumOfAcceptedClockClass;  /**< Number of accepted ToP master clock class */
    u8                    topAcceptedClockClassList[DAATOP_NUM_OF_ACCEPTED_CLOCK_CLASS];  /**< ToP master clock class list */
    SAaToPMasterConfig    topMasterList[DAATOP_NUM_OF_MASTER_CLOCK]; /**< ToP master list */
    char                  topSrcIpAddr[DAATOP_IP_ADDRESS_LENGTH];    /**< An IPv4 or IPv6 address over which the ToP traffic is transported */
} SAaToPConfigure;

/**  @brief PTP master clock states */
typedef struct SAaToPMasterStates
{
    EAaToPSlaveClockStatus  lockStatus;            /**< Shows synchronizaiton status of the ToP slave clock */
    char                    topMasterIpAddr[DAATOP_IP_ADDRESS_LENGTH]; /**< ToP master clock IP address */
    EAaToPMasterClockStatus topMasterClockStatus;  /**< Indicates the status of the ToP master clock */
    u8                      topGMasterClockIdentity[DAATOP_CLOCK_IDENTITY_LENGTH]; /**<  Clock identity of grandmaster, part of PortIdentity */
    u8                      topGMasterClockClass;  /**< Clock class of grandmaster, part of ClockQuality */
    u8                      topGMClockAccuracy;    /**< Clock accuracy of grandmaster, part of ClockQuality */
    u16                     topGMOffsetScaledLogVariance; /**< OffsetScaledLogVariance of grandmaster, part of ClockQuality */
    u8                      topMasterClockIdentity[DAATOP_CLOCK_IDENTITY_LENGTH];  /**<  Clock identity of master, part of PortIdentity */
    u16                     topMasterPortNumber;   /**< Port number of master clock, part of PortIdentity */
    u16                     topSlavePortNumber;    /**< Port number of slave clock, part of PortIdentity */
    TBoolean                timeTraceable;         /**< Indicates whether the timesacle and currentUtcOffset are traceable to a primary reference clock. */
    TBoolean                freqTraceable;         /**< Indicates whether the frequency determining the timescale is traceable to a primary reference clock. */
    TBoolean                activeState;           /**< Indicates whether master is selected as active master or not. (GLO_TRUE = active, GLO_FALSE = inactive) */
    TBoolean                reachable;             /**< Indicates whether master is reachable or not. (GLO_TRUE = reachable, GLO_FALSE = unreachable) */
    u8                      topStepsRemoved;       /**< The "distance" measured by the number of boundary clocks between the local clock and the foreign master */
    u8                      topGMPriority1;        /**< The attribute priority1 is used in the execution of the best master clock algorithm */
    u8                      topGMPriority2;        /**< The attribute priority2 is used in the execution of the best master clock algorithm */
    u8                      pad;
} SAaToPMasterStates;

/**  @brief struct for application query top status */
typedef struct SAaToPStatus
{
    u8  waitingTime;           /**< The time a random value between 30 and 35 sec the ToP slave has to wait, before switching over to another ToP master. */
    u8  topSlaveClockClass;    /**< Clock class of slave clock, part of PortIdentity */
    u8  topNumberOfMasters;    /**< Number of ToP master */
    u8  pad;
    SAaToPMasterStates masterStates[DAATOP_NUM_OF_MASTER_CLOCK]; /**< List of master clock states */
    u8  topSlaveClockIdentity[DAATOP_CLOCK_IDENTITY_LENGTH];     /**< Clock identity of slave clock, part of PortIdentity */
} SAaToPStatus;

/**  @brief struct for ToP counter info */
typedef struct SAaToPCounterData
{
    EAaToPCounterId     counterId;     /**< ID of the counter which value is given */
    EAaToPCounterStatus counterStatus; /**< Status of the counter */
    i64                 counterValue;  /**< Value of the counter */
} SAaToPCounterData;

/**  @brief struct for ToP phase sync statistics */
typedef struct SAaToPPhaseSyncStats
{
    u32                 itemNum;       /**< Number of counters which value is given */
    SAaToPCounterData   counters[1];   /**< Counter data (one element per counter ID; number of itemNum elements) */
} SAaToPPhaseSyncStats;

#ifdef __cplusplus
}
#endif

/**@}*/

#endif /*  _IFAATOP_DEFS_H */

