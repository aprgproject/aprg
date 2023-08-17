/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Messages/STransportBearerReallocationCleanupReq.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Olgierd Sobinski
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/
#ifndef _STRANSPORT_BEARER_REALLOCATION_CLEANUP_REQ_H
#define _STRANSPORT_BEARER_REALLOCATION_CLEANUP_REQ_H

#include <SMessageHeader.h>
#include <TTransactionID.h>
#include <TNbccId.h>
#include <TCellId.h>


struct STransportBearerReallocationCleanupReq
{
    MESSAGEHEADER(header)
    TTransactionID                 transactionId;
    TCellId                        cellId;
    TNbccId                        nbccId;
};

typedef struct STransportBearerReallocationCleanupReq STransportBearerReallocationCleanupReq;

#endif /* _STRANSPORT_BEARER_REALLOCATION_CLEANUP_REQ_H */


/******************************************************************
* @struct STransportBearerReallocationCleanupReq
* SW Block            : Ppc_Env
*
* Description         : The message is sent by Telecom SW to TUP CONMAN after the reallocation commit phase 
*                       has been successfully completed (the activation CFN elapsed and all affected FP instances sent positive acknowledgments).
*                       The message is sent in order to allow CONMAN to release all DL ports related to the old FP locations. 
*                       It is sent in a moment when no old FP instance uses these ports, so the ports can be safely released 
*                       and then can be immediately assigned for another transport bearer if needed.
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




