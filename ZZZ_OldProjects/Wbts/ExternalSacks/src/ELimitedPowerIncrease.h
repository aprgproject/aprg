/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/ELimitedPowerIncrease.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _ELIMITEDPOWERINCREASE_H
#define _ELIMITEDPOWERINCREASE_H

typedef enum ELimitedPowerIncrease
{
    ELimitedPowerIncrease_Disabled,
    ELimitedPowerIncrease_Enabled
} ELimitedPowerIncrease;

#endif /* _ELIMITEDPOWERINCREASE_H */

/**
*******************************************************************************
* @enum ELimitedPowerIncrease
*
* Description : The parameter is used for a more efficient use of the inner
*               loop DL power control for non real time data.
*               If the limited power increase is used, the BTS shall use
*               the limited power increase algorithm as specified in TS 25.214,
*               Chapter 5.2
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* @param ELimitedPowerIncrease_Disabled :
* @param ELimitedPowerIncrease_Enabled :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



