/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EMeasurIncDecThreshChoice.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _EMEASURINCDECTHRESHCHOICE_H
#define _EMEASURINCDECTHRESHCHOICE_H

typedef enum EMeasurIncDecThreshChoice {
    EMeasurIncDecThreshChoice_ReceivedTotalWideBand             =0,
    EMeasurIncDecThreshChoice_TransmittedCarrierPower           =1,
    EMeasurIncDecThreshChoice_AcknowledgedPRACHPreambles        =2,
    EMeasurIncDecThreshChoice_ULTimeslotISCP                    =3,
    EMeasurIncDecThreshChoice_SIR                               =4,
    EMeasurIncDecThreshChoice_SIRError                          =5,
    EMeasurIncDecThreshChoice_TransmittedCodePower              =6,
    EMeasurIncDecThreshChoice_RSCP                              =7,
    EMeasurIncDecThreshChoice_RoundTripTime                     =8,
    EMeasurIncDecThreshChoice_AcknowledgedPCPCHAccessPreambles  =9,
    EMeasurIncDecThreshChoice_DetectedPCPCHAccessPreambles      =10
} EMeasurIncDecThreshChoice;

#endif /* _EMEASURINCDECTHRESHCHOICE_H */

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description : Measurement Increase/Decrease Threshold Choice.
*
* Reference   : 3GPP TS 25.433 v4.1.0
*
*
*
* Provider : Telecom / Jesse Pasuri / Mika Hautala
*
************************************************************************/



