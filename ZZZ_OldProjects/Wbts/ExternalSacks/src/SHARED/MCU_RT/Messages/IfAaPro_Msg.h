/**
*******************************************************************************
* @file                  $HeadURL: $
* @version               $LastChangedRevision: $
* @date                  $LastChangedDate: $
*
* @brief                 AaPro messages header for MCU and RT
* @module                AaPro
*
* Copyright 2017 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAAPRO_MSG_H
#define _MCU_RT_IFAAPRO_MSG_H

/*----------------------- INCLUDED FILES --------------------------------------*/

#include <CcsCommon.h>
#include <IfAaPro_Defs.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup dgAaPro
 * @{
 */


/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/**
*******************************************************************************
*
*   @brief SIC message IDs for CPU load measurement service
*
*   CPID of the service is defined by @par AAPRO_CPULOAD_SERVICE_CPID
*
* @{
*/
#define AAPRO_START_LOAD_MEAS_REQ_MSG  0x1406   /* !- SIGNO(struct SAaProStartLoadMeasReqMsg) -! */
#define AAPRO_START_LOAD_MEAS_RESP_MSG 0x1407   /* !- SIGNO(struct SAaProStartLoadMeasRespMsg) -! */
#define AAPRO_STOP_LOAD_MEAS_REQ_MSG   0x1408   /* !- SIGNO(struct SAaProStopLoadMeasReqMsg) -! */
#define AAPRO_STOP_LOAD_MEAS_RESP_MSG  0x1409   /* !- SIGNO(struct SAaProStopLoadMeasRespMsg) -! */
#define AAPRO_LOAD_MEAS_REQ_MSG        0x140A   /* !- SIGNO(struct SAaProLoadMeasReqMsg) -! */
#define AAPRO_LOAD_MEAS_RESP_MSG       0x140B   /* !- SIGNO(struct SAaProLoadMeasRespMsg) -!  */
/** @} */

/**
*******************************************************************************
*
*   @brief Message for requesting start of CPU load measurement
*
*   Message ID is @par AAPRO_START_LOAD_MEAS_REQ_MSG
*/
typedef struct SAaProStartLoadMeasReqMsg
{
    u32 reserved;                          /**< Not used, must be initialized to zero. */
} SAaProStartLoadMeasReqMsg;

/**
*******************************************************************************
*
*   @brief Message for responding to start of CPU load measurement request
*
*   Message ID is @par AAPRO_START_LOAD_MEAS_RESP_MSG
*/
typedef struct SAaProStartLoadMeasRespMsg
{
    TAaProMeasurementIdType measurementId; /**< ID of the started measurement or
                                                EAaProMeasurementIdType_InvalidValue
                                                in case of failure. */
} SAaProStartLoadMeasRespMsg;

/**
*******************************************************************************
*
*   @brief Message for requesting CPU load measurement results of an active measurement
*
*   Message ID is @par AAPRO_LOAD_MEAS_REQ_MSG
*/
typedef struct SAaProLoadMeasReqMsg
{
    TAaProMeasurementIdType measurementId; /**< ID got from SAaProStartIdleMeasRespMsg. */
} SAaProLoadMeasReqMsg;

/**
*******************************************************************************
*
*   @brief Message for CPU load measurement results of an active measurement
*
*   Message ID is @par AAPRO_LOAD_MEAS_RESP_MSG
*
*   Results are calculated from start of measurement or from last request for
*   results.
*/
typedef struct SAaProLoadMeasRespMsg
{
    TAaProMeasurementIdType measurementId;  /**< ID given in SAaProIdleMeasReqMsg. */
    u32                     totalLoadPct;   /**< Total load (percents; parts per hundred). */
    u32                     coreCount;      /**< Number of cores in coreLoadPct. */
    u32                     coreLoadPct[1]; /**< Load per core (percents; parts per hundred). */
} SAaProLoadMeasRespMsg;

/**
*******************************************************************************
*
*   @brief Message for requesting stop of an active CPU load measurement
*
*   Message ID is @par AAPRO_STOP_LOAD_MEAS_REQ_MSG
*/
typedef struct SAaProStopLoadMeasReqMsg
{
    TAaProMeasurementIdType measurementId; /**< ID got from SAaProStartIdleMeasRespMsg. */
} SAaProStopLoadMeasReqMsg;

/**
*******************************************************************************
*
*   @brief Message for responding to stop of an active CPU load measurement
*
*   Message ID is @par AAPRO_STOP_LOAD_MEAS_RESP_MSG
*/
typedef struct SAaProStopLoadMeasRespMsg
{
    TAaProMeasurementIdType measurementId; /**< ID given in SAaProStopIdleMeasReqMsg. */
} SAaProStopLoadMeasRespMsg;


/** @} end: @addtogroup dgAaPro */


#ifdef __cplusplus
}
#endif

#endif /*  _MCU_RT_IFAAPRO_MSG_H */
