/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SAdditionalEdchCellInfoSetup.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_ADDITIONAL_EDCH_CELL_INFO_SETUP_H
#define _S_ADDITIONAL_EDCH_CELL_INFO_SETUP_H

#include <SUlScramblingCode.h>
#include <TSirTarget.h>
#include <TNumberOfItems.h>
#include <SEdchAdditionalRlSpecificInfo.h>
#include <TMacdFlowId.h>
#include <THarqProcessAllocation.h>
#include <TBitRate.h>
#include <TEDchProcessingOverloadLevel.h>
#include <TETfci.h>
#include <SFDpchInformation.h>
#include <SMulticellEdchInfo.h>
#include <DOpenIUBCommonDefs.h>

struct SAdditionalEdchCellInfoSetup
{
    SUlScramblingCode                   ulScramblingCode;
    TSirTarget                          ulSirTarget;
    TNumberOfItems                      numOfEdchAdditionalRlSpecificInfo;
    SEdchAdditionalRlSpecificInfo       edchAdditionalRlSpecificInfo[MAX_NR_OF_EDCH_RLS];
    TNumberOfItems                      numOfAdditionalEdchMacdFlowSpecificInfo;
    TMacdFlowId                         eDchMacDFlowId[MAX_NR_OF_EDCH_MACD_FLOWS_VER2];
    THarqProcessAllocation              harqProcAllocFor2msScheduledTxGrant;
    TBitRate                            eDchMaxBitRate;
    TEDchProcessingOverloadLevel        eDchProcessingOverloadLevel;
    TETfci                              eDchMinimumSetETfci;
    SFDpchInformation                   fDpchInformation;
    TNumberOfItems                      numOfMulticellEdchInfo;
    SMulticellEdchInfo                  multicellEdchInfo;
};
typedef struct SAdditionalEdchCellInfoSetup SAdditionalEdchCellInfoSetup;

#endif /* _S_ADDITIONAL_EDCH_CELL_INFO_SETUP_H */

/******************************************************************************
* @struct SAdditionalEdchCellInfoSetup
* Description         : E-DCH on Secondary uplink frequency.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param ulScramblingCode :
*   The UL Scrambling Code is the scrambling code used by UE. Every UE has its 
*   specific UL Scrambling Code.
*
* @param ulSirTarget :
*   The UL SIR target.
*
* @param numOfEdchAdditionalRlSpecificInfo :
*   Defines Number of SEdchAdditionalRlSpecificInfo struct(s).
*
* @param edchAdditionalRlSpecificInfo : 
*   E-DCH Additional RL Specific Information.
*
* @param numOfAdditionalEdchFddInfo :
*   Defines Number of SAdditionalEdchFddInformation struct(s).
*
* @param additionalEdchFddInfo : 
*   Additional E-DCH FDD Information.
*
* @param fDpchInformation : 
*   F-DPCH Information .
*
* @param numOfMulticellEdchInfo :
*   Defines Number of SMulticellEdchInfo struct(s).
*
* @param multicellEdchInfo : 
*   Multicell E-DCH Information.
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

