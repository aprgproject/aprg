/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Messages/STransportBearerUnregisterResponseMsg.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Olgierd Sobinski
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/
#ifndef _S_TRANSPORT_BEARER_UNREGISTER_RESPONSE_MSG_H
#define _S_TRANSPORT_BEARER_UNREGISTER_RESPONSE_MSG_H

#include <SMessageHeader.h>
#include <TTransactionID.h>
#include <EResponseCond.h>
#include <TCause.h>
#include <TNbccId.h>
#include <TCellId.h>


struct STransportBearerUnregisterResponseMsg
{
    MESSAGEHEADER(header)
    TTransactionID                     transactionId;
    EResponseCond                      response;
    TCause                             cause;
    TCellId                            cellId;
    TNbccId                            nbccId;
};

typedef struct STransportBearerUnregisterResponseMsg STransportBearerUnregisterResponseMsg;

#endif /* _S_TRANSPORT_BEARER_UNREGISTER_RESPONSE_MSG_H */

/******************************************************************
* @struct STransportBearerUnregisterResponseMsg
* SW Block            : Flexi Rel2 BTS / Ppc_Env
*
* Description : This message is used by Conman to respond to Telecom on
*                transport bearer unregistration message.
*
* Reference   : ATM_CTRL_MCUS_IF_spec.doc, 18.0, sharenet-IMS
*
* Parameters  :
*
* @param    header            : NMAP header
* @param    transactionId     : Transaction identifier
* @param    response          : Success/Failure indicator for requested operation
* @param    cause             : Cause value (present only if failed)
* @param    cellId            : Id of the cell
* @param    nbccId            : NodeB Communication Context Id
*
* Additional Information    :
* Definition Provided by    : TUP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
**********************************************************************/




