/**
*******************************************************************************
* @file
*
* @brief                 AaSysLog API configuration interface
*
* Copyright 2016 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _RT_DSP_IFAASYSLOG_MSG_H
#define _RT_DSP_IFAASYSLOG_MSG_H

#include <IfAaSysLog_Defs.h>

/*----------------------- DOXYGEN GROUPS --------------------------------------*/
/**
* @addtogroup dgUpCcs U-Plane specific CC&S API
* @{
*/

/**
* @addtogroup dgUpCcsAaSysLog AaSysLog API
* @{
*/

/**
* @addtogroup dgUpCcsRtDspAaSysLog AaSysLog API for RT and OSECK DSP nodes
* @{
*/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  @brief  Message: Create runtime log request.
*/

typedef struct AaSysLogRuntimeLogReq
{
    /*!
     *  @brief  Maximum size of runtime log.
     *
     *  If zero is given, all data that are available are stored.
     *
     *  If file is compressed this parameters does not limit the compressed
     *  file size, it limits the ASCII log size inside compressed file.
     */
    u32 size;
    /*!
     *  @brief  Name of runtime log file.
     *
     *  If name is not given (NULL), unit system name is used for file prefix
     *  and file is compressed. Example Unit1_Runtime.zip file is saved to
     *  temporary disk.
     *
     *  If name contains file extension ".zip" then file is compressed,
     *  otherwise it is ASCII log file.
     */
    u8  name[AASYSLOG_MAX_FILE_NAME_LENGTH];
}AaSysLogRuntimeLogReq;


#ifdef __cplusplus
}
#endif

/** @} */   /* dgUpCcsRtDspAaSysLog */
/** @} */   /* dgUpCcsAaSysLog */
/** @} */   /* dgUpCcs */

#endif  /* _RT_DSP_IFAASYSLOG_MSG_H */
