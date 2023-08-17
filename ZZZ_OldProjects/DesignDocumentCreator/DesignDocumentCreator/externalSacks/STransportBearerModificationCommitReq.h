/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Messages/STransportBearerModificationCommitReq.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Lukasz Haracz
*
* Copyright 2013 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_TRANSPORT_BEARER_MODIFICATION_COMMIT_REQ_H
#define _S_TRANSPORT_BEARER_MODIFICATION_COMMIT_REQ_H

#include <SMessageHeader.h>
#include <TTransactionID.h>
#include <TCellId.h>
#include <TNbccId.h>

struct STransportBearerModificationCommitReq
{
    MESSAGEHEADER(msgHeader)
    TTransactionID     transactionId;
    TCellId            cellId;
    TNbccId            nbccId;
};
typedef struct STransportBearerModificationCommitReq STransportBearerModificationCommitReq;

#endif /* _S_TRANSPORT_BEARER_MODIFICATION_COMMIT_REQ_H */

/**
*******************************************************************************
* @struct STransportBearerModificationCommitReq
*
* Description         : Telecom internal message
*
* Reference           : WCDMA BTS TCOM SW
*
* @param msgHeader                :  Message header
* @param transactionId            :  Transaction ID
* @param cellId                   :  CellId
* @param nbccId                   :  NbccId
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

