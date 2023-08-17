/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SDssWcdmaLteCommissioningParametersForLoadMonitoring.h $
* @version               $LastChangedRevision: 2882 $
* @date                  $LastChangedDate: 2019-06-10 18:05:39 +0800 (Mon, 10 Jun 2019) $
* @author                $Author: malba $
*
* Original author        Mark Alba
*
* Copyright 2019 Nokia. All rights reserved.
******************************************************************************/

#ifndef _SDSS_WCDMA_LTE_COMMISSIONING_PARAMETERS_FOR_LOAD_MONITORING_H
#define _SDSS_WCDMA_LTE_COMMISSIONING_PARAMETERS_FOR_LOAD_MONITORING_H

#include <TLoadUnit.h>
#include <TPercentage.h>

struct SDssWcdmaLteCommissioningParametersForLoadMonitoring
{
    TLoadUnit               mediumLoadThreshold;
    TLoadUnit               highLoadThreshold;
    TPercentage             dchLoadFactor;
    TPercentage             hsdpaAndHsfachLoadFactor;
};
typedef struct SDssWcdmaLteCommissioningParametersForLoadMonitoring SDssWcdmaLteCommissioningParametersForLoadMonitoring;

#endif /* _SDSS_WCDMA_LTE_COMMISSIONING_PARAMETERS_FOR_LOAD_MONITORING_H */

/**
*******************************************************************************
* @struct SDssWcdmaLteCommissioningParametersForLoadMonitoring
*
* Description : This structure contains parameters needed for load monitoring in Dynamic Spectrum Sharing (DSS).
*
* Reference   : OAM CPlane Interface Specification
*
* Parameters  :
*
* @param mediumLoadThreshold          : This indicates whether WCDMA load is medium and also implicitly defines low load.
*                                       If the calculated load is below the mediumLoadThreshold, the load is considered as low.
*                                       If the calculated load is equal or above the mediumLoadThreshold and below the highLoadThreshold, the load is considered as medium.
*                                       If the calculated load is equal or above the highLoadThreshold, the load is considered as high.
*
* @param highLoadThreshold            : This indicates whether WCDMA load is high.
*                                       If the calculated load is below the mediumLoadThreshold, the load is considered as low.
*                                       If the calculated load is equal or above the mediumLoadThreshold and below the highLoadThreshold, the load is considered as medium.
*                                       If the calculated load is equal or above the highLoadThreshold, the load is considered as high.
*
* @param dchLoadFactor                : This is the percentage of the factor or weight for DCH in WCDMA load calculation in DSS (Range: 0-100, Step: 1).
*
* @param hsdpaAndHsfachLoadFactor     : This is the percentage of the factor or weight for HSDPA/HSFACH in WCDMA load calculation in DSS (Range: 0-100, Step: 1).
*
* Additional Information :
*
* Definition Provided by : TCOM, Mark Alba
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

