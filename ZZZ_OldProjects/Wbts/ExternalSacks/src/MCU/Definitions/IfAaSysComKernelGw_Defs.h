/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2018 Nokia. All rights reserved.
*******************************************************************************/

#ifndef IF_MCU_AASYSCOMKERNELGW_DEFS_H
#define IF_MCU_AASYSCOMKERNELGW_DEFS_H

#include <CcsCommon.h>
#include "../../COMMON/Definitions/IfAaSysComGw_Defs.h"
#include "../../SHARED/MCU_RT/Definitions/IfAaSysComGw_Defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
 * @addtogroup dgAaSysComKernelGwMcu AaSysComKernelGw MCU
 * @ingroup dgAaSysComKernelGw
 *
 *
 * @{
 */

 /*----------------------- PUBLIC DECLARATIONS --------------------------------*/


/** @name Interface types (MCU specific)
 * @{
 */

/** CPID for the Kernel Gateway
 *  This CPID is used to configure gateway supported by linux kernel -
 *  SysCom socket gateway provided by LFS
 * */
#ifndef AASYSCOM_KERNEL_GW_CPID
#define AASYSCOM_KERNEL_GW_CPID 0x0658
#endif /* AASYSCOM_KERNEL_GW_CPID */

/** @} */

/** @} end: @addtogroup dgAaSysComKernelGwMcu AaSysComKernelGw MCU */

#ifdef __cplusplus
}
#endif

#endif /* IF_MCU_AASYSCOMKERNELGW_DEFS_H */
