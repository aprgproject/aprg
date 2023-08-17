/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Definitions/STransportBearerModificationData.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Lukasz Haracz
*
* Copyright 2013 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_TRANSPORT_BEARER_MODIFICATION_DATA_H
#define _S_TRANSPORT_BEARER_MODIFICATION_DATA_H

#include <TTransportBearerId.h>
#include <SIpPayloadParameters.h>

struct STransportBearerModificationData
{
    TTransportBearerId      transportBearerId;
    SIpPayloadParameters    ulParameters;
};
typedef struct STransportBearerModificationData STransportBearerModificationData;

#endif /* _S_TRANSPORT_BEARER_MODIFICATION_DATA_H */

/**
*******************************************************************************
* @struct STransportBearerModificationData
*
* Description         : Telecom internal message
*
* Reference           : WCDMA BTS TCOM SW
*
* @param transportBearerId      :  Transport bearer id
* @param ulParameters           :  Ip Payload parameters
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

