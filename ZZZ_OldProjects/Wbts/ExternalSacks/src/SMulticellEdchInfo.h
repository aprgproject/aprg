/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SMulticellEdchInfo.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_MULTICELL_EDCH_INFO_H
#define _S_MULTICELL_EDCH_INFO_H

#include <TNumberOfItems.h>
#include <SDlPowerBalancingInfo.h>
#include <EMinRedEdpdchGainFactor.h>
#include <ESecondUlFreqActivState.h>

struct SMulticellEdchInfo
{
    TNumberOfItems                      numOfDlPowerBalancingInfo;
    SDlPowerBalancingInfo               dlPowerBalancingInfo;
    EMinRedEdpdchGainFactor             minRedEdpdchGainFactor;
    ESecondUlFreqActivState             secondUlFreqActivState;
};
typedef struct SMulticellEdchInfo SMulticellEdchInfo;

#endif /* _S_MULTICELL_EDCH_INFO_H */

/******************************************************************************
* @struct SMulticellEdchInfo
* Description         : Multicell E-DCH Information.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param numOfDlPowerBalancingInfo :
*   Defines Number of SDlPowerBalancingInfo struct(s).
*
* @param dlPowerBalancingInfo : 
*   This IE provides information for power balancing to be activated in the relevant RL(s).
*
* @param minRedEdpdchGainFactor : 
*   The minimum gain factor..
*
* @param secondUlFreqActivState : 
*   Activation state signalled to Node B at setup of RL on secondary UL frequency.
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

