/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2017 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_IF_AACONFIG_TAG_H_
#define _MCU_IF_AACONFIG_TAG_H_

#include <CcsCommon.h>
#include <TAaSysComSicad.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include "../../COMMON/ServiceInterface/IfAaConfigTag.h"
#include "../../SHARED/MCU_RT/ServiceInterface/IfAaConfigTag.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaConfigTagApiMcu AaConfigTag MCU functions
 * @ingroup dgAaConfigTagApi
 */
/*@{*/

/**
****************************************************************************************
*
*   @brief    AaConfigTag service SIC address getter for messages based API usage.
*
*   @return  AaConfigTag service SIC address.
*
*   @par Description:
*   Function returns SIC address of AaConfigTag service.\n
*   The returned SIC address can be used to communicate with AaConfigTag service, using messages based API.
*
*   @par Errors:
*   - AASYSCOM_ADDRESS_INVALID - AaConfigTag service is not initialized and its SIC address is not set.
*
*   @par Restrictions:
*   EE start up must be completed before this function can be used.
*
*   @par Examples:
*
*   @code
*   TAaSysComSicad configTagSicad = AaConfigTagEeGetSicad();
*   if (AASYSCOM_ADDRESS_INVALID != configTagSicad)
*   {
*       TAaSysComCpid myCpId = AaSysComEuUserRegister(AASYSCOM_CP_INVALID);
*       TAaSysComSicad mySicad = AaSysComSicadGet(myCpId, AaSysComGetOwnNid());
*       void* msg = AaSysComMsgCreate(AACONFIG_TAG_GET_REQ_MSG,
*                                     sizeof(SAaConfigTagGetReqMsg),
*                                     configTagSicad);
*       SAaConfigTagGetReqMsg* getReq =
*           (SAaConfigTagGetReqMsg*)AaSysComMsgGetPayload(msg);
*       if (GLO_NULL != getReq)
*       {
*          getReq->type = u32_type;
*          strncpy(getReq->name,
*                  AACONFIG_TAG_CCS_RAT_MODE_ENABLED,
*                  sizeof(getReq->name));
*          getReq->name[sizeof(getReq->name) - 1)] = '\0';
*
*          PrepareSend_SAaConfigTagGetReqMsg(msg);
*          AaSysComMsgSendS(&msg, mySicad);
*       }
*   }
*   @endcode
*
*   @par Usage:
*   The API function shall be used by applications communicating with AaConfigTag service using messages based API.
*   The API function shall be preferred over the static @ref AACONFIG_TAG_MASTER_CPID address.
*
*   @par Rationale:
*   The static @ref AACONFIG_TAG_MASTER_CPID address belongs to AaConfigTag service instance running in context of CC&S EE.
*   AaConfigTag service instance running in scope of application EE uses dynamic address.
*   Application shall use the @ref AaConfigTagEeGetSicad API function to get the dynamic SIC address of AaConfigTag service instance from own EE.
*   The static @ref AACONFIG_TAG_MASTER_CPID address can be used by testing tools,
*   external applications not having access to @ref AaConfigTagEeGetSicad API function and applications running on remote node.
*
*   @par Future directions:
*   None
*
*   @see AACONFIG_TAG_GET_REQ_MSG
*   @see AACONFIG_TAG_GET_RESP_MSG
*   @see AACONFIG_TAG_SET_REQ_MSG
*   @see AACONFIG_TAG_SET_RESP_MSG
*   @see AACONFIG_TAG_DELETE_REQ_MSG
*   @see AACONFIG_TAG_DELETE_RESP_MSG
*
***************************************************************************************/
TAaSysComSicad AaConfigTagEeGetSicad(void);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  //_MCU_IF_AACONFIG_TAG_H_
