/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _COMMON_IF_TRBL_MSG_H_
#define _COMMON_IF_TRBL_MSG_H_

#include <CcsCommon.h>
#include <TAaSysComSicad.h>
#include <IfAaTrbl_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaTrblApiCommon AaTrbl COMMON API
 * @ingroup  dgAaTrbl
 */

/* @{ */

/**@name AaTrbl message id definitions.
 * @{
 */
#define AATRBL_CLIENT_REGISTER_REQ_MSG    0x0979	/* !- SIGNO(struct SAaTrblClientRegisterReq) -!  */
#define AATRBL_CLIENT_REGISTER_RESP_MSG   0x097B	/* !- SIGNO(struct SAaTrblClientRegisterResp) -!  */
#define AATRBL_FILE_PREPARE_REQ_MSG       0x097E	/* !- SIGNO(struct SAaTrblFilePrepReq) -!  */
#define AATRBL_FILE_PREPARE_RESP_MSG      0x097F	/* !- SIGNO(struct SAaTrblFilePrepResp) -!  */
#define AATRBL_FILE_STORE_REQ_MSG         0x097D	/* !- SIGNO(struct SAaTrblFileStoreReq) -!  */
#define AATRBL_FILE_STORE_RESP_MSG        0x097C	/* !- SIGNO(struct SAaTrblFileStoreResp) -!  */
#define AATRBL_TRANSF_STOP_NOTIF_MSG      0x097A        /* !- SIGNO(struct SAaTrblTransfStopNotif) -!  */
#define AATRBL_SELECTIVE_SNAPSHOT_START_REQ_MSG     0x13B5	/* !- SIGNO(struct SAaTrblSelectiveSnapshotStartReq) -!  */
#define AATRBL_SELECTIVE_SNAPSHOT_START_RESP_MSG    0x13B6	/* !- SIGNO(struct SAaTrblSelectiveSnapshotStartResp) -! */
#define AATRBL_SELECTIVE_FILE_PREP_REQ_MSG          0x13B7	/* !- SIGNO(struct SAaTrblSelectiveFilePrepReq) -!   */
/**
 * @}
 */
/**
 * @}
 */

/**@name AaTrbl message structures.
 * @{
 */

/**
* @brief AaTrbl/Technical log client registration message structure
* @param clientSicad    Sic address of registered client.
*
* @par Description
* AaTrbl uses this message to get registered to Technical log master.
*
* @par Message Id
* AATRBL_CLIENT_REGISTER_REQ_MSG
*/
typedef struct SAaTrblClientRegisterReq
{
  TAaSysComSicad  clientSicad;
} SAaTrblClientRegisterReq;


/**
* @brief Response for AaTrblTechLogSrv's registration message
* @param empty    Only for making every compiler happy.
*
* @par Description
* AaTrbl receives this message as reply for registration message.
*
* @par Message Id
* AATRBL_CLIENT_REGISTER_RESP_MSG
*/
typedef struct SAaTrblClientRegisterResp
{
  u32 empty;
} SAaTrblClientRegisterResp;


/**
* @brief AaTrbl file prepare request message structure
* @param coverage     Defines coverage of wanted files.
*
* @par Description
* Technical log master sends this message to AaTrbl when files are wanted to
* be frozen. AaTrbl service calls registered files callback functions that
* prepare and freeze the file.
*
* @par message Id
* AAATRBL_FILE_PREPARE_REQ_MSG
*/
typedef struct SAaTrblFilePrepReq
{
  EAaTrblCoverage   coverage;
} SAaTrblFilePrepReq;

/**
* @brief AaTrbl file prepare response message structure
* @param status                Informs status of operation.
* @param numberOfPreparedFiles Number of successfully prepared files by AaTrblClient.
*
* @par Description
* A response message that AaTrbl sends to Technical log master when files are
* freezed and prepared.
*
* @par message Id
* AAATRBL_FILE_PREPARE_RESP_MSG
*/
typedef struct SAaTrblFilePrepResp
{
  EAaTrblFileTransfStatus status;
  u32                     numberOfPreparedFiles;
} SAaTrblFilePrepResp;


/**
* @brief AaTrbl file store request message structure
* @param first True if this is the first request
*
* @par Description
* Technical log master sends this message to AaTrbl when it is ready to start
* handling files. first-field indicates if request is the first. AaTrbl
* service calls one of registered files callback function that handles storing
* file to AaFile service. In case request is not the first, AaTrbl calls file
* deletion callback function for previously handled file.
*
* @par message Id
* AAATRBL_FILE_STORE_REQ_MSG
*/
typedef struct SAaTrblFileStoreReq
{
  TBoolean          first;
} SAaTrblFileStoreReq;

/**
* @brief AaTrbl file store response message structure.
* @param status                 Informs status of operation.
* @param last                   True if file is the last.
* @param compressed             True if file is compressed.
* @param fileTransferInfo       Defines all important information that is
*                               needed when transferring file.
* @param logicalFileName        Logical name of the file.
* @param pathAndActualFileName  Path and actual file name.
* @param fileSize               File size, -1 if file doesn't exist.
*
* @par Description
* A response message that AaTrbl sends to Technical log master
* when files are ready to be fetched from AaFile service. Last-field indicates
* that the last file is ready to be fetched.
* User (Tech Log Master) needs to call AaSysComGetRawData() to read message AATRBL_FILE_STORE_RESP_MSG,
* because filename and path are stored in BIG_ENDIAN notation.
*
* @par message Id
* AATRBL_FILE_STORE_RESP_MSG
*/
typedef struct SAaTrblFileStoreResp
{
  EAaTrblFileTransfStatus status;
  TBoolean                last;
  TBoolean                compressed;
  SAaTrblFileTransferInfo fileTransferInfo;
  char logicalFileName[AATRBL_FILENAME_MAX_LENGTH];
  char pathAndActualFileName[AATRBL_FILENAME_MAX_LENGTH];
  i32  fileSize;
} SAaTrblFileStoreResp;


/**
* @brief Message notifying that all files have been transferred.
* @param empty  Only for making every compiler happy.
*
* @par Description
* AaTrbl receives this message from Technical log master when the last file is
* fetched and is ready to be removed from filesystem.
*
* @par message Id
* AATRBL_TRANSF_STOP_NOTIF_MSG
*/
typedef struct SAaTrblTransfStopNotif
{
  u32 empty;
} SAaTrblTransfStopNotif;

/**
* @brief AaTrbl selective snapshot start request message structure
* @param coverage       Defines coverage of wanted files
*
* @par Description
* AaTrblServer sends this message to AaTrbl to trigger mini snapshot start.
* AaTrbl service calls presnapshot callbacks and get a complete list of registered files.
*
* @par message Id
* AATRBL_SELECTIVE_SNAPSHOT_START_REQ_MSG
*/
typedef struct SAaTrblSelectiveSnapshotStartReq
{
  EAaTrblCoverage  coverage;
}SAaTrblSelectiveSnapshotStartReq;

/**
* @brief AaTrbl selective snapshot start response message structure
* @param status        Status of the operation
* @param last          In case of multiple messages. If there is more than AATRBL_MAX_SELECTIVE_FILE_COUNT files, multiple messages will be send, last message will have last=GLO_TRUE
* @param fileCount     Number of files in message
* @param files         An array holding registered files information, max count is defined by AATRBL_MAX_SELECTIVE_FILE_COUNT
*
*
* @par Description
* AaTrbl sends this response message to AatrblServer to provide a list of registered files.
*
* @par message Id
* AATRBL_SELECTIVE_SNAPSHOT_START_RESP_MSG
*/
typedef struct SAaTrblSelectiveSnapshotStartResp
{
  EAaTrblSnapshotStartStatus status;
  TBoolean                   last;
  u32                        fileCount;
  SAaTrblRegisteredFileInfo  files[1];
}SAaTrblSelectiveSnapshotStartResp;

/**
* @brief AaTrbl selective file request message structure
* @param coverage           Defines coverage of wanted files(needed only for running performance)
* @param last          In case of multiple messages. If there is more than AATRBL_MAX_SELECTIVE_FILE_COUNT files, multiple messages will be send, last message will have last=GLO_TRUE
* @param fileCount          Number of files in message
* @param logicalFilesName   A list of logical files to be prepared whose names match certain
*                           key words and priorities match coverage, max count is defined by AATRBL_MAX_SELECTIVE_FILE_COUNT
*
* @par Description
* AaTrblServer sends this message to AaTrbl when selective files are wanted to
* be frozen. AaTrbl service calls registered files callback functions that
* prepare and freeze the files.
*
* @par message Id
* AATRBL_SELECTIVE_FILE_PREP_REQ_MSG
*/
typedef struct SAaTrblSelectiveFilePrepReq
{
  EAaTrblCoverage  coverage;
  TBoolean         last;
  u32              fileCount;
  char             logicalFilesName[1][AATRBL_FILENAME_MAX_LENGTH]; //must be in network endianness
}SAaTrblSelectiveFilePrepReq;

/**
 * @}
 */

/**@}*/


#ifdef __cplusplus
}
#endif

#endif /* _COMMON_IF_TRBL_MSG_H_*/
