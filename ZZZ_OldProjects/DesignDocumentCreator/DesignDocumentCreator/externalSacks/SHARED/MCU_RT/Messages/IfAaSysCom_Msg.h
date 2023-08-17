/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef IF_MCU_RT_AASYSCOM_MSG_H_
#define IF_MCU_RT_AASYSCOM_MSG_H_

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
 * @addtogroup dgAaSysComMcuRt AaSysCom MCU_RT
 * @ingroup dgAaSysCom
 *
 * Common Computer and Support SW System Communication Configuration.
 *
 * @{
 */

/** Message ID for EE shutdown notification message. */
#ifndef AASYSCOM_EE_SHUTDOWN_NOTIF_MSG
#define AASYSCOM_EE_SHUTDOWN_NOTIF_MSG 0x0C0A   /* !- SIGNO(void) -! */
#endif /* AASYSCOM_EE_SHUTDOWN_NOTIF_MSG */

/** @} end: @addtogroup dgAaSysComMcuRt AaSysCom MCU_RT */

#ifdef __cplusplus
}
#endif

#endif  //IF_MCU_RT_AASYSCOM_MSG_H_
