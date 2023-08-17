/** @file
*   @brief Contains AaSysLog Definitions interface
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: Copyright 2017 Nokia. All rights reserved.$
*/

#ifndef _MCU_IFAASYSLOG_DEF_H_
#define _MCU_IFAASYSLOG_DEF_H_

#include <CcsCommon.h>
#include "../../COMMON/Definitions/IfAaSysLog_Defs.h"
#include "../../SHARED/MCU_RT/Definitions/IfAaSysLog_Defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaSysLogDefs AaSysLog Definitions
 * @ingroup dgAaSysLog
 */
/*@{*/

/**
 *  @deprecated NOT IN USE ANYMORE!
 */
#define AASYSLOG_CONFIG_TAG_IP_ADDRESS_LCP0     "ccs.service.aasyslog.ipaddress.lcp0"

/**
 *  @deprecated NOT IN USE ANYMORE!
 */
#define AASYSLOG_CONFIG_TAG_IP_ADDRESS_LCP1     "ccs.service.aasyslog.ipaddress.lcp1"

/**
*  @brief  Path where system logs are stored.
*  On system startup logs from directory: pm_2 will be removed, pm_1 will be renamed to pm_2 and from runtime moved to pm_1.
*  System log file format: systemlog_<sequenceNumber>.log, systemlog_<featureName>_<sequenceNumber>.log
*  During snapshot collection all systemlog_<sequenceNumber>.log, systemlog_<featureName>_<sequenceNumber>.log files are merged.
*  and all files are added to already existing registered AaSysLog files: runtime.zip, pm_1_syslog.zip and pm_2_syslog.zip
*  Example content of AaSysLog files in snapshot:
*  runtime.zip:
*       runtime_BTSOM.log.xz
*       runtime_CPLANE_Central.log.xz
*       runtime_DEFAULT.log.xz
*       runtime_TRSW.log.xz
*       runtime_SYSTEM.log.xz
*       runtime_SYSTEM_<featureName>.log.xz
*  pm_1_syslog.zip:
*       pm_1_BTSOM.log.xz
*       pm_1_CPLANE_Central.log.xz
*       pm_1_DEFAULT.log.xz
*       pm_1_TRSW.log.xz
*       pm_1_SYSTEM.log.xz
*       pm_1_SYSTEM_<featureName>.log.xz
*  pm_2_syslog.zip:
*       pm_2_BTSOM.log.xz
*       pm_2_CPLANE_Central.log.xz
*       pm_2_DEFAULT.log.xz
*       pm_2_TRSW.log.xz
*       pm_2_SYSTEM.log.xz
*       pm_2_SYSTEM_<featureName>.log.xz
*/
#define AASYSLOG_CONFIG_TAG_SYSTEM_LOG_PATH                         "ccs.service.aasyslog.system.log.path"

/**
*  @brief  Path to passive partition from which system logs are added to snapshot.
*  During snapshot collection all systemlog_<sequenceNumber>.log, systemlog_<featureName>_<sequenceNumber>.log files are merged.
*  and all other files are added to pm_syslog_stb.zip
*  Example content of AaSysLog files in snapshot:
*  pm_syslog_stb.zip
*       runtime_SYSTEM.log.xz
*       runtime_SYSTEM_<featureName>.log.xz
*       pm_1_SYSTEM.log.xz
*       pm_1_SYSTEM_<featureName>.log.xz
*       pm_2_SYSTEM.log.xz
*       pm_2_SYSTEM_<featureName>.log.xz
*/
#define AASYSLOG_CONFIG_TAG_SYSTEM_LOG_PATH_STB                      "ccs.service.aasyslog.system.log.path_stb"


/**
*  @brief  System log single file size.
*  When the maximum file size is reached file is compressed and closed.
*/
#define AASYSLOG_CONFIG_TAG_SYSTEM_LOG_SIZE                         "ccs.service.aasyslog.system.log.size"

/**
*  @brief  Number of stored system log files.
*  When the maximum number of stored files is reached last file is removed.
*  First file is always preserved.
*/
#define AASYSLOG_CONFIG_TAG_SYSTEM_LOG_COUNT                        "ccs.service.aasyslog.system.log.count"

/**
*  @brief Maximum interval in seconds after which the system logs are moved from a temporary buffer to a system log file.
*         Tag is used to reduce the number of writes to flash.
*/
#define AASYSLOG_CONFIG_TAG_SYSTEM_LOG_TIME_WINDOW                  "ccs.service.aasyslog.system.log.time.window"

/**
*  @brief Maximum number of bytes to be saved in system log buffer in defined TIME_WINDOW interval.
*         Tag is used to reduce the number of saved logs to flash.
*/
#define AASYSLOG_CONFIG_TAG_SYSTEM_LOG_TIME_WINDOW_SIZE             "ccs.service.aasyslog.system.log.time.window.size"

/**
*  @brief runtime_SnapshotCollection.log file size in Bytes.
*  File contains first "n" Bytes of logs from all log buffers collected during the runtime log generation freeze.
*  File is temporary stored in RAM and included in runtime.zip after the runtime log collection procedure.
*/
#define AASYSLOG_CONFIG_TAG_SNAPSHOT_COLLECTION_STARTUP_LOG_SIZE     "ccs.service.aasyslog.snapshot.collection.startup.log.size"

/**
*  @brief runtime_SnapshotCollectionEnd.log file size in Bytes.
*  File contains last "n" Bytes of logs from all log buffers collected during the runtime log generation freeze.
*  File is stored in RPRAM and included in runtime.zip after the runtime log collection procedure.
*/
#define AASYSLOG_CONFIG_TAG_SNAPSHOT_COLLECTION_RUNTIME_LOG_SIZE     "ccs.service.aasyslog.snapshot.collection.runtime.log.size"

/**
*  @brief pm_1/2_SnapshotCollection.log file size in Bytes.
*  File contains last "n" Bytes of runtime_SnapshotCollectionEnd.log from before the reset.
*  File is stored in RPRAM and included in pm_1/2_syslog.zip.
*/
#define AASYSLOG_CONFIG_TAG_SNAPSHOT_COLLECTION_POSTMORTEM_LOG_SIZE "ccs.service.aasyslog.snapshot.collection.postmortem.log.size"

/*!
 *  @brief RCP startup log size
 */
#define AASYSLOG_CONFIG_TAG_RCP_STARTUP_LOG_SIZE "ccs.service.aasyslog.rcp.startuplog.size"

/*!
 *  @brief RCP runtime log size
 */
#define AASYSLOG_CONFIG_TAG_RCP_RUNTIME_LOG_SIZE "ccs.service.aasyslog.rcp.runtimelog.size"

/*!
 *  @brief RCP FM startup log size
 */
#define AASYSLOG_CONFIG_TAG_RCP_FM_STARTUP_LOG_SIZE "ccs.service.aasyslog.rcp_fm.startuplog.size"

/*!
 *  @brief RCP FM runtime log size
 */
#define AASYSLOG_CONFIG_TAG_RCP_FM_RUNTIME_LOG_SIZE "ccs.service.aasyslog.rcp_fm.runtimelog.size"

/*!
 *  @brief RCP PM startup log size
 */
#define AASYSLOG_CONFIG_TAG_RCP_PM_STARTUP_LOG_SIZE "ccs.service.aasyslog.rcp_pm.startuplog.size"

/*!
 *  @brief RCP PM runtime log size
 */
#define AASYSLOG_CONFIG_TAG_RCP_PM_RUNTIME_LOG_SIZE "ccs.service.aasyslog.rcp_pm.runtimelog.size"

/*!
 *  @brief RCP GIVZXI startup log size
 */
#define AASYSLOG_CONFIG_TAG_RCP_GIVAXI_STARTUP_LOG_SIZE "ccs.service.aasyslog.rcp_givaxi.startuplog.size"

/*!
 *  @brief RCP GIVAXI runtime log size
 */
#define AASYSLOG_CONFIG_TAG_RCP_GIVAXI_RUNTIME_LOG_SIZE "ccs.service.aasyslog.rcp_givaxi.runtimelog.size"

/*!
 *  @brief RCP LWSD startup log size
 */
#define AASYSLOG_CONFIG_TAG_RCP_LWSD_STARTUP_LOG_SIZE "ccs.service.aasyslog.rcp_lwsd.startuplog.size"

/*!
 *  @brief RCP LWSD runtime log size
 */
#define AASYSLOG_CONFIG_TAG_RCP_LWSD_RUNTIME_LOG_SIZE "ccs.service.aasyslog.rcp_lwsd.runtimelog.size"

/*!
 *  @brief RCP LWSDL startup log size
 */
#define AASYSLOG_CONFIG_TAG_RCP_LWSDL_STARTUP_LOG_SIZE "ccs.service.aasyslog.rcp_lwsdl.startuplog.size"

/*!
 *  @brief RCP LWSDL runtime log size
 */
#define AASYSLOG_CONFIG_TAG_RCP_LWSDL_RUNTIME_LOG_SIZE "ccs.service.aasyslog.rcp_lwsdl.runtimelog.size"

/*!
 *  @brief RCP Provider startup log size
 */
#define AASYSLOG_CONFIG_TAG_RCP_PROVIDER_STARTUP_LOG_SIZE "ccs.service.aasyslog.rcp_provider.startuplog.size"

/*!
 *  @brief RCP Provider runtime log size
 */
#define AASYSLOG_CONFIG_TAG_RCP_PROVIDER_RUNTIME_LOG_SIZE "ccs.service.aasyslog.rcp_provider.runtimelog.size"

/*!
 *  @brief RCP SysComDataProvider startup log size
 */
#define AASYSLOG_CONFIG_TAG_RCP_SYSCOMDATAPROVIDER_STARTUP_LOG_SIZE "ccs.service.aasyslog.rcp_SyscomDataProvider.startuplog.size"

/*!
 *  @brief RCP SysComDataProvider runtime log size
 */
#define AASYSLOG_CONFIG_TAG_RCP_SYSCOMDATAPROVIDER_RUNTIME_LOG_SIZE "ccs.service.aasyslog.rcp_SyscomDataProvider.runtimelog.size"

/*!
 *  @brief LFS startup log size
 */
#define AASYSLOG_CONFIG_TAG_LFS_STARTUP_LOG_SIZE "ccs.service.aasyslog.lfs.startuplog.size"

/*!
 *  @brief LFS runtime log size
 */
#define AASYSLOG_CONFIG_TAG_LFS_RUNTIME_LOG_SIZE "ccs.service.aasyslog.lfs.runtimelog.size"

/**
 *  @brief  Defines AaSysLog threads nice level. By default the level is 0.
 */
#define AASYSLOG_CONFIG_TAG_THREAD_NICE_LEVEL      "ccs.service.aasyslog.thread.nice.level"

/**
 *  @brief  Path where logs are stored while log saving on ram disc is enabled
 */
#define AASYSLOG_CONFIG_TAG_RAM_PATH     "ccs.service.aasyslog.rampath"

/**
 *  @brief  Substring search time in seconds between snapshot trigger and start of the next search.
 */
#define AASYSLOG_CONFIG_TAG_SUBSTRING_SEARCH_DELAY     "ccs.service.aasyslog.substring.search.delay"

/**
 *  @brief  Substring search maximum searching patterns.
 */
#define AASYSLOG_CONFIG_TAG_SUBSTRING_SEARCH_MAXIMUM_PATTERNS     "ccs.service.aasyslog.substring.search.maximum.patterns"

/**
 *  @brief  Substring search enable feature.
 */
#define AASYSLOG_CONFIG_TAG_SUBSTRING_SEARCH_ENABLED     "ccs.service.aasyslog.substring.search.enabled"

/**
 *  @brief  String, which existence in logs has to trigger indication to one who subscribed on it.
 */
#define AASYSLOG_CONFIG_TAG_SEARCH_STRING1     "ccs.service.aasyslog.substring.search.string.1"

/**
 *  @brief  Count of postmortem logs consisting of runtime and startup logs from previous executions. In other words how many previous executions will be covered by logs.
 *  If the tag is not set, then default value is 2 for runtime logs and 0 for startup logs.
 */
#define AASYSLOG_CONFIG_TAG_POSTMORTEM_LOG_COUNT     "ccs.service.aasyslog.postmortem.log.count"

/**
 *  @brief  Path where postmortem logs, consisting of runtime and startup logs from previous executions, are stored.
 *  If the tag is not set, then default path is /rpram/aasyslog/ for runtime and /ram/ for startup logs.
 */
#define AASYSLOG_CONFIG_TAG_POSTMORTEM_LOG_PATH     "ccs.service.aasyslog.postmortem.log.path"

/**
 *  @brief  Maximum length of domain name
 */
#define AASYSLOG_MAX_DOMAIN_NAME_LENGTH 30

/**
 *  @brief  Minimum domain runtime buffer size
 */
#define MINIMUM_RUNTIME_LOG_SIZE    (1024*50)

/**
 *  @brief  Default RAM device directory.
 */
#define AASYSLOG_DEFAULT_RAM_PATH "/rpram/syslog/"

/**
 *  @brief  IP address with array element 0 being the MSB, for example with 192.168.1.1 the "192" would be at index 0
 */
typedef u8 TIp4Octets[AASYSLOG_IP_ADDR_SIZE];

/**
 *  @brief  Domain buffer register status.
 */
typedef enum EAaSysLogDomainBufferRegister
{
    EAaSysLogDomainBufferRegister_Ok                     = 0,
    EAaSysLogDomainBufferRegister_Exists                 = 1,
    EAaSysLogDomainBufferRegister_QuotaExceeded          = 2,
    EAaSysLogDomainBufferRegister_RuntimeLogSizeTooSmall = 3,
    EAaSysLogDomainBufferRegister_NOk                    = 4
}EAaSysLogDomainBufferRegister;

/**
 *  @brief  Domain buffer setting status.
 */
typedef enum EAaSysLogDomainBufferSet
{
    EAaSysLogDomainBufferSet_Ok                  = 0,
    EAaSysLogDomainBufferSet_BufferNotRegistered = 1,
    EAaSysLogDomainBufferSet_BufferAlreadySet    = 2,
    EAaSysLogDomainBufferSet_NOk                 = 3
}EAaSysLogDomainBufferSet;

/**
 *  @brief  Type for the runtime log coverage vealue.
 */
typedef enum EAaSysLogRuntimeLogDomainCoverage
{
    EAaSysLogRuntimeLogDomainCoverage_Partial     = 0,     /*runtime log is requested only from specified log domain */
    EAaSysLogRuntimeLogDomainCoverage_Full        = 1,     /*runtime log is requested from all registered log domains*/
    EAaSysLogRuntimeLogDomainCoverage_NotValid    = 2
} EAaSysLogRuntimeLogDomainCoverage;

/**
 *  @brief Type for remote syslog start operation result
 */
typedef enum EAaSysLogRemoteSyslogStartStatus
{
    /**
     *  @brief Procedure started successfully
     */
    EAaSysLogRemoteSyslogStartStatus_Ok               = 0,
    /**
     *  @brief Wrong parameters
     */
    EAaSysLogRemoteSyslogStartStatus_WrongParameters  = 1,
    /**
     *  @brief Streaming to remote syslog server already active
     */
    EAaSysLogRemoteSyslogStartStatus_AlreadyRunning   = 2,
    /**
     *  @brief Remote syslog server not stopped yet
     */
    EAaSysLogRemoteSyslogStartStatus_StopInProgress   = 3,
    /**
     *  @brief Remote syslog server not started yet
     */
    EAaSysLogRemoteSyslogStartStatus_StartInProgress  = 4,
    /**
     *  @brief Procedure start failed
     */
    EAaSysLogRemoteSyslogStartStatus_Nok              = 5

} EAaSysLogRemoteSyslogStartStatus;

/**
 *  @brief Type for remote syslog stop operation result
 */
typedef enum EAaSysLogRemoteSyslogStopStatus
{
    /**
     *  @brief Procedure stopped successfully
     */
    EAaSysLogRemoteSyslogStopStatus_Ok              = 0,
    /**
     *  @brief Streaming to remote syslog server not active
     */
    EAaSysLogRemoteSyslogStopStatus_NotRunning      = 1,
    /**
     *  @brief Streaming to remote not started yet
     */
    EAaSysLogRemoteSyslogStopStatus_StartInProgress = 2,
    /**
     *  @brief Procedure previous stop in progress
     */
    EAaSysLogRemoteSyslogStopStatus_StopInProgress  = 3,
    /**
     *  @brief Procedure stop failed
     */
    EAaSysLogRemoteSyslogStopStatus_Nok             = 4

} EAaSysLogRemoteSyslogStopStatus;

/**
 *  @brief  Feature Ring Buffer register status.
 */
typedef enum EAaSysLogFeatureBufferRegister
{
    EAaSysLogFeatureBufferRegister_Ok        = 0,
    EAaSysLogFeatureBufferRegister_Exists    = 1,
    EAaSysLogFeatureBufferRegister_NOk       = 2,
    EAaSysLogFeatureBufferRegister_NotNeeded = 3
}EAaSysLogFeatureBufferRegister;

/**
 *  @brief  Feature Ring Buffer dump to file status.
 */
typedef enum EAaSysLogFeatureBufferDumpToFile
{
    EAaSysLogFeatureBufferDumpToFile_Ok      = 0,
    EAaSysLogFeatureBufferDumpToFile_NOk     = 1,
    EAaSysLogFeatureBufferDumpToFile_Invalid = 2
}EAaSysLogFeatureBufferDumpToFile;

/**
 *  @brief  Feature Ring Buffer dump to log status.
 */
typedef enum EAaSysLogFeatureBufferDumpToLog
{
    EAaSysLogFeatureBufferDumpToLog_Ok      = 0,
    EAaSysLogFeatureBufferDumpToLog_NOk     = 1
}EAaSysLogFeatureBufferDumpToLog;

typedef enum EAaSysLogSubstringSearchStatus
{
    EAaSysLogSubstringSearchStatus_Ok = 0,              /**< Ok, substring search started */
    EAaSysLogSubstringSearchStatus_InvalidParams,       /**< Invalid parameters were given in AASYSLOG_SUBSTRING_SEARCH_REGISTER_REQ or AASYSLOG_SUBSTRING_SEARCH_UNREGISTER_REQ */
    EAaSysLogSubstringSearchStatus_AlreadyRegistered,   /**< Given string is already being searched */
    EAaSysLogSubstringSearchStatus_NotRegistered,       /**< Substring Id from AASYSLOG_SUBSTRING_SEARCH_UNREGISTER_REQ is not registered */
    EAaSysLogSubstringSearchStatus_Disabled,            /**< Searching currently disabled, registrations are refused */
    EAaSysLogSubstringSearchStatus_Busy,                /**< Max allowed number of searched strings reached */
    EAaSysLogSubstringSearchStatus_Error                /**< Error while trying to launch searching */
}EAaSysLogSubstringSearchStatus;

/**
 *  @brief  System feature buffer register status.
 */
typedef enum EAaSysLogSystemFeatureBufferRegister
{
    EAaSysLogSystemFeatureBufferRegister_Ok                   = 0, /**< Ok, system feature buffer registered */
    EAaSysLogSystemFeatureBufferRegister_Exists               = 1, /**< System feature buffer already exists. Buffer not registered */
    EAaSysLogSystemFeatureBufferRegister_InvalidConfiguration = 2, /**< Provided wrong configuration. Buffer not registered */
    EAaSysLogSystemFeatureBufferRegister_Disabled             = 3, /**< System feture bufers are disabled. Buffer not registered */
    EAaSysLogSystemFeatureBufferRegister_Error                = 4, /**< Other error. Buffer not registered */
    EAaSysLogSystemFeatureBufferRegister_MasterNidNotSet      = 5  /**< Master node ID is not set. Buffer not registered */
}EAaSysLogSystemFeatureBufferRegister;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* _MCU_IFAASYSLOG_DEF_H_ */
