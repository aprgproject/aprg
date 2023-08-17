/** @file
*   @brief CC&S static memory pool ID reservations
*   @copyright 2014 Nokia Solutions and Networks. All rights reserved.
*   @copyright 2019 Nokia. All rights reserved.
*/

#ifndef _AAMEMCCSPOOLDEFINITIONS_H
#define _AAMEMCCSPOOLDEFINITIONS_H


/************************** DOXYGEN GROUPS ************************************/

/*@{*/

/************************** INCLUDED FILES ************************************/

#include <CcsCommon.h>
#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/************************** PUBLIC DECLARATIONS *******************************/

typedef enum EAaMemSysPoolId
{
    EAaMemSysPoolId_Private = 0, /**< Basic dynamic memory. Pool operation mode is SAFE. */
    EAaMemSysPoolId_Shared,      /**< Shared dynamic memory. Pool operation mode is SAFE. */
    EAaMemSysPoolId_Msg,         /**< Messaging dynamic memory. Pool operation mode is SAFE. */

    EAaMemSysPoolId_NbrOf        /**< Last id. And keep it that way! */

} EAaMemSysPoolId;


/** @brief Macro for creating static pool ID for CC&S internal use  
* @param[in] __sid_offs  Offset for pool sub identifier, starting from zero.
*
* @return 32bit pool ID
*/
#define AAMEM_POOLID_CREATE(__cid, __sid) CCS_STATIC_CAST(i32,(((__cid) << 16) | (__sid)))
#define AAMEM_CCS_POOL_ID(__sid_offs) (EAaMemSysPoolId_NbrOf + AAMEM_POOLID_CREATE(0, (__sid_offs)))


/** @brief Macro AAMEM_CCS_COMPONENT_POOL_ID is used if the pool ID may be target-specific,
 *         and need not be unique. 
 */
#ifdef CCS_OSECK
# define AAMEM_CCS_COMPONENT_POOL_ID(__pool_sid) AAMEM_CCS_POOL_ID(__pool_sid)
#else
# define AAMEM_CCS_COMPONENT_POOL_ID(__pool_sid) ((i32)EAaMemSysPoolId_Private)
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

    EAaMemCcsPoolId_Last                = AAMEM_CCS_POOL_ID(9)  /**< Not usable value, let always be the last! */ 
};


/************************** PUBLIC INTERFACES *********************************/

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* _AAMEMCCSPOOLDEFINITIONS_H */
