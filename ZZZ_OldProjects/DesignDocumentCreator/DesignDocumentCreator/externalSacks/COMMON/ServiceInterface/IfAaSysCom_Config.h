/* ****************************************************************************
 * @brief  AaSysCom config interface header file.
 * @module AaSysCom
 * @owner  Vedran Cundekovic
 *
 * Copyright 2014 Nokia Solutions and Networks. All rights reserved.
 * ****************************************************************************/

#ifndef IF_COMMON_AASYSCOM_CONFIG_H
#define IF_COMMON_AASYSCOM_CONFIG_H
#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @addtogroup dgAaSysComCommon AaSysCom Common
 * @ingroup dgAaSysCom
 *
 * @{
 */

/**
********************************************************************************
*
* @brief        Initializes AaSysCom.
*
*               This function must be called first in system that wants to use
*               AaSysCom. The function is used in CE startup phase internally.
*               by CC&S.
*
* @return       The function returns nothing.
*
*******************************************************************************/
void AaSysComInit(void);

/** @} */


#ifdef __cplusplus
}
#endif

#endif /* IF_COMMON_AASYSCOM_CONFIG_H */
