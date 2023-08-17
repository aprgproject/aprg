/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EHappyBitDelayConditionPeriod.h $
* @version               $LastChangedRevision: 5072 $
* @date                  $LastChangedDate: 2017-10-11 16:36:51 +0800 (Wed, 11 Oct 2017) $
* @author                $Author: zogeng $
*
* Original author        Angelica Grace Martires
*
* Copyright 2017 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _EHAPPYBITDELAYCONDITIONPERIOD_H
#define _EHAPPYBITDELAYCONDITIONPERIOD_H

#include <DFromTc_dsp.h>

typedef enum EHappyBitDelayConditionPeriod
{
    EHappyBitDelayConditionPeriod_2ms     = 0,
    EHappyBitDelayConditionPeriod_10ms    = 1,
    EHappyBitDelayConditionPeriod_20ms    = 2,
    EHappyBitDelayConditionPeriod_50ms    = 3,
    EHappyBitDelayConditionPeriod_100ms   = 4,
    EHappyBitDelayConditionPeriod_200ms   = 5,
    EHappyBitDelayConditionPeriod_500ms   = 6,
    EHappyBitDelayConditionPeriod_1000ms  = 7,
    EHappyBitDelayConditionPeriod_NoValue = NO_VALUE_FOR_ENUMS
} EHappyBitDelayConditionPeriod;

#endif /* _EHAPPYBITDELAYCONDITIONPERIOD_H*/

/******************************************************************
* @enum EHappyBitDelayConditionPeriod
* Description         : Happy bit delay condifition period of UE
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* Parameters          :
* @param 2ms          : 2ms HBDC period of UE
* @param 10ms         : 10ms HBDC period of UE
* @param 20ms         : 20ms HBDC period of UE
* @param 50ms         : 50ms HBDC period of UE
* @param 100ms        : 100ms HBDC period of UE
* @param 200ms        : 200ms HBDC period of UE
* @param 500ms        : 500ms HBDC period of UE
* @param 1000ms       : 1000ms HBDC period of UE
* @param NoValue      : HBDC period not available
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/

