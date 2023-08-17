/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/
#ifndef IFAALOGCOLLECTOR_MSG_H
#define IFAALOGCOLLECTOR_MSG_H

/************************** INCLUDED FILES ************************************/

#include <glo_def.h>
#include "CcsCommon.h"

#ifdef __cplusplus
extern "C"{
#endif

/************************** PUBLIC DECLARATIONS *******************************/


/************************** DOXYGEN GROUPS ************************************/

 /**
 *  @defgroup dgAaLogCollectorMcuMsgs MCU AaLogCollector Messages
 *  @ingroup  dgAaLogCollector
 *
 *  Application Programming Interface.
 *
 *  For more information see API specification on IMS:
 */
 /*@{*/
/**
* @brief Start streaming of AaSysLog logs and AaTrace message traces to RamDisk.
*
* @par Description
* Message to start streaming of AaSysLog logs and AaTrace message traces to RamDisk.
*
* @par Message Id
* AALOG_COLLECTOR_START_RAMDISK_REQ_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AALOG_COLLECTOR_START_RAMDISK_REQ_MSG   0x0F49  /* !- SIGNO(struct SAaLogCollectorStartRamdiskReqMsg) -! */

/**
* @brief CC&S starts streaming AaSysLog logs and AaTrace message traces to RamDisk and replies.
*
* @par Description
* Message to start streaming of AaSysLog logs and AaTrace message traces to RamDisk.
*
* @par Message Id
* AALOG_COLLECTOR_START_RAMDISK_RESP_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AALOG_COLLECTOR_START_RAMDISK_RESP_MSG  0x0F4A  /* !- SIGNO(struct SAaLogCollectorStartRamdiskRespMsg) -! */

/**
* @brief Start streaming of AaSysLog logs and AaTrace message traces to RamDisk.
*
* @par Description
* Stop streaming of AaSysLog logs and AaTrace message traces to RamDisk.
*
* @par Message Id
* AALOG_COLLECTOR_STOP_RAMDISK_REQ_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AALOG_COLLECTOR_STOP_RAMDISK_REQ_MSG    0x0F4B  /* !- SIGNO(struct void) -! */

/**
* @brief CC&S stops streaming AaSysLog logs and AaTrace message traces to RamDisk.
*
* @par Description
* CC&S stops streaming AaSysLog logs and AaTrace message traces to RamDisk.
*
* @par Message Id
* AALOG_COLLECTOR_STOP_RAMDISK_RESP_MSG
*
* @par Restrictions:
*
***********************************************************************************************/
#define AALOG_COLLECTOR_STOP_RAMDISK_RESP_MSG   0x0F4C  /* !- SIGNO(struct SAaLogCollectorStopRamdiskRespMsg) -! */

#define AALOGCOLLECTOR_CPID	        0x0638


/************************** PUBLIC INTERFACES *********************************/

/**  @brief  Message: Start streaming of AaSysLog logs and AaTrace message traces to RamDisk. */
typedef struct SAaLogCollectorStartRamdiskReqMsg
{
   /*
    *  @brief  Maximum size of RamDisk log.
    *
    */
   u32 size;
   /*
    *  @brief  Type of logs to collect: syslog, message trace or both.
    *
    */
   u32 logType;
} SAaLogCollectorStartRamdiskReqMsg;

/** @brief  Message: CC&S starts streaming AaSysLog logs and AaTrace message traces to RamDisk and replies. */
typedef struct SAaLogCollectorStartRamdiskRespMsg
{
   u32 status;
} SAaLogCollectorStartRamdiskRespMsg;

/** @brief  Message: Start streaming of AaSysLog logs and AaTrace message traces to RamDisk. */
typedef struct SAaLogCollectorStopRamdiskRespMsg
{
   u32 status;
} SAaLogCollectorStopRamdiskRespMsg;
/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* IFAALOGCOLLECTOR_MSG_H */
