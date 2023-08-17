/** @file
* @brief Definitions for IfAaXz.h.
* @copyright 2019 Nokia. All rights reserved.
*/
#ifndef _IF_MCU_AAXZ_DEFS_H_
#define _IF_MCU_AAXZ_DEFS_H_

/**
* @defgroup dgAaXzMcuDefs AaXz Mcu definitions
* @ingroup dgCompressions
*/

/** @{ */

/**
* @brief AaXz return codes.
*/
typedef enum EAaXzRet {
    EAaXzRet_Ok = 0,       /**< operation was successful */
    EAaXzRet_InvalidParam, /**< invalid parameter */
    EAaXzRet_BufferError,  /**< not enough space for out buffer */
    EAaXzRet_Error         /**< operation failed */
} EAaXzRet;

/** @} */

#endif /* _IF_MCU_AAXZ_DEFS_H_  */
