/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EMaceResetInd.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_MAC_E_RESET_IND_H
#define _E_MAC_E_RESET_IND_H

#include <DFromTc_dsp.h>

typedef enum EMaceResetInd
{
    EMaceResetInd_Reset     = 0,
    EMaceResetInd_NoValue   = NO_VALUE_FOR_ENUMS

} EMaceResetInd;

#endif /* _E_MAC_E_RESET_IND_H */

/******************************************************************************
* @enum EMaceResetInd
*
* Description         : Indicates the MAC-e Reset is performewd in UE.
*                       If this IE is not present NO_VALUE_FOR_ENUMS is used
* 
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

