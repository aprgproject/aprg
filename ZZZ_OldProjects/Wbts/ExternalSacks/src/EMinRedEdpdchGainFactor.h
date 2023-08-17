/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EMinRedEdpdchGainFactor.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_MIN_RED_EDPDCH_GAIN_FACTOR_H
#define _E_MIN_RED_EDPDCH_GAIN_FACTOR_H

#include <DFromTc_dsp.h>

typedef enum EMinRedEdpdchGainFactor
{
    EMinRedEdpdchGainFactor_815        = 0,
    EMinRedEdpdchGainFactor_1115       = 1,
    EMinRedEdpdchGainFactor_One        = 2,
    EMinRedEdpdchGainFactor_2115       = 3,
    EMinRedEdpdchGainFactor_Two        = 4,
    EMinRedEdpdchGainFactor_4215       = 5,
    EMinRedEdpdchGainFactor_Four       = 6,
    EMinRedEdpdchGainFactor_8415       = 7,
    EMinRedEdpdchGainFactor_NoValue    = NO_VALUE_FOR_ENUMS
}EMinRedEdpdchGainFactor;

#endif /* _E_MIN_RED_EDPDCH_GAIN_FACTOR_H */

/***********************************************************************
* @enum EMinRedEdpdchGainFactor
* Description         : Minimum Reduced E-DPDCH Gain Factor.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/

