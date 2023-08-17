/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/ECpcState.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_CPC_STATE_H
#define _E_CPC_STATE_H

#include <DFromTc_dsp.h>

typedef enum ECpcState
{
    ECpcState_Active     = 0,
    ECpcState_Deactive   = 1,
    ECpcState_NoValue    = NO_VALUE_FOR_ENUMS

} ECpcState;

#endif /* _E_CPC_STATE_H */

/******************************************************************************
@enum ECpcState
*
* Description         : This IE indicates state of the CPC.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: PI
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

