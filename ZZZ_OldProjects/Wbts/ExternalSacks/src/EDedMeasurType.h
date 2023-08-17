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

#ifndef _EDEDMEASURTYPE_H
#define _EDEDMEASURTYPE_H

typedef enum EDedMeasurType {
    EDedMeasurType_SIR                  =0,
    EDedMeasurType_SIRError             =1,
    EDedMeasurType_TransmittedCodePower =2,
    EDedMeasurType_RSCP                 =3,
    EDedMeasurType_RxTimingDeviation    =4,
    EDedMeasurType_RoundTripTime        =5,
    EDedMeasurType_RxTimingDeviationLCR =6,
    EDedMeasurType_UEPowerHeadroom      =14
} EDedMeasurType;

#endif /* EDEDMEASURTYPE_H */

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description : 9.2.1.23 Dedicated Measurement Type.
* Sematic:      RSCP is used by TDD only, Rx Timing Deviation isare used
*               by 3.84Mcps TDD only, Rx Timing Deviation LCR is used by
*               1.28 Mcps TDD only, Round Trip Time, SIR Error are used
*               by FDD only.
*
* Reference   : 3GPP TS 25.433 v4.3.0
*
*               "The Dedicated Measurement Type identifies the type of
*                measurement that shall be performed."
*
* Provider : Telecom / Jesse Pasuri / Mika Hautala
*
************************************************************************/



