/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Messages/oam_tcom.h $
* @version               $LastChangedRevision: 2809 $
* @date                  $LastChangedDate: 2018-10-04 11:44:19 +0800 (Thu, 04 Oct 2018) $
* @author                $Author: echano $
*
* Original author        <nn>
*
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _OAM_TCOM_H
#define _OAM_TCOM_H

#include <EBlockPriority.h>
#include <EBlockResult.h>
#include <ECellAvailabilityState.h>
#include <EConfigChangeAddAction.h>
#include <EConfigChangeType.h>
#include <EConfigInfoType.h>
#include <EFreeResourceRespResult.h>
#include <EHoRequestResult.h>
#include <ELinkState.h>
#include <EState.h>
#include <EStatus.h>
#include <EUpdateStatus.h>
#include <IfAaSysCom.h>
#include <SBsConfigData.h>
#include <SCarrierResources.h>
#include <SCellMap.h>
#include <SLocalCellParameters.h>
#include <SLocalCellResource.h>
#include <SMessageAddress.h>
#include <SMessageHeader.h>
#include <STtpSignalingLinkStates.h>
#include <SWamUnit.h>
#include <SWspUnit.h>
#include <TAaSysComSicad.h>
#include <TCarrierNumber.h>
#include <TCellId.h>
#include <TDynamicData.h>
#include <TLocalCellResId.h>
#include <TNumberOfItems.h>
#include <UConfigInfoElement.h>

struct SHwConfigurationMsg
{
    MESSAGEHEADER(msgHeader)
    SMessageAddress         btsomTelecomServiceAddr;
    SMessageAddress         lmsAddress;
    TAaSysComNid            tupcAalmanNid;
    TAaSysComNid            tupcConmanNid;
    SWamUnit                wamUnit[MAX_NUM_OF_CONTROL_UNITS];
    SWspUnit                wspUnit[MAX_NUM_OF_DSP_RESOURCES];
    SCarrierResources       carrierResources;
    TNumberOfItems          numOfValidLcr;
    SLocalCellResource      localCellResource[MAX_NUM_OF_LOCAL_CELLS];
    SBsConfigData           bsConfigData;
    TNumberOfItems          btsSwVersionLength;
    TDynamicData            btsSwVersion[1];
};
typedef struct SHwConfigurationMsg SHwConfigurationMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader                    API message header
*
*  btsomTelecomServiceAddr      BTSOM Telecom service address
*
*  lmsAddress                   Address to be used for any TCOM-originated messages going to License Management Service
*
*  tupcAalmanNid                The address TUPC instance near TRSW instance
*
*  tupcConmanNid                TUPC address
*
*  wamUnit[..]                  WAM/FCM/FSPB units config info
*
*  wspUnit[..]                  WSP/FSPA/Faraday units config info
*
*  carrierResources             Carrier resources config info
*
*  numOfValidLcr                Indicates how many of following array elements are valid
*
*  localCellResource[..]        Local cell resources config info
*
*  bsConfigData                 Commissioning parameters
*
*  btsSwVersionLength           Number of octets needed for BTS SW Version
*
*  btsSwVersion                 Start of dynamic data for ASCII encoded BTS SW Version (without null terminator), the size is indicated by btsSwVersionLength
*
***********************************************************************/



struct SHwConfigurationResponseMsg
{
    MESSAGEHEADER(msgHeader)
    EStatus             status;
};
typedef struct SHwConfigurationResponseMsg SHwConfigurationResponseMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader    API message header
*
*  status       status code
*
***********************************************************************/



struct SHwConfigurationChangeMsg
{
    MESSAGEHEADER(msgHeader)
    EConfigInfoType        configInfoType;
    UConfigInfoElement     configInfoElement;
    EConfigChangeType      configChangeType;
    EConfigChangeAddAction configChangeAddAction;
};
typedef struct SHwConfigurationChangeMsg SHwConfigurationChangeMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader            API message header
*
*  configInfoType       indicates which info struct the following element contains
*
*  configInfoElement    contains the info about the changed unit or cell resource
*
*  configChangeType     contains the info about type of the configuration change
*
*  configChangeAddAction contains information about additional action type
*
************************************************************************/



struct SHwConfigurationChangeResponseMsg
{
    MESSAGEHEADER(msgHeader)
    EStatus             status;
};
typedef struct SHwConfigurationChangeResponseMsg SHwConfigurationChangeResponseMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader    API message header
*
*  status       status code
*
************************************************************************/



struct SLocalCellResourceStateIndicationMsg
{
    MESSAGEHEADER(msgHeader)
    TLocalCellResId     localCellResId;
    EState              localCellResState;
};
typedef struct SLocalCellResourceStateIndicationMsg SLocalCellResourceStateIndicationMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader            API message header
*
*  localCellResId       local cell resource id
*
*  localCellResState    state of local cell resource
*
************************************************************************/



struct SClockStateMsg
{
    MESSAGEHEADER(msgHeader)
    u32          spare;
};
typedef struct SClockStateMsg SClockStateMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader        API message header
*
*  spare            needed for CC&S SW
*
************************************************************************/



struct SLocalCellMappingInfoMsg
{
    MESSAGEHEADER(msgHeader)
    TNumberOfItems    numOfCellMaps;
    SCellMap          cellMap[MAX_NUM_OF_LOCAL_CELLS];
};
typedef struct SLocalCellMappingInfoMsg SLocalCellMappingInfoMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader        API message header
*
*  numOfCellMaps    number of valid cell maps
*
*  cellMap[..]      maps LCR Ids to Cell Ids
*
************************************************************************/



struct SCellAvailabilityStateRequestMsg
{
    MESSAGEHEADER(msgHeader)
    TLocalCellResId     localCellResId;
};
typedef struct SCellAvailabilityStateRequestMsg SCellAvailabilityStateRequestMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader        API message header
*
*  localCellResId   local cell resource Id
*
************************************************************************/



struct SCellAvailabilityStateIndicationMsg
{
    MESSAGEHEADER(msgHeader)
    TLocalCellResId         localCellResId;
    ECellAvailabilityState  cellAvailabilityState;
    TAaSysComSicad          cchAddress;
};
typedef struct SCellAvailabilityStateIndicationMsg SCellAvailabilityStateIndicationMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader                API message header
*
*  localCellResId           local cell resource Id
*
*  cellAvailabilityState    availablity state (incative / active) of the cell
*
*  cchAddress               CCH Faraday address
*
************************************************************************/



struct SStartForcedHoMsg
{
    MESSAGEHEADER(msgHeader)
    TLocalCellResId     localCellResId;
};
typedef struct SStartForcedHoMsg SStartForcedHoMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader        API message header
*
*  localCellResId   local cell resource Id
*
************************************************************************/



struct SHoFinishedMsg
{
    MESSAGEHEADER(msgHeader)
    TLocalCellResId     localCellResId;
    EHoRequestResult    hoRequestResult;
};
typedef struct SHoFinishedMsg SHoFinishedMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader        API message header
*
*  localCellResId   local cell resource Id
*
*  hoRequestResult  result of the HO request
*
************************************************************************/



struct SLinkStatesMsg
{
    MESSAGEHEADER(msgHeader)
    ELinkState                  cnbapLinkState;
    STtpSignalingLinkStates     ttpSignalingLinkStates[MAX_NUM_OF_CONTROL_UNITS];
    TBoolean                    testModeFlag;
};
typedef struct SLinkStatesMsg SLinkStatesMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader                    API message header
*
*  cnbapLinkState               state of C-NBAP link
*
*  ttpSignalingLinkStates[..]   state of D-NBAP and AAL2 Sig link of
*                               each Traffic Termination Point
*
*  testModeFlag                 indicates if BS is in test mode
*
************************************************************************/



struct SLinkStatesResponseMsg
{
    MESSAGEHEADER(msgHeader)
    u32          spare;
};
typedef struct SLinkStatesResponseMsg SLinkStatesResponseMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader                    API message header
*
*  spare                        needed for CC&S SW
*
************************************************************************/



struct SFreeResourceReqMsg
{
    MESSAGEHEADER(msgHeader)
    TBoard              boardId;
};
typedef struct SFreeResourceReqMsg SFreeResourceReqMsg;



/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader            API message header
*
*  wspAddress           unit address of the WSP which is going to be
*                       blocked.
*
*  chipId               Faraday chip address (needed only with FSPB)
*
************************************************************************/



struct SFreeResourceRespMsg
{
    MESSAGEHEADER(msgHeader)
    TBoard                  boardId;
    u8                      pad1;
    u16                     pad2;
    EFreeResourceRespResult result;
    TNumberOfItems          numOfCellsInBoard;
    TCellId                 cellIdList[MAX_NUM_OF_LOCAL_CELLS];
};
typedef struct SFreeResourceRespMsg SFreeResourceRespMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader            API message header
*
*  wspAddress           unit address of the blocked WSP
*
*  chipId               Faraday chip address (needed only with FSPB)
*
*  result               indicates the success
*
*  numOfCellsInWsp      indicates number of cells which had common channels in this WSP-card
*
*  cellIdList           cell id's which had common channels
*
************************************************************************/



struct SBtsManagerUsedIndMsg
{
    MESSAGEHEADER(msgHeader)
    u32          spare;
};
typedef struct SBtsManagerUsedIndMsg SBtsManagerUsedIndMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader                    API message header
*
*  spare                        needed for CC&S SW
*
************************************************************************/



struct STcomStartupReadyIndMsg
{
    MESSAGEHEADER(msgHeader)
    u32          spare;
};
typedef struct STcomStartupReadyIndMsg STcomStartupReadyIndMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader                    API message header
*
*  spare                        needed for CC&S SW
*
************************************************************************/



struct SLocalCellParametersIndMsg
{
    MESSAGEHEADER(msgHeader)
    TNumberOfItems          numOfCells;
    SLocalCellParameters    cellParameterList[MAX_NUM_OF_LOCAL_CELLS];
};
typedef struct SLocalCellParametersIndMsg SLocalCellParametersIndMsg;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader                    API message header
*
*  numOfCells                   number of cells reported in message
*
*  cellParameterList            list of parameters that are reported
*
************************************************************************/



struct SCellBlockingReq
{
    MESSAGEHEADER(msgHeader)
    TLocalCellResId         localCellResId;
    EBlockPriority          blockPriority;
};
typedef struct SCellBlockingReq SCellBlockingReq;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader        API message header
*
*  localCellResId   local cell resource Id
*
*  blockPriority    blocking priority (high, normal, low)
*
************************************************************************/



struct SCellBlockingResp
{
    MESSAGEHEADER(msgHeader)
    TLocalCellResId         localCellResId;
    EBlockResult            blockResult;
};
typedef struct SCellBlockingResp SCellBlockingResp;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader        API message header
*
*  localCellResId   local cell resource Id
*
*  blockResult      result of cell blocking
*
************************************************************************/



struct SCancelBlockingInd   /* OAM --> Toam*/
{
    MESSAGEHEADER(msgHeader)
    TLocalCellResId         localCellResId;
};
typedef struct SCancelBlockingInd SCancelBlockingInd;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader        API message header
*
*  localCellResId   local cell resource Id
*
*
************************************************************************/



struct SCellInformationInd   /* Toam --> OAM*/
{
    MESSAGEHEADER(msgHeader)
    EUpdateStatus            updateStatus;
    TLocalCellResId          localCellResourceId;
    TCellId                  cellId;
    TAaSysComSicad           dssDspAddress;
    TAaSysComSicad           cchDspAddress;
};
typedef struct SCellInformationInd SCellInformationInd;

/*************************** PARAMETERS IN STRUCT **********************
*
*  msgHeader             API message header
*
*  addDeleteIndicator    indicates add (for cell setup) or delete (for cell deletion)
*
*  localCellResourceId   LCR ID of the cell
*
*  cellId                Cell ID of the cell
*
*  dssDspAddress         DSS DSP address mapped to the cell
*
*  cchDspAddress         CCH DSP address mapped to the cell
*
*
************************************************************************/

#endif /* _OAM_TCOM_H */

/**
*******************************************************************************
* Description : Collection of message definitions for O&M-Telecom
*               interface
*
* Reference   : WCDMA BTS SW BTSOM-TCOM IFS, version 13.0. PI
*
* Parameters  :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom / Jari Jamsa,Telecom / Aldina Codesso / Margus Metsanurm
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
************************************************************************/

