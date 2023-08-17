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

#ifndef IFAASTARTUP_H_
#define IFAASTARTUP_H_

#include "CcsCommon.h"
#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaStartup Startup Service (AaStartup)
 * @ingroup dgBasicComputingSw
 *
 * Common Computer and Support SW Startup Service.
 *
 * @defgroup dgAaStartupApi API
 * @ingroup dgAaStartup
 *
 * Application Programming Interface.
 * @{
 *
 * @defgroup dgAaStartupApiCommon AaStartup COMMON API
 * @ingroup  dgAaStartupApi
 * @{
 */

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** @brief Indicator that the system reset due to application definition file problems is disabled */
#define AASTARTUP_CONFIG_TAG_APPDEF_RESET_DISABLED "ccs.service.daemon.appdef.reset.disable"

/** @brief DEPRECATED - please do not use */
#define AASTARTUP_TAG_NAME_DAEMONIZE               "ccs.service.aastartup.daemonize"

/** @brief AaStartup return code enumeration */
typedef enum EAaStartupRet
{
    EAaStartupRet_Ok = 0,                   /**< No errors occurred */
    EAaStartupRet_StartupError,             /**< Startup failed */
    EAaStartupRet_ShutdownError,            /**< Shutdown failed */
    EAaStartupRet_InvalidServiceState,      /**< Service in invalid state for requested operation */
    EAaStartupRet_NbrOf                     /**< Always the last memeber */
} EAaStartupRet;

/** @brief AaStartup return codes in convenience textual representation */
#define EAASTARTUPRET_VALUES \
   { \
       "EAaStartupRet_Ok", \
       "EAaStartupRet_StartupError", \
       "EAaStartupRet_ShutdownError", \
       "EAaStartupRet_InvalidServiceState", \
       "EAaStartupRet_NbrOf", \
   }

/** @brief CCSDaemon initialization is finished */
#define CCSDAEMON_INIT_FINISHED_NOTIF_MSG     0x1B9D    /* !- SIGNO(struct void) -! */

/*----------------------- PUBLIC INTERFACES --------------------------------*/

/**
*******************************************************************************
*
*   @brief    Executes CE startup at Early level.
*
*   @param    none
*
*   @return   EAaStartupRet_Ok                   Startup succeeded
*   @return   EAaStartupRet_StartupError         Startup failed
*   @return   EAaStartupRet_InvalidServiceState  Startup already done at early level
*                                                or OS is running.
*
*   @par Description:
*       Must be done once before OS is started.
*
*   @par Errors:
*
*   @par Restrictions:
*   Not supported in every OS. See https://sharenet-ims.int.net.nokia.com/Open/D-171114.latest
*   for more details.
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
EAaStartupRet AaStartupEarlyStartup (void);

/**
*******************************************************************************
*
*   @brief    Executes EE startup at Early level.
*
*   @param    none
*
*   @return   EAaStartupRet_Ok                   Startup succeeded
*   @return   EAaStartupRet_StartupError         Startup failed
*   @return   EAaStartupRet_InvalidServiceState  EE Startup already done at early level
*                                                or OS is running.
*
*   @par Description:
*       Must be done once before OS is started.
*
*   @par Errors:
*
*   @par Restrictions:
*   Not supported in every OS. See https://sharenet-ims.int.net.nokia.com/Open/D-171114.latest
*   for more details.
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
EAaStartupRet AaStartupEeEarlyStartup (void);

/**
*******************************************************************************
*
*   @brief    Executes startup at CE level.
*
*   @param    none
*
*   @return   EAaStartupRet_Ok                   Startup succeeded
*   @return   EAaStartupRet_StartupError         Startup failed
*   @return   EAaStartupRet_InvalidServiceState  Startup already done at CE level
*
*   @par Description:
*       Must be done once in every CE context. Creates daemon EE/EU and executes
*       CC&S SW service startups in the context of the daemon.
*
*   @par Errors:
*
*
*   @par Restrictions:
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
EAaStartupRet AaStartupCeStartup (void);

/**
*******************************************************************************
*
*   @brief    Executes startup at EE level.
*
*   @param    none
*
*   @return   EAaStartupRet_Ok                   Startup succeeded
*   @return   EAaStartupRet_StartupError         Startup failed
*   @return   EAaStartupRet_InvalidServiceState  Startup already done at EE level
*
*   @par Description:
*       Must be done once in every EE context. After execution of this function,
*       CC&S SW services are available at the current EE level.
*
*   @par Errors:
*
*
*   @par Restrictions:
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
EAaStartupRet AaStartupEeStartup (void);

/**
*******************************************************************************
*
*   @brief    Executes shutdown at CE level
*
*   @param    none
*
*   @return   EAaStartupRet_Ok                   Shutdown succeeded
*   @return   EAaStartupRet_ShutdownError        Shutdown failed
*   @return   EAaStartupRet_InvalidServiceState  Startup not done at CE level
*
*   @par Description:
*       Must be done once in every CE context after CE startup is done.
*       Executes CC&S SW service shutdowns in the context of the daemon,
*       created during CE startup. The daemon is terminated after all service
*       shutdown is done.
*
*   @par Errors:
*
*
*   @par Restrictions:
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
EAaStartupRet AaStartupCeShutdown (void);

/**
*******************************************************************************
*
*   @brief    Executes shutdown at EE level
*
*   @param    none
*
*   @return   EAaStartupRet_Ok                   Shutdown succeeded
*   @return   EAaStartupRet_ShutdownError        Shutdown failed
*   @return   EAaStartupRet_InvalidServiceState  Startup not done at EE level
*
*   @par Description:
*       Must be done once in every EE context after EE startup is done.
*       Executes CC&S SW service shutdowns in the context of the EE.
*       The CC&S SW services are not available in the current EE after calling
*       this function.
*
*   @par Errors:
*
*
*   @par Restrictions:
*       EUs in the context of current EE may lose access to CC&S SW services,
*       thus this function should not be called until all EUs have got
*       AaStartupEuShutdown called and no one is using CC&S SW services in
*       the current EE context.
*       Applications can call AaStartupEeShutdown() only in case of normal
*       process termination. Function AaStartupEeShutdown() can't be called
*       from callbacks registered with AaStartupAtEeShutdown().
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
*   AaStartupAtEeShutdown
*
******************************************************************************/
EAaStartupRet AaStartupEeShutdown (void);

/**
 * @}
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif /*IFAASTARTUP_H_ */
