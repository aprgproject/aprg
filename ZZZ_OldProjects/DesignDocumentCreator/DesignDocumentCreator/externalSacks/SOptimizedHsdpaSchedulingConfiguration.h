/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SOptimizedHsdpaSchedulingConfiguration.h $
* @version               $LastChangedRevision: 2770 $
* @date                  $LastChangedDate: 2018-07-24 18:10:00 +0800 (Tue, 24 Jul 2018) $
* @author                $Author: echano $
*
* Original author        Andrea Echano
*
* Copyright 2018 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _SOPTIMIZED_HSDPA_SCHEDULING_CONFIGURATION_H
#define _SOPTIMIZED_HSDPA_SCHEDULING_CONFIGURATION_H

#include <EOptimizedHsdpaSchedulingType.h>

struct SOptimizedHsdpaSchedulingConfiguration
{
  EOptimizedHsdpaSchedulingType optimizedHsdpaSchedulingType;
};
typedef struct SOptimizedHsdpaSchedulingConfiguration SOptimizedHsdpaSchedulingConfiguration;

#endif /* _SOPTIMIZED_HSDPA_SCHEDULING_CONFIGURATION_H */

/**
*******************************************************************************
* @struct SOptimizedHsdpaSchedulingConfiguration
*
* Description : Optimized hsdpa scheduling configuration.
*
* Reference   : https://confluence.int.net.nokia.com/display/CpPta/CNI-31510+Control+the+enabling+of+RAN3269+by+introducing+a+commissioning+parameter
*
* Parameters  :
*
* @param optimizedHsdpaSchedulingType : Indicates the optimized hsdpa scheduling type
*
* Additional Information :
*
* Definition Provided by : TCOM, Andrea Echano
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

