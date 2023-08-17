/**
*******************************************************************************
* @file
* $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaTestPort MCU RT Definitions.
*
* Copyright 2015 Nokia Soultions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IF_AATESTPORT_DEF_H_
#define _MCU_RT_IF_AATESTPORT_DEF_H_

#include <CcsCommon.h>
#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaTestPortMcuRtDefs AaTestPort Definitions (MCU RT)
 * @ingroup dgAaTestPort
 */

/*@{*/

/*!
 * Setting this RAD config tag allows the user to set the internal message buffer for
 * Tcp tester port server instances, created with AaTestPortCreateTcp(). The buffer
 * size is restricted to #AATESTPORT_MIN_BUFFER_SIZE and #AATESTPORT_MAX_BUFFER_SIZE.
 */
#define AATESTPORT_CONFIG_TAG_BUFFER_SIZE         "ccs.service.testport.buffersize"

/*!
 * Setting this RAD config tag allows the user to set the testport server ip address
 * in string format for all Tcp tester port server instances. Both IPv4 and IPv6 ip
 * family is supported. Supported only by RCP CC&S.
 */
#define AATESTPORT_CONFIG_TAG_IP_ADDRESS         "ccs.service.testport.ipaddress"

/*!
 * This define describes the minimum size, in Bytes, of the internal message buffer.
 */
#define AATESTPORT_MIN_BUFFER_SIZE                128000

/*!
 * This define describes the maximum size, in Bytes, of the internal message buffer,
 * when set with the RAD config tag #AATESTPORT_CONFIG_TAG_BUFFER_SIZE.
 */
#define AATESTPORT_MAX_BUFFER_SIZE                512000

/*!
 * This define describes the maximum size, in Bytes, of the internal message buffer,
 * when set using AaTestPortCreateTcpLargeBuffer().
 */
#define AATESTPORT_MAX_BUFFER_SIZE_API            2048000

/*!
 * This define describes the default size, in Bytes, of the internal message buffer,
 * when the RAD config tag #AATESTPORT_CONFIG_TAG_BUFFER_SIZE is not set.
 */
#define AATESTPORT_DEFAULT_BUFFER_SIZE            128000

/*!
 * This define describes the lower boundary for setting a Port.
 */
#define AATESTPORT_PORT_RANGE_FROM                1

/*!
 * This define describes the upper boundary for setting a Port.
 */
#define AATESTPORT_PORT_RANGE_TO                  65534

/*!
 * This define describes the number of possible Tcp server instances.
 */
#define AATESTPORT_MAX_TCP_PORT                   20

/*!
 * This define describes the number of possible Tcp client instances.
 */
#define AATESTPORT_MAX_TCP_CLIENT                 40

/*
 *  @brief Forward declaration of AaTestPort internal structure.
 */
typedef struct SAaTestPort* TAaTestPort; /*!< Pointer to the internal TestPort structure. */

/*!
 *  @brief A type for interface function return values.
 */
typedef enum EAaTestPortRetVal
{
    EAaTestPortRetVal_Ok                   = 0, /*!< Success of action */
    EAaTestPortRetVal_Error                = 1, /*!< Some internal error */
    EAaTestPortRetVal_InvalidParameter     = 2, /*!< Invalid parameter is given */
    EAaTestPortRetVal_ResourceNotAvailable = 3  /*!< Service is not initialized */
}EAaTestPortRetVal;

/*!
 *  @brief      A type of stream parser RX callback function.
 *
 *  @param[in]  opaquePtr       User given data.
 *  @param[in]  dataSize        Size of received data in bytes.
 *  @param[in]  dataPtr         Received data to be handled.
 *
 *  @return     Zero in success otherwise error.
 */
typedef i32 TAaTestPortRxCb(void* opaquePtr, u32 dataSize, void* dataPtr);

/*!
 *  @brief      A type of stream parser TX callback function.
 *
 *  @param[in]  opaquePtr       User given data.
 *  @param[in]  messagePtrPtr   SysCom message handle.
 *
 *  @return     Zero in success otherwise error.
 */
typedef i32 TAaTestPortTxCb(void* opaquePtr, void** messagePtrPtr);

/*!
 *  @brief      A type of stream parser reset callback function.
 *
 *  @param[in]  opaquePtr       User given data.
 */
typedef void TAaTestPortResetCb(void* opaquePtr);


/*@}*/

#ifdef __cplusplus
}
#endif

#endif  //_MCU_RT_IF_AATESTPORT_DEF_H_
