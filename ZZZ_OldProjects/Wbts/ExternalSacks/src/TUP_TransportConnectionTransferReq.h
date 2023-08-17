/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Messages/TUP_TransportConnectionTransferReq.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _TUP_TRANSPORT_CONNECTION_TRANSFER_REQ_H
#define _TUP_TRANSPORT_CONNECTION_TRANSFER_REQ_H

#include <SMessageHeader.h>
#include <TTransportIdentifier.h>
#include <STransportEndPoint.h>
#include <TPresenceIndicator.h>
#include <TFpId.h>
#include <TAaSysComSicad.h>

struct TUP_TransportConnectionTransferReq
{
    MESSAGEHEADER(msgHeader)
    TAaSysComSicad            fpSicAddress;
    TFpId                     fpId;
    TTransportIdentifier      localPort;
    STransportEndPoint        remoteAddress;
    TPresenceIndicator        dataDuplicationAddressPresent;
    STransportEndPoint        dataDuplicationAddress;
};

typedef struct TUP_TransportConnectionTransferReq TUP_TransportConnectionTransferReq;

#endif /* _TUP_TRANSPORT_CONNECTION_TRANSFER_REQ_H */

/**
*******************************************************************************
* @struct TUP_TransportConnectionTransferReq
* Description         : Transport Connection Transfer request message.
*
* Reference           : DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param msgHeader     : header of the message
* @param fpSicAddress  : SIC address of Execution Unit (task) on which the FP is located.
* @param fpId          : The unique ID that defines the FP instance inside a Faraday core.
*                        Own FP Id is allocated for every transport bearer.
* @param localPort     : Port number of a local transport endpoint.
* @param remoteAddress : Address on which the new FP instance will send the UL data.
* @param dataDuplicationAddressPresent : If set on TRUE then subsequent Data Duplicaton 
*                                        Address of the old FP is provided and the data 
*                                        duplication should occur during connection transfer.
* @param dataDuplicationAddress : Address of old (source) FP  to which the new FP will
*                                 duplicate DL data until CFN expires
*
* Additional Information : 
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/


