/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2018 Nokia. All rights reserved.
*******************************************************************************/

#ifndef IF_MCU_AASYSCOM_KERNELGW_H
#define IF_MCU_AASYSCOM_KERNELGW_H

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <glo_def.h>
#include <CcsCommon.h>
#include "../Definitions/IfAaSysCom_Defs.h"
#include "../Definitions/IfAaSysComKernelGw_Defs.h"
#include "../Messages/IfAaSysComGw_Msg.h"
#include "../../COMMON/Definitions/IfAaSysComGw_Defs.h"
#include "../../SHARED/MCU_RT/ServiceInterface/IfAaSysComGw.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
 * @addtogroup dgAaSysComKernelGwMcu AaSysComKernelGw MCU
 * @ingroup dgAaSysComKernelGw
 *
 * Common Computer and Support SW SysCom Kernel Gateway.
 *
 * @{
 */

 /*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** @name AaSysComKernelGw route configuration (MCU specific)
 * @{
 */

/**
********************************************************************************
*
* @brief	removes route to another node
*
*
* @param[in]    routeId	id of the route which has to be removed
*
*
* @return       GLO_TRUE: Succeed to remove route.
*               GLO_FALSE: Failed to remove route.
*
* @par Description:
* The AaSysComKernelGwRemoveRoute() function removes the route for the given route id.
*
* @par Errors:
* returns GLO_FALSE if route cannot be removed and relevant message is printed into log.
*
* @par Restrictions:
* No restrictions.
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
TBoolean AaSysComKernelGwRemoveRoute(TAaSysComGwRouteId routeId);

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
* @param[in]    remoteSicAddr   Remote SIC address mask for which the route needs to be added.
*
*
* @param[in]    localIp         IP address of local endpoint of the route.
*
*
* @param[in]    localPort       Port number of the local endpoint of the route.
*
*
* @param[in]    localSicAddr    Local SIC address mask for which the route needs to be added.
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
* The AaSysComKernelGwAddRouteExt() function establishes a SysComKernelGW route between local node and
* a remote node so that applications can communicate with the other node by sending syscom messages.
*
* @par Errors:
* returns AASYSCOM_GW_INVALID_ROUTE_ID in any of the following cases: remoteIp or localIp is GLO_NULL,
* remotePort or localPort not in range (0,65535], invalid protocol, invalid IP version,
* identical route already exists, internal SysComKernelGW error
*
* @par Restrictions:
* No restrictions.
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
TAaSysComGwRouteId AaSysComKernelGwAddRouteExt(const char *remoteIp, const u32 remotePort, const TAaSysComSicad remoteSicAddr, const char *localIp, const u32 localPort, const TAaSysComSicad localSicAddr, const ERetainMsgHeader retainMsgHeader, const u32 msgID, const EAaSysComGwReliability  reliability, const EAaSysComGwProtocol protocol, const EAaSysComGwIpVer ipVersion);

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
* The AaSysComKernelGwAddRouteLpm() function establishes a SysComKernelGW route between local node and
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
* Additional description can be found in AaSysComKernelGw and AaSysComGw API specifications.
*
* @par Errors:
* returns AASYSCOM_GW_INVALID_ROUTE_ID in any of the following cases: remoteIp or localIp is GLO_NULL,
* remotePort or localPort not in range (0,65535], invalid protocol, invalid IP version,
* identical route already exists, internal SysComKernelGW error
*
* @par Restrictions:
* No restrictions.
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
TAaSysComGwRouteId AaSysComKernelGwAddRouteLpm(const AaSysComGwRegReqLpm *reqRegLpm);

/** @} */

/** @} end: @addtogroup dgAaSysComKernelGwMcu AaSysComKernelGw MCU */

#ifdef __cplusplus
}
#endif

#endif /* IF_MCU_AASYSCOM_KERNELGW_H */
