/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaError MCU definitions.
* @module                AaError
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAAERROR_DEF_H_
#define _MCU_RT_IFAAERROR_DEF_H_

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaErrorApiLinux AaError LINUX API
* @ingroup dgAaError
*/
/*@{*/

/**
* Limits maximum Application name length
*/
#define AAERROR_MAX_APPLICATION_NAME 256
/**
* Limits maximum core path length
*/
#define AAERROR_MAX_CORE_PATH_LENGTH 256

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* _MCU_RT_IFAAERROR_DEF_H_ */
