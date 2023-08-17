/** @file
*   @brief Header file for SysComUdsLink definitions external interface
*
*   $Copyright: 2018 Nokia. All rights reserved.$
*/

#ifndef IF_MCU_AASYSCOMUDSLINK_DEFS_H_
#define IF_MCU_AASYSCOMUDSLINK_DEFS_H_

#include <glo_def.h>
#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
 * @addtogroup dgAaSysComLink AaSysComUdsLink MCU
 * @ingroup dgAaSysComLink
 *
 * @{
 */

 /*----------------------- PUBLIC DECLARATIONS --------------------------------*/


/** @name Interface types (MCU specific)
 * @{
 */

/**
******************************************************************************
*
* @verbatim
* Tag name:         ccs.service.aasyscom.socketlink.uds_routing
*
* Direction:        input
*
* Description:      This flag enables/disables routing via UDS sockets.
*                   As default it is disabled.
*
* Effect analysis:  If not set, routing via UDS socket is not possible.
*                   Only delivering to destination node is realized.
*
* Restriction:      Concerns only messages routed via AASYSCOM_SOCKET_LINK
*                   and via UDS. Value of this tag is read only in startup phase.
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <0, 1>
*
* Define:           AASYSCOM_CONFIG_TAG_SOCKETLINK_UDS_ROUTING
*
* See:              none
* @endverbatim
*****************************************************************************/
#define AASYSCOM_CONFIG_TAG_SOCKETLINK_UDS_ROUTING "ccs.service.aasyscom.socketlink.uds_routing"

/**
******************************************************************************
*
* @verbatim
* Tag name:         ccs.service.aasyscom.socketlink.msg_size_threshold
*
* Direction:        input
*
* Description:      The flag sets message size threshold in bytes. Socket receiver
*                   allocates AASYSCOM_MAXPAYLOADSIZE size message and receives
*                   the data to the buffer. If socket receiver receives more
*                   than message size threshold, message is sent immediately (the whole
*                   buffer). Otherwise, if socket receiver receives less or equal to
*                   message size threshold, message with proper size is created and
*                   then sent. Performance gain in cost of memory.
*
* Effect analysis:  If not set, default value is used (8192 bytes).
*                   Configuration tag can be changed in runtime as callback is registered.
*
* Restriction:      No restrictions.
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <0, AASYSCOM_MAXPAYLOADSIZE>
*
* Define:           AASYSCOM_CONFIG_TAG_SOCKETLINK_MSG_SIZE_THRESHOLD
*
* See:              none
* @endverbatim
*****************************************************************************/
#define AASYSCOM_CONFIG_TAG_SOCKETLINK_MSG_SIZE_THRESHOLD "ccs.service.aasyscom.socketlink.msg_size_threshold"

/** @brief invalid value for route ID */
#define AASYSCOM_UDSLINK_INVALID_ROUTE_ID 0

/** @brief AaSysCom UDS Link route ID type to identify a route */
typedef u32 TAaSysComUdsLinkRouteId;

/** @brief AaSysCom UDS Link status */
typedef enum EAaSysComUdsLinkStatus
{
  EAaSysComUdsLinkStatus_OK                    = 0,  /**< success, no error */
  EAaSysComUdsLinkStatus_NoRouteExists         = 1,  /**< route is not found for message that was trying to be sent */
  EAaSysComUdsLinkStatus_RouteAlreadyExists    = 2,  /**< route has already been registered before */
  EAaSysComUdsLinkStatus_InvalidParam          = 3,  /**< invalid parameter */
  EAaSysComUdsLinkStatus_RouteIdsExhausted     = 4,  /**< all route IDs are reserved, new route can not be registered */
  EAaSysComUdsLinkStatus_OffendingRoute        = 5,  /**< route is offending with other route */
  EAaSysComUdsLinkStatus_InternalError         = 6,  /**< internal error */
  EAaSysComUdsLinkStatus_Unknown               = 7   /**< unknown/non-classified error */
} EAaSysComUdsLinkStatus;

/** @brief UDS route type */
typedef enum EAaSysComUdsLinkRouteType
{
  EAaSysComUdsLinkRouteType_Server          = 0,   /**< UDS server */
  EAaSysComUdsLinkRouteType_Client          = 1    /**< UDS client */
} EAaSysComUdsLinkRouteType;

/** @} */

/** @} end: @addtogroup dgAaSysComUdsLinkMcu AaSysComLink MCU */

#ifdef __cplusplus
}
#endif

#endif /* IF_MCU_AASYSCOMUDSLINK_DEFS_H_ */
