/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaConfig interface header file.
* @module                AaConfig
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAACONFIGSTARTUP_H
#define _MCU_RT_IFAACONFIGSTARTUP_H
/*----------------------- LaTeX INLINE DOCUMENTATION --------------------------*/

/* -> see ccs_api_spec_body.tex */

/*----------------------- INCLUDED FILES -------------------------------------*/

#include "CcsCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/*--------------------- PUBLIC INTERFACES (MCU API) --------------------------*/

/**
 * @defgroup dgAaConfigStartupApiMcuRt AaConfigStartup MCU-RT shared functions
 * @ingroup  dgAaConfigStartupApi
 */

/* @{ */

/**
********************************************************************************
*
* @brief        AaConfigCeEarlyStartup executes CE early startup of AaConfig service.
*
* @param[in]    earlyxml   path to CCSEarlyConfig.xml file
*
* @return       Function returns success of operation.
*
* @par Description:
* After starting AaConfig at "early level", configuration tags are available.
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
*   ret = AaConfigCeEarlyStartup("CCSEarlyConfig.xml");
* @endcode
*
*******************************************************************************/

EAaConfigRet AaConfigCeEarlyStartup(char * earlyxml);

/* @} */

#ifdef __cplusplus
}
#endif

#endif /* _MCU_RT_IFAACONFIGSTARTUP_H */
