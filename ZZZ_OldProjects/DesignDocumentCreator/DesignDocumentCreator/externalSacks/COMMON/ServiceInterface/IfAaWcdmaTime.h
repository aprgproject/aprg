/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaWcdmaTime interface header file
* @module                AaWcdmaTime
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _IFAAWCDMATIME_H
#define _IFAAWCDMATIME_H
#include "CcsCommon.h"

#ifdef CCS_NEW_IF_STRUCTURE
#include <IfAaWcdmaTime_Defs.h>
#endif
/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
*@defgroup dgAaWcdmaTime WCDMA Time Services (AaWcdmaTime)
*@ingroup dgCommonApplicationUtilitiesSw
*
* Common Computer and Support SW WCDMA Time Service.
*
* This service provides WCDMA frame time based time and timeout services.
*
* CC&S Wiki: http://wikis.inside.nokiasiemensnetworks.com/bin/view/CSSWiki/AaWcdmaTime
* 
*/

/** 
* @defgroup dpAaWcdmaTimeErrors Exception codes
* @ingroup dgAaWcdmaTime
*
* OSEck (DSP) AaWcdmaTime implementation reports errors via local Fault Manager.
* Error codes can be found from DSP HWAPI ENV (EDspPlatErrCause.h and
* EDspPlatComp.h).
*
*/

/**
*@defgroup dgAaWcdmaTimeApi API
*@ingroup dgAaWcdmaTime
*
* Application Programming Interface.
* 
* API specification (current): https://sharenet-ims.int.net.nokia.com/Open/D-171133
*
*@{*/

/*----------------------- INCLUDED FILES --------------------------------------*/

#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PUBLIC INTERFACES ---------------------------------*/
/**
 * @defgroup dgAaWcdmaTimeApiCommon AaWcdmaTime COMMON API
 * @ingroup  dgAaWcdmaTime
 */

/* @{ */
/**
*******************************************************************************
*   
*   @brief      Deletes the pending timer request.
*
*   @param[in]  timerId     The timer identifier.
*
*   @return     EAaWcdmaTimeRetVal_NoError or EAaWcdmaTimeRetVal_Error
*
*   @par Description:
*   Function deletes a pending timer request according the given timer
*   identifier. If the timer is not found (e.g. one-shot timer has been
*   triggered already), the function returns an error value. If message timer
*   has elapsed, but the message is not yet handled (is in the user's message
*   queue), message is not released.
*
*   @par Errors:
*   AaWcdmaTimerDelete() function has fail if:
*   [EAaWcdmaTimeRetVal_Error] The requested timer has not been found and any
*                              timers have not been deleted.
*
*   @par Restrictions:
*   Identifier of deleted timer can be reused later, when new timers are
*   created. Identifier is not reused right away, but in some phase identifier
*   may be used again.
*
*   @par Example:
*   @code
*   // Here is the usage example for the function.
*   AaWcdmaTimerDelete( timerId );
*   @endcode
*
*   @par Usage:
*   Any allocated memory blocks for the parameters of the callback or recovery
*   function are not released by this function. If message timer is deleted with
*   using this method, the message is released automatically by using the method
*   of the AaSysCom. 
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see
*   AaWcdmaTimermCreate, AaWcdmaTimermMatchCreate, AaWcdmaTimermSyncCreate,
*   AaWcdmaTimercCreate, AaWcdmaTimercMatchCreate, AaWcdmaTimercSyncCreate,
*   AaWcdmaTimermDelete
* 
*******************************************************************************/
EAaWcdmaTimeRetVal AaWcdmaTimerDelete(const TAaWcdmaTimerId timerId);

/* @} */

/*----------------------- CC&S INTERNAL INTERFACES ---------------------------*/
/**
*******************************************************************************
*
*   @brief      Starts AaWcdmaTime service on Ce level
*
*   @return     #EAaWcdmaTimeRetVal_NoError when startup successful.
*               #EAaWcdmaTimeRetVal_Error when startup has failed.
*
*******************************************************************************/
EAaWcdmaTimeRetVal AaWcdmaTimeCeStartup(void);

/**
*******************************************************************************
*
*   @brief      Starts AaWcdmaTime service on Ee level
*
*   @return     #EAaWcdmaTimeRetVal_NoError when startup successful.
*               #EAaWcdmaTimeRetVal_Error when startup has failed.
*
*******************************************************************************/
EAaWcdmaTimeRetVal AaWcdmaTimeEeStartup(void);

#ifdef __cplusplus
}
#endif

/**@}*/

#endif /*  _IFAAWCDMATIME_H */

