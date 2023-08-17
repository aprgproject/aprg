/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EUeDpcchBurst.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Krzysztof Michalak
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_UE_DPCCH_BURST_H
#define _E_UE_DPCCH_BURST_H

#include <DFromTc_dsp.h>

typedef enum EUeDpcchBurst
{
  EUeDpcchBurst_1   = 0,
  EUeDpcchBurst_2   = 1,
  EUeDpcchBurst_5   = 2,
  EUeDpcchBurst_NoValue = NO_VALUE_FOR_ENUMS

} EUeDpcchBurst;

#endif /* _E_UE_DPCCH_BURST_H */

/******************************************************************************
* @enum EUeDpcchBurst
* Description         : UE DPCCH Burst
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

