/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SMeasurementThreshold.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _SMEASUREMENTTHRESHOLD_H
#define _SMEASUREMENTTHRESHOLD_H

#include <EMeasurThreshChoice.h>
#include <TTypeForMeasurThreshold.h>
#include <SUTRANGPSTimofCellFrameforLCS.h>
#include <SFNSFNObservedTimeDifference.h>

typedef struct SMeasurementThreshold {

	EMeasurThreshChoice                     measurThreshChoice;
	TTypeForMeasurThreshold                 receivedTotalWideBand;
	TTypeForMeasurThreshold                 transmittedCarrierPower;
	TTypeForMeasurThreshold                 acknowledgedPRACHPreambles;
	TTypeForMeasurThreshold                 uLTimeslotISCP;
	TTypeForMeasurThreshold                 sir;
	TTypeForMeasurThreshold                 sirError;
	TTypeForMeasurThreshold                 transmittedCodePower;
	TTypeForMeasurThreshold                 rSCP;
	TTypeForMeasurThreshold                 rxTimingDeviation;
	TTypeForMeasurThreshold                 roundTripTime;
	TTypeForMeasurThreshold                 acknowledgedPCPCHAccessPreambles;
	TTypeForMeasurThreshold                 detectedPCPCHAccessPreambles;
	SUTRANGPSTimofCellFrameforLCS           uTRANGPSTimingofCellFramesforLCS;
	SFNSFNObservedTimeDifference            fNSFNObservedTimeDifference;
	TTypeForMeasurThreshold                 nonHsdpaMeasurement;
} SMeasurementThreshold;

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description : 9.2.1.44	Measurement Threshold.
*               "The Measurement Threshold defines which threshold that
*                shall trigger Event A, B, E, F or On Modification."
*
* Reference   : 3GPP TS 25.433 v4.3.0
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

#endif  /* _SMEASUREMENTTHRESHOLD_H */

