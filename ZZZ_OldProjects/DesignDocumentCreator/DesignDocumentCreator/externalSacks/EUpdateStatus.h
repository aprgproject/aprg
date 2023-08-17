/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EUpdateStatus.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _EUPDATESTATUS_H
#define _EUPDATESTATUS_H

typedef enum EUpdateStatus
{
    EUpdateStatus_Add           = 0,
    EUpdateStatus_Delete        = 1,
    EUpdateStatus_Reconfigured  = 2,
    EUpdateStatus_Unchanged     = 3
} EUpdateStatus;

#endif /* _EUPDATESTATUS_H */

/**
*******************************************************************************
* @enum EUpdateStatus
*
* Description : Update status selection
*
* Reference   : Telecom SW internal type definition for feature Open IUB
*               (Xena WN2.1)
*
* Parameters  :
*
* @param EUpdateStatus_Add          : item is added
* @param EUpdateStatus_Delete       : item is deleted
* @param EUpdateStatus_Reconfigured : item is reconfigured
* @param EUpdateStatus_Unchanged    : item stays unchanged
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom / Katja Saapunki
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



