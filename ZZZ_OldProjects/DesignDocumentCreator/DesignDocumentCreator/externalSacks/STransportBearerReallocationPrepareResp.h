/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Messages/STransportBearerReallocationPrepareResp.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Olgierd Sobinski
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/
#ifndef _STRANSPORT_BEARER_REALLOCATION_PREPARE_RESP_H
#define _STRANSPORT_BEARER_REALLOCATION_PREPARE_RESP_H

#include <SMessageHeader.h>
#include <TTransactionID.h>
#include <EResponseCond.h>
#include <TCause.h>
#include <TNbccId.h>
#include <TCellId.h>


struct STransportBearerReallocationPrepareResp
{
    MESSAGEHEADER(header)
    TTransactionID                     transactionId;
    EResponseCond                      response;
    TCause                             cause;
    TCellId                            cellId;
    TNbccId                            nbccId;
};

typedef struct STransportBearerReallocationPrepareResp STransportBearerReallocationPrepareResp;

#endif /* _STRANSPORT_BEARER_REALLOCATION_PREPARE_RESP_H */

/******************************************************************
* @struct STransportBearerReallocationPrepareResp
* SW Block            : Ppc_Env
*
* Description         : The response message for TC_TRANSPORT_BEARER_REALLOCATION_PREPARE_RESP_MSG .
*
* Reference           : ATM_CTRL_MCUS_IF_spec.doc ver. 23.0, sharenet-IMS
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





