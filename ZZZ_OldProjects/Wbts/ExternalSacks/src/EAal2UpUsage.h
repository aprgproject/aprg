/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EAal2UpUsage.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        TUP Kari Vakeva
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _E_AAL2_UP_USAGE_H
#define _E_AAL2_UP_USAGE_H

typedef enum EAal2UpUsage
{
    EAal2UpUsage_Any           = 0,
    EAal2UpUsage_Shared        = 1,
    EAal2UpUsage_Dch           = 2,
    EAal2UpUsage_Hsdpa         = 3,
    EAal2UpUsage_Hsupa         = 4,
    EAal2UpUsage_Hspa          = 5,
    EAal2UpUsage_NotApplicable = 6
} EAal2UpUsage;

#endif /* _E_AAL2_UP_USAGE_H */

/**
*******************************************************************************
* @enum EAal2UpUsage
*
* Description         : AAL2 UP Usage parameter (for TUP Hw config).
*
* Reference           : TUP IFS
*                       WCDMA BTS SW BTSOM-TCOM IFS, version 11.0, PI
*
* Parameters :
*
* @param EAal2UpUsage_Any            : (any)
* @param EAal2UpUsage_Shared         : SHARED
* @param EAal2UpUsage_Dch            : DCH
* @param EAal2UpUsage_Hsdpa          : HSDPA
* @param EAal2UpUsage_Hsupa          : HSUPA
* @param EAal2UpUsage_Hspa           : HSPA
* @param EAal2UpUsage_NotApplicable  : NOT_APPLICABLE
*
* Additional Information : Taken into use from WN3.1 onward (Nora) because of
*                          new Route Selection and Path Selection features.
*
* Definition Provided by : TUP
*                          Telecom
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/


