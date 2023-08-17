/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EProtocolType.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef EPROTOCOLTYPE_H
#define EPROTOCOLTYPE_H

typedef enum EProtocolType
{
    EProtocolType_WamWamIp       = 1,
    EProtocolType_WamWamApi      = 2,
    EProtocolType_WamAxuIp       = 3,    /* (Note: AXU IP Router will forward to RNC/NMS when needed!) */
    EProtocolType_WamRncNbap     = 4,
    EProtocolType_RncWspFpAal2   = 5,
    EProtocolType_RncWamAal2Sign = 6,
    EProtocolType_OamF4          = 7,
    EProtocolType_NmapGwUdp      = 8,
    EProtocolType_NmapGwUdpcp    = 9
} EProtocolType;

#endif /* EPROTOCOLTYPE_H */

/**
*******************************************************************************
* @enum EProtocolType
*
* Description  : Protocol type in ATM connections
*
* Reference   : Atm-Ctrl MCUs if spec doc, 6.0, PI
*
* Parameters  :
*
* @param EProtocolType_WamWamIp :
* @param EProtocolType_WamWamApi :
* @param EProtocolType_WamAxuIp :
* @param EProtocolType_WamRncNbap :
* @param EProtocolType_RncWspFpAal2 :
* @param EProtocolType_RncWamAal2Sign :
* @param EProtocolType_OamF4 :
* @param EProtocolType_NmapGwUdp :
* @param EProtocolType_NmapGwUdpcp :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : TUP / KVAKEVA
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



