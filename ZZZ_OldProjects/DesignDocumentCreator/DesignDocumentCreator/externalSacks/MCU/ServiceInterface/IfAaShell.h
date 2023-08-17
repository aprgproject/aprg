/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/
#ifndef _MCU_IFAASHELL_H
#define _MCU_IFAASHELL_H
#include "CcsCommon.h"
#ifdef CCS_NEW_IF_STRUCTURE
#include <../../SHARED/MCU_RT/ServiceInterface/IfAaShell.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup dgAaShellApiMcu AaShell MCU function API
 * @ingroup  dgAaShell
 */
/* @{ */

/**
*******************************************************************************
*
*   @brief      Deletes user command from shell.
*
*   @param[in]  name            Command identifier in shell
*
*   @return
*   -  0 if successfull
*   - -1 in case of incorrect input parameter
*   - -2 if command was not found
*   - -3 if AaShell is not initialized
*
*   @par Description:
*        Deletes user command from shell.
*
*   @par Errors:
*   - -1 in case of incorrect input parameter
*   - -2 if command was not found
*   - -3 if AaShell is not initialized
*
*   @par Restrictions:
*        Command name must not contain any metacharacters
*
*   @see AaShellAddCommand
*
*******************************************************************************/
int AaShellDeleteCommand(const char* name);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* _MCU_IFAASHELL_H */
