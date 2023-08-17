/** @file
*   @brief Header file for SysComUdsLink message external interface
*
*   $Copyright: 2018 Nokia. All rights reserved.$
*/

#ifndef IF_MCU_AASYSCOMUDSLINK_MSGS_H_
#define IF_MCU_AASYSCOMUDSLINK_MSGS_H_

#include <glo_def.h>
#include <CcsCommon.h>
#include <TAaSysComSicad.h>
#include "../Definitions/IfAaSysComUdsLink_Defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaSysComLink AaSysComUdsLink MCU
 * @ingroup dgAaSysComLink
 *
 * @{
 */

 /*----------------------- PUBLIC DECLARATIONS --------------------------------*/

 /** @name Interface messages (MCU specific)
 * @{
 */

#define AASYSCOM_UDS_LINK_ROUTE_REG_REQ_MSG     0x154f /* !- SIGNO(struct SAaSysComUdsLinkRouteRegReq) -! */
#define AASYSCOM_UDS_LINK_ROUTE_REG_RESP_MSG    0x1550 /* !- SIGNO(struct SAaSysComUdsLinkRouteRegResp) -! */
#define AASYSCOM_UDS_LINK_ROUTE_DEREG_REQ_MSG   0x1551 /* !- SIGNO(struct SAaSysComUdsLinkRouteDeregReq) -! */
#define AASYSCOM_UDS_LINK_ROUTE_DEREG_RESP_MSG  0x1552 /* !- SIGNO(struct SAaSysComUdsLinkRouteDeregResp) -! */

/**
 * @brief Message to add UDS route
 *
 * This message is sent to AaSysComUdsLink when UDS route is required to be registered.
 */
typedef struct SAaSysComUdsLinkRouteRegReq
{
  TAaSysComSicad            localSicAddr;         /**< Applications own Sic address */
  TAaSysComSicad            remoteSicAddr;        /**< Sic address of remote application */
  u32                       remoteSicValidBits;   /**< Number of valid bits in remote SIC address */
  TAaSysComSicad            peerSicAddr;          /**< Sic address of UDS peer to reroute message */
  EAaSysComUdsLinkRouteType udsRouteType;         /**< Define route behavior */
} SAaSysComUdsLinkRouteRegReq;

/**
 * @brief Reply message for UDS route add
 *
 * AaSysComUdsLink will send this message back to requesting application upon route registration.
 */
typedef struct SAaSysComUdsLinkRouteRegResp
{
  TAaSysComSicad            localSicAddr;         /**< Applications own Sic address */
  TAaSysComSicad            remoteSicAddr;        /**< Sic address of remote application */
  u32                       remoteSicValidBits;   /**< Number of valid bits in remote SIC address */
  TAaSysComSicad            peerSicAddr;          /**< Sic address of UDS peer to reroute message */
  EAaSysComUdsLinkRouteType udsRouteType;         /**< Define route behavior */
  EAaSysComUdsLinkStatus    status;               /**< status of the operation */
  TAaSysComUdsLinkRouteId   routeId;              /**< route ID of the added route (AASYSCOM_LINK_INVALID_ROUTE_ID if route add failed) */
} SAaSysComUdsLinkRouteRegResp;

/**
 * @brief Message to remove UDS route
 *
 * This message is sent to AaSysComUdsLink when a registered route is requested to be removed.
 * The route removal is based on the TAaSysComUdsLinkRouteId that was returned in
 * the AASYSCOM_LINK_ROUTE_REG_RESP_MSG message, upon route registration.
 */
typedef struct SAaSysComUdsLinkRouteDeregReq
{
    TAaSysComUdsLinkRouteId      routeId;     /**< Route Identifier of the UDS route to be removed */
} SAaSysComUdsLinkRouteDeregReq;

/**
 * @brief Reply message to UDS route remove
 */
typedef struct SAaSysComUdsLinkRouteDeregResp
{
    TAaSysComUdsLinkRouteId   routeId;     /**< Route Identifier of the UDS route to be removed */
    EAaSysComUdsLinkStatus    status;      /**< status of the operation */
} SAaSysComUdsLinkRouteDeregResp;

/** @} */

/** @} end: @addtogroup dgAaSysComLinkMcu AaSysComUdsLink MCU */

#ifdef __cplusplus
}
#endif

#endif // IF_MCU_AASYSCOMUDSLINK_MSGS_H_
