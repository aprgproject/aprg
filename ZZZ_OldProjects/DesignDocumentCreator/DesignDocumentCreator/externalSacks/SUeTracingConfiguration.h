/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SUeTracingConfiguration.h $
* @version               $LastChangedRevision: 2545 $
* @date                  $LastChangedDate: 2016-02-04 12:38:02 +0800 (Thu, 04 Feb 2016) $
* @author                $Author: malba $
*
* Original author        <Mark Alba>
*
* Copyright 2016 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _SUETRACINGCONFIGURATION_H
#define _SUETRACINGCONFIGURATION_H

#include <IfAaSysComGw.h>
#include <TTransportIdentifier.h>

struct SUeTracingConfiguration
{
  char                     dataCollectorIpAddress[AASYSCOM_GW_IP_ADDRESS_MAX_STR_LEN];
  TTransportIdentifier     dataCollectorPortNumber;
  u32                      commissionedTraceTypes;
};
typedef struct SUeTracingConfiguration SUeTracingConfiguration;

#endif /* _SUETRACINGCONFIGURATION_H */

/**
*******************************************************************************
* @struct SUeTracingConfiguration
*
* Parameters :
*
* @param dataCollectorIpAddress  : Data collector IP Address. This field must always end with a null terminating character. If strlen returns zero, then UE tracing is disabled. Otherwise, UE tracing is considered as enabled.
*
* @param dataCollectorPortNumber : Data collector Port Number
*
* @param commissionedTraceTypes  : Each bit represents a trace type. This contains values for ECommissionedTraceType.
*
* Description : Structure for UE tracing configuration
*
* Additional Information : RAN2861
*
* Reference :
*
* Definition Provided by : Mark Alba
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

