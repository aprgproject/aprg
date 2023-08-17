/** @file
*   @brief Contains MCU AaStarupTime API
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: Copyright 2018 Nokia. All rights reserved.$
*/

#ifndef _MCU_IFAASTARTUPTIME_H_
#define _MCU_IFAASTARTUPTIME_H_

#include "CcsCommon.h"

#include <glo_def.h>
#include <IfAaSysCom_Defs.h>
#include <../Definitions/IfAaStartupTime_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *@defgroup dgAaStartupTime  AaStartupTime service
 *
 * Common Computer and Support SW Startup Time service
 *
 */

/**
 *@defgroup dgAaStartupTimeApi  AaStartupTime service API
 *@ingroup dgAaStartupTime
 */

/**
 *@defgroup dgAaStartupTimeApiMcu AaStartupTime MCU functions
 *@ingroup dgAaStartupTimeApi
 */

/*@{*/

/**
*******************************************************************************
*
*   @brief      Function reports checkpoint occurrence to CC&S
*
*   @param[in]  checkpointId                Checkpoint identifier
*   @param[in]  attributesCount             Number of attributes
*   @param[in]  attributes                  Checkpoint attributes, ignored when attributesCount is set to 0.
*
*   @par Description:
*   Function reports checkpoint occurrence by system component to CC&S. Should be used when event happens inside reporter's CE.
*   CC&S uses local node value to describe occurrence place.
*   Timestamp specific for checkpoint is fetched from LFS during function call. The same checkpoint can be reported multiple times and stored with different timestamp.
*
*   @return     Function returns status of operation.
*
*   @par Errors:
*   - EAaStartupTimeRet_Error
*   - EAaStartupTimeRet_NotSupported
*   - EAaStartupTimeRet_ShutdownOngoing
*   - EAaStartupTimeRet_NoMoreSpace
*   - EAaStartupTimeRet_InvalidParameter
*
*   @par Restrictions:
*   Not supported on FSMr2.
*   If AaStarupTime service is in shutdown phase ( cleaning resources, unregistered from application client ), then it could refuse to store checkpoint.
*   In such case EAaStartupTimeRet_ShutdownOngoing is returned.
*   If quota limit (see @ref AASTARTUPTIME_CHECKPOINTS_MAX_RUNTIME_QUOTA ) is reached, then no new checkpoint is accepted.
*   In such case EAaStartupTimeRet_NoMoreSpace is returned.
*   Number of checkpoints attributes is limited ( see @ref AASTARTUPTIME_MAX_ATTRIBUTES_COUNT ).
*   EAaStartupTimeRet_InvalidParameter is returned in case invalid number of checkpoints attributes ( bigger than @ref AASTARTUPTIME_MAX_ATTRIBUTES_COUNT ).
*   In addition EAaStartupTimeRet_InvalidParameter is returned, if attributesCount is different than 0 and attributes pointer is set to NULL.
*   The function implementation communicates with CCSDaemonExe instance located on the same node as reporter.
*   The function should be called only from EU having SysCom message queue.
*   The calling EU is blocked until the communication with CCSDaemonExe is completed.
*
*   @par Example:
*   @code
*   //Report checkpoint CHCKP-54(optical cable - sync attempt) with link-id 55 and sfp-connector-id equals 25
*   #define CHCKP_54_ATTRIBUTES_COUNT 2
*   TAaStartupCheckpointId checkpointId = 54;
*   u16 attributesCount = CHCKP_54_ATTRIBUTES_COUNT;
*   u32 checkpointAttributes[CHCKP_54_ATTRIBUTES_COUNT];
*   checkpointAttributes[0] = 55;
*   checkpointAttributes[1] = 25;
*   if( EAaStartupTimeRet_Ok != AaStartupTimeReportCheckpoint(checkpointId, attributesCount, checkpointAttributes) )
*   {
*       //  handle error
*   }
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
EAaStartupTimeRet AaStartupTimeReportCheckpoint(TAaStartupCheckpointId checkpointId, u16 attributesCount, const u32* attributes);

/**
*******************************************************************************
*
*   @brief      Function reports checkpoint occurrence inside neighbour nodes to CC&S
*
*   @param[in]  checkpointId                Checkpoint identifier
*   @param[in]  attributesCount             Number of attributes
*   @param[in]  attributes                  Checkpoint attributes, ignored when attributesCount is set to 0.
*   @param[in]  nodeId                      Node ID where event happens
*
*   @par Description:
*   Function reports checkpoint occurrence by system component to CC&S. Should be used when event happens inside other CE than reporter's CE.
*   CC&S uses provided node value to describe occurrence place.
*   Timestamp specific for checkpoint is fetched from LFS during function call. The same checkpoint can be reported multiple times and stored with different timestamp.
*
*   @return     Function returns status of operation.
*
*   @par Errors:
*   - EAaStartupTimeRet_Error
*   - EAaStartupTimeRet_NotSupported
*   - EAaStartupTimeRet_ShutdownOngoing
*   - EAaStartupTimeRet_NoMoreSpace
*   - EAaStartupTimeRet_InvalidParameter
*
*   @par Restrictions:
*   Not supported on FSMr2.
*   If AaStarupTime service is in shutdown phase ( cleaning resources, unregistered from application client ), then it could refuse to store checkpoint.
*   In such case EAaStartupTimeRet_ShutdownOngoing is returned.
*   If quota limit (see @ref AASTARTUPTIME_CHECKPOINTS_MAX_RUNTIME_QUOTA ) is reached, then no new checkpoint is accepted.
*   In such case EAaStartupTimeRet_NoMoreSpace is returned.
*   Number of checkpoints attributes is limited ( see @ref AASTARTUPTIME_MAX_ATTRIBUTES_COUNT ).
*   EAaStartupTimeRet_InvalidParameter is returned in case invalid number of checkpoints attributes ( bigger than @ref AASTARTUPTIME_MAX_ATTRIBUTES_COUNT ).
*   In addition EAaStartupTimeRet_InvalidParameter is returned, if attributesCount is different than 0 and attributes pointer is set to NULL.
*   EAaStartupTimeRet_InvalidParameter is returned, when nodeId is passed with value AASYSCOM_NODE_INVALID.
*   The function implementation communicates with CCSDaemonExe instance located on the same node as reporter.
*   The function should be called only from EU having SysCom message queue.
*   The calling EU is blocked until the communication with CCSDaemonExe is completed.
*
*   @par Example:
*   @code
*   //Report checkpoint CHCKP-54(optical cable - sync attempt) with link-id 55 and sfp-connector-id equals 25
*   #define CHCKP_54_ATTRIBUTES_COUNT 2
*   TAaStartupCheckpointId checkpointId = 54;
*   u16 attributesCount = CHCKP_54_ATTRIBUTES_COUNT;
*   u32 checkpointAttributes[CHCKP_54_ATTRIBUTES_COUNT];
*   checkpointAttributes[0] = 55;
*   checkpointAttributes[1] = 25;
*   TAaSysComNid nodeId = 0x123D;
*   if( EAaStartupTimeRet_Ok != AaStartupTimeReportCheckpointForNode(checkpointId, attributesCount, checkpointAttributes, nodeId) )
*   {
*       //  handle error
*   }
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
EAaStartupTimeRet AaStartupTimeReportCheckpointForNode(TAaStartupCheckpointId checkpointId, u16 attributesCount,
                                                       const u32* attributes, TAaSysComNid nodeId);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* _MCU_IFAASTARTUPTIME_H_ */
