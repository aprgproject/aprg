/** @file
*   @brief Contains AaStartup definitions shared between CC&S MCU and RT
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: Copyright 2018 Nokia. All rights reserved.$
*/

#ifndef _MCU_RT_IF_AASTARTUP_DEFS_H_
#define _MCU_RT_IF_AASTARTUP_DEFS_H_

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaStartupDefs AaStartup definitions
 * @ingroup dgAaStartup
 */

/**
 * @defgroup dgAaStartupDefsSharedMcuRt AaStartup shared definitions for MCU and RT
 * @ingroup dgAaStartupDefs
 */

/*@{*/

/** AaStartup service - static cpid of shutdown task */
#define AASTARTUP_SHUTDOWN_TASK_CPID 0x065D

/** @brief AaStartup reset types. Used to inform CC&S about reset type. */
typedef enum EAaStartupResetType{
  EAaStartupReset_Other                      = 0,           /**< Other reset type than defined*/
  EAaStartupReset_Warm                       = 7,           /**< Warm reset */
  EAaStartupReset_SiteReset                  = 15,          /**< Site reset */
  EAaStartupReset_BtsReset                   = 16,          /**< Bts group reset */
  EAaStartupReset_RatReset                   = 17,          /**< RAT reset */
  EAaStartupReset_Rapid                      = 19           /**< Rapid reset */
} EAaStartupResetType;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* _MCU_RT_IF_AASTARTUP_DEFS_H_ */
