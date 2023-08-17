/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EMeasurThreshChoice.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _EMEASURTHRESHCHOICE_H
#define _EMEASURTHRESHCHOICE_H

typedef enum EMeasurThreshChoice {
    EMeasurThreshChoice_ReceivedTotalWideBand           =0,
    EMeasurThreshChoice_TransmittedCarrierPower         =1,
    EMeasurThreshChoice_AcknowledgedPRACHPreambles      =2,
    EMeasurThreshChoice_ULTimeslotISCP                  =3,
    EMeasurThreshChoice_SIR                             =4,
    EMeasurThreshChoice_SIRError                        =5,
    EMeasurThreshChoice_TransmittedCodePower            =6,
    EMeasurThreshChoice_RSCP                            =7,
    EMeasurThreshChoice_RxTimingDeviation               =8,
    EMeasurThreshChoice_RoundTripTime                   =9,
    EMeasurThreshChoice_AcknowledgedPCPCHAccessPreambles=10,
    EMeasurThreshChoice_DetectedPCPCHAccessPreambles    =11,
    EMeasurThreshChoice_UTRANGPSTimingofCellFramesforLCS=12,
    EMeasurThreshChoice_SFNSFNObservedTimeDifference    =13,
    EMeasurThreshChoice_NonHsdpaMeasurement             =14
} EMeasurThreshChoice;

#endif /* _EMEASURTHRESHCHOICE_H */

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description : Measurement Threshold Choice.
*
* Reference   : 3GPP TS 25.433 v4.1.0
*
*
*
* Provider : Telecom / Jesse Pasuri / Mika Hautala
*
************************************************************************/



