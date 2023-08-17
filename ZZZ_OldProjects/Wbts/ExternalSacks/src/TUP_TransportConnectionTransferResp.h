/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Messages/TUP_TransportConnectionTransferResp.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _TUP_TRANSPORT_CONNECTION_TRANSFER_RESP_H
#define _TUP_TRANSPORT_CONNECTION_TRANSFER_RESP_H

#include <SMessageHeader.h>
#include <TTransportIdentifier.h>
#include <EStatus.h>
#include <ETransportCause.h>
#include <TAaSysComSicad.h>

struct TUP_TransportConnectionTransferResp
{
    MESSAGEHEADER(msgHeader)
    TAaSysComSicad            fpSicAddress;
    TTransportIdentifier      localPort;
    EStatus                   status;
    ETransportCause           transportCause;
};

typedef struct TUP_TransportConnectionTransferResp TUP_TransportConnectionTransferResp;

#endif /* _TUP_TRANSPORT_CONNECTION_TRANSFER_RESP_H */

/**
*******************************************************************************
* @struct TUP_TransportConnectionTransferResp
* Description         : Transport Connection Release response message.
*
* Reference           : DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param msgHeader      : header of the message
* @param fpSicAddress   : SIC address of Execution Unit (task) on which the FP is located.
* @param localPort      : Port number of a local transport endpoint.
* @param status         : Status codes used in transport procedures.
* @param transportCause : Cause codes used in transport procedures.
*
* Additional Information : 
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

