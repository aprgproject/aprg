/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Messages/STransportBearerReallocationCommitReq.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Olgierd Sobinski
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/
#ifndef _STRANSPORT_BEARER_REALLOCATION_COMMIT_REQ_H
#define _STRANSPORT_BEARER_REALLOCATION_COMMIT_REQ_H

#include <SMessageHeader.h>
#include <TTransactionID.h>
#include <TNbccId.h>
#include <TCellId.h>


struct STransportBearerReallocationCommitReq
{
    MESSAGEHEADER(header)
    TTransactionID                 transactionId;
    TCellId                        cellId;
    TNbccId                        nbccId;
};

typedef struct STransportBearerReallocationCommitReq STransportBearerReallocationCommitReq;

#endif /* _STRANSPORT_BEARER_REALLOCATION_COMMIT_REQ_H */

/******************************************************************
* @struct STransportBearerReallocationCommitReq
* SW Block            : Ppc_Env
*
* Description         : The message is sent by Telecom SW to TUP CONMAN after successful transport 
*                       bearer reallocation preparation phase. It carries reallocation transaction id 
*                       which has to be committed. The transaction id is the same like used in the preparation phase.
*
* Reference           : ATM_CTRL_MCUS_IF_spec.doc, 23.0, sharenet-IMS
*
* Parameters  :
*
* @param    header            : NMAP header
* @param    transactionId     : Identifier of the reallocation transaction.
* @param    cellId            : Id of the cell
* @param    nbccId            : NodeB Communication Context Id
*
* Additional Information    :
* Definition Provided by    : TUP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
**********************************************************************/




