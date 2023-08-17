/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SE164AesaFormat.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _SE164AESAFORMAT_H
#define _SE164AESAFORMAT_H

#include <glo_def.h>

#include <D_AtmConsts.h>

typedef struct SE164AesaFormat
{
    u8         octet[AESA_SIZE];
} SE164AesaFormat;

#endif /* _SE164AESAFORMAT_H */

/**
*******************************************************************************
* @struct SE164AesaFormat
*
* Description :
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* @param octet :
*
* Additional Information :
*            (AFI == 0x45)
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



