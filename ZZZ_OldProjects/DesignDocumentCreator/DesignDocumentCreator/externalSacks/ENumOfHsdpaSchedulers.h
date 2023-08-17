/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/ENumOfHsdpaSchedulers.h $
* @version               $LastChangedRevision: 2581 $
* @date                  $LastChangedDate: 2016-05-11 18:45:31 +0800 (Wed, 11 May 2016) $
* @author                $Author: joseplop $
* 
* Original author        Bartosz Ciesla
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _E_NUM_OF_HDSPA_SCHEDULERS_H
#define _E_NUM_OF_HDSPA_SCHEDULERS_H

typedef enum ENumOfHsdpaSchedulers
{
    ENumOfHsdpaSchedulers_0 = 0,
    ENumOfHsdpaSchedulers_1 = 1,
    ENumOfHsdpaSchedulers_2 = 2,
    ENumOfHsdpaSchedulers_3 = 3,
    ENumOfHsdpaSchedulers_4 = 4,
    ENumOfHsdpaSchedulers_5 = 5,
    ENumOfHsdpaSchedulers_6 = 6,
    ENumOfHsdpaSchedulers_7 = 7,
    ENumOfHsdpaSchedulers_8 = 8,
    ENumOfHsdpaSchedulers_9 = 9,
    ENumOfHsdpaSchedulers_10 = 10,
    ENumOfHsdpaSchedulers_11 = 11,
    ENumOfHsdpaSchedulers_12 = 12
} ENumOfHsdpaSchedulers;

#endif /* _E_NUM_OF_HDSPA_SCHEDULERS_H */

/**
*******************************************************************************
* @enum ENumOfHsdpaSchedulers
*
* Description         : Enumerated values which indicate amount of HSDPA Schedulers in BTS.
*
* Reference           : BTSOM Telecom IFS, 37.0, ShareNet-IMS
*
* Parameters :
*
* @param 0 : No schedulers
* @param 1 : One (1) scheduler
* @param 2 : Two (2) schedulers
* @param 3 : Three (3) schedulers
* @param 4 : Four (4) schedulers
* @param 5 : Five (5) schedulers
* @param 6 : Six (6) schedulers
* @param 7 : Seven (7) schedulers
* @param 8 : Eight (8) schedulers
* @param 9 : Nine (9) schedulers
* @param 10 : Ten (10) schedulers
* @param 11 : Eleven (11) schedulers
* @param 12 : Twelve (12) schedulers
*
* Additional Information :
*
* Definition Provided by : Telecom
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

