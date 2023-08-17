/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaConfig defintions header file.
* @module                AaConfig
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _IFAACONFIG_DEFS_H
#define _IFAACONFIG_DEFS_H

/*----------------------- INCLUDED FILES -------------------------------------*/

#include "CcsCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup dgAaConfig AaConfig API
*
* Common Computer and Support SW Configuration AaConfig service API.
*
*/

/**
 * @defgroup dgAaConfigDefs AaConfig definitions
 * @ingroup dgAaConfig
 */

/**
 * @defgroup dgAaConfigDefsCommon AaConfig common definitions
 * @ingroup dgAaConfigDefs
 */
/*@{*/

/** @brief AaConfig return values */
typedef enum EAaConfigRet{
  EAaConfigRet_Ok                = 0,  /**< Ok. */
  EAaConfigRet_InvalidParameter,       /**< Invalid parameter. */
  EAaConfigRet_TagNotFound,            /**< Tag is not found */
  EAaConfigRet_NotRegistered,          /**< Not registered */
  EAaConfigRet_PublicFailure,          /**< Something else went wrong when
                                            trying to set public tag */
  EAaConfigRet_NotAllowed,             /**< Requested action is not allowed,
                                            e.g. some initialization is already
                                            been done and can't be done again. */
  EAaConfigRet_TagNotSet,              /**< Tag exist but it has no assigned value. */
  EAaConfigRet_TagSizeMismatch,        /**< Tag length does not match requested size. */
  EAaConfigRet_TagTypeMismatch,        /**< Tag type does not match requested type. */
  EAaConfigRet_NoMem,                  /**< Memory allocation failed. */
  EAaConfigRet_Error,                  /**< Unspecified internal error. */
  EAaConfigRet_NotInitialized,         /**< Service is not yet initialized. */

  EAaConfigRet_NbrOf                   /**< Always the last one. */

} EAaConfigRet;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* _IFAACONFIG_DEFS_H */
