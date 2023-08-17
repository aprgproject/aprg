/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EInactivityThreshold.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Krzysztof Michalak
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_INACTIVITY_THRESHOLD_H
#define _E_INACTIVITY_THRESHOLD_H

#include <DFromTc_dsp.h>

typedef enum EInactivityThreshold
{
  EInactivityThreshold_0    = 0,
  EInactivityThreshold_1    = 1,
  EInactivityThreshold_2    = 2,
  EInactivityThreshold_4    = 3,
  EInactivityThreshold_8    = 4,
  EInactivityThreshold_16   = 5,
  EInactivityThreshold_32   = 6,
  EInactivityThreshold_64   = 7,
  EInactivityThreshold_128  = 8,
  EInactivityThreshold_256  = 9,
  EInactivityThreshold_512  = 10,
  EInactivityThreshold_Infinity  = 11,
  EInactivityThreshold_NoValue  = NO_VALUE_FOR_ENUMS

} EInactivityThreshold;

#endif /* _E_INACTIVITY_THRESHOLD_H */

/******************************************************************************
* @enum EInactivityThreshold
* Description         : Inactivity Threshold
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

