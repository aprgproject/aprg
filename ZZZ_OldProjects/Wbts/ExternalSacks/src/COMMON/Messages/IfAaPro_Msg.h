/**
*******************************************************************************
* @brief                 AaPro messages header
* @module                AaPro
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
* Copyright 2019 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _COMMON_IFAAPRO_MSG_H
#define _COMMON_IFAAPRO_MSG_H

#include <CcsCommon.h>
#include <glo_def.h>
#include <IfAaPro_Defs.h>

/*----------------------- INCLUDED FILES --------------------------------------*/

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup dgAaPro
 * @{
 */


/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

#define AAPRO_NODE_POLL_REQ_MSG  0x111C  /* !- SIGNO(struct SAaProNodePollReq) -! */
#define AAPRO_NODE_POLL_RESP_MSG 0x111D  /* !- SIGNO(struct SAaProNodePollResp) -! */

/** @brief CC&S node polling request message.
*
* Message AAPRO_NODE_POLL_REQ_MSG
*/
typedef struct SAaProNodePollReq
{
    u32      transactionId;  /**< To identify request and response message belonging to same procedure */
} SAaProNodePollReq;

/** @brief CC&S node pooling response message.
*
* Message AAPRO_NODE_POLL_RESP_MSG
*/
typedef struct SAaProNodePollResp
{
    EAaProNodeAppStatus appStatus;      /**< CC&S node application status info */
    u32                 transactionId;  /**< Transaction Id to identify request and response message belonging to same procedure */
} SAaProNodePollResp;

/**
*******************************************************************************
*
*   @brief Static SIC CP ID for CPU load measurement service
*/
#define AAPRO_CPULOAD_SERVICE_CPID 0x0618

/**
*******************************************************************************
*
*   @brief SIC message IDs for CPU load measurement service
* @{
*/
#define AAPRO_START_IDLE_MEAS_REQ_MSG 0x0ADD	/* !- SIGNO(struct void) -! */
#define AAPRO_STOP_IDLE_MEAS_REQ_MSG  0x0ADE	/* !- SIGNO(struct void) -! */
#define AAPRO_IDLE_MEAS_REQ_MSG       0x0ADF	/* !- SIGNO(struct void) -! */
#define AAPRO_IDLE_MEAS_ACK_MSG       0x0AE0	/* !- SIGNO(struct SAaProIdleMeasAckMsg) -!  */
/** @} */

/**
*******************************************************************************
*
*   @brief SIC message struct AAPRO_IDLE_MEAS_ACK_MSG for CPU load measurement service
*/
typedef struct SAaProIdleMeasAckMsg {
  u32 cpuload;         /** In percent, in DSP default period of measurements is 100ms, 
                           it can be modified using 
                           ERadDspHwApi_CpuLoadMeasurementsDefaultPeriod R&D flag. */
  u32 idleCycleCount_Low;   /** Lower word in cycles, valid for DSP, 0 otherwise,
                                idleCycleCount_Low and idleCycleCount_High should
                                be combined to get the complete 64 bit value of
                                idleCycleCount. */
  u32 idleCycleCount_High;  /** Higher word in cycles, valid for DSP, 0 otherwise,
                                idleCycleCount_Low and idleCycleCount_High should
                                be combined to get the complete 64 bit value of
                                idleCycleCount. */
  u32 totalCycleCount_Low;  /** Lower word in cycles, valid for DSP, 0 otherwise,
                                totalCycleCount_Low and totalCycleCount_High should
                                be combined to get the complete 64 bit value of
                                totalCycleCount. */
  u32 totalCycleCount_High; /** Higher word in cycles, valid for DSP, 0 otherwise,
                                totalCycleCount_Low and totalCycleCount_High should
                                be combined to get the complete 64 bit value of
                                totalCycleCount. */
} SAaProIdleMeasAckMsg;

/**
*******************************************************************************
*
*   @brief SIC message struct AAPRO_IDLE_MEAS_ACK_MSG
*/

/**
*******************************************************************************
*
*   @brief Basic messages for AaPro CPU/Memory load supervision msg API
*/

/* Static cp id's for Supervision service tasks */
#define AAPRO_CPUMEMSUPERVISION_SERVICE_CPID 0x062A

/* Messages from API to service */
#define AAPRO_CE_CPULOAD_SUPERVISION_REGISTER_REQ_MSG    0x0B4B  /* !- SIGNO(struct SAaProCeCpuloadSupervisionRegisterReqMsg) -! */
#define AAPRO_CE_CPULOAD_SUPERVISION_REGISTER_RESP_MSG   0x0B4C  /* !- SIGNO(struct SAaProCeCpuloadSupervisionRegisterRespMsg) -! */
#define AAPRO_CE_CPULOAD_SUPERVISION_DEREGISTER_MSG      0x0B4D  /* !- SIGNO(struct SAaProCeCpuloadSupervisionDeregisterMsg) -! */
#define AAPRO_CE_CPULOAD_SUPERVISION_TIMER_MSG           0x0B4E  /* !- SIGNO(struct SAaProCeCpuloadSupervisionTimerMsg) -! */
#define AAPRO_CE_CPULOAD_SUPERVISION_LOGTIMER_MSG        0x0B4F  /* !- SIGNO(struct SAaProCeCpuloadSupervisionLogtimerMsg) -! */
#define AAPRO_CE_MEMORY_SUPERVISION_REGISTER_REQ_MSG     0x0B50  /* !- SIGNO(struct SAaProCeMemorySupervisionRegisterReqMsg) -! */
#define AAPRO_CE_MEMORY_SUPERVISION_REGISTER_RESP_MSG    0x0B51  /* !- SIGNO(struct SAaProCeMemorySupervisionRegisterRespMsg) -! */
#define AAPRO_CE_MEMORY_SUPERVISION_DEREGISTER_MSG       0x0B52  /* !- SIGNO(struct SAaProCeMemorySupervisionDeregisterMsg) -! */
#define AAPRO_CE_MEMORY_SUPERVISION_TIMER_MSG            0x0B53  /* !- SIGNO(struct SAaProCeMemorySupervisionTimerMsg) -! */

/**
*******************************************************************************
*
*   @brief Message structures for AaPro CPU/Memory load supervision msg API
*/

typedef struct SAaProCeCpuloadSupervisionRegisterReqMsg {
    u32 level;
    u32 interval;
    EAaProMeasurementType measurementType;
    u32 logging;
    TAaSysComSicad sicAddr;
} SAaProCeCpuloadSupervisionRegisterReqMsg;

typedef struct SAaProCeCpuloadSupervisionRegisterRespMsg {
    TAaProMeasurementIdType measurementId;
} SAaProCeCpuloadSupervisionRegisterRespMsg;

typedef struct SAaProCeCpuloadSupervisionDeregisterMsg {
    TAaProMeasurementIdType measurementId;
} SAaProCeCpuloadSupervisionDeregisterMsg;

typedef struct SAaProCeCpuloadSupervisionTimerMsg {
    TAaProMeasurementIdType measurementId;
} SAaProCeCpuloadSupervisionTimerMsg;

typedef struct SAaProCeCpuloadSupervisionLogtimerMsg {
    TAaProMeasurementIdType measurementId;
} SAaProCeCpuloadSupervisionLogtimerMsg;

typedef struct SAaProCeMemorySupervisionRegisterReqMsg {
    u32 level;
    TAaSysComSicad sicAddr;
} SAaProCeMemorySupervisionRegisterReqMsg;

typedef struct SAaProCeMemorySupervisionRegisterRespMsg {
    TAaProMeasurementIdType measurementId;
} SAaProCeMemorySupervisionRegisterRespMsg;

typedef struct SAaProCeMemorySupervisionDeregisterMsg {
    TAaProMeasurementIdType measurementId;
} SAaProCeMemorySupervisionDeregisterMsg;

typedef struct SAaProCeMemorySupervisionTimerMsg {
    TAaProMeasurementIdType measurementId;
} SAaProCeMemorySupervisionTimerMsg;


/**
*******************************************************************************
*
*   @brief SIC message IDs for CPU load and memory supervision service
* @{
*/
#define AAPRO_CE_CPULOAD_OVERLOAD_IND_MSG 0x0B49	/* !- SIGNO(struct SAaProCeCpuLoadOverloadIndMsg) -!  */
#define AAPRO_CE_MEMORY_OVERLOAD_IND_MSG  0x0B4A	/* !- SIGNO(struct SAaProCeMemoryOverloadIndMsg) -!  */
/** @} */

/**
*******************************************************************************
*
*   @brief SIC message struct SAaProCeCpuLoadOverloadIndMsg for CPU load measurement service
*/
typedef struct SAaProCeCpuLoadOverloadIndMsg {
  TAaProMeasurementIdType measurementId;
  EAaProOverloadStatus overloadStatus;
  EAaProMeasurementType measurementType; /** Since DSP is working on OSE, load type is limited to
                                             EAaProMeasurementType_Normal */
  u32 currentNormalCpuLoad; /** in percent. @DSP this variable store DSP CPU load */
  u32 currentBackgroundCpuLoad; /** in percent. Not used @DSP */
  u32 currentIrqCpuLoad; /** in percent. Not used @DSP */
} SAaProCeCpuLoadOverloadIndMsg;

/**
*******************************************************************************
*
*   @brief SIC message struct SAaProCeMemoryOverloadIndMsg for CPU load measurement service
*/
typedef struct SAaProCeMemoryOverloadIndMsg {
  TAaProMeasurementIdType measurementId;
  EAaProOverloadStatus overloadStatus;
  u32 memoryUsage; /* in percent */
} SAaProCeMemoryOverloadIndMsg;



/** @} end: @addtogroup dgAaPro */




#ifdef __cplusplus
}
#endif

#endif /*  _COMMON_IFAAPRO_MSG_H */
