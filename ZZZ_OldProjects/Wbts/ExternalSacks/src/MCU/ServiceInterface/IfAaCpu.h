/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2018 Nokia Networks. All rights reserved.
*******************************************************************************/
#ifndef _MCU_IFAACPU_H
#define _MCU_IFAACPU_H

#include "CcsCommon.h"

#include "../../COMMON/ServiceInterface/IfAaCpu.h"
#include "../../SHARED/MCU_RT/ServiceInterface/IfAaCpu.h"
#include "../../MCU/Definitions/IfAaCpu_Defs.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
*@defgroup dgAaCpuApiMcu MCU API
*@ingroup dgAaCpu
*@{
*/

/**
* @name CPU affinity management API
* @{
*/

/**
*******************************************************************************
*
*   @brief  Get number of cores affined to current EE.
*
*   @return  Number of cores affined to current application or 0 in case of fail.
*
*   @par Description:
*   This function is used to get number of cores assigned to current application.
*
*   @par Errors:
*   If the core affinity could not be read successfully the function will log
*   error message and return 0.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   u32 coreCount = AaCpuAffinityGetOwnEeCoreCount();
*
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
*   @see AaCpuAffinitySetCoreMask
*   @see AaCpuAffinityGetCoreMask
*   @see AaCpuAffinityGetCoreCount
*   @see AaCpuAffinityGetAvailableCoreCount
*
******************************************************************************/
u32 AaCpuAffinityGetOwnEeCoreCount(void);

/**
*******************************************************************************
*
*   @brief  Get number of cores affined to EE.
*
*   @param[in] eeId  ID of EE to get the number of cores for
*
*   @return  Number of cores affined to application or 0 in case of fail.
*
*   @par Description:
*   This function is used to get number of cores assigned to application with EE id given as argument.
*
*   @par Errors:
*   If the core affinity could not be read successfully the function will log
*   error message and return 0.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*   #include <IfAaPro.h>
*
*   u32 coreCount = AaCpuAffinityGetCoreCount(AaProEeCurrent());
*
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
*   @see AaCpuAffinitySetCoreMask
*   @see AaCpuAffinityGetCoreMask
*   @see AaCpuAffinityGetOwnEeCoreCount
*   @see AaCpuAffinityGetAvailableCoreCount
*
******************************************************************************/
u32 AaCpuAffinityGetCoreCount(u32 eeId);

/**
*******************************************************************************
*
*   @brief  Get number of available cores.
*
*   @return  Number of cores available in the system or 0 in case of fail.
*
*   @par Description:
*   This function is used to get number of cores currently available in the system.
*
*   @par Errors:
*   If the core number could not be read successfully the function will log
*   error message and return 0.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*
*   u32 availableCoreCount = AaCpuAffinityGetAvailableCoreCount();
*
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
*   @see AaCpuAffinitySetCoreMask
*   @see AaCpuAffinityGetCoreMask
*   @see AaCpuAffinityGetCoreCount
*   @see AaCpuAffinityGetOwnEeCoreCount
*
******************************************************************************/
u32 AaCpuAffinityGetAvailableCoreCount(void);

/**
*******************************************************************************
*
*   @brief  Get core affinity mask.
*
*   @param[in] eeId  ID of EE to get the mask for
*
*   @return  Cores mask assign to application or 0 in case of fail.
*
*   @par Description:
*   This function is used to get cores mask assigned to application with EE id given as argument.
*
*   @par Errors:
*   If the core affinity could not be read successfully the function will log
*   error message and return 0.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*   #include <IfAaPro.h>
*
*   TAaCpuAffinityMask mask = AaCpuAffinityGetCoreMask(AaProEeCurrent());
*
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
*   @see AaCpuAffinitySetCoreMask
*   @see AaCpuAffinityGetCoreCount
*   @see AaCpuAffinityGetOwnEeCoreCount
*   @see AaCpuAffinityGetAvailableCoreCount
*
******************************************************************************/
TAaCpuAffinityMask AaCpuAffinityGetCoreMask(u32 eeId);

/**
*******************************************************************************
*
*   @brief  Set core affinity mask.
*
*   @param[in] eeId          ID of EE to set the mask for
*   @param[in] affinityMask  CPU mask to be set for given EE
*
*   @return  -1 on error, 0 otherwise
*
*   @par Description:
*   The function sets core affinity mask of the EE to the one given by the user.
*   The mask defines on which cpu cores the EE will be allowed to run.
*   Each bit of the mask corresponds to CPU core where LSB is CPU0. Bits which
*   don't associate to cores available in the system will be ignored (e.g. bits
*   4-31 on the system with 4 cores). Bit value of 1 means that the core is
*   allowed for given EE while 0 means that executions on the core is forbidden.
*
*   @par Errors:
*   If the core affinity could not be set successfully the function will log
*   error message and return -1.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaCpu.h>
*   #include <IfAaPro.h>
*
*   u32 eeId = AaProEeCurrent(); // getting eeId of current EE
*   TAaCpuAffinityMask mask = 0;
*
*   AACPU_AFFINITY_SET_CORE(mask, 3); // setting affinity to core 3
*   if ( -1 == AaCpuAffinitySetCoreMask(eeId, mask) )
*   {
*       //error handling
*   }
*
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
*   @see AaCpuAffinityGetCoreMask
*   @see AaCpuAffinityGetCoreCount
*   @see AaCpuAffinityGetOwnEeCoreCount
*   @see AaCpuAffinityGetAvailableCoreCount
*
******************************************************************************/
i32 AaCpuAffinitySetCoreMask(u32 eeId, TAaCpuAffinityMask affinityMask);

/* @}*/
/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* _MCU_IFAACPU_H */
