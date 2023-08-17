/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SDtxInformation.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Krzysztof Michalak
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_DTX_INFORMATION_H
#define _S_DTX_INFORMATION_H

#include <EETti.h>
#include <EUeCycle.h>
#include <EInactivityThreshold.h>
#include <EUeDtxLongPreamble.h>
#include <ECqiDtxTimer.h>
#include <EUeDpcchBurst.h>

struct SDtxInformation
{
  EETti                 eDchTtiLength;
  EUeCycle              ueDtxCycle1;
  EUeCycle              ueDtxCycle2;
  EUeCycle              macDtxCycle;
  EInactivityThreshold  inactivThresholdUeDtxCycle2;
  EUeDtxLongPreamble    ueDtxLongPreamble;
  EInactivityThreshold  macInactivThreshold;
  ECqiDtxTimer          cqiDtxTimer;
  EUeDpcchBurst         ueDpcchBurst1;
  EUeDpcchBurst         ueDpcchBurst2;
};

typedef struct SDtxInformation SDtxInformation;

#endif /* _S_DTX_INFORMATION_H */

/******************************************************************************
* @struct SDtxInformation
* Description         : DTX Information
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: PI
*
* @param eDchTtiLength :
*   E-DCH TTI Length
*
* @param ueDtxCycle1 :
*   Units of subframes If the E-DCH TTI Length IE has been set to 
*   EEdchTtiLength_10ms only values 1, 5, 10 and 20 are supported.
*
* @param ueDtxCycle2 :
*   Units of subframes If the E-DCH TTI Length IE has been set to 
*   EEdchTtiLength_10ms only values 5, 10, 20, 40, 80 and 160 are 
*   supported.
*
* @param macDtxCycle :
*   Units of subframes If the E-DCH TTI Length IE has been set to 
*   EEdchTtiLength_10ms only values 5, 10 and 20 are supported.
* 
* @param inactivThresholdUeDtxCycle2 :
*   Units of E-DCH TTIs
*
* @param ueDtxLongPreamble :
*   Units of slots
*
* @param macInactivThreshold :
*   Units of E-DCH TTIs
*
* @param cqiDtxTimer :
*   Units of subframes
*
* @param ueDpcchBurst1 :
*   Units of subframes
*
* @param ueDpcchBurst2 :
*   Units of subframes
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

