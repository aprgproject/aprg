/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EUeDtxLongPreamble.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Krzysztof Michalak
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_UE_DTX_LONG_PREAMBLE_H
#define _E_UE_DTX_LONG_PREAMBLE_H

#include <DFromTc_dsp.h>

typedef enum EUeDtxLongPreamble
{
  EUeDtxLongPreamble_2  = 0,
  EUeDtxLongPreamble_4  = 1,
  EUeDtxLongPreamble_15 = 2,
  EUeDtxLongPreamble_NoValue = NO_VALUE_FOR_ENUMS

} EUeDtxLongPreamble;

#endif /* _E_UE_DTX_LONG_PREAMBLE_H */

/******************************************************************************
* @enum EUeDtxLongPreamble
* Description         : UE DTX Long Preamble
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

