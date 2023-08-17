/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/ERlSetupType_Ver2.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_RL_SETUP_TYPE_VER2_H
#define _E_RL_SETUP_TYPE_VER2_H

#include <DFromTc_dsp.h>

typedef enum ERlSetupType_Ver2
{
    ERlSetupType_Ver2_FirstRl                            = 0,
    ERlSetupType_Ver2_SofterHandover                     = 1,
    ERlSetupType_Ver2_SoftHandover                       = 2,
    ERlSetupType_Ver2_NoValue                            = NO_VALUE_FOR_ENUMS

}ERlSetupType_Ver2;

#endif /* _E_RL_SETUP_TYPE_VER2_H */

/***********************************************************************
* @enum ERlSetupType_Ver2
* Description         : Setup type in Radio Link Setup.
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


