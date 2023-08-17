/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SHsDschInformation_Ver2.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_HS_DSCH_INFORMATION_VER2_H 
#define _S_HS_DSCH_INFORMATION_VER2_H

#include <ECqiFeedbackCycleK_Ver2.h>
#include <TRepetitionFactor.h>
#include <TPowerOffset.h>
#include <TMeasurementPowerOffset.h>
#include <EHarqPreambleMode.h>
#include <TNumberOfItems.h>
#include <EHsDschMacdPduSizeFormat.h>
#include <ESixtyfourQamAllowedIndicator.h>
#include <THsDschRnti.h>
#include <TRadioLinkId.h>
#include <DOpenIUBCommonDefs.h>
#include <THsDschMacDFlowId.h>
#include <SUeCapabilitiesInformation.h>
#include <TDynamicData.h>

struct SHsDschInformation_Ver2
{
    ECqiFeedbackCycleK_Ver2             cqiFeedbackCycleK;
    TRepetitionFactor                   cqiRepetFactor;
    TRepetitionFactor                   ackNackRepetFactor;
    TPowerOffset                        cqiPwrOffset;
    TPowerOffset                        ackPwrOffset;
    TPowerOffset                        nackPwrOffset;
    TPowerOffset                        hsScchPwrOffset;
    TMeasurementPowerOffset             measPwrOffset;
    EHarqPreambleMode                   harqPreambleMode;
    TNumberOfItems                      mimoActivationInd;
    EHsDschMacdPduSizeFormat            hsDschMacdPduSizeFormat;
    ESixtyfourQamAllowedIndicator       sixtyFourQAMUsageAllowedInd;
    THsDschRnti                         hsDschRnti;
    TRadioLinkId                        hsPdschRlId;
    TNumberOfItems                      numOfHsDschMacDFlowSpecifInfos;
    THsDschMacDFlowId                   hsDschMacDFlowId[MAX_NR_OF_MACD_FLOWS_VER2];
    SUeCapabilitiesInformation          ueCapabilitiesInfo;
    TNumberOfItems                      numOfPrioQInfos;
    TDynamicData                        dynamicPart[1];
};

typedef struct SHsDschInformation_Ver2 SHsDschInformation_Ver2;

#endif /* _S_HS_DSCH_INFORMATION_VER2_H */

/******************************************************************************
* @struct SHsDschInformation_Ver2
* Description         : This IE is not present if # of HS-DSCH Information for ver2 IE has been set to '0'.
*                       NOTE: Parameters are in different order than in IUB spec due to RAKE SW restrictions. 

*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param cqiFeedbackCycleK :
*   Units: ms The following combination is not allowed: CQI Feedback Cycle k IE and CQI Repetition Factor IE are set to '2'.
* 
* @param cqiRepetFactor :
*   Value is 0 if CQI Feedback cycle is zero
*
* @param ackNackRepetFactor :
*   ACK-NACK Repetition Factor
*
* @param cqiPwrOffset :
*   CQI Power Offset 
*
* @param ackPwrOffset :
*   ACK Power Offset
*
* @param nackPwrOffset :
*   NACK Power Offset
*
* @param hsScchPwrOffset : 
* If this IE is not present NO_VALUE is used.
*
* @param measPwrOffset :
*   Range: -6 -+13 Unit: dB Step: 0.5dB If this IE is not present NO_VALUE is used.
* 
* @param harqPreambleMode :
*   If this IE is not present NO_VALUE_FOR_ENUMS is used.
*   
* @param mimoActivationInd :
*   0 = not present 1 = present If this IE is not present value 0 is used.
* 
* @param hsDschMacdPduSizeFormat :
*   If this IE is not present NO_VALUE_FOR_ENUMS is used.
*
* @param sixtyFourQAMUsageAllowedInd :
*   This IE indicates whether the BTS is allowed to use 64 QAM modulation for HS-DSCH transmission or not.
*   If this IE is not present NO_VALUE_FOR_ENUMS is used.
*
* @param hsDschRnti :
*   HS-DSCH RNTI
*
* @param hsPdschRlId :
*   HS-PDSCH RL-ID  
*
* @param numOfHsDschMacDFlowSpecifInfos :
* Number of HS-DSCH MAC-d Flow Specific Information
*
* @param hsDschMacDFlowId[MAX_NR_OF_MACD_FLOWS_VER2] :
* HS-DSCH MAC-d Flow Specific Information.
* 
* @param ueCapabilitiesInfo :
* Provides information of UE capabilities of this HSDPA user.
*
* @param numOfPrioQInfos :
*   This IE value is zero in case of HSDPA RL Setup to RAKE. 
*   This IE value is zero in case of HSUPA RL Setup to Master HSUPA L2.
*
*******************************************
*    Dynamic part
*******************************************
*
*   Each struct must be present as many times as set to the 'Number of' -field
*   for appropriate struct in static part of this Message.
*   MANDATORY = struct must exists at least once.
*   OPTIONAL = struct may not exists at all.
*
*   Content of the dynamic part in order:
*
*   SPriorityQueueInformation_Ver2  MANDATORY
*                                   Provides information of priority queues
*                                   to be established for this HSDPA user.
*                                   Number of SPriorityQueueInformation_Ver2 to be 
*                                   in this structure is set to numOfPrioQInfos_ver2 
*                                   in the Static part of this message.
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

