/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/ERadioResourceType.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _ERADIORESOURCETYPE_H
#define _ERADIORESOURCETYPE_H

typedef enum ERadioResourceType
{
    ERadioResourceType_Rx            = 0,
    ERadioResourceType_Tx            = 1
} ERadioResourceType;

#endif /* _ERADIORESOURCETYPE_H */

/**
*******************************************************************************
* @enum ERadioResourceType
*
* Description :	 Enum definitions for radio resource type
*
* Reference   :  BTSOM - TCOM Interface Specification, v 3.0, PI
*
* Parameters :
*
* @param ERadioResourceType_Rx : for Rx carrier
*
* @param ERadioResourceType_Tx : for Tx carrier
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Margus Metsanurm
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/
