/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaPro common definitions
* @module                AaPro
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _COMMON_IFAAPRO_DEF_H
#define _COMMON_IFAAPRO_DEF_H

#ifdef CCS_OSECK
#define AAEU_PROCESS(name) void* name(void* arg)
#else
#define AAEU_PROCESS(name) void* name(void* arg __attribute__((unused)) )
#endif
/************************** INCLUDED FILES ************************************/

#include <stdio.h>
#include <CcsCommon.h>
#include <glo_def.h>
#include <IfAaSysTime_Defs.h>
#include <TAaSysComSicad.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup dgAaPro
 * @{
 */

/** @brief CC&S node application status */
typedef enum EAaProNodeAppStatus
{
    EAaProNodeAppStatus_Ok = 0,             /**< CC&S node has no errors */
    EAaProNodeAppStatus_CriticalFailed,     /**< CC&S node Critical Application failure */
    EAaProNodeAppStatus_NonCriticalFailed,  /**< CC&S node Non-critical Application failure */
    EAaProNodeAppStatus_NumOfStatuses       /**< The number of available statuses */
} EAaProNodeAppStatus;

/** @brief CC&S supervision flag values */
typedef enum EAaProSupervisionFlag
{
    EAaProSupervisionFlag_NotSupervised = 0,       /**< Application is not supervised by AaPro */
    EAaProSupervisionFlag_ReportExit,              /**< Non-Critical application exits, report exit */
    EAaProSupervisionFlag_CriticalFailed           /**< Critical application exits, reboot/report exit (platform dependent) */
} EAaProSupervisionFlag;

/************************** PUBLIC DECLARATIONS *******************************/
/** @brief AaPro max core number */
#define AAPRO_CPULOAD_MAX_CPU_CORES_IN_SMP 32

/** @brief AaPro tag should be set if AaPro is to service the HW watchdog.
* MCU specific behaviour:
* Values: Default(tag not set) = AaPro is handling watchdog, 0 = AaPro is not handling watchdog, 1 = AaPro is handling watchdog.*/
#define   AAPRO_TAG_WD_ENABLED "ccs.service.aapro.watchdog_enabled"



/** @name EU priority definitions
 *  For portability reasons the values for the euPriority argument of
 *  AaProEuCreateAndStart() have to be expressed in an abstracted way.
 *  This is due to different priority numbering schemes used by different
 *  operating systems. Thus the API shall define the following constants.
 *
 *  #EU_PRIORITY_01 corresponds to the highest priority and #EU_PRIORITY_32
 *  corresponds to the lowest priority. For  each supported OS these constants
 *  are mapped to corresponding priority values offered by the OS.
 * @{
 */
#define EU_PRIORITY_01        0
#define EU_PRIORITY_02        1
#define EU_PRIORITY_03        2
#define EU_PRIORITY_04        3
#define EU_PRIORITY_05        4
#define EU_PRIORITY_06        5
#define EU_PRIORITY_07        6
#define EU_PRIORITY_08        7
#define EU_PRIORITY_09        8
#define EU_PRIORITY_10        9
#define EU_PRIORITY_11       10
#define EU_PRIORITY_12       11
#define EU_PRIORITY_13       12
#define EU_PRIORITY_14       13
#define EU_PRIORITY_15       14
#define EU_PRIORITY_16       15
#define EU_PRIORITY_17       16
#define EU_PRIORITY_18       17
#define EU_PRIORITY_19       18
#define EU_PRIORITY_20       19
#define EU_PRIORITY_21       20
#define EU_PRIORITY_22       21
#define EU_PRIORITY_23       22
#define EU_PRIORITY_24       23
#define EU_PRIORITY_25       24
#define EU_PRIORITY_26       25
#define EU_PRIORITY_27       26
#define EU_PRIORITY_28       27
#define EU_PRIORITY_29       28
#define EU_PRIORITY_30       29
#define EU_PRIORITY_31       30
#define EU_PRIORITY_32       31
#define EU_PRIORITY_DEFAULT  12
#define EU_PRIORITY_INVALID  0xFF /**< Invalid priority definition */
/** @} */

/**
*******************************************************************************
*
*   @brief Static timer and hysteresis definitions for CPU load and memory supervision service
* @{
*/
#define CPULOAD_SUPERVISION_LOGTIMER_INTERVAL 60
#define MEMORY_SUPERVISION_TIMER_INTERVAL     60
#define SUPERVISION_HYSTERESIS_FACTOR         0.95
/** @} */

/** @brief Maximum EU name length (including terminating NUL) */
#define AAPRO_MAX_EU_NAME_LENGTH 20

/** @brief Maximum EE name length (including terminating NUL) */
#define AAPRO_MAX_EE_NAME_LENGTH 15

/** @brief Invalid EU id */
#define AAPRO_INVALID_EU_ID 0xFFFFFFFF

/** @brief Invalid EE id */
#define AAPRO_INVALID_EE_ID 0xFFFFFFFF

/** @brief Returns a pointer to the argumets given to the EU
* @return Pointer to EU arguments or GLO_NULL if no arguments given
*
*   @par Example:
*   @code
*   AAEU_PROCESS(exampleEuStart)
*   {
*     void* arguments = AAPRO_GET_EU_ARGS();
*
*     // Use arguments, no need to free them
*
*     return GLO_NULL;
*   }
*   @endcode
*/
#define AAPRO_GET_EU_ARGS() arg

/** @brief Supervision flags
 */
#define AAPRO_FLAG_CMDEXEC_REPORT_EXIT	(1 << 0)
#define AAPRO_FLAG_CMDEXEC_CRITICAL_EE  (1 << 1)

/**
*******************************************************************************
*
*   @brief Basic types for AaPro CPU load and memory supervision
*/
#define EAaProMeasurementIdType_InvalidValue 0

/** @brief AaPro EU exit handler type */
typedef void TAaProEuExitHandler (void* args);

/** @brief AaPro EU scheduling classes */
typedef enum EAaProEuSchedulingPolicy
{
    EAaProEuSchedulingPolicy_RealTime,
    EAaProEuSchedulingPolicy_Background
} EAaProEuSchedulingPolicy;

/** @brief AaPro public return codes */
typedef enum EAaProEuRetVal
{
    EAaProEuRetVal_NoError = 0,         /**< No errors occurred */
    EAaProEuRetVal_Error,               /**< An error exists */
    EAaProEuRetVal_InvalidValue,        /**< Invalid value */
    EAaProEuRetVal_OutOfResources,      /**< Lack of the resources */
    EAaProEuRetVal_PermissionDenied,    /**< Lack of permissions */
    EAaProEuRetVal_ChildKilled,         /**< The child process was terminated by a signal */
    EAaProEuRetVal_ChildCrashed,        /**< The child process produced a segfault */
    EAaProEuRetVal_NotSupported,        /**< The feature is not supported */
    EAaProEuRetVal_NonRootUser,         /**< The feature works only with root rights */
    EAaProEuRetVal_NumOfRetVals         /**< The number of available
                                             return values */

} EAaProEuRetVal;


/** @brief A type for EU entrypoint
* @param[in] args  Pointer to EU arguments
* @return Pointer to entrypoint return value or GLO_NULL
*/
typedef void* TAaProEuEntryPoint (void* args);


/** @brief Supervision status codes
 */
typedef enum EAaProEuNodeStatus {
  EAaProEuNodeStatus_Ok = 0,	/**< All processes alive. */
  EAaProEuNodeStatus_Nok	/**< At least one process missing. */
} EAaProEuNodeStatus;

/** @brief Self reset state
 */
typedef enum EAaProSelfResetStatus {
  EAaProSelfReset_Disabled = 0,
  EAaProSelfReset_Enabled
} EAaProSelfResetStatus;

/**
*******************************************************************************
*
*   @brief Basic types for AaPro CPU load and memory supervision
*/
typedef u32 TAaProMeasurementIdType;

/**
*******************************************************************************
*
*   @brief Basic type for AaPro CPU Load Data
*/
typedef struct SAaProCpuLoadData {
	TAaProMeasurementIdType measurementId;
	u32 cpuload; /** in percent */
	u32 numOfCores;
	u32 coreload[AAPRO_CPULOAD_MAX_CPU_CORES_IN_SMP];  /** in percent */
} SAaProCpuLoadData;

/**
*******************************************************************************
*
*   @brief Basic types for AaPro CPU overload status
*/
typedef enum EAaProOverloadStatus
{
    EAaProOverloadStatus_Begin,
    EAaProOverloadStatus_End
} EAaProOverloadStatus;

/**
*******************************************************************************
*
*   @brief Basic types for AaPro CPU load measurement type
*/
typedef enum EAaProMeasurementType
{
    EAaProMeasurementType_Normal,
    EAaProMeasurementType_Irq,
    EAaProMeasurementType_Total
} EAaProMeasurementType;

/**
*******************************************************************************
*
*   @brief Basic types for AaPro recovery type
*/
typedef enum EAaProRecoveryType
{
    EAaProRecoveryType_Error,
    EAaProRecoveryType_NoRecovery,
    EAaProRecoveryType_ProcessRestart,
    EAaProRecoveryType_VmReset
} EAaProRecoveryType;


 /** @} end: @addtogroup dgAaPro */

#ifdef __cplusplus
}
#endif

#endif /*  _COMMON_IFAAPRO_DEF_H */
