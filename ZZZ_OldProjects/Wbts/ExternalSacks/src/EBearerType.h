/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Definitions/EBearerType.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Lukasz Haracz
*
* Copyright 2013 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_BEARER_TYPE_H
#define _E_BEARER_TYPE_H

typedef enum EBearerType
{
  EBearerType_ATM                = 0,
  EBearerType_IP                 = 1,
  EBearerType_SecTBbyTBId        = 2,
  EBearerType_SecTBbyBindingId   = 3
} EBearerType;

#endif /* _E_BEARER_TYPE_H */

/**
*******************************************************************************
* @enum EBearerType
*
* Description         : Used in Telecom internal messages
*
* Reference           : WCDMA BTS TCOM SW
*
* @param EBearerType_ATM  : atm TB only
* @param EBearerType_IP  : ip iub TB
* @param EBearerType_SecTBbyTBId  : activation of secondary TB
* @param EBearerType_SecTBbyBindingId  : addtion of secondary TB during reconfiguration
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

