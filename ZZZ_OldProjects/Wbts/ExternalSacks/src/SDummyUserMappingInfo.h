/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SDummyUserMappingInfo.h $
* @version               $LastChangedRevision: 4701 $
* @date                  $LastChangedDate: 2015-07-20 17:32:31 +0800 (Mon, 20 Jul 2015) $
* @author                $Author: q6chen $
*
* Original author        Anoop Maddi
*
* Copyright 2015 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_DUMMY_USER_MAPPING_INFO_H
#define _S_DUMMY_USER_MAPPING_INFO_H

#include <TUserId.h>
#include <TAaSysComSicad.h>

struct SDummyUserMappingInfo
{
    TUserId                dummyUserId;
    TAaSysComSicad         commonEdchDedicatedChannelDeviceAddress;
};
typedef struct SDummyUserMappingInfo SDummyUserMappingInfo;

#endif /* _S_DUMMY_USER_MAPPING_INFO_H */

/**
*******************************************************************************
* @struct SDummyUserMappingInfo
* Description         : This IE provides dummy user Information.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param dummyUserId :
*                       Dummy user ID is used by Rake to fetch UlTimingInfo of dummy users
*                       moving from Cell_Fach to Cell_Dch state.
*
* @param commonEdchDedicatedChannelDeviceAddress :
*                       Common Edch Dedicated Channel Device Address is used by TCOM and Rake
*                       to fetch UlTimingInfo of dummy users moving from Cell_Fach to Cell_Dch state.
*
*
* Additional Information : -
*
* Definition Provided by : DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/

