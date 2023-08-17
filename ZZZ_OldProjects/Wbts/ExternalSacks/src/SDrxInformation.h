/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SDrxInformation.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Krzysztof Michalak
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_DRX_INFORMATION_H
#define _S_DRX_INFORMATION_H

#include <EUeCycle.h>
#include <EInactivityThreshold.h>
#include <TNumberOfItems.h>

struct SDrxInformation
{
  EUeCycle              ueDrxCycle;
  EInactivityThreshold  inactivThresholdUeDrxCycle;
  EInactivityThreshold  inactivThresholdUeGrantMonit;
  TNumberOfItems        ueDrxGrantMonit;
};

typedef struct SDrxInformation SDrxInformation;

#endif /* _S_DRX_INFORMATION_H */

/******************************************************************************
* @struct SDrxInformation
* Description         : This IE is not present if # of DRX Information IE 
*                       has been set to zero.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: PI
*
* @param ueDrxCycle :
*   Units of subframes
*
* @param inactivThresholdUeDrxCycle :
*   Units of subframes
*
* @param inactivThresholdUeGrantMonit :
*   Units of E-DCH TTIs
*
* @param ueDrxGrantMonit :
*   False ('0') = DRX Grant Monitoring shall not be applied.
*   True ('1') = DRX Grant Monitoring shall be applied.
*   
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

