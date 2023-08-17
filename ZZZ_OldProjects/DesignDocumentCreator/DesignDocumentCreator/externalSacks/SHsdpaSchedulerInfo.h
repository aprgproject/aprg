/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SHsdpaSchedulerInfo.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        Bartosz Ciesla
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _S_HSDPA_SCHEDULER_INFO_H
#define _S_HSDPA_SCHEDULER_INFO_H

#include <EHsdpaSchedulerId.h>
#include <glo_def.h>

typedef struct SHsdpaSchedulerInfo
{
    EHsdpaSchedulerId schedulerId;
    u32               schedulerThroughput;
} SHsdpaSchedulerInfo;

#endif /* _S_HSDPA_SCHEDULER_INFO_H */

/**
*******************************************************************************
* @struct SHsdpaSchedulerInfo
*
* Description         : Structure which defines HSDPA scheduler max throughput
*
* Reference           : BTSOM Telecom IFS, 37.0, ShareNet-IMS
*
* Parameters :
*
* @param schedulerId         : HSDPA Scheduler Id
* @param schedulerThroughput : Max Throughput Per HSDPA Scheduler
*
* Additional Information :
*
* Definition Provided by : Telecom
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

