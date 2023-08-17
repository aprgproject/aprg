/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EAirScaleCoreRole.h $
* @version               $LastChangedRevision: 2700 $
* @date                  $LastChangedDate: 2017-07-11 11:16:06 +0800 (Tue, 11 Jul 2017) $
* @author                $Author: psakurai $
*
* Original author        Paul Sakurai
*
* Copyright 2017 Nokia. All rights reserved.
******************************************************************************/

#ifndef _EAIR_SCALE_CORE_ROLE_H
#define _EAIR_SCALE_CORE_ROLE_H

enum EAirScaleCoreRole
{
    EAirScaleCoreRole_Unknown   = 0,
    EAirScaleCoreRole_Primary   = 1,
    EAirScaleCoreRole_Secondary = 2
};
typedef enum EAirScaleCoreRole EAirScaleCoreRole;

#endif /* _EAIR_SCALE_CORE_ROLE_H */

/**
*******************************************************************************
* @enum EAirScaleCoreRole
*
* Description :  Enumeration for supported roles of a Core in AirScale BTS.
*
* Reference   :  http://nok.it/CpPtaRP001621
*
* Parameters :
* @param Unknown   : This is the default value that is used only in other HW releases,
*                    such as FSMr2, FSMr3, FlexiLite, FlexiZonePico, etc.
* @param Primary   : This is assigned to the Core in AirScale BTS where the active SOAM (also TRSW) resides.
* @param Secondary : This is assigned to the other cores that doesn't satisfy the condition for Primary role.
*
* Additional Information :
*
* Definition Provided by : WCDMA CP (TCOM)
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

