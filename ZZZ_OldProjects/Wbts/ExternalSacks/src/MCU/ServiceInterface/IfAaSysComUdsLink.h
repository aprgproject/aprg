/** @file
*   @brief Header file for SysComUdsLink external interface
*
*   $Copyright: 2018 Nokia. All rights reserved.$
*/
#ifndef CCS_SERVICES_AASYSCOM_SRC_LINKHANDLER_IFAASYSCOMUDSLINK_H_
#define CCS_SERVICES_AASYSCOM_SRC_LINKHANDLER_IFAASYSCOMUDSLINK_H_

#include <glo_def.h>
#include <CcsCommon.h>
#include "../Definitions/IfAaSysComUdsLink_Defs.h"
#include "../Messages/IfAaSysComUdsLink_Msg.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/
/**
 * @addtogroup dgAaSysComLink AaSysComUdsLink MCU
 * @ingroup dgAaSysComLink
 *
 * Common Computer and Support SW SysCom dynamic Uds link configuration.
 *
 * @{
 */

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** @name Interface functions (MCU specific)
 * @{
 */

/**
 * @brief   CCS MCU API to add UDS route
 *
 * @param[in]    request           structure describes all parameters required to add new route
 * @param[out]   operationStatus   optional parameter to get status
 * @return  New route id on success, otherwise AASYSCOM_LINK_INVALID_ROUTE_ID
 */
TAaSysComUdsLinkRouteId AaSysComUdsLinkAddRoute(const SAaSysComUdsLinkRouteRegReq* const request, EAaSysComUdsLinkStatus* const operationStatus);

/**
 * @brief   CCS MCU API to remove UDS route
 *
 * @param[in]    routeId           Route Identifier of the UDS route to be removed
 * @return  EAaSysComUdsLinkStatus_OK on success, otherwise value to check failure reason
 */
EAaSysComUdsLinkStatus AaSysComUdsLinkRemoveRoute(const TAaSysComUdsLinkRouteId routeId);

/** @} */

/** @} end: @addtogroup dgAaSysComUdsLinkMcu AaSysComUdsLink MCU */

#ifdef __cplusplus
}
#endif

#endif /* CCS_SERVICES_AASYSCOM_SRC_LINKHANDLER_IFAASYSCOMUDSLINK_H_ */
