/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Messages/STransportBearerRegisterMsg.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Olgierd Sobinski
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/
#ifndef _S_TRANSPORT_BEARER_REGISTER_MSG_H
#define _S_TRANSPORT_BEARER_REGISTER_MSG_H

#include <SMessageHeader.h>
#include <TTransactionID.h>
#include <TNumberOfPresence.h>
#include <STransportBearerLocationData.h>
#include <TNbccId.h>
#include <TCellId.h>

struct STransportBearerRegisterMsg
{
    MESSAGEHEADER(msgHeader)
    TTransactionID                     transactionId;
    TCellId                            cellId;
    TNbccId                            nbccId;
    TNumberOfPresence                  numConnections;
    STransportBearerLocationData       tbLocationData[1];
};
typedef struct STransportBearerRegisterMsg STransportBearerRegisterMsg;

#endif /* _S_TRANSPORT_BEARER_REGISTER_MSG_H */

/**
****************************************************************
* @struct STransportBearerRegisterMsg
* SW Block            : Flexi Rel2 BTS / Ppc_Env
*
* Description : This message is used by Telecom SW for requesting TUP
*                to register a number of transport bearer connections
*                between TRSW and DSP which are going to be established
*                by TRSW.
*
* Reference   : ATM_CTRL_MCUS_IF_spec.doc, 18.0, sharenet-IMS
*
* Parameters  :
*
* @param msgHeader         : NMAP header
* @param transactionId     : Transaction identifier
* @param cellId            : Id of the cell
* @param nbccId            : NodeB Communication Context Id
* @param numConnections    : Number of transport bearer connections to register
* @param tbLocationData    : Dynamic part - frame protocol location to transport bearer mapping data
*
* Additional Information    :
* Definition Provided by    : TUP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
**********************************************************************/

