/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SClusterInformation_Ver2.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_CLUSTER_INFORMATION_VER2_H
#define _S_CLUSTER_INFORMATION_VER2_H

#include <TNumberOfItems.h>    
#include <SClusterFractionInformation_Ver2.h>
#include <DFromTc_dsp.h>

struct SClusterInformation_Ver2
{
    TNumberOfItems                     numOfValidClusterFractionInfo;
    SClusterFractionInformation_Ver2   clusterFractionInfo[MAX_CLUSTER_FRACT_IN_SPLIT_DECODING];
};

typedef struct SClusterInformation_Ver2 SClusterInformation_Ver2;

#endif /* _S_CLUSTER_INFORMATION_VER2_H */

/******************************************************************************
* @struct SClusterInformation_Ver2
* Description         : Information of HSUPA cluster.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param numOfValidClusterFractionInfo :
*       Informs number of valid cluster fraction information IEs.
*       1 = no split decoding
*       2 = split decoding
*
* @param clusterFractionInfo[MAX_CLUSTER_FRACT_IN_SPLIT_DECODING] :
*       Actual information of cluster fraction(s).
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

