/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/ESecondUlFreqActivState.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_SECOND_UL_FREQ_ACTIV_STATE_H
#define _E_SECOND_UL_FREQ_ACTIV_STATE_H

#include <DFromTc_dsp.h>

typedef enum ESecondUlFreqActivState
{
    ESecondUlFreqActivState_Activated         = 0,
    ESecondUlFreqActivState_Deactivated       = 1,
    ESecondUlFreqActivState_NoValue           = NO_VALUE_FOR_ENUMS
}ESecondUlFreqActivState;

#endif /* _E_SECOND_UL_FREQ_ACTIV_STATE_H */

/***********************************************************************
* @enum ESecondUlFreqActivState
* Description         : Activation state signalled to Node B at setup of 
*                       RL on secondary UL frequency.
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

