/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/UAesa.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef UAESA_H
#define UAESA_H

#include <SDccAesaFormat.h>
#include <SIcdAesaFormat.h>
#include <SE164AesaFormat.h>
#include <SLocalAesaFormat.h>

typedef union
{
  SDccAesaFormat   dccAesa;       /* (not so elegant, but should work ;-)*/
  SIcdAesaFormat   icdAesa;
  SE164AesaFormat  e164Aesa;
  SLocalAesaFormat localAesa;
} UAesa;

#endif /* UAESA_H */

/**
*******************************************************************************
* @union UAesa
*
* Description  : ATM End System Address
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* @param dccAesa :
* @param icdAesa :
* @param e164Aesa :
* @param localAesa :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



