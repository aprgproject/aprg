/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SFlexiConnectionInfo.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        Kari Vakeva
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _SFLEXICONNECTIONINFO_H
#define _SFLEXICONNECTIONINFO_H

#include <SMrsConfigurationInfo.h>
#include <TTransportIdentifier.h>
#include <SMessageAddress.h>
#include <SProtocolDescriptor.h>

typedef struct SFlexiConnectionInfo
{
     SMrsConfigurationInfo      mrsConfigurationInfo;
     TTransportIdentifier       fcmUdpPort;
     SMessageAddress            node1;
     SMessageAddress            node2;
     SProtocolDescriptor        protocol;
} SFlexiConnectionInfo;

#endif /* _SFLEXICONNECTIONINFO_H */

/**
*******************************************************************************
* @struct SFlexiConnectionInfo
*
* Description         : Flexi Connection information.
*
* Reference           : ATM CTRL MCUS IF SPEC, 5.1, PI
*
* Parameters:
*
* @param mrsConfigurationInfo : MRS (FTM) commissioning information for this connection
* @param fcmUdpPort : The UDP port of the FCM for this IP connection between TUP-MRS
* @param node1 : NMAP address of the source of the p2p connection (Peer).
* @param node2 : NMAP address of the sink of the p2p connection (Local).
* @param protocol : Protocol selection.
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : TUP / KVAKEVA
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/


