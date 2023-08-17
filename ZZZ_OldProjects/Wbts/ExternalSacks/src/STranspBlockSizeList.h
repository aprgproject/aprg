/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/STranspBlockSizeList.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Krzysztof Michalak
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_TRANSP_BLOCK_SIZE_LIST_H
#define _S_TRANSP_BLOCK_SIZE_LIST_H

#include <TNumberOfItems.h>

struct STranspBlockSizeList
{
    TNumberOfItems   transpBlockSizeIndex;
    TNumberOfItems   hsPdschSecondCodeSupport;
};

typedef struct STranspBlockSizeList STranspBlockSizeList;

#endif /* _S_TRANSP_BLOCK_SIZE_LIST_H */

/******************************************************************************
* @struct STranspBlockSizeList
* Description         : Transport Block Size List
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: PI
*
* @param transpBlockSizeIndex :
*   Transport Block Size Index
*
* @param hsPdschSecondCodeSupport :
*   False ('0') = The second HS-PDSCH code shall not be used
*   True ('1') = The second HS-PDSCH code shall also be used
*
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

