/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/ 
#ifndef _MCU_AAPROCCSEUDEFINITIONS_H
#define _MCU_AAPROCCSEUDEFINITIONS_H


/************************** INCLUDED FILES ************************************/
#include "CcsCommon.h"

/************************** DOXYGEN GROUPS ************************************/

/**
 *  @defgroup dgEuConfigs EU configurations
 *  @ingroup  dgCcs
 *
 *  Defines CC&S EU configurations (priority, stack size, etc.) per service.
 *  They can be configured at OS resolution.
 */

/** @name AaSysCom
* @{
*/
/** @brief AaSyscom EU priority
*   @def AAPRO_EU_PRIORITY_AASYSCOM_GW_DEF_PRI
*/
#ifndef AAPRO_EU_PRIORITY_AASYSCOM_GW_DEF_PRI
# define AAPRO_EU_PRIORITY_AASYSCOM_GW_DEF_PRI EU_PRIORITY_06
#endif

/** @brief AaSyscom EU stack size
*   @def AAPRO_EU_STACK_AASYSCOM_GW_DEF_STACK
*/
#ifndef AAPRO_EU_STACK_AASYSCOM_GW_DEF_STACK
# define AAPRO_EU_STACK_AASYSCOM_GW_DEF_STACK 4096
#endif

/** @brief AaSyscom EU priority
*   @def AAPRO_EU_PRIORITY_AASYSCOM_CONTROL_PRIO
*/
// set prio a bit lower than default
#ifndef AAPRO_EU_PRIORITY_AASYSCOM_CONTROL_PRIO
# define AAPRO_EU_PRIORITY_AASYSCOM_CONTROL_PRIO (AAPRO_EU_PRIORITY_AASYSCOM_GW_DEF_PRI + 2)
#endif

/** @brief AaSyscom EU stack size
*   @def AAPRO_EU_STACK_AASYSCOM_CONTROL_STACK_SIZE
*/
#ifndef AAPRO_EU_STACK_AASYSCOM_CONTROL_STACK_SIZE
# define AAPRO_EU_STACK_AASYSCOM_CONTROL_STACK_SIZE 2048
#endif
/** @} */

/** @name AaFile
* @{
*/
/** @brief AaFileSicFtpTask EU priority
* @def AAPRO_EU_PRIORITY_AAFILE_SICFTP_TASK
*/
#ifndef AAPRO_EU_PRIORITY_AAFILE_SICFTP_TASK
# define AAPRO_EU_PRIORITY_AAFILE_SICFTP_TASK EU_PRIORITY_28
#endif

/** @brief AaFileSicFtpTask EU stack size
* @def AAPRO_EU_STACK_AAFILE_SICFTP_TASK
*/
#ifndef AAPRO_EU_STACK_AAFILE_SICFTP_TASK
# define AAPRO_EU_STACK_AAFILE_SICFTP_TASK 4092
#endif

/** @brief AaFileTftp server control EU priority
* @def AAPRO_EU_PRIORITY_AAFILETFTP_SERVER_CONTROL_TASK
*/
#ifndef AAPRO_EU_PRIORITY_AAFILETFTP_SERVER_CONTROL_TASK
#  define AAPRO_EU_PRIORITY_AAFILETFTP_SERVER_CONTROL_TASK EU_PRIORITY_13
#endif

/** @brief AaFileTftp server EU stack size
* @def AAPRO_EU_STACK_AAFILETFTP_SERVER_CONTROL_TASK
*/
#ifndef AAPRO_EU_STACK_AAFILETFTP_SERVER_CONTROL_TASK
#  define AAPRO_EU_STACK_AAFILETFTP_SERVER_CONTROL_TASK 4092
#endif


/** @brief AaFileTftp client EU priority
* @def AAPRO_EU_PRIORITY_AAFILETFTP_CLIENT
*/
#ifndef AAPRO_EU_PRIORITY_AAFILETFTP_CLIENT
#  define AAPRO_EU_PRIORITY_AAFILETFTP_CLIENT EU_PRIORITY_28
#endif

/** @brief AaFileTftp client EU stack size
* @def AAPRO_EU_STACK_AAFILETFTP_CLIENT
*/
#ifndef AAPRO_EU_STACK_AAFILETFTP_CLIENT
#  define AAPRO_EU_STACK_AAFILETFTP_CLIENT 2048
#endif

/** @brief AaFileTftp server control EU priority
* @def AAPRO_EU_PRIORITY_AAFILETFTP_SERVER_DYNAMIC_TASK
*/
#ifndef AAPRO_EU_PRIORITY_AAFILETFTP_SERVER_DYNAMIC_TASK
#  define AAPRO_EU_PRIORITY_AAFILETFTP_SERVER_DYNAMIC_TASK EU_PRIORITY_28
#endif

/** @brief AaFileTftp server EU stack size
* @def AAPRO_EU_STACK_AAFILETFTP_SERVER_DYNAMIC_TASK
*/
#ifndef AAPRO_EU_STACK_AAFILETFTP_SERVER_DYNAMIC_TASK
#  define AAPRO_EU_STACK_AAFILETFTP_SERVER_DYNAMIC_TASK 4092
#endif
/** @} */

#endif /* _MCU_AAPROCCSEUDEFINITIONS_H */
