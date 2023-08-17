/* ****************************************************************************
 * @brief  AaSysCom GW interface
 * @module AaSysCom
 * @owner  Vedran Cundekovic
 *
 * Copyright 2014 Nokia Solutions and Networks. All rights reserved.
 * ****************************************************************************/

#ifndef IF_MCU_RT_AASYSCOM_GW_H
#define IF_MCU_RT_AASYSCOM_GW_H

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <glo_def.h>
#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CCS_NEW_IF_STRUCTURE
#include "../Definitions/IfAaSysCom_Defs.h"
#include "../Definitions/IfAaSysComGw_Defs.h"
#include "../Messages/IfAaSysComGw_Msg.h"
#endif

/*----------------------- PRIVATE DECLARATIONS -------------------------------*/

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/


/**
********************************************************************************
*
* @brief    Subscribe for route events.
* @par Restrictions: route supervision is supported by CC&S-MCU and RCP CC&S-RT
* @param[in]    routeId     Existing route id on which events will be received.
* @param[in]    subscriber  SIC address that will receive events.
*
* @return       Success:    EAaSysComGwStatus_Ok.
*               Failure:    EAaSysComGwStatus with reason of the failure.
*
* @par Description:
* The AaSysComGwSubscribeForEvents() function sends supervision request toward SysComGw
* in order to subscribe (on specified route id) for link events that will be received by
* given SIC address (subscriber).
*
* Structure EAaSysComGwRouteStatus defines possible events that can be received.
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
* LTE3022.
*
* @par Future directions:
* None.
*
********************************************************************************
**/
EAaSysComGwStatus AaSysComGwSubscribeForEvents(TAaSysComGwRouteId routeId, TAaSysComSicad subscriber);

/**
********************************************************************************
*
* @brief    Unsubscribe for route events.
* @par Restrictions: route supervision is supported by CC&S-MCU and RCP CC&S-RT
* @param[in]    routeId     Existing route id on which events are being received.
* @param[in]    subscriber  SIC address that is receiving events.
*
* @return       Success:    EAaSysComGwStatus_Ok.
*               Failure:    EAaSysComGwStatus with reason of the failure.
*
* @par Description:
* The AaSysComGwUnsubscribeFromEvents() function sends supervision request toward SysComGw
* in order to unsubscribe (on specified route id) for link events that are received by
* given SIC address (subscriber).
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
* LTE3022.
*
* @par Future directions:
* None.
*
********************************************************************************
**/
EAaSysComGwStatus AaSysComGwUnsubscribeFromEvents(TAaSysComGwRouteId routeId, TAaSysComSicad subscriber);

#ifdef __cplusplus
}
#endif

#endif /* IF_MCU_RT_AASYSCOM_GW_H */
