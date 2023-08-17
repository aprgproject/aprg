/** @file
*   @brief Common AaConfigSvcReg definitions
*   @copyright 2016 Nokia Networks. All rights reserved.
*   @copyright 2019 Nokia. All rights reserved.
*/

#ifndef _COMMON_IF_AACONFIG_SVC_REG_DEF_H_
#define _COMMON_IF_AACONFIG_SVC_REG_DEF_H_

#include "CcsCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaConfigSvcRegDefs AaConfigSvcReg definitions
 * @ingroup dgAaConfigSvcReg
 */

/**
 * @defgroup dgAaConfigSvcRegDefsCommon AaConfigSvcReg common definitions
 * @ingroup dgAaConfigSvcRegDefs
 */
/*@{*/

/** @brief Maximum length of service name */
#define AACONFIG_SERVICE_MAX_NAME_LENGTH 80

/** @brief SvcReg static CCS CPID */
#define AACONFIG_SVC_CCS_CPID                   0x0631

/** @brief Service Registry online */
#define AACONFIG_TAG_SVC_REGISTRY_ONLINE        "ccs.service.aaconfig.svc.registry.online"

/** @brief AaConfig service registry wildcard indicator */
#define AACONFIG_SVC_REG_MINOR_VERSION_WILDCARD   CCS_STATIC_CAST(u32,~0)
/** @brief AaConfig service registry infinite timer */
#define AACONFIG_SVC_REG_TIMER_INFINITE           CCS_STATIC_CAST(u32,0)

/** @brief AaConfig service registration scope */
typedef enum
{
  EAaConfigSvcRegScope_INVALID         = 0, /**< invalid */
  EAaConfigSvcRegScope_EE              = 1, /**< EE wide */
  EAaConfigSvcRegScope_CE              = 2, /**< CE wide */
  EAaConfigSvcRegScope_GLOBAL          = 3  /**< Global */
} EAaConfigSvcRegScope;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  //_COMMON_IF_AACONFIG_SVC_REG_DEF_H_
