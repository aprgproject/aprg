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

#ifndef _DSP_LITE_IFAASYSTIME_H
#define _DSP_LITE_IFAASYSTIME_H

#ifdef __cplusplus
extern "C" {
#endif

/**
*******************************************************************************
*
*   @brief      Returns long code state
*
*
*   @param[in]  cdmaTimeIn10MSecSteps CDMA time in 10ms steps
*
*   @return     Long code state
*
*   @par Description:   Returns the 42-bit long code state for a given 39-bit
*                       CDMA time. 
*   
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
*   @see  AaCdmaTimeGet
*         AaCdmaTimeAsyncGet
*
******************************************************************************/
TAaSysTime64 AaCdmaLongCodeState1XRTT(TAaSysTime64 cdmaTimeIn10MSecSteps);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

/**@}*/

#endif /*  _DSP_LITE_IFAASYSTIME_H */

