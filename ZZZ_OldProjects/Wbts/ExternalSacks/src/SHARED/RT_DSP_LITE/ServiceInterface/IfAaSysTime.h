/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaSysTime interface header file
* @module                AaSysTime
*
* Copyright 2018 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _RT_DSP_LITE_IFAASYSTIME_H
#define _RT_DSP_LITE_IFAASYSTIME_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaSysTimeApiDsp AaSysTime DSP API RT_LINUX_API
 * @ingroup  dgAaSysTime
 */

/* @{ */

/**
*******************************************************************************
*
*   @brief      Returns the CDMA time
*
*   @param[out] cdmaTime         CDMA time
*   @param[in]  reqHyperFrame    Requested hyper frame time 0..3.
*   @param[in]  reqFrame         Requested frame time 0..1023.
*
*   @return     EAaSysTimeRetVal_NoError
*               EAaSysTimeRetVal_Error
*               EAaSysTimeRetVal_InvalidParamValue
*
*   @par Description:   Returns the CDMA time represented by 39-bit count of 
*                       10 ms ticks since the GPS Epoch.
*                       cdmaTime 0 is returned in case time is set to be invalid
*                       by AaCdmaTimeInvalid.
*   @par Errors:
*   None
*
*   @par Restrictions:
*    
*
*   @par Example:
*   @code
*     #include <IfAaSysTime.h>
*
*   
*   @endcode
*
*   @par Usage:
*   
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see  AaCdmaTimeAsyncGet
*
******************************************************************************/
EAaSysTimeRetVal AaCdmaTimeGet(TAaSysTime64 *const cdmaTime,
                               TAaSysTime    const reqHyperFrame,
                               TAaSysTime    const reqFrame);

/**
*******************************************************************************
*
*   @brief      Returns the asynchronous CDMA system time
*
*   @param[out] cdmaTime         asynchronous CDMA time
*   @param[in]  reqHyperFrame    Reguested hyper frame time 0..3.
*   @param[in]  reqFrame         Reguested frame time 0..1023.
*
*   @return     EAaSysTimeRetVal_NoError
*               EAaSysTimeRetVal_Error
*               EAaSysTimeRetVal_InvalidParamValue
*
*   @par Description:   Returns the asynchronous CDMA time represented by 49-bit
*                       count of 8/1.2288 us steps since the GPS Epoch.
*                       cdmaTime 0 is returned in case time is set to be invalid
*                       by AaCdmaTimeInvalid.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*
*   @par Example:
*   @code
*     #include <IfAaSysTime.h>
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see  AaCdmaTimeGet
*
******************************************************************************/
EAaSysTimeRetVal AaCdmaTimeAsyncGet(TAaSysTime64 *const cdmaTime,
                                    TAaSysTime    const reqHyperFrame,
                                    TAaSysTime    const reqFrame);

#ifdef __cplusplus
}
#endif

/**@}*/

#endif /*  _RT_DSP_LITE_IFAASYSTIME_H */

