/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Messages/BB_2_RlSetupReq.h $
* @version               $LastChangedRevision: 4701 $
* @date                  $LastChangedDate: 2015-07-20 17:32:31 +0800 (Mon, 20 Jul 2015) $
* @author                $Author: q6chen $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _BB_2_RL_SETUP_REQ_H
#define _BB_2_RL_SETUP_REQ_H

#include <SMessageHeader.h>
#include <STransaction.h>
#include <TUserId.h>
#include <TAaSysComSicad.h>
#include <TNumberOfItems.h>
#include <ELoopMode.h>
#include <TSfn.h>
#include <TFrameOffset.h>
#include <EUserType_Ver2.h>
#include <EStatus.h>
#include <TPowerCtrlTableIndex.h>
#include <SUlDpchInfoRlSetup.h>
#include <SDummyUserMappingInfo.h>
#include <TDynamicData.h>
#include <TUserIndex.h>

struct BB_2_RlSetupReq
{
    MESSAGEHEADER(msgHeader)
    STransaction          transaction;
    TUserId               userId;
    TUserIndex            ltcomUserIndex;
    ELoopMode             loopMode;
    TSfn                  sfn;
    TFrameOffset          referenceFrameOffset;
    EUserType_Ver2        userType;
    EStatus               syncStatus;
    TAaSysComSicad        dedicatedChannelDeviceAddress;
    TAaSysComSicad        sourceDedicatedChannelDeviceAddress;
    TAaSysComSicad        commonChannelDeviceAddress;
    TAaSysComSicad        hsPdschSchedulerDeviceAddress;
    TAaSysComSicad        telecomSicAddress;
    TPowerCtrlTableIndex  powerCtrlTableIndex;
    TNumberOfItems        numOfDummyUserMappingInfo;
    SDummyUserMappingInfo dummyUserMappingInfo;
    TNumberOfItems        trueUlTfcCount;
    SUlDpchInfoRlSetup    ulDpchInfoRlSetup;
    TNumberOfItems        numOfDlDpchInfo;
    TNumberOfItems        numOfRlInfo;
    TNumberOfItems        numOfCmTransGapPatternSeqInfo;
    TNumberOfItems        numOfCmTransGapPatternSeqInfoForCmSet2;
    TNumberOfItems        numOfCmActivePatternSeqInfo;
    TNumberOfItems        numOfUlTfc;
    TNumberOfItems        numOfDlTfc;
    TNumberOfItems        numOfDch;
    TNumberOfItems        numOfHsDschInfo;
    TNumberOfItems        numOfEDpchInfo;
    TNumberOfItems        numOfFDpchInfo;
    TNumberOfItems        numOfCpcDtxDrxInfo;
    TNumberOfItems        numOfCpcHsScchInfo;
    TNumberOfItems        numOfPrivateRlInfo;
    TNumberOfItems        numOfAdditionalHsCellInfo;
    TNumberOfItems        numOfAdditionalEdchCellInfo;
    TNumberOfItems        numOfAddiEdchRlMappingInfo;
    TDynamicData          dynamicData[1];
};
typedef struct BB_2_RlSetupReq BB_2_RlSetupReq;

#endif /* _BB_2_RL_SETUP_REQ_H */

/**
*********************************************************************
* @struct BB_2_RlSetupReq
* Description         : Definition of Base Band Radio Link Setup Request
*                       message
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location : ShareNet
*
********************************************************
*    Static part                                       *
********************************************************
*
* @param msgHeader :             Message header.
*                                MessageId for Setup =
*                                BB_2_RL_SETUP_REQ_MSG
*
* @param transaction :           Transaction parameters
*
* @param userId :                Instead of Node B Communication Context ID,
*                                Radio Link Handler will use User ID = Node B
*                                Communication Context ID - WAM Offset. User
*                                id is an individual inside one base station
*                                subrack.
* @param ltcomUserIndex :        User Index in DCD LTCOM
*
* @param loopMode :              Normal mode or specified testloop.
*
* @param sfn :                   The SFN is used to synchronize the L1
*                                operations. There are some values outside
*                                the normal SFN range (0 - 4095) that have
*                                specific meanings:
*                                SFN = "Execute immediately", used
*                                to indicate immediate execution, which can
*                                be use for example in
*                                CCH ACTIVATION/DEACTIVATION messages or
*                                RADIO LINK DELETION message.
*                                SFN = "Deactivated initial state" = 0xFFF1,
*                                used to indicate that the channel is to be
*                                activated at a later point. Can be used for
*                                common channels, which can later be
*                                activated with ACTIVATION messages, or in
*                                RADIO LINK SETUP message, when moving users
*                                between DSPs.
*
* @param referenceFrameOffset :  Frame offset for converting SFN (System Frame
*                                Number) values for this user to CFN (Connection
*                                Frame Number) values.
*                                CFN = (SFN - Reference RL Frame Offset + 256)
*                                mod 256.
*
* @param userType :              Type of user.
*
* @param syncStatus :            Used to indicate what is synchronization state for user
*                                that will be setup.
*
* @param dedicatedChannelDeviceAddress :   Address of LTCOM in Dedicated channel device Faraday.
*
* @param sourceDedicatedChannelDeviceAddress :  Source Dedicated Channel Device Address is used when user
*                                             is transfered from source LTCOM to destination LTCOM.
*
* @param commonChannelDeviceAddress :      Address of LTCOM in Common channel device Faraday.
*
* @param hsPdschSchedulerDeviceAddress :   Address of HSDPA RM in HS-PDSCH Scheduler device Faraday.
*
* @param telecomSicAddress :      RAKE sends syncronization messages to this address.
*
* @param powerCtrlTableIndex :  . All dedicated channel devices in the SM chain have dedicated memory
*                                locations that includes the power control information of every user
*                                in that device (Faraday). The Power Control Table Index IE tells the
*                                user location in that memory area.
*
* @param numOfDummyUserMappingInfo :      Defines Number of SDummyUserMappingInfo struct(s).
*
* @param dummyUserMappingInfo :          Dummy user mapping information
*
* @param trueUlTfcCount :         Defines the actual number of TCtfc in setup
*                                In case this message is sent to Rake, the
*                                velue of trueUlTfcCount != numOfUlTfc
*
* @param ulDpchInfoRlSetup :      Includes UL DPCH Information from IUB
*
* @param numOfDlDpchInfo :       Defines Number of SDlDpchInfoRlSetup struct(s)
*                                included in dynamicData.
*
* @param numOfRlInfo :             Defines Number of SRadioLinkSetup_Ver2 struct(s)
*                                included in dynamicData.
*
* @param numOfCmTransGapPatternSeqInfo :
*                                Defines Number of SCmTransGapPatternSeqInfo
*                                struct(s) for CM Set 1 included in dynamicData.
*
* @param numOfCmTransGapPatternSeqInfoForCmSet2 :
*                                Defines Number of SCmTransGapPatternSeqInfo
*                                struct(s) for CM Set 2 included in dynamicData.
*
* @param numOfCmActivePatternSeqInfo :
*                                Defines Number of SCmActivePatternSeqInfo
*                                struct(s) included in dynamicData.
*
* @param numOfUlTfc :            Defines Number of TCtfc struct(s) for UL
*                                included in dynamicData.
*
* @param numOfDlTfc :            Defines Number of TCtfc struct(s) for DL
*                                included in dynamicData.
*
* @param numOfDch :              Number of Dedicated transport channels in
*                                the DPCH. Defines Number of SDchInfo_Ver2
*                                struct(s) included in dynamicData.
*
* @param numOfHsDschInfo :       Defines Number of SHsDschInformation_Ver2
*                                struct(s) included in dynamicData.
*
* @param numOfEDpchInfo :        Defines Number of SEDpchInformation_Ver2 struct(s) included in
*                                dynamicData.
*
* @param numOfFDpchInfo :        Defines Number of SFDpchInformation struct(s) included in
*                                dynamicData.
* @param numOfCpcDtxDrxInfo :    Defines Number of SCpcDtxDrxInfo struct(s) included in
*                                dynamicData.
*
* @param numOfCpcHsScchInfo :    Defines Number of SCpcHsScchInfo struct(s) included in
*                                dynamicData.
*
* @param numOfPrivateRlInfo :    Defines Number of SPrivateRlInformation struct(s) included in
*                                dynamicData.
*
* @param numOfAdditionalHsCellInfo :
*                                Defines Number of SAdditionalHsCellInfo struct(s)
*                                included in dynamicData.
*
* @param numOfAdditionalEdchCellInfo :
*                                Defines Number of SAdditionalEdchCellInfo struct(s)
*                                included in dynamicData.
*
* @param numOfAddiEdchRlMappingInfo :
*                                Defines Number of SAddiEdchRlMappingInfo struct(s)
*                                included in dynamicData.
*
* @param dynamicData :           Dynamic part.
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
* @param SDlDpchInfoRlSetup :       OPTIONAL
*                                   0, 1
*                                   Number of SDlDpchInfoRlSetup to be in this
*                                   message is set to numOfDlDpchInfo in the
*                                   Static part of this message.
*
* @param SRadioLinkSetup_Ver2 :     MANDATORY
*                                   1...MAX_NR_OF_RLS
*                                   Provides RL information for the Radio Link
*                                   to be established.
*                                   Number of SRadioLinkSetup_Ver2 to be in this
*                                   message is set to numOfRlInfo in the
*                                   Static part of this message.
*
* @param SCmTransGapPatternSeqInfo : 
*                                   OPTIONAL
*                                   0, 1...MAX_TGPS
*                                   Defines the parameters for the compressed mode
*                                   set 1 gap pattern sequence.
*                                   Number of SCmTransGapPatternSeqInfo
*                                   for CM set 1 to be in this message is set to
*                                   numOfCmTransGapPatternSeqInfo in the
*                                   Static part of this message.
*
* @param SCmTransGapPatternSeqInfo : 
*                                   OPTIONAL
*                                   0, 1...MAX_TGPS
*                                   Defines the parameters for the compressed mode
*                                   set 2 gap pattern sequence.
*                                   Number of SCmTransGapPatternSeqInfo
*                                   for CM set 2 to be in this message is set to
*                                   numOfCmTransGapPatternSeqInfoForCmSet2 in the
*                                   Static part of this message.
*
* @param SCmActivePatternSeqInfo :  OPTIONAL
*                                   0, 1
*                                   Defines the parameters for the compressed mode
*                                   pattern sequence activation.
*                                   Number of SCmActivePatternSeqInfo to be in
*                                   this message is set to
*                                   numOfCmActivePatternSeqInfo in the Static
*                                   part of this message.
*
* @param TCtfc for UL :             OPTIONAL
*                                   0...MAX_NR_OF_TFCS
*                                   Transport format combination set for uplink.
*                                   Number of TCtfc to be in this message is
*                                   set to numOfUlTfc in the Static part of this
*                                   message.
*
* @param TCtfc for DL :             OPTIONAL
*                                   0...MAX_NR_OF_TFCS
*                                   Transport format combination set for downlink.
*                                   Number of TCtfc to be in this message is
*                                   set to numOfDlTfc in the Static part of this
*                                   message.
*
* @param SDchInfo_Ver2 :            OPTIONAL
*                                   0...MAX_NR_OF_DCHS
*                                   Provides information for DCHs to be
*                                   established.
*                                   Number of SDchInfo_Ver2 to be in this message
*                                   is set to numOfDch in the Static part of
*                                   this message.
*
* @param SHsDschInformation_Ver2 :  OPTIONAL
*                                   0, 1
*                                   Provides information for HS DSCH channels
*                                   to be established to MAC-hs.
*                                   Number of SHsDschInformation_Ver2 (0 or 1) to be in
*                                   this message is set to numOfHsDschInfo in the
*                                   Static part of this message.
*
* @param SEDpchInformation_Ver2 :   OPTIONAL
*                                   0, 1
*                                   Provides information for E-DPCH channels
*                                   to be establised to HSUPA L2.
*                                   Number of SEDpchInformation_Ver2 (0 or 1) to be in
*                                   this message is set to numOfEDpchInfo in the
*                                   Static part of this message.
*
* @param SFDpchInformation :        OPTIONAL
*                                   0, 1
*                                   Number of SFDpchInformation (0 or 1) to be in
*                                   this message is set to numOfFDpchInfo in the
*                                   Static part of this message.
*
* @param SCpcDtxDrxInfo :           OPTIONAL
*                                   0, 1
*                                   Number of SCpcDtxDrxInfo (0 or 1) to be in
*                                   this message is set to numOfCpcDtxDrxInfo in the
*                                   Static part of this message.
*
* @param SCpcHsScchInfo :           OPTIONAL
*                                   0, 1
*                                   Number of SCpcHsScchInfo (0 or 1) to be in
*                                   this message is set to numOfCpcHsScchInfo in the
*                                   Static part of this message.
*
* @param SPrivateRlInformation :    OPTIONAL
*                                   0, 1
*                                   Number of SPrivateRlInformation (0 or 1) to be in
*                                   this message is set to numOfPrivateRlInformation in the
*                                   Static part of this message.
*
* @param SAdditionalHsCellInfo :    OPTIONAL
*                                   0...MAX_NR_OF_HSDSCH-1
*                                   Number of SAdditionalHsCellInfo (0...MAX_NR_OF_HSDSCH-1)
*                                   to be in this message is set to numOfAdditionalHsCellInfo
*                                   in the Static part of this message.
*
* @param SAdditionalEdchCellInfo :  OPTIONAL
*                                   0, 1
*                                   Number of SAdditionalEdchCellInfo (0 or 1)
*                                   to be in this message is set to numOfAdditionalEdchCellInfo
*                                   in the Static part of this message.
*
* @param SAddiEdchInfo :            OPTIONAL
*                                   0, 1
*                                   Number of SAddiEdchInfo (0 or 1)
*                                   to be in this message is set to numOfAddiEdchInfo
*                                   in the Static part of this message.
*
* Additional Information :
*
* Definition Provided by : DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/

