/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_IFAAWCDMATIME_H
#define _MCU_IFAAWCDMATIME_H
#include "CcsCommon.h"
#ifdef CCS_NEW_IF_STRUCTURE
#include <../../COMMON/ServiceInterface/IfAaWcdmaTime.h>
#include <../../SHARED/MCU_RT/ServiceInterface/IfAaWcdmaTime.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaWcdmaTimeApiMcu AaWcdmaTime MCU API
 * @ingroup  dgAaWcdmaTime 
 */

/* @{ */

/**
*******************************************************************************
*
*   @brief      Offers the current BTS WCDMA time
*
*   @param[out]  framePtr      Pointer for the current frame of the WCDMA time.
*   @param[out]  subframePtr   Pointer for the current subframe of the WCDMA time.
*                              WCDMA time.
*
*   @return     #EAaWcdmaTimeRetVal_NoError,
*               #EAaWcdmaTimeRetVal_Error or
*               #EAaWcdmaTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   The current BTS WCDMA time is returned by this function. Function updates
*   variables for the current BTS frame and  subframe.
*   It is possible to fetch only one of offered values by passing GLO_NULL as
*   the pointer of not needed value.
*
*   @par Errors:
*   [#EAaWcdmaTimeRetVal_Error] Internal error of WCDMA Time Services.
*   [#EAaWcdmaTimeRetVal_InvalidParamValue] Invalid input parameter(s) given.

*
*   @par Example:
*   @code
*   EAaWcdmaTimeRetVal retval;
*   TAaWcdmaBtsFrameNr frame;
*
*   retval = AaWcdmaTimeGet(&frame, GLO_NULL);
*   @endcode
*
*   @par Usage:
*   None.
*
*   @par Rationale:
*   None.
*
*   @par Future directions:
*   None.
*
*   @see
*   None
*
*******************************************************************************/
EAaWcdmaTimeRetVal AaWcdmaTimeGet(
    TAaWcdmaBtsFrameNr      *const framePtr,
    TAaWcdmaBtsSubframeNr   *const subframePtr);

/**
*******************************************************************************
*
*   @brief      Offers the current BTS WCDMA time - deprecated
*
*   @param[out]  framePtr      Pointer for the current frame of the WCDMA time.
*   @param[out]  subframePtr   Pointer for the current subframe of the WCDMA time.
*   @param[out]  slotPtr       Pointer for the current slot of the WCDMA time.
*   @param[out]  basicTUPtr    Pointer for the current basic time unit of the
*                              WCDMA time.
*
*   @return     #EAaWcdmaTimeRetVal_NoError,
*               #EAaWcdmaTimeRetVal_Error or
*               #EAaWcdmaTimeRetVal_InvalidParamValue.
*
*   @par Description:
*   The current BTS WCDMA time is returned by this function. Function updates
*   variables for the current BTS frame, subframe, slot and basic time unit.
*   It is possible to fetch only one or few of offered values by using NULL to
*   the pointers of not needed values.
*
*   @par Errors:
*   [#EAaWcdmaTimeRetVal_Error] Internal error of WCDMA Time Services.
*   [#EAaWcdmaTimeRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   On MCU environment only frames and subframes are used i.e.
*   if only slots or basicTUs are tried to get,
*   #EAaWcdmaTimeRetVal_InvalidParamValue will be returned.
*
*   @par Example:
*   @code
*   EAaWcdmaTimeRetVal retval;
*   TAaWcdmaBtsFrameNr frame;
*
*   retval = AaWcdmaTimeGetMcu(&frame, GLO_NULL, GLO_NULL, GLO_NULL);
*   @endcode
*
*   @par Usage:
*   None.
*
*   @par Rationale:
*   None.
*
*   @par Future directions:
*   None.
*
*   @see
*   None
*
*******************************************************************************/
EAaWcdmaTimeRetVal AaWcdmaTimeGetMcu(
    TAaWcdmaBtsFrameNr      *const framePtr,
    TAaWcdmaBtsSubframeNr   *const subframePtr,
    TAaWcdmaBtsSlotNr       *const slotPtr,
    TAaWcdmaBtsBasicTUNr    *const basicTUPtr );
/* @} */

#ifdef __cplusplus
}
#endif

#endif /*  _MCU_IFAAWCDMATIME_H */

