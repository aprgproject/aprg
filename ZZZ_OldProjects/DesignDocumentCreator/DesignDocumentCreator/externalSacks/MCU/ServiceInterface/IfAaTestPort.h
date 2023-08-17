/**
*******************************************************************************
* @file
* $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaTestPort MCU Interface.
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/
#ifndef _MCU_IFAATESTPORT_H
#define _MCU_IFAATESTPORT_H
#include "CcsCommon.h"
#include <IfAaTestPort_Defs.h>
#ifdef CCS_NEW_IF_STRUCTURE
#include <../../SHARED/MCU_RT/ServiceInterface/IfAaTestPort.h>
#include <IfAaSysComGw_Defs.h>
#endif
#include <IfAaTestPort_Msgs.h>

#ifdef __cplusplus
extern "C"{
#endif
/************************** DOXYGEN GROUPS ************************************/

/**
* @defgroup dgAaTestPortMcu AaTestPort Functions (MCU)
* @ingroup dgAaTestPort
*/
/**@{*/


/**
*******************************************************************************
*
*   @brief      Function to create an AaTestPort client instance.
*
*   @param[in]  namePtr     Name of AaTestPort client, the name should be unique per CE and
*                           restricted to #AATESTPORT_CLIENT_MAX_NAME_LENGTH characters.
*   @param[out] cpid        SysCom communication point identifier.
*   @param[in]  ipVersion   Ip version.
*   @param[in]  localPort   Local TCP port.
*   @param[in]  localIp     Local IP address string. Must fulfill requirements from inet_pton linux function.
*   @param[in]  remotePort  Remote TCP port.
*   @param[in]  remoteIp    Remote server IP address string. Must fulfill requirements from inet_pton linux function.
*   @param[in]  managerAddr SicAddress to send notifications about the connection
*                           status. If not needed, use #AASYSCOM_CP_INVALID.
*                           The Syscom message is holding a #SAaTestPortClientExtInd struct.
*
*   @return    Indicates if the function was executed successfully.
*
*
*   @par Description:
*   This function creates an AaTestport client instance for connections based on ipv4 or ipv6.
*   The AaTestPort client forwards Syscom messages via Tcp connection to the connected remote server.
*   The AaTestPort client uses an internal memory buffer for incoming syscom messages,
*   buffer size is set via the config tag #AATESTPORT_CONFIG_TAG_BUFFER_SIZE.
*   Note: localIp and remoteIp have to be in the same ip version.
*
*   @par Errors:
*   EAaTestPortRetVal_Error                 Some internal error
*   EAaTestPortRetVal_InvalidParameter      Invalid parameter is given
*   EAaTestPortRetVal_ResourceNotAvailable  Service is not initialized or too many instances created.
*
*   @par Restrictions:
*   The number of the AaTestPort client instances is limited to #AATESTPORT_MAX_TCP_CLIENT per EE.
*   In case the input data rate is too high and AaTestPort buffer gets full,the messages can be lost.
*
*   @par Example:
*   Following example shows basic usage for IPv6.
*   (For Ipv4, the version is EAaSysComGwIpVer_4 and remote
*   and local ip address string is in ipv4 format e.g. "127.0.0.1")
*   @code
        #include <IfAaTestPort.h>

         void ExampleFunction(void)
         {
             EAaTestPortRetVal retVal = EAaTestPortRetVal_Ok;
             const char* clientName = "AaTestPortClient_Name";
             TAaSysComCpid cpid = AASYSCOM_CP_INVALID;
             const char* localIpVer6 = "::1";
             const char* remoteIpVer6 = "FE80:0000:0000:0000:0202:B3FF:FE1E:8329";
             retVal = AaTestPortCreateTraceTcpClientExt( clientName,
                                                         &cpid,
                                                         EAaSysComGwIpVer_6,
                                                         localPort,
                                                         localIpVer6,
                                                         remotePort,
                                                         remoteIpVer6,
                                                         AASYSCOM_CP_INVALID);
             if( EAaTestPortRetVal_Ok != retVal )
             {
                 if( EAaTestPortRetVal_Ok != AaTestPortTraceClientStartExt(clientName) )
                 {
                     // return error;
                 }
             }
             else
             {
                 // return error;
             }
         }
    @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*
*******************************************************************************/
EAaTestPortRetVal AaTestPortCreateTraceTcpClientExt( const char*      namePtr,
                                                     TAaSysComCpid*   cpid,
                                                     EAaSysComGwIpVer ipVersion,
                                                     u32              localPort,
                                                     const char*      localIp,
                                                     u32              remotePort,
                                                     const char*      remoteIp,
                                                     TAaSysComSicad   managerAddr);

/**
*******************************************************************************
*
*   @brief      Function to start an AaTestPort client instance.
*
*   @param[in]  clientName    AaTestPort client name.
*
*   @return    Indicates if the function was executed successfully.
*
*
*   @par Description:
*   Sets AaTestPort client instance as active it makes the AaTestPort is started
*   sending the connection statuses.
*
*   @par Errors:
*   EAaTestPortRetVal_Error                 Some internal error
*   EAaTestPortRetVal_InvalidParameter      Invalid parameter is given
*   EAaTestPortRetVal_ResourceNotAvailable  Service is not initialized or too many instances created.
*
*   @par Restrictions:
*   None
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaTestPortCreateTraceTcpClientExt().
*
*******************************************************************************/
EAaTestPortRetVal AaTestPortStartTraceTcpClientExt(const char* clientName);

/**
*******************************************************************************
*
*   @brief      Function to halt an AaTestPort client instance.
*
*   @param[in]  clientName    AaTestPort client name.
*
*   @return    Indicates if the function was executed successfully.
*
*
*   @par Description:
*   This function will put the AaTestPort client instance on halt, shutting down
*   the opened socket. Other than with AaTestPortDeleteTraceTcpClientExt(), communication can be
*   reestablished by calling the function AaTestPortStartTraceTcpClientExt().
*
*   @par Errors:
*   EAaTestPortRetVal_Error                 Some internal error
*   EAaTestPortRetVal_InvalidParameter      Invalid parameter is given
*   EAaTestPortRetVal_ResourceNotAvailable  Service is not initialized or too many instances created.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   Following example shows basic usage. See AaTestPortCreateTraceTcpClientExt()
*   for information on how to create an instance.
*   @code
        #include <IfAaTestPort.h>

         void ExampleFunction(const char* clientName)
         {
             AaTestPortHaltTraceTcpClientExt(clientName);
             // Do something
             AaTestPortStartTraceTcpClientExt(clientName);
         }
    @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*
*******************************************************************************/
EAaTestPortRetVal AaTestPortHaltTraceTcpClientExt(const char* clientName);


/**
*******************************************************************************
*
*   @brief      Function to delete an AaTestPort client instance.
*
*   @param[in]  clientName    AaTestPort client name.
*
*   @return Indicates if the function was executed successfully.
*
*
*   @par Description:
*   Calling this function will make existing connection to close.
*   After the connection is closed, the socket will be closed and this
*   AaTestPort client instance number is given back to the pool of free client instances.
*
*   @par Errors:
*   EAaTestPortRetVal_Error                 Some internal error
*   EAaTestPortRetVal_InvalidParameter      Invalid parameter is given
*
*   @par Restrictions:
*   The function is asynchronous and will return before the background cleanup and deletions are complete.
*   This is to avoid the applications from blocking on AaTestPortDelete. The actual cleanup and deletion of instances
*   takes some time. So in case the instances are deleted and created with the same name in quick succession, it is
*   possible that instance creation might fail. In such a scenario, it is advised to use a different unused name for
*   creating a new instance.
*
*   @par Example:
*   Following example shows basic usage.
*   AaTestPortCreateTraceTcpClientExt() for information on how to create an instance.
*   @code
        #include <IfAaTestPort.h>

         void ExampleFunction(const char* clientName)
         {
             AaTestPortDeleteTraceTcpClientExt(clientName);
         }
    @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*
*******************************************************************************/
EAaTestPortRetVal AaTestPortDeleteTraceTcpClientExt(const char* clientName);

/**
*******************************************************************************
*
*   @brief      Function to create AaTestPort client instance with Socket options.
*
*   @param[in]  namePtr     Name of AaTestPort client, the name should be unique per CE and
*                           restricted to #AATESTPORT_CLIENT_MAX_NAME_LENGTH characters.
*   @param[out] cpid        SysCom communication point identifier.
*   @param[in]  ipVersion   Ip version.
*   @param[in]  localPort   Local TCP port.
*   @param[in]  localIp     Local IP address string. Must fulfill requirements from inet_pton linux function.
*   @param[in]  remotePort  Remote TCP port.
*   @param[in]  remoteIp    Remote server IP address string. Must fulfill requirements from inet_pton linux function.
*   @param[in]  managerAddr SicAddress to send notifications about the connection
*                           status. If not needed, use #AASYSCOM_CP_INVALID.
*                           The Syscom message is holding a #SAaTestPortClientExtInd struct.
*   @param[in]  options     Structure AaTestPortClientSocketOptions containing the socket options
*                           that can be set for AaTestPort client.
*
*   @return    Indicates if the function was executed successfully. EAaTestPortRetVal_Ok in case of success.
*
*
*   @par Description:
*   This function creates an AaTestport client instance for connections based on ipv4 or ipv6 with the possibility
*   to set socket options while socket creation.
*   AaTestPortClientSockOptsInit should be called before calling this API to initialize the socket options.
*   In case socket options are required to be set then the value of the particular option can be set by the user
    as required after the call to AaTestPortClientSockOptsInit.
*   The AaTestPort client forwards Syscom messages via Tcp connection to the connected remote server.
*   The AaTestPort client uses an internal memory buffer for incoming syscom messages,
*   buffer size is set via the config tag #AATESTPORT_CONFIG_TAG_BUFFER_SIZE.
*   Note: localIp and remoteIp have to be in the same ip version.
*
*   @par Errors:
*   EAaTestPortRetVal_Error                 Some internal error
*   EAaTestPortRetVal_InvalidParameter      Invalid parameter is given
*   EAaTestPortRetVal_ResourceNotAvailable  Service is not initialized or too many instances created.
*
*   @par Restrictions:
*   The number of the AaTestPort client instances is limited to #AATESTPORT_MAX_TCP_CLIENT per EE.
*   In case the input data rate is too high and AaTestPort buffer gets full,the messages can be lost.
*   AaTestPortClientSockOptsInit should be called before calling this API.
*
*
*   @par Example:
*   Following example shows basic usage for IPv6.
*   (For Ipv4, the version is EAaSysComGwIpVer_4 and remote
*   and local ip address string is in ipv4 format e.g. "127.0.0.1")
*   @code
        #include <IfAaTestPort.h>

         void ExampleFunction(void)
         {
             EAaTestPortRetVal retVal = EAaTestPortRetVal_Ok;
             const char* clientName = "AaTestPortClient_Name";
             TAaSysComCpid cpid = AASYSCOM_CP_INVALID;
             const char* localIpVer6 = "::1";
             const char* remoteIpVer6 = "FE80:0000:0000:0000:0202:B3FF:FE1E:8329";
             AaTestPortClientSocketOptions option;
             AaTestPortClientSockOptsInit(&option);   //  option maxSegmentSize is first initialized to 0 (not set value)
             option.maxSegmentSize = 1400;            // option initialized to desired value.
             retVal = AaTestPortClientCreate( clientName,
                                              &cpid,
                                              EAaSysComGwIpVer_6,
                                              localPort,
                                              localIpVer6,
                                              remotePort,
                                              remoteIpVer6,
                                              AASYSCOM_CP_INVALID,
                                              option);
             if( EAaTestPortRetVal_Ok == retVal )
             {
                 if( EAaTestPortRetVal_Ok != AaTestPortTraceClientStartExt(clientName) )
                 {
                     // return error;
                 }
             }
             else
             {
                 // return error;
             }
         }
    @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*
*******************************************************************************/
EAaTestPortRetVal AaTestPortClientCreate( const char*      namePtr,
                                          TAaSysComCpid*   cpid,
                                          EAaSysComGwIpVer ipVersion,
                                          u32              localPort,
                                          const char*      localIp,
                                          u32              remotePort,
                                          const char*      remoteIp,
                                          TAaSysComSicad   managerAddr,
                                          AaTestPortClientSocketOptions options);

/**
*******************************************************************************
*
*   @brief      Function to initialize socket options for AaTestPort client
*
*   @param[in]  options     Pointer to structure AaTestPortClientSocketOptions containing the socket options
*                           that can be set for AaTestPort client.
*   @param[out] options     Pointer to structure AaTestPortClientSocketOptions with socket options initialized
*                           to values indicating the option as not set.
*
*   @par Description:
*   This function is used to initialize the socket options that can be set for AaTestPort client socket
*   It is mandatory for the user to call this API before calling AaTestPortClientCreate.
*   The function initializes the value of the socket options to indicate that option is not set.
*   So if user wants to set the socket option, the value of the socket option must be set after
*   the call to this API.
*
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*   It is mandatory for the user to call this function before calling AaTestPortClientCreate
*
*   @par Example:
*   Following example shows basic usage.
*
*   AaTestPortClientCreate() for information on how to create an instance.
*   @code
        #include <IfAaTestPort.h>

         void ExampleFunction(void)
         {
             AaTestPortClientSocketOptions options;
             AaTestPortClientSockOptsInit(&options);
         }
    @endcode
*
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*
*******************************************************************************/
void AaTestPortClientSockOptsInit(AaTestPortClientSocketOptions *options);



/**@}*/

#ifdef __cplusplus
}
#endif
#endif /* _MCU_IFAATESTPORT_H */
