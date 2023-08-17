/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SRadioLinkSetup_Ver2.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Wang Xiaojiang
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_RADIO_LINK_SETUP_VER2_H
#define _S_RADIO_LINK_SETUP_VER2_H

#include <DFromTc_dsp.h>
#include <TRadioLinkId.h>
#include <TCellId.h>
#include <ERlSetupType_Ver2.h>
#include <TFrameOffset.h>
#include <TChipOffset.h>
#include <TPropagationDelay.h>
#include <EDiversityControlField.h>
#include <TNumberOfItems.h>
#include <SDlChannelisationCode.h>
#include <TDlTxPower.h>
#include <TMaxDlPower.h>
#include <TMinDlPower.h>
#include <ETransmitDiversityIndicator.h>
#include <TPowerOffset.h>
#include <TSlotFormat.h>
#include <SHsDschPreconfigSetup.h>
#include <TERnti.h>
#include <SNonServingRlPreconfigurationSetup.h>
#include <TIndex.h>
#include <TDlChannelisationCodeNumber.h>
#include <TDlScramblingCode.h>

struct SRadioLinkSetup_Ver2
{
    TRadioLinkId                radioLinkId;
    TCellId                     cellId;
    ERlSetupType_Ver2           typeOfSetup;
    TFrameOffset                frameOffset;
    TChipOffset                 chipOffset;
    TPropagationDelay           propagationDelay;
    EDiversityControlField      diversityControlField;
    TNumberOfItems              numberOfDlChannelisationCodes;
    SDlChannelisationCode       dlChannelisationCode[MAX_NUM_OF_DL_CHAN_CODES];
    TDlTxPower                  dlTxPower;
    TMaxDlPower                 maxDlPower;
    TMinDlPower                 minDlPower;
    ETransmitDiversityIndicator transmitDiversityIndicator;
    TPowerOffset                eAgchPo;
    TPowerOffset                eRgchPo;
    TPowerOffset                eHichPo;
    TSlotFormat                 fDpchSlotFormat;
    TNumberOfItems              numberOfHsDschPreconfigSetup;
    SHsDschPreconfigSetup       hsDschPreconfigSetup;
    TERnti                      eRnti;
    TNumberOfItems              numberOfNonServingRlPreconfigurationSetup;
    SNonServingRlPreconfigurationSetup       nonServingRlPreconfigurationSetup;
    TIndex                      eHichSignatureSequenceIndex;
    TDlChannelisationCodeNumber eHichRgchChannelisationCode;
    TDlScramblingCode           eAgchRgchHichScramblingCode;
};

typedef struct SRadioLinkSetup_Ver2 SRadioLinkSetup_Ver2;

#endif /* _S_RADIO_LINK_SETUP_VER2_H */

/******************************************************************************
* @struct SRadioLinkSetup_Ver2
* Description         : Radio Link Information part in Radio Link Setup 
*                       message.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param radioLinkId :
*       The unique identifier for one RL associated with a UE.
*
* @param cellId :
*       The C-ID (Cell identifier) is the identifier of a cell in one RNC.
*
* @param typeOfSetup :
*       Indicates if a specific Radio Link which are part of the same Radio 
*       Link Set, shall be considered as the first radio link established
*       towards the UE or not.
*
* @param frameOffset :
*       The Frame Offset is the required offset between the dedicated channel
*       downlink transmission frames (CFN, Connection Frame Number) and the 
*       broadcast channel frame offset (Cell Frame Number). The Frame_offset
*       is used in the translation between Connection Frame Number (CFN) on 
*       Iub/Iur and the least significant 8 bits of SFN (System Frame Number) 
*       on Uu. The Frame Offset is UE and cell specific.
*
* @param chipOffset :
*       The Chip Offset is defined as the radio timing offset inside a radio 
*       frame. The Chip offset is used as offset for the DL DPCH relative to 
*       the Primary CPICH timing.
*
* @param propagationDelay :
*       The Propagation delay is the one-way propagation delay of the radio 
*       signal from the MS to the Node B.
*
* @param diversityControlField :
*       The Diversity Control Field indicates if the current RL may, must or 
*       must not be combined with the already existing RLs. Parameter is used 
*       for Uplink receiving diversity.
*       Note: This is not downlink diversity parameter.
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
* @param transmitDiversityIndication :
*       Indication of transmit diversity.
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
* @param fDpchSlotFormat :
*       Defines the F-DPCH slot format for the TPC bits.
*
* @param numberOfHsdschPreconfigSetup :
*       Number of HsdschPreconfigSetup in this RL.
*
* @param hsDschPreconfigSetup.:
*       This IE indicates that the Node B shall preconfigure
*       set(s) of HS-SCCH codes and may contain a list of 
*       secondary serving HS-DSCH cells to be preconfigured
*       for Enhanced Service Cell Change.
*
* @param eRnti:
*   	This IE is needed for the UE (or UE group) specific CRC in E-AGCH.
*   	If this IE is not present NO_VALUE is used.
*
* @param numberOfNonServingRlPreconfigurationSetup :
*       Number of NonServingRlPreconfigurationSetup in this RL.
*
* @param nonServingRlPreconfigurationSetup:
*       This IE indicates that the Node B may preconfigure E-DCH 
*       DL Code Information configured for new non-serving RL for 
*       Enhanced Service Cell Change and contains the information 
*       for the location of new serving RL after the Enhanced 
*       Serving Cell Change.
*
* @param eHichSignatureSequenceIndex :
*       DSP internal use only. TCOM always uses NO_VALUE.
*       Master HSUPA L2 allocates and passes to Slave HSUPA L2.
*
* @param eHichRgchChannelisationCode;
*       DSP internal use only. TCOM always uses NO_VALUE.
*       Master HSUPA L2 allocates and passes to Slave HSUPA L2.
*
* @param eAgchRgchHichScramblingCode;
*       DSP internal use only. TCOM always uses NO_VALUE.
*       Master HSUPA L2 passes to Slave HSUPA L2.
*
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

