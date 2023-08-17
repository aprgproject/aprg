/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EHibernationMode.h $
* @version               $LastChangedRevision: 2732 $
* @date                  $LastChangedDate: 2018-03-12 16:46:52 +0800 (Mon, 12 Mar 2018) $
* @author                $Author: rancastr $
*
* Original author        Ranizel Castro
*
* Copyright 2015 Nokia. All rights reserved.
******************************************************************************/

#ifndef _EHIBERNATION_MODE_H
#define _EHIBERNATION_MODE_H

typedef enum EHibernationMode
{
  EHibernationMode_Disabled          = 0,
  EHibernationMode_EnabledAlways     = 1,
  EHibernationMode_EnabledOnSchedule = 2
} EHibernationMode;

#endif /* _EHIBERNATION_MODE_H */

/**
*******************************************************************************
* @enum EHibernationMode
*
* Description : Indicates the hibernation mode.
*
* Reference   : BTSOM - TCOM IFS, < BTSOM - TCOM IFS version >
*
* Parameters  :
*
* @param Disabled          : Hibernation is disabled.
*
* @param EnabledAlways     : Hibernation is enabled always.
*
* @param EnabledOnSchedule : Hibernation is enabled on specific times and specific days only.
*
* Additional Information :
*
* Definition Provided by   : TCOM, Ranizel Castro
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

