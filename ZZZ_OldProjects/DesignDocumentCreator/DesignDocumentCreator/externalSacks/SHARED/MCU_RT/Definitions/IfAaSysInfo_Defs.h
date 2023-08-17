/** @file
 *  @brief AaSysInfo config tag definitions
 *
 *  $HeadURL$
 *  $LastChangedRevision$
 *  $LastChangedDate$
 *  $Author$
 *  $Copyright: Copyright 2018 Nokia. All right reserved.$
 */
#ifndef _MCU_RT_IF_AASYSINFO_DEF_H_
#define _MCU_RT_IF_AASYSINFO_DEF_H_

#include <CcsCommon.h>

/************************** DOXYGEN GROUPS ************************************/

/**
 *  @defgroup dgAaSysInfo AaSysInfo API
 *  @ingroup  dgBasicSystemSw
 *
 *  Common Computer and Support SW System System information service.
 *
 *  Service provides means for memory usage and cpu load monitoring.
 *
 */

/************************** INCLUDED FILES ************************************/


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
 *  @brief Defines rad control over sysinfo.
 */
#define AASYSINFO_CONFIG_TAG_RAD_CONTROL_MODE           "ccs.service.aasysinfo.rad.control.mode"

/*!
 *  @brief Defines AaSysInfo thread nice level.
 */
#define AASYSINFO_CONFIG_TAG_RAD_THREAD_NICE_LEVEL      "ccs.service.aasysinfo.rad.thread.nice.level"

/*!
 *  @brief Enables extended output mode. All directories in the system shall be listed.
 */
#define AASYSINFO_CONFIG_TAG_RAD_EXTENDED_OUTPUT        "ccs.service.aasysinfo.rad.extended.output"

/*!
 *  @brief Defines time in seconds when first memory sample since CE start up is collected.
 */
#define AASYSINFO_CONFIG_TAG_MEMORY_STARTUP_TIME        "ccs.service.aasysinfo.memory.startup.time"

/*!
 *  @brief Defines memory monitor sampling time in seconds.
 */
#define AASYSINFO_CONFIG_TAG_MEMORY_SAMPLING_TIME       "ccs.service.aasysinfo.memory.sampling.time"

/*!
 *  @brief Defines maximum memory statistic days of saved history.
 */
#define AASYSINFO_CONFIG_TAG_MEMORY_MAX_DAY_HISTORY     "ccs.service.aasysinfo.memory.maximum.days.history"

/*!
 *  @brief Defines minimum memory statistic days of saved history.
 */
#define AASYSINFO_CONFIG_TAG_MEMORY_MIN_DAY_HISTORY     "ccs.service.aasysinfo.memory.minimum.days.history"

/*!
 *  @brief Defines files quota in bytes for all memory statistic logs.
 */
#define AASYSINFO_CONFIG_TAG_MEMORY_FILES_QUOTA         "ccs.service.aasysinfo.memory.files.quota"

/*!
 *  @brief Defines directories listed via AaSysInfo ( separated by a semicolon, e.g. "/tmp;/var/log;/var/tmp" )
 */
#define AASYSINFO_CONFIG_TAG_MEMORY_LISTED_DIRS         "ccs.service.aasysinfo.memory.listed.dirs"

/*!
 *  @brief Defines time in seconds when first cpu sample since CE start up is collected.
 */
#define AASYSINFO_CONFIG_TAG_CPU_STARTUP_TIME           "ccs.service.aasysinfo.cpu.startup.time"

/*!
 *  @brief Defines cpu monitor sampling time in seconds.
 */
#define AASYSINFO_CONFIG_TAG_CPU_SAMPLING_TIME          "ccs.service.aasysinfo.cpu.sampling.time"

/*!
 *  @brief Defines maximum cpu statistic files of saved history.
 */
#define AASYSINFO_CONFIG_TAG_CPU_MAX_DAY_HISTORY        "ccs.service.aasysinfo.cpu.maximum.files.history"

/*!
 *  @brief Defines minimum cpu statistic files of saved history.
 */
#define AASYSINFO_CONFIG_TAG_CPU_MIN_DAY_HISTORY        "ccs.service.aasysinfo.cpu.minimum.files.history"

/*!
 *  @brief Defines files quota in bytes for all cpu statistic logs.
 */
#define AASYSINFO_CONFIG_TAG_CPU_FILES_QUOTA            "ccs.service.aasysinfo.cpu.files.quota"

/*!
 *  @brief Defines the number of top X CPU consuming processes to be monitored. CPU usage is measured within the process discovery interval
 */
#define AASYSINFO_CONFIG_TAG_CPU_THRESHOLD        "ccs.service.aasysinfo.process.cpu.threshold"

/*!
 *  @brief Enables CPU load monitorign for threads
 */
#define AASYSINFO_CONFIG_TAG_CPU_THREAD_MONITORING            "ccs.service.aasysinfo.cpu.thread.monitoring"

/*!
 *  @brief Defines USS memory threshold in bytes for processes not linked with CCS library.
 */
#define AASYSINFO_CONFIG_TAG_PROCESS_USS_THRESHOLD      "ccs.service.aasysinfo.process.uss.threshold"

/*!
 *  @brief Defines full system scan interval in seconds.
 */
#define AASYSINFO_CONFIG_TAG_PROCESS_DISCOVERY_INTERVAL "ccs.service.aasysinfo.process.discovery.interval"

/*!
 *  @brief Defines Linux system commands which are executed on snapshot request, commands output is saved to CommandOutputDump.txt
 *  Commands must be separated via semicolon and maximum length of the string must not exceed 254 charactersDefines.
 *  e.g. "arp –a;ifconfig -a" )
 */
#define AASYSINFO_CONFIG_TAG_SYSTEM_COMMANDS            "ccs.service.aasysinfo.system.commands"

/*!
 *  @brief Defines the path, where output files from RT/DSP cores are stored.
 */
#define AASYSINFO_CONFIG_TAG_UPLOAD_STORAGE_PATH "ccs.service.aasysinfo.upload.storage.path"

/*!
 *  @brief Defines maximum number of statistic files of saved history, for RT/DSP clients.
 */
#define AASYSINFO_CONFIG_TAG_UPLOAD_MAX_HISTORY "ccs.service.aasysinfo.upload.maximum.files.history"

/*!
 *  @brief Defines minimum number of statistic files of saved history, for RT/DSP clients.
 */
#define AASYSINFO_CONFIG_TAG_UPLOAD_MIN_HISTORY "ccs.service.aasysinfo.upload.minimum.files.history"

/*!
 *  @brief Defines files quota in bytes for all RT/DSP statistic logs.
 */
#define AASYSINFO_CONFIG_TAG_UPLOAD_FILES_QUOTA "ccs.service.aasysinfo.upload.files.quota"

/*!
 *  @brief Defines compression interval for RT/DSP statistic logs.
 */
#define AASYSINFO_CONFIG_TAG_UPLOAD_COMPRESSION_INTERVAL "ccs.service.aasysinfo.upload.compression.interval"


/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* _MCU_RT_IF_AASYSINFO_DEF_H_ */
