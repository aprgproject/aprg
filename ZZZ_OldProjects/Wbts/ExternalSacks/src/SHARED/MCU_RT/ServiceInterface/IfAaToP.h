/**
*******************************************************************************
* @file                 $HeadURL$
* @version              $LastChangedRevision$
* @date                 $LastChangedDate$
* @author               $Author$
*
* @brief                AaToP interface header file
* @module               AaToP
*
* Copyright 2017 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAATOP_H
#define _MCU_RT_IFAATOP_H
#include "CcsCommon.h"

#ifdef CCS_NEW_IF_STRUCTURE
#include <IfAaToP_Defs.h>
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
 * @defgroup dgAaToPApi ToP Synchronization Service
 * @ingroup dgAaToP
 *
 *  Application Programming Interface, only supported in RCP.
 *
 *
 *  API specification (current): https://sharenet-ims.int.net.nokia.com/Overview/D551332685
 *
 * @{*/


/*----------------------- INCLUDED FILES --------------------------------------*/

#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------ PUBLIC INTERFACES ---------------------------------*/

/**
*******************************************************************************
*
*   @brief      Configure PTP synchronization parameters and start PTP service
*
*   @param[in]  topConfigPtr       A pointer to ToP paramters buffer
*
*   @return #EAaToPRetVal_NoError,
*           #EAaToPRetVal_Error or
*           #EAaToPRetVal_InvalidParamValue.
*
*   @par Description:
*   This function configures PTP synchronization paramters and start PTP service.
*   Before starting PTP service, all NTP external server will be removed in order to avoid
*   synchronization conflict between PTP and NTP.
*
*   @par Errors:
*   [#EAaToPRetVal_Error] Internal error of PTP Service.
*   [#EAaToPRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*      - None
*
*   @par Example:
*   @code
*   // Here is the usage example for the function.
*   SAaToPConfigure topConfig = {0};
*   const char* const topSrcIpAddr = "10.10.10.2";
*   const char* const topMasterIpAddr = "10.10.10.10";
*   EAaToPRetVal      retval;
*
*   topConfig.topDscp = 46;
*   topConfig.topDomainNumber = 0;
*   topConfig.topSyncMsgRate = 1;
*   topConfig.topProfile = EAaTopProfile_Telecom2008;
*   topConfig.topNumOfAcceptedClockClass = 2;
*   topConfig.topAcceptedClockClassList[0] = 6;
*   topConfig.topAcceptedClockClassList[1] = 7;
*   topConfig.topNumberofMaster = 1;
*   strncpy(topConfig.topMasterList[0].topMasterIpAddr, topMasterIpAddr, sizeof(topConfig.topMasterList[0].topMasterIpAddr));
*   topConfig.topMasterList[0].topLocalPriority[0] = 0;
*   strncpy(topConfig.topSrcIpAddr, topSrcIpAddr, sizeof(topConfig.topSrcIpAddr));
*
*   retval = AaToPConfigure(&topConfig);
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
*   @see None
*
******************************************************************************/
EAaToPRetVal AaToPConfigure(const SAaToPConfigure *const topConfigPtr);

/**
*******************************************************************************
*
*   @brief      Get ToP clock and synchronization status information from PTP service.
*
*   @param[out]  topStatusPtr       A pointer to ToP slave status buffer
*
*   @return #EAaToPRetVal_NoError,
*           #EAaToPRetVal_Error or
*           #EAaToPRetVal_NotInitialized or
*           #EAaToPRetVal_StatusUnavailable.
*
*   @par Description:
*   This function will provide ToP synchronization status information, including slave
*   clock information, master/grandmaster clock information and synchronization
*   status between slave clock and master clock, then store into input buffer.
*
*   @par Errors:
*   [#EAaToPRetVal_Error] Internal error of PTP Service.
*   [#EAaToPRetVal_NotInitialized] PTP service not be started.
*   [#EAaToPRetVal_StatusUnavailable] PTP status is unavailable.
*
*   @par Restrictions:
*      - None
*
*   @par Example:
*   @code
*   // Here is the usage example for the function.
*   SAaToPStatus topStatus = {0};
*   EAaToPRetVal      retval;
*
*   retval = AaToPGetStatus(&topConfig);
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
*   @see None
*
******************************************************************************/
EAaToPRetVal AaToPGetStatus(SAaToPStatus *topStatusPtr);

/**
*******************************************************************************
*
*   @brief    Get ToP counter statistics informations.
*
*   @param[in/out]  topSyncStatsPtr   A pointer to ToP counter statistics informations buffer
*
*   @return
*       - #EAaToPRetVal_NoError: counter data can be obtained, but still need to check the result
*                                             of a certain counter, if retrieve failed, the data is invalid
*       - #EAaToPRetVal_Error: get domain number failed
*       - #EAaToPRetVal_InvalidParamValue: incorrect input parameter detected
*
*   @par Description:
*   This function specify an interface to collect ToP counter statistical information.
*   This function provides the retrieve result of a certain counter. If retrieve failed,
*   the counter value will be an invalid value.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*   SAaToPPhaseSyncStats *topSyncStatsPtr;
*   EAaToPRetVal  ret;
*   u32                itemNum = 2;
*   size_t             length;
*
*   length = sizeof(SAaToPPhaseSyncStats) + (itemNum - 1)*sizeof(SAaToPCounterData);
*   topSyncStatsPtr = (SAaToPPhaseSyncStats *)malloc(length);
*   memset(topSyncStatsPtr, 0 , length);
*
*   topSyncStatsPtr->itemNum = itemNum;
*   topSyncStatsPtr->counters[0].counterId = EAaToPCounter_MinPhaseError;
*   topSyncStatsPtr->counters[1].counterId = EAaToPCounter_MaxPhaseError;
*
*   ret = AaToPGetCounter(topSyncStatsPtr);
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
*   AaToPGetCounter()
******************************************************************************/
EAaToPRetVal AaToPGetCounter(SAaToPPhaseSyncStats *topSyncStatsPtr);

#ifdef __cplusplus
}
#endif

/**@}*/

#endif /*  _MCU_RT_IFAATOP_H */

