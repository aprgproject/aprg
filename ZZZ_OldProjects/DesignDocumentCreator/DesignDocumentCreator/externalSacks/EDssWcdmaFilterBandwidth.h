/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EDssWcdmaFilterBandwidth.h $
* @version               $LastChangedRevision: 2882 $
* @date                  $LastChangedDate: 2019-06-10 18:05:39 +0800 (Mon, 10 Jun 2019) $
* @author                $Author: malba $
*
* Original author        Mark Alba
*
* Copyright 2019 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _EDSS_WCDMA_FILTER_BANDWIDTH_H
#define _EDSS_WCDMA_FILTER_BANDWIDTH_H

typedef enum EDssWcdmaFilterBandwidth
{
    EDssWcdmaFilterBandwidth_0_KHz     = 0,
    EDssWcdmaFilterBandwidth_600_KHz   = 1,
    EDssWcdmaFilterBandwidth_1200_KHz  = 2
} EDssWcdmaFilterBandwidth;

#endif /* _EDSS_WCDMA_FILTER_BANDWIDTH_H */

/**
*******************************************************************************
* @enum EDssWcdmaFilterBandwidth
*
* Description : Enumerated type to identify DSS WCDMA filter bandwidth
*
* Reference   : OAM CPlane Interface Specification
*
* Parameters :
*
* @param 0_KHz           :   Indicates that the DSS WCDMA filter bandwidth is 0 KHz.
*
* @param 600_KHz         :   Indicates that the DSS WCDMA filter bandwidth is 600 KHz.
*
* @param 1200_KHz        :   Indicates that the DSS WCDMA filter bandwidth is 1200 KHz.
*
* Additional Information :
*
* Definition Provided by : WCDMA OAM TCOM DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

