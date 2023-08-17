/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaPro shared definitions and types
* @module                AaPro
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAAPRO_DEFS_H
#define _MCU_RT_IFAAPRO_DEFS_H

#include <CcsCommon.h>

/************************** INCLUDED FILES ************************************/

/**
*
*@defgroup dgAaProApiLinux AaPro LINUX API
*@ingroup  dgAaPro
**/
/*@{*/

#ifdef __cplusplus
extern "C"{
#endif

/** @brief AaPro used to overide default EE name */
#define   AAPRO_TAG_EE_NAME    "ccs.service.aapro.eename"

#ifdef __cplusplus
}
#endif
#endif /* _MCU_RT_IFAAPRO_DEFS_H */
