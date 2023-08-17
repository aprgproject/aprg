/** @file
*   @brief Contains AaCpuProfiler API interface
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: Copyright 2018 Nokia. All rights reserved.$
*/

#ifndef _MCU_IFAACPUPROFILER_H
#define _MCU_IFAACPUPROFILER_H

#include <CcsCommon.h>
#include <glo_def.h>
#include <IfAaCpuProfiler_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 *  * @defgroup dgAaCpuProfilerApiMcu AaCpuProfiler MCU API
 *   * @ingroup dgAaCpuProfiler
 *    */
/*@{*/



/**
*******************************************************************************
*
*   @brief      Function collects cpu profiler trace for defined thread.
*
*   @param[in]  threadId          Traced thread id. 0 - all threads in the process will be traced.
*   @param[in]  outputPath        Output path (AaFile volume notation path).
*
*   @par Description:
*   Function collects CPU profiler trace for a defined thread. Reports are saved in user defined outputPath path.
*   Generated reports are not automatically registered to snapshot.
*
*   @return EAaCpuProfilerStatus
*
******************************************************************************/
EAaCpuProfilerStatus AaCpuProfilerCollectTrace( u32 threadId, const char* outputPath );

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /*  _MCU_IFAACPUPROFILER_H */
