/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SAddiEdchRlPairInfo.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Hemant Jain
*
* Copyright 2013 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_ADDI_EDCH_RL_PAIR_INFO_H
#define _S_ADDI_EDCH_RL_PAIR_INFO_H

#include <TRadioLinkId.h>

struct SAddiEdchRlPairInfo
{
    TRadioLinkId   primaryRlId;
    TRadioLinkId   secondaryRlId;
};
typedef struct SAddiEdchRlPairInfo SAddiEdchRlPairInfo;

#endif /* _S_ADDI_EDCH_RL_PAIR_INFO_H */

/**
****************************************************************************
* @struct SAddiEdchRlPairInfo
* Description         : Additional EDCH RL Pair Info.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param primaryRlId :
*       Defines Primary Radio Link Id of the DC HSUPA pair
*
* @param secondaryRlId :
*       Defines Primary Secondary Link Id of the DC HSUPA pair
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/
