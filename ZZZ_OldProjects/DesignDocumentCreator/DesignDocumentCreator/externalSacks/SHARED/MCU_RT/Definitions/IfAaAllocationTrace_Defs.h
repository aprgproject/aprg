/** @file
*   @brief This file contains the definitions used in AaAllocationTrace service.
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: 2016 Nokia. All rights reserved.$
*/

#ifndef MCU_RT_IF_AAALLOCATIONTRACE_DEFS_H
#define MCU_RT_IF_AAALLOCATIONTRACE_DEFS_H

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaAllocationTraceApiMcuRt AaAllocationTrace MCU-RT shared definitions
 * @ingroup  dgAaAllocationTrace
 */

/** @{ */

/**
******************************************************************************
*
* @verbatim
* Tag name:         ccs.service.aaallocationtrace.trace.mode
*
* Direction:        input
*
* Description:      Allocation trace mode:
*                   0: disabled;
*                   1: memory leak detection mode, only active allocations are traced (default);
*                   2: heap profiler mode, all allocations are traced, including not active.
*
* Effect analysis:  If this tag is not set, a value of RAD flag
*                   ERadCcs_AaAllocationTraceMode is used.
*
* Restriction:      none
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <0, 2>
*
* Define:           AAALLOCATIONTRACE_CONFIG_TAG_TRACE_MODE
*
* See:              none
* @endverbatim
*****************************************************************************/
#define AAALLOCATIONTRACE_CONFIG_TAG_TRACE_MODE "ccs.service.aaallocationtrace.trace.mode"

/**
******************************************************************************
*
* @verbatim
* Tag name:         ccs.service.aaallocationtrace.pool.memory.quota
*
* Direction:        input
*
* Description:      Memory quota for allocation pools in Bytes.
*
* Effect analysis:  If this tag is not set, a value of RAD flag
*                   ERadCcs_AaAllocationTracePoolMemoryQuota is used.
*
* Restriction:      none
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <0x100000, 0xFFFFFFFF>
*
* Define:           AAALLOCATIONTRACE_CONFIG_TAG_POOL_MEMORY_QUOTA
*
* See:              none
* @endverbatim
*
*****************************************************************************/
#define AAALLOCATIONTRACE_CONFIG_TAG_POOL_MEMORY_QUOTA "ccs.service.aaallocationtrace.pool.memory.quota"

/**
******************************************************************************
*
* @verbatim
* Tag name:         ccs.service.aaallocationtrace.pools.count
*
* Direction:        input
*
* Description:      Number of trace pools.
*
* Effect analysis:  If this tag is not set, a value of RAD flag
*                   ERadCcs_AaAllocationTracePoolCount is used.
*
* Restriction:      The number of trace pools must be a prime number.
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <1, 0xFFFFFFFF>
*
* Define:           AAALLOCATIONTRACE_CONFIG_TAG_POOLS_COUNT
*
* See:              none
* @endverbatim
*
*****************************************************************************/
#define AAALLOCATIONTRACE_CONFIG_TAG_POOLS_COUNT "ccs.service.aaallocationtrace.pools.count"

/**
******************************************************************************
*
* @verbatim
* Tag name:         ccs.service.aaallocationtrace.compressed.pools.memory.quota
*
* Direction:        input
*
* Description:      Memory quota for compressed pool reports in Bytes.
*
* Effect analysis:  If this tag is not set, a value of RAD flag
*                   ERadCcs_AaAllocationTraceCompressedPoolMemoryQuota is used.
*
* Restriction:      none
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <0, 0xFFFFFFFF>
*
* Define:           AAALLOCATIONTRACE_CONFIG_TAG_COMPRESSED_POOLS_MEMORY_QUOTA
*
* See:              none
* @endverbatim
*
*****************************************************************************/
#define AAALLOCATIONTRACE_CONFIG_TAG_COMPRESSED_POOLS_MEMORY_QUOTA "ccs.service.aaallocationtrace.compressed.pools.memory.quota"

/**
******************************************************************************
*
* @verbatim
* Tag name:         ccs.service.aaallocationtrace.call.stack.depth
*
* Direction:        input
*
* Description:      Call stack depth.
*
* Effect analysis:  If this tag is not set, a value of RAD flag
*                   ERadCcs_AaAllocationTraceCallStackDepth is used.
*
* Restriction:      none
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <0, 100>
*
* Define:           AAALLOCATIONTRACE_CONFIG_TAG_CALL_STACK_DEPTH
*
* See:              none
* @endverbatim
*
*****************************************************************************/
#define AAALLOCATIONTRACE_CONFIG_TAG_CALL_STACK_DEPTH "ccs.service.aaallocationtrace.call.stack.depth"

/**
******************************************************************************
*
* @verbatim
* Tag name:         ccs.service.aaallocationtrace.file.location
*
* Direction:        input
*
* Description:      Location of the folder where allocation trace logs are dumped.
*
* Effect analysis:  If this tag is not set, logs are dumped to /ram volume.
*
* Restriction:      Specified path must conform to AaFile path notation.
*
* Value:            IE Type:                    Size:       Range:
*                   zero-terminated string      N/A         N/A
*
* Define:           AAALLOCATIONTRACE_CONFIG_TAG_FILE_LOCATION
*
* See:              none
* @endverbatim
*
*****************************************************************************/
#define AAALLOCATIONTRACE_CONFIG_TAG_FILE_LOCATION "ccs.service.aaallocationtrace.file.location"

/**
******************************************************************************
*
* @verbatim
* Tag name:         ccs.service.aaallocationtrace.allocation.timestamp.enabled
*
* Direction:        input
*
* Description:      Enable allocation timestamp in memory leak detection mode:
*                   0: disabled (default);
*                   1: enabled.
*
* Effect analysis:  If this tag is not set, a value of RAD flag
*                   ERadCcs_AaAllocationTraceAllocationTimestampEnabled is used.
*
* Restriction:      none
*
* Value:            IE Type:     Size:     Range:
*                   number       u32       <0, 1>
*
* Define:           AAALLOCATIONTRACE_CONFIG_TAG_ALLOCATION_TIMESTAMP_ENABLED
*
* See:              none
* @endverbatim
*
*****************************************************************************/
#define AAALLOCATIONTRACE_CONFIG_TAG_ALLOCATION_TIMESTAMP_ENABLED "ccs.service.aaallocationtrace.allocation.timestamp.enabled"


/**
 * @brief AaAllocationTrace return codes
 */
typedef enum EAaAllocationTraceRet {
    EAaAllocationTraceRet_Ok             = 0,   /**< Operation was successful. */
    EAaAllocationTraceRet_Error          = 1,   /**< An error occurred. */
    EAaAllocationTraceRet_NoMem          = 2,   /**< Not enough memory for tracing initialization. */
    EAaAllocationTraceRet_NotEnabled     = 3,   /**< Action cannot be performed because service is disabled. */
    EAaAllocationTraceRet_AlreadyRunning = 4,   /**< Action cannot be performed because service is already enabled. */
    EAaAllocationTraceRet_ConfError      = 5,   /**< Configuring tracing failed. */
    EAaAllocationTraceRet_WrongParams    = 6,   /**< Wrong parameters provided. */
    EAaAllocationTraceRet_AlreadyDumped  = 7    /**< Dump report already exists. */
} EAaAllocationTraceRet;


/**
 * @brief AaAllocationTrace operational status
 */
typedef enum EAaAllocationTraceStatus {
    EAaAllocationTraceStatus_On     = 0,    /**< Tracing is enabled. Memory pools are allocated and registered to snapshot. */
    EAaAllocationTraceStatus_Stop   = 1,    /**< Tracing is stopped. Memory pools are not removed. */
    EAaAllocationTraceStatus_Off    = 2     /**< Tracing is disabled. Memory pools are removed. */
} EAaAllocationTraceStatus;

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* MCU_RT_IF_AAALLOCATIONTRACE_DEFS_H */
