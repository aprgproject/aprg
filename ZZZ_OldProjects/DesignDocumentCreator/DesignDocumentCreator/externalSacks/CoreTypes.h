/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_GLOBAL/tags/GLOBAL_ENV_13_168/I_Interface/Global_Env/Definitions/CoreTypes.h $
* @version               $LastChangedRevision: 3080 $
* @date                  $LastChangedDate: 2014-05-23 20:32:51 +0800 (Fri, 23 May 2014) $
* @author                $Author: plaskonk $
*
* Original author        <nn>
*
* Copyright 2010 Nokia. All rights reserved.
*******************************************************************************/
#ifndef _CORE_TYPES_H
#define _CORE_TYPES_H

#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <EMonitorMode.h>

#include <TMsgHeaderTypes.h>
#include <SMessageAddress.h>
#include <SHeaderFlags.h>

#include <SMessageHeader.h>

#include <TSize.h>

#include <TTimeBase.h>

#include <TOsPid.h>

#ifndef UF_RELIABLE_ACK_REQ
/* Dummy definition for backward compatibility to old CPA version */
#define UF_RELIABLE_ACK_REQ      0x20
/*********
*
* Note that the obsolete user flag UF_RELIABLE_ACK_REQ has been removed.
* This definition here is temporary just to make old version of Platform Agent
* to compile. An application is not allowed to use the obsolete user
* flag.
*
*********/
#endif
 

typedef u32         TMessageFlags;
typedef u32         TTimerId;
typedef TMessageId  TMessageFilter;
typedef u32         TAgentError;
typedef i32         TSemaphoreValue;
typedef u8          TSemaphore;     /* TODO - improve (used as pointer)*/
typedef u32         TOsPriority;
typedef u32         TOsTimeSlice;
typedef u32         TOsIntVector;
#ifndef __TLC_PC_ENV
typedef u64         TDelayTime;
typedef void (TOsEntryPoint)(void);
#endif
typedef enum EOsProcType
{
    EOsProcType_Normal      = 0,
    EOsProcType_BackGround  = 1,
    EOsProcType_Timer       = 2,
    EOsProcType_Dummy       = 3,
    EOsProcType_Interrupt   = 4
} EOsProcType;
typedef u32         TEventActionBits;
typedef enum ELogType
{
    ELogType_None       =0, /* these must be in order*/
    ELogType_Fatal      =1, /* starting from 0 (used internally as index)!*/
    ELogType_Error      =2,
    ELogType_Warning    =3,
    ELogType_Info       =4,
    ELogType_Debug      =5,
    ELogType_ExtraDebug =6,  /* paranoid debugging...*/
    ELogType_Last       =7   /* used only internally!*/
} ELogType;
typedef enum ECoreRetVal
{
    ECoreRetVal_OK                  = 0,
    ECoreRetVal_NotInitialized      = 1,     /* Requested operation is not initialized*/
    ECoreRetVal_InvalidArgument     = 2,     /* Input parameter error*/
    ECoreRetVal_NotSupported        = 3,     /* Unsupported operation attempted*/
    ECoreRetVal_Timeout             = 4,     /* Receive or other timeout*/
    ECoreRetVal_NoMemory            = 5,     /* Out of memory*/
    ECoreRetVal_BufferCorrupted     = 6,     /* Message buffer was corrupted*/
    ECoreRetVal_NoMessage           = 7,     /* No message waiting (poll)*/
    ECoreRetVal_Expired             = 8,     /* Timer already expired*/
    ECoreRetVal_TooMany             = 9,     /* Too many requested objects*/
    ECoreRetVal_Unexpected          = 10,    /* Unexpected error, should never happen.*/
    ECoreRetVal_NoSuchObject        = 11,    /* Unknown task etc.*/
    ECoreRetVal_OperationFailed     = 12,    /* Any other reason...*/
    ECoreRetVal_OverFlow            = 13,    /* Buffer overflow etc.*/
    ECoreRetVal_Busy                = 14,    /* Try again later*/
    ECoreRetVal_IntegrityFailed     = 15,    /* Data possibly garbage (checksum fail etc)*/
    ECoreRetVal_EncodeMessageFailed = 16,    /* Encoded message size still exceeds DSC_MTU*/
    ECoreRetVal_Undefined           = 99
} ECoreRetVal;
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* _CORE_TYPES_H */

/**
*******************************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions /
*
* Description  : THIS IS OBSOLETE FILE TO BE REMOVED SOME DAY!!
*                It is left in bs_env to not break all code.
*                Start using the separate definitions. Types removed
*                from here will appear in AgentTypes.hpp
*                (for CorePlatformAgent users)
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* Additional Information : <type additional information if needed>
*
* Title        : Type definitions for CorePlatformAgent
*
* Definition Provided by : ATM / Krister Wikstrom
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



