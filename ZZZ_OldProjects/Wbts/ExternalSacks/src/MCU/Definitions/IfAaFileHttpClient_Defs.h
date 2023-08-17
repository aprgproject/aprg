/** @file
*   @brief AaFile Http Client MCU definitions
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright 2017 Nokia. All rights reserved.$
*/

#ifndef _MCU_IF_AAFILEHTTPCLIENT_DEFS_H_
#define _MCU_IF_AAFILEHTTPCLIENT_DEFS_H_

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaFileApiMcu
 * @ingroup dgAaFile
 */

/** @{ */

/**
 * @brief Security mode used for http file transfers:
 */
typedef enum EAaFileHttpClientSecurityMode {
    EAaFileHttpClientSecurityMode_PlainText = 0,    /**< plain text: no encryption */
    EAaFileHttpClientSecurityMode_Tls,              /**< use Transport Layer Security */

    EAaFileHttpClientSecurityMode_Last
} EAaFileHttpClientSecurityMode;

/**
 * @brief AaFile Http Client error codes:
 */
typedef enum EAaFileHttpClientRet {
    EAaFileHttpClientRet_Ok = 0,            /**< operation successful */
    EAaFileHttpClientRet_ParamError,        /**< invalid parameters (NULL pointers, etc.) */
    EAaFileHttpClientRet_AccessDenied,      /**< wrong login credentials */
    EAaFileHttpClientRet_FileNotFound,      /**< file not found on remote server */
    EAaFileHttpClientRet_Timeout,           /**< transfer timeout */
    /* TODO new elements will be added as necessary */

    EAaFileHttpClientRet_Last
} EAaFileHttpClientRet;

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _MCU_IF_AAFILEHTTPCLIENT_DEFS_H_ */
