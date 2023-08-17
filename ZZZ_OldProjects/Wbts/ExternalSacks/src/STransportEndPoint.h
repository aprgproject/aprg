/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/STransportEndPoint.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        KWIKSTRO
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _STRANSPORTENDPOINT_H
#define _STRANSPORTENDPOINT_H

#include <glo_def.h>
#include <TTransportPathIdentifier.h>
#include <TTransportIdentifier.h>

typedef struct STransportEndPoint
{
    TTransportPathIdentifier    path;
    TTransportIdentifier        id;
} STransportEndPoint;

#endif /* _STRANSPORTENDPOINT_H */

/**
*******************************************************************************
* @struct STransportEndPoint
*
* Description         : Type definition for transport identifier. Transport
*                       identifier is in Nora Connection Idendifier (CID).
*                       In Flexi it is UDP-port.
*
* Reference           : ATM CTRL MCUS interface spec
*
* Parameters :
*
* @param path  : binary Ipv4 address (Flexi) or ATM (SAR)channel Id
* @param id :    UDP port (Flexi) or AAL2 CID (Nora)
*
* Additional Information : 
*
* Definition Provided by : TUP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/


