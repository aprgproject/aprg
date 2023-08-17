/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EEnablingDelay.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Krzysztof Michalak
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_ENABLING_DELAY_H
#define _E_ENABLING_DELAY_H

#include <DFromTc_dsp.h>

typedef enum EEnablingDelay
{
  EEnablingDelay_0    = 0,
  EEnablingDelay_1    = 1,
  EEnablingDelay_2    = 2,
  EEnablingDelay_4    = 3,
  EEnablingDelay_8    = 4,
  EEnablingDelay_16   = 5,
  EEnablingDelay_32   = 6,
  EEnablingDelay_64   = 7,
  EEnablingDelay_128  = 8,
  EEnablingDelay_NoValue  = NO_VALUE_FOR_ENUMS

} EEnablingDelay;

#endif /* _E_ENABLING_DELAY_H */

/******************************************************************************
* @enum EEnablingDelay
* Description         : Units of radio frames
*
* Reference           : WCDMA BTS SW DSP SW - MCU SW INTERFACE SPECIFICATION
**
* Additional Information : <type additional information if needed>
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/

