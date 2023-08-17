/**
*******************************************************************************
* @brief                 AaTrblServer MCU definitions.
* @module                AaTrblServer
*
* Copyright 2019 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_IF_AATRBLSERVER_DEF_H_
#define _MCU_IF_AATRBLSERVER_DEF_H_

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaTrblServerMcuDefs AaTrblServer MCU definitions
 * @ingroup dgAaTrblServer
 * @{
 */

/*!
 * @brief Defines a maximum number of active AaTrblServer receive files threads. By default the level is 0 (unlimited).
 */
#define AATRBLSERVER_CONFIG_TAG_RECEIVEFILES_THREADS_LIMIT  "ccs.service.aatrblserver.receivefiles.threads.limit"


#define AATRBL_SERVER_CLIENT_TIMEOUT 60               /* Timeout in seconds for Server to wait for Client response  */
#define AATRBL_SERVER_FILE_RESP_MSG_TIMEOUT 900       /* Timeout in seconds for snapshot file response */
#define AATRBL_SERVER_DOWNLOADED_IND_MSG_TIMEOUT 1800 /* Timeout in seconds for snapshot download indication */

typedef enum EAaTrblServerFilePrepareStatus
{
  EAaTrblServerFilePrepareStatus_Ok = 0,                   /**< Ok, file is prepared.
                                                                CC&S will wait for `AATRBL_SERVER_DOWNLOADED_IND_MSG` in order to remove the prepared file */
  EAaTrblServerFilePrepareStatus_Partial,                  /**< Not all files are included in container due to an error in gathering logs from AaTrbl clients.
                                                                CC&S will wait for `AATRBL_SERVER_DOWNLOADED_IND_MSG` in order to remove the prepared file */
  EAaTrblServerFilePrepareStatus_NoFiles,                  /**< There are no files to fetch.
                                                                This status is used together with with 'last' = `true`, CC&S will not wait for `AATRBL_SERVER_DOWNLOADED_IND_MSG` */
  EAaTrblServerFilePrepareStatus_InvalidParams,            /**< Invalid parameters in request. There are no files to fetch.
                                                                This status is used together with with 'last' =`true`, CC&S will not wait for `AATRBL_SERVER_DOWNLOADED_IND_MSG` */
  EAaTrblServerFilePrepareStatus_Error,                    /**< Something went wrong, error. There are no files to fetch.
                                                                This status is used together with with 'last' = `true`, CC&S will not wait for `AATRBL_SERVER_DOWNLOADED_IND_MSG` */
  EAaTrblServerFilePrepareStatus_FailedSnapshotInProgress, /**< Snapshot is currently in progress, in order to collect snapshot, previous one should finish first or can be cancelled,
                                                                CC&S will not wait for `AATRBL_SERVER_DOWNLOADED_IND_MSG */
  EAaTrblServerFilePrepareStatus_NbrOf                     /**< Not usable value */
} EAaTrblServerFilePrepareStatus;


/*!
 *  @brief Defines AaTrblServer store request thread count per node.
 */
#define AATRBLSERVER_CONFIG_TAG_RECEIVEFILES_PARALLEL_PER_NODE  "ccs.service.aatrblserver.receivefiles.thread.numberpernode"

/*!
 *  @brief Defines AaTrblServer receive files thread nice level. By default the level is 0.
 */
#define AATRBLSERVER_CONFIG_TAG_RECEIVEFILES_THREAD_NICE  "ccs.service.aatrblserver.receivefiles.thread.nice.level"

/** @brief Maximum length of key words*/
#define AATRBL_SERVER_KEYWORD_MAX_LENGTH 512

/** @} end: @addtogroup dgAaTrblServerMcuDefs AaTrblServer MCU definitions */

#ifdef __cplusplus
}
#endif

#endif /* _MCU_IF_AATRBLSERVER_DEF_H_*/
