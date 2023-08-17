/* ****************************************************************************
 * @brief  AaSysCom config interface header file.
 * @module AaSysCom
 * @owner  Vedran Cundekovic
 *
 * Copyright 2014 Nokia Solutions and Networks. All rights reserved.
 * ****************************************************************************/

#ifndef IF_MCU_RT_AASYSCOM_CONFIG_H
#define IF_MCU_RT_AASYSCOM_CONFIG_H
#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
 * @addtogroup dgAaSysComMcuRt AaSysCom MCU_RT
 * @ingroup dgAaSysCom
 *
 * Common Computer and Support SW System Communication Configuration.
 *
 * @{
 */

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <glo_def.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include "../Definitions/IfAaSysCom_Defs.h"
#endif

/*----------------------- PRIVATE DECLARATIONS -------------------------------*/

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/*----------------------- PUBLIC INTERFACES ----------------------------------*/

/**
********************************************************************************
*
* @brief        Initializes AaSysCom in EE level.
*
*               Function initializes AaSysCom in EE level. This function must
*               be called in every EE before using SysCom interface.
*
*
* @return     The function returns nothing.
*
*******************************************************************************/
void AaSysComInitEe(void);


/**
********************************************************************************
*
* @brief        Exit AaSysCom.
*
*               AaSysComExit() frees allocated shared memory. This must be
*               called last when AaSysCom is not needed anymore.
*
*
* @return     The function returns nothing.
*
*******************************************************************************/
void AaSysComExit(void);


/**
********************************************************************************
*
* @brief        Exit AaSysCom in EE level.
*
*               The AaSysComExitEe() function exits AaSysCom in EE level. This
*               function must be called in every EE when AaSysCom is not needed
*               anymore.
*
*
* @return     The function returns nothing.
*
*******************************************************************************/
void AaSysComExitEe(void);

/** @} end: addtogroup dgAaSysComMcuRt AaSysCom MCU_RT*/

#ifdef __cplusplus
}
#endif

#endif /* IF_MCU_RT_AASYSCOM_CONFIG_H */
