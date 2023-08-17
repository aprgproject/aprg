/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SLcrEirpControlParameters.h $
* @version               $LastChangedRevision: 2890 $
* @date                  $LastChangedDate: 2019-07-19 07:06:00 +0800 (Fri, 19 Jul 2019) $
* @author                $Author: iyee $
*
* Original author        Iangelo Yee
*
* Copyright 2019 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _SLCR_EIRP_CONTROL_PARAMETERS_H
#define _SLCR_EIRP_CONTROL_PARAMETERS_H

#include <EBoolean.h>
#include <TPowerLevel.h>
#include <TMeasurementPeriod.h>

struct SLcrEirpControlParameters
{
    EBoolean           isEirpControlEnabled;
    TPowerLevel        eirpReduction;
    TMeasurementPeriod eirpAveragingWindow;
};
typedef struct SLcrEirpControlParameters SLcrEirpControlParameters;

#endif /* _SLCR_EIRP_CONTROL_PARAMETERS_H */

/**
*******************************************************************************
* @struct SLcrEirpControlParameters
*
* Description : EIRP control parameters of an LCR.
*
* Reference   : https://confluence.int.net.nokia.com/display/CpPta/SR002318+BTS+RF+exposure+mitigation+for+3G+RAT
*
* Parameters  :
*
* @param isEirpControlEnabled : Indicates if LCR has SR002318 EIRP control enabled (based on NIDD actEirpControl).
*
* @param eirpReduction        : The EIRP reduction for an LCR based on upperLimitForPaMaxOutputPower (or NIDD maxCarrierPower).
*                               Range: 0...6; Step: 0.1; Unit: dB; Precision: Value is already multiplied by 10 for accuracy of 0.1
*
* @param eirpAveragingWindow  : Sliding window for the time averaging to be used for eirp control.
*                               Range: 1...60; Step: 1; Unit: minute
*
* Additional Information :
*
* Definition Provided by : TCOM, Iangelo Yee
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

