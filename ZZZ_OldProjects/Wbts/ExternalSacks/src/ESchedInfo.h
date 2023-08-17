/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/ESchedInfo.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Kari Korvela
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_SCHED_INFO_H
#define _E_SCHED_INFO_H

typedef enum ESchedInfo
{
    ESchedInfo_Included     = 0,
    ESchedInfo_NotIncluded  = 1
}ESchedInfo;

#endif /* _E_SCHED_INFO_H */

/******************************************************************************
* @enum ESchedInfo
* Description         : Schedling information indicator.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: PI
*
* Additional Information : 
*
* Definition Provided by : DSP, L2
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

