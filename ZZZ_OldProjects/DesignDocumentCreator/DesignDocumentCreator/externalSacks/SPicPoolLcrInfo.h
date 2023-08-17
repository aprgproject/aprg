/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SPicPoolLcrInfo.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        Bartosz Ciesla
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _S_PIC_POOL_LCR_INFO_H
#define _S_PIC_POOL_LCR_INFO_H

#include <TLocalCellResId.h>
#include <glo_def.h>

struct SPicPoolLcrInfo
{
     TLocalCellResId    localCellResId;
     u32                amountOfAntennasPerLcr;
};
typedef struct SPicPoolLcrInfo SPicPoolLcrInfo;

#endif /* _S_PIC_POOL_LCR_INFO_H */

/**
*******************************************************************************
* @struct SPicPoolLcrInfo
*
* Description         : LCR and antenna amount per PIC pool
*
* Reference           : WCDMA BTS SW BTSOM-TCOM IFS version 28.0, ShareNet-IMS
*
* Parameters :
*
* @param localCellResId         : Local cell resource id
* @param amountOfAntennasPerLcr : Amount of antennas assigned for PIC Pool
*
* Additional Information : -
*
* Definition Provided by : Bartosz Ciesla / Telecom
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

