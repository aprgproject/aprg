/** @file
*   @brief This file contains the prototypes of AaAllocationTrace service functions.
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: 2016 Nokia. All rights reserved.$
*/

#ifndef MCU_RT_IF_AAALLOCATIONTRACE_H
#define MCU_RT_IF_AAALLOCATIONTRACE_H

#include <CcsCommon.h>
#ifdef CCS_NEW_IF_STRUCTURE
#include <../../SHARED/MCU_RT/Definitions/IfAaAllocationTrace_Defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaAllocationTraceApiMcuRt AaAllocationTrace MCU-RT
 * @ingroup  dgAaAllocationTrace
 */

/** @{ */

/**
******************************************************************************
*
*   @brief Set allocation tracing mode.
*
*   @param[in]  status  allocation tracing status
*
*   @return EAaAllocationTraceRet_Ok on success,
*           appropriate EAaAllocationTraceRet values otherwise.
*
*   @par Description:
*   Set tracing mode to one of three possible values: ON, STOP or OFF:
*       - #EAaAllocationTraceStatus_On: enables allocation tracing. Memory pools are allocated
*         and registered to snapshot. Trace report will be automatically dumped during the
*         snapshot collection.
*       - #EAaAllocationTraceStatus_Stop: stops allocation tracing. Memory pools are not
*         removed.
*       - #EAaAllocationTraceStatus_Off: allocation tracing is disabled. Memory pools and
*         compressed pools are removed.
*
******************************************************************************/
EAaAllocationTraceRet AaAllocationTraceSetStatus(EAaAllocationTraceStatus status);

/**
******************************************************************************
*
*   @brief Dump allocation trace to a file.
*
*   @return EAaAllocationTraceRet_Ok on success,
*           appropriate EAaAllocationTraceRet values otherwise.
*
*   @par Description:
*   Dumps allocation trace to a file named memory_allocation_trace_<ProcessName>.zip
*
*   @see AaAllocationTraceDumpDecodedReport()
*
******************************************************************************/
EAaAllocationTraceRet AaAllocationTraceDumpReport(void);

/**
******************************************************************************
*
*   @brief Dump decoded allocation trace report.
*
*   @return EAaAllocationTraceRet_Ok on success,
*           appropriate EAaAllocationTraceRet values otherwise.
*
*   @par Description:
*   Generates decoded allocation trace report. Traced executable must not be
*   stripped in order to provide backtrace translation of function calls.
*
*   @see AaAllocationTraceDumpReport()
*
******************************************************************************/
EAaAllocationTraceRet AaAllocationTraceDumpDecodedReport(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* MCU_RT_IF_AAALLOCATIONTRACE_H */
