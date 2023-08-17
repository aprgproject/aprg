/**
*******************************************************************************
* @file
* $HeadURL$
* $LastChangedRevision$
* $LastChangedDate$
* $Author$
*
* @brief                 CC&S static memory pool ID reservations
*
* Copyright 2016 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _RT_DSP_AAMEMCCSPOOLDEFINITIONS_H
#define _RT_DSP_AAMEMCCSPOOLDEFINITIONS_H

#include <CcsCommon.h>

/*----------------------- DOXYGEN GROUPS --------------------------------------*/
/**
* @addtogroup dgUpCcs U-Plane specific CC&S API
* @{
*/

/**
* @addtogroup dgUpCcsAaMem AaMem API
* @{
*/

/**
* @addtogroup dgUpCcsRtDspAaMem AaMem API for RT and OSECK DSP nodes
* @{
*/

#ifdef __cplusplus
extern "C" {
#endif

typedef enum EAaMemSysPoolId
{
    EAaMemSysPoolId_Private = 0, /**< Basic dynamic memory. Pool operation mode is SAFE. */
    EAaMemSysPoolId_Shared,      /**< Shared dynamic memory. Pool operation mode is SAFE. */
    EAaMemSysPoolId_Msg,         /**< Messaging dynamic memory. Pool operation mode is SAFE. */

    EAaMemSysPoolId_NbrOf        /**< Last id. And keep it that way! */

} EAaMemSysPoolId;


/** @brief Macro for creating static pool ID for CC&S internal use
* @param[in] __cid  Memory pool category.
* @param[in] __sid  Memory pool ID.
*
* @return 32bit pool ID
*/
#define AAMEM_POOLID_CREATE(__cid, __sid) (i32)(((__cid) << 16) | (__sid))


/** @brief Maximum number of memory pool categories for DSP nodes */
#define MAX_NUM_OF_CATEGORIES              (20)

/** @brief Last category number for DSP nodes */
#define LAST_CATEGORY_NO                   (MAX_NUM_OF_CATEGORIES - 1)

/** @brief Macro for creating static pool ID for CC&S internal use
* @param[in] __sid_offs  Offset for pool sub identifier, starting from zero.
*
* @return 32bit pool ID
*/
#define AAMEM_CCS_POOL_ID(__sid_offs) (AAMEM_POOLID_CREATE(LAST_CATEGORY_NO, (__sid_offs)))

/** @brief Macro AAMEM_CCS_COMPONENT_POOL_ID is used if the pool ID may be target-specific,
*         and need not be unique.
*/
#ifdef CCS_OSECK
#define AAMEM_CCS_COMPONENT_POOL_ID(__pool_sid) AAMEM_CCS_POOL_ID(__pool_sid)
#else
#define AAMEM_CCS_COMPONENT_POOL_ID(__pool_sid) ((i32)EAaMemSysPoolId_Private)
#endif

/*------------ CC&S pool IDs reserved for components ---------------*/

/** @brief Pool identifiers for CC&S internal use */
enum EAaMemCcsPoolId {
    EAaMemCcsPoolId_Test                = AAMEM_CCS_COMPONENT_POOL_ID(0),   /**< Pool for any portable test code.
                The contents of this pool are not guaranteed to be preserved between successive test runs. */

    EAaMemCcsPoolId_AaFile              = AAMEM_CCS_COMPONENT_POOL_ID(1),   /**< Pool for AaFile */
    EAaMemCcsPoolId_AaConfig            = AAMEM_CCS_COMPONENT_POOL_ID(2),   /**< Pool for AaConfig */
    EAaMemCcsPoolId_AaTrbl              = AAMEM_CCS_COMPONENT_POOL_ID(3),   /**< Pool for AaTrbl */
    EAaMemCcsPoolId_AaTbts              = AAMEM_CCS_COMPONENT_POOL_ID(4),   /**< Pool for AaTbts */
    EAaMemCcsPoolId_AaSysCom            = AAMEM_CCS_COMPONENT_POOL_ID(5),   /**< Pool for AaSysCom */
    EAaMemCcsPoolId_AaSysLog            = AAMEM_CCS_COMPONENT_POOL_ID(6),   /**< Pool for AaSysLog */
    EAaMemCcsPoolId_AaSysMb             = AAMEM_CCS_COMPONENT_POOL_ID(7),   /**< Pool for AaSysMb */
    EAaMemCcsPoolId_AaPro               = AAMEM_CCS_COMPONENT_POOL_ID(8),   /**< Pool for AaPro */
    EAaMemCcsPoolId_AaSysInfo           = AAMEM_CCS_COMPONENT_POOL_ID(9),   /**< Pool for AaSysInfo */

    EAaMemCcsPoolId_Last                = AAMEM_POOLID_CREATE(0, 10)  /**< Not usable value, let always be the last! */
};


/************************** PUBLIC INTERFACES *********************************/
#ifdef __cplusplus
}
#endif

/** @} */   /* dgUpCcsRtDspAaMem */
/** @} */   /* dgUpCcsAaMem */
/** @} */   /* dgUpCcs */

#endif /* _RT_DSP_AAMEMCCSPOOLDEFINITIONS_H */
