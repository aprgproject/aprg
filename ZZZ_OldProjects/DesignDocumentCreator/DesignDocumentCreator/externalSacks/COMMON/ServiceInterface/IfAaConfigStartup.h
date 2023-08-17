/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _IFAACONFIGSTARTUP_H
#define _IFAACONFIGSTARTUP_H
/*----------------------- LaTeX INLINE DOCUMENTATION --------------------------*/

/* -> see ccs_api_spec_body.tex */

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <CcsCommon.h>
#include <glo_def.h>

#include <IfAaConfig_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup dgAaConfigStartup AaConfigStartup API
*
* Common Computer and Support SW Configuration AaConfigStartup service API.
*
*/

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/


/*------------------- PUBLIC INTERFACES (COMMON API) -------------------------*/

/**
 * @defgroup dgAaConfigStartupApi AaConfigStartup functions
 * @ingroup  dgAaConfigStartup
 */

/**
 * @defgroup dgAaConfigStartupApiCommon AaConfigStartup common functions
 * @ingroup  dgAaConfigStartupApi
 */

/* @{ */

/**
********************************************************************************
*
* @brief        AaConfigCeStartup executes CE level startup.
*
* @return       Function returns success of operation.
*
* @par Description:
* Function executes CE level startup for AaConfig service.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
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
*
* @par Example:
* @code
*   ret = AaConfigCeStartup();
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigCeStartup(void);


/**
********************************************************************************
*
* @brief        AaConfigCeShutdown executes CE level shutdown.
*
* @return       Function returns success of operation.
*
* @par Description:
* Function executes CE level shutdown for AaConfig service.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
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
*
* @par Example:
* @code
*   ret = AaConfigCeShutdown();
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigCeShutdown(void);


/**
********************************************************************************
*
* @brief        AaConfigEeStartup executes EE level startup.
*
* @param[in]    radDomainCount      Maximum R&D Parameter SW Domain count
*
* @return       Function returns success of operation.
*
* @par Description:
* Function executes EE level startup for AaConfig service.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
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
*
* @par Example:
* @code
*   u32 radDomCnt = 50;
*   ret = AaConfigEeStartup(radDomCnt);
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigEeStartup(u32 radDomainCount);


/**
********************************************************************************
*
* @brief        AaConfigEeShutdown executes EE level shutdown.
*
* @return       Function returns success of operation.
*
* @par Description:
* Function executes EE level shutdown for AaConfig service.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
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
*
* @par Example:
* @code
*   ret = AaConfigEeShutdown();
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigEeShutdown(void);

/**
********************************************************************************
*
* @brief        AaConfigEarlyStartup executes startup before OS is running.
*
* @return       Function returns success of operation.
*
* @par Description:
* After starting AaConfig on "early level", configuration tags are available.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
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
*
* @par Example:
* @code
*   ret = AaConfigEarlyStartup();
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigEarlyStartup(void);
/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif /* _IFAACONFIGSTARTUP_H */
