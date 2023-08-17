/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EHsdpaSchedulerId.h $
* @version               $LastChangedRevision: 2581 $
* @date                  $LastChangedDate: 2016-05-11 18:45:31 +0800 (Wed, 11 May 2016) $
* @author                $Author: joseplop $
* 
* Original author        Bartosz Ciesla
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _E_HSDPA_SCHEDULER_ID_H
#define _E_HSDPA_SCHEDULER_ID_H

typedef enum EHsdpaSchedulerId
{
    EHsdpaSchedulerId_Rel3_Lcg1S1 = 0,
    EHsdpaSchedulerId_Rel3_Lcg1S2 = 1,
    EHsdpaSchedulerId_Rel3_Lcg2S1 = 2,
    EHsdpaSchedulerId_Rel3_Lcg2S2 = 3,
    EHsdpaSchedulerId_Rel3_Lcg3S1 = 4,
    EHsdpaSchedulerId_Rel3_Lcg3S2 = 5,
    EHsdpaSchedulerId_Rel3_Lcg4S1 = 6,
    EHsdpaSchedulerId_Rel3_Lcg4S2 = 7,
    EHsdpaSchedulerId_Rel2_S1     = 8,
    EHsdpaSchedulerId_Rel2_S2     = 9,
    EHsdpaSchedulerId_Rel2_S3     = 10,
    EHsdpaSchedulerId_Rel2_S4     = 11,
    EHsdpaSchedulerId_Rel4_Lcg1S1 = 12,
    EHsdpaSchedulerId_Rel4_Lcg1S2 = 13,
    EHsdpaSchedulerId_Rel4_Lcg1S3 = 14,
    EHsdpaSchedulerId_Rel4_Lcg2S1 = 15,
    EHsdpaSchedulerId_Rel4_Lcg2S2 = 16,
    EHsdpaSchedulerId_Rel4_Lcg2S3 = 17,
    EHsdpaSchedulerId_Rel4_Lcg3S1 = 18,
    EHsdpaSchedulerId_Rel4_Lcg3S2 = 19,
    EHsdpaSchedulerId_Rel4_Lcg3S3 = 20,
    EHsdpaSchedulerId_Rel4_Lcg4S1 = 21,
    EHsdpaSchedulerId_Rel4_Lcg4S2 = 22,
    EHsdpaSchedulerId_Rel4_Lcg4S3 = 23
} EHsdpaSchedulerId;

#endif /* _E_HSDPA_SCHEDULER_ID_H */

/**
*******************************************************************************
* @enum EHsdpaSchedulerId
*
* Description         : Enumerated values which define ids for HSDPA schedulers in BTS.
*
* Reference           : BTSOM Telecom IFS, 37.0, ShareNet-IMS
*
* Parameters :
*
* @param Rel3_Lcg1S1 : 1st HSDPA Scheduler for LCG 1 in Flexi Rel3
* @param Rel3_Lcg1S2 : 2nd HSDPA Scheduler for LCG 1 in Flexi Rel3
* @param Rel3_Lcg2S1 : 1st HSDPA Scheduler for LCG 2 in Flexi Rel3
* @param Rel3_Lcg2S2 : 2nd HSDPA Scheduler for LCG 2 in Flexi Rel3
* @param Rel3_Lcg3S1 : 1st HSDPA Scheduler for LCG 3 in Flexi Rel3
* @param Rel3_Lcg3S2 : 2nd HSDPA Scheduler for LCG 3 in Flexi Rel3
* @param Rel3_Lcg4S1 : 1st HSDPA Scheduler for LCG 4 in Flexi Rel3
* @param Rel3_Lcg4S2 : 2nd HSDPA Scheduler for LCG 4 in Flexi Rel3
* @param Rel2_S1     : 1st HSDPA Scheduler for Flexi Rel2
* @param Rel2_S2     : 2nd HSDPA Scheduler for Flexi Rel2
* @param Rel2_S3     : 3rd HSDPA Scheduler for Flexi Rel2
* @param Rel2_S4     : 4th HSDPA Scheduler for Flexi Rel2
* @param Rel4_Lcg1S1 : 1st HSDPA Scheduler for LCG 1 in Flexi Rel4
* @param Rel4_Lcg1S2 : 2nd HSDPA Scheduler for LCG 1 in Flexi Rel4
* @param Rel4_Lcg1S3 : 3rd HSDPA Scheduler for LCG 1 in Flexi Rel4
* @param Rel4_Lcg2S1 : 1st HSDPA Scheduler for LCG 2 in Flexi Rel4
* @param Rel4_Lcg2S2 : 2nd HSDPA Scheduler for LCG 2 in Flexi Rel4
* @param Rel4_Lcg2S3 : 3rd HSDPA Scheduler for LCG 2 in Flexi Rel4
* @param Rel4_Lcg3S1 : 1st HSDPA Scheduler for LCG 3 in Flexi Rel4
* @param Rel4_Lcg3S2 : 2nd HSDPA Scheduler for LCG 3 in Flexi Rel4
* @param Rel4_Lcg3S3 : 3rd HSDPA Scheduler for LCG 3 in Flexi Rel4
* @param Rel4_Lcg4S1 : 1st HSDPA Scheduler for LCG 4 in Flexi Rel4
* @param Rel4_Lcg4S2 : 2nd HSDPA Scheduler for LCG 4 in Flexi Rel4
* @param Rel4_Lcg4S3 : 3rd HSDPA Scheduler for LCG 4 in Flexi Rel4
*
* Additional Information :
*
* Definition Provided by : Telecom
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

