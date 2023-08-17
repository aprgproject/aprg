/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaSNTP messages definitions.
* @module                AaSNTP
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_IFAASNTP_MSG_H
#define _MCU_IFAASNTP_MSG_H

#include <CcsCommon.h>
#include <glo_def.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <IfAaSNTP_Defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup dgAaSNTPMcuMsgs AaSNTP MCU Messages
* @ingroup  dgAaSNTP
*/
/*@{*/


/**
* @brief AaSNTP Start request message
*
* @par Description
* This message is used for starting SNTP.
*
* @par Message Id
* AASNTP_START_REQ_MSG
*
* @par Restrictions:
*
***********************************************************************************************/

#define AASNTP_START_REQ_MSG            0x1F00  /* !- SIGNO(struct SAaSNTPStartReq) -! */


/**
* @brief AaSNTP Start response message
*
* @par Description
* This message is being sent by AaSNTP with Start result.
*
* @par Message Id
* AASNTP_START_RESP_MSG
*
* @par Restrictions:
*
***********************************************************************************************/

#define AASNTP_START_RESP_MSG           0x1F01  /* !- SIGNO(struct SAaSNTPResult) -! */


/**
* @brief AaSNTP Stop request message
*
* @par Description
* This message is used for stopping SNTP.
*
* @par Message Id
* AASNTP_STOP_REQ_MSG
*
* @par Restrictions:
*
***********************************************************************************************/

#define AASNTP_STOP_REQ_MSG             0x1F02  /* !- SIGNO(struct void) -! */


/**
* @brief AaSNTP Stop response message
*
* @par Description
* This message is being sent by AaSNTP with Stop result.
*
* @par Message Id
* AASNTP_STOP_RESP_MSG
*
* @par Restrictions:
*
***********************************************************************************************/

#define AASNTP_STOP_RESP_MSG            0x1F03  /* !- SIGNO(struct SAaSNTPResult) -! */


/**
* @brief AaSNTP Status request message
*
* @par Description
* This message is used for request actual status of AaSNTP service.
*
* @par Message Id
* AASNTP_STATUS_REQ_MSG
*
* @par Restrictions:
*
***********************************************************************************************/

#define AASNTP_STATUS_REQ_MSG           0x1F04  /* !- SIGNO(struct void) -! */


/**
* @brief AaSNTP Status response message
*
* @par Description
* This message is being sent by AaSNTP with status of AaSNTP service.
*
* @par Message Id
* AASNTP_STATUS_RESP_MSG
*
* @par Restrictions:
*
***********************************************************************************************/

#define AASNTP_STATUS_RESP_MSG          0x1F05  /* !- SIGNO(struct SAaSNTPResult) -! */


/**
* @brief AaSNTP Configure TRSW request message
*
* @par Description
* This message is used for sending configuration to AaSNTP service.
*
* @par Message Id
* AASNTP_CONFIGURE_TRSW_REQ_MSG
*
* @par Restrictions:
*
***********************************************************************************************/

#define AASNTP_CONFIGURE_TRSW_REQ_MSG   0x1F06  /* !- SIGNO(struct SAaSNTPConfigureTrswReq) -! */


/**
* @brief AaSNTP Configure TRSW response message
*
* @par Description
* This message is being sent by AaSNTP with result of configuration of AaSNTP service.
*
* @par Message Id
* AASNTP_CONFIGURE_TRSW_RESP_MSG
*
* @par Restrictions:
*
***********************************************************************************************/

#define AASNTP_CONFIGURE_TRSW_RESP_MSG  0x1F07  /* !- SIGNO(struct SAaSNTPResult) -! */


/**
* @brief AaSNTP Get server IP request message
*
* @par Description
* This message is used for request currently used server IP by AaSNTP service.
*
* @par Message Id
* AASNTP_GET_SERVER_IP_REQ_MSG
*
* @par Restrictions:
*
***********************************************************************************************/

#define AASNTP_GET_SERVER_IP_REQ_MSG    0x1F0A  /* !- SIGNO(struct void) -! */


/**
* @brief AaSNTP Get server IP response message
*
* @par Description
* This message is being sent by AaSNTP service and consist currently used server IP.
*
* @par Message Id
* AASNTP_GET_SERVER_IP_RESP_MSG
*
* @par Restrictions:
*
***********************************************************************************************/

#define AASNTP_GET_SERVER_IP_RESP_MSG   0x1F0B  /* !- SIGNO(struct SAaSNTPGetServerIpResp) -! */


/**
* @brief AaSNTP Get peers status request message
*
* @par Description
* This message is used for request status of connection NTPd to servers.
*
* @par Message Id
* AASNTP_GET_PEERS_STATUS_REQ_MSG
*
* @par Restrictions:
*
***********************************************************************************************/

#define AASNTP_GET_PEERS_STATUS_REQ_MSG 0x1F0C   /* !- SIGNO(struct void) -! */


/**
* @brief AaSNTP Get peers status response message
*
* @par Description
* This message is being sent by AaSNTP service and consist NTPd to servers connection statuses .
*
* @par Message Id
* AASNTP_GET_PEERS_STATUS_RESP_MSG
*
* @par Restrictions:
*
***********************************************************************************************/

#define AASNTP_GET_PEERS_STATUS_RESP_MSG 0x1F0D  /* !- SIGNO(struct SAaSNTPGetPeersStatusResp) -! */


/**
************************************************************************************************
* @brief AaSNTP peers statuses message structure
* @param result
* @param status
*
* @par Description
* This message is used to pass statuses of conection NTPd to servers.
*
* @par Message Id
* AASNTP_GET_PEERS_STATUS_RESP_MSG
***********************************************************************************************/
typedef struct SAaSNTPGetPeersStatusResp
{
    u32 result;
    SAaSNTPStatus status;
} SAaSNTPGetPeersStatusResp;

/**
************************************************************************************************
* @brief AaSNTP Configure TRSW message structure
* @param mPlane IP Address
* @param mPlane IP Tos
* @param external Primary NTP Server IP
* @param external Secondary NTP Server IP
* @param external Tertiary NTP Server IP
* @param fsmInternalNtpIPAddress IP
*
* @par Description
* This message is used to pass configuration to AaSNTP.
* fsmInternalNtpIPAddress is optional, please fill with "0.0.0.0" if you do not want to pass IP.
*
* @par Message Id
* AASNTP_CONFIGURE_TRSW_REQ_MSG
***********************************************************************************************/

typedef struct SAaSNTPConfigureTrswReq
{
    char mPlaneIPAddress[AASNTP_STR_LEN];
    u32 dscp;
    char extPrimaryNTPSrv[AASNTP_STR_LEN];
    char extSecondaryNTPSrv[AASNTP_STR_LEN];
    char extTertiaryNTPSrv[AASNTP_STR_LEN];
    char fsmInternalNtpIPAddress[AASNTP_STR_LEN];
} SAaSNTPConfigureTrswReq;

/**
************************************************************************************************
* @brief AaSNTP Get Server IP message structure
* @param server IP Address
* @param result
*
* @par Description
* This message is used to pass IP of currently used server by SNTP.
*
* @par Message Id
* AASNTP_GET_SERVER_IP_RESP_MSG
***********************************************************************************************/

typedef struct SAaSNTPGetServerIpResp
{
    char serverIp[AASNTP_STR_LEN];
    u32 result;
} SAaSNTPGetServerIpResp;

/**
************************************************************************************************
* @brief AaSNTP Start request message structure
* @param flags
*
* @par Description
* This message is used to pass flags to AaSNTPStart function.
*
* @par Message Id
* AASNTP_START_REQ_MSG
***********************************************************************************************/

typedef struct SAaSNTPStartReq
{
    u32 flags;
} SAaSNTPStartReq;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /*  _IFAASNTP_MSG_H */
