/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef  _COMMON_IF_AATRBL_DEF_H_
#define  _COMMON_IF_AATRBL_DEF_H_

#include <CcsCommon.h>
#include <TAaSysComSicad.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaTrblApiCommon AaTrbl COMMON API
 * @ingroup  dgAaTrbl
 */

/* @{ */

/** @brief  Technical log master sic address. This tag should be set in case
            message broker service is not used for registering. */
#define AATRBL_CONFIG_TAG_TECHLOGMASTERSICAD  "ccs.service.aatrbl.techlogmastersicad"

/*!
 * @brief Defines AaTrbl thread nice level. By default the level is 0.
 *
 * @par Restrictions:
 * This config tag is supported only on LINUX_PC, LINUX_PC64, LINUX_FSM3, LINUX_FSM4 and CCS_RT_LINUX targets.
 * Rest platforms are not supported. DSP not handle this tag.
 */
#define AATRBL_CONFIG_TAG_THREAD_NICE  "ccs.service.aatrbl.thread.nice.level"

/** @brief Maximum length of filename */
#define AATRBL_FILENAME_MAX_LENGTH        80
/** @brief Maximum length of transfer info parameter (see SAaTrblFileTransferInfo). */
#define AATRBL_TR_INFO_MAX_LENGTH         64

/** @brief Maximum number registered files */
#define AATRBL_MAX_NUM_REGISTERED_FILE    200

/** @brief Maximum selective snapshot file count per message */
#define AATRBL_MAX_SELECTIVE_FILE_COUNT    100

/** @brief AaTrbl return values. */
typedef enum EAaTrblRet{
  EAaTrblRet_Ok                = 0, /**< Ok. */
  EAaTrblRet_InvalidParameter,      /**< Invalid parameter. */
  EAaTrblRet_NotInitialized,        /**< Service not started/initialized. */
  EAaTrblRet_MemAllocFailure,	    /**< Failed to allocate memory for internal usage. */
  EAaTrblRet_Locked,                /**< File locked, try again later. */
  EAaTrblRet_AlreadyRegistered,     /**< File is already registered. */
  EAaTrblRet_NbrOf                  /**< Not usable value, always the last. */

} EAaTrblRet;


/** @brief Coverage level. */
typedef enum EAaTrblCoverage
{
  EAaTrblCoverage_Minor   = 0,      /**< Minor coverage. Covers only the most important
                                         (high priority) files. */
  EAaTrblCoverage_Normal,           /**< Normal coverage. */
  EAaTrblCoverage_Full,             /**< Full coverage. */
  EAaTrblCoverage_NbrOf             /**< Not usable value, always the last. */
} EAaTrblCoverage;


/** @brief File priority. */
typedef enum EAaTrblFilePriority
{
  EAaTrblFilePriority_High  = 0,    /**< The most important files. For minor coverage file requests. */
  EAaTrblFilePriority_Normal,       /**< Normal file priority. */
  EAaTrblFilePriority_Low,          /**< Priority is low. */
  EAaTrblFilePriority_NbrOf         /**< Not usable value, always the last. */
} EAaTrblFilePriority;

/** @brief Status of file preparation for being transferred. */
typedef enum EAaTrblFileTransfStatus
{
  EAaTrblFileTransfStatus_FreezedOk  = 0, /**< Ok, file is freezed. */
  EAaTrblFileTransfStatus_FileUploadable, /**< Ok, file is ready for uploading. */
  EAaTrblFileTransfStatus_NoFiles,        /**< There is no files to fetch. */
  EAaTrblFileTransfStatus_Error,          /**< Something went wrong, error. */
  EAaTrblFileTransfStatus_NbrOf           /**< Not usable value, always the last. */
} EAaTrblFileTransfStatus;


/** @brief Callback function return value. */
typedef enum EAaTrblCbStatus
{
  EAaTrblCbStatus_Ok  = 0,  /**< Ok. */
  EAaTrblCbStatus_Nok,      /**< File not OK. Used inside storeCb. When storeCb returns this value - file is discarded from snapshot
                                 and error is reported. Snapshot will continue with next file. When prepareCb returns this value -
                                 whole snapshot is stoped.  EAaTrblCbStatus_Nok should not be used in prepare callback functions. */
  EAaTrblCbStatus_NotReady, /**< File not ready. Used inside prepareCb. When prepareCb returns this value - file is ignored and
                                 discarded from snapshot (but this is not error). When storeCb returns this enum - file is discarded,
                                 but error is also reported.  EAaTrblCbStatus_NotReady should not be used in store callback functions. */
  EAaTrblCbStatus_NbrOf     /**< Not usable value, always the last. */
} EAaTrblCbStatus;


/** @brief Defines username and passwd needed when fetching the file. */
typedef struct SAaTrblFileTransferInfo
{
  char username[AATRBL_TR_INFO_MAX_LENGTH];  /**< Username needed when fetching file from AaFile service. */
  char passwd[AATRBL_TR_INFO_MAX_LENGTH];    /**< Password needed when fetching file from AaFile service. */

} SAaTrblFileTransferInfo;

/** @brief Status of snapshot start response status. */
typedef enum EAaTrblSnapshotStartStatus
{
  EAaTrblSnapshotStartStatus_Ok  = 0,            /**< Ok. */
  EAaTrblSnapshotStartStatus_AlreadyInProgress,  /**< Error, already in progress */
  EAaTrblSnapshotStartStatus_Error,              /**< Error. */
  EAaTrblSnapshotStartStatus_NbrOf               /**< Not usable value, always the last. */
} EAaTrblSnapshotStartStatus;


/** @brief Defines registered file information. */
typedef struct SAaTrblRegisteredFileInfo
{
  TBoolean            compressed;
  EAaTrblFilePriority priority;
  char                logicalFileName[AATRBL_FILENAME_MAX_LENGTH]; //must be in big endian
}SAaTrblRegisteredFileInfo;



/**@name AaTrbl callback function types.
 * @{
 */

/**
* @brief Callback function typedef for freezing the file.
* @param[in] logicalFileName  logical name of the file to be prepared.
* @param[in] opaque           User defined data passed to function.
*/
typedef EAaTrblCbStatus TAaTrblPrepareFileCb(char const * const logicalFileName,
                                             const void *opaque);


/**
* @brief Callback function typedef for storing the file to AaFile.
* @param[in] logicalFileName  logical name of the file to be stored.
* @param[in] opaque           User defined data passed to function.
*/
typedef EAaTrblCbStatus TAaTrblStoreFileCb(char const * const logicalFileName,
                                           const void *opaque);


/**
* @brief Callback function typedef for deleting the file.
* @param[in] logicalFileName  logical name of the file to be deleted.
* @param[in] opaque           User defined data passed to function.
*/
typedef void TAaTrblDeleteFileCb(char const * const logicalFileName,
                                 const void *opaque);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* _COMMON_IF_AATRBL_DEF_H_*/
