/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/ECarrierResourceInterfaceType.h $
* @version               $LastChangedRevision: 2688 $
* @date                  $LastChangedDate: 2017-03-06 17:02:40 +0800 (Mon, 06 Mar 2017) $
* @author                $Author: malba $
*
* Original author        Mark Alba
*
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _ECARRIERRESOURCEINTERFACETYPE_H
#define _ECARRIERRESOURCEINTERFACETYPE_H

#include <DFromTc_dsp.h>

typedef enum ECarrierResourceInterfaceType
{
    ECarrierResourceInterfaceType_Obsai = 0,
    ECarrierResourceInterfaceType_Cpri = 1,
    ECarrierResourceInterfaceType_Unknown = NO_VALUE_FOR_ENUMS
} ECarrierResourceInterfaceType;

#endif /* _ECARRIERRESOURCEINTERFACETYPE_H */

/**
*******************************************************************************
* @enum ECarrierResourceInterfaceType
*
* Description :  This enum indicates the interface type of the carrier resource
*
* Reference   : BTSOM Telecom IFS
*
* Parameters  :
*
* @param Obsai   : Defines that the interface type is OBSAI
* @param Cpri    : Defines that the interface type is CPRI
* @param Unknown : Defines that the interface type is unknown
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom / Mark Alba
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

