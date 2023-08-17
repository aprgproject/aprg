/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SAddiEdchRlMappingInfo.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Hemant Jain
*
* Copyright 2013 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_ADDI_EDCH_RL_MAPPING_INFO_H
#define _S_ADDI_EDCH_RL_MAPPING_INFO_H

#include <TNumberOfItems.h>
#include <SAddiEdchRlPairInfo.h>
#include <TAaSysComSicad.h>
#include <DOpenIUBCommonDefs.h>


struct SAddiEdchRlMappingInfo
{
    TNumberOfItems                  nbrOfRlPair;
    SAddiEdchRlPairInfo             rlMappingInfo[MAX_NR_OF_EDCH_RLS];
    TAaSysComSicad                  primayDCDAddress;
};
typedef struct SAddiEdchRlMappingInfo SAddiEdchRlMappingInfo;

#endif /* _S_ADDI_EDCH_RL_MAPPING_INFO_H */

/**
****************************************************************************
* @struct SAddiEdchRlMappingInfo
* Description         : Additional EDCH RL mapping Info.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param nbrOfRlPair :
*       Defines Number of DC HSUPA RL pair info
*
* @param rlMappingInfo :
*       Defines mapping of Primary RLid and Secondary Rlid of the DC HSUPA pair
*
* @param primayDCDAddress :
*       Defines Primary User LTCOM address
*
* Additional Information :
*
* Definition Provided by : DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/
