/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SEDchLogicalChannel_Ver2.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_E_DCH_LOGICAL_CHANNEL_VER2_H
#define _S_E_DCH_LOGICAL_CHANNEL_VER2_H

#include <TChannelId.h>
#include <TSchedulingPrioIndicator.h>
#include <ESchedInfo.h>
#include <TBitRate.h>
#include <TDdi.h>
#include <TNumberOfItems.h>
#include <TMacDPduSize.h>
#include <DOpenIUBCommonDefs.h>

struct SEDchLogicalChannel_Ver2
{
    TChannelId                  logicalChannelId;
    TSchedulingPrioIndicator    schedPrioIndicator;
    ESchedInfo                  schedulingInformation;
    TBitRate                    macEGuaranteedBitRate;
    TDdi                        eDchDdiValue;
    TNumberOfItems              numOfMacDPduSizes;
    TMacDPduSize                macDPduSize[MAX_NR_OF_DDIS_VER2];
    TMacDPduSize                maxMacDPduSizeExtended;
};

typedef struct SEDchLogicalChannel_Ver2 SEDchLogicalChannel_Ver2;

#endif /* _S_E_DCH_LOGICAL_CHANNEL_VER2_H */

/******************************************************************************
* @struct SEDchLogicalChannel_Ver2
* Description         : Information of E-DCH Logical Channel
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param logicalChannelId :
*       ID of this logical channel.
*
* @param schedPrioIndicator :
*       -
*
* @param schedulingInformation :
*       -
*
* @param macEGuaranteedBitRate :
*       Guaranteed bit rate for MAC-e.
*
* @param eDchDdiValue :
*       If more than 1 MAC-d PDU size is configured for this Logical Channel, 
*       the different sizes will use subsequent DDI values starting from this 
*       DDI value. Value "0x3F" is reserved.
*
* @param numOfMacDPduSizes :
*       Number of configured MAC-d PDU sizes.
*
* @param macDPduSize[MAX_NR_OF_DDIS_VER2] :
*       Actual list of MAC-d PDU sizes.
*
* @param maxMacDPDUSizeExtended :
*       IE provides the size in octets of the MAC level PDU when an extended MAC
*       level PDU size is required. In case of E-DCH, value 1 shall not be used.
*       If this IE is not present NO_VALUE_FOR_ENUMS is used.
*
* Additional Information :
*
* Definition Provided by : DSP, L2
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

