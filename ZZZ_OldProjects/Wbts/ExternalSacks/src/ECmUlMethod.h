/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/ECmUlMethod.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_CM_UL_METHOD_H
#define _E_CM_UL_METHOD_H

#include <DFromTc_dsp.h>

typedef enum ECmUlMethod
{
    ECmUlMethod_SFReduction             = 0,
    ECmUlMethod_HigherLayerScheduling   = 1,
    ECmUlMethod_NoValue                 = NO_VALUE_FOR_ENUMS
}ECmUlMethod;

#endif /* _E_CM_UL_METHOD_H */

/***********************************************************************
* @enum ECmUlMethod
* Description         : Enumeration indicating the CM method for UL
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       version 12.0, 
*                       location: PI
*
* @param ECmUlMethod_SFReduction :           Compressed Mode method with spreading factor reduction
* @param ECmUlMethod_HigherLayerScheduling : Compressed Mode method with Higher layer Scheduling
* @param ECmUlMethod_NoValue:                This parameter is not present
*
* Additional Information : 3GPP TS 25.215 V6.0.0
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/


