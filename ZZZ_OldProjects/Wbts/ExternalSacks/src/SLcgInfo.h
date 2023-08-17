/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SLcgInfo.h $
* @version               $LastChangedRevision: 2882 $
* @date                  $LastChangedDate: 2019-06-10 18:05:39 +0800 (Mon, 10 Jun 2019) $
* @author                $Author: malba $
*
* Original author        Iangelo Yee
*
* Copyright 2015 Nokia. All rights reserved.
******************************************************************************/
#ifndef _S_LCG_INFO_H
#define _S_LCG_INFO_H

#include <EAirScaleCoreRole.h>
#include <EHspaConfigurationType.h>
#include <glo_def.h>
#include <SDssWcdmaLteCommissioningParametersForLoadMonitoring.h>
#include <TCaGroupId.h>
#include <TLocalCellGroupId.h>
#include <TNumberOfItems.h>
#include <TPercentage.h>

struct SLcgInfo
{
    TLocalCellGroupId                                       localCellGroupId;
    TCaGroupId                                              caGroupId;
    TPercentage                                             dedicatedBB;
    TPercentage                                             dedicatedHsdpaAllocation;
    TPercentage                                             dedicatedHsupaAllocation;
    EHspaConfigurationType                                  hspaConfigurationType;
    TBoolean                                                hspaSharing;
    i32                                                     lcgAccessToBB;
    TNumberOfItems                                          numOfHsupaResourceStepsRes;
    TNumberOfItems                                          minNumOfHsRachResourceStepsRes;
    TNumberOfItems                                          maxNumOfHsRachResourceStepsRes;
    TBoolean                                                isNbicEnabled;
    EAirScaleCoreRole                                       assignedAirScaleCore;
    SDssWcdmaLteCommissioningParametersForLoadMonitoring    dssWcdmaLteCommissioningParametersForLoadMonitoring;
};
typedef struct SLcgInfo SLcgInfo;

#endif /* _S_LCG_INFO_H */

/**
*******************************************************************************
* @struct SLcgInfo
*
* Description : This structure contains parameters for each LCG
*
* Reference   : OAM CPlane Interface Specification
*
* Parameters  :
*
* @param localCellGroupId                                        : The Local Cell Group Id
*
* @param caGroupId                                               : The Carrier Aggregation Group Id
*
* @param dedicatedBB                                             : The percentage for LCG's dedicated BB capacity
*
* @param dedicatedHsdpaAllocation                                : The percentage for LCG's access dedicated HSDPA capacity
*
* @param dedicatedHsupaAllocation                                : The percentage for LCG's access dedicated HSUPA capacity
*
* @param hspaConfigurationType                                   : The HSPA configuration for flexi rel3 / flexi rel 4 of the LCG
*
* @param hspaSharing                                             : The HSPA sharing of the LCG (for HSDPA and HSUPA) (true or false, default false)
*
* @param lcgAccessToBB                                           : The percentage for LCG's access to BB capacity,
*                                                                  The value -1 indicates sector BB Pooling
* @param numOfHsupaResourceStepsRes                              : The number of HSUPA resource steps
*                                                                  reserved for HSUPA users
*                                                                  (range 0..48, default 0)
*
* @param minNumOfHsRachResourceStepsRes                          : The minimum number of HSUPA resource steps for HS-RACH users (range 0..8, step 1, default 0)
*
* @param maxNumOfHsRachResourceStepsRes                          : The maximum number of HSUPA resource steps for HS-RACH users (range 1..8, step 1, default 1)
*
* @param isNbicEnabled                                           : This parameter indicates if NBIC is enabled for the LCG.
*
* @param assignedAirScaleCore                                    : This indicates the AirScale Core where the RF module/s of the LCG's cells is/are connected to.
*
* @param dssWcdmaLteCommissioningParametersForLoadMonitoring     : This contains parameters needed for load monitoring in WCDMA+LTE Dynamic Spectrum Sharing (DSS).
*
* Additional Information :
*
* Definition Provided by : TCOM
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

