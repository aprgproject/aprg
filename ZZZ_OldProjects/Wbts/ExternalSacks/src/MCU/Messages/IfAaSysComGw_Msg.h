/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef IF_MCU_IFAASYSCOMGW_MSG_H
#define IF_MCU_IFAASYSCOMGW_MSG_H

#include <CcsCommon.h>
#include "../Definitions/IfAaSysComGw_Defs.h"
#include "../../COMMON/Messages/IfAaSysComGw_Msg.h"
#include "../../SHARED/MCU_RT/Messages/IfAaSysComGw_Msg.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @addtogroup dgAaSysComGwMcu AaSysComGw MCU
 * @ingroup dgAaSysCom
 *
 * Common Computer and Support SW SysCom Gateway.
 *
 * @{
 */

 /*----------------------- PUBLIC DECLARATIONS --------------------------------*/


#ifndef AASYSCOM_GW_REG_LPM_REQ_MSG
# define AASYSCOM_GW_REG_LPM_REQ_MSG                    0x1289 /* !- SIGNO(struct AaSysComGwRegReqLpm) -! */
#endif /* AASYSCOM_GW_REG_LPM_REQ_MSG */

#ifndef AASYSCOM_GW_REG_LPM_RESP_MSG
# define AASYSCOM_GW_REG_LPM_RESP_MSG                   0x128A /* !- SIGNO(struct AaSysComGwRegRespLpm) -! */
#endif /* AASYSCOM_GW_REG_LPM_RESP_MSG */

#ifndef AASYSCOM_GW_DEF_ROUTE_SUPERVISION_REQ_MSG
# define AASYSCOM_GW_DEF_ROUTE_SUPERVISION_REQ_MSG      0x1561 /* !- SIGNO(struct AaSysComGwDefRouteSupervisionReq) -! */
#endif /* AASYSCOM_GW_DEF_ROUTE_SUPERVISION_REQ_MSG */

#ifndef AASYSCOM_GW_DEF_ROUTE_SUPERVISION_RESP_MSG
# define AASYSCOM_GW_DEF_ROUTE_SUPERVISION_RESP_MSG     0x1562 /* !- SIGNO(struct AaSysComGwDefRouteSupervisionResp) -! */
#endif /* AASYSCOM_GW_DEF_ROUTE_SUPERVISION_RESP_MSG */

#ifndef AASYSCOM_GW_DEF_ROUTE_SUPERVISION_IND_MSG
# define AASYSCOM_GW_DEF_ROUTE_SUPERVISION_IND_MSG      0x1563 /* !- SIGNO(struct AaSysComGwDefRouteSupervisionInd) -! */
#endif /* AASYSCOM_GW_DEF_ROUTE_SUPERVISION_IND_MSG */

/** @name AaSysComGw message structure definitions (MCU Specific)
 * @{
 */


/**
 * @brief Extended message (with remote SIC address as mask) to add a route
 *
 * This message is sent by application to AaSysCom GW when a new route is wanted
 * to be registered.
 */
typedef struct AaSysComGwRegReqLpm
{
  TAaSysComSicad          localSicAddr;     /**< Applications own Sic address */
  TAaSysComSicad          remoteSicAddr;    /**< Sic address of remote application */
  u32                     remoteSicMaskLen; /**< Number of significant bits in remote SIC address */
  SAaSysComGwIpAddressExt localIP;          /**< IP address of local application @note this field is used in bind() */
  SAaSysComGwIpAddressExt remoteIP;         /**< IP address of remote application */
  EAaSysComGwProtocol     protocol;         /**< information about the protocol used in link, e.g UDPCP, UDP, TCP, ... */
  ERetainMsgHeader        retainMsgHeader;  /**< 1 if Msg header should be left intact to messages send */
  u32                     msgID;            /**< message ID to be put into external messages when delivering to application */
  EAaSysComGwReliability  reliability;      /**< route reliability information */
  u32                     protocolDataLen;  /**< Length of protocol specific data.\n
                                                 This field should be set like sizeof( <protocol_specific_data_structure> ).\n
                                                 Value 0 means no protocol specific data is used. */
  u8                      protocolData[1];  /**< Protocol specific data
                                                 This field can contain one of below structure:\n
                                                 AaSysComGwRegTcpParameters
                                                 AaSysComGwRegSctpParameters
                                                 AaSysComGwRegTcpExtParameters.\n
                                                 Field protocolDataLen indicates which structure is in use.
                                                 In case protocolDataLen equals 0 no protocol specific data is used. */
} AaSysComGwRegReqLpm;

/**
 * @brief Extended reply message (with remote SIC address as mask) for route add
 *
 * AaSys GW will send this message to the application upon route registration.
 */
typedef struct AaSysComGwRegRespLpm
{
  TAaSysComSicad          localSicAddr;     /**< Applications own Sic address */
  TAaSysComSicad          remoteSicAddr;    /**< Sic address of remote application */
  u32                     remoteSicMaskLen; /**< Number of significant bits in remote SIC address */
  SAaSysComGwIpAddressExt localIP;          /**< IP address of local application @note this field is used in bind() */
  SAaSysComGwIpAddressExt remoteIP;         /**< IP address of remote application */
  EAaSysComGwProtocol     protocol;         /**< information about the protocol used in link, e.g UDPCP, UDP, TCP, ... */
  ERetainMsgHeader        retainMsgHeader;  /**< 1 if Msg header should be left intact to messages send */
  u32                     msgID;            /**< message ID to be put into external messages when delivering to application */
  EAaSysComGwReliability  reliability;      /**< route reliability information */
  /* above fields discarding the api_header will be copied to the reply from the request */
  EAaSysComGwStatus       status;           /**< status of the operation */
  TAaSysComGwRouteId      routeId;          /**< route ID of the added route (AASYSCOMGW_INVALID_ROUTE_ID if route add failed) */
  TAaSysComGwPortNum      port;             /**< port number assigned by the transport layer. Main usage for this parameter
                                                 is the case when user has specified port number zero to the request message,
                                                 in which case IP STACK will assign a dynamic port, though this is used to inform
                                                 the dynamic port number to the user. */
  /* bellow fields will be copied to the reply from the request */
  u32                     protocolDataLen;  /**< Length of protocol specific data.\n
                                                 This field should be set like sizeof( <protocol_specific_data_structure> ).\n
                                                 Value 0 means no protocol specific data is used. */
  u8                      protocolData[1];  /**< Protocol specific data
                                                 This field can contain one of below structure:\n
                                                 AaSysComGwRegTcpParameters
                                                 AaSysComGwRegSctpParameters
                                                 AaSysComGwRegTcpExtParameters.\n
                                                 Field protocolDataLen indicates which structure is in use.
                                                 In case protocolDataLen equals 0 no protocol specific data is used. */
} AaSysComGwRegRespLpm;

/*
 * @brief   Default route supervision request.
 *
 * Request to (un)subscribe for link events on default route.
 * Local IP and protocol are the key to identify route.
 * Subscriber is composed from SICAD and transaction id.
 *
 * @par Restrictions:
 * User shall ensure that transaction id is unique - i.e. user shall not
 * subscribe for default route A and default route B with the same transaction id
 * as it will fail to match transaction id to proper (A or B) default route data
 * in user context.
 *
 * From LBT4089-A-b, only TCP is supported.
 *
 * @par See:
 * AaSysComGwSubscribeForEventsDefRoute, AaSysComGwUnsubscribeFromEventsDefRoute
 */
typedef struct AaSysComGwDefRouteSupervisionReq
{
    EAaSysComGwRouteSubReqType  reqType;        /**< request type e.g. subscribe, unsubscribe */
    SAaSysComGwIpAddressExt     localIP;        /**< local IP address */
    EAaSysComGwProtocol         protocol;       /**< protocol (UDP, UDPCP, TCP, SCTP) */
    TAaSysComSicad              subscriber;     /**< SIC address of the subscriber */
    u32                         transactionId;  /**< transaction id */
} AaSysComGwDefRouteSupervisionReq;

/*
 * @brief   Default route supervision response.
 *
 * Response on (un)subscribe for link request.
 */
typedef struct AaSysComGwDefRouteSupervisionResp
{
    u32                         transactionId;  /**< transaction id (from request) */
    EAaSysComGwStatus           status;         /**< status of the operation */
} AaSysComGwDefRouteSupervisionResp;

/*
 * @brief   Default route supervision indication.
 *
 * Indication of link status change, received by subscribers,
 * after successful subscription on default route.
 */
typedef struct AaSysComGwDefRouteSupervisionInd
{
    u32                     transactionId;  /**< transaction id (from request) */
    EAaSysComGwRouteStatus  status;         /**< status of the route */
} AaSysComGwDefRouteSupervisionInd;

/** @} */

/** @} end: @addtogroup dgAaSysComGwMcu AaSysComGw MCU */

#ifdef __cplusplus
}
#endif

#endif /* IF_MCU_IFAASYSCOMGW_MSG_H */

