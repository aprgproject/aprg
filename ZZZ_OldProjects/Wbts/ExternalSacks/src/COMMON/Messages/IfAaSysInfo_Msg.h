/** @file
 *  @brief                 AaSysInfo messages definitions
 *
 *  $HeadURL$
 *  $LastChangedRevision$
 *  $LastChangedDate$
 *  $Author$
 *  $Copyright: Copyright 2018 Nokia. All right reserved.$
 */

#ifndef IF_COMMON_AASYSINFO_MSGS_H
#define IF_COMMON_AASYSINFO_MSGS_H

#include <CcsCommon.h>
#include <glo_def.h>
#include <TAaSysComSicad.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AASYSINFO_MAX_NAME_SIZE 64
#define AASYSINFO_MAX_LINE_SIZE 256

/**
************************************************************************************************
* @brief AaSysInfo End Point Type
*
* @par Description
* This enumerator is used as parameter in AASYSINFO_LOAD_CLIENT_NOTIF_MSG payload, to specify,
* if the AaSysInfo instance will act as client or local server.
***********************************************************************************************/
typedef enum ESysInfoEndPointType
{
    ESysInfoEndPointType_Server,
    ESysInfoEndPointType_Client
} ESysInfoEndPointType;

/**
************************************************************************************************
* @brief AaSysInfo Load Status
* @param dataLine an array holding each entry record, of the current measurement, as declared
* in register message. String must be \0 terminated.
*
* @par Description
* This structure holds AaSysInfo records, from the current measurements, that AaSysInfo clients
* want to store on AaSysInfo master via AASYSINFO_LOAD_STATUS_RESP_MSG.
* Example data line: 2017-01-01T00:03:06Z;4564;4604;588;
***********************************************************************************************/
typedef struct SAaSysInfoLoadStatus
{
    u8 dataLine[AASYSINFO_MAX_LINE_SIZE];
} SAaSysInfoLoadStatus;

/**
************************************************************************************************
* @brief AaSysInfo Load Header
* @param fileName an array holding filename for every entry the client wants to store on
* AaSysInfo server.
* @param headerLine of coma separated headers for measurements stored in single entity,
* string must be \0 terminated
*
* @par Description
* This message requests load info from client for the registered entities.
* The user provides the filename, for the file, that will be stored under this
* pattern: AaSysInfoUPLoad<SICAD><fileName><seq number>_<date>.csv[.xz]
* Example of header line: time stamp;USS [kB];PSS [kB];Loaded process code section [kB];
***********************************************************************************************/
typedef struct SAaSysInfoLoadHeader
{
    u8 fileName[AASYSINFO_MAX_NAME_SIZE];
    u8 headerLine[AASYSINFO_MAX_LINE_SIZE];
} SAaSysInfoLoadHeader;

/**
* @brief AaSysInfo client notification message
*
* @par Description
* This message is used to inform master AaSysInfo MCU (master node), that the client is up and would like to
* register to a given slave AaSysInfo MCU (FSP MCU node), for memory/CPU load storage.
*
* @par Message Id
* AASYSINFO_LOAD_CLIENT_NOTIF_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AASYSINFO_LOAD_CLIENT_NOTIF_MSG       0x14BD  /* !- SIGNO(struct SAaSysInfoLoadClientNotify ) -!  */

/**
* @brief AaSysInfo master ready notification
*
* @par Description
* This message is used to inform AaSysInfo clients that their master AaSysinfo node (FSP MCU node) is
* ready and waiting for registration message.
*
* @par Message Id
* AASYSINFO_READY_IND_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AASYSINFO_READY_IND_MSG        0x146A

/**
* @brief AaSysInfo client register message
*
* @par Description
* This message is used to register AaSysInfo client to AaSysInfo master. The client informs about
* the number of entries, pooling period in seconds and header and file name for each entry.
*
* @par Message Id
* AASYSINFO_LOAD_CLIENT_REGISTER_REQ_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AASYSINFO_LOAD_CLIENT_REGISTER_REQ_MSG        0x146B  /* !- SIGNO(struct SAaSysInfoLoadClientRegister ) -!  */

/**
* @brief AaSysInfo load request message
*
* @par Description
* This message is used to request CPU/memory samples collection from AaSysInfo clients.
*
* @par Message Id
* AASYSINFO_LOAD_STATUS_REQ_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AASYSINFO_LOAD_STATUS_REQ_MSG        0x146C

/**
* @brief AaSysInfo load respond message
*
* @par Description
* This message is used as an answer to request CPU/memory message, containing current sample
* from AaSysInfo clients.
*
* @par Message Id
* AASYSINFO_LOAD_STATUS_RESP_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AASYSINFO_LOAD_STATUS_RESP_MSG        0x146D  /* !- SIGNO(struct SAaSysInfoLoadStatusResp ) -!  */

/**
************************************************************************************************
* @brief AaSysInfo RT/DSP load client registration message structure
* @param client Sicad
* @param sampling period in seconds for AaSysInfo MCU to request data from RT/DSP nodes
* @param number of entries from one client
* @param header info structure holding file name and header for every entry.
*
* @par Description
* This message registers RT/DSP client to MCU SysInfo, for CPU and Memory load collection.
*
*
* @par Message Id
* AASYSINFO_LOAD_CLIENT_REGISTER_MSG
*
* @par Preconditions:
* In order to register to AaSysInfo master must pass the discovery process:
* -In the first step AaSysInfo client must publish AASYSINFO_LOAD_CLIENT_NOTIF_MSG via AaSysMb.
* -The master node AaSysInfo will validate the AaSysInfoServerConfig.txt configuration file and
* inform every MCU Slave about its clients.
* -On ready AaSysInfo MCU slave node will send AASYSINFO_LOAD_CLIENT_NOTIF_MSG to every client
* awaiting for registration messages.
* Example AaSysInfoServerConfig.txt content:
* 0x120D;[0x1231;0x1232;0x1233;0x1234;0x1241;0x1242;0x1243;0x1244;]
* 0x130D;[0x1331;0x1332;0x1333;0x1334;0x1341;0x1342;0x1343;0x1344;]
* 0x140D;[0x1431;0x1432;0x1433;0x1434;0x1441;0x1442;0x1443;0x1444;]
*
*
* @par Restrictions:
* Message has to be byte-mode oriented. Endianness has to be specified by Apf flag.
* Endianness can be set using AaSysComMsgSetApf2B. The receiver has to correctly decode
* word oriented parameters.
***********************************************************************************************/
typedef struct SAaSysInfoLoadClientRegister
{
    TAaSysComSicad clientSicad;
    u32 period;
    u32 numberOfEntries;
    SAaSysInfoLoadHeader headerInfo[1];
} SAaSysInfoLoadClientRegister;

/**
************************************************************************************************
* @brief AaSysInfo RT/DSP load client response message structure
* @param number of entries in the message
* @param data array, for every entry
*
* @par Description
* This message contains the information about memory/CPU data requested from the client. The data
* for every entry must match the header for that entry.
*
*
* @par Message Id
* AASYSINFO_LOAD_STATUS_RESP_MSG
*
* @par Restrictions:
* Message has to be byte-mode oriented. Endianness has to be specified by Apf flag.
* Endianness can be set using AaSysComMsgSetApf2B. The receiver has to correctly decode
* word oriented parameters.

***********************************************************************************************/
typedef struct SAaSysInfoLoadStatusResp
{
    u32 numberOfEntries;
    SAaSysInfoLoadStatus data[1];
} SAaSysInfoLoadStatusResp;

/**
************************************************************************************************
* @brief AaSysInfo client notification message.
* @param endpoint informs if the AaSysInfo instance will act as client or local server
*
* @par Description
* This message notifies AaSysInfo master (master node), that the client is ready. The notification
* informs the server about the clients SICAD.
*
* @par Message Id
* AASYSINFO_LOAD_CLIENT_NOTIF_MSG
***********************************************************************************************/
typedef struct SAaSysInfoLoadClientNotify
{
    ESysInfoEndPointType endpoint;
} SAaSysInfoLoadClientNotify;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* IF_COMMON_AASYSINFO_MSGS_H */
