/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SClusterFractionInformation_Ver2.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_CLUSTER_FRACTION_INFORMATION_VER2_H
#define _S_CLUSTER_FRACTION_INFORMATION_VER2_H

#include <TAaSysComSicad.h>
#include <TBitMask.h>

struct SClusterFractionInformation_Ver2
{
    TAaSysComSicad          dedicatedChannelDeviceAddress;
    TBitMask                harqProcSelectionMaskForClusterFraction;
};

typedef struct SClusterFractionInformation_Ver2 SClusterFractionInformation_Ver2;

#endif /* _S_CLUSTER_FRACTION_INFORMATION_VER2_H */

/******************************************************************************
* @struct SClusterFractionInformation_Ver2
* Description         : Information of cluster fraction.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param dedicatedChannelDeviceAddress
*       Address of LTCOM in Dedicated Channel device Faraday.
*
* @param harqProcSelectionMaskForClusterFraction :
*       The Initial Value For Active HARQ Process Bit Mask IE indicates those 
*       HARQ processes that are received and decoded by cluster fraction. 
*       If process is active then corresponding bit in HARQ process mask has 
*       been set to "1".
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

