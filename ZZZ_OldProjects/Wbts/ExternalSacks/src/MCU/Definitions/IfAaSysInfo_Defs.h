/** @file
 *  @brief AaSysInfo config tag definitions
 *
 *  $HeadURL$
 *  $LastChangedRevision$
 *  $LastChangedDate$
 *  $Author$
 *  $Copyright: Copyright 2018 Nokia. All right reserved.$
 */
#ifndef _MCU_IF_AASYSINFO_DEF_H_
#define _MCU_IF_AASYSINFO_DEF_H_

#include <CcsCommon.h>
#include <../../SHARED/MCU_RT/Definitions/IfAaSysInfo_Defs.h>

#ifdef __cplusplus
extern "C"{
#endif

/************************** PUBLIC DECLARATIONS *******************************/

/**
* @defgroup dgAaSysInfoApiCommon AaSysInfo shared API
* @ingroup dgAaSysInfo
* @{
*/

/*!
 *  @brief Defines syscom monitoring sampling interval, in seconds.
 */
#define AASYSINFO_CONFIG_TAG_SYSCOM_SAMPLING_TIME               "ccs.service.aasysinfo.syscom.sampling.time"

/*!
 *  @brief Defines syscom monitoring maximum number of history files
 */
#define AASYSINFO_CONFIG_TAG_SYSCOM_MAXIMUM_FILES_HISTORY       "ccs.service.aasysinfo.syscom.maximum.files.history"

/*!
 *  @brief Defines syscom monitoring minimum number of history files
 */
#define AASYSINFO_CONFIG_TAG_SYSCOM_MINIMUM_FILES_HISTORY       "ccs.service.aasysinfo.syscom.minimum.files.history"

/*!
 *  @brief Defines syscom monitoring reporting thresholds, see description.
 *
 *  Defines syscom monitoring reporting thresholds in a format of string of percentages.
 *  It's possible to set one or multiple thresholds.
 *  Thresholds must be semicolon separated and maximum length of the string must not exceed 254 characters.
 *  Example: "60;70;80;90".
 */
#define AASYSINFO_CONFIG_TAG_SYSCOM_REPORT_THRESHOLD            "ccs.service.aasysinfo.syscom.report.threshold"

/*!
 *  @brief Defines syscom monitoring reporting interval, in seconds.
 */
#define AASYSINFO_CONFIG_TAG_SYSCOM_REPORT_INTERVAL         "ccs.service.aasysinfo.syscom.report.interval"

/*!
 *  @brief Defines syscom monitoring log file size quota, in bytes.
 */
#define AASYSINFO_CONFIG_TAG_SYSCOM_FILES_QUOTA             "ccs.service.aasysinfo.syscom.files.quota"

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* _MCU_IF_AASYSINFO_DEF_H_ */
