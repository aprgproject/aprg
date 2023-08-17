/**
*******************************************************************************
* @file
*
* @brief                 AaSysCom inline NMAP functions implementation.
*
* Copyright 2016 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _RT_DSP_IFAASYSCOMNMAP_INLINE_H
#define _RT_DSP_IFAASYSCOMNMAP_INLINE_H

/*----------------------- INCLUDED FILES -------------------------------------*/

#include "CcsCommon.h"
#include <glo_def.h>
#include <IfAaSysCom_Defs.h>

/*----------------------- DOXYGEN GROUPS --------------------------------------*/
/**
* @addtogroup dgUpCcs U-Plane specific CC&S API
* @{
*/

/**
* @addtogroup dgUpCcsAaSysCom AaSysCom API
* @{
*/

/**
* @addtogroup dgUpCcsRtDspAaSysCom AaSysCom API for RT and OSECK DSP nodes
* @{
*/

/**
* @addtogroup dgUpCcsRtDspAaSysComNmapInlineApi AaSysComNmap Inline API
* @{
*
* This service provides inline implementation of certain SysCom services.
*
* Users should not include this header directly. Instead include the normal
* SysCom interface header file and indicate intention to use the inline
* implementations with a:
*
* -DAASYSCOM_USE_INLINE_IMPL
*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PRIVATE DECLARATIONS -------------------------------*/

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/**
* @name Structure definitions
* @{
*
* @par Restrictions:
* Users should not rely on any of these structures as these are only meant
* for syscom internal use and can change without any notice.
*/


/** @} end: @name Structure definitions */

/*----------------------- PUBLIC INTERFACES ----------------------------------*/

/**
* @name Definitions for inline implementation functions
* @{
*/
#define AaSysComNmapGetSicad AaSysComNmapGetSicad_inlineImpl
#define AaSysComNmapGetSicAddress AaSysComNmapGetSicAddress_inlineImpl
#define AaSysComNmapGetBoard AaSysComNmapGetBoard_inlineImpl
#define AaSysComNmapGetCpu AaSysComNmapGetCpu_inlineImpl
#define AaSysComNmapGetTask AaSysComNmapGetTask_inlineImpl

/** @} */

/**
********************************************************************************
*
* @brief       Get the address based on board, cpu and task identifiers used
*              in NMAP.
*
* @see
* respective function documentation in IfAaSysComNmap.h
*
*******************************************************************************/
static __CCS_INLINE__ TAaSysComSicad AaSysComNmapGetSicad_inlineImpl(
    const TBoard board,
    const TCpu cpu,
    const TTask task)
{
    return (TAaSysComSicad)((board << 24) | (cpu << 16) | task);
}

/**
********************************************************************************
*
*   @brief  Get the address based on board, cpu and task identifiers used
*           in NMAP.
*
*           This is an old version from AaSysComNmapGetSicad. It is kept here
*           for compability. It shall be removed in the future
*
* @see
* respective function documentation in IfAaSysComNmap.h
*
*******************************************************************************/
static __CCS_INLINE__ TAaSysComSicad AaSysComNmapGetSicAddress_inlineImpl(
    const TBoard board,
    const TCpu cpu,
    const TTask task)
{
    return (TAaSysComSicad)((board << 24) | (cpu << 16) | task);
}

/**
********************************************************************************
*
* @brief       Get the board identifier used in NMAP.
*
* @see
* respective function documentation in IfAaSysComNmap.h
*
*******************************************************************************/
static __CCS_INLINE__ TBoard AaSysComNmapGetBoard_inlineImpl(
    const TAaSysComSicad address)
{
    return (TBoard)((address) >> 24);
}

/**
********************************************************************************
*
* @brief       Get the cpu identifier used in NMAP.
*
* @see
* respective function documentation in IfAaSysComNmap.h
*
*******************************************************************************/
static __CCS_INLINE__ TCpu AaSysComNmapGetCpu_inlineImpl(
    const TAaSysComSicad address)
{
    return (TCpu)((0x00FF0000 & address) >> 16);
}

/**
********************************************************************************
*
* @brief       Get the task identifier used in NMAP.
*
* @see
* respective function documentation in IfAaSysComNmap.h
*
*******************************************************************************/
static __CCS_INLINE__ TTask AaSysComNmapGetTask_inlineImpl(
    const TAaSysComSicad address)
{
    return (TTask)(0xFFFF & address);
}


/** @} */   /* dgUpCcsRtDspAaSysComNMapInlineApi */

#ifdef __cplusplus
}
#endif

/** @} */   /* dgUpCcsRtDspAaSysCom */
/** @} */   /* dgUpCcsAaSysCom */
/** @} */   /* dgUpCcs */

#endif /* _RT_DSP_IFAASYSCOMNMAP_INLINE_H */
