/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SDynamicTfInfo.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef SDYNAMICTFINFO_H
#define SDYNAMICTFINFO_H

#include <TNumberOfItems.h>
#include <TTransportBlockSize.h>

 
/*Transport Format Set*/
/************************************************************
*   The type definitions for dynamic parts of message		*
************************************************************/
struct SDynamicTfInfo
{
    TNumberOfItems             numberOfTransportBlocks;
    TTransportBlockSize        transportBlockSize;
};
typedef struct SDynamicTfInfo SDynamicTfInfo;

#endif /* SDYNAMICTFINFO_H */

/**
*******************************************************************************
* @struct SDynamicTfInfo
*
* Description :
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* @param numberOfTransportBlocks :
* @param transportBlockSize :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



