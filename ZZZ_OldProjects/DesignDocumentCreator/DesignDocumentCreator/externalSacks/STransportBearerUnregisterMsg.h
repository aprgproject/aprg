/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Messages/STransportBearerUnregisterMsg.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Olgierd Sobinski
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_TRANSPORT_BEARER_UNREGISTER_MSG_H
#define _S_TRANSPORT_BEARER_UNREGISTER_MSG_H

#include <SMessageHeader.h>
#include <TTransactionID.h>
#include <TNumberOfPresence.h>
#include <EBoolean.h>
#include <TTransportBearerId.h>
#include <TNbccId.h>
#include <TCellId.h>
#include <EUnregisterType.h>

struct STransportBearerUnregisterMsg
{
    MESSAGEHEADER(header)
    TTransactionID                  transactionId;
    EBoolean                        immediateRelease;
    EBoolean                        skipDspConnectionRelease;
    EUnregisterType                 unregisterType;
    TCellId                         cellId;
    TNbccId                         nbccId;
    TNumberOfPresence               numConnections;
    TTransportBearerId              transportBearerIds[1];
};

typedef struct STransportBearerUnregisterMsg STransportBearerUnregisterMsg;

#endif /* _S_TRANSPORT_BEARER_UNREGISTER_MSG_H */

/******************************************************************
* @struct STransportBearerUnregisterMsg
* SW Block            : Flexi Rel2 BTS / Ppc_Env
*
* Description : This message is used by Telecom SW to inform TUP that a number of setup 
*               (or registered) transport bearer connections between TRSW and DSP are 
*               going to be released (or unregistered). Unregistration request can apply 
*               to a number of separate connections under a single transaction identified 
*               by transaction ID. If immediate transport connection release is TRUE 
*               transport bearer connection is released locally, without waiting TRSW to 
*               release the transport bearer.
*
* Reference   : ATM_CTRL_MCUS_IF_spec.doc, 34.0, sharenet-IMS
*
* Parameters  :
*
* @param    header                  : NMAP header
* @param    transactionId           : Transaction identifier
* @param    immediateRelease        : Immediate transport connection release indicator
* @param    skipDspConnectionRelease: Field valid only when immediatedRelease set. 
*                                     If set then the transport connection release message (TUP_TRANSPORT_CONNECTION_RELEASE_REQ_MSG)
*                                     will be not sent to DSPs containing unregistered connections (CN4397, WBTS_RECOV_65851)
* @param    unregisterType          : type of unregister.
* @param    cellId                  : Id of the cell
* @param    nbccId                  : NodeB Communication Context Id
* @param    numConnections          : Number of transport bearer connections to register
* @param    transportBearerIds      : Dynamic part - a sequence of transport bearer Id's to be unregistered.
*
* Additional Information    :
* Definition Provided by    : TUP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
**********************************************************************/




