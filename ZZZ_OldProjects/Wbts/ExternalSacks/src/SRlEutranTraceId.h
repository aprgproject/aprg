/**
*******************************************************************************
* @file                  $HeadURL:
* @version               $LastChangedRevision:
* @date                  $LastChangedDate:
* @author                $Author:
*
* Original author        Chen Shubao
*
* Copyright 2016 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _SRL_EUTRAN_TRACE_ID_H
#define _SRL_EUTRAN_TRACE_ID_H

#include <glo_def.h>

struct SRlEutranTraceId
{
    u32 traceSessionIdForRNCId;
    u32 traceSessionIdForComputer;
    u32 traceSessionIdForFamily;
    u32 traceRecSessionId;
};
typedef struct SRlEutranTraceId SRlEutranTraceId;

#endif /* _SRL_EUTRAN_TRACE_ID_H */

/**
*******************************************************************************
* @struct SRlEutranTraceId
* Development Workset : WCDMA:BS_ENV_WS
*
* Description                      : From TCOM to DSP contains EUTRAN Trace ID.
*
* Reference                        : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                                    DSP SW - MCU SW INTERFACE SPECIFICATION
*                                    Location: Sharenet
*
* Parameters :
*
* @param traceSessionIdForRNCId      : Trace Session ID-RNC Id for given UE
*
* @param traceSessionIdForComputer      : Trace Session ID-Computer for given UE
*
* @param traceSessionIdForFamily      : Trace Session ID-Family for given UE
*
* @param traceRecSessionId      : Trace Recording Session ID for given UE
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : TCOM, DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

