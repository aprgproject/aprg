/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EConfigChangeAddAction.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Bartosz Ciesla
* @module                WCDMA Control Plane
* @owner                 Bartosz Ciesla
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_CONFIG_CHANGE_ADD_ACTION_H
#define _E_CONFIG_CHANGE_ADD_ACTION_H

typedef enum EConfigChangeAddAction
{
    EConfigChangeAddAction_NoAction         = 0,
    EConfigChangeAddAction_TxCarrierDisable = 1
} EConfigChangeAddAction;

#endif /* _E_CONFIG_CHANGE_ADD_ACTION_H */

/**
*******************************************************************************
* @enum EConfigChangeAddAction
*
* Description         : Flag which indicates additional action during HwConfigChange
*
* Reference           : BTSOM TCOM IFS, version 42.0, ShareNet-IMS
*
* Parameters :
*
* @param EConfigChangeAddAction_NoAction         : No action needed
* @param EConfigChangeAddAction_TxCarrierDisable : Carrier deactivation
*
* Additional Information : 79915ESPE04
*
* Definition Provided by : WCDMA Control Plane
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

