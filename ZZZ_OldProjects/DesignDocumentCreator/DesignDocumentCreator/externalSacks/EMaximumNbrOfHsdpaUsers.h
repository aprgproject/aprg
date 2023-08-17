/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EMaximumNbrOfHsdpaUsers.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _EMAXIMUMNBROFHSDPAUSERS_H
#define _EMAXIMUMNBROFHSDPAUSERS_H

typedef enum EMaximumNbrOfHsdpaUsers
{
    EMaximumNbrOfHsdpaUsers_16PerCell        = 0,
    EMaximumNbrOfHsdpaUsers_16PerBts         = 1,
    EMaximumNbrOfHsdpaUsers_EfficientBB      = 2,
    EMaximumNbrOfHsdpaUsers_4CellOptimizedBB = 3,
    EMaximumNbrOfHsdpaUsers_FullBB           = 4,
    EMaximumNbrOfHsdpaUsers_NotPresent       = 0xffff /* Optional IE not present */
} EMaximumNbrOfHsdpaUsers;

#endif /* _EMAXIMUMNBROFHSDPAUSERS_H */

/**
*******************************************************************************
* @enum EMaximumNbrOfHsdpaUsers
*
* Description : Maximum Number of HSDPA Users shall be used to notify
*               the CRNC about maximum number of HSDPA users that can
*               be handled in the Node B or in the cell.
*
* Reference   : Annex Z ver. 2.4 for 3GPP TS25.433 NBAP (normative):
*               Z.5.1C	Maximum Number of HSDPA Users
*
* Parameters :
*
* @param EMaximumNbrOfHsdpaUsers_16PerCell :
* @param EMaximumNbrOfHsdpaUsers_16PerBts :
* @param EMaximumNbrOfHsdpaUsers_EfficientBB :
* @param EMaximumNbrOfHsdpaUsers_4CellOptimizedBB :
* @param EMaximumNbrOfHsdpaUsers_FullBB :
* @param EMaximumNbrOfHsdpaUsers_NotPresent :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom / Andrus Lehtmets
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/


