/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SEDpchInformation_Ver2.h $
* @version               $LastChangedRevision: 4548 $
* @date                  $LastChangedDate: 2014-12-23 15:24:04 +0800 (Tue, 23 Dec 2014) $
* @author                $Author: suzliao $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_E_DPCH_INFORMATION_VER2_H
#define _S_E_DPCH_INFORMATION_VER2_H

#include <TRadioLinkId.h>
#include <ESetOfEDpdchs_Ver2.h>
#include <TPunctureLimit.h>
#include <EETti.h>
#include <TPowerOffset.h>
#include <TThreshold.h>
#include <EHarqInfoForEDch.h>
#include <EHsDschConfInd.h>
#include <TERnti.h>
#include <TETfci.h>
#include <SClusterInformation_Ver2.h>
#include <SETfcsInformation_Ver2.h>
#include <TNumberOfItems.h>
#include <SEDchMacDFlow_Ver2.h>
#include <TBitMask.h>
#include <TBitRate.h>
#include <EMaceResetInd.h>
#include <DOpenIUBCommonDefs.h>
#include <ESixteenQamInd.h>
#include <EEdchMacdPduSizeFormat.h>
#include <SEDchDlCtrlChChangeInfo.h>
#include <EEagchTableChoice.h>
#include <EBoolean.h>

struct SEDpchInformation_Ver2
{
    TRadioLinkId                servingEDchRlId;
    ESetOfEDpdchs_Ver2          maxSetOfEDpdchs;
    TPunctureLimit              punctureLimit;
    EETti                       eTti;
    TPowerOffset                eDpcchPowerOffset;
    TThreshold                  eRgch2IndexStepThreshold;
    TThreshold                  eRgch3IndexStepThreshold;
    EHarqInfoForEDch            harqInfoForEDch;
    EHsDschConfInd              hsDschConfiguredIndicator;
    TERnti                      eRnti;
    ESetOfEDpdchs_Ver2          initialSetOfEDpdchs;
    TETfci                      initialMaxAllowedETfci;
    EBoolean                    hwGrantInMixedState;
    SClusterInformation_Ver2    clusterInformation;
    SETfcsInformation_Ver2      eTfcsInformation;
    TNumberOfItems              numOfEDchMacDFlows;
    SEDchMacDFlow_Ver2          eDchMacDFlowSpecificInfo[MAX_NR_OF_EDCH_MACD_FLOWS_VER2];
    TBitMask                    harqProcAllocFor2msScheduledTxGrant;
    TBitRate                    eDchMaxBitRate;
    TNumberOfItems              eDchProcessingOverloadLevel;
    TPowerOffset                eDchRefPowerOffset;
    EMaceResetInd               maceResetIndicator;
    TPowerOffset                eDchPowerOffsetSchedInf;
    ESixteenQamInd              sixteenQamUlOperInd;
    EEdchMacdPduSizeFormat      edchMacdPduSizeFormat;
    TNumberOfItems              numOfEDchDlCtrlChGrantInfo;
    SEDchDlCtrlChChangeInfo     eDchDlCtrlChGrantInfo[MAX_NR_OF_RLS];
    EEagchTableChoice           eagchTableChoice;
    EBoolean                    dcHsupaConfigued;
};
typedef struct SEDpchInformation_Ver2 SEDpchInformation_Ver2;

#endif /* _S_E_DPCH_INFORMATION_VER2_H */

/**
****************************************************************************
* @struct SEDpchInformation_Ver2
* Description         : E-DPCH Information for ver2
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param servingEDchRlId :
*   Scheduler, MAC-e(CQI), Should also indicate if this is a non-serving DSP
*   In case of non-serving DSP NO_VALUE is used.
*
* @param maxSetOfEDpdchs :
*   Details 10.60 E-DCH Decoder, Scheduler, E-DCH RM, RAKE, Max from RNC.
*   Needed by rate matching algorithm.
*
* @param punctureLimit :
*   E-DCH Decoder, E-DCH RM Unit: % Range: 40..100 % Step: 4 % 100% means no puncturing
*   Value zero is not applicable for E-DPCH.
*
* @param eTti :
*   All.
*
* @param eDpcchPowerOffset :
*   Scheduler, needed for E-DCH Power if it is calculated. Most likely not needed.
*
* @param eRgch2IndexStepThreshold :
*   Refers to an index in the SG-Table
*
* @param eRgch3IndexStepThreshold :
*   Refers to an index in the SG-Table
*
* @param harqInfoForEDch :
*   Rv0  indicates that  the UE will only use E_DCH RV index 0.
*   Rvtable indicates that  the UE will use an RSN based RV index
*
* @param hsDschConfiguredIndicator :
*   Indicator if HS-DSCH is configured for the UE or not.
*   This information is used for E-DPDCHs IQ branch mapping.
*
* @param eRnti :
*   This IE is needed for the UE (or UE group) specific CRC in E-AGCH.
*   If this IE is not present NO_VALUE is used.
*
* @param initialSetOfEDpdchs :
*   DSP internal use only. TCOM uses NO_VALUE_FOR_ENUMS or it can also
*   set this parameter for testing purposes. Master HSUPA L2 determines
*   and passes to Slave HSUPA L2. Defines the initial HW resource reservation.
*   RAKE, E-DCH RM, Initial data rate that should be configured.
*   Anyway E-DCH RM will update this but it would be useful for testing if
*   we can separately switch off the E-DCH RM from updating the HW Pointer.
*   Can be put to noE-DPDCHs, i.e. only E-DPCCH will be decoded.
*
* @param initialMaxAllowedETfci :
*   DSP internal use only. TCOM uses NO_VALUE. Information is needed in
*   HSUPA RAKE for detecting non-functional mobiles.
*
* @param hwGrantInMixedState :
*   RAN3043: This value is set to EBoolean_True only if  RAN 3043 is activated and
*   "Initial Set of E-DPDCHs Ver2" is ESetOfEdpdch_2SF4;
*   TCOM copies this information to Rake from the last sent message by Master HSUPAL2.
*
* @param clusterInformation :
*   Cluster information which Master HSUPA L2 allocates for the HSUPA.
*
* @param eTfcsInformation :
*   E-TFCS Information for ver2
*
* @param numOfEDchMacDFlows :
*   Number of E-DCH MAC-d Flow Specific Information.
*
* @param eDchMacDFlowSpecificInfo[MAX_NR_OF_EDCH_MACD_FLOWS_VER2] :
*   E-DCH MAC-d Flow Specific Information
*
* @param harqProcAllocFor2msScheduledTxGrant :
*   If this IE is not present NO_VALUE is used. The HSUPA L2 may change this value.
*
* @param eDchMaxBitRate :
*   Bitrate on transport block level. Unit is kbits per second.
*   If this IE is not present NO_VALUE is used.
*
* @param eDchProcessingOverloadLevel :
*   Number of consecutive TTIs. The value '0' is a special value that means infinity,
*   i.e. when this value is used, the Node B shall never indicate processing issue to the RNC.
*   If this IE is not present NO_VALUE is used.
*
* @param eDchRefPowerOffset :
*   The E-DCH Reference Power Offset is used to estimate the E-DPDCH power
*   from E-TFCI without decoding MAC-e PDUs. If this IE is not present NO_VALUE is used.
*
* @param maceResetIndicator :
*   Indicates the MAC-e reset is performed in UE.
*   If this IE is not present NO_VALUE_FOR_ENUMS is used.
*
* @param eDchPowerOffsetSchedInf :
*   Unit: dB Step: 1 dB. The E-DCH Power Offset for Scheduling Info is used to calculate
*   the E-DPDCH power for transmission of scheduling information without any MAC-d PDUs.
*   If this IE is not present NO_VALUE is used.
*
* @param sixteenQamUlOperInd :
*   If this IE is not present NO_VALUE_FOR_ENUMS is used.
*
* @param edchMacdPduSizeFormat :
*   This IE provides information about the type of MAC-d PDU Size Format
*   that shall be used for the E-DCH in the new configuration.
*
* @param numOfEDchDlCtrlChGrantInfo :
*   Number of E-DCH DL Control Channel Grant Information.
*
* @param eDchDlCtrlChGrantInfo :
*   Number of SEDchDlCtrlChChangeInfo to be in
*   this message is set to numOfEDchDlCtrlChGrantInfo.
*
* @param eagchTableChoice :
*   This IE shall be present if the SixteenQAM UL Operation Indicator IE is set to "Activate".
*   If sixteenQAM UL operation is not used in the new configuration for this UE, Table 16B
*   for E-AGCH shall be used in the new configuration.
*
* @param dcHsupaConfigued :
*   Indicate if DC HSUPA Configured to the UE.
*
*
* Additional Information :
*
* Definition Provided by : DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

