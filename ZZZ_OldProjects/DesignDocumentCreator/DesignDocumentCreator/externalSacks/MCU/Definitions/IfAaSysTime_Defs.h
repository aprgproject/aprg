/** @file
*   @brief Contains AaSysTime MCU definitions
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: Copyright 2016 Nokia. All rights reserved.$
*/

#ifndef _MCU_IF_AASYSTIME_DEF_H_
#define _MCU_IF_AASYSTIME_DEF_H_

#include <../../COMMON/Definitions/IfAaSysTime_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaSysTimeDefsMcu AaSysTime MCU definitions
 * @ingroup dgAaSysTimeDefs
 */
/*@{*/

/**
 * @brief This tag contains information if DST is applied in current localtime.
 *        0 - DST is not active
 *        1 - DST is active
 *        2 - error - current localtime can be incorrect
 */
#define AASYSTIME_TAG_IS_DST_ACTIVE "ccs.service.aasystime.isdstactive"

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  //_MCU_IF_AASYSTIME_DEF_H_
