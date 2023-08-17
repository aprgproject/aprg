/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/ECmDlMethod.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        RAJA
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_CM_DL_METHOD_H
#define _E_CM_DL_METHOD_H

#include <DFromTc_dsp.h>

typedef enum ECmDlMethod
{
    ECmDlMethod_Puncturing              = 0,
    ECmDlMethod_SFReduction             = 1,
    ECmDlMethod_HigherLayerScheduling   = 2,
    ECmDlMethod_NoValue                 = NO_VALUE_FOR_ENUMS
}ECmDlMethod;

#endif /* _E_CM_DL_METHOD_H */

/***********************************************************************
* @struct SNonIubParameters
* Description         : Enumeration indicating the CM method for DL.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       version 12.0, 
*                       location: PI
*
* @param Puncturing
* @param SFReduction
* @param HigherLayerScheduling
* @param NoValue        This parameter is not present
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/

