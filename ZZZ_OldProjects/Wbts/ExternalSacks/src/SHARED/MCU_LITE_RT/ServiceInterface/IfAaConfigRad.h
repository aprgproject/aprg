/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_LITE_RT_IF_AACONFIG_RAD_H_
#define _MCU_LITE_RT_IF_AACONFIG_RAD_H_

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaConfigRad AaConfigRad shared lite mcu rt function API
 * @ingroup dgAaConfig
 */
/*@{*/

/**
*******************************************************************************
*
*   @brief      Function for getting R&D tag value.
*
*   @param[in]  tag           Identier of R&D tag.
*
*   @return     Function returns value of R&D tag.
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   Not supported on DSP
*
*   @par Example:
*   @code
*     u32 value = AaConfigRadGetValue(ERadCcs_PrintAaSysCom);
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
******************************************************************************/
u32 AaConfigRadGetValue(u32 tag);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  //_MCU_LITE_RT_IF_AACONFIG_RAD_H_
