/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/TDeltaSir.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        yaohliu
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/
#ifndef _T_DELTAD_SIR_H
#define _T_DELTAD_SIR_H

#include <glo_def.h>

typedef u32 TDeltaSir;

#endif  /* _T_DELTAD_SIR_H */


/**
*******************************************************************************
* @typedef TDeltaSir
* TDeltaSir is the type for varibles that BTS sets during the frame(and the following frame) 
* where transmission gap begins. This type also discribe combined settings for different 
* compressed mode (CM) sequence.
* 
* - Range: [0 ... 30]
* .
********************************************************************************/

/******************************************************************
*
* Description         : Delta in UL SIR target
*
* Reference           :  CmS Design document, PI
*
* Additional Information : 3GPP TS 25.215 V6.0.0
*
* Definition Provided by : Compressed Mode Service Component.
*
* Remember to put an empty line in the end of each definition 
* file. Otherwise the compiler will generate a warning.
********************************************************************************/

