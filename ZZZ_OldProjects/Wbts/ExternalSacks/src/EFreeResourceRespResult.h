/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EFreeResourceRespResult.h $
* @version               $LastChangedRevision: 2061 $
* @date                  $LastChangedDate: 2014-07-10 20:54:51 +0800 (Thu, 10 Jul 2014) $
* @author                $Author: budziak $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef EFREERESOURCERESPRESULT_H
#define EFREERESOURCERESPRESULT_H

enum EFreeResourceRespResult
{
    EFreeResourceRespResult_Ack = 0,
    EFreeResourceRespResult_Nack_EmergCallInWsp = 1,
    EFreeResourceRespResult_Nack_CchInWsp = 2,
    EFreeResourceRespResult_Nack_UnknownWsp = 3,
    EFreeResourceRespResult_Nack_StartupAllocationOngoing = 4
};
typedef enum EFreeResourceRespResult EFreeResourceRespResult;

#endif /* EFREERESOURCERESPRESULT_H */

/**
*******************************************************************************
* @enum EFreeResourceRespResult
*
* Description : Defines WSP blocking success codes
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* @param EFreeResourceRespResult_Ack :
* @param EFreeResourceRespResult_Nack_EmergCallInWsp :
* @param EFreeResourceRespResult_Nack_CchInWsp :
* @param EFreeResourceRespResult_Nack_UnknownWsp :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



