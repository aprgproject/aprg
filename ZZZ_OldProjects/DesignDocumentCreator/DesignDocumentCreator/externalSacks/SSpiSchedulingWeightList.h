/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SSpiSchedulingWeightList.h $
* @version               $LastChangedRevision: 2529 $
* @date                  $LastChangedDate: 2015-12-21 14:57:29 +0800 (Mon, 21 Dec 2015) $
* @author                $Author: jfranco $
*
* Original author        jfranco
*
* Copyright 2015 Nokia. All rights reserved.
******************************************************************************/

#ifndef _SSPI_SCHEDULING_WEIGHT_LIST_H
#define _SSPI_SCHEDULING_WEIGHT_LIST_H

#include <glo_def.h>
#include <DOpenIUBCommonDefs.h>

struct SSpiSchedulingWeightList
{
    u32 spiSchedulingWeight[MAX_NUM_OF_HSDPA_QOS_SPI_CLASS];
};
typedef struct SSpiSchedulingWeightList SSpiSchedulingWeightList;

#endif /* _SSPI_SCHEDULING_WEIGHT_LIST_H */

/**
*******************************************************************************
* @struct SSpiSchedulingWeightList
*
* Description : SPI Scheduling Weight List
*
* Reference   : IS_BTSOM_CPLANE_IFS 5.1.1.83
*
* Parameters  :
*
* @param spiSchedulingWeight    : SPI Scheduling weight
*
* Additional Information :
*
* Definition Provided by : TCOM
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

