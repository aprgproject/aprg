/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SCpcHsScchInfo.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_CPC_HS_SCCH_INFO_H
#define _S_CPC_HS_SCCH_INFO_H

#include <TNumberOfItems.h>
#include <STranspBlockSizeList.h>
#include <DOpenIUBCommonDefs.h>

struct SCpcHsScchInfo
{
  TNumberOfItems          numOfTransportBlSize;
  STranspBlockSizeList    transportBlSizeList[MAX_NR_OF_HS_DSCH_TBS_HS_SCCH_LESS];
};

typedef struct SCpcHsScchInfo SCpcHsScchInfo;

#endif /* _S_CPC_HS_SCCH_INFO_H */

/******************************************************************************
* @struct SCpcHsScchInfo
* Description         : Continuous Packet Connectivity HS-SCCH less Information
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param numOfTransportBlSize :
*   Number of Transport Block Size List
*
* @param transportBlSizeList:
*   Transport Block Size List
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

