/**
*******************************************************************************
* @brief                 AaTrblServer MCU messages.
* @module                AaTrblServer
*
* Copyright 2015, 2019 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_IF_AATRBLSERVER_MSG_H
#define _MCU_IF_AATRBLSERVER_MSG_H

#include <CcsCommon.h>

#include <../../COMMON/Messages/IfAaTrblServer_Msg.h>
#include <../Definitions/IfAaTrblServer_Defs.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
************************************************************************************************
* @defgroup dgAaTrblServerApiLinux AaTrblServer
* @ingroup  dgAaTrblServer
*/
/*@{*/
/**
* @brief AaTrblServer publishing message
*
* @par Description
* AaTrblServer uses this message to publish information to applications about new AaTrblServer in system.
*
* @par Message Id
* AATRBL_SERVER_REGISTER_REQ_MSG
*
* @par Restrictions:
* This message is supported only on LINUX_PC, LINUX_PC64, LINUX_FSM3, LINUX_FSM4, LINUX_OCTEON2_LRC, LINUX_ARM53_LE, LINUX_ARM57_LE and CCS_RT_LINUX targets.
* Rest platforms are not supported. DSP not handle this message.
***********************************************************************************************/
#define AATRBL_SERVER_REGISTER_REQ_MSG      0x10F2   /* !- SIGNO(struct SAaTrblServerRegisterReq) -!  */

/**
************************************************************************************************
* @defgroup dgAaTrblServerApiLinux AaTrblServer
* @ingroup  dgAaTrblServer
*/
/*@{*/
/**
* @brief AaTrblServer publishing response.
*
* @par Description
* AaTrblServer gets this message as a reply for `AATRBL_CLIENT_REGISTER_REQ_MSG` message.
*
* @par Message Id
* AATRBL_CLIENT_REGISTER_RESP_MSG
*
* @par Restrictions:
* This message is supported only on LINUX_PC, LINUX_PC64, LINUX_FSM3, LINUX_FSM4, LINUX_OCTEON2_LRC LINUX_ARM53_LE, LINUX_ARM57_LE and CCS_RT_LINUX targets.
* Rest platforms are not supported. DSP not handle this message.
***********************************************************************************************/
#define AATRBL_SERVER_REGISTER_RESP_MSG     0x10F3   /* !- SIGNO(struct SAaTrblServerRegisterResp) -!  */

/**
************************************************************************************************
* @defgroup dgAaTrblServerApiLinux AaTrblServer
* @ingroup  dgAaTrblServer
*/
/*@{*/
/**
* @brief AaTrblServer is requested by this message to store file/files
*
* @par Description
* AaTrblServer receives this message from application to store file/files
*
* @par message Id
* AATRBL_SERVER_FILE_REQ_MSG
*
* @par Restrictions:
* This message is supported only on LINUX_PC, LINUX_PC64, LINUX_FSM3, LINUX_FSM4, LINUX_OCTEON2_LRC LINUX_ARM53_LE, LINUX_ARM57_LE and CCS_RT_LINUX targets.
* Rest platforms are not supported. DSP not handle this message.
***********************************************************************************************/
#define AATRBL_SERVER_FILE_REQ_MSG          0x10F4   /* !- SIGNO(struct SAaTrblServerFileReq) -!  */

/**
************************************************************************************************
* @defgroup dgAaTrblServerApiLinux AaTrblServer
* @ingroup  dgAaTrblServer
*/
/*@{*/
/**
* @brief AaTrblServer response for AATRBL_SERVER_FILE_REQ_MSG message
*
* @par Description
* AaTrblServer sends this message as a reply for `AATRBL_SERVER_FILE_REQ_MSG` message.
*
* @par Message Id
* AATRBL_SERVER_FILE_RESP_MSG
*
* @par Restrictions:
* This message is supported only on LINUX_PC, LINUX_PC64, LINUX_FSM3, LINUX_FSM4, LINUX_OCTEON2_LRC LINUX_ARM53_LE, LINUX_ARM57_LE and CCS_RT_LINUX targets.
* Rest platforms are not supported. DSP not handle this message.
***********************************************************************************************/
#define AATRBL_SERVER_FILE_RESP_MSG         0x10F5   /* !- SIGNO(struct SAaTrblServerFileResp) -!  */

/**
************************************************************************************************
* @defgroup dgAaTrblServerApiLinux AaTrblServer
* @ingroup  dgAaTrblServer
*/
/*@{*/
/**
* @brief AaTrblServer is informed about finished download
*
* @par Description
* AaTrblServer is informed by this message that download is finished and file can be deleted
*
* @par message Id
* AATRBL_SERVER_DOWNLOADED_IND_MSG
*
* @par Restrictions:
* This message is supported only on LINUX_PC, LINUX_PC64, LINUX_FSM3, LINUX_FSM4, LINUX_OCTEON2_LRC LINUX_ARM53_LE, LINUX_ARM57_LE and CCS_RT_LINUX targets.
* Rest platforms are not supported. DSP not handle this message.
***********************************************************************************************/
#define AATRBL_SERVER_DOWNLOADED_IND_MSG    0x10F6   /* !- SIGNO(struct SAaTrblServerDownloadedInd) -!  */

/**
************************************************************************************************
* @defgroup dgAaTrblServerApiLinux AaTrblServer
* @ingroup  dgAaTrblServer
*/
/*@{*/
/**
* @brief AaTrblServer is requested to break store procedure
*
* @par Description
* AaTrblServer is requested to break store procedure, and finalize procedure in progress
*
* @par message Id
* AATRBL_SERVER_TRANSFER_STOP_IND_MSG
*
* @par Restrictions:
* This message is supported only on LINUX_PC, LINUX_PC64, LINUX_FSM3, LINUX_FSM4, LINUX_OCTEON2_LRC LINUX_ARM53_LE, LINUX_ARM57_LE and CCS_RT_LINUX targets.
* Rest platforms are not supported. DSP not handle this message.
***********************************************************************************************/
#define AATRBL_SERVER_TRANSFER_STOP_IND_MSG 0x10F7   /* !- SIGNO(struct SAaTrblServerTransferStopInd) -!  */

/**
************************************************************************************************
* @defgroup dgAaTrblServerApiLinux AaTrblServer
* @ingroup  dgAaTrblServer
*/
/*@{*/
/**
* @brief AaTrblServer is informed about changed configuration and client list
*
* @par Description
* AaTrblServer Master sends this message to AaTrblServer and informs about changed configuration and client list
*
* @par message Id
* AATRBL_SERVER_NODE_LIST_IND
*
* @par Restrictions:
* This message is supported only on LINUX_PC, LINUX_PC64, LINUX_FSM3, LINUX_FSM4, LINUX_OCTEON2_LRC LINUX_ARM53_LE, LINUX_ARM57_LE and CCS_RT_LINUX targets.
* Rest platforms are not supported. DSP not handle this message.
***********************************************************************************************/
#define AATRBL_SERVER_NODE_LIST_IND_MSG 0x1170   /* !- SIGNO(struct SAaTrblServerNodeListInd) -!  */

/**
************************************************************************************************
* @defgroup dgAaTrblServerApiLinux AaTrblServer
* @ingroup  dgAaTrblServer
*/
/*@{*/
/**
* @brief AaTrblServer is requested by this message to store snapshot
*
* @par Description
* AaTrblServer receives this message from application to store snapshot
*
* @par message Id
* AATRBL_SERVER_SNAPSHOT_REQ_MSG
*
* @par Restrictions:
* This message is supported only on LINUX_PC, LINUX_PC64, LINUX_FSM3, LINUX_FSM4, LINUX_ARM53_LE, LINUX_ARM57_LE targets.
* Rest platforms are not supported. DSP not handle this message.
***********************************************************************************************/
#define AATRBL_SERVER_SNAPSHOT_REQ_MSG          0x1443   /* !- SIGNO(struct SAaTrblServerSnapshotReq) -!  */

/**
************************************************************************************************
* @brief AaTrblServer registration message structure
* @param serverSicad   Sic address of registered server.
*
* @par Description
* AaTrblServer uses this message to get registered to Technical log master.
*
* @par Message Id
* AATRBL_SERVER_REGISTER_REQ_MSG
***********************************************************************************************/
typedef struct SAaTrblServerRegisterReq
{
  TAaSysComSicad  serverSicad;
} SAaTrblServerRegisterReq;

/**
************************************************************************************************
* @brief AaTrblServer registration response message.
* @param empty  this parameter is not really needed. It is used only to meet the C standard,
* which says that empty structures can cause an undefined behavior.
*
* @par Description
* AaTrblServer receives this message as a reply for `AATRBL_CLIENT_REGISTER_REQ_MSG` message.
*
* @par Message Id
* AATRBL_CLIENT_REGISTER_RESP_MSG
***********************************************************************************************/
typedef struct SAaTrblServerRegisterResp
{
  u32 empty;
} SAaTrblServerRegisterResp;


/**
************************************************************************************************
* @brief AaTrblServer file store request message structure
* @param first          this parameter is set to `True` if this is the first request.
* @param coverage       defines coverage of wanted files from AaTrbl clients (see AaTrbl API).
* @param containerName  container name prefix.
* @param keyWordList    holds key words in regexp format. Key words are separated by "|".
*                       ignored if empty. max length is AATRBL_SERVER_KEYWORD_MAX_LENGTH.
*
* @par Description
* After receiving this message from Technical log master, AaTrblServer
* starts to prepare a new package containing files from AaTrbl clients.
* Maximum package size and list of AaTrlb clients, from which
* AaTrblServer collects the  logs, is defined in
* AaTrblServerConfig.txt file contained within psconfig.tgz archive file.
*
* AaTrblServerConfig.txt config file format:
*
* <AaTrblServer Node Id>;<memory budget in bytes>;[<AaTrblClient Node Id>;<AaTrblClient Node Id>]
* e.g.
* 0x120D;10240;[0x120D;0x1231;0x1232;0x1233;0x1234;0x1235;0x1236;0x1237;0x1238]
*
* AaTrblServer requests log files from AaTrbl client using
* `AATRBL_FILE_STORE_REQ_MSG` / `AATRBL_FILE_STORE_RESP_MSG` message sequence.
* Files from AaTrbl clients are compressed using xz utility and added to a .zip
* container until maximum container size is not reached or there is no more files available.
* If maximum container size is set to `0`, container size is not limited
* and all files will be contained within one container file.
* If 'first' is set to `True` and keyWordList is empty, AaTrblServer will first send
* `AATRBL_FILE_PREPARE_REQ_MSG` to all its registered AaTrbl clients.
* If 'first' is set to `True` and keyWordList is not empty, AaTrblServer will first send
* `AATRBL_SELECTIVE_SNAPSHOT_START_REQ_MSG` to all its registered AaTrbl clients and receive
* a list of registered files from each AaTrbl client. AaTrlServer will select the files whose
* priorities match the coverage and logical file names match key words in keyWordList. Then
* AaTrblServer will send AATRBL_SELECTIVE_FILE_PREP_REQ_MSG` to all its registered AaTrlb clients
* with the selected files.

* If 'containerName' is NOT set, <name> parameter stays empty.
*
* Container file format:
*     <name>_< AaTrblServerNodeId >_part_<sequence number>.zip
*         <name>_<AaTrblClientNodeId>_<filename>.<zip|gzip|xz>
*         <name>_<AaTrblClientNodeId>_<filename>.<zip|gzip|xz>
*         <name>_<AaTrblClientNodeId>_<filename>.<zip|gzip|xz>
* e.g.
*     BTS10_120D_part_1.zip
*         BTS10_120D_runtime.xz
*         BTS10_1231_runtime.zip
*         BTS10_1232_runtime.gzip
*
* @par message Id
* AATRBL_SERVER_FILE_REQ_MSG
***********************************************************************************************/
typedef struct SAaTrblServerFileReq
{
  TBoolean          first;
  EAaTrblCoverage   coverage;
  char containerName[AATRBL_FILENAME_MAX_LENGTH]; //must be in big endian
  char keyWordList[AATRBL_SERVER_KEYWORD_MAX_LENGTH]; //must be in big endian
} SAaTrblServerFileReq;

/**
************************************************************************************************
* @brief AaTrblServer file prepare response message structure.
* @param status                 holds the status of operation.
* @param last                   this parameter is set to `True` if requested file is the last.
* @param fileName               path and actual filename.
* @param numberOfRemainingFiles Number of remaining files in AaTrblClients associated with AaTrblServer.
*
* @par Description
* Response message from AaTrblServer informs, that package containing files
* from AaTrbl clients have been prepared.
*
* @par message Id
* AATRBL_SERVER_FILE_RESP_MSG
***********************************************************************************************/
typedef struct SAaTrblServerFileResp
{
  EAaTrblServerFilePrepareStatus status;
  TBoolean                       last;
  char                           fileName[AATRBL_FILENAME_MAX_LENGTH]; //must be in big endian
  u32                            numberOfRemainingFiles;
} SAaTrblServerFileResp;



/**
************************************************************************************************
* @brief  Message notifies that requested files have been transferred
* @param empty  this parameter is not really needed. It is used only to meet the C standard,
* which says that empty structures can cause an undefined behavior.
*
* @par Description
* AaTrblServer receives this message from Technical log master when the file is
* fetched and is ready to be removed from the filesystem.
*
* @par Message Id
* AATRBL_SERVER_DOWNLOADED_IND_MSG
***********************************************************************************************/
typedef struct SAaTrblServerDownloadedInd
{
  u32 empty;
} SAaTrblServerDownloadedInd;


/**
************************************************************************************************
* @brief Message stops log collection from AaTrbl clients
* @param empty  this parameter is not really needed. It is used only to meet the C standard,
* which says that empty structures can cause an undefined behavior.
*
* @par Description
* AaTrblServer will remove temporary files from the filesystem and
* send `AATRBL_TRANSF_STOP_NOTIF_MSG` to its log clients.
*
* @par message Id
* AATRBL_SERVER_TRANSFER_STOP_IND_MSG
***********************************************************************************************/
typedef struct SAaTrblServerTransferStopInd
{
  u32 empty;
} SAaTrblServerTransferStopInd;

/**
************************************************************************************************
* @brief AaTrblServer is informed about changed configuration and client list
* @param memoryBudget       AaTrblServer configuration: memoryBudget (maximum size of zip file container)
* @param fullUpdate         Infomation if update is full or incremental
* @param clientsCount       Count of clients in list
* @param clientList         List of clients to be registered to AaTrblServer (size defined by clientsCount)
*
* @par Description
* AaTrblServer Master sends this message to AaTrblServer and informs about changed configuration and client list
*
* @par message Id
* AATRBL_SERVER_NODE_LIST_IND
***********************************************************************************************/
typedef struct SAaTrblServerNodeListInd
{
  u32 memoryBudget;
  TBoolean fullUpdate;
  u32 clientsCount;
  TAaSysComSicad clientList[1];
} SAaTrblServerNodeListInd;

/**
************************************************************************************************
* @brief AaTrblServer snapshot store request message structure
* @param coverage       defines coverage of wanted files from AaTrbl clients (see AaTrbl API).
* @param zipMaxFileSize defines target size of zip files (0 for single zip file).
* @param snapshotPath   output path (AaFile path) for snapshot collection. Path has to exist prior to snapshot request.
* @param containerName  container name prefix.
* @param keyWordList    holds key words in regexp format. Key words are separated by "|".
*                       ignored if empty. max length is AATRBL_SERVER_KEYWORD_MAX_LENGTH.
*
* @par Description
* After receiving this message AaTrblServer starts to prepare a packages containing files from AaTrbl clients.
* AaTrblServer will respond with one or multiple AATRBL_SERVER_FILE_RESP_MSG (depending on zipMaxFileSize setting).
* If zipMaxFileSize is 0, there always will be only one response (single zip file). In other case there will be
* response for each zip file, ending with response with last = true.
* List of AaTrlb clients, from which AaTrblServer collects the logs, is defined in
* AaTrblServerConfig.txt file contained within psconfig.tgz archive file.
*
* AaTrblServerConfig.txt config file format:
*
* <AaTrblServer Node Id>;<memory budget in bytes>;[<AaTrblClient Node Id>;<AaTrblClient Node Id>]
* e.g.
* 0x120D;10240;[0x120D;0x1231;0x1232;0x1233;0x1234;0x1235;0x1236;0x1237;0x1238]
*
* AaTrblServer requests log files from AaTrbl client using
* `AATRBL_FILE_STORE_REQ_MSG` / `AATRBL_FILE_STORE_RESP_MSG` message sequence.
* Files from AaTrbl clients are compressed using xz utility and added to a .zip
* container until maximum container size is not reached or there is no more files available.
* If maximum container size is set to `0`, container size is not limited
* and all files will be contained within one container file.
* If 'first' is set to `True` and keyWordList is empty, AaTrblServer will first send
* `AATRBL_FILE_PREPARE_REQ_MSG` to all its registered AaTrbl clients.
* If 'first' is set to `True` and keyWordList is not empty, AaTrblServer will first send
* `AATRBL_SELECTIVE_SNAPSHOT_START_REQ_MSG` to all its registered AaTrbl clients and receive
* a list of registered files from each AaTrbl client. AaTrlServer will select the files whose
* priorities match the coverage and logical file names match key words in keyWordList. Then
* AaTrblServer will send AATRBL_SELECTIVE_FILE_PREP_REQ_MSG` to all its registered AaTrlb clients
* with the selected files.

* If 'containerName' is NOT set, <name> parameter stays empty.
*
* Container file format:
*     <name>_< AaTrblServerNodeId >_part_<sequence number>.zip
*         <name>_<AaTrblClientNodeId>_<filename>.<zip|gzip|xz>
*         <name>_<AaTrblClientNodeId>_<filename>.<zip|gzip|xz>
*         <name>_<AaTrblClientNodeId>_<filename>.<zip|gzip|xz>
* e.g.
*     BTS10_120D_part_1.zip
*         BTS10_120D_runtime.xz
*         BTS10_1231_runtime.zip
*         BTS10_1232_runtime.gzip
*
* This message shall be send to AaTrblServer, which sicad can be obtained by subscribing for AATRBL_SERVER_REGISTER_RESP_MSG
*
* @par message Id
* AATRBL_SERVER_SNAPSHOT_REQ_MSG
***********************************************************************************************/
typedef struct SAaTrblServerSnapshotReq
{
  EAaTrblCoverage   coverage;
  u32 zipMaxFileSize;
  char snapshotPath[AATRBL_FILENAME_MAX_LENGTH]; //must be in big endian
  char containerName[AATRBL_FILENAME_MAX_LENGTH]; //must be in big endian
  char keyWordList[AATRBL_SERVER_KEYWORD_MAX_LENGTH]; //must be in big endian
} SAaTrblServerSnapshotReq;

/*@}*/

#ifdef __cplusplus
}
#endif


#endif /* _MCU_IF_AATRBLSERVER_MSG_H*/

