/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EDeviceType.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Krzysztof Michalak
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_DEVICE_TYPE_H
#define _E_DEVICE_TYPE_H

#include <DFromTc_dsp.h>

typedef enum EDeviceType
{
    EDeviceType_Battery     = 0,
    EDeviceType_NotBattery  = 1,
    EDeviceType_NoValue     = NO_VALUE_FOR_ENUMS

} EDeviceType;

#endif /* _E_DEVICE_TYPE_H */

/******************************************************************************
* @enum EDeviceType
*
* Description         : This IE is present only when CPC configured. 
*       0 = UE battery dependent 1 = UE not battery dependent
*       If this IE is not present NO_VALUE_FOR_ENUMS is used
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

