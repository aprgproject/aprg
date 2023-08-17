/** @file
 *  @brief                 AaSysInfo messages definitions
 *
 *  $HeadURL$
 *  $LastChangedRevision$
 *  $LastChangedDate$
 *  $Author$
 *  $Copyright: Copyright 2018 Nokia. All right reserved.$
 */

#ifndef _MCU_IFAASYSINFO_MSG_H_
#define _MCU_IFAASYSINFO_MSG_H_

#include <CcsCommon.h>
#include <glo_def.h>

#include "../../COMMON/Messages/IfAaSysInfo_Msg.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
************************************************************************************************
* @defgroup dgAaSysInfoMsg AaSysInfo Messages
* @ingroup  dgAaSysInfo
*/
/*@{*/
/**
* @brief AaSysInfo CPU overload indication message
*
* @par Description
* This message is used to inform about exceeding CPU usage quota
* Quota thresholds are defined in SysinfoQuota.xml
* To receive this message application has to subscribe for in using AaSysMb
*
* @par Message Id
* AASYSINFO_CPU_OVERLOAD_IND_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AASYSINFO_CPU_OVERLOAD_IND_MSG          0x1321  /* !- SIGNO(struct SAaSysInfoCpuOverloadIndMsg) -!  */

/**
* @brief AaSysInfo CPU core set overload indication message
*
* @par Description
* This message is used to inform about exceeding CPU core set usage quota
* Quota thresholds are defined in SysinfoQuota.xml
* To receive this message application has to subscribe for in using AaSysMb
*
* @par Message Id
* AASYSINFO_CPU_CORE_SET_OVERLOAD_IND_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AASYSINFO_CPU_CORE_SET_OVERLOAD_IND_MSG 0x1322  /* !- SIGNO(struct SAaSysInfoCpuCoreSetOverloadIndMsg) -!  */

/**
* @brief AaSysInfo memory overload indication message
*
* @par Description
* This message is used to inform about exceeding memory usage quota
* Quota thresholds are defined in SysinfoQuota.xml
* To receive this message application has to subscribe for in using AaSysMb
*
* @par Message Id
* AASYSINFO_MEMORY_OVERLOAD_IND_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AASYSINFO_MEMORY_OVERLOAD_IND_MSG       0x1323  /* !- SIGNO(struct SAaSysInfoMemoryOverloadIndMsg) -!  */

/**
* @brief AaSysInfo message pool overload indication message
*
* @par Description
* This message is used to inform about exceeding AaSyscom message pool usage quota
* Quota thresholds are defined in SysinfoQuota.xml
* To receive this message application has to subscribe for in using AaSysMb.
* This message will be published in the local zone.
*
* @par Message Id
* AASYSINFO_MSG_POOL_OVERLOAD_IND_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AASYSINFO_MSG_POOL_OVERLOAD_IND_MSG       0x13AF  /* !- SIGNO(struct SAaSysInfoMsgPoolOverloadIndMsg) -!  */

/**
* @brief Overload status enum
**/
typedef enum EAaSysInfoOverloadStatus
{
    EAaSysInfoOverloadStatus_Begin,      /**< overload begin */
    EAaSysInfoOverloadStatus_End,        /**< overload end */
    EAaSysInfoOverloadStatus_Invalid     /**< invalid value */
} EAaSysInfoOverloadStatus;

/**
* @brief Measurement type enum
**/
typedef enum EAaSysInfoCPUMeasurementType
{
    EAaSysInfoCPUMeasurementType_Total,   /**< total cpu usage */
    EAaSysInfoCPUMeasurementType_Normal,  /**< normal cpu usage, without background usage */
    EAaSysInfoCPUMeasurementType_Invalid  /**< invalid value */
} EAaSysInfoCPUMeasurementType;

/**
************************************************************************************************
* @brief AaSysInfo AaSysInfo CPU overload indication message structure
* @param id of the measurement
* @param status of overload
* @param type of measurement
* @param current load in percent
* @param load threshold in percent
*
* @par Description
* This message is used to inform about exceeding CPU usage quota
*
* @par Message Id
* AASYSINFO_CPU_OVERLOAD_IND_MSG
***********************************************************************************************/
typedef struct SAaSysInfoCpuOverloadIndMsg {
    u32                          measurementId;
    EAaSysInfoOverloadStatus     overloadStatus;
    EAaSysInfoCPUMeasurementType measurementType;
    u32                          currentLoad;       /* in percent */
    u32                          definedThreshold; /* in percent */
} SAaSysInfoCpuOverloadIndMsg;

/**
 *  @brief  Maximum count of CPU cores supported by CPU core set measurement
 */
#define MAX_CORES 64

/**
************************************************************************************************
* @brief AaSysInfo AaSysInfo CPU core set overload indication message structure
* @param id of the measurement
* @param status of overload
* @param type of measurement
* @param current load in percent
* @param load threshold in percent
* @param id of core set
* @param number of cores
* @param list of assigned cores
*
* @par Description
* This message is used to inform about exceeding CPU core set usage quota
*
* @par Message Id
* AASYSINFO_CPU_CORE_SET_OVERLOAD_IND_MSG
***********************************************************************************************/
typedef struct SAaSysInfoCpuCoreSetOverloadIndMsg {
    u32                          measurementId;
    EAaSysInfoOverloadStatus     overloadStatus;
    EAaSysInfoCPUMeasurementType measurementType;
    u32                          currentLoad;       /* in percent */
    u32                          definedThreshold; /* in percent */
    u32                          coreSetId;
    u32                          numberOfCores;     /* number of CPU cores in core set */
    u32                          cores[MAX_CORES];   /* CPU cores assigned to this core set */
} SAaSysInfoCpuCoreSetOverloadIndMsg;

/**
************************************************************************************************
* @brief AaSysInfo AaSysInfo memory overload indication message structure
* @param id of the measurement
* @param status of overload
* @param type of measurement
* @param current load in percent
* @param load threshold in percent

*
* @par Description
* This message is used to inform about exceeding memory usage quota
*
* @par Message Id
* AASYSINFO_MEMORY_OVERLOAD_IND_MSG
***********************************************************************************************/
typedef struct SAaSysInfoMemoryOverloadIndMsg {
    u32                          measurementId;
    EAaSysInfoOverloadStatus     overloadStatus;
    u32                          currentLoad;       /* in percent */
    u32                          definedThreshold;  /* in percent */
} SAaSysInfoMemoryOverloadIndMsg;

/**
************************************************************************************************
* @brief AaSysInfo AaSysInfo msgpool overload indication message structure
* @param id of the measurement
* @param status of overload
* @param type of measurement
* @param current load in percent
* @param load threshold in percent

*
* @par Description
* This message is used to inform about exceeding msgpool usage quota
*
* @par Message Id
* AASYSINFO_MSG_POOL_OVERLOAD_IND_MSG
***********************************************************************************************/
typedef struct SAaSysInfoMsgPoolOverloadIndMsg {
    u32                          measurementId;
    EAaSysInfoOverloadStatus     overloadStatus;
    u32                          currentLoad;       /* in percent */
    u32                          definedThreshold;  /* in percent */
} SAaSysInfoMsgPoolOverloadIndMsg;
/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* _MCU_IFAASYSINFO_MSG_H_ */

