/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EUeTracingState.h $
* @version               $LastChangedRevision: 4822 $
* @date                  $LastChangedDate: 2016-01-27 22:49:33 +0800 (Wed, 27 Jan 2016) $
* @author                $Author: shubchen $
*
* Original author        Chen Shubao
*
* Copyright 2016 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _EUE_TRACING_STATE_H
#define _EUE_TRACING_STATE_H

#include <DFromTc_dsp.h>

typedef enum EUeTracingState
{
    EUeTracingState_Enable     = 0,
    EUeTracingState_Disable    = 1,
    EUeTracingState_NoValue    = NO_VALUE_FOR_ENUMS
} EUeTracingState;

#endif /* _EUE_TRACING_STATE_H */

/**
*******************************************************************************
* @enum EUeTracingState
*
* Description : Enum type to identify the UE tracing state in RAN2861.
*
* Reference   : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                                    DSP SW - MCU SW INTERFACE SPECIFICATION
*                                    Location: Sharenet
*
* Parameters :
*
* @param Enable   :   To enable UE tracing.
*
* @param Disable   :  To disable UE tracing.
*
* @param NoValue   : UE tracing state is not changed.
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : TCOM, DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

