/**
*******************************************************************************
* @file
* $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaTestPort MCU Messages.
*
* Copyright 2015 Nokia Soultions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_IF_AATESTPORT_MSGS_H
#define _MCU_IF_AATESTPORT_MSGS_H

#include <CcsCommon.h>
#include <glo_def.h>
#include <IfAaTestPort_Defs.h>
#include <IfAaSysComGw_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
********************************************************************************
* @defgroup dgAaTestPortMcuMsgs AaTestPort Messages (MCU)
* @ingroup  dgAaTestPort
*/

/**@{*/

/**
********************************************************************************
*
* @brief AaTestPort extended client connection status message
*
* @par Description
* This message indicates availability of TCP client connection on Test Port.
*
* @par Message Id
* AATESTPORT_CLIENT_EXT_CONN_STATUS_IND_MSG
*
* @par Restrictions:
*
********************************************************************************/
#define AATESTPORT_CLIENT_EXT_CONN_STATUS_IND_MSG  0x11B3 /* !- SIGNO(struct SAaTestPortClientExtInd) -!  */

/**
********************************************************************************
* @brief AaTestPort extended client connection status message structure
*
* @par Description
* This message indicates availability of TCP client connection on Test Port.
*
* @par Message Id
* AATESTPORT_CLIENT_EXT_CONN_STATUS_IND_MSG
*
* @par Restrictions:
*
*********************************************************************************/
typedef struct SAaTestPortClientExtInd
{
    char  clientName[AATESTPORT_CLIENT_MAX_NAME_LENGTH];    /**< Client name. */
    char  remoteIpAddr[AASYSCOM_GW_IP_ADDRESS_MAX_STR_LEN]; /**< Remote Ip address. */
    u32   remotePort;                                       /**< Remote Port. */
    u32   status;                                           /**< Connection status - 0 if unavailable, 1 if available.*/
}SAaTestPortClientExtInd;


/**
********************************************************************************
*
* @brief AaTestPort Server connection indication message
*
* @par Description
* This message indicates AaTestPort Sever is successfully connected to client
*
* @par Message Id
* AATESTPORT_SERVER_CONN_IND_MSG
*
* @par Restrictions:
*
********************************************************************************/
#define AATESTPORT_SERVER_CONN_IND_MSG  0x4FBA /* !- SIGNO( No structure needed as only header is required for indication) -!  */

/**@}*/

#ifdef __cplusplus
}
#endif
#endif /* _MCU_IF_AATESTPORT_MSGS_H */
