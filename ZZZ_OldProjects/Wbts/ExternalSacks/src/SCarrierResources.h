/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SCarrierResources.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _S_CARRIER_RESOURCES_H
#define _S_CARRIER_RESOURCES_H

#include <Glo_bs.h>
#include <SRxTxResource.h>

typedef struct SCarrierResources
{
    SRxTxResource        txResource[MAX_NUM_OF_TX_RESOURCES];
    SRxTxResource        rxResource[MAX_NUM_OF_RX_RESOURCES];
} SCarrierResources;

#endif /* _S_CARRIER_RESOURCES_H */

/**
*******************************************************************************
* @struct SCarrierResources
*
* Description :  Structure of carrier resources
*
* Reference   :  BTSOM - TCOM Interface Specification, v 3.0, PI
*
* Parameters :
*
* @param txResource : Tx carrier resources
*
* @param rxResource : Rx carrier resources
*
* Additional Information : -
*
* Definition Provided by   : Margus Metsanurm
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/
