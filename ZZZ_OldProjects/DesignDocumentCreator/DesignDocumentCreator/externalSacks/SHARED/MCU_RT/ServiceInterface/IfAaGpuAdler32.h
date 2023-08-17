/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 Adler32 Algorithm API header file
* @module                AaGpu
*
* Copyright 2017 Nokia Networks. All rights reserved.
*******************************************************************************/
#ifndef _MCU_RT_IFAAGPUADLER32_H
#define _MCU_RT_IFAAGPUADLER32_H


/*----------------------- INCLUDED FILES --------------------------------------*/

#include <CcsCommon.h>
#include <glo_def.h>
#include <IfAaGpuChecksums.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
*@addtogroup dgChecksums
*
* @par Adler32 algorithm compliant checksum calculation service
*/

/* @{ */

/**
 * @defgroup dgGpuAdler32ApiMcuRt Adler MCU-RT shared API
 * @ingroup  dgChecksumsApiMcu
 */

/* @{ */

/**
*******************************************************************************
*
*   @brief  AaGpuAdler32Init initializes checksum handler to be used for adler32 checksumming
*
*
*   @param[in]  handler  Pointer to checksum handler.
*
*   @return EAaGpuChecksumsRet_Ok
*   @return EAaGpuChecksumsRet_InvalidParameter
*
*   @par Description:
*
*   @par Errors:
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
*   EAaGpuChecksumsRet ret;
*   SAaGpuChecksumHandler handler;
*
*   ret = AaGpuAdler32Init(&handler);
*
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
EAaGpuChecksumsRet
AaGpuAdler32Init(SAaGpuChecksumHandler* const handler);

/** @} */


#ifdef __cplusplus
}
#endif

/*@}*/


#endif /*  _MCU_RT_IFAAGPUADLER32_H */
