/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Original author        <nn>
*
* Copyright 2012 Nokia Siemens Networks. All rights reserved.
*******************************************************************************/

#ifndef _SPUSCHIDOPTLST_H
#define _SPUSCHIDOPTLST_H

#include <TNumberOfItems.h>
#include <DOpenIUBCommonDefs.h>
#include <TPUSCHID.h>

typedef struct SPUSCHIDOPTLST {
	
	TNumberOfItems	                        numberOfPUSCHIDInfo;
	TPUSCHID				pUSCHID[MAX_NR_OF_PUSCHS];
	
} SPUSCHIDOPTLST;

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description :
*
* Reference   : 3GPP TS 25.433 v4.1.0
*
* Parameters  :
*  MAX_NR_OF_PUSCHS       Maximum number of PUSCH per RL a measurement
*                      can be started on. 
*
* Provider : Telecom / Jesse Pasuri / Mika Hautala
*
************************************************************************/

#endif  /* _SPUSCHIDOPTLST_H */

