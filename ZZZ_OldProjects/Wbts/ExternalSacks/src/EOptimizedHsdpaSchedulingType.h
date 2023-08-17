/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EOptimizedHsdpaSchedulingType.h $
* @version               $LastChangedRevision: 2770 $
* @date                  $LastChangedDate: 2018-07-24 18:10:00 +0800 (Tue, 24 Jul 2018) $
* @author                $Author: echano $
*
* Original author        Andrea Echano
*
* Copyright 2018 Nokia. All rights reserved.
******************************************************************************/

#ifndef _EOPTIMIZED_HSDPA_SCHEDULING_TYPE_H
#define _EOPTIMIZED_HSDPA_SCHEDULING_TYPE_H

typedef enum EOptimizedHsdpaSchedulingType
{
  EOptimizedHsdpaSchedulingType_None = 0,
  EOptimizedHsdpaSchedulingType_IncreaseNumberOfUesPerTti = 1,
  EOptimizedHsdpaSchedulingType_IncreaseNumberOfUesPerTtiAndScheduleBannedUsers = 2
} EOptimizedHsdpaSchedulingType;

#endif /* _EOPTIMIZED_HSDPA_SCHEDULING_TYPE_H */

/**
*******************************************************************************
* @enum EOptimizedHsdpaSchedulingType
*
* Description : Indicates the optimized hsdpa scheduling type.
*
* Reference   : https://confluence.int.net.nokia.com/display/CpPta/CNI-31510+Control+the+enabling+of+RAN3269+by+introducing+a+commissioning+parameter
*
* Parameters  :
*
* @param None                                            : RAN3269 Optimized Hsdpa Scheduler is disabled.
*
* @param IncreaseNumberOfUesPerTti                       : Increase number of UEs subfeature is enabled.
*
* @param IncreaseNumberOfUesPerTtiAndScheduleBannedUsers : Increase number of UEs and scheduled banned users subfeatures enabled.
*
* Additional Information :
*
* Definition Provided by   : TCOM, Andrea Echano
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

