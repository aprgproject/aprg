/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/STupConfigurationInfo.h $
* @version               $LastChangedRevision: 2809 $
* @date                  $LastChangedDate: 2018-10-04 11:44:19 +0800 (Thu, 04 Oct 2018) $
* @author                $Author: echano $
*
* Original author        Kari Vakeva
*
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _S_TUP_CONFIGURATION_INFO_H
#define _S_TUP_CONFIGURATION_INFO_H

#include <TAaSysComSicad.h>
#include <TLogicalWamId.h>
#include <TTransportIdentifier.h>
#include <TTransportLayerAddress.h>
#include <TTransportPathIdentifier.h>

typedef struct STupConfigurationInfo
{
     TTransportPathIdentifier   ipAddress;
     TTransportIdentifier       minSctpPortIub;
     TTransportLayerAddress     tupAddress;
     TLogicalWamId              wamNumber;
     TAaSysComSicad             tupcAalManSicad;
     TAaSysComSicad             trswSicad;
} STupConfigurationInfo;

#endif /* _S_TUP_CONFIGURATION_INFO_H */

/**
*******************************************************************************
* @struct STupConfigurationInfo
*
* Description         : TUP Configuration information.
*
* Reference           : ATM CTRL MCUS IF SPEC, 13.0, PI
*
* Parameters :
*
* @param ipAddress        : The IP address of the FCM.
* @param minSctpPortIub   : Minimum SCTP port number. (optional: iub/IP)
* @param tupIpAddress     : The address of TUP for SCTP in NSAP format. Refer to RFC-4548 for NSAP format. (Optional: iub/IP)
* @param wamNumber        : WAM number.
* @param tupcAalManSicad  : The address TUPC instance near TRSW instance.
* @param trswSicad        : Contains IPCS TRSW NID in SICAD format but CPID is set to 0x0.
*
* Additional Information :
*
* Definition Provided by : TUP / KVAKEVA
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/


