/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/ENewServingRl.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Wang Xiaojiang
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_NEW_SERVING_RL_H
#define _E_NEW_SERVING_RL_H

#include <DFromTc_dsp.h>

typedef enum ENewServingRl
{
    ENewServingRl_Bts          = 0,
    ENewServingRl_NotBts       = 1,
    ENewServingRl_BtsOrNotBts  = 2,
    ENewServingRl_NoValue      = NO_VALUE_FOR_ENUMS
}ENewServingRl;

#endif /* _E_NEW_SERVING_RL_H */

/******************************************************************************
* @enum ENewServingRl
* Description         : 0 = Master HSUPA L2 preconfigures E-DCH for non-serving RL in Intra BTS case
*                       1 = Master HSUPA L2 preconfigures E-DCH for non-serving RL in Inter BTS case
*                       2 = Master HSUPA L2 preconfigures E-DCH for non-serving RL in Intra or Inter BTS case
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Sharenet
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

