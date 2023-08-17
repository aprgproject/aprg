/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SHsDschPreconfigSetup.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Wang Xiaojiang
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_HSDSCH_PRECONFIG_SETUP
#define _S_HSDSCH_PRECONFIG_SETUP

#include <DOpenIUBCommonDefs.h>
#include <EMacResetScheme.h>
#include <TPhysicalLayerCategory.h>
#include <TReorderingBufferSize.h>
#include <TNumberOfItems.h>
#include <SSecondaryCells.h>
#include <TNumHsScchCodes.h>
#include <EHarqPreambleMode.h>
#include <TMimoActivationInd.h>
#include <EHsDschMacdPduSizeFormat.h>
#include <ESixtyfourQamAllowedIndicator.h>
#include <TUeEnhancedHsScchSupportInd.h>
#include <SCpcHsScchInfo.h>
#include <TUeSupportIndicatorExtension.h>


struct SHsDschPreconfigSetup 
{
    EMacResetScheme                     macResetScheme;
    TPhysicalLayerCategory              physicalLayerCategory;
    TReorderingBufferSize               reorderingBufSize;
    TNumberOfItems                      numberOfSecondaryCells;
    SSecondaryCells                     secondaryCells[MAX_NR_OF_HSDSCH];
    TNumHsScchCodes                     numPrimaryHsScchCodes;
    EHarqPreambleMode                   harqPreambleMode;
    TMimoActivationInd                  mimoActivationInd;
    EHsDschMacdPduSizeFormat            hsDschMacdPduSizeFormat;
    ESixtyfourQamAllowedIndicator       sixtyFourQamUsageAllowedInd;
    TUeEnhancedHsScchSupportInd         ueEnhancedHsScchSupportInd;
    TNumberOfItems                      numberOfCpcHsScchInfo;
    SCpcHsScchInfo                      cpcHsScchInfo;
    TUeSupportIndicatorExtension        ueSupportIndicatorExtension;
};
typedef struct SHsDschPreconfigSetup SHsDschPreconfigSetup;

#endif /* _S_HSDSCH_PRECONFIG_SETUP */

/******************************************************************
* @struct SHsDschPreconfigSetup
* Description         : This IE indicates that the Node B shall preconfigure set(s) of
*                       HS-SCCH codes and may contain a list of secondary serving HS-DSCH
*                       cells to be preconfigured for Enhanced Service Cell Change.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param macResetScheme :
*                       MAC-hs/ehs reset handling at enhanced HS serving cell change:
*                       "Always" means always reset  "Inter Node B Change" means 
*                       Only reset at Inter NodeB cell change.
*
* @param physicalLayerCategory : 
*                       Defines a set of UE radio access capabilities related to HSDPA
*
* @param reorderingBufSize : 
*                       The MAC-hs Reordering Buffer Size for RLC-UM IE indicates the
*                       portion of the buffer in the UE that can be used for RLC-UM
*                       traffic (i.e. for Priority Queues whose RLC Mode IE is set to "RLC-UM").
*
* @param numberOfSecondaryCells : 
*                       Defines Number of SSecondaryCells struct(s).
*
* @param secondaryCells : 
*                       Number of SSecondaryCells (0...MAX_NR_OF_HSDSCH) to be in
*                       this message is set to numberOfSecondaryCells.
*
* @param numPrimaryHsScchCodes : 
*                       For the secondary serving HS-DSCH cell.
*                       If this IE is not present NO_VALUE is used.
*
* @param harqPreambleMode :
*                       If this IE is not present NO_VALUE_FOR_ENUMS is used.
*
* @param mimoActivationInd :
*                       0 = not present 1 = present If this IE is not present value 0 is used.
*
* @param hsDschMacdPduSizeFormat :
*                       If this IE is not present value 0 "Indexed MAC-d PDU Size" is used.
*
* @param sixtyFourQAMUsageAllowedInd :
*                       For the secondary serving HS-DSCH cell.
*                       This IE indicates whether the BTS is allowed to use 64 QAM modulation
*                       for HS-DSCH transmission or not.
*                       If this IE is not present NO_VALUE_FOR_ENUMS is used.
*
* @param ueEnhancedHsScchSupportInd :
*                       If this IE is not present value 0 is used.
*                       UE supports enhanced HS-SCCH functionality:
*                       - UE supports different HS-SCCH in consecutive TTIs and
*                       - in HS-SCCH-less operation mode the UE supports HS-SCCH orders
*
* @param numberOfCpcHsScchInfo : 
*                       Defines Number of SCpcHsScchInfo struct(s).
*
* @param cpcHsScchInfo : 
*                       Continuous Packet Connectivity HS-SCCH less Information
*
* @param ueSupportIndicatorExtension :
*                       This IE is used to indicate the support level in the UE for optional
*                       HSDPA functions to the Node B.
*                       If this IE is not present NO_VALUE is used.
*
* Additional Information : -
*
* Definition Provided by : DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/

