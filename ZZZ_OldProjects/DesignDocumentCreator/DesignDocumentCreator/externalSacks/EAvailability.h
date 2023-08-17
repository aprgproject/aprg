/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EAvailability.h $
* @version               $LastChangedRevision: 2732 $
* @date                  $LastChangedDate: 2018-03-12 16:46:52 +0800 (Mon, 12 Mar 2018) $
* @author                $Author: rancastr $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef EAVAILABILITY_H
#define EAVAILABILITY_H

typedef enum EAvailability
{
    EAvailability_NotAvailable     = 0,
    EAvailability_Available        = 1,
    EAvailability_BasebandDisabled = 2,
    EAvailability_Hibernated       = 3
} EAvailability;  /* typedef for unit availability state*/

#endif /* EAVAILABILITY_H */

/**
*******************************************************************************
* @enum EAvailability
*
* Description : Enum definition for unit availability state
*
* Reference   : BTSOM - TCOM Interface Specification, v 10.0, PI
*
* Parameters :
*
* @param NotAvailable     : unit is not available
* @param Available        : unit is available
* @param BasebandDisabled : Used only with WAM/FCM.
*                           Unit is available but the whole baseband
*                           capacity under the unit is disabled.
*                           (e.g. WSM failure, all WSPs out of use)
* @param Hibernated       : Used only for FSMr3 FSPs. Unit is temporarily not available
*                           due to low demand for baseband resources.
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

