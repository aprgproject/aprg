/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Definitions/STransportBearerLocationData.h $
* @version               $LastChangedRevision: 4882 $
* @date                  $LastChangedDate: 2016-04-11 17:53:44 +0800 (Mon, 11 Apr 2016) $
* @author                $Author: sazon $
*
* Original author        Olgierd Sobinski
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/
#ifndef _S_TRANSPORT_BEARER_LOCATION_DATA_H
#define _S_TRANSPORT_BEARER_LOCATION_DATA_H

#include <EBearerType.h>
#include <SFpLocation.h>
#include <SIpPayloadParameters.h>
#include <STransportEndPointVer2.h>
#include <TDsField.h>
#include <glo_def.h>

struct STransportBearerLocationData
{
    EBearerType                 bearerType;
    u32                         transportId;
    SFpLocation                 fpLocation;
    u32                         messageTypeNumber;
    SIpPayloadParameters        ulParameters;
    SIpPayloadParameters        oldUlParameters;
    STransportEndPointVer2      rncEndPoint;
    TDsField                    dsField;
};
typedef struct STransportBearerLocationData STransportBearerLocationData;

#endif /* _S_TRANSPORT_BEARER_LOCATION_DATA_H */

/**
****************************************************************
* @struct STransportBearerLocationData
* SW Block            : Flexi Rel2 BTS / Ppc_Env
*
* Description         : A helper structure for STransportBearerRegisterMsg.
*                       Describes a single transport bearer parameters.
*
* Reference           : ATM_CTRL_MCUS_IF_spec.doc, 35.0, sharenet-IMS
*
* Parameters  :
* @param bearerType         : Transport bearer type.
* @param transportId        : Transport Id.
* @param fpLocation         : Frame protocol instance location data.
* @param messageTypeNumber  : specifies the message type number associated with given connection that will be communicated to TRSW when connection is being established.(remark: the message type number is be used by TRSW as the message identifier when sending DL FP frames via Syscom to DSP on FSM rel 3 HW.)
* @param ulParameters       : Ip payload parameters
* @param oldUlParameters    : Old Ip payload parameters
* @param rncEndPoint        : RNC end point in NSAP format (Refer to RFC-4548)
* @param dsField            : QpS DS Field
*
* Additional Information :
* Definition Provided by : TUP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
**********************************************************************/

