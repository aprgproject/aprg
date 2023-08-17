/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SPicPoolInfo.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        Bartosz Ciesla
* 
* Copyright 2010 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_PIC_POOL_INFO_H
#define _S_PIC_POOL_INFO_H

#include <glo_def.h>
#include <TNumberOfItems.h>
#include <SPicPoolLcrInfo.h>
#include <DOpenIUBCommonDefs.h>

struct SPicPoolInfo
{
     u32             picPoolId;
     TNumberOfItems  numOfPicPoolLcrInfo;
     SPicPoolLcrInfo picPoolLcrInfo[MAX_NUM_OF_PIC_POOL_LCR_INFO];
};
typedef struct SPicPoolInfo SPicPoolInfo;

#endif /* _S_PIC_POOL_INFO_H */

/**
*******************************************************************************
* @struct SPicPoolInfo
*
* Description         : PIC Pool information structure
*
* Reference           : WCDMA BTS SW BTSOM-TCOM IFS version 28.0, ShareNet-IMS
*
* Parameters :
*
* @param picPoolId           : PIC Pool identifier
* @param numOfPicPoolLcrInfo : Informs how many valid PIC Pool LCR Info structures will follow
* @param picPoolLcrInfo      : PIC Pool LCR info structures
*
* Additional Information : -
*
* Definition Provided by : Bartosz Ciesla / Telecom
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

