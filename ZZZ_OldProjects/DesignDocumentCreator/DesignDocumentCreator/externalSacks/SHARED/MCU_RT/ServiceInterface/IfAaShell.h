/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAASHELL_H
#define _MCU_RT_IFAASHELL_H

/*----------------------- INCLUDED FILES -------------------------------------*/

#include "CcsCommon.h"
#include <glo_def.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
*@defgroup   dgAaShell   AaShell
*@ingroup    dgTestabilitySw
*
* AaShell Wiki: http://wikis.inside.nokiasiemensnetworks.com/bin/view/CSSWiki/AaShell
*
* @par Shell Command Service (AaShell)
*
*   Features
*   - Register commands at runtime
*   - User can use TCP or UDP to connect remote shell
*/



/**
 * @defgroup dgAaShellMcuRt AaShell MCU RT function API
 * @ingroup  dgAaShell
 */
/*@{*/

/** @brief Defines number of maximum registered shell commands. If tag is not set or its value is lower than 64 default value is used - 64, if tags value is bigger than 256 max value is used - 256. */
#define   AASHELL_MAX_COMMAND_COUNT          "ccs.service.aashell.commands.count.max"

/** @brief A type for shell command callback function. Returns zero in success otherwise error. */
typedef int TAaShellFunction(int argc, char** argv);

/**
*******************************************************************************
*
*   @brief      Registers client process to AaShell Router
*
*   @param[in]  None
*
*   @par Description:
*
*   This function is used to register a Client process to Router and
*   to setup a socket communication with it.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @see
*
*******************************************************************************/
void AaShellEeStartup(void);

/**
*******************************************************************************
*
*   @brief      Deregisters client process from AaShell Router
*
*   @param[in]  None
*
*   @par Description:
*
*   This function is used to deregister a Client process from Router and
*   delete it from the list of active client processes.
*
*   @par Errors:	    None
*
*   @par Restrictions:	    None
*
*   @see
*
*******************************************************************************/
void AaShellEeShutdown(void);

/**
*******************************************************************************
*
*   @brief      Add command to shell.
*
*   @param[in]  name            Command identifier in shell
*   @param[in]  description     Short command description
*   @param[in]  callback        Command function
*                               max nr of command arguments is 49
*
*   @return
*     0 if successfull
*    -1 in case of incorrect input parameters
*    -2 if max nr. of shell commands is reached
*    -3 if AaShell not initialized
*
*   @par Description:
*
*   Register user command to shell.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @see
*
*******************************************************************************/
int AaShellAddCommand(const char*       name,
                      const char*       description,
                      TAaShellFunction* callback);

/**
*******************************************************************************
*
*   @brief      Print to shell session.
*
*   @param[in]  fmt         Pointer to unformatted text. 
*   @param[in]  ...         Variable arguments
*
*   @par Description:
*
*   This function is used from user remote command to print information
*   to shell session.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @see
*
*******************************************************************************/
void AaShellPrint(const char* ftm, ...);

/**
*******************************************************************************
*
*   @brief      Starts AaShell Router process
*
*   @param[in]  stream_port Stream port number
*   @param[in]  dgram_port  Dgram port number
*
*   @par Description:
*
*   This function is used to start a Shell Router process. Setup service on Application level
*   - used before introduction of Shell Router.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @see
*
*******************************************************************************/
int  AaShellApplicationStartup(u32 stream_port, u32 dgram_port);

/*@}*/



//AaShell private API

/** @brief AaShell private function to sstartup service on CE level */
void AaShellCeStartup(void);

/** @brief AaShell private function to shutdown service on CE level */
void AaShellCeShutdown(void);



#ifdef __cplusplus
}
#endif


#endif /* _MCU_RT_IFAASHELL_H */
