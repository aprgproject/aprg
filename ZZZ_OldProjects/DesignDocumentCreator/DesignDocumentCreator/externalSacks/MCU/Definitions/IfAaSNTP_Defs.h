/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaSNTP definitions.
* @module                AaSNTP
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_IFAASNTP_DEFS_H
#define _MCU_IFAASNTP_DEFS_H

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <glo_def.h>
#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup dgAaSNTPMcuDefs AaSNTP MCU Definitions 
* @ingroup dgAaSNTP
 */
/*@{*/


/** Pathname where to find NTP client. If not set then "/usr/bin/ntpclient" is used */
#define   AASNTP_CONFIG_TAG_CLIENT_EXECUTABLE    "ccs.service.aasntp.client.executable"

/** Port number on which the SNTP server connects for connections. */
#define   AASNTP_CONFIG_TAG_CLIENT_REMOTE_PORT   "ccs.service.aasntp.client.remoteport"

#define AASNTP_FLAGS_NONE	0x0
#define AASNTP_FLAGS_ONESHOT    0x1
#define AASNTP_FLAGS_NOSET	0x2
#define AASNTP_STR_LEN 100


#define AASNTP_DAEMON_CPID 0x062C

#define AASNTP_NUM_OF_EXT_NTP_SERVERS 3
#define AASNTP_NOT_CONFIGURED "0.0.0.0"
#define AASNTP_NUM_OF_INT_GPS_ADDRESSES 1 /* Deprecated with CNI-4779 */
#define AASNTP_NUM_OF_EXT_NTP_SERVERS 3
#define AASNTP_IP_ADDRESS_LENGTH 256
#define AASNTP_NUM_OF_SERVERS 6 //GPS internal or external, ToP, CPRI (3 shm address + 3 external ntp servers)
#define AASNTP_FSM_IP_ADDRESS "192.168.255.1"

#define AASNTP_INTERNAL_GPS_ADDRESS "127.127.28.1" /* Deprecated with CNI-4779 */
#define AASNTP_BACKPLANE_ADDRESS "127.127.28.2"
#define AASNTP_EXTERNAL_GPS_ADDRESS "127.127.28.3"
#define AASNTP_TOP_ADDRESS "127.127.28.4"
#define AASNTP_CPRI_ADDRESS "127.127.28.5"
#define AASNTP_DSCP_NOT_CONFIGURED 0xFF

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** @brief AaSNTP return values. */
typedef enum EAaSNTPRet {
    EAaSNTPRet_Ok                = 0,  /**< Ok. */
    EAaSNTPRet_ExecutableNotFound,     /**< Client executable not found. */
    EAaSNTPRet_TaskError,              /**< Problem creating client EU. */
    EAaSNTPRet_InvalidParameter,       /**< Invalid parameter. */
    EAaSNTPRet_NotConfigured,          /**< Client not configured */
    EAaSNTPRet_AlreadyRunning,         /**< Client already running */
    EAaSNTPRet_NotRunning,             /**< Client not running. */
    EAaSNTPRet_NotSupported,           /**< Api not supported. */
    EAaSNTPRet_NtpqError,              /**< Ntpq exec error */
    EAaSNTPRet_NtpdError,              /**< Ntpd exec error */
    EAaSNTPRet_PeerNotSynced,          /**< No synced peers */
    EAaSNTPRet_PeerStatusError,        /**< Error getting peer status */
    EAaSNTPRet_NotInitialized,         /**< The appropriate service level is not initialized */
    EAaSNTPRet_NbrOf                   /**< Always the last one. */
} EAaSNTPRet;

/** @brief AaSNTP runtime status values. */
typedef enum EAaSNTPStatus {
    EAaSNTPStatus_NotConfigured          = 0, /**< Client has never been configures. */
    EAaSNTPStatus_Configured,                 /**< Client has been configured. */
    EAaSNTPStatus_Running,                    /**< Client has is running */
    EAaSNTPStatus_StopPending,                /**< Client is being shutdown.  */
    EAaSNTPStatus_Stopped,                    /**< Client has been stopped. */
    EAaSNTPStatus_StartPending,               /**< Client has been started but its not configured yet (rel3 only) */
    EAaSNTPStatus_NotSupported,               /**< Api not supported */
    EAaSNTPStatus_NbrOf                       /**< Always the last one. */
} EAaSNTPStatus;

/** @brief AaSNTP connection status values. */
typedef enum EAaSNTPConnectionStatus {
    EAaSNTPConnectionStatus_NeverConnected,      /**< Client has never connected to server. */
    EAaSNTPConnectionStatus_Connected,           /**< Client has connected to server. */
    EAaSNTPConnectionStatus_NotSupported,        /**< Api not supported */
    EAaSNTPConnectionStatus_NbrOf                /**< Always the last one. */
} EAaSNTPConnectionStatus;

/** @brief AaSNTP status values.
 * part of SAaSNTPStates structure which desribes status of time source */
typedef enum EAaSNTPState
{
    EAaSNTPState_Unknown = 0,     /**< initial default value */
    EAaSNTPState_InSync,         /**< for NTPd selected source Ok */
    EAaSNTPState_Ok,             /**< for accessible NTP source */
    EAaSNTPState_NotOk           /**< for not available NTP source */
} EAaSNTPState;

/** @brief AaSNTP shm based time sources.
 * @warning enum is deprecated
 * input values for AaSNTPGetSyncSourceAddress */
typedef enum EAaSNTPSyncSource
{
    EAaSNTPSyncSource_GNSS = 0, /**< GPS sync source.     */
    EAaSNTPSyncSource_TOP,      /**< TOP sync source. (127.127.28.4)    */
    EAaSNTPSyncSource_CPRI,     /**< CPRI sync source. (127.127.28.5)   */
    EAaSNTPSyncSource_INT_GPS,      /**< Internal GPS sync source. (127.127.28.1)    */
    EAaSNTPSyncSource_BACKPLANE,    /**< Backplane sync source. (127.127.28.2)    */
    EAaSNTPSyncSource_EXT_GPS,      /**< External GPS sync source. (127.127.28.3)    */
    EAaSNTPSyncSource_NbrOf     /**< Always the last one. */
} EAaSNTPSyncSource
CCS_DEPRECATED("Deprecated with CNI-4779");


/** @brief AaSNTP Peer status data */
typedef struct SAaSNTPPeerStatus
{
    TBoolean inSync;                   /**< GLO_TRUE if in sync with ntp server(peer) / GLO_FALSE if out of sync */
    TBoolean accessible;               /**< GLO_TRUE if ntp server is accessible / GLO_FALSE if not accesible */
    char ipAddress[AASNTP_STR_LEN];    /**< ip address of ntp server(peer) */
} SAaSNTPPeerStatus;

/** AaSNTP status data */
typedef struct SAaSNTPStatus
{
    TBoolean ntpNotInUse;                                       /**< GLO_TRUE if GPS is in use as time sync source / GLO_FALSE if it's not */
    u32 numOfPeers;                                             /**< number of ntp servers(peers) */
    SAaSNTPPeerStatus peerStatus[AASNTP_NUM_OF_SERVERS];        /**< array of peer status data */

} SAaSNTPStatus;

/** AaSNTP result data */
typedef struct SAaSNTPResult
{
    u32 result;                         /**< result */
} SAaSNTPResult;

/** AaSNTP configuration data */
typedef struct SAaSNTPConfig
{
    char pathIPAddress[AASNTP_IP_ADDRESS_LENGTH];                                       /**< path IP address - force to use by ntpd specified interface with pathIpAddress address.
                                                                                             In result src address in ntp packets send by ntpd as requests to the ntp server is address specified by pathIPAddress.
                                                                                             Ntpd will also only listen on pathIPAddress address*/
    u32 pathDscp;                                                                       /**< Differentiated Services Code Point value*/
    u32 maxDist;                                                                        /**< threshold of rootDistance (in nanoseconds) - setting for sanity checks algorithm in ntp protocol.
                                                                                             Bellow threshold - devault value is 1.5s - ntpd refuses to synchronize to time source.
                                                                                             Option is used to enforce a distance error on ntpd
                                                                                             on different level than default - 1.5s. When passed 0 no optimization from AaSNTP side will be performed,
                                                                                             and default behaviour applied - distance error on 1.5s level.*/
    u32 numOfExternalNtpServers;                                                        /**< number of external servers used in configuration*/
    char arrayOfExternalNtpServers[AASNTP_NUM_OF_SERVERS][AASNTP_IP_ADDRESS_LENGTH];    /**< array of servers IP passed in configuration*/
    char fsmInternalNtpIPAddress[AASNTP_IP_ADDRESS_LENGTH];                                   /**< ntp interface listen IP address*/
    TBoolean noselectMode;                                                              /**< if noselectMode is GLO_TRUE then noselect parameter will be passed to servers configuration */
} SAaSNTPConfig;

/**  AaSNTP server state data */
typedef struct SAaSNTPState
{
    char ipAddress[AASNTP_IP_ADDRESS_LENGTH];       /**< IP address of source */
    EAaSNTPState state;                             /**< state of connection to source (check EAaSNTPState description above)*/
    u32 stratum;                                    /**< stratum value of the server delivered by ntp protocol*/
    i64 offset;                                     /**< offset value calculated by ntpd based on ntp protocol - difference between client OS time and serwer time (nanoseconds)*/
    u64 rootDelay;                                  /**< rootDelay value calculated by ntpd based on ntp protocol (nanoseconds)*/
    u64 rootDispersion;                             /**< rootDispersion value of the server delivered by ntp protocol (nanoseconds)*/
    u64 rootDistance;                               /**< rootDistance calculated internally by AaSNTP (nanoseconds)*/
} SAaSNTPState;

/** AaSNTP servers state data */
typedef struct SAaSNTPStates
{
    u32 numOfExtNtpServers;                         /**< number of servers used */
    SAaSNTPState ntpStates[AASNTP_NUM_OF_SERVERS];  /**< structure consists of state of connection and IP (check SAaSNTPState description above)*/
    u32 stratum;                                    /**< stratum value of the client calculated by ntpd based on ntp protocol*/
    i64 offset;                                     /**< offset combined value calculated by ntpd based on ntp protocol */
    u64 rootDelay;                                  /**< rootDelay combined value calculated by ntpd based on ntp protocol (nanoseconds)*/
    u64 rootDispersion;                             /**< rootDispersion combined value calculated by ntpd based on ntp protocol (nanoseconds)*/
} SAaSNTPStates;
/*@}*/

#ifdef __cplusplus
}
#endif


#endif /* _MCU_IFAASNTP_H */
