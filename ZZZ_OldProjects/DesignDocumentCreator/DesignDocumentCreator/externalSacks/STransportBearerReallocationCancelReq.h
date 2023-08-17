/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Messages/STransportBearerReallocationCancelReq.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Olgierd Sobinski
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/
#ifndef _STRANSPORT_BEARER_REALLOCATION_CANCEL_REQ_H
#define _STRANSPORT_BEARER_REALLOCATION_CANCEL_REQ_H

#include <SMessageHeader.h>
#include <TTransactionID.h>
#include <TNbccId.h>
#include <TCellId.h>


struct STransportBearerReallocationCancelReq
{
    MESSAGEHEADER(header)
    TTransactionID                 transactionId;
    TCellId                        cellId;
    TNbccId                        nbccId;
};

typedef struct STransportBearerReallocationCancelReq STransportBearerReallocationCancelReq;

#endif /* _STRANSPORT_BEARER_REALLOCATION_CANCEL_REQ_H */


/******************************************************************
* @struct STransportBearerReallocationCancelReq
* SW Block            : Ppc_Env
*
* Description         : The message is sent by Telecom SW to TUP CONMAN after unsuccessful preparation phase of user transfer or
*                       unsuccessful transport bearer transfer during user reconfiguration procedure. 
*                       The result is sending transport bearer release messages to all affected new FP instances 
*                       and releasing all DL ports allocated for new FP instances in CONMAN. Also all transaction related data are removed in CONMAN.
*
* Reference           : ATM_CTRL_MCUS_IF_spec.doc, 23.0, sharenet-IMS
*
* Parameters          :
*  @param    header             : NMAP header
*  @param    transactionId      : Identifier of the reallocation transaction.
*  @param    cellId             : Id of the cell
*  @param    nbccId             : NodeB Communication Context Id
*
* Additional Information    :
* Definition Provided by    : TUP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
**********************************************************************/



