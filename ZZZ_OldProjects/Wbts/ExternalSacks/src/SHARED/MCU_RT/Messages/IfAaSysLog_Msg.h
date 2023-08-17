/** @file
*   @brief AaSysLog Msg API
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: 2017 Nokia. All rights reserved.$
*/

#ifndef _MCU_RT_IFAASYSLOG_MSG_H
#define _MCU_RT_IFAASYSLOG_MSG_H

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief  Message: Set severity levels for specific process request
 */
typedef struct AaSysLogPidFilterSetReq
{
    u32                    processId;   /**< OS process ID */
    EAaSysLogSeverityLevel inputLevel;  /**< New 1.severity level for process */
    EAaSysLogSeverityLevel outputLevel; /**< New 2.severity level for process */
}AaSysLogPidFilterSetReq;

/**
 *  @brief  Message: Set severity levels for specific process response
 */
typedef struct AaSysLogPidFilterSetResp
{
    EAaSysLogConfigureRetVal status;      /**< Overall status of filter set */
    u32                      processId;   /**< OS process ID */
    EAaSysLogSeverityLevel   inputLevel;  /**< New 1.severity level for process */
    EAaSysLogSeverityLevel   outputLevel; /**< New 2.severity level for process */
}AaSysLogPidFilterSetResp;

/**
 *  @brief  Message: Clear severity level filtering for all process request
 */
typedef struct AaSysLogPidFilterClearReq
{
    void *dummy;  /**< Dummy pointer */
}AaSysLogPidFilterClearReq;

/**
 *  @brief  Message: Clear severity level filtering for all process response
 */
typedef struct AaSysLogPidFilterClearResp
{
    EAaSysLogConfigureRetVal status;      /**< Overall status of filter clearing */
}AaSysLogPidFilterClearResp;

#ifdef __cplusplus
}
#endif

#endif  /* _MCU_RT_IFAASYSLOG_MSG_H */

