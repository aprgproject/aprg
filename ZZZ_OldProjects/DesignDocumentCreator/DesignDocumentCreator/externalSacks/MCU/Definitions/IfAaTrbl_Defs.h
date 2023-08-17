/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_IF_AATRBL_DEF_H_
#define _MCU_IF_AATRBL_DEF_H_

#include <CcsCommon.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <../../COMMON/Definitions/IfAaTrbl_Defs.h>
#endif

/**
* @brief Callback function typedef for pre snapshot procedures.
* @param[in] coverage  Coverage of snapshot to be collected.
*/
typedef void TAaTrblPreSnapshotCb(EAaTrblCoverage coverage, void* opaque);

#endif /* _MCU_IF_AATRBL_DEF_H_*/

