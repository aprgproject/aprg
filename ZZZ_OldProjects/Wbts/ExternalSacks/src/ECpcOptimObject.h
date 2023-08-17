/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/ECpcOptimObject.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Krzysztof Michalak
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_CPC_OPTIM_OBJECT_H
#define _E_CPC_OPTIM_OBJECT_H

#include <DFromTc_dsp.h>

typedef enum ECpcOptimObject
{
    ECpcOptimObject_RttOptim  = 0,
    ECpcOptimObject_Battery   = 1,
    ECpcOptimObject_NoValue   = NO_VALUE_FOR_ENUMS

} ECpcOptimObject;

#endif /* _E_CPC_OPTIM_OBJECT_H */

/******************************************************************************
@enum ECpcOptimObject
*
* Description         : This IE is present only when CPC configured. 
*       0 = RTT Optimization 1 = Battery savings
*       If this IE is not present NO_VALUE_FOR_ENUMS is used.
* 
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: PI
*
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

