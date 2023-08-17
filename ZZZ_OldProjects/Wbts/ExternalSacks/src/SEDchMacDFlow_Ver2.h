/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SEDchMacDFlow_Ver2.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_E_DCH_MAC_D_FLOW_VER2_H
#define _S_E_DCH_MAC_D_FLOW_VER2_H

#include <TMacdFlowId.h>
#include <ETransportBearReqInd.h>
#include <TNumberOfItems.h>
#include <TPowerOffset.h>
#include <TBitMask.h>
#include <SEDchNonScheduledInformation.h>
#include <EBundModeInd.h>
#include <TVoiceFlag.h>
#include <TSrbFlag.h>
#include <SEDchLogicalChannel_Ver2.h>
#include <DOpenIUBCommonDefs.h>
#include <EFpPayloadCrc.h>
#include <EBoolean.h>

struct SEDchMacDFlow_Ver2
{
    TMacdFlowId                     eDchMacDFlowId;
    ETransportBearReqInd            transportBearerRequestInd;
    EFpPayloadCrc                      payloadCrcPresenceIndicator;
    TNumberOfItems                  maxNumOfRetransmissionsForEDch;
    TPowerOffset                    eDchHarqPo;
    TBitMask                        eDchMacDFlowMultiplexingList;
    TNumberOfItems                  numOfEDchNonSchedTransmGrant;
    SEDchNonScheduledInformation    eDchNonScheduled;
    EBundModeInd                    bundlingModeIndicator;
    TVoiceFlag                      voiceFlag;
    TSrbFlag                        srbFlag;
    EBoolean                        isPttQueue;
    TNumberOfItems                  numOfEDchLogicalChannels;
    SEDchLogicalChannel_Ver2        eDchLogicalChannel[MAX_NR_OF_LOGICAL_CHANNELS_VER2];
};
typedef struct SEDchMacDFlow_Ver2 SEDchMacDFlow_Ver2;

#endif /* _S_E_DCH_MAC_D_FLOW_VER2_H */

/**
*******************************************************************************
* @struct SEDchMacDFlow_Ver2
* Description         : Information of E-DCH MAC-d Flow.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param eDchMacDFlowId :
*       UE specific MAC-d flow ID.
*
* @param transportBearerRequestInd :
*       Indicates whether a new transport bearer needs
*       to be established for carrying the concerned
*       transport channel.
*
* @param payloadCrcPresenceIndicator :
*       indicates whether FP payload 16 bit CRC is used or not,
*       TCOM should get this value from related NBAP message.
*
* @param maxNumOfRetransmissionsForEDch :
*       -
*
* @param eDchHarqPo :
*       -
*
* @param eDchMacDFlowMultiplexingList :
*       If this IE is not present NO_VALUE is used.
*
* @param numOfEDchNonSchedTransmGrant :
*       0 = E-DCH Scheduled Transmission Grant
*       1 = E-DCH Non-Scheduled Transmission Grant
*
* @param eDchNonScheduled :
*       E-DCH Non-Scheduled Transmission Grant information.
*
* @param bundlingModeIndicator :
*       The value "Bundling" is applicable only when E-TTI indicates "2ms".
*       If this IE is not present NO_VALUE_FOR_ENUMS is used.
*
* @param voiceFlag :
*       Determined by TCOM from voice specific SPI value and E-DCH/HS-DSCH PDU sizes.
*       TUP shall ignore HSUPA Congestion Control for CSVoHSPA MAC-d flow.
*       Can be used in scheduling to apply special handling.
* 
* @param srbFlag :
*       Determined by TCOM from MAC-d flow Id = 7, when
*       F-DPCH is in use. Otherwise MAC-d flow Id = 7
*       does not indicate SRBs and the flag shall not be set.
*
* @param  isPttQueue        : ptt flag refer to refer to WBTS_CP_13486.
*
* @param numOfEDchLogicalChannels :
*       Number of logical channels in this MAC-d flow.
*
* @param eDchLogicalChannel[MAX_NR_OF_LOGICAL_CHANNELS_VER2] :
*       Actual logical channel(s) information.
*
* Additional Information :
*
* Definition Provided by : DSP, L2
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/


