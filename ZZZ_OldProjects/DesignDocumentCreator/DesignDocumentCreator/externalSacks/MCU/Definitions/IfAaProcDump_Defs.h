/** @file
*   @brief This file contains the definitions used in AaProcDump service.
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: Copyright 2016 Nokia Networks. All rights reserved.$
*/

#ifndef _MCU_IF_AAPROCDUMP_DEFS_H_
#define _MCU_IF_AAPROCDUMP_DEFS_H_

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaProcDumpMcuDefs AaProcDump Definitions
 * @ingroup  dgAaProcDumpMcu
 */

/** @{ */

/**
******************************************************************************
*
* @verbatim
* Tag name:         sys.procdump.memory.budget
*
* Direction:        input
*
* Description:      Memory budget for procdump service in kB.
*
* Effect analysis:  If this tag is not set, a value of RAD flag
*                   ERadCcsMcu_AaProcDumpMemoryBudget is used.
*
* Restriction:      The number must be maximum 25 percent of RP RAM total size,
*                   Minimum FCT MCU: 2.04MB
*                   Minimum FSP MCU: 0.54MB
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <0, 0xFFFFFFFF>
*
* Define:           AAPROCDUMP_CONFIG_TAG_MEMORY_BUDGET
*
* See:              none
* @endverbatim
*****************************************************************************/
#define AAPROCDUMP_CONFIG_TAG_MEMORY_BUDGET "sys.procdump.memory.budget"

/**
******************************************************************************
*
* @verbatim
* Tag name:         sys.procdump.initial.delay
*
* Direction:        input
*
* Description:      Initial delay before taking first procdump, in seconds.
*
* Effect analysis:  If this tag is not set, a value of RAD flag
*                   ERadCcsMcu_AaProcDumpInitialDelay is used.
*
* Restriction:      none
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <0, 600>
*
* Define:           AAPROCDUMP_CONFIG_TAG_INITIAL_DELAY
*
* See:              none
* @endverbatim
*
*****************************************************************************/
#define AAPROCDUMP_CONFIG_TAG_INITIAL_DELAY "sys.procdump.initial.delay"

/**
******************************************************************************
*
* @verbatim
* Tag name:         sys.procdump.periodic.interval
*
* Direction:        input
*
* Description:      Interval for periodic procdump taking, in seconds.
*
* Effect analysis:  If this tag is not set, a value of RAD flag
*                   ERadCcsMcu_AaProcDumpPeriodicInterval is used.
*
* Restriction:      none
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <300, 0xFFFFFFFF>
*
* Define:           AAPROCDUMP_CONFIG_TAG_PERIODIC_INTERVAL
*
* See:              none
* @endverbatim
*
*****************************************************************************/
#define AAPROCDUMP_CONFIG_TAG_PERIODIC_INTERVAL "sys.procdump.periodic.interval"

/**
******************************************************************************
*
* @verbatim
* Tag name:         sys.procdump.at.shutdown.enable
*
* Direction:        input
*
* Description:      Enable performing procdump at shutdown:
*                   0: disabled;
*                   1: enabled.
*
* Effect analysis:  If this tag is not set, a value of RAD flag
*                   ERadCcsMcu_AaProcDumpAtShutdownEnable is used.
*
* Restriction:      none
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <0, 1>
*
* Define:           AAPROCDUMP_CONFIG_TAG_SHUTDOWN_ENABLE
*
* See:              none
* @endverbatim
*
*****************************************************************************/
#define AAPROCDUMP_CONFIG_TAG_SHUTDOWN_ENABLE "sys.procdump.at.shutdown.enable"

/**
******************************************************************************
*
* @verbatim
* Tag name:         sys.procdump.at.snapshot.disable
*
* Direction:        input
*
* Description:      Disable performing procdump at snapshot:
*                   0: enabled;
*                   1: disabled.
*
* Effect analysis:  If this tag is not set, a value of RAD flag
*                   ERadCcsMcu_AaProcDumpAtSnapshotDisable is used.
*
* Restriction:      none
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <0, 1>
*
* Define:           AAPROCDUMP_CONFIG_TAG_SNAPSHOT_DISABLE
*
* See:              none
* @endverbatim
*
*****************************************************************************/
#define AAPROCDUMP_CONFIG_TAG_SNAPSHOT_DISABLE "sys.procdump.at.snapshot.disable"

/**
******************************************************************************
*
* @verbatim
* Tag name:         sys.procdump.content.full.disable
*
* Direction:        input
*
* Description:      Disable performing full content of procdump:
*                   0: enabled;
*                   1: disabled.
*
* Effect analysis:  If this tag is not set, a value of RAD flag
*                   ERadCcsMcu_AaProcDumpContentFullDisable is used.
*
* Restriction:      none
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <0, 1>
*
* Define:           AAPROCDUMP_CONFIG_TAG_CONTENT_FULL_DISABLE
*
* See:              none
* @endverbatim
*
*****************************************************************************/
#define AAPROCDUMP_CONFIG_TAG_CONTENT_FULL_DISABLE "sys.procdump.content.full.disable"

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* _MCU_IF_AAPROCDUMP_DEFS_H_ */
