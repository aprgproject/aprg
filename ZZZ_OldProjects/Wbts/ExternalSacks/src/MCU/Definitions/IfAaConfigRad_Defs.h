/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_IF_AACONFIG_RAD_DEF_H_
#define _MCU_IF_AACONFIG_RAD_DEF_H_

#include <CcsCommon.h>

#include "../../COMMON/Definitions/IfAaConfigRad_Defs.h"
#include "../../SHARED/MCU_RT/Definitions/IfAaConfigRad_Defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaConfigRadDefsMcu AaConfigRad MCU definitions
 * @ingroup dgAaConfigRadDefs
 */
/*@{*/

/** @brief The size of buffer (in bytes) for logging RaD parameters changes in RadMaster.
    The type of tag is u32. Value 0 disables logging of RaD parameters changes in RadMaster */
#define   AACONFIGRAD_TAG_RAD_MASTER_CHANGE_LOG_SIZE "ccs.service.aaconfig.rad.master.change.log.size"
/** @brief The size of buffer (in bytes) for logging R&D parameters changes through AaShell commands.
    The type of tag is u32. Value 0 disables logging of RaD parameters changes through AaShell commands.*/
#define   AACONFIGRAD_TAG_SHELL_COMMAND_CHANGE_BUFFER_SIZE "ccs.service.aaconfig.rad.shell.change.log.size"
/** @brief The size of file (in bytes) for logging R&D parameters with non-default values in technical report.
    The type of tag is u32. Value 0 disables logging of R&D parameters with non-default values in technical report*/
#define   AACONFIGRAD_TAG_NONDEFAULT_RAD_PARAMETERS_FILE_SIZE "ccs.service.aaconfig.rad.nondefault.log.size"

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  //_MCU_IF_AACONFIG_RAD_DEF_H_
