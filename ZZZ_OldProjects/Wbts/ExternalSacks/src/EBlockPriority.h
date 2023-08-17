/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EBlockPriority.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _EBLOCKPRIORITY_H
#define _EBLOCKPRIORITY_H

typedef enum EBlockPriority
{
    EBlockPriority_High   = 0,
    EBlockPriority_Normal = 1,
    EBlockPriority_Low    = 2
} EBlockPriority;

#endif /* _EBLOCKPRIORITY_H */

/**
*******************************************************************************
* @enum EBlockPriority
*
* Description : 9.2.15  Block priority indicator -
*
* Reference   : 3GPP TS 25.433 v4.3.0
*
* Parameters  :
*
* @param EBlockPriority_High   : Block resource immediately.
* @param EBlockPriority_Normal : Block resource when idle or upon timer expiry.
* @param EBlockPriority_Low    : Block resource when idle.
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom / Mika Kauppinen
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



