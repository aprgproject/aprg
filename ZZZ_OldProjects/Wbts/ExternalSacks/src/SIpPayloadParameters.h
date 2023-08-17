/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SIpPayloadParameters.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        Mikko Tikkakoski
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _S_IP_PAYLOAD_PARAMETERS_H
#define _S_IP_PAYLOAD_PARAMETERS_H

#include <TIpPayloadLayerBitRate.h>
#include <TIpPayloadSize.h>
#include <SVlanIdInfo.h>

struct SIpPayloadParameters
{
    TIpPayloadLayerBitRate    maxBitRateInIpPayloadLayer;
    TIpPayloadLayerBitRate    averageBitRateInIpPayloadLayer;
    TIpPayloadSize            maxSizeOfIpPayloadInOneIpPacket;
    TIpPayloadSize            averageSizeOfIpPayloadInOneIpPacket;
    SVlanIdInfo               vlanIdInfo;
};
typedef struct SIpPayloadParameters SIpPayloadParameters;

#endif /* _S_IP_PAYLOAD_PARAMETERS_H */

/**
*******************************************************************************
* @struct SIpPayloadParameters
*
* Description         : Z.5.1aFA  IP payload parameters
*
* Reference           : Annex Z
*
* Parameters :
*
* @param maxBitRateInIpPayloadLayer           : Maximum bit rate in IP payload layer
* @param averageBitRateInIpPayloadLayer       : Average bit rate in IP payload layer
* @param maxSizeOfIpPayloadInOneIpPacket      : Maximum size of IP payload in one IP packet
* @param averageSizeOfIpPayloadInOneIpPacket  : Average size of IP payload in one IP packet
* @param vlanIdInfo                           : VLAN Identifier Information Element
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

