/** @file
*   @brief Contains AaStartup message's definititions shared between CC&S MCU and RT
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: Copyright 2018 Nokia. All rights reserved.$
*/

#ifndef _MCU_RT_IF_AASTARTUP_MSG_H_
#define _MCU_RT_IF_AASTARTUP_MSG_H_

#include <CcsCommon.h>
#include "../Definitions/IfAaStartup_Defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaStartupMsg AaStartup messages
 * @ingroup dgAaStartup
 */

/**
 * @defgroup dgAaStartupMsgSharedMcuRt AaStartup shared MCU and RT messages
 * @ingroup dgAaStartupMsg
 */

/*@{*/

/** Informs CC&S about reset. */
#define AASTARTUP_RESET_IND_MSG 0x153D                     /* !- SIGNO(struct SAaStartupResetInd) -!  */

/** Informs application that tasks related to reset inside CC&S are finished. */
#define AASTARTUP_RESET_ACK_MSG 0x153E                     /* !- SIGNO(struct void) -!  */

/**  Structure used to request checkpoint data report */
typedef struct SAaStartupResetInd
{
    EAaStartupResetType resetType;                          /**< Reset type */
} SAaStartupResetInd;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* _MCU_RT_IF_AASTARTUP_MSG_H_ */
