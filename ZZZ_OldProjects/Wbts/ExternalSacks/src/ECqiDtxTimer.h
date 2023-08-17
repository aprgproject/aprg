/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/ECqiDtxTimer.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Krzysztof Michalak
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_CQI_DTX_TIMER_H
#define _E_CQI_DTX_TIMER_H

#include <DFromTc_dsp.h>

typedef enum ECqiDtxTimer
{
  ECqiDtxTimer_0          = 0,
  ECqiDtxTimer_1          = 1,
  ECqiDtxTimer_2          = 2,
  ECqiDtxTimer_4          = 3,
  ECqiDtxTimer_8          = 4,
  ECqiDtxTimer_16         = 5,
  ECqiDtxTimer_32         = 6,
  ECqiDtxTimer_64         = 7,
  ECqiDtxTimer_128        = 8,
  ECqiDtxTimer_256        = 9,
  ECqiDtxTimer_512        = 10,
  ECqiDtxTimer_Infinity   = 11,
  ECqiDtxTimer_NoValue    = NO_VALUE_FOR_ENUMS

} ECqiDtxTimer;

#endif /* _E_CQI_DTX_TIMER_H */

/******************************************************************************
*@enum ECqiDtxTimer
*
* Description         : Units of subframes
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

