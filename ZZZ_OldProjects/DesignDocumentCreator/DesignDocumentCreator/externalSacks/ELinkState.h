/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/ELinkState.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef ELINKSTATE_H
#define ELINKSTATE_H

typedef enum ELinkState
{
    ELinkState_InService            = 0,
    ELinkState_OutOfService         = 1,
    ELinkState_DeactivationOngoing  = 2,
    ELinkState_LinkDeleted          = 3
} ELinkState;

#endif /* ELINKSTATE_H */

/**
*******************************************************************************
* @enum ELinkState
*
* Development Workset : Only in SVN
*
* Description  : Link status
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* @param ELinkState_InService :
* @param ELinkState_OutOfService :
* @param ELinkState_DeactivationOngoing :
* @param ELinkState_LinkDeleted :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/
