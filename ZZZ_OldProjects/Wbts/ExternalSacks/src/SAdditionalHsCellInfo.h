/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SAdditionalHsCellInfo.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_ADDITIONAL_HS_CELL_INFO_H
#define _S_ADDITIONAL_HS_CELL_INFO_H

#include <TRadioLinkId.h>
#include <TCellId.h>
#include <TPowerOffset.h>
#include <TMeasurementPowerOffset.h>
#include <ESixtyfourQamAllowedIndicator.h>
#include <THsDschRnti.h>
#include <TMimoActivationInd.h>
#include <TNumberOfItems.h>

struct SAdditionalHsCellInfo
{
    TRadioLinkId                        hsPdschRlId;
    TCellId                             cellId;
    TPowerOffset                        hsScchPwrOffset;
    TMeasurementPowerOffset             measPwrOffset;
    ESixtyfourQamAllowedIndicator       sixtyFourQAMUsageAllowedInd;
    THsDschRnti                         hsDschRnti;
    TMimoActivationInd                  mimoActivationInd;
    TNumberOfItems                      ordinalNbrOfFrequency;
};
typedef struct SAdditionalHsCellInfo SAdditionalHsCellInfo;

#endif /* _S_ADDITIONAL_HS_CELL_INFO_H */

/**
*******************************************************************************
* @struct SAdditionalHsCellInfo
* Description         : This IE is not present if # of Additional HS Cell Information IE has been set to '0'.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param hsPdschRlId :
*   HS-PDSCH RL-ID
*
* @param cellId :
*   The C-ID (Cell idenfier) is the identifier of a cell in one RNC.
*
* @param hsScchPwrOffset : 
*   If this IE is not present NO_VALUE is used.
*
* @param measPwrOffset :
*   Range: -6 -+13 Unit: dB Step: 0.5dB.
* 
* @param sixtyFourQAMUsageAllowedInd :
*   This IE indicates whether the BTS is allowed to use 64 QAM modulation for HS-DSCH transmission or not.
*   If this IE is not present NO_VALUE_FOR_ENUMS is used.
* 
* @param hsDschRnti :
*   The HS-DSCH RNTI is used for the UE-specific CRC in HS-SCCH and HS-DSCH.
*
* @param mimoActivationInd :
*   This IE indicates whether MIMO is activated or not..
*
* @param ordinalNbrOfFrequency :
*   This IE indicates the ordinal number for the secondary cell.
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

