/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Messages/STransportBearerSetupMsg.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Olgierd Sobinski
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/
#ifndef _STRANSPORT_BEARER_SETUP_MSG_H
#define _STRANSPORT_BEARER_SETUP_MSG_H

#include <SMessageHeader.h>
#include <TTransportBearerId.h>
#include <TTransactionID.h>
#include <TNbccId.h>
#include <TCellId.h>

struct STransportBearerSetupMsg
{
    MESSAGEHEADER(header)
    TTransportBearerId       transportBearerId;
    TTransactionID           transactionId;
    TCellId                  cellId;
    TNbccId                  nbccId;
};

typedef struct STransportBearerSetupMsg STransportBearerSetupMsg;

#endif /* _STRANSPORT_BEARER_SETUP_MSG_H */

/******************************************************************
* @struct STransportBearerSetupMsg
* SW Block            : Ppc_Env
*
* Description         : This message is used by TUP to inform Telecom SW about 
*                        established transport bearer connection between TRSW and DSP.
*
* Reference           : ATM_CTRL_MCUS_IF_spec.doc, 26.0, sharenet-IMS
*
* Parameters          :
*  @param    header             : NMAP header
*  @param    transportBearerId  : Transport bearer identifier.
*  @param    transactionId      : Transaction ID passed by TELECOM for transport bearer in TC_TRANSPORT_BEARER_REGISTER_MSG 
*  @param    cellId             : Id of the cell
*  @param    nbccId             : NodeB Communication Context Id
*
* Additional Information    :
* Definition Provided by    : TUP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
**********************************************************************/



