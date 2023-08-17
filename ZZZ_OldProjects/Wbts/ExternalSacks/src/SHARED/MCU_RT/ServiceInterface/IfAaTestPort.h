/**
*******************************************************************************
* @file
* $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaTestPort MCU RT Interface.
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAATESTPORT_H
#define _MCU_RT_IFAATESTPORT_H

/************************** DOXYGEN GROUPS ************************************/

/**
 *  @defgroup dgAaTestPort      Tester Port (AaTestPort)
 *  @ingroup  dgBasicSystemSw
 *
 *  Common Computer and Support SW System Tester Port Service.
 *
 *  @par        Configuring Service
 *
 */

/************************** INCLUDED FILES ************************************/

#include "CcsCommon.h"
#include <glo_def.h>
#include <IfAaSysCom.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include "../Definitions/IfAaTestPort_Defs.h"
#endif

#ifdef __cplusplus
extern "C"{
#endif

/************************** PUBLIC INTERFACES *********************************/

/**
 * @defgroup dgAaTestPortMcuRt AaTestPort Functions (MCU RT)
 * @ingroup  dgAaTestPort
 * Application Programming Interface.
 */

/**@{*/

/**
*******************************************************************************
*
*   @brief      Function to create a TCP tester port server instance.
*
*   @param[in]  name        Name of the tester port server.
*                           Note: AaTestPort server name should be unique per CE.
*   @param[in]  cpid        SysCom communication point identifier.
*   @param[in]  port        TCP port to listen for incoming connection requests.
*   @param[in]  priorityRx  Priority of process which handles RX data.
*   @param[in]  priorityTx  Priority of process which handles TX data.
*
*   @return     Pointer to the TestPort server instance in success, otherwise GLO_NULL.
*
*
*   @par Description:
*   This Function creates a tester port server instance. The tester port server is a kind
*   of Syscom/Tcp gateway to exchange data between system module threads and external
*   applications like BtsLog, PySCT. Syscom messages will be forwarded to Tcp and vice
*   versa, if a connection between the server and a client is established.
*   The internal message buffer can be set via the rad config tag
*   #AATESTPORT_CONFIG_TAG_BUFFER_SIZE.
*   Note: If data, sent in a short time, exceeds the internal message buffer size
*   some messages may be dropped.
*
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*     - The maximum current data throughput of this server is limited by
*       the buffer size.
*     - The buffer size itself is restricted by #AATESTPORT_MAX_BUFFER_SIZE
*       and #AATESTPORT_MIN_BUFFER_SIZE.
*     - The number of server instances is limited to #AATESTPORT_MAX_TCP_PORT.
*     - Only one client connection per server is allowed.
*     - In case the input data rate is too high and AaTestPort buffer gets full,
*       the messages can be lost.
*
*   @par Example:
*   Following example shows basic usage.
*   @code
        #include <IfAaTestPort.h>

         void ExampleFunction(void)
         {
             SAaTestPort *port;

             port = AaTestPortCreateTcp("AaTestPort_Name",
                                         cpid
                                         listenPort,
                                         RxPriority,
                                         TxPriority);
             if( GLO_NULL != port )
             {
                 if( EAaTestPortRetVal_Ok != AaTestPortStart(port) )
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
*
*******************************************************************************/
TAaTestPort AaTestPortCreateTcp(const char*   name,
                                TAaSysComCpid cpid,
                                u32           port,
                                u32           priorityRx,
                                u32           priorityTx);


/**
*******************************************************************************
*
*   @brief      Function to create a TCP tester port server instance with large buffer.
*
*   @param[in]  name        Name of the tester port server.
*                           Note: AaTestPort server name should be unique per CE.
*   @param[in]  cpid        SysCom communication point identifier.
*   @param[in]  port        TCP port to listen for incoming connection requests.
*   @param[in]  priorityRx  Priority of process which handles RX data.
*   @param[in]  priorityTx  Priority of process which handles TX data.
*   @param[in]  bufferSize  Size of incoming and outgoing buffer in Bytes.
*
*   @return     Pointer to the TestPort server instance in success, otherwise GLO_NULL.
*
*
*   @par Description:
*   This Function creates a tester port server instance with large buffer.
*   It works similar to #AaTestPortCreateTcp.
*   AaTestPortCreateTcpLargeBuffer should be used very thoughtfully to not increase
*   the memory consumption unnecessarily. The internal message buffer can be set via
*   the API parameter \a bufferSize.
*   Note: If data, sent in a short time, exceeds the internal message buffer size
*   some messages may be dropped.
*
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*     - The maximum current data throughput of this server is limited by
*       the buffer size.
*     - The buffer size itself is restricted by #AATESTPORT_MAX_BUFFER_SIZE_API
*       and #AATESTPORT_MIN_BUFFER_SIZE.
*     - The number of server instances is limited to #AATESTPORT_MAX_TCP_PORT.
*     - Only one client connection per server is allowed.
*     - In case the input data rate is too high and AaTestPort buffer gets full,
*       the messages can be lost.
*
*   @par Example:
*   Following example shows basic usage.
*   @code
        #include <IfAaTestPort.h>

         void ExampleFunction(void)
         {
             SAaTestPort* port;
             port = AaTestPortCreateTcpLargeBuffer("AaTestPort_Name",
                                                   cpid,
                                                   listenPort,
                                                   RxPriority,
                                                   TxPriority,
                                                   256000);
             if( GLO_NULL != port )
             {
                 if( EAaTestPortRetVal_Ok != AaTestPortStart(*port) )
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
TAaTestPort AaTestPortCreateTcpLargeBuffer(char*         name,
                                           TAaSysComCpid cpid,
                                           u32           port,
                                           u32           priorityRx,
                                           u32           priorityTx,
                                           u32           bufferSize);



/**
*******************************************************************************
*
*   @brief      Function to start a tester port client or server instance.
*
*   @param[in]  instance    Tester port instance.
*
*   @return     #EAaTestPortRetVal_Ok in success, otherwise #EAaTestPortRetVal_Error.
*
*
*   @par Description:
*   Sets the given tester port instance as active.
*   Activates listening and accepts a external connection on the given tester port instance.
*
*   @par Errors:
*   #EAaTestPortRetVal_Error in case of failure.
*
*   @par Restrictions:
*   In case this API is used to start tester port client instance, it is valid only for CCS-RT.
*   For CCS-MCU AaTestPort client, please refer to new API AaTestPortStartTraceTcpClientExt()
*
*   @par Example:
*   see AaTestPortCreateTcp(), AaTestPortCreateTcpLargeBuffer() or (in CCS-RT only) AaTestPortCreateTraceTcpClient() for information on how to create an instance.
*
*   @code
        include <IfAaTestPort.h>

        void ExampleFunction(void)
        {
            SAaTestPort* port;
            AaTestPortStart(port);
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
EAaTestPortRetVal AaTestPortStart(TAaTestPort instance);


/**
*******************************************************************************
*
*   @brief      Function to stop and delete a tester port instance.
*
*   @param[in]  instance    Tester port instance.
*
*   @return     #EAaTestPortRetVal_Ok in success, otherwise #EAaTestPortRetVal_Error.
*
*
*   @par Description:
*   Calling this function will make this instance to stop listening for
*   new connection requests and wait for the existing connection to close.
*   After the connection is closed, the socket will be closed and this
*   tester port slot is given back to the pool of free tester ports.
*
*   @par Errors:
*   #EAaTestPortRetVal_Error in case of null pointer or the instance does not exist.
*
*   @par Restrictions:
*   1. The function is asynchronous and will return before the background cleanup and deletions are complete.
*   This is to avoid the applications from blocking on AaTestPortDelete. The actual cleanup and deletion of instances
*   takes some time. So in case the instances are deleted and created with the same name in quick succession, it is
*   possible that instance creation might fail. In such a scenario, it is advised to use a different unused name for
*   creating a new instance.
*   2. In case this API is used to stop tester port client instance, it is valid only for CCS-RT.
*   For CCS-MCU AaTestPort client, please refer to new API AaTestPortDeleteTraceTcpClientExt()
*
*   @par Example:
*   Following example shows basic usage.
*   See AaTestPortCreateTcp(), AaTestPortCreateTcpLargeBuffer() or
*   (in CCS-RT only) AaTestPortCreateTraceTcpClient() for information on how to create an instance.
*   @code
        #include <IfAaTestPort.h>

         void ExampleFunction(void)
         {
             SAaTestPort* port;
             AaTestPortStop(port);
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
EAaTestPortRetVal AaTestPortStop(TAaTestPort instance);


/**
*******************************************************************************
*
*   @brief      Function to halt a tester port instance.
*
*   @param[in]  instance    Tester port instance.
*
*   @return     #EAaTestPortRetVal_Ok in success, otherwise #EAaTestPortRetVal_Error.
*
*
*   @par Description:
*   This function will put the tester port instance on halt, shutting down
*   the opened socket. Other than with AaTestPortDelete(), communication can be
*   reestablished by calling the function AaTestPortStart().
*
*   @par Errors:
*   #EAaTestPortRetVal_Error in case the instance does not exist.
*
*   @par Restrictions:
*   In case this API is used to halt tester port client instance, it is valid only for CCS-RT.
*   For CCS-MCU AaTestPort client, please refer to new API AaTestPortHaltTraceTcpClientExt()
*
*   @par Example:
*   Following example shows basic usage. See AaTestPortCreateTcp(),
*   AaTestPortCreateTcpLargeBuffer() or (in CCS-RT only) AaTestPortCreateTraceTcpClient()
*   for information on how to create an instance.
*   @code
        #include <IfAaTestPort.h>

         void ExampleFunction(void)
         {
             SAaTestPort* port;
             AaTestPortHalt(port);
             // Do something
             AaTestPortStart(port);
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
EAaTestPortRetVal AaTestPortHalt(TAaTestPort instance);


/**
*******************************************************************************
*
*   @brief      Function to delete a tester port instance.
*
*   @param[in]  instance    Created tester port instance.
*
*   @return #EAaTestPortRetVal_Ok in success, otherwise #EAaTestPortRetVal_Error.
*
*
*   @par Description:
*   Calling this function will make this instance to stop listening for
*   new connection requests and wait for the existing connection to close.
*   After the connection is closed, the socket will be closed and this
*   tester port slot is given back to the pool of free tester ports.
*
*   @par Errors:
*   #EAaTestPortRetVal_Error in case of null pointer or the instance does not exist.
*
*   @par Restrictions:
*   1. The function is asynchronous and will return before the background cleanup and deletions are complete.
*   This is to avoid the applications from blocking on AaTestPortDelete. The actual cleanup and deletion of instances
*   takes some time. So in case the instances are deleted and created with the same name in quick succession, it is
*   possible that instance creation might fail. In such a scenario, it is advised to use a different unused name for
*   creating a new instance.
*   2. In case this API is used to stop tester port client instance, it is valid only for CCS-RT.
*   For CCS-MCU AaTestPort client, please refer to new API AaTestPortDeleteTraceTcpClientExt()
*
*   @par Example:
*   Following example shows basic usage.
*   See AaTestPortCreateTcp(), AaTestPortCreateTcpLargeBuffer() or
*   (in CCS-RT only) AaTestPortCreateTraceTcpClient() for information on how to create an instance.
*   @code
        #include <IfAaTestPort.h>

         void ExampleFunction(void)
         {
             SAaTestPort* port;
             AaTestPortDelete(port);
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
EAaTestPortRetVal AaTestPortDelete(TAaTestPort instance);


/**
*******************************************************************************
*
*   @brief      Function to set own stream parser for a tester port instance.
*
*   @param[in]  instance    Tester port instance.
*   @param[in]  opaque      User data to be passed as parameter to the callback functions.
*   @param[in]  rx          Receive callback function.
*   @param[in]  tx          Transmit callback function.
*   @param[in]  reset       Reset callback function.
*
*   @return     #EAaTestPortRetVal_Ok in success,
*               otherwise #EAaTestPortRetVal_InvalidParameter or #EAaTestPortRetVal_Error.
*
*
*   @par Description:
*   User can define own protocol.
*
*   @par Errors:
*   - #EAaTestPortRetVal_Error in case of null pointer tester port instance.
*   - #EAaTestPortRetVal_InvalidParameter in case of null pointer to the callback functions.
*
*   @par Restrictions:
*   Setting the parsers will only take effect if instance is not started.
*   Setting the parsers is only applicable to AaTestPort Server instances in CCS_MCU
*
*   @par Example:
*   Following example shows basic usage.
*   @code
         #include <IfAaTestPort.h>

         TAaTestPortRxCb*    rx(void* opaquePtr, u32 dataSize, void* dataPtr);
         TAaTestPortTxCb*    tx(void* opaquePtr, void** messagePtrPtr);
         TAaTestPortResetCb* reset(void* opaquePtr);

         void ExampleFunction(void)
         {
             SAaTestPort* port;
             port = AaTestPortCreateTcp("AaTestPort_Name",
                                         cpid
                                         listenPort,
                                         RxPriority,
                                         TxPriority);
             if( GLO_NULL != port )
             {
                 if(EAaTestPortRetVal_Ok != AaTestPortParserSetup(port,
                                                                  opaque,
                                                                  rx,
                                                                  tx,
                                                                  reset) )
                 {
                     //return error;
                 }

                 if( EAaTestPortRetVal_Ok != AaTestPortStart(port) )
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
EAaTestPortRetVal AaTestPortParserSetup(TAaTestPort         instance,
                                        void*               opaque,
                                        TAaTestPortRxCb*    rx,
                                        TAaTestPortTxCb*    tx,
                                        TAaTestPortResetCb* reset);


/**
*******************************************************************************
*
*   @brief      Function to allocate memory for outgoing data.
*
*   @param[in]  instance    Created tester port instance.
*   @param[in]  size        Size of the needed buffer in bytes.
*
*   @return     Pointer to memory block on success, otherwise GLO_NULL.
*
*
*   @par Description:
*   User can allocate own memory for outgoing data
*
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*   New memory buffer will be used if instance is not started.
*   This can only be used for AaTestPort Server instances in CCS-MCU
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
void* AaTestPortParserAllocTx(TAaTestPort instance, u32 size);

/**@}*/

#ifdef __cplusplus
}
#endif
#endif /*  _MCU_RT_IFAATESTPORT_H */
