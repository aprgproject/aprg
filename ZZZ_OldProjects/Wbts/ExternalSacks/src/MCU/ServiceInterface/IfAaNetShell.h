/** @file
*   @brief Functions for handling shell configuration.
*   @copyright 2019 Nokia. All rights reserved.
*/

#ifndef _MCU_IF_AANET_SHELL_H_
#define _MCU_IF_AANET_SHELL_H_

#include <glo_def.h>
#include <CcsCommon.h>
#include <../Definitions/IfAaNet_Defs.h>

/** @addtogroup dgAaNetMcu */

/** @{ */

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief Set the value of shell inactivity timeout.
*
* @param[in] timeout            shell inactivity timeout in seconds
*
* @retval #EAaNetRet_Ok         operation was successful
* @retval #EAaNetRet_ParmError  timeout value out of allowed range
* @retval #EAaNetRet_Error      failed to set shell inactivity timeout
*
* @par Description
* This function configures the shell idle timeout. The argument is
* specified in seconds. The inactivity timer is disabled when the
* timeout value is set to #AANET_SHELL_NO_TIMEOUT.
*
* @par Errors
* See Return values section.
*
* @par Restrictions
*  - Supported values of inactivity timer range from #AANET_SHELL_NO_TIMEOUT
*    to #AANET_SHELL_MAX_TIMEOUT seconds (inclusive).
*  - New timeout value applies only to new shells.
*
* @par Example
* @code
* #include <IfAaNetShell.h>
*
* u32 inactivityTimeout = 600;
*
* EAaNetRet result = AaNetShellSetTimeout(inactivityTimeout);
* if( EAaNetRet_Ok != result ) {
*   // handle error of setting shell timeout
* }
* @endcode
*
* @par Rationale
* RP002015_1_F1
*/
EAaNetRet AaNetShellSetTimeout(u32 timeout);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* _MCU_IF_AANET_SHELL_H_ */
