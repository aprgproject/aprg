/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/
#ifndef _MCU_IFAASNTP_H
#define _MCU_IFAASNTP_H
#include <CcsCommon.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <IfAaSNTP_Defs.h>
#include <IfAaSNTP_Msg.h>
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/** @defgroup dgAaSNTP SNTP Service 
* @ingroup dgBasicComputingSw
*
* Common Computer and Support SW SNTP Service.
*
* AaSNTP in CC&S Wiki: http://wikis.inside.nokiasiemensnetworks.com/bin/view/CSSWiki/AaSNTP
*
*/

/** @defgroup dgAaSNTPApiMcu AaSNTP MCU API 
* @ingroup dgAaSNTP
*
*/
/*@{*/



/*----------------------- INCLUDED FILES -------------------------------------*/

#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PUBLIC INTERFACES ----------------------------------*/

void AaSNTPCeInit(void) CCS_DEPRECATED("Deprecated with PS-1593 - should be not used outside CCS");
void AaSNTPEeInit(void) CCS_DEPRECATED("Deprecated with PS-1593 - should be not used outside CCS");

/**
********************************************************************************
*
* @brief        AaSNTPConfigure stores configuration of SNTP.
*
* @param[in]    ipAddress    IP Address of NTP server.
*
* @return       Function returns success of operation.
*
* @par Description:
* Stores configuration which will be used when NTP Client is started.
*
* @par Errors:
*   Returns #EAaSNTPRet_InvalidParameter if ipAddress is invalid.\n
*   Returns #EAaSNTPRet_AlreadyRunning if client is already started.\n
*   Returns #EAaSNTPRet_NotSupported returned always (function deprecated) except FSMr2 in non BASE mode\n
*
* @par Restrictions:
*   Does not change behaviour of client if it is already running.\n
*   AaSNTP API calls can only be used by one EE per CE.\n
*   Function is accessible on FSMr2 in non BASE mode, on LRC and on FZM.\n
*   Function should not be used.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
*
* @par Example:
*
* @code
*   char *ipAddress = "172.16.0.10";
*   ret = AaSNTPConfigure(ipAddress);
* @endcode
*
*******************************************************************************/
EAaSNTPRet AaSNTPConfigure(const char *ipAddress);


/**
********************************************************************************
*
* @brief        AaSNTPStart starts previously configure SNTP
*
* @param[in]    flags      Flags controlling startup.
*
* @return       Function returns success of operation.
*
* @par Description:
* Function start SNTP client.\n
* Flags may be extended to control behaviour of daemon.\n
* Valid flags are AASNTP_FLAGS_NONE, AASNTP_FLAGS_ONESHOT, AASNT_FLAGS_NOSET.\n
* The oneshot flag causes the client to synch the time once with ther server then exit.\n
* The noset flag can be used on test systems without root access. The clock_settime call will not be called.
*
* @par Errors:
*   Returns #EAaSNTPRet_NotConfigured if client has not been configured.\n
*   Returns #EAaSNTPRet_ExecutableNotFound if client executable is not installed.\n
*   Returns #EAaSNTPRet_AlreadyRunning if client is already running.\n
*   Returns #EAaSNTPRet_TaskError if there was a problem spwawining an EU to run the client.\n
*   Returns #EAaSNTPRet_NotSupported if BASE mode is used.
*
* @par Restrictions:
* AaSNTP API calls can only be used by one EE per CE.\n
* Function is accessible in non BASE mode, on LRC and on FZM.\n
* Function should not be used.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
*
* @see
*
* @par Example:
* @code
*   ret = AaSNTPStart(AASNTP_FLAGS_NONE);
* @endcode
*
*******************************************************************************/
EAaSNTPRet AaSNTPStart(u32 flags);

/**
********************************************************************************
*
* @brief        AaSNTPStop stops previously started SNTP client
*
* @return       Function returns success of operation.
*
* @par Description:
* Function stops SNTP client
* (ntpd for BASE mode and Non BASE mode on FSMr3
* ntpclient for Non BASE mode on FSMr2).\n
* Function waits for stopping client then return.\n
*
* @par Errors:
*   Returns #EAaSNTPRet_NotRunning if client is not running.\n
*   Returns #EAaSNTPRet_ExecutableNotFound if the process can not be stopped.\n
*   Returns #EAaSNTPRet_TaskError if the process can not be stopped.\n
*
* @par Restrictions:
* AaSNTP API calls can only be used by one EE per CE.\n
* If BASE mode is used there are no restrictions, function can be called from any EE.\n
* Function should not be used in non BASE configuration, except LRC and FZM.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
*
* @par Example:
* @code
*   ret = AaSNTPStop();
* @endcode
*
*******************************************************************************/
EAaSNTPRet AaSNTPStop(void);

/**
********************************************************************************
*
* @brief        AaSNTPStatus queries the status of the NTP client.
*
* @return
* Function returns status of SNTP client\n
*   Returns #EAaSNTPStatus_NotConfigured  if client was never started.\n
*   Returns #EAaSNTPStatus_Running        if client is a running.\n
*   Returns #EAaSNTPStatus_StopPending    if client is being shutdown.\n
*   Returns #EAaSNTPStatus_Stopped        if client is now stopped.\n
*
* @par Errors:
*         Returns #EAaSNTPRet_NotSupported for BASE mode.
*
* @par Restrictions:
* AaSNTP API calls can only be used by one EE per CE.\n
* Function is accessible in non BASE mode, on LRC and on FZM.\n
* Function should not be used.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
*
* @par Example:
* @code
*   EAaSNTPStatus ret;
*   ret = AaSNTPStatus();
* @endcode
*
*******************************************************************************/
EAaSNTPStatus AaSNTPStatus(void);

/**
********************************************************************************
*
* @brief        AaSNTPConnectionStatus queries the if NTP client has connected to server.
*
* @return
* Function returns conncted status of SNTP client\n
*   Returns #EAaSNTPConnectionStatus_NeverConnected  if client was never connected to server.\n
*   Returns #EAaSNTPConnectionStatus_Connected       if client is connected to server.\n
*
* @par Errors:
* None.
*
* @par Restrictions:
* AaSNTP API calls can only be used by one EE per CE.\n
* Function is accessible in non BASE mode, on LRC and on FZM.\n
* Function should not be used.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
*
* @par Example:
* @code
*   EAaSNTPConnectionStatus ret;
*   ret = AaSNTPConnectionStatus();
* @endcode
*
*******************************************************************************/
EAaSNTPConnectionStatus AaSNTPConnectionStatus(void);

/**
********************************************************************************
*
* @brief        AaSNTPConfigureTrswExt is extended version of AaSNTPConfigureTrsw.
*
* @param[in]    mPlaneIPAddress             source IP address to bind.
* @param[in]    dscp                        Differentiated Services Code Point value.
* @param[in]    extPrimaryNTPSrv            IP Address of first NTP server.
* @param[in]    extSecondaryNTPSrv          IP Address of second NTP server.
* @param[in]    extTertiaryNTPSrv           IP Address of third NTP server.
* @param[in]    fsmInternalNtpIPAddress     IP Address for listening on.
*
* @return       Function returns success of operation.
*
* @par Description:
* Stores configuration which will be used when NTP Client is started.
*
* @par Errors:
*   Returns #EAaSNTPRet_InvalidParameter if IP address is invalid.\n
*   Returns #EAaSNTPRet_NotSupported returned always (function deprecated) except FSMr3 in non BASE mode\n
*
* @par Restrictions:
* If function is called and NTP client is running,
* function will restart NTP Client and configure him with the new values.\n
* Function is accessible in non BASE mode (except FSMr2) on FZM.\n
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
*
* @par Example:
*
* @code
*   char* sourceIp = "10.0.2.10";
*   u32   dscp = DSCP_NOT_CONFIGURED;
    char* firstNtpServer = "10.0.2.25";
    char* secondNtpServer = "10.0.2.26";
    char* thirdNtpServer = "10.0.2.27";
    char* fsmInternalNtpIPAddress = "192.168.255.1";
*   ret = AaSNTPConfigureTrswExt(sourceIp, dscp, firstNtpServer, secondNtpServer, thirdNtpServer, fsmInternalNtpIPAddress);
* @endcode
*
*******************************************************************************/
EAaSNTPRet AaSNTPConfigureTrswExt(const char *mPlaneIPAddress, u32 dscp, const char *extPrimaryNTPSrv, const char *extSecondaryNTPSrv, const char *extTertiaryNTPSrv, const char *fsmInternalNtpIPAddress);

/**
********************************************************************************
*
* @brief        AaSNTPConfigureTrsw stores configuration of SNTP. Used by TRSW and in FSMr3 only.
*
* @param[in]    mPlaneIPAddress      source IP address to bind.
* @param[in]    dscp                 Differentiated Services Code Point value.
* @param[in]    extPrimaryNTPSrv     IP Address of first NTP server.
* @param[in]    extSecondaryNTPSrv   IP Address of second NTP server.
* @param[in]    extTertiaryNTPSrv    IP Address of third NTP server.
*
* @return       Function returns success of operation.
*
* @par Description:
* Stores configuration which will be used when NTP Client is started.
*
* @par Errors:
*   Returns #EAaSNTPRet_InvalidParameter if IP address is invalid.\n
*   Returns #EAaSNTPRet_NotSupported returned always (function deprecated) except FSMr3 in non BASE mode\n
*
* @par Restrictions:
* If function is called and NTP client is running,
* function will restart NTP Client and configure him with the new values.\n
* Function is accessible in non BASE mode (except FSMr2), on LRC and on FZM.\n
* Function should not be used.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
*
* @par Example:
*
* @code
*   char* sourceIp = "10.0.2.10";
*   u32   dscp = DSCP_NOT_CONFIGURED;
    char* firstNtpServer = "10.0.2.25";
    char* secondNtpServer = "10.0.2.26";
    char* thirdNtpServer = "10.0.2.27";
*   ret = AaSNTPConfigureTrsw(sourceIp, dscp, firstNtpServer, secondNtpServer, thirdNtpServer);
* @endcode
*
*******************************************************************************/
EAaSNTPRet AaSNTPConfigureTrsw(const char *mPlaneIPAddress, u32 dscp, const char *extPrimaryNTPSrv, const char *extSecondaryNTPSrv, const char *extTertiaryNTPSrv);

/**
********************************************************************************
*
* @brief        AaSNTPGetServerIpAddress returs the IP address of in sync NTP server
*
* @param[out]   serverIpAddress      IP address of in sync NTP server.
*
* @return       Function returns success of operation.
*
* @par Description:
* Returns the ip address of external ntp server, ntp client is in sync with.
*
* @par Errors:
* Returns #EAaSNTPRet_InvalidParameter.\n
*         #EAaSNTPRet_NtpqError.\n
*         #EAaSNTPRet_NotSupported if BASE mode is used.\n
*
* @par Restrictions:
* Function is accessible in non BASE mode (except FSMr2), on LRC and on FZM.\n
* Function should not be used.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
*
* @par Example:
* @code
*   char inSyncNtpServer[50] = "";
*   ret = AaSNTPGetServerIpAddress(inSyncNtpServer);
* @endcode
*
*******************************************************************************/
EAaSNTPRet AaSNTPGetServerIpAddress(char* serverIpAddress);

/**
********************************************************************************
*
* @brief        AaSNTPGetPeersStatus returs the status of NTP servers (peers)
*
* @param[out]   status      ntp server status data.
*
* @return       Function returns success of operation.
*
* @par Description:
* Returns the staus data of external ntp servers.
*
* @par Errors:
* Returns #EAaSNTPRet_InvalidParameter.\n
*         #EAaSNTPRet_NtpqError.\n
*         #EAaSNTPRet_NotSupported if BASE mode is used.\n
*
* @par Restrictions:
* Function is accessible in non BASE (except FSMr2), on LRC and on FZM.\n
* Function should not be used.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
*
* @par Example:
* @code
*   SAaSNTPStatus status;
*   int i;
*   ret = AaSNTPGetPeersStatus(&status);
*   if(EAaSNTPRet_Ok == ret)
*   {
*       // print status data
*       printf("status.gpsInUse = %d", status.gpsInUse);
*       printf("status.numOfPeers = %d", status.numOfPeers);
*       for(i = 0; i < status.numOfPeers; ++i)
*       {
*          printf("status.peerStatus[%d].inSync = %d", i, status.peerStatus[i].inSync);
*          printf("status.peerStatus[%d].accesible = %d", i, status.peerStatus[i].accesible);
*          printf("status.peerStatus[%d].ipAddress = %s", i, status.peerStatus[i].ipAddress);
*       }
*
*   }
*
* @endcode
*
*******************************************************************************/
EAaSNTPRet AaSNTPGetPeersStatus(SAaSNTPStatus* status);

/**
********************************************************************************
*
* @brief        AaSNTPConfigureAndStart configures and starts AaSNTP
*
* @param[in]    config      configuration data
*
* @return       Function returns success of operation.
*
* @par Description:
* Function configures and starts SNTP client - ntpd daemon.\n
* Function doesn't wait for ntpd startup or setting os time.
*
*
* @par Errors:
*   Returns #EAaSNTPRet_ExecutableNotFound if client executable is not installed.\n
*   Returns #EAaSNTPRet_TaskError if there was a problem spawning an EU to run the client.\n
*   Returns #EAaSNTPRet_NotSupported if non BASE mode is used.
*
* @par Restrictions:
* This api call can not be used with AaSNTPStart, AaSNTPConfigure, AaSNTPConfigureTrsw, AaSNTPGetPeersStatus.\n
* Function is allowed to use in BASE mode, only.\n
* Function is not supported for LRC and FZM.\n
* BASE mode is default configuration.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
*
* @see
*
* @par Example:
* @code
*   SAaSNTPConfig config;
*   // fill config with relevant data
*   ret = AaSNTPConfigureAndStart(&config);
* @endcode
*
*******************************************************************************/
EAaSNTPRet AaSNTPConfigureAndStart(SAaSNTPConfig* config);

/**
********************************************************************************
*
* @brief        AaSNTPStates returs the status of NTP servers (peers)
*
* @param[out]   states      ntp server status data.
*
* @return       Function returns success of operation.
*
* @par Description:
* Returns the staus data of external ntp servers.
*
* @par Errors:
* Returns #EAaSNTPRet_InvalidParameter.\n
*         #EAaSNTPRet_NtpqError.\n
*         #EAaSNTPRet_NotSupported if non BASE mode is used.
*
* @par Restrictions:
* Used only in combination with AaSNTPConfigureAndStart\n
* Function is not supported for LRC and FZM.\n
* Function is allowed to use in BASE mode, only.\n
* BASE mode is default configuration.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
*
* @par Example:
* @code
*   SAaSNTPStates states;
*   int i;
*   ret = AaSNTPStates(&states);
*   if(EAaSNTPRet_Ok == ret)
*   {
*       // print status data
*       printf("states.numOfExtNtpServers = %d", states.numOfExtNtpServers);
*       for(i = 0; i < states.numOfExtNtpServers; ++i)
*       {
*          printf("states.ntpStates[%d].ipAddress = %s", i, states.ntpStates[i].ipAddress);
*          printf("states.ntpStates[%d].state = %d", i, states.ntpStates[i].state);
*          printf("states.ntpStates[%d].rootDistance = %llu", i, states.ntpStates[i].rootDistance);
*       }
*   }
*
* @endcode
*
*******************************************************************************/
EAaSNTPRet AaSNTPStates (SAaSNTPStates* states);

/**
********************************************************************************
*
* @brief        AaSNTPFsmGetIpAddress returns the IP address of FSM moule
*
* @return       Returns the ip address of FSM (master module)
*
* @par Description:
* None
*
* @par Errors:
*           Returns GLO_NULL if non BASE mode is used.
*
* @par Restrictions:
* Function is not accessible for LRC and FZM.\n
* Function is allowed to use in BASE mode, only.\n
* BASE mode is default configuration.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
*
* @par Example:
* @code
*   char* fsmIpAddress = AaSNTPFsmGetIpAddress();
* @endcode
*
*******************************************************************************/
const char* AaSNTPFsmGetIpAddress(void);

/**
********************************************************************************
*
* @brief        AaSNTPGetBtsInternalServerIpAddress returns the IP address of FSM moule
*
* @return       Returns the ip address of FSM (master module)
*
* @par Description:
* None
*
* @par Errors:
*               Returns GLO_NULL if non BASE mode is used.
*
* @par Restrictions:
* Function is accessible to use in BASE mode, only.\n
* Function is not supported for FZM.\n
* BASE mode is default configuration.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
*
* @par Example:
* @code
*   char* fsmIpAddress = AaSNTPGetBtsInternalServerIpAddress();
* @endcode
*
*******************************************************************************/
const char* AaSNTPGetBtsInternalServerIpAddress(void);

/**
********************************************************************************
*
* @brief        AaSNTPGetSyncSourceAddress returns internal IP address of ntpd shm reference clock driver\n
* @warning function is deprecated
*               (GNSS,0)   -> 127.127.28.1\n
*               (GNSS,1)   -> 127.127.28.3\n
*               (TOP)      -> 127.127.28.4\n
*               (CPRI)     -> 127.127.28.5
*               (INT_GPS)  -> 127.127.28.1\n
*               (BACKPLANE)-> 127.127.28.2\n
*               (EXT_GPS)  -> 127.127.28.3\n
*
* @param[in]   syncSource      GPS, ToP, Cpri or Backplane
* @param[in]   portType        used to identify internal or external GPS (parameter used only if GNSS passed, ignored otherwise)
*
* @return       Returns the internal (used by ntpd) ip address of sync source (internal GPS, external GPS, Backplane, TOP or CPRI)
*
* @par Description:
* This Api is used to retrieve IP address (string format) of internal GPS, external GPS, Backplane, ToP or CPRI sync source.
* ntpd's shm reference clock driver use these addresses to map shared memory segments(NTP1,NTP3,NTP4,NTP5) where gpsd, ToPd or CPRI handler
* write their time data. These api addresses are used during ntpd configuration (creating ntp.conf).
*
* @par Errors:
*               on error GLO_NULL is returned\n
*               Returns GLO_NULL in Non BASE mode.
*
* @par Restrictions:
* portType used only if GNSS passed, ignored for other sources
* Function is accessible to use in BASE mode, only.\n
* Function is not supported for FZM.\n
* BASE mode is default configuration.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
*
* @par Example:
* @code
*   char* internalGpsAddress = AaSNTPGetSyncSourceAddress(EAaSNTPSyncSource_GNSS,0);
* @endcode
*
*******************************************************************************/
const char* AaSNTPGetSyncSourceAddress(EAaSNTPSyncSource syncSource, u32 portType)
CCS_DEPRECATED("Deprecated with CNI-4779");
/*@}*/


#ifdef __cplusplus
}
#endif


#endif /* _MCU_IFAASNTP_H */
