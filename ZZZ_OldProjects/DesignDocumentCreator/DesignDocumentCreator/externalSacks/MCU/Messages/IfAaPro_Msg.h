/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaPro messages definitions.
* @module                AaPro
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_IFAAPRO_MSG_H_
#define _MCU_IFAAPRO_MSG_H_

#include <CcsCommon.h>

#include <IfAaPro_Defs.h>
#include <../../COMMON/Messages/IfAaPro_Msg.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
*@addtogroup dgAaProApiMcu
 * @{
*/


/* Static cp id's for Supervision service tasks */
#define AAPRO_SUPERVISION_SERVICE_CPID 0x0615  /* CPID for CC&S supervision service */

#define AAPRO_NODE_STATUS_SERVICE_CPID 0x063F /* CPID for CC&S RAT node supervision service */

/** @} end: @addtogroup dgAaProApiMcu */

#ifdef __cplusplus
}
#endif

#endif /* _IFAAPRO_MSG_H_ */

