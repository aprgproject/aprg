/** @file
*   @brief Contains common AaStarupTime definitions
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: Copyright 2018 Nokia. All rights reserved.$
*/

#ifndef _MCU_IF_AASTARTUPTIME_DEFS_H_
#define _MCU_IF_AASTARTUPTIME_DEFS_H_

#include <glo_def.h>
#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaStartupTimeDefs AaStartupTime definitions
 * @ingroup dgAaStartupTime
 */

/**
 * @defgroup dgAaStartupTimeDefsMcu AaStartupTime MCU definitions
 * @ingroup dgAaStartupTimeDefs
 */

/*@{*/

/** AaStartupTime service cpid */
#define AASTARTUPTIME_SERVICE_CPID 0x065B

/** If tag is set to any value, then fetching checkpoints from LFS is disabled. Tag type is u32.
 *  Tag change is supported in next run.*/
#define AASTARTUPTIME_FETCH_LFS_CHECKPOINTS_DISABLED "ccs.service.aastartuptime.fetch.lfs.checkpoints.disabled"

/** Describes ( in KB ) maximum checkpoint runtime buffer size. Tag change is supported in next run.
 *  0 value disables checkpoints storage by CC&S. In addition functionality is disabled, if tag is not set.
 *  If runtime buffer size reaches quota, then new checkpoints are ignored. */
#define AASTARTUPTIME_CHECKPOINTS_MAX_RUNTIME_QUOTA "ccs.service.aastartuptime.checkpoints.max.runtime.quota"

/** Describes maximum attributes count for every checkpoint */
#define AASTARTUPTIME_MAX_ATTRIBUTES_COUNT 10

/** Type descibing checkpoint's ID */
typedef u32 TAaStartupCheckpointId;

/**  Helper structure describing u64 type via two u32 types. */
typedef struct SAaStartupU64
{
  u32 msw;                                      /**< Most significant part of u64*/
  u32 lsw;                                      /**< Least significant part of u64 */
} SAaStartupU64;

/** @brief AaStartupTime operation status */
typedef enum EAaStartupTimeRet{
  EAaStartupTimeRet_Ok                  = 0,    /**< Ok */
  EAaStartupTimeRet_NotSupported,               /**< Not supported functionality */
  EAaStartupTimeRet_InvalidParameter,           /**< Invalid parameter */
  EAaStartupTimeRet_Error,                      /**< Unspecified internal error */
  EAaStartupTimeRet_NoMoreSpace,                /**< Quota describing size reached, no more space in buffer */
  EAaStartupTimeRet_ShutdownOngoing,            /**< Operation not allowed ( service in shutdown phase ) */
} EAaStartupTimeRet;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* _MCU_IF_AASTARTUPTIME_DEFS_H_ */
