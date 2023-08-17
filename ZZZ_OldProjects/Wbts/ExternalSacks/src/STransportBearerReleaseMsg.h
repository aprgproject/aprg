/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Messages/STransportBearerReleaseMsg.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Olgierd Sobinski
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/
#ifndef _STRANSPORT_BEARER_RELEASE_MSG_H
#define _STRANSPORT_BEARER_RELEASE_MSG_H

#include <SMessageHeader.h>
#include <TTransactionID.h>
#include <TNumberOfPresence.h>
#include <STransportBearerReleaseData.h>
#include <TNbccId.h>
#include <TCellId.h>

struct STransportBearerReleaseMsg
{
    MESSAGEHEADER(header)
    TTransactionID                     requestId;
    TCellId                            cellId;
    TNbccId                            nbccId;
    TNumberOfPresence                  numConnections;
    STransportBearerReleaseData        transportBearers[1];
};

typedef struct STransportBearerReleaseMsg STransportBearerReleaseMsg;

#endif /* _STRANSPORT_BEARER_RELEASE_MSG_H */

/******************************************************************
* @struct STransportBearerReleaseMsg
* SW Block            : Ppc_Env
*
* Description : This message is used by TUP to inform Telecom SW about 
*                released transport bearer connection(s) between TRSW and DSP/hsTUP
*
* Reference   : ATM_CTRL_MCUS_IF_spec.doc, ver. 26.0, sharenet-IMS
*
* Parameters  :
*
* @param    header            : NMAP header
* @param    requestId         : Internal TUP request ID to match TC_TRANSPORT_BEARER_RELEASE_RESP
* @param    cellId            : Id of the cell
* @param    nbccId            : NodeB Communication Context Id
* @param    numConnections    : Number of transport bearer connections to release
* @param    transportBearers: Dynamic data: list of transport bearer identification tuples: {signalling association ID's, transactionId }
*
* Additional Information    :
* Definition Provided by    : TUP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
**********************************************************************/




