/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SDlPowerBalancingInfo.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_POWER_BALANCING_INFO_H
#define _S_POWER_BALANCING_INFO_H

#include <EPowerAdjustmentType.h>
#include <TDlTxPower.h>
#include <TNumberOfItems.h>
#include <SDlTxRefPowerInfo.h>
#include <DOpenIUBCommonDefs.h>
#include <TMaxAdjustmentStep.h>
#include <TAdjustmentPeriod.h>
#include <TAdjustmentRatio.h>

struct SDlPowerBalancingInfo
{
    EPowerAdjustmentType      powerAdjustmentType;
    TDlTxPower                dlReferencePower;
    TNumberOfItems            numOfRadioLinks;
    SDlTxRefPowerInfo         dlTxRefPowerInfo[MAX_NR_OF_RLS];
    TMaxAdjustmentStep        maxAdjustmentStep;
    TAdjustmentPeriod         adjustmentPeriod;
    TAdjustmentRatio          adjustmentRatio;
};
typedef struct SDlPowerBalancingInfo SDlPowerBalancingInfo;

#endif /* _S_POWER_BALANCING_INFO_H */

/******************************************************************************
* @struct SDlPowerBalancingInfo
* Description         : This IE provides information for power balancing to be 
*                       activated in the relevant RL(s).
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param powerAdjustmentType :
*   Defines the characteristic of the power adjustment. (None/Common/Individual)
*
* @param dlReferencePower :
*   The IE shall be present if the Adjustment Type IE is equal to 'Common'.
*
* @param numOfRadioLinks :
*   Number of RLs listed in following table
*
* @param dlTxRefPowerInfo :
*   These IEs shall be present if the Adjustment Type IE is equal to 'Individual'.
*
* @param maxAdjustmentStep :
*   The IE shall be present if the Adjustment Type IE is equal to 'Common" or "Individual'.
*   Defines a time period, in which the accumulated power adjustment shall be maximum 1dB.
*
* @param adjustmentPeriod :
*   The IE shall be present if the Adjustment Type IE is equal to 'Common" or "Individual'.
*   Defines the period to be used for power balancing.
*
* @param adjustmentRatio :
*   The IE shall be present if the Adjustment Type IE is equal to 'Common" or "Individual'.
*   Defines the convergence rate used for the associated Adjustment Period.
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/


