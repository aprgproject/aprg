/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 Startup Service API header file
* @module                AaStartup
*
* Copyright 2017 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAASTARTUP_H
#define _MCU_RT_IFAASTARTUP_H

#include "CcsCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/*------------------- PUBLIC INTERFACES (LINUX API) -------------------------*/

/**
 * @defgroup dgAaStartupApiLinux AaStartup LINUX API (MCU & RT)
 * @ingroup  dgAaStartupApi
 * @{
 */

/** @brief Maximum number of functions registered to be called at Ee shutdown. */
#define AASTARTUP_AT_EE_SHUTDOWN_MAX    32

/**
*******************************************************************************
*
*   @brief    Starts spplications listed in the application definition file.
*
*   @param    filename   path and name of the application definition file
*
*   @return   GLO_TRUE if applications are succesfully started from the application definition file,
*   @return   GLO_FALSE if applications are not succesfully started from the application definition file,.
*
*   @par Description:
*       Application definition file is parsed and applications started.
*
*   @par Errors:
*
*   @par Restrictions:
*   Supported only for Linux.
*
*   @par Example:
*
*   @code
*
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
*   @see
*
******************************************************************************/
TBoolean AaStartupFromFile(const char* filename);

/**
*******************************************************************************
*
*   @brief    Registers the given function to be called at Ee shutdown.
*
*   @param    (*function)(void)  pointer to function to be registered.
*
*   @return   0 if successful, nonzero value otherwise
*
*   @par Description:
*       This function registers the given function to be called at Ee shutdown.
*       Functions so registered are called in the reverse order of their
*       registration, no arguments are passed.
*       The same function may be registered multiple times, in which case
*       it will be called once for each registration.
*
*   @par Errors:
*
*   @par Restrictions:
*   Registered callback function can't call AaStartupEeShutdown().
*
*   @par Example:
*
*   @code
*
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
*   @see
*   AaStartupEeShutdown
*
******************************************************************************/
u32 AaStartupAtEeShutdown(void (*function)(void));

/* @} */

#ifdef __cplusplus
}
#endif
#endif /* _MCU_RT_IFAASTARTUP_H */
