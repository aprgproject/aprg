/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2016, 2018, 2019 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_IF_AASTARTUP_DEFS_H_
#define _MCU_IF_AASTARTUP_DEFS_H_

#include <CcsCommon.h>
#include <../../SHARED/MCU_RT/Definitions/IfAaStartup_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaStartupDefsMcu AaStartup MCU definitions
 * @ingroup dgAaStartupDefs
 */

/*@{*/

/**
 * @brief Indicates that CCS handshaking and supervision are enabled. The type of tag is u16.
 *        CC&S starts supervision and handshaking if tag is set to any value
 * @deprecated Please do not use this definition anymore. It will be removed in SM19B release.
 */
#define AACONFIG_TAG_DAEMON_HANDSHAKING_SUPERVISION_ENABLED  "ccs.daemon.handshaking.supervision.enabled"

/**
 * @brief Controls default CPU affinity mask of CCS CE process.
 *
 * @par Description:
 *      Attribute tag controls default CPU affinity of CCS CE process.
 *      Desired CPU affinity mask is set at early startup of CCS CE process.
 *
 * @par Restrictions:
 *      The type of tag is u32.
 *      Validity of tag value depends on CPU architecture and
 *      possible restrictions applied by lower layer software starting CCS (e.g. systemd or lxc).
 *      Value 0 is always invalid.
 */
#define AACONFIG_TAG_NAME_CE_CPU_AFFINITY_MASK  "sys.ce.cpu.affinity.mask"

/**
 * @brief Controls default CPU affinity mask of CCS EE application process.
 *
 * @par Description:
 *      Attribute tag controls default CPU affinity of CCS EE application process.
 *      Desired CPU affinity mask is set at early startup of CCS EE application process.
 *      The desired CPU affinity mask is set for the EU executing early startup of CCS
 *      and inherited by all EUs started at later phases of application startup.
 *      Affinity mask is not set for application's EUs started before CCS early initialization.
 *
 * @par Restrictions:
 *      The type of tag is u32.
 *      Validity of tag value depends on CPU architecture and
 *      possible restrictions applied by lower layer software starting CCS (e.g. systemd or lxc).
 *      Value 0 is always invalid.
 */
#define AACONFIG_TAG_NAME_EE_CPU_AFFINITY_MASK  "sys.ee.cpu.affinity.mask"

/*@}*/

#ifdef __cplusplus
}
#endif
#endif  /* _MCU_IF_AASTARTUP_DEFS_H_ */
