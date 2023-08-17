/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaMem MCU_RT definitions.
* @module                AaMem
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _COMMON_IFAAMEM_DEF_H_
#define _COMMON_IFAAMEM_DEF_H_

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaMem AaMem API
 */

/**
 * @defgroup dgAaMemApiCommon AaMem COMMON API
 * @ingroup dgAaMem
 */

/* @{ */

/** @brief AaMem public return codes */
typedef enum EAaMemRet
{
    EAaMemRet_Ok = 0,                   /**< No errors occurred */
    EAaMemRet_NullParameter,            /**< NULL parameter error */
    EAaMemRet_UnexistentPoolId,         /**< Unexistent pool ID */
    EAaMemRet_RefCountMaxLimitExceeded, /**< Maximum limitation of block references exceeded */
    EAaMemRet_InvalidEndmark,           /**< Invalid endmark detected */
    EAaMemRet_InvalidOperationMode,     /**< Invalid pool operation mode */
    EAaMemRet_InitializationFailure,    /**< Initialization (e.g. EE level) failed */
    EAaMemRet_OperationNotSupported,    /**< Requested operation not supported by pool impl. */
    EAaMemRet_PoolNameConflict,         /**< Given pool name does not match to existing pool */
    EAaMemRet_InvalidPoolId,            /**< Given pool ID is not valid for the operation */
    EAaMemRet_MaxAttachedPools,         /**< Maximum number of attached pools exceeded */
    EAaMemRet_WrongPoolParameters,      /**< Wrong Pool Parameters exceeded*/

    EAaMemRet_NbrOf                     /**< Keep always last and do not remove */

} EAaMemRet;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* _COMMON_IFAAMEM_DEF_H_ */
