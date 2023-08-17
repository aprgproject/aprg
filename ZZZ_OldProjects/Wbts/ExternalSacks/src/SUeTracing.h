/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SUeTracing.h $
* @version               $LastChangedRevision: 4909 $
* @date                  $LastChangedDate: 2016-06-13 17:52:20 +0800 (Mon, 13 Jun 2016) $
* @author                $Author: shubchen $
*
* Original author        Chen Shubao
*
* Copyright 2016 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _SUE_TRACING_H
#define _SUE_TRACING_H

#include <EUeTracingState.h>
#include <SRlEutranTraceId.h>

struct SUeTracing
{
    EUeTracingState    ueTracingState;
    SRlEutranTraceId   rlEutranTraceId;
};
typedef struct SUeTracing SUeTracing;

#endif /* _SUE_TRACING_H */

/******************************************************************
* @struct SUeTracing
* Development Workset : WCDMA:BS_ENV_WS
*
* Description         : This structure contains the needed information for UE tracing.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* Parameters :
*
* @param ueTracingState : This indicates to enable or disable UE tracing, or not changed.
*
* @param rlEutranTraceId : Contains the RNC ID, Computer Trace ID, Family Trace ID, Process ID.
*                          This parameter is valid only when ueTracingState is EUeTracingState_Enable.
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : TCOM, DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/

