/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EHeaderFormat.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef EHEADERFORMAT_H
#define EHEADERFORMAT_H

typedef enum
{
  EHeaderFormat_AddRemoveApi = 1,      /* E.g., from/to RNC  - (NBAP, AAL2sig)!!*/
  EHeaderFormat_Api          = 2,      /* Normal WAM protocol traffic: inside BTS.*/
  EHeaderFormat_Ip           = 3,      /* IPoA-Ethernet traffic.*/
  EHeaderFormat_UserSpecific = 4,      /* ATM MCUs (AAL2 VCCs, AXU Loop VCC, etc.).*/
  EHeaderFormat_Null         = 5       /* No normal traffic (e.g., only OAM cells).*/
} EHeaderFormat;

#endif /* EHEADERFORMAT_H */

/**
*******************************************************************************
* @enum EHeaderFormat
*
* Description  : Header format in ATM connection
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* @param EHeaderFormat_AddRemoveApi :
* @param EHeaderFormat_Api :
* @param EHeaderFormat_Ip :
* @param EHeaderFormat_UserSpecific :
* @param EHeaderFormat_Null :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/


