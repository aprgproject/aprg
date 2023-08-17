/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EBundModeInd.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Kari Korvela
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_BUND_MODE_IND_H
#define _E_BUND_MODE_IND_H

#include <DFromTc_dsp.h>

typedef enum EBundModeInd
{
    EBundModeInd_Bundling   = 0,
    EBundModeInd_NoBundling = 1,
    EBundModeInd_NoValue    = NO_VALUE_FOR_ENUMS
}EBundModeInd;

#endif /* _E_BUND_MODE_IND_H */

/******************************************************************************
* @enum EBundModeInd
* Description         : Bundling mode indicator.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: PI
*
* Additional Information : 
*
* Definition Provided by : DSP, L2
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

