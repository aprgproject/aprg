/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
* Copyright 2018, 2019 Nokia. All rights reserved.
*
*******************************************************************************/
#ifndef _MCU_IFAAERROR_H
#define _MCU_IFAAERROR_H

#include "CcsCommon.h"
#ifdef CCS_NEW_IF_STRUCTURE
#include <../../COMMON/ServiceInterface/IfAaError.h>
#include <../../SHARED/MCU_RT/ServiceInterface/IfAaError.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup dgAaErrorApiMcuLinux AaError LINUX MCU API
* @ingroup dgAaError
*/

/** @{ */

/**
* @brief Limits core file size, value will be read by AaError at Startup
*/
#define AAERROR_CONFIG_TAG_CORE_SIZE "ccs.service.aaerror.core_size"

/**
* @brief The tag disables core pattern setting by CC&S. The type of tag is u32. CC&S sets core pattern if tag is not set
* @deprecated Please do not use this definition anymore. It will be removed in SM19B release.
*/
#define AAERROR_CONFIG_TAG_SET_CORE_PATTERN_DISABLED "ccs.service.aaerror.set.core_pattern.disabled"

/**
* @brief Enables core dumping if set to 1, otherwise coredumping will be
* disabled. Size of core enabled by this tag is defined by "ccs.service.aaerror.core_size".
* Value of this tag will be read by AaError at startup.
*/
#define AAERROR_CONFIG_TAG_CORE_ENABLED "ccs.service.aaerror.core.enabled"

/**
* @brief Enables multi core dumping if set to 1, otherwise one core dumping will be
* supported. The tag value is read by AaError at startup.
*/
#define AAERROR_CONFIG_TAG_MULTI_CORE_ENABLED "ccs.service.aaerror.multi.core.enabled"

/**
* @brief Specifies timeout for locking mechanism used in the crashHandler script. If not set
* default value 30s is used. The tag value is checked only if AAERROR_CONFIG_TAG_MULTICORE_ENABLED
* is enabled. The tag value is read by AaError at startup.
*/
#define AAERROR_CONFIG_TAG_MULTI_CORE_TIMEOUT "ccs.service.aaerror.multi.core.timeout"

/**
*******************************************************************************
*
*   @brief  Enables core dump on BTS
*
*   @return Indicates if the function was performed successfully.
*
*   @par Description:
*        Sets R&D flag ERadCcs_AaErrorCoreOamDumpEnabled to 1.
*
*   @par Errors:
*        EAaErrorRet_Nok.
*
*   @par Restrictions:
*
*   @par Example:
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
EAaErrorRet AaErrorBtsEnableCoreDump(void);

/**
*******************************************************************************
*
*   @brief  Disables core dump on BTS
*
*   @return Indicates if the function was performed successfully.
*
*   @par Description:
*        Sets R&D flag ERadCcs_AaErrorCoreOamDumpEnabled to 0.
*
*   @par Errors:
*        EAaErrorRet_Nok.
*
*   @par Restrictions:
*
*   @par Example:
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
EAaErrorRet AaErrorBtsDisableCoreDump(void);

/**
*******************************************************************************
*
*   @brief  Disables core dumping in EE.
*
*   @return Indicates if the function was performed successfully.
*
*   @par Description:
*        Disables core generation in EE which is calling the function.
*
*   @par Errors:
*        EAaErrorRet_Nok.
*
*   @par Restrictions:
*
*   @par Example:
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
EAaErrorRet AaErrorEeDisableCoreDump(void);

/**
*******************************************************************************
*
*   @brief  Enables core dumping in EE.
*
*   @return Indicates if the function was performed successfully.
*
*   @par Description:
*        Enables core dumping in EE which is calling the function.
*
*   @par Errors:
*        EAaErrorRet_Nok.
*
*   @par Restrictions:
*
*   @par Example:
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
EAaErrorRet AaErrorEeEnableCoreDump(void);

/**
*******************************************************************************
*
*   @brief  Function to check if core dumping is enabled on current Node.
*           It applies for the CE domain.
*
*   @return GLO_TRUE if core dumping is enabled,
*           GLO_FALSE if core dumping is disabled.
*
*   @par Description:
*   This function is used to determine whether core dumping via AaError is currently enabled.
*
*   @par Errors:
*   None.
*
*   @par Restrictions:
*   None.
*   @par Example:
*
*   @code
*   #include <IfAaError.h>
*
*   if ( GLO_TRUE == AaErrorIsCoreDumpEnabled() )
*   {
*        //Core dumps are enabled - happy debugging :)
*   }
*   @endcode
*
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
TBoolean AaErrorIsCoreDumpEnabled(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /*  _MCU_IFAAERROR_H */
