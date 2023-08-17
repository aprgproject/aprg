/** @file
*   @brief AaTestPortServer MCU Interface.
*
*   $Copyright: 2018, 2019 Nokia. All rights reserved.$
*/

#ifndef _MCU_IFAATESTPORTSERVER_H
#define _MCU_IFAATESTPORTSERVER_H

#include "CcsCommon.h"
#include <IfAaTestPortServer_Defs.h>
#include <IfAaTestPortServer_Msgs.h>
#include <../Definitions/IfAaSysCom_Defs.h>

#ifdef __cplusplus
extern "C"{
#endif

/************************** DOXYGEN GROUPS ************************************/

/**
* @defgroup dgAaTestPortServerMcu AaTestPortServer Functions (MCU)
* @ingroup dgAaTestPortServer
*/
/**@{*/

/**
*******************************************************************************
*
*   @brief      Function to create an AaTestPortServer process.
*
*   @param[in]  name                 Name of AaTestPortServer,
*                                    restricted to #AATESTPORTSERVER_MAX_NAME_LENGTH characters.
*   @param[in]  port                 TCP port to listen for incoming connection requests.
*                                    Port 0 is treated as invalid parameter.
*   @param[in]  cpid                 SysCom communication point identifier of the server process.
*                                    If \c AASYSCOM_CP_INVALID is passed, then dynamic cpid is
*                                    registered.
*   @param[in]  bufferSize           Size of AaTestPortServer internal message buffer in bytes.
*                                    Restricted to #AATESTPORTSERVER_MIN_BUFFER_SIZE and
*                                    #AATESTPORTSERVER_MAX_BUFFER_SIZE.
*                                    If 0 then #AATESTPORTSERVER_MIN_BUFFER_SIZE is used
*   @param[in]  ipAddress            Server binds to this IP. If \c GLO_NULL then any address "::"
*                                    is used. IPv6 address should be passed. Argument \p ipAddress
*                                    is passed to \c inet_pton() as the "src" argument of the
*                                    \c inet_pton() function, hence please see \c inet_pton() manual
*                                    http://man7.org/linux/man-pages/man3/inet_pton.3.html
*                                    for possible \p ipAddress formats for IPv6 (\c AF_INET6
*                                    section).
*
*   @return     #EAaTPServerRetVal_Ok if the function was executed successfully otherwise see
*               Errors description.
*
*   @par Description:
*   - This Function creates a tester port server process which is used as a kind of SysCom/TCP and
*     TCP/SysCom gateway to exchange data between system module threads and external applications
*     like BtsLog, PySCT.
*   - If a connection between the AaTestPortServer process and a TCP client is established then
*     SysCom messages coming to the AaTestPortServer process will be forwarded to the client and
*     vice versa.
*   - If the connection between the AaTestPortServer process and the client is not established then
*     SysCom messages coming to the server are dropped.
*   - Server port passed in \p port argument is bound to IPv6 address.
*   - The process name of AaTestPortServer is a null-terminated string consisting of max 16 chars,
*     9 first chars of \p name argument then '_' char, then 5 chars of \p port argument and
*     NULL char '\0' at the end. Note that AaTestPortServer name specified by \p name argument and
*     process name of AaTestPortServer are 2 different variables. Argument \p name is seen in logs
*     printed by AaTestPortServer. Process name of AaTestPortServer is set using PR_SET_NAME macro
*     and is limited by system to 16 chars. Process name of AaTestPortServer is used to identify
*     appropriate server to be closed by AaTestPortServerDelete() function.
*   - The internal message buffer size can be set via config tag
*     #AATESTPORTSERVER_CONFIG_TAG_BUFFER_SIZE, however the config tag is ignored if \p bufferSize
*     is other than 0 or if #ERadCcsMcu_AaTestPortServerBipBufferSize is set to non-default value.
*   - TCP send buffer size is set to 512kB (note this size is doubled by system), it can be changed
*     by #ERadCcsMcu_AaTestPortServerTcpSocketWriteBufferSize 0x1003D flag (kB = 1024B).
*   - TCP receive buffer size is set to 64kB (note this size is doubled by system), it can be
*     changed by #ERadCcsMcu_AaTestPortServerTcpSocketReadBufferSize 0x1003E flag (kB = 1024B).
*   - Note: If data, sent to the server via SysCom in a short time, exceeds the internal message
*     buffer size some messages may be dropped.
*   - If execution of AaTestPortServer binary fails or if AaTestPortServer fails/crashes after being
*     executed then the node status is set to NOK for non-critical application.
*   - The IP address can be set via config tag #AATESTPORTSERVER_CONFIG_TAG_IP_ADDRESS, however the
*     config tag is ignored if \p ipAddress is other than \c GLO_NULL or other than any "::".
*   - If link-local IP address is passed as \p ipAddress (or by the config tag
*     #AATESTPORTSERVER_CONFIG_TAG_IP_ADDRESS) then the scope id for the address is set in
*     following way: Get the list of all IP addresses available on the machine (using
*     \c getifaddrs() function). Search for address in the list, that is the same as the one passed
*     in \p ipAddress. Set scope id for \p ipAddress the same as scope id of the corresponding
*     address from the list.
*
*   @par Errors:
*   EAaTPServerRetVal_Error            is returned in case of some internal error and error is
*                                      printed in logs.
*   EAaTPServerRetVal_InvalidParameter is returned if invalid parameter is given and error is
*                                      printed in logs.
*
*   @par Restrictions:
*    - Only one client connection per server is allowed.
*    - In case the input data rate via SysCom is too high, internal AaTestPortServer buffer gets
*      full and the messages can be lost.
*    - The function is asynchronous and will return before actual AaTestPortServer binary is
*      executed. This is to avoid the applications from blocking on AaTestPortServerCreate().
*    - Server sends data via TCP every 1ms (providing there are data to send in the internal message
*      buffer). Additionally server sends at max 128kB (kB = 1024B) at one send operation. This
*      means that the ideal (with infinity CPU speed and availability) maximum throughput of the
*      server is 128 Megabytes per second.
*    - There should be no 2 AaTestPortServers with the same \p name and \p port arguments, running
*      within the same CE as then, calling AaTestPortServerDelete() for one of them will close both
*      of them. This means that creating 2 servers with the same \p name is allowed, providing that
*      their \p port arguments are different.
*
*   @par Example:
*   Following example shows basic usage.
*   @code
        #include <IfAaTestPortServer.h>

        void ExampleFunction(void)
        {
            u16 serverPort = 1234;
            TAaSysComCpid cpid = 2222;
            u32 bufferSize = 0; // Default size #AATESTPORTSERVER_MIN_BUFFER_SIZE is used
            const char* ipAddress = GLO_NULL; // Any address "::" is used

            EAaTPServerRetVal retVal = AaTestPortServerCreate( "AaTestPortServer1",
                                                               serverPort,
                                                               cpid,
                                                               bufferSize,
                                                               ipAddress );
            if( EAaTPServerRetVal_Ok != retVal )
            {
                // Error
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
EAaTPServerRetVal AaTestPortServerCreate( const char*   name,
                                          u16           port,
                                          TAaSysComCpid cpid,
                                          u32           bufferSize,
                                          const char*   ipAddress );

/**
*******************************************************************************
*
*   @brief      Function to create an AaTestPortServer process with Tassu parser instead of SysCom
*               parser.
*
*   @par Description:
*   - This Function creates a tester port server process which is used as a kind of Tassu/TCP and
*     TCP/Tassu gateway to exchange data between system module threads and external applications
*     like BtsLog, PySCT.
*   - This function behaves the same as AaTestPortServerCreate() with the
*     exception that Tassu messages are handled instead of SysCom messages.
*
*******************************************************************************/
EAaTPServerRetVal AaTestPortServerCreateTassu( const char*   name,
                                               u16           port,
                                               TAaSysComCpid cpid,
                                               u32           bufferSize,
                                               const char*   ipAddress );

/**
*******************************************************************************
*
*   @brief      Function to delete AaTestPortServer process
*
*   @param[in]  serverName    Name of the server to be deleted,
*                             restricted to #AATESTPORTSERVER_MAX_NAME_LENGTH characters.
*   @param[in]  port          Server port number. Port 0 is treated as invalid parameter.
*
*   @return #EAaTPServerRetVal_Ok when server is deleted successfully otherwise refer to Errors
*           description
*
*   @par Description:
*   Calling this function will make the server process specified by passed parameters to stop
*   listening for new connection requests and to close the existing connection.
*   After the connection is closed, the server process will cleanup the resources and the process
*   will end.
*
*   @par Errors:
*   EAaTPServerRetVal_Error            is returned in case of some internal error and error is
*                                      printed in logs.
*   EAaTPServerRetVal_InvalidParameter is returned if invalid parameter is given and error is
*                                      printed in logs.
*
*   @par Restrictions:
*   - The function is asynchronous and will return before the background cleanup and deletion are
*   completed. This is to avoid the applications from blocking on AaTestPortServerDelete(). The
*   actual cleanup and deletion of the server process take some time. So in case the server is
*   deleted and new one is created with the same \p port in quick succession, it is possible that
*   the new server creation might fail due to the specified \p port being not free. In such
*   a scenario, it is advised to use a different unused port for creating a new server.
*
*   @par Example:
*
*   @code
        #include <IfAaTestPortServer.h>

        void ExampleFunction(void)
        {
            if( EAaTPServerRetVal_Ok != AaTestPortServerDelete("AaTestPortServer1", 12345) )
            {
                // Error
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
EAaTPServerRetVal AaTestPortServerDelete(const char* serverName, u16 port);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* _MCU_IFAATESTPORTSERVER_H */
