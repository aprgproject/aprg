/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SMeasurementIncDecThreshold.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _SMEASUREMENTINCDECTHRESHOLD_H
#define _SMEASUREMENTINCDECTHRESHOLD_H

#include <EMeasurIncDecThreshChoice.h>
#include <TTypeForMeasurThreshold.h>

typedef struct SMeasurementIncDecThreshold {
 	
	EMeasurIncDecThreshChoice               measurIncDecThreshChoice;
	TTypeForMeasurThreshold                 receivedTotalWideBand;
	TTypeForMeasurThreshold                 transmittedCarrierPower;
	TTypeForMeasurThreshold                 acknowledgedPRACHPreambles;
	TTypeForMeasurThreshold                 uLTimeslotISCP;
	TTypeForMeasurThreshold                 sIR;
	TTypeForMeasurThreshold                 sIRError;
	TTypeForMeasurThreshold                 transmittedCodePower;
	TTypeForMeasurThreshold                 rSCP;
	TTypeForMeasurThreshold                 roundTripTime;
	TTypeForMeasurThreshold                 acknowledgedPCPCHAccessPreambles;
	TTypeForMeasurThreshold                 detectedPCPCHAccessPreambles;

} SMeasurementIncDecThreshold;

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

#endif  /* _SMEASUREMENTINCDECTHRESHOLD_H */

