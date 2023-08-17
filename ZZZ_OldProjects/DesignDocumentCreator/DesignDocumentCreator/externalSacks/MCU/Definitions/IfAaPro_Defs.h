/** @file
*   @brief AaPro MCU definitions.
*   @copyright 2015 Nokia Solutions and Networks. All rights reserved.
*   @copyright 2019 Nokia. All rights reserved.
*/

#ifndef _MCU_IFAAPRO_DEF_H_
#define _MCU_IFAAPRO_DEF_H_

#include <CcsCommon.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <../../COMMON/Definitions/IfAaPro_Defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @addtogroup dgAaProApiMcu
 * @{
 */
 /** @brief Definition for AaProWaitForEu for infinite timeout  */
#define AAPRO_EU_WAIT_INFINITE 0xFFFFFFFF

 /** @brief Config tag to disable CpuMemSupervisionService // PR067151 // type u16 // 0 - service enabled, any other value - service disabled  */
#define AAPRO_CMSS_DISABLE "ccs.service.aapro.supervision.disabled"

/** @brief AaPro tag to control CC&S CE recovery reset, when EU stopped to send keepAlive signal towards AaProEuSupervision.
* For commands executed via \ref AaProCmdExec or \ref AaProCmdExecRaw tag disables CC&S CE recovery reset after critical application crash.
* Values:
* - not set(default) - AaPro is performing CC&S CE recovery reset,
* - \c 0 - AaPro is performing CC&S CE recovery reset,
* - \c 1 - AaPro is NOT performing CC&S CE recovery reset.
* */
#define AAPRO_TAG_RECOVERY_RESET "ccs.service.aapro.supervision.recovery_reset"

 /** @} end: @addtogroup dgAaProApiMcu */

#ifdef __cplusplus
}
#endif

#endif /* _MCU_IFAAPRO_DEF_H_ */
