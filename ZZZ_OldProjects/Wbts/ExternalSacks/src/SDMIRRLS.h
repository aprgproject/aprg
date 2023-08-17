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

#ifndef _SDMIRRLS_H
#define _SDMIRRLS_H


#include <TNumberOfItems.h>
#include <DOpenIUBCommonDefs.h>
#include <SDMIRRLSInfoLST.h>

typedef struct SDMIRRLS {
    
        TNumberOfItems                          numberOfrlInfo;
        SDMIRRLSInfoLST                            rlSInfo[MAX_NR_OF_RLSETS];
	
} SDMIRRLS;

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description :
*
* Reference   : 3GPP TS 25.433 v4.1.0
*
* Parameters  :
*  MAX_NR_OF_RLSETS          Maximum number of individual RL Sets a
*                         measurement can be started on.
*
* Provider : Telecom / Jesse Pasuri / Mika Hautala
*
************************************************************************/

#endif  /* _SDMIRRLS_H */

