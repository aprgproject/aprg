/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/STransportBlockSizeCOND.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _STRANSPORTBLOCKSIZECOND_H
#define _STRANSPORTBLOCKSIZECOND_H

#include <EIEPresentType.h>
#include <TTransportBlockSize.h>

typedef struct STransportBlockSizeCOND
{
        EIEPresentType          iePresent;
        TTransportBlockSize     blocksize;
} STransportBlockSizeCOND;

#endif /* _STRANSPORTBLOCKSIZECOND_H */

/**
*******************************************************************************
* @struct STransportBlockSizeCOND
*
* Description :
*
* Reference   : 3GPP TS 25.433 v4.1.0
*
* Parameters  :
*
* @param iePresent :
* @param blocksize :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom / Jesse Pasuri / Mika Hautala
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



