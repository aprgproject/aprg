/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SVlanIdInfo.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        Lukasz Jarzmik
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _S_VLAN_ID_INFO_H
#define _S_VLAN_ID_INFO_H

#include <glo_def.h>
#include <EIEPresentType.h>
#include <TVlanId.h>

struct SVlanIdInfo
{
  EIEPresentType    iePresent;
  TVlanId           vlanId;
};
typedef struct SVlanIdInfo SVlanIdInfo;

#endif /* _S_VLAN_ID_INFO_H */

/**
*******************************************************************************
* @struct SVlanIdInfo
*
* Description         : Z.5.1aFA	VLAN Identifier Information Elements
*
* Reference           : Annex Z
*
* @param iePresent                            : VLAN Identifier Information Element
* @param vlanId                               : VLAN Identifier Information Element
*
* Additional Information : 
*
* Definition Provided by : Telecom
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/


