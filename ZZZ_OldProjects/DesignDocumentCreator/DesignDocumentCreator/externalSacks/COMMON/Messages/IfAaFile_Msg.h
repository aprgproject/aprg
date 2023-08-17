/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaFile interface header
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _COMMON_IF_AAFILE_MSG_H_
#define _COMMON_IF_AAFILE_MSG_H_

#include <glo_def.h>
#include <CcsCommon.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <../../COMMON/Definitions/IfAaFile_Defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaFile AaFile API
 */

/** @{ */

/** @brief Un-Mount message ID
*   @par Restrictions: Currently used only by HDBDE.
*/
#define AAFILE_PREPARE_UNMOUNT_NOTIF_MSG 0x108B      /**< !- SIGNO(struct SAaFilePrepareUnmountNotif) -!  */

/**  @struct SAaFilePrepareUnmountNotif
 *   @brief Mount message
 *   @details Restrictions: Currently used only by HDBDE.
 */
typedef struct SAaFilePrepareUnmountNotif {
    char path[AAFILE_FILENAME_MAX];   /**< Unmounted volume path. Zero terminated string. */
} SAaFilePrepareUnmountNotif;

/** @brief Mount message ID
*   @par Restrictions: Currently used only by HDBDE.
*/
#define AAFILE_MOUNTED_NOTIF_MSG 0x108C      /**< !- SIGNO(struct SAaFileMountedNotif) -!  */

/** @brief Mount message
*   @par Restrictions: Currently used only by HDBDE.
*/
typedef struct SAaFileMountedNotif {
    char path[AAFILE_FILENAME_MAX];   /**< Mounted volume path. Zero terminated string. */
} SAaFileMountedNotif;

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _COMMON_IF_AAFILE_MSG_H_ */
