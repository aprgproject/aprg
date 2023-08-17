/** @file
 *  @brief AaCpuProfiler config tag definitions
 *
 *  $HeadURL$
 *  $LastChangedRevision$
 *  $LastChangedDate$
 *  $Author$
 *  $Copyright: Copyright 2018 Nokia. All right reserved.$
 */
#ifndef _MCU_IF_AACPUPROFILER_DEF_H_
#define _MCU_IF_AACPUPROFILER_DEF_H_

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C"{
#endif

/************************** PUBLIC DECLARATIONS *******************************/

/**
 *  * @defgroup dgAaCpuProfilerApiMcu AaCpuProfiler MCU API
 *   * @ingroup dgAaCpuProfiler
 *    */
/*@{*/

/*!
 *  @brief Defines signal ID used for profiling.
 */
#define AACPUPROFILER_CONFIG_TAG_SIGNAL_ID              "ccs.service.aacpuprofiler.signal.id"


/*!
 *  @brief Defines signal ID used for profiling.
 */
#define AACPUPROFILER_CONFIG_TAG_LOG_PATH               "ccs.service.aacpuprofiler.log.path"


/**
 *  @brief  Domain buffer setting status.
 */
typedef enum EAaCpuProfilerStatus
{
    EAaCpuProfilerStatus_Ok                    = 0,
    EAaCpuProfilerStatus_InvalidParameters     = 1,
    EAaCpuProfilerStatus_ThreadAlreadyFinished = 2,
    EAaCpuProfilerStatus_FileOpenError         = 3,
    EAaCpuProfilerStatus_NOk                   = 4
}EAaCpuProfilerStatus;


/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* _MCU_IF_AACPUPROFILER_DEF_H_ */
