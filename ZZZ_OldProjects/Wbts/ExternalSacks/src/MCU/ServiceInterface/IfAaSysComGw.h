/** @file
*   @brief MCU Interfaces of AaSysComGw
*   @copyright 2015 Nokia Networks. All rights reserved.
*   @copyright 2019 Nokia. All rights reserved.
*/
#ifndef IF_MCU_AASYSCOM_GW_H
#define IF_MCU_AASYSCOM_GW_H

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <glo_def.h>
#include <CcsCommon.h>
#include "../Definitions/IfAaSysCom_Defs.h"
#include "../Definitions/IfAaSysComGw_Defs.h"
#include "../Messages/IfAaSysComGw_Msg.h"
#include "../../COMMON/Definitions/IfAaSysComGw_Defs.h"
#include "../../SHARED/MCU_RT/ServiceInterface/IfAaSysComGw.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
 * @addtogroup dgAaSysComGwMcu AaSysComGw MCU
 * @ingroup dgAaSysCom
 *
 * Common Computer and Support SW SysCom Gateway.
 *
 * @{
 */

 /*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** @name AaSysComGw route configuration (MCU specific)
 * @{
 */

/**
********************************************************************************
*
* @brief	Convenience function to configure UDPCP routes.
*
* @param[in]    remoteIp	ip address of the remote node for which the route needs to be added.
*
*
* @param[in]    remoteNid	nid of the remote node for which the route needs to be added.
*
*
* @param[in]    masterIp	local ip address to be used in the route configuration.
*
*
* @param[in]    masterPort	the value to be used as both local and remote port in the route configuration.
*
*
* @return       Route id is returned. In case of errors
*               AASYSCOM_GW_INVALID_ROUTE_ID is returned.
*
* @par Description:
* Adds an IPv4/UDPCP route to another node, so that applications can communicate to the other node by sending syscom messages.
*
* @par Errors:
* Returns AASYSCOM_GW_INVALID_ROUTE_ID if the remoteIp or masterIp or masterPort is NULL and if the remoteNid is 0.
*
* @par Restrictions:
* No known restrictions.
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
********************************************************************************
**/
TAaSysComGwRouteId AaSysComGwAddRoute(const char *remoteIp,TAaSysComNid remoteNid, char *masterIp, u32 *masterPort);

/**
********************************************************************************
*
* @brief	Convenience function to configure SCTP routes.
*
* @param[in]    remoteIp	ip address of the remote node for which the route needs to be added.
*
*
* @param[in]    remoteNid	nid of the remote node for which the route needs to be added.
*
*
* @param[in]    masterIp	local ip address to be used in the route configuration.
*
*
* @param[in]    masterPort	the value to be used as both local and remote port in the route configuration.
*
*
* @return       Route id is returned. In case of errors
*               AASYSCOM_GW_INVALID_ROUTE_ID is returned.
*
* @par Description:
* Adds an IPv4/SCTP route to another node, so that applications can communicate to the other node by sending syscom messages.
*
* @par Errors:
* Returns AASYSCOM_GW_INVALID_ROUTE_ID if the remoteIp or masterIp or masterPort is NULL and if the remoteNid is 0.
*
* @par Restrictions:
* No known restrictions.
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
********************************************************************************
**/
TAaSysComGwRouteId AaSysComGwAddRouteSCTP(const char *remoteIp,TAaSysComNid remoteNid, char *masterIp, u32 *masterPort);

/**
********************************************************************************
*
* @brief	removes route to an another node
*
*
* @param[in]    routeId	id of the route which has to be removed
*
*
* @return       true if operation succeed, else otherwise
*
* @par Description:
* The AaSysComGwRemoveRoute() function retrieves the route id and removes the route for the given route id.
*
* @par Errors:
* returns false if route cannot be removed.
*
* @par Restrictions:
* No known restrictions.
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
********************************************************************************
**/
GLO_BOOLEAN AaSysComGwRemoveRoute(TAaSysComGwRouteId routeId);

/**
********************************************************************************
*
* @brief fetches the IP address given the Node ID
*
* @param[in]    nid  nid of the remote node for which the IPAddress is to be fetched
*
*
* @param[in]    buf  buffer allocated for size AASYSCOM_GW_IPV4_ADDRESS_STR_LEN
*
* @return       true if IPAddress mapping is found; false if no entry is found
*
* @par Description:
* The AaSysComGwGetIpAddressFromNid() function retrieves the remote IP Address given the Node ID
*
* @par Errors:
* No errors are defined apart from false in case of return
*
* @par Restrictions:
* No known restrictions.
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
********************************************************************************
**/
GLO_BOOLEAN AaSysComGwGetIpAddressFromNid(TAaSysComNid nid, char* buf) CCS_DEPRECATED("Do not use this function.");

/**
********************************************************************************
*
* @brief    Adds a route to another node, so that applications can communicate with the other node by sending syscom messages.
*
* @param[in]    remoteIp        IP address of the remote endpoint of the route.
*
*
* @param[in]    remotePort      Port number of the remote endpoint of the route.
*
*
* @param[in]    remoteSicAddr   Remote sic address mask for which the route needs to be added.
*
*
* @param[in]    localIp         IP address of local endpoint of the route.
*
*
* @param[in]    localPort       Port number of the local endpoint of the route.
*
*
* @param[in]    localSicAddr    Local sic address mask for which the route needs to be added.
*
*
* @param[in]    retainMsgHeader Messages to be transmitted with/without SIC headers
*
*
* @param[in]    msgID           Msg ID for messages received without SIC header
*
*
* @param[in]    reliability     Underlying transport protocol to be used in reliable/unreliable mode
*
*
* @param[in]    protocol        Protocol used to communicate with the remote node.
*
*
* @param[in]    ipVersion       Version of IP protocol to be used as underlying transport.
*
*
* @return       Actual route id is returned on success. In case of errors
*               AASYSCOM_GW_INVALID_ROUTE_ID is returned.
*
* @par Description:
* The AaSysComGwAddRouteExt() function establishes a SysComGW route between local node and 
* a remote node so that applications can communicate with the other node by sending syscom messages.
*
* @par Errors:
* returns AASYSCOM_GW_INVALID_ROUTE_ID in any of the following cases: remoteIp or localIp is NULL,
* remotePort or localPort not in range (0,65535], invalid protocol, invalid IP version, 
* identical route already exists, internal SysComGW error
*
* @par Restrictions:
* No known restrictions.
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
********************************************************************************
**/
TAaSysComGwRouteId AaSysComGwAddRouteExt(const char *remoteIp, const u32 remotePort, const TAaSysComSicad remoteSicAddr, const char *localIp, const u32 localPort, const TAaSysComSicad localSicAddr, const ERetainMsgHeader retainMsgHeader, const u32 msgID, const EAaSysComGwReliability  reliability, const EAaSysComGwProtocol protocol, const EAaSysComGwIpVer ipVersion);

/**
********************************************************************************
*
* @brief    Adds a route to another node, so that applications can communicate with the other node by sending syscom messages.
*
* @param[in]    reqRegLpm   Extended message (with remote SIC address as mask) to add a route.
*
* @return       Actual route id is returned on success. In case of errors
*               AASYSCOM_GW_INVALID_ROUTE_ID is returned.
*
* @par Description:
* The AaSysComGwAddRouteExtLpm() function establishes a SysComGW route between local node and
* a remote node so that applications can communicate with the other node by sending syscom messages.
* Remote SIC address is defined as address mask, with explicit amount of most significant bits to be
* compared with the message receive address when matching the route for an outbound message.
*
* Example:
*
* Assume that three routes are added:
* - Route 1: for RSIC 0x1011 1234 with 32 - all bits will be used to find the match;
* - Route 2: for RSIC 0x1011 1234 with 16 - 16, most significant bits (0x1011) will be used to find the match;
* - Route 3: for RSIC 0x1011 1233 with 12 - 12, most significant bits (0x101) will be used to find the match.
*
* Assuming that the message is send to 0x1011 1233, the route will be selected as follow:
* - Route 1 will be skipped - not all bits matches;
* - Route 2 will be used - 16 most significant bits matches;
* - In route 3, exactly the same RSIC was given, but only 12 most significant are used in comparison
*   (the rest is not significant), so the route will not be used.
*
* Additional description can be found in SysComGw API specification.
*
* @par Errors:
* returns AASYSCOM_GW_INVALID_ROUTE_ID in any of the following cases: remoteIp or localIp is NULL,
* remotePort or localPort not in range (0,65535], invalid protocol, invalid IP version,
* identical route already exists, internal SysComGW error
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* LTE2959.
*
* @par Future directions:
* None.
*
********************************************************************************
**/
TAaSysComGwRouteId AaSysComGwAddRouteLpm(const AaSysComGwRegReqLpm *reqRegLpm);

/**
********************************************************************************
*
* @brief    Subscribe for route events on default route.
*
* @param[in]    localIp         local IP address on which user subscribes.
* @param[in]    protocol        protocol on which user subscribes.
* @param[in]    subscriber      SIC address that will receive events.
* @param[in]    transactionID   transaction identifier.
*
* @return       Success:    EAaSysComGwStatus_Ok.
*               Failure:    EAaSysComGwStatus with reason of the failure.
*
* @par Description:
* The AaSysComGwSubscribeForEventsDefRoute() function sends supervision request toward SysComGw
* in order to subscribe (on specified local IP address and protocol) for link events that will be
* received by given subscriber (SIC address and transaction identifier).
*
* Structure EAaSysComGwRouteStatus defines possible events that can be received.
*
* @par Errors:
* EAaSysComGwStatus_Ok is returned in case of success. Otherwise, proper error is returned.
*
* @par Restrictions:
* User shall ensure that transaction id is unique - i.e. user shall not
* subscribe for default route A and default route B with the same transaction id
* as it will fail to match transaction id to proper (A or B) default route data
* in user context.
*
* From LBT4089-A-b, only TCP is supported.
*
* @par Usage:
* None.
*
* @par Rationale:
* LBT4089-A-b.
*
* @par Future directions:
* None.
*
********************************************************************************
**/
EAaSysComGwStatus AaSysComGwSubscribeForEventsDefRoute(const SAaSysComGwIpAddressExt localIp,
        const EAaSysComGwProtocol protocol, const TAaSysComSicad subscriber, const u32 transactionId);

/**
********************************************************************************
*
* @brief    Unsubscribe for route events on default route.
*
* @param[in]    localIp         local IP address on which user subscribed.
* @param[in]    protocol        protocol on which user subscribed.
* @param[in]    subscriber      SIC address that is receiving events.
* @param[in]    transactionID   transaction identifier.
*
* @return       Success:    EAaSysComGwStatus_Ok.
*               Failure:    EAaSysComGwStatus with reason of the failure.
*
* @par Description:
* The AaSysComGwUnsubscribeFromEventsDefRoute() function sends supervision request toward SysComGw
* in order to unsubscribe (on specified local IP address and protocol) for link events that are
* received by given subscriber (SIC address and transaction identifier).
*
* @par Errors:
* EAaSysComGwStatus_Ok is returned in case of success. Otherwise, proper error is returned.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* LBT4089-A-b.
*
* @par Future directions:
* None.
*
********************************************************************************
**/
EAaSysComGwStatus AaSysComGwUnsubscribeFromEventsDefRoute(const SAaSysComGwIpAddressExt localIp,
        const EAaSysComGwProtocol protocol, const TAaSysComSicad subscriber, const u32 transactionId);

/** @} */

/** @} end: @addtogroup dgAaSysComGwMcu AaSysComGw MCU */

#ifdef __cplusplus
}
#endif

#endif /* IF_MCU_AASYSCOM_GW_H */
