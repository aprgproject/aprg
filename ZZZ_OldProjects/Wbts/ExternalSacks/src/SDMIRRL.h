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

#ifndef _SDMIRRL_H
#define _SDMIRRL_H


#include <TNumberOfItems.h>
#include <DOpenIUBCommonDefs.h>
#include <SDMIRRLInfoLST.h>

typedef struct SDMIRRL {

        TNumberOfItems                          numberOfrlInfo;
        SDMIRRLInfoLST                          rlInfo[MAX_NR_OF_RLS];

} SDMIRRL;

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description : 9.1.52	RL group for DEDICATED MEASUREMENT INITIATION REQUEST
*
* Reference   : 3GPP TS 25.433 v4.3.0 (Open Iub)
*
* Parameters  :
*  MAX_NR_OF_RLS             Maximum number of individual RL's a measurement
*                         can be started on.
*
* Provider : Telecom / Jesse Pasuri / Mika Hautala
*
************************************************************************/

#endif  /* _SDMIRRL_H */

