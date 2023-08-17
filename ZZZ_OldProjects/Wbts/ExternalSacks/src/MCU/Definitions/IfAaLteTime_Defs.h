/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaLteTime defintions header file
* @module                AaLteTime
*
* Copyright 2018 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _MCU_IFAALTETIME_DEFS_H
#define _MCU_IFAALTETIME_DEFS_H

#include <../../COMMON/Definitions/IfAaLteTime_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @addtogroup dgAaLteTimeDefinitions
* @ingroup dgAaLteTime
*/

/**
* @defgroup dgAaLteTimeDefinitionsMcu MCU Definitions
* @ingroup dgAaLteTimeDefinitions
*/

/*@{*/

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** Indication if AaLteTime has finished startup on EE level.
* Its value is set by AaLteTime service from 0 to 1 when EE level startup is
* completed. Please not set this tag. */
#define AALTETIME_TAG_EE_LEVEL_ONLINE "ccs.service.aaltetime.ee.online"

/** Indication if AaLteTime has finished startup on CE level.
* Its value is set by AaLteTime service from 0 to 1 when CE level startup is
* completed. Please not set this tag. */
#define AALTETIME_TAG_CE_LEVEL_ONLINE "ccs.service.aaltetime.ce.online"

/** Indication if sfn sender thread has finished startup.
* Its value is set by AaLteTime service from 0 to 1 when sfn sender startup is
* completed. Please not set this tag. */
#define AALTETIME_TAG_SFN_SENDER_ONLINE "ccs.service.aaltetime.sfn.sender.online"

/** Controls the startup/shutdown of AaLteTime service on EE level.
* To be set to 1 if EE level startup of AaLteTime is required. */
#define AALTETIME_TAG_EE_LEVEL_ENABLED "ccs.service.aaltetime.ee.enabled"

/** Controls the startup/shutdown of AaLteTime service on CE level.
* To be set to 1 if CE level startup of AaLteTime is required.*/
#define AALTETIME_TAG_CE_LEVEL_ENABLED "ccs.service.aaltetime.ce.enabled"

/** Controls the start/terminate of sfn sender thread.
* Should be used only if service providing sfn
* via AALTETIME_GET_SFN_REQ_MSG / AALTETIME_GET_SFN_RESP_MSG is needed.
* @see AALTETIME_GET_SFN_REQ_MSG */
#define AALTETIME_TAG_SFN_SENDER_ENABLED "ccs.service.aaltetime.sfn.sender.enabled"

#ifdef __cplusplus
}
#endif

/**@}*/

#endif /*  _MCU_IFAALTETIME_DEFS_H */

