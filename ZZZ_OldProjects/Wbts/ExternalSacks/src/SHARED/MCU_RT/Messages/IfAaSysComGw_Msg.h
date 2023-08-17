/**
*******************************************************************************
* Copyright 2015,2019 Nokia. All rights reserved.
*******************************************************************************/

#ifndef IF_MCU_RT_AASYSCOM_GW_MSGS_H
#define IF_MCU_RT_AASYSCOM_GW_MSGS_H

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <glo_def.h>
#include <CcsCommon.h>
#include "../Definitions/IfAaSysCom_Defs.h"
#include "../Definitions/IfAaSysComGw_Defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
 * @addtogroup dgAaSysComGwMcuRt AaSysComGw MCU_RT
 * @ingroup dgAaSysCom
 *
 * Common Computer and Support SW SysCom Gateway.
 *
 * @{
 */

/*----------------------- PRIVATE DECLARATIONS -------------------------------*/

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** @name GW Messages
 * @{
 */
#ifndef AASYSCOM_GW_CREATE_MSG
# define AASYSCOM_GW_CREATE_MSG                  0x2BD1 /* !- SIGNO(struct void) -! */
#endif /* AASYSCOM_GW_CREATE_MSG */
#ifndef AASYSCOM_GW_READY_IND_MSG
# define AASYSCOM_GW_READY_IND_MSG               0x2BD2 /* !- SIGNO(struct AaSysComGwReadyInd) -! */
#endif /* AASYSCOM_GW_READY_IND_MSG */
#ifndef AASYSCOM_GW_REG_REQ_MSG
# define AASYSCOM_GW_REG_REQ_MSG                 0x2BD3 /* !- SIGNO(struct AaSysComGwRegReq) -! */
#endif /* AASYSCOM_GW_REG_REQ_MSG */
#ifndef AASYSCOM_GW_REG_REPLY_MSG
# define AASYSCOM_GW_REG_REPLY_MSG               0x2BD4 /* !- SIGNO(struct AaSysComGwRegReply) -! */
#endif /* AASYSCOM_GW_REG_REPLY_MSG */
#ifndef AASYSCOM_GW_DEREG_REQ_MSG
# define AASYSCOM_GW_DEREG_REQ_MSG               0x2BD5 /* !- SIGNO(struct AaSysComGwDeRegReq) -! */
#endif /* AASYSCOM_GW_DEREG_REQ_MSG */
#ifndef AASYSCOM_GW_DEREG_REPLY_MSG
# define AASYSCOM_GW_DEREG_REPLY_MSG             0x2BD6 /* !- SIGNO(struct AaSysComGwDeRegReply) -! */
#endif /* AASYSCOM_GW_DEREG_REPLY_MSG */
#ifndef AASYSCOM_GW_COMM_FAIL_IND_MSG
# define AASYSCOM_GW_COMM_FAIL_IND_MSG           0x2BD8 /* !- SIGNO(struct AaSysComGwCommFailureInd) -! */
#endif /* AASYSCOM_GW_COMM_FAIL_IND_MSG */
#ifndef AASYSCOM_GW_REG_DEF_ROUTE_REQ_MSG
# define AASYSCOM_GW_REG_DEF_ROUTE_REQ_MSG       0x2BD9 /* !- SIGNO(struct AaSysComGwRegDefRouteReq) -! */
#endif /* AASYSCOM_GW_REG_DEF_ROUTE_REQ_MSG */
#ifndef AASYSCOM_GW_REG_DEF_ROUTE_REPLY_MSG
# define AASYSCOM_GW_REG_DEF_ROUTE_REPLY_MSG     0x2BDA /* !- SIGNO(struct AaSysComGwRegDefRouteReply) -! */
#endif /* AASYSCOM_GW_REG_DEF_ROUTE_REPLY_MSG */
#ifndef AASYSCOM_GW_STATS_REQ_MSG
# define AASYSCOM_GW_STATS_REQ_MSG               0x1B9E /* !- SIGNO(struct AaSysComGwStatsReq) -! */
#endif /* AASYSCOM_GW_STATS_REQ_MSG */
#ifndef AASYSCOM_GW_DEREG_ALL_REQ_MSG
# define AASYSCOM_GW_DEREG_ALL_REQ_MSG           0x1F0E /* !- SIGNO(struct void) -! */
#endif /* AASYSCOM_GW_DEREG_ALL_REQ_MSG */
#ifndef AASYSCOM_GW_DEREG_ALL_REPLY_MSG
# define AASYSCOM_GW_DEREG_ALL_REPLY_MSG         0x1F0F /* !- SIGNO(struct AaSysComGwDeregAllReply) -! */
#endif /* AASYSCOM_GW_DEREG_ALL_REPLY_MSG */
#ifndef AASYSCOM_GW_ROUTE_INFO_REQ_MSG
# define AASYSCOM_GW_ROUTE_INFO_REQ_MSG          0x1F10 /* !- SIGNO(struct AaSysComGwRouteInfoReq) -! */
#endif /* AASYSCOM_GW_ROUTE_INFO_REQ_MSG */
#ifndef AASYSCOM_GW_ROUTE_INFO_REPLY_MSG
# define AASYSCOM_GW_ROUTE_INFO_REPLY_MSG        0x1F11 /* !- SIGNO(struct AaSysComGwRouteInfoReply) -! */
#endif /* AASYSCOM_GW_ROUTE_INFO_REPLY_MSG */
#ifndef AASYSCOM_GW_REG_TCP_REQ_MSG
# define AASYSCOM_GW_REG_TCP_REQ_MSG             0x1F12 /* !- SIGNO(struct AaSysComGwRegTcpReq) -! */
#endif /* AASYSCOM_GW_REG_TCP_REQ_MSG */
#ifndef AASYSCOM_GW_REG_TCP_REPLY_MSG
# define AASYSCOM_GW_REG_TCP_REPLY_MSG           0x1F13 /* !- SIGNO(struct AaSysComGwRegTcpReply) -! */
#endif /* AASYSCOM_GW_REG_TCP_REPLY_MSG */

/** @brief: Extended message (with IPv6 support).
 *  @par Restrictions: IPv6 is supported by CC&S-MCU and CC&S-RT on RCP only. CC&S-DSP does not support IPv6.
 */
#ifndef AASYSCOM_GW_REG_EXT_REQ_MSG
# define AASYSCOM_GW_REG_EXT_REQ_MSG                0x1172 /* !- SIGNO(struct AaSysComGwRegReqExt) -! */
#endif /* AASYSCOM_GW_REG_EXT_REQ_MSG */

/** @brief: Extended message (with IPv6 support).
 *  @par Restrictions: IPv6 is supported by CC&S-MCU and CC&S-RT on RCP only. CC&S-DSP does not support IPv6.
 */
#ifndef AASYSCOM_GW_REG_EXT_REPLY_MSG
# define AASYSCOM_GW_REG_EXT_REPLY_MSG              0x1173 /* !- SIGNO(struct AaSysComGwRegReplyExt) -! */
#endif /* AASYSCOM_GW_REG_EXT_REPLY_MSG */

/** @brief: Extended message (with IPv6 support).
 *  @par Restrictions: IPv6 is supported by CC&S-MCU and CC&S-RT on RCP only. CC&S-DSP does not support IPv6.
 */
#ifndef AASYSCOM_GW_REG_DEF_ROUTE_EXT_REQ_MSG
# define AASYSCOM_GW_REG_DEF_ROUTE_EXT_REQ_MSG      0x1188 /* !- SIGNO(struct AaSysComGwRegDefRouteReqExt) -! */
#endif /* AASYSCOM_GW_REG_DEF_ROUTE_EXT_REQ_MSG */

/** @brief: Extended message (with IPv6 support).
 *  @par Restrictions: IPv6 is supported by CC&S-MCU and CC&S-RT on RCP only. CC&S-DSP does not support IPv6.
 */
#ifndef AASYSCOM_GW_REG_DEF_ROUTE_EXT_REPLY_MSG
# define AASYSCOM_GW_REG_DEF_ROUTE_EXT_REPLY_MSG    0x1189 /* !- SIGNO(struct AaSysComGwRegDefRouteReplyExt) -! */
#endif /* AASYSCOM_GW_REG_DEF_ROUTE_EXT_REPLY_MSG */

/** @brief: Extended message (with IPv6 support).
 *  @par Restrictions: IPv6 is supported by CC&S-MCU and CC&S-RT on RCP only. CC&S-DSP does not support IPv6.
 */
#ifndef AASYSCOM_GW_ROUTE_INFO_EXT_REQ_MSG
# define AASYSCOM_GW_ROUTE_INFO_EXT_REQ_MSG         0x118A /* !- SIGNO(struct AaSysComGwRouteInfoReqExt) -! */
#endif /* AASYSCOM_GW_ROUTE_INFO_EXT_REQ_MSG */

/** @brief: Extended message (with IPv6 support).
 *  @par Restrictions: IPv6 is supported by CC&S-MCU and CC&S-RT on RCP only. CC&S-DSP does not support IPv6.
 */
#ifndef AASYSCOM_GW_ROUTE_INFO_EXT_REPLY_MSG
# define AASYSCOM_GW_ROUTE_INFO_EXT_REPLY_MSG       0x118B /* !- SIGNO(struct AaSysComGwRouteInfoReplyExt) -! */
#endif /* AASYSCOM_GW_ROUTE_INFO_EXT_RESP_MSG */

/** @brief: Extended message (with IPv6 support).
 *  @par Restrictions: IPv6 is supported by CC&S-MCU and CC&S-RT on RCP only. CC&S-DSP does not support IPv6.
 */
#ifndef AASYSCOM_GW_UNKNOWN_SENDER_EXT_MSG
# define AASYSCOM_GW_UNKNOWN_SENDER_EXT_MSG         0x118C /* !- SIGNO(struct AaSysComGwUnknownSenderIndExt) -! */
#endif /* AASYSCOM_GW_UNKNOWN_SENDER_EXT_MSG */

/** @brief: route supervision message
*   @par Restrictions: route supervision is supported by CC&S-MCU and CC&S-RT
*/
#ifndef AASYSCOM_GW_ROUTE_SUPERVISION_REQ_MSG
# define AASYSCOM_GW_ROUTE_SUPERVISION_REQ_MSG          0x139c /* !- SIGNO(struct AaSysComGwRouteSupervisionReq) -! */
#endif /* AASYSCOM_GW_ROUTE_SUPERVISION_REQ_MSG */

#ifndef AASYSCOM_GW_ROUTE_SUPERVISION_RESP_MSG
# define AASYSCOM_GW_ROUTE_SUPERVISION_RESP_MSG         0x139D /* !- SIGNO(struct AaSysComGwRouteSupervisionResp) -! */
#endif /* AASYSCOM_GW_ROUTE_SUPERVISION_RESP_MSG */

#ifndef AASYSCOM_GW_ROUTE_SUPERVISION_IND_MSG
# define AASYSCOM_GW_ROUTE_SUPERVISION_IND_MSG          0x139E /* !- SIGNO(struct AaSysComGwRouteSupervisionInd) -! */
#endif /* AASYSCOM_GW_ROUTE_SUPERVISION_IND_MSG */

/** @} */


/** @name AaSysComGw message structure definitions
 * @{
 */

/**
 * @brief create message
 *
 * This message has to be sent to AaSysCom GW after it is started.
 * Main purpose of this message is to pass the own board and
 * cpu information to AaSysCom Gw.
 *
 * there is no struct defined for this message because the message
 * content is empty. Message Id for this is AASYSCOM_GW_CREATE_MSG
 */

typedef struct AaSysComGwMsgInd
{
  /** following field is a special field ment for users to be able to point to
      the place in the message, where the actual message data starts (array of 4 bytes to make
      the struct padding divisible by 4). Length of data is
      api_header.length - sizeof(struct Api_header) */
  u8                data[4];   /**< accessory field to transparent data */
} AaSysComGwMsgInd;

/**
 * @brief message to inform that we are up and kicking.
 *
 * AaSysCom GW sends this message to the Cp that sent the create msg
 * when it has been started successfully and it is ready to operate.
 */
typedef struct AaSysComGwReadyInd
{
  u32  gwEuId; /**< Eu ID of the AaSysCom GW */
} AaSysComGwReadyInd;

/**
 * @brief message to add a route
 *
 * This message is sent by application to AaSysCom GW when a new route is wanted
 * to be registered.
 */
typedef struct AaSysComGwRegReq_deprecated
{
  TAaSysComSicad                    localSicAddr;     /**< Applications own Sic address */
  TAaSysComSicad                    remoteSicAddr;    /**< Sic address of remote application */
  SAaSysComGwIpAddress_deprecated   localIP;          /**< IP address of local application @note this field is used in bind() */
  SAaSysComGwIpAddress_deprecated   remoteIP;         /**< IP address of remote application */
  EAaSysComGwProtocol               protocol;         /**< information about the protocol used in link, e.g UDPCP, UDP, TCP, ... */
  ERetainMsgHeader                  retainMsgHeader;  /**< 1 if Msg header should be left intact to messages send */
  u32                               msgID;            /**< message ID to be put into external messages when delivering to application */
  EAaSysComGwReliability            reliability;      /**< route reliability information */
} AaSysComGwRegReq_deprecated;
typedef AaSysComGwRegReq_deprecated AaSysComGwRegReq CCS_DEPRECATED("Use AaSysComGwRegReqExt instead.");

/**
 * @brief Extended message to add a route
 *
 * This message is sent by application to AaSysCom GW when a new route is wanted available for both IPv4 and IPv6
 * to be registered.
 * @par Restrictions: IPv6 is supported by CC&S-MCU and CC&S-RT on RCP only. CC&S-DSP does not support IPv6.
 */
typedef struct AaSysComGwRegReqExt
{
  TAaSysComSicad          localSicAddr;     /**< Applications own Sic address */
  TAaSysComSicad          remoteSicAddr;    /**< Sic address of remote application */
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
} AaSysComGwRegReqExt;

/**
 * @brief reply message for route add
 *
 * AaSys GW will send this message to the application upon route registeration.
 */
typedef struct AaSysComGwRegReply
{
  TAaSysComSicad                    localSicAddr;   /**< Applications own Sic address */
  TAaSysComSicad                    remoteSicAddr;  /**< Sic address of remote application */
  SAaSysComGwIpAddress_deprecated   localIP;        /**< IP address of local application @note this field is used in bind() */
  SAaSysComGwIpAddress_deprecated   remoteIP;       /**< IP address of remote application */
  EAaSysComGwProtocol               protocol;       /**< information about the protocol used in link, e.g UDPCP, UDP, TCP, ... */
  ERetainMsgHeader                  retainMsgHeader; /**< 1 if Msg header should be left intact to messages send */
  u32                               msgID;          /**< message ID to be put into external messages when delivering to application */
  EAaSysComGwReliability            reliability;    /**< route reliability information */
  /* above fields discarding the api_header will be copied to the reply from the request */
  EAaSysComGwStatus                 status;         /**< status of the operation */
  TAaSysComGwRouteId                routeId;        /**< route ID of the added route (AASYSCOMGW_INVALID_ROUTE_ID if route add failed) */
  TAaSysComGwPortNum                port;           /**< port number assigned by the transport layer. Main usage for this parameter
                                             is the case when user has specified port number zero to the request message,
                                             in which case IP STACK will assign a dynamic port, though this is used to inform
                                             the dynamic port number to the user. */
} AaSysComGwRegReply CCS_DEPRECATED("Use AaSysComGwRegReplyExt instead.");

/**
 * @brief Extended reply message for route add
 *
 * AaSys GW will send this message to the application upon route registration.
 */
typedef struct AaSysComGwRegReplyExt
{
  TAaSysComSicad          localSicAddr;     /**< Applications own Sic address */
  TAaSysComSicad          remoteSicAddr;    /**< Sic address of remote application */
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
} AaSysComGwRegReplyExt;

/**
 * @brief message to remove route
 *
 * This message is sent by application to AaSyscom GW when a registered route
 * is wanted to be removed. The route removal is based on the RouteID that
 * was returned in the AASYSCOM_GW_REG_REPLY_MSG message, upon route registeration.
 */
typedef struct AaSysComGwDeRegReq
{
  TAaSysComGwRouteId      routeId;     /**< Route Identifier of the route to be removed */
} AaSysComGwDeRegReq;

/**
 * @brief reply message to route remove
 */
typedef struct AaSysComGwDeRegReply
{
  TAaSysComGwRouteId      routeId;     /**< Route Identifier of the route to be removed */
  /* above fields discarding the api_header will be copied to the reply from the request */
  EAaSysComGwStatus       status; /**< status of the operation */
} AaSysComGwDeRegReply;

/**
 * @brief communication failure indication
 *
 * This message is sent by AaSysCom Gw to the application in case GW notices
 * that message delivery failed. Message contains the original message that
 * were tried to send (accessed by the data field). AaSysCom GW does not
 * perform any auxiliary actions for this matter after it has send this message,
 * rest is up to the application.
 *
 * @note this feature is dependent of the fact the AaSysCom GW can detect such
 * situation from the transport protocol. If such information cannot be detected
 * then GW will not naturally send this message, thus communication failures will
 * not be detected by this layer.
 */
typedef struct AaSysComGwCommFailureInd
{
  EAaSysComGwStatus   status; /**< error code describing why delivery failed */
  /** following field is a special field ment for users to be able to point to
      the place in the message, where the actual message data starts (array of 4 bytes to make
      the struct padding divisible by 4). Length of data is
      api_header.length - sizeof(struct Api_header) */
  u8                data[4];      /**< accessory field for the original message */
} AaSysComGwCommFailureInd;

/**
 * @brief message to add a default route
 *
 * This message is used to register a default route. Each socket
 * can have a default route registered. There can be only one
 * default route registered per socket and if this message
 * is sent multiple times the last received one will be valid.
 *
 */
typedef struct AaSysComGwRegDefRouteReq
{
  SAaSysComGwIpAddress_deprecated   address;   /**< IP address/port that this default route applies */
  TAaSysComSicad                    receiver;  /**< Sic address of the default receiver */
  EAaSysComGwProtocol               protocol;  /**< information about the protocol used in link, e.g UDPCP, UDP, ... */
  u32                               msgID;     /**< message ID to be put into external messages when delivering to application */
} AaSysComGwRegDefRouteReq CCS_DEPRECATED("Use AaSysComGwRegDefRouteReqExt instead.");

/**
 * @brief message to add a default route available for both IPv4 and IPv6
 *
 * This message is used to register a default route. Each socket
 * can have a default route registered. There can be only one
 * default route registered per socket and if this message
 * is sent multiple times the last received one will be valid.
 *
 */
typedef struct AaSysComGwRegDefRouteReqExt
{
  SAaSysComGwIpAddressExt   address;          /**< IP address/port that this default route applies */
  TAaSysComSicad            receiver;         /**< Sic address of the default receiver */
  EAaSysComGwProtocol       protocol;         /**< information about the protocol used in link, e.g UDPCP, UDP, ... */
  u32                       msgID;            /**< message ID to be put into external messages when delivering to application */
  u32                       protocolDataLen;  /**< Length of protocol specific data.\n
                                                   This field should be set like sizeof( <protocol_specific_data_structure> ).\n
                                                   Value 0 means no protocol specific data is used */
  u8                        protocolData[1];  /**< Protocol specific data
                                                   This field can contain one of below structure:\n
                                                   AaSysComGwRegTcpParameters
                                                   AaSysComGwRegSctpParameters
                                                   AaSysComGwRegTcpExtParameters.\n
                                                   Field protocolDataLen indicates which structure is in use.
                                                   In case protocolDataLen equals 0 no protocol specific data is used. */
} AaSysComGwRegDefRouteReqExt;

/**
 * @brief Message to request route info.
 * CCS internal message. Not be be used by applications.
 * May and will change without any notice.
 */
typedef struct AaSysComGwRouteInfoReqExt
{
  u32 id;                   /**< Used to distinguish between multiple requests. */
  u32 returnRouteDetails;   /**< 0 - no route info, 1 - route info will be returned in reply message. */
} AaSysComGwRouteInfoReqExt;

/**
 * @brief reply message for default route add
 *
 * AaSysCom GW will send this message to the application upon default route registeration.
 */
typedef struct AaSysComGwRegDefRouteReply
{
  SAaSysComGwIpAddress_deprecated   address;     /**< IP address/port that this default route applies */
  TAaSysComSicad                    receiver;    /**< Sic address of the default receiver */
  EAaSysComGwProtocol               protocol;    /**< information about the protocol used in link, e.g UDPCP, UDP, ... */
  u32                               msgID;       /**< message ID to be put into external messages when delivering to application */
  /* above fields discarding the api_header will be copied to the reply from the request */
  EAaSysComGwStatus                 status;      /**< status of the operation */
  TAaSysComGwPortNum                port;        /**< port number (meaningful in case port number in request was zero) */
} AaSysComGwRegDefRouteReply CCS_DEPRECATED("Use AaSysComGwRegDefRouteReplyExt instead.");

/**
 * @brief reply message for default route add available for IPv4 and IPv6
 *
 * AaSysCom GW will send this message to the application upon default route registration.
 */
typedef struct AaSysComGwRegDefRouteReplyExt
{
  SAaSysComGwIpAddressExt   address;          /**< IP address/port that this default route applies */
  TAaSysComSicad            receiver;         /**< Sic address of the default receiver */
  EAaSysComGwProtocol       protocol;         /**< information about the protocol used in link, e.g UDPCP, UDP, ... */
  u32                       msgID;            /**< message ID to be put into external messages when delivering to application */
  /* above fields discarding the api_header will be copied to the reply from the request */
  EAaSysComGwStatus         status;           /**< status of the operation */
  TAaSysComGwPortNum        port;             /**< port number (meaningful in case port number in request was zero) */
  /* bellow fields will be copied to the reply from the request */
  u32                       protocolDataLen;  /**< Length of protocol specific data.\n
                                                   This field should be set like sizeof( <protocol_specific_data_structure> ).\n
                                                   Value 0 means no protocol specific data is used. */
  u8                        protocolData[1];  /**< Protocol specific data
                                                   This field can contain one of below structure:\n
                                                   AaSysComGwRegTcpParameters
                                                   AaSysComGwRegSctpParameters
                                                   AaSysComGwRegTcpExtParameters.\n
                                                   Field protocolDataLen indicates which structure is in use.
                                                   In case protocolDataLen equals 0 no protocol specific data is used. */
} AaSysComGwRegDefRouteReplyExt;

/**
 * @brief AaSysCom GW statistics enable/disable message.
 */
typedef struct AaSysComGwStatsReq
{
  u32 action;   /**< 0 - disable stats, 1 - enable stats */
} AaSysComGwStatsReq;


/**
 * @brief Reply message for deregister all routes request.
 */
typedef struct AaSysComGwDeregAllReply
{
  EAaSysComGwStatus status;     /**< status of operation */
} AaSysComGwDeregAllReply;

/**
 * @brief Message to request route info.
 *
 * CCS internal message. Not be be used by applications.
 * May and will change without any notice.
 */
typedef struct AaSysComGwRouteInfoReq
{
  u32 id;                   /**< Used to distinguish between multiple requests. */
  u32 returnRouteDetails;   /**< 0 - no route info, 1 - route info will be returned in reply message. */
} AaSysComGwRouteInfoReq CCS_DEPRECATED("Use AaSysComGwRouteInfoReqExt instead.");

/**
 * @brief AaSysCom GW route information.
 */
typedef struct AaSysComGwRouteInfo_deprecated
{
  TAaSysComGwRouteId                routeId;         /**< Route ID. */
  i32                               socketID;        /**< Socket ID this route is using. */
  TAaSysComSicad                    localSicAddr;    /**< Applications own SIC address. */
  TAaSysComSicad                    remoteSicAddr;   /**< SIC address of remote application. */
  SAaSysComGwIpAddress_deprecated   localIP;         /**< IP address of local application. */
  SAaSysComGwIpAddress_deprecated   remoteIP;        /**< IP address of remote application. */
  EAaSysComGwProtocol               protocol;        /**< Information about the protocol used in link, e.g UDPCP, UDP, TCP, ... */
  ERetainMsgHeader                  retainMsgHeader; /**< 1 if Msg header should be left intact to messages send. */
  u32                               msgID;           /**< Message ID to be put into external messages when delivering to application. */
  EAaSysComGwReliability            reliability;     /**< Route reliability information - currently unused and set to 0. */
} AaSysComGwRouteInfo_deprecated;
typedef AaSysComGwRouteInfo_deprecated AaSysComGwRouteInfo CCS_DEPRECATED("Use AaSysComGwRouteInfoExt instead.");

/**
 * @brief AaSysCom GW route information available for both IPv4 and IPv6.
 */
typedef struct AaSysComGwRouteInfoExt
{
  TAaSysComGwRouteId                routeId;          /**< Route ID. */
  i32                               socketID;         /**< Socket ID this route is using. */
  TAaSysComSicad                    localSicAddr;     /**< Applications own Sic address. */
  TAaSysComSicad                    remoteSicAddr;    /**< Sic address of remote application. */
  SAaSysComGwIpAddressExt           localIP;          /**< IP address of local application. */
  SAaSysComGwIpAddressExt           remoteIP;         /**< IP address of remote application. */
  EAaSysComGwProtocol               protocol;         /**< Information about the protocol used in link, e.g UDPCP, UDP, TCP, ... */
  ERetainMsgHeader                  retainMsgHeader;  /**< 1 if Msg header should be left intact to messages send. */
  u32                               msgID;            /**< Message ID to be put into external messages when delivering to application. */
  EAaSysComGwReliability            reliability;      /**< Route reliability information - currently unused and set to 0. */
  AaSysComGwRegProtocolParameters   protocolParams;   /**< Protocol specific data */
} AaSysComGwRouteInfoExt;

/**
 * @brief Reply message to route info request.
 *
 * CCS internal message. Not be be used by applications.
 * May and will change without any notice.
 */
typedef struct AaSysComGwRouteInfoReply
{
  u32 id;                                       /**< Used to distinguish between multiple requests. */
  u32 returnRouteDetails;                       /**< 0 - no route list, 1 - route list will be returned in reply message. */
  /* Above fields will be copied to the reply from the request. */
  EAaSysComGwStatus status;                     /**< Status of operation. */
  u32 routeCount;                               /**< Number of registered routes. Valid if status is EAaSysComGwStatus_OK. */
  u32 defaultRouteCount;                        /**< Number of registered default routes. Valid if status is EAaSysComGwStatus_OK. Currently unused. */
  AaSysComGwRouteInfo_deprecated routeInfo[1];  /**< Dynamic array with route info.
                                       Valid if status is EAaSysComGwStatus_OK and if returnRouteDetails was non zero. */
} AaSysComGwRouteInfoReply CCS_DEPRECATED("Use AaSysComGwRouteInfoReplyExt instead.");

/**
 * @brief Reply message to route info request.
 *
 * CCS internal message. Not be used by applications.
 * May and will change without any notice.
 *
 * @par Description:
 * In case detailed routes info take more than ~64kB (one syscom message)
 * response is divided into pieces of ~64kB, and all fragments of response
 * are sent one by one.
 * The last reply fragment has set replyCompleted to 1, in other fragments it is set to 0.
 * Receiver of message AASYSCOM_GW_ROUTE_INFO_EXT_REPLY_MSG might receive more than one message
 * and have to read all responses until replyCompleted!=1 without sending new request.
 */
typedef struct AaSysComGwRouteInfoReplyExt
{
  u32                       id;                 /**< Used to distinguish between multiple requests. */
  u32                       returnRouteDetails; /**< 0 - no route list, 1 - route list will be returned in reply message. */
  /* Above fields will be copied to the reply from the request. */
  EAaSysComGwStatus         status;             /**< Status of operation. */
  u32                       routeCount;         /**< Number of registered routes. Valid if status is EAaSysComGwStatus_OK. */
  u32                       defaultRouteCount;  /**< Number of registered default routes. Valid if status is EAaSysComGwStatus_OK. Currently unused. */
  u32                       replyCompleted;     /**< Indicates it is the last piece/fragment of reply */
  AaSysComGwRouteInfoExt    routeInfo[1];       /**< Dynamic array with route info.
                                                     Valid if status is EAaSysComGwStatus_OK and if returnRouteDetails was non zero. */
} AaSysComGwRouteInfoReplyExt;

/**
 * @brief message to add TCP route
 *
 * This message is sent by application to AaSysCom GW when a new TCP route
 * should be registered.
 */
typedef struct AaSysComGwRegTcpReq
{
  AaSysComGwRegReq_deprecated   routeParams;            /**< Usual parameters for creating any AaSysComGw route. */

  /* Additional parameters needed for TCP route setup. */
  EAaSysComGwTcpType            tcpRouteType;           /**< Either server or client. */
  u32                           messageSizePosition;    /**< Message size position in received stream. Special value
                                                   AASYSCOM_GW_TCP_TRANSPARENT_ROUTE means data is received transparently. */
  EMessageSizeLength            messageSizeLength;      /**< Number of bytes used for message size. */
  EMessageSizeFormat            messageSizeFormat;      /**< Message size format encoding. */
  EClientValidation             clientValidation;       /**< Relevant only for TCP server route type. */
} AaSysComGwRegTcpReq CCS_DEPRECATED("Use AaSysComGwRegReqExt instead.");

/**
 * @brief reply message for TCP route add
 *
 * AaSysCom GW will send this message to the application upon TCP route registration.
 */
typedef struct AaSysComGwRegTcpReply
{
  AaSysComGwRegReq_deprecated   routeParams;            /**< Usual parameters for creating any AaSysComGw route. */
  EAaSysComGwTcpType            tcpRouteType;           /**< Either server or client. */
  u32                           messageSizePosition;    /**< Message size position in received stream. */
  EMessageSizeLength            messageSizeLength;      /**< Number of bytes used for message size. */
  EMessageSizeFormat            messageSizeFormat;      /**< Message size format encoding. */
  EClientValidation             clientValidation;       /**< Relevant only for TCP server route type. */
  /* above fields discarding the api_header will be copied to the reply from the request */
  EAaSysComGwStatus             status;                 /**< status of the operation */
  TAaSysComGwRouteId            routeId;                /**< route ID of the added route (AASYSCOMGW_INVALID_ROUTE_ID if route add failed) */
} AaSysComGwRegTcpReply CCS_DEPRECATED("Use AaSysComGwRegReplyExt instead.");

/**
 * @brief Message with unknown sender
 *
 * This message is sent to the registrated default receiver incase route
 * mapping information for message sender does not exist is GW.
 * @note If default receiver is not registrated the message will be
 * ignored with an error log writing.
 */
typedef struct AaSysComGwUnknownSenderIndExt
{
  /** IP address, port and IP version of the original message sender */
    SAaSysComGwIpAddressExt sender;
  /** following field is a special field ment for users to be able to point
      to the place in the message, where the actual message data starts
      (array of 4 bytes to make the struct padding divisible by 4). Length
      of data is api_header.length - sizeof(struct Api_header) */
  u8 data[4]; /* dummy message payload accessory field */
} AaSysComGwUnknownSenderIndExt;


#ifndef AaSysComGwRouteSupervisionResp
/**
 * @brief   Supervision response message.
 *
 * Application will receive the message in order to inform about the status of (un)subscribing for transport events.
 */
typedef struct AaSysComGwRouteSupervisionResp
{
    EAaSysComGwRouteSubReqType  reqType;        /**< request type e.g. subscribe, unsubscribe */
    TAaSysComGwRouteId          routeId;        /**< route ID of the existing route */
    TAaSysComSicad              receiver;       /**< Sic address of the receiver that subscribes for transport events */
    EAaSysComGwStatus           status;         /**< status of the operation */
} AaSysComGwRouteSupervisionResp;

#endif

#ifndef AaSysComGwRouteSupervisionReq

typedef struct AaSysComGwRouteSupervisionReq
{
    EAaSysComGwRouteSubReqType  reqType;        /**< request type e.g. subscribe, unsubscribe */
    TAaSysComGwRouteId          routeId;        /**< route ID of the existing route */
    TAaSysComSicad              receiver;       /**< Sic address of the receiver that subscribes for transport events */
} AaSysComGwRouteSupervisionReq;

#endif

#ifndef AaSysComGwRouteSupervisionInd

typedef struct AaSysComGwRouteSupervisionInd
{
    TAaSysComGwRouteId      routeId;        /**< route ID of the existing route */
    EAaSysComGwRouteStatus  status;         /**< status of the route */
} AaSysComGwRouteSupervisionInd;

#endif

/** @} */
/** @} end: @addtogroup dgAaSysComGwMcuRt AaSysComGw MCU_RT*/

#ifdef __cplusplus
}
#endif

#endif /* IF_MCU_RT_AASYSCOM_GW_MSGS_H */
