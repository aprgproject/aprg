/** @file
*   @brief AaSysComControl common definitions
*
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: 2016 Nokia. All rights reserved.$
*/


#ifndef IF_COMMON_AASYSCOMCONTROL_DEFS_H
#define IF_COMMON_AASYSCOMCONTROL_DEFS_H

#include <glo_def.h>
#include <CcsCommon.h>
#include <IfAaSysCom_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaSysComCommon AaSysCom Common
 * @ingroup dgAaSysCom
 * @{
 */

/** @brief SysCom time stamp split to two words. */
typedef struct SAaSysComTimeStampInTwoWords
{
    u32 tStampMsw; /**< Most significant word of BCN time */
    u32 tStampLsw; /**< Least significant word of BCN time */
} SAaSysComTimeStampInTwoWords;

/** @brief Receiver address for the echo route message. */
typedef struct SEchoRouteReceiver
{
    TAaSysComSicad sicad; /**< receiver address */
    TAaSysComLinkId linkId; /**< id of used link, if invalid SysCom uses
     default link */
} SEchoRouteReceiver;

/* @} end: @name Structure definitions */

/*@} end: addtogroup dgAaSysComCommon AaSysCom Common*/

#ifdef __cplusplus
}
#endif

#endif /* IF_COMMON_AASYSCOMCONTROL_DEFS_H */
