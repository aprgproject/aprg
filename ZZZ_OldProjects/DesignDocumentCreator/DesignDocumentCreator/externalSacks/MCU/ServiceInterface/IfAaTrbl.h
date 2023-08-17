#ifndef _MCU_IF_AATRBL_H_
#define _MCU_IF_AATRBL_H_
#include "CcsCommon.h"
#ifdef CCS_NEW_IF_STRUCTURE
#include <../../COMMON/ServiceInterface/IfAaTrbl.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
********************************************************************************
*
* @brief        Registers pre-snapshot callback function.
*
* @param[in]    cbName          Callback name.
*
* @param[in]    preSnapshotCb   Pointer to callback function.
*
* @param[in]    opaque        A pointer to user specified data which is passed
*                             to callback function as argument ex. class instance.
*
* @return       Function returns success of operation.
*
* @par Description:
* User registered funcation is executed after AATRBL_FILE_PREPARE_REQ_MSG
* is recieved ( before file prepare callbacks )
*
* @par Errors:
* EAaTrblRet_InvalidParameter - returned in case function is alredy registered.
* EAaTrblRet_InvalidParameter - returned in case null pointer is provided.
*
* @par Restrictions:*
* Function cannot be called from:
* - Callback that was registered with this function
* - Callbacks registered with file (prepareCb, storeCb and deleteCb)
*
* @par Usage:
* Callback function can be used to register additional files just before file
* collection procedure begins.
* Calls to AaTrblFileRegister, AaTrblFileRegisterOneShot, AaTrblFileUnregister
* from callback function are supported. Files registered in callback are treaded exacly
* as files registered in other places.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaTrblPreSnapshotCbUnRegister
*
* @par Example:
* @code
*   #include <IfAaTrbl.h>
*
*   void PreSnapshotCb(EAaTrblCoverage coverage, void* opaque)
*   {
*       // register additional files
*   }
*
*   EAaTrblRet ret = AaTrblPreSnapshotCbRegister("CalbackName", PreSnapshotCb, (void*)this);
* @endcode
*
*******************************************************************************/
EAaTrblRet AaTrblPreSnapshotCbRegister(const char* cbName,
                                       TAaTrblPreSnapshotCb * const preSnapshotCb,
                                       void* opaque);

/**
********************************************************************************
*
* @brief        Unregisters pre-snapshot callback function.
*
* @param[in]    cbName   Callback name.
*
* @return       Function returns success of operation.
*
* @par Description:
* Function unregisters presnapshot callback function.
*
* @par Errors:
* EAaTrblRet_InvalidParameter - returned in case function is not registered.
* EAaTrblRet_InvalidParameter - returned in case null pointer is provided.
*
* @par Restrictions:
* Function cannot be called from:
* - Callback that was registered with this function
* - Callbacks registered with file (prepareCb, storeCb and deleteCb)
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaTrblPreSnapshotCbRegister
*
* @par Example:
* @code
*   #include <IfAaTrbl.h>
*
*   void PreSnapshotCb(EAaTrblCoverage coverage, void* opaque)
*   {
*       // register additional files
*   }
*
*   EAaTrblRet ret = AaTrblPreSnapshotCbUnRegister("CalbackName");
* @endcode
*
*******************************************************************************/
EAaTrblRet AaTrblPreSnapshotCbUnRegister(const char* cbName);

#ifdef __cplusplus
}
#endif

#endif /* _MCU_IF_AATRBL_H_*/
