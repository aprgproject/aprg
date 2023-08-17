/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EMcuSwDeployment.h $
* @version               $LastChangedRevision: 2432 $
* @date                  $LastChangedDate: 2015-06-30 17:25:09 +0800 (Tue, 30 Jun 2015) $
* @author                $Author: zborkows $
*
* Original author        Zbigniew Borkowski
*
* Copyright 2014 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_MCU_SW_DEPLOYMENT_H
#define _E_MCU_SW_DEPLOYMENT_H

typedef enum EMcuSwDeployment
{
    EMcuSwDeployment_Tcom       = 0,
    EMcuSwDeployment_NonWcdmaSw = 1
} EMcuSwDeployment;

#endif /* _E_MCU_SW_DEPLOYMENT_H */

/**
*******************************************************************************
* @enum EMcuSwDeployment
*
* Description         : Defines if TCOM SW is running on given MCU
*
* Reference           : BTSOM - TCOM Interface Specification
*
* @param EMcuSwDeployment_Tcom  : Indicates that TCOM instance is running
*                                 on given MCU
* @param EMcuSwDeployment_NonWcdmaSw : Indicates that non WCMDA RAT software is
*                                      running on that MCU
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Michal Budziak
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/


