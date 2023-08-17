/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SCpcDtxDrxInfo.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_CPC_DTX_DRX_INFO_H
#define _S_CPC_DTX_DRX_INFO_H

#include <ECpcOptimObject.h>
#include <EDeviceType.h>
#include <ECpcState.h>
#include <TNumberOfItems.h>
#include <EEnablingDelay.h>
#include <SDtxInformation.h>
#include <SDrxInformation.h>

struct SCpcDtxDrxInfo
{
    ECpcOptimObject       cpcOptimizationObjective;
    EDeviceType           deviceType;
    ECpcState             cpcState;
    TNumberOfItems        ueDtxDrxOffset;
    EEnablingDelay        enablingDelay;
    SDtxInformation       dtxInfo;
    TNumberOfItems        numOfDrxInfo;
    SDrxInformation       drxInfo;
};

typedef struct SCpcDtxDrxInfo SCpcDtxDrxInfo;

#endif /* _S_CPC_DTX_DRX_INFO_H */

/******************************************************************************
* @struct SCpcDtxDrxInfo
* Description         : Continuous Packet Connectivity DTX-DRX Information
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: PI
*
*
* @param cpcOptimizationObjective :
*   This IE is present only when CPC configured. 0 = RTT Optimization 1 = Battery savings. 
*   If this IE is not present NO_VALUE_FOR_ENUMS is used.
*
* @param deviceType :
*   This IE is present only when CPC configured. 0 = UE battery dependent 1 = UE not battery dependent. 
*   If this IE is not present NO_VALUE_FOR_ENUMS is used.
*
* @param cpcState :
*   DSP internal use only. TCOM always uses NO_VALUE_FOR_ENUMS.
*
* @param ueDtxDrxOffset :
*   Units of subframes. Offset of the UE DTX and DRX cycles at the given TTI
*
* @param enablingDelay :
*   Units of radio frames
*
* @param dtxInfo :
*   DTX Information
*
* @param numOfDrxInfo :
*   Number of DRX Information
*
* @param drxInfo :
*   DRX Information
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

