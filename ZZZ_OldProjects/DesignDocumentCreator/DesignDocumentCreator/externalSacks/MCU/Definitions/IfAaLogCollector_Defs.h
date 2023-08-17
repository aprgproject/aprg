/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/
#ifndef IFAALOGCOLLECTOR_DEF_H_
#define IFAALOGCOLLECTOR_DEF_H_

/************************** INCLUDED FILES ************************************/

#include <glo_def.h>
#include "CcsCommon.h"

#ifdef __cplusplus
extern "C"{
#endif

/************************** DOXYGEN GROUPS ************************************/

/**
 *  @defgroup dgAaLogCollectorApi MCU AaLogCollector Definitions
 *  @ingroup  dgAaLogCollector
 *
 *  Application Programming Interface.
 *
 *  For more information see API specification on IMS:
 *
 */
 /*@{*/
/************************** PUBLIC DECLARATIONS *******************************/

/** @brief  RAM device directory path. */
#define AALOGCOLLECTOR_CONFIG_TAG_DIR_PATH  "ccs.service.aalogcollector.dirpath"

/** @brief  Default RAM device directory path. */
#define AALOGCOLLECTOR_DEFAULT_DIR_PATH     "/rpram/syslog/"

/** @brief AaLogCollector operating mode selector. */
typedef enum EAaLogCollectorLogType
{
    EAaLogCollectorLogType_Syslog = 0,
    EAaLogCollectorLogType_MsgTrace,
    EAaLogCollectorLogType_All,
    EAaLogCollectorLogType_Last
} EAaLogCollectorLogType;

/** @brief AaLogCollector return values. */
typedef enum EAaLogCollectorRetVal
{
    EAaLogCollectorRetVal_NoError = 0,
    EAaLogCollectorRetVal_Error,
    EAaLogCollectorRetVal_InvalidParameter,
    EAaLogCollectorRetVal_ResourceNotAvailable,
    EAaLogCollectorRetVal_NotSupported,         /**< Indicate API is not supported on specific platform. */
    EAaLogCollectorRetVal_AlreadyRunning,       /**< Server already running */
    EAaLogCollectorRetVal_NotRunning,           /**< Server not running. */
    EAaLogCollectorRetVal_Last
} EAaLogCollectorRetVal;
/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* IFAALOGCOLLECTOR_DEF_H */
