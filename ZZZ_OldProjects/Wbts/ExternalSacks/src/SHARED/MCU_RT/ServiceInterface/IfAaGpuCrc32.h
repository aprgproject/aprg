/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 CRC32 Algorithm API header file
* @module                AaGpu
* @owner                 Marcela Nemet
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAAGPUCRC32_H
#define _MCU_RT_IFAAGPUCRC32_H


/*----------------------- INCLUDED FILES --------------------------------------*/
#include "CcsCommon.h"
#include <glo_def.h>
#include <IfAaGpuChecksums.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
*@addtogroup dgChecksums
*
*
* @par Used polynomial is CRC-32-IEEE 802.3
* x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1
*
*/


/* @{ */

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/


/*----------------------- PUBLIC INTERFACES (MCU API)-------------------------*/


/**
 * @defgroup dgGpuCrc32ApiMcu Crc32 MCU API
 * @ingroup  dgChecksumsApiMcu
 */

/* @{ */

/**
*******************************************************************************
*
*   @brief  AaGpuCrc32Init initializes checksum handler to be used for CRC32 checksumming
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
AaGpuCrc32Init(SAaGpuChecksumHandler* const handler);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

/*@}*/


#endif /*  _MCU_RT_IFAAGPUCRC32_H */
