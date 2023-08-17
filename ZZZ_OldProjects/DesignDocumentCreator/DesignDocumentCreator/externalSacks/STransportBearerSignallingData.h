/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Definitions/STransportBearerSignallingData.h $
* @version               $LastChangedRevision: 4882 $
* @date                  $LastChangedDate: 2016-04-11 17:53:44 +0800 (Mon, 11 Apr 2016) $
* @author                $Author: sazon $
*
* Original author        Olgierd Sobinski
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/
#ifndef _S_TRANSPORT_BEARER_SIGNALLING_DATA_H
#define _S_TRANSPORT_BEARER_SIGNALLING_DATA_H

#include <EBearerType.h>
#include <TTransportBearerId.h>
#include <STransportEndPoint.h>
#include <STransportEndPointVer2.h>
#include <glo_def.h>

struct STransportBearerSignallingData
{
    EBearerType                  bearerType;
    u32                          transportId;
    TTransportBearerId           transportBearerId;
    STransportEndPointVer2       btsEndPoint;
    STransportEndPoint           ftmIpta;
    STransportEndPoint           dspIpta;
};
typedef struct STransportBearerSignallingData STransportBearerSignallingData;

#endif /* _S_TRANSPORT_BEARER_SIGNALLING_DATA_H */

/**
****************************************************************
* @struct STransportBearerSignallingData
* SW Block            : Flexi Rel2 BTS / Ppc_Env
*
* Description : A helper structure for STransportBearerRegisterResponseMsg
*
* Reference   : ATM_CTRL_MCUS_IF_spec.doc, 26.0, sharenet-IMS
*
* Parameters  :
*
* @param bearerType          : Binding id of registered connection.
* @param transportId         : Transport bearer identifier.
* @param transportBearerId   : Binding id of registered connection.
* @param btsEndPoint         : BTS end point in NSAP format (Refer to RFC-4548)
* @param ftmIpta             : Binding id of registered connection.
* @param dspIpta             : Transport bearer identifier.
*
* Additional Information    : <type additional information if needed>
* Definition Provided by    : TUP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
**********************************************************************/

