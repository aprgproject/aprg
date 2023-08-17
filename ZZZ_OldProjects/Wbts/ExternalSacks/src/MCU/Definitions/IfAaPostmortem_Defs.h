/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaPostmortem definitions.
* @module                AaPostmortem
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef IFAAPOSTMORTEM_DEFS_H
#define IFAAPOSTMORTEM_DEFS_H

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup dgAaPostmortemMcuDefs MCU AaPostmortem Definitions
* @ingroup dgAaPostmortem
*/

/*@{*/

/*
*  Configuration tags for backup procedure.
*/

/**
*  @brief The tag defines the path where backup logs are stored .
*  The type of tag is u32.
*/
#define AAPOSTMORTEM_CONFIG_TAG_BACKUP_PATH  "ccs.service.aapostmortem.backup.path"

/**
*  @brief The tag limits execution time for backup script.
*  The type of tag is u32. The max timeout is 60s.
*/
#define AAPOSTMORTEM_CONFIG_TAG_BACKUP_TIMEOUT  "ccs.service.aapostmortem.backup.timeout"

/**
*  @brief The tag defines if AaPostmortem registers coldreset logs to AaTrb.
*  The type of tag is u32. Value 0 disables coldreset logs registration to AaTrbl.
*/
#define AAPOSTMORTEM_CONFIG_TAG_BACKUP_REGISTER  "ccs.service.aapostmortem.backup.register"

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* IFAAPOSTMORTEM_DEFS_H */
