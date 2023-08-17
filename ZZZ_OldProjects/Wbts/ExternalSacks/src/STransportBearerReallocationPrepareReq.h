/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Messages/STransportBearerReallocationPrepareReq.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Olgierd Sobinski
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/
#ifndef _STRANSPORT_BEARER_REALLOCATION_PREPARE_REQ_H
#define _STRANSPORT_BEARER_REALLOCATION_PREPARE_REQ_H

#include <SMessageHeader.h>
#include <TTransactionID.h>
#include <TNumberOfPresence.h>
#include <STransportBearerReallocationData.h>
#include <TNbccId.h>
#include <TCellId.h>


struct STransportBearerReallocationPrepareReq
{
    MESSAGEHEADER(header)
    TTransactionID                   transactionId;
    TCellId                          cellId;
    TNbccId                          nbccId;
    TNumberOfPresence                numConnections;
    STransportBearerReallocationData transportBearerReallocationData[1];
};

typedef struct STransportBearerReallocationPrepareReq STransportBearerReallocationPrepareReq;

#endif /* _STRANSPORT_BEARER_REALLOCATION_PREPARE_REQ_H */

/******************************************************************
* @struct STransportBearerReallocationPrepareReq
* SW Block            : Ppc_Env
*
* Description         : The message is sent by Telecom SW to TUP CONMAN in order to start up 
*                      the transport bearer reallocation process related to DCH, HSDPA, HSUPA user transfer.
*
* Reference           : ATM_CTRL_MCUS_IF_spec.doc, 23.0, sharenet-IMS
*
* Parameters  :
*  @param    header              : NMAP header
*  @param    transactionId       : Transaction ID passed by TELECOM for transport bearer in TC_TRANSPORT_BEARER_REGISTER_MSG 
*  @param    cellId              : Id of the cell
*  @param    nbccId              : NodeB Communication Context Id
*  @param    transportBearerReallocationData
*                                : Dynamic array of data related to transport bearer reallocations.
*
* Additional Information    :
* Definition Provided by    : TUP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
**********************************************************************/




