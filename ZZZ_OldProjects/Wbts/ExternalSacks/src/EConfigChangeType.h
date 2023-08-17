/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EConfigChangeType.h $
* @version               $LastChangedRevision: 2732 $
* @date                  $LastChangedDate: 2018-03-12 16:46:52 +0800 (Mon, 12 Mar 2018) $
* @author                $Author: rancastr $
*
* Original author        Bartosz Ciesla
*
* Copyright 2010 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_CONFIG_CHANGE_TYPE_H
#define _E_CONFIG_CHANGE_TYPE_H

typedef enum EConfigChangeType
{
    EConfigChangeType_Standard                = 0,
    EConfigChangeType_DspSoftReset            = 1,
    EConfigChangeType_CardBlock               = 2,
    EConfigChangeType_BasebandReset           = 3,
    EConfigChangeType_EsmHotRemoval           = 4,
    EConfigChangeType_DspResetFailure         = 5,
    EConfigChangeType_FspReset                = 6,
    EConfigChangeType_BasebandResetWithMcu    = 7,
    EConfigChangeType_FspResetWithoutMcu      = 8,
    EConfigChangeType_FspShutdown             = 9,
    EConfigChangeType_SecondaryCoreHotRemoval = 10,
    EConfigChangeType_SecondaryCoreReset      = 11,
    EConfigChangeType_FspHibernation          = 12
} EConfigChangeType;

#endif /* _E_CONFIG_CHANGE_TYPE_H */

/**
*******************************************************************************
* @enum EConfigChangeType
*
* Description : Indicates type of HW_CONFIGURATION_CHANGE_MSG
*
* Reference   : BTSOM - TCOM Interface Specification (BTSOM CPLANE IFS), v 4.0, ShareNet-IMS
*
* Parameters :
*
* @param Standard                : Standard config change type
* @param DspSoftReset            : DSP soft reset case
* @param CardBlock               : FSP card block case
* @param BasebandReset           : Full BB reset case (without FSP reset)
* @param EsmHotRemoval           : ESM hot removal case
* @param DspResetFailure         : DSP reset case (FSMr3 HW-specific)
* @param FspReset                : FSP reset case (FSMr3 HW-specific)
* @param BasebandResetWithMcu    : BB reset case with FSP reset
* @param FspResetWithoutMcu      : FSP reset case (FSMr3 HW-specific) in which all DSP in FSP are reset but MCU is not
* @param FspShutdown             : FSP shutdown case (FSMr3 HW-specific)
* @param SecondaryCoreHotRemoval : Secondary Core hot removal case (AirScale HW-specific)
* @param SecondaryCoreReset      : Secondary Core reset case (AirScale HW-specific)
* @param FspHibernation          : FSP hibernation case (FSMr3 HW-specific)
*
* Additional Information :
*
* Definition Provided by : TCOM / Bartosz Ciesla
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

