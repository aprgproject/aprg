/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/
#ifndef _MCU_IFAASTARTUP_H
#define _MCU_IFAASTARTUP_H

#include <CcsCommon.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <../../COMMON/ServiceInterface/IfAaStartup.h>
#include <../../SHARED/MCU_RT/ServiceInterface/IfAaStartup.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaStartupApiMcuLinux AaStartup LINUX MCU API
 * @ingroup  dgAaStartupApi
 * @{
 */

/**
*******************************************************************************
*
*   @brief Notifies system service manager about service startup.
*
*   @par Description:
*   Function notifies system service manager that application completed startup.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   Supported only by CC&S MCU LINUX_X86_64 (Xeon D-1548) build variant.
*
*   @par Example:
*   @code
*
*   #include <IfAaStartup.h>
*   ...
*   AaConfigEarlyStartup();
*   AaStartupEeStartup();
*
*   // Application startup code goes here
*
*   AaStartupNotifySystemReady();
*   ...
*
*   @endcode
*
******************************************************************************/
void AaStartupNotifySystemReady(void);

/* @} */

#ifdef __cplusplus
}
#endif
#endif /* _MCU_IFAASTARTU_H */
