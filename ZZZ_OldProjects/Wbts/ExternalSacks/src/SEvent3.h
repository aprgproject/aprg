/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Definitions/SEvent3.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _SEVENT3_H
#define _SEVENT3_H


#include <SMeasurementThreshold.h>
#include <SMeasurementThresholdOPT.h>
#include <SMeasurementHystTimeOPT.h>
#include <SReportPeriodicityOPT.h>


typedef struct SEvent3 {
    
    SMeasurementThreshold               measurThreshold1;
    SMeasurementThresholdOPT            measurThreshold2;/* Optional */
    SMeasurementHystTimeOPT             measurementHystTime;/* Optional */
    SReportPeriodicityOPT               reportPeriodicityChoice;/* Optional */
	
} SEvent3;

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description :
*
* Reference   : 3GPP TS 25.433 v4.1.0
*
* Parameters  :
* 	typeOne		<explanation>    
*
* 	structOne	<explanation>   
*
* 	typeTwo		<explanation>      
*
*  <additional explanations>
*
* Provider : Telecom / Jesse Pasuri / Mika Hautala
*
************************************************************************/

#endif  /* _SEVENT3_H */

