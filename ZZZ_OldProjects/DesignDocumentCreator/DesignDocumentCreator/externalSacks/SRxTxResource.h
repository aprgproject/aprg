/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SRxTxResource.h $
* @version               $LastChangedRevision: 2716 $
* @date                  $LastChangedDate: 2017-12-19 15:59:02 +0800 (Tue, 19 Dec 2017) $
* @author                $Author: malba $
*
* Original author        Bartosz Ciesla
* @module                Control Plane WCDMA
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_RX_TX_RESOURCE_H
#define _S_RX_TX_RESOURCE_H

#include <SMessageAddress.h>
#include <TCarrierResourceId.h>
#include <ERadioResourceType.h>
#include <EAvailability.h>
#include <TLocalCellResId.h>
#include <EBoolean.h>
#include <glo_def.h>
#include <EUarfcnBand.h>
#include <ECarrierResourceInterfaceType.h>

struct SRxTxResource
{
    SMessageAddress                   resourceAddress;
    TCarrierResourceId                carrierResourceId;
    ERadioResourceType                radioResourceType;
    EAvailability                     availability;
    TLocalCellResId                   associatedLcrId;
    EBoolean                          isPrimaryTx;
    u32                               combinedRp3Address;
    EUarfcnBand                       uarfcnBand;
    i32                               maxRxLevel;
    ECarrierResourceInterfaceType     interfaceType;
    EBoolean                          isAntennaLineMonitoringEnabled;
};
typedef struct SRxTxResource SRxTxResource;

#endif /* _S_RX_TX_RESOURCE_H */

/**
*******************************************************************************
* @struct SRxTxResource
*
* Description         : Structure definition of Rx/Tx Resource
*
* Reference           : BTSOM - TCOM Interface Specification, v 49.0, ShareNet-IMS
*
* Parameters :
*
* @param resourceAddress                 : resource address
* @param carrierResourceId               : carrier resource id
* @param radioResourceType               : type of carrier (Rx or Tx)
* @param availability                    : status of the carrier resource
* @param associatedLcrId                 : associated LCR id
* @param isPrimaryTx                     : indicates if it is the primary TX resource
* @param combinedRp3Address              : node id (8 bits) + subnode id (5 bits) of the carrier resource on the RP3 bus
* @param uarfcnBand                      : UARFCN Band number
* @param maxRxLevel                      : maximum RX level
* @param interfaceType                   : interface type of the carrier resource
* @param isAntennaLineMonitoringEnabled  : indicates if RTWP reports from RX resource will be sent to OAM for antenna line monitoring (RP001749)
*
* Additional Information : none
*
* Definition Provided by : TCOM SW
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

