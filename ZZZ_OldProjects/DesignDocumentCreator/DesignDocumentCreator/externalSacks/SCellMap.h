/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SCellMap.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef SCELLMAP_H
#define SCELLMAP_H

#include <TCellId.h>
#include <TLocalCellID.h>

typedef struct SCellMap
{
    TCellId            cellId;         /* cell id used in Iub IF*/
    TLocalCellID     localCellResId; /* local cell resource id*/
} SCellMap;

#endif /* SCELLMAP_H */

/**
*******************************************************************************
* @struct SCellMap
*
* Description : Type for Local cell mapping info
*
* Reference   : Wcdma Bts O&M - Telecom interface specification v. 0.3.0,
*       used Helena type SCellMap as a base
*
* Parameters:
*
* @param cellId :
* @param localCellResId :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom / Iker Garagarza
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



