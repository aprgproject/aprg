/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SFDpchInformation.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Krzysztof Michalak
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_F_DPCH_INFORMATION_H
#define _S_F_DPCH_INFORMATION_H


#include <ETpcDlStepSize.h>
#include <ELimitedPowerIncrease.h>
#include <EInnerLoopDLPCStatus.h>

struct SFDpchInformation
{
    ETpcDlStepSize              tpcDlStepSize;
    ELimitedPowerIncrease       limitedPowerIncrease;
    EInnerLoopDLPCStatus        innerLoopDlPcStatus;

};

typedef struct SFDpchInformation SFDpchInformation;

#endif /* _S_F_DPCH_INFORMATION_H */

/******************************************************************************
* @struct SFDpchInformation
* Description         : This IE is not present if # of F-DPCH Information 
*                       IE has been set to '0'.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: PI
*
* @param fddTpcDlStepSize :
*   Indicates step size for the DL power adjustment. Unit: dB
*   
* @param limitedPowerIncrease :
*   0 = Disabled
*   1 = Enabled
*   
* @param innerLoopDlPcStatus :
*   0 = Active
*   1 = Inactive
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

