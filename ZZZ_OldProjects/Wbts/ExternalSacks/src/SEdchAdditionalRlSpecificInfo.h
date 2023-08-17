/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SEdchAdditionalRlSpecificInfo.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_EDCH_ADDITIONAL_RL_SPECIFIC_INFO_H
#define _S_EDCH_ADDITIONAL_RL_SPECIFIC_INFO_H

#include <TRadioLinkId.h>
#include <TCellId.h>
#include <EFirstRLSIndicator.h>
#include <TPropagationDelay.h>
#include <TNumberOfItems.h>
#include <SDlChannelisationCode.h>
#include <TDlTxPower.h>
#include <TMaxDlPower.h>
#include <TMinDlPower.h>
#include <TSlotFormat.h>
#include <TERnti.h>
#include <EPrimaryCpichUsageForChEstim.h>
#include <TCommonPhysicalChannelId.h>
#include <TPowerOffset.h>
#include <TEdchDlControlChannelGrant.h>
#include <DOpenIUBCommonDefs.h>

struct SEdchAdditionalRlSpecificInfo
{
    TRadioLinkId                        edchAdditionalRlId;
    TCellId                             cellId;
    EFirstRLSIndicator                  firstRlsIndicator;
    TPropagationDelay                   propagationDelay;
    TNumberOfItems                      numberOfDlChannelisationCodes;
    SDlChannelisationCode               dlChannelisationCode[MAX_NUM_OF_DL_CHAN_CODES];
    TDlTxPower                          initialDlTransmissionPower;
    TMaxDlPower                         maxDlPower;
    TMinDlPower                         minDlPower;
    TSlotFormat                         fDpchSlotFormat;
    TERnti                              eRnti;
    EPrimaryCpichUsageForChEstim        primaryCpichUsageForChEstim;
    TCommonPhysicalChannelId            secondaryCpichInformation;
    TCommonPhysicalChannelId            secondaryCpichInformationChange;
    TPowerOffset                        eAgchPo;
    TPowerOffset                        eRgchPo;
    TPowerOffset                        eHichPo;
    TDlTxPower                          dlReferencePower;
    TEdchDlControlChannelGrant          eDchDlControlChannelGrant;
};
typedef struct SEdchAdditionalRlSpecificInfo SEdchAdditionalRlSpecificInfo;

#endif /* _S_EDCH_ADDITIONAL_RL_SPECIFIC_INFO_H */

/******************************************************************************
* @struct SEdchAdditionalRlSpecificInfo
* Description         : E-DCH Additional RL Specific Information.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param edchAdditionalRlId :
*       The unique identifier for one RL associated with a UE.
*
* @param cellId :
*       The C-ID (Cell identifier) is the identifier of a cell in one RNC.
*
* @param firstRlsIndicator : 
*       This IE indicates if a specific Radio Link and all Radio Links which
*       are part of the same Radio Link Set, shall be considered as the first
*       radio links established towards the UE or not.
*
* @param propagationDelay :
*       The Propagation delay is the one-way propagation delay of the radio 
*       signal from the MS to the Node B.
*
* @param numberOfDlChannelisationCodes :
*       Number of dlChannelisationCodes in this RL.
*
* @param dlChannelisationCode[] :
*       A table size of MAX_NUM_OF_DL_CHAN_CODES for SDlChannelisationCode 
*       structs. SDlChannelisationCode provides FDD DL code information for 
*       the RL: DL scrambling code, DL Channelisation code and in optional 
*       whether alternative scrambling code is used for compressed mode method
*       'SF/2'.
*
* @param dlTxPower :
*       Indicates the initial power level of the transmitted DPDCH symbols 
*       relative to the primary CPICH power configured in a cell.
*
* @param maxDlPower :
*       Indicates the maximum power level of the transmitted DPDCH symbols 
*       relative to the primary CPICH power configured in a cell.
*
* @param minDlPower :
*       Indicates the minimum power level of the transmitted DPDCH symbols 
*       relative to the primary CPICH power configured in a cell.
*
* @param fDpchSlotFormat :
*       Defines the F-DPCH slot format for the TPC bits.
*
* @param eRnti :
*       The E-RNTI is needed for the UE (or UE group) specific CRC in E-AGCH.
*
* @param primaryCpichUsageForChEstim :
*       This IE indicates whether the Primary CPICH may be used for channel 
*       estimation or not.
*
* @param secondaryCpichInformation :
*       If IE is not present NO_VALUE is used.
*
* @param secondaryCpichInformationChange :
*       This IE indicates modification of information of the Secondary CPICH 
*       for channel estimation.
*
* @param eAgchPo :
*       If IE is not present NO_VALUE is used.
*
* @param eRgchPo :
*       If IE is not present NO_VALUE is used.
*
* @param eHichPo :
*       If IE is not present NO_VALUE is used.
*
* @param dlReferencePower :
*       The DL Power IE indicates a power level relative to the primary CPICH power
*       configured in a cell. If Transmit Diversity is applied to a downlink physical 
*       channel, the DL Power IE indicates the power offset between the linear sum of 
*       the power for this downlink physical channel on all branches and the primary 
*       CPICH power configured in a cell. 
*       If referred to a DPCH, it indicates the power of the transmitted DPDCH symbols.
*       If referred to an F DPCH, it indicates the Reference F-DPCH TX Power.
*
* @param eDchDlControlChannelGrant :
*       E-DCH DL Control Channel Grant.
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

