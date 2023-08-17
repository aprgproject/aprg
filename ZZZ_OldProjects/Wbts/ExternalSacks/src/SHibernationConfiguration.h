/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SHibernationConfiguration.h $
* @version               $LastChangedRevision: 2732 $
* @date                  $LastChangedDate: 2018-03-12 16:46:52 +0800 (Mon, 12 Mar 2018) $
* @author                $Author: rancastr $
*
* Original author        Ranizel Castro
*
* Copyright 2010 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _SHIBERNATION_CONFIGURATION_H
#define _SHIBERNATION_CONFIGURATION_H

#include <EHibernationMode.h>
#include <IfAaSysTime_Defs.h>
#include <TSubunits.h>

struct SHibernationConfiguration
{
  EHibernationMode   hibernationMode;
  TAaMinute          filteringTime;
  TSubunits          hibernationThreshold;
  TSubunits          powerOnThreshold;
};
typedef struct SHibernationConfiguration SHibernationConfiguration;

#endif /* _SHIBERNATION_CONFIGURATION_H */

/**
*******************************************************************************
* @struct SHibernationConfiguration
*
* Description : Hibernation configuration.
*
* Reference   : BTSOM - TCOM IFS, < BTSOM - TCOM IFS version >
*
* Parameters  :
*
* @param hibernationMode       : Hibernation mode.
*
* @param filteringTime         : Time limit in minutes that FSP is below hibernation threshold before hibernating the FSP.
*
* @param hibernationThreshold  : The threshold for hibernation measured in subunits (Range: 2 - 36, Step: 0.25).
*
* @param powerOnThreshold      : The threshold for power-on measured in subunits (Range: 1 - 36, Step: 0.25).
*
* Additional Information :
*
* Definition Provided by : TCOM, Ranizel Castro
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

