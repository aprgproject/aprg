/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SDynamicTransportFormatInfoLST.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _SDYNAMICTRANSPORTFORMATINFOLST_H
#define _SDYNAMICTRANSPORTFORMATINFOLST_H

#include <TNumberOfTransportBlocks.h>
#include <STransportBlockSizeCOND.h>

typedef struct SDynamicTransportFormatInfoLST
{
    TNumberOfTransportBlocks  numberOfTransportBlocks;
    STransportBlockSizeCOND   transportBlockSize;
} SDynamicTransportFormatInfoLST;

#endif /* _SDYNAMICTRANSPORTFORMATINFOLST_H */

/**
*******************************************************************************
* @struct SDynamicTransportFormatInfoLST
*
* Description :
*
* Reference   : 3GPP TS 25.433 v4.1.0
*
* Parameters  :
*
* @param numberOfTransportBlocks:
* @param transportBlockSize :
*
* Additional Information :
*    Semantics description: The first instance of the parameter corresponds to TFI zero,
*                           the second to 1 and so on.
*
*    STransportBlockSizeCOND: This IE is only present if
*                             "Number of Transport Blocks" is greater than 0
*
* Definition Provided by : Telecom / Jesse Pasuri / Mika Hautala
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



