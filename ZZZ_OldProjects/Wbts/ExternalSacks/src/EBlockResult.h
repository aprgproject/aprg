/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EBlockResult.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _EBLOCKRESULT_H
#define _EBLOCKRESULT_H
 
typedef enum EBlockResult
{
  EBlockResult_Cleared              = 0,
  EBlockResult_RequestDenied        = 1,
  EBlockResult_RejectedByRNC        = 2,
  EBlockResult_BlockReqSentToRnc    = 3,
  EBlockResult_CellDeletionStarted  = 4
} EBlockResult;

#endif /* _EBLOCKRESULT_H */

/**
*******************************************************************************
* @enum EBlockResult
*
* Description :
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* @param EBlockResult_Cleared :
* @param EBlockResult_RequestDenied :
* @param EBlockResult_RejectedByRNC :
* @param EBlockResult_BlockReqSentToRnc :
* @param EBlockResult_CellDeletionStarted :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



