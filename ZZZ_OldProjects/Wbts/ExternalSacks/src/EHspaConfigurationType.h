/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EHspaConfigurationType.h $
* @version               $LastChangedRevision: 2581 $
* @date                  $LastChangedDate: 2016-05-11 18:45:31 +0800 (Wed, 11 May 2016) $
* @author                $Author: joseplop $
* 
* Original author        Bartosz Ciesla
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _E_HSPA_CONFIGURATION_TYPE_H
#define _E_HSPA_CONFIGURATION_TYPE_H

typedef enum EHspaConfigurationType
{
    EHspaConfigurationType_Normal     = 0,
    EHspaConfigurationType_Small      = 1,
    EHspaConfigurationType_R99        = 2,
    EHspaConfigurationType_Large      = 3,
    EHspaConfigurationType_BasicRel4  = 4
} EHspaConfigurationType;

#endif /* _E_HSPA_CONFIGURATION_TYPE_H */

/**
*******************************************************************************
* @enum EHspaConfigurationType
*
* Description         : Enumerated values which define type of HSDPA in Flexi BTS Rel3.
*
* Reference           : BTSOM Telecom IFS, 37.0, ShareNet-IMS
*
* Parameters :
*
* @param Normal : Normal HSPA configuration (default)
* @param Small  : Small HSPA configuration
* @param R99    : R99 HSPA configuration
* @param Large  : Large HSPA configuration
* @param BasicRel4 : HSPA configuration in Flexi Rel4
*
* Additional Information :
*
* Definition Provided by : Telecom
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

