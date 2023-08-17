/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 MCU AaFile definitions.
*
* Copyright 2017 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _MCU_IF_AAFILE_DEFS_H_
#define _MCU_IF_AAFILE_DEFS_H_

#include <CcsCommon.h>

#include <../../COMMON/Definitions/IfAaFile_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaFileApiMcu
 * @ingroup dgAaFile
 */

/** @{ */

/**
 *  @brief  A type for interface function parameters.
 */
typedef enum EAaFileListDirFormat
{
    EAaFileListDirFormat_Short      = 0,    /**< Short format parameter */
    EAaFileListDirFormat_Long       = 1,    /**< Long format parameter */
    EAaFileListDirFormat_NotValid           /**< Invalid parameter */
} EAaFileListDirFormat;

/**
 *  @brief  AaFileIsFsMounted return values.
 */
typedef enum EAaFileFsMountStatus
{
    EAaFileFsNotMounted     = 0,    /**< Queried FS is not mounted */
    EAaFileFsMounted        = 1,    /**< Queried FS is mounted */
    EAaFileFsInvalidPath    = 2     /**< Given path is incorrect */
} EAaFileFsMountStatus;

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _MCU_IF_AAFILE_DEFS_H_ */
