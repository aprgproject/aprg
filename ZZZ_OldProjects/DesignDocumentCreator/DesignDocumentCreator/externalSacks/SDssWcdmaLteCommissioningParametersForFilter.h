/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SDssWcdmaLteCommissioningParametersForFilter.h $
* @version               $LastChangedRevision: 2882 $
* @date                  $LastChangedDate: 2019-06-10 18:05:39 +0800 (Mon, 10 Jun 2019) $
* @author                $Author: malba $
*
* Original author        Mark Alba
*
* Copyright 2019 Nokia. All rights reserved.
******************************************************************************/

#ifndef _SDSS_WCDMA_LTE_COMMISSIONING_PARAMETERS_FOR_FILTER_H
#define _SDSS_WCDMA_LTE_COMMISSIONING_PARAMETERS_FOR_FILTER_H

#include <EDssFilterMode.h>
#include <EDssWcdmaFilterBandwidth.h>

struct SDssWcdmaLteCommissioningParametersForFilter
{
    EDssFilterMode                       dssFilterMode;
    EDssWcdmaFilterBandwidth             staticFilterBandwidth;
};
typedef struct SDssWcdmaLteCommissioningParametersForFilter SDssWcdmaLteCommissioningParametersForFilter;

#endif /* _SDSS_WCDMA_LTE_COMMISSIONING_PARAMETERS_FOR_FILTER_H */

/**
*******************************************************************************
* @struct SDssWcdmaLteCommissioningParametersForFilter
*
* Description : This structure contains all LCR parameters needed for WCDMA+LTE Dynamic Spectrum Sharing (DSS).
*
* Reference   : OAM CPlane Interface Specification
*
* Parameters  :
*
* @param dssFilterMode                       : Shared spectrum filter mode (can be static or dynamic)
*
* @param staticFilterBandwidth               : Filter bandwidth in static filter mode
*
* Additional Information :
*
* Definition Provided by : TCOM, Mark Alba
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

