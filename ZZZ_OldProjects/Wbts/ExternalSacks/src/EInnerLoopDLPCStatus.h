/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EInnerLoopDLPCStatus.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Telecom
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_INNER_LOOP_DL_PC_STATUS_H
#define _E_INNER_LOOP_DL_PC_STATUS_H

#include <DFromTc_dsp.h>

typedef enum EInnerLoopDLPCStatus
{
    EInnerLoopDLPCStatus_Active     = 0,
    EInnerLoopDLPCStatus_Inactive   = 1,
    EInnerLoopDLPCStatus_NoValue    = NO_VALUE_FOR_ENUMS
}EInnerLoopDLPCStatus;

#endif  /* _E_INNER_LOOP_DL_PC_STATUS_H */

/******************************************************************************
* @enum EInnerLoopDLPCStatus
* Description         : The Inner Loop DL PC Status IE indicates whether inner
*                       loop DL power control shall be active or inactive for 
*                       all radio links associated with the context identified 
*                       by the Node B Communication Context Id IE.
*
* Reference           : DSP SW - MCU SW Interface Specification
*                       Link to PI:
*                       espoo11/Projects/WCDMA RAN/WCDMA BTS/WBTS3.x/
*                       2 Technical Management/Specification/Specification
*                       Documents/IFS
*
* @param EInnerLoopDLPCStatus_Active   : The inner loop DL PC shall be active.
* @param EInnerLoopDLPCStatus_Inactive : The inner loop DL PC shall be inactive.
* @param EInnerLoopDLPCStatus_NoValue  : "This IE is not present."
*
* Additional Information : N/A
*
* Definition Provided by : DSP, Kari Korvela
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

