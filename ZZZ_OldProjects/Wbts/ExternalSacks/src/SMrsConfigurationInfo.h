/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SMrsConfigurationInfo.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        Kari Vakeva
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _SMRSCONFIGURATIONINFO_H
#define _SMRSCONFIGURATIONINFO_H

#include <EConnectionName.h>
#include <TTransportPathIdentifier.h>
#include <TTransportIdentifier.h>
#include <UAesa.h>
#include <EServiceCategory.h>
#include <TAtmCellRate.h>
#include <TCommunControlPortID.h>

typedef struct SMrsConfigurationInfo
{
    EConnectionName          connectionName;
    TTransportPathIdentifier ipAddress;
    TTransportIdentifier     udpPort;
    UAesa                    a2ea;
    TCommunControlPortID     controlPortId;
    EServiceCategory         vcType;
    TAtmCellRate             pcr;
    TAtmCellRate             scr;
} SMrsConfigurationInfo;

#endif /* _SMRSCONFIGURATIONINFO_H */

/**
*******************************************************************************
* @struct SMrsConfigurationInfo
*
* Description         : Flexi MRS Configuration information.
*
* Reference           : ATM CTRL MCUS IF SPEC, 5.1, PI
*
* @param connectionName : Connection name (CNBAP, DNBAP, AAL2S).
* @param ipAddress      : MRS IP address for the connection.
* @param udpPort        : MRS UDP port number for the connection.
* @param a2ea           : Optional MRS TLA (=A2EA) for the related iub connection (conditional: field connectionName = EConnectionName_AAL2S).
* @param controlPortId  : This section is conditional, field connectionName = EConnectionName_DNBAP:
*                         This attribute identifies the control port that uses the D-NBAP signalling.
*                         This attribute is not used for C-NBAP. It is fixed to "1" for D-NBAP.
* @param vcType         : This attribute identifies the type of the ATM virtual channel used as NBAP signalling bearer.
* @param pcr            : The following attributes tell the transport capacity of the ATM virtual channel in cells/second:
*                         This attribute is the peak cell rate of the ATM connection in cells per second.
* @param scr            : Further: This attribute is the sustainable cell rate of the ATM connection. In case of a CBR or UBR connection the scr is not present.
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : TUP / KVAKEVA
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/


