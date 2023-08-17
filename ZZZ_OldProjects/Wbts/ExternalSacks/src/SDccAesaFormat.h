/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SDccAesaFormat.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _SDCCAESAFORMAT_H
#define _SDCCAESAFORMAT_H

#include <glo_def.h>

#include <D_AtmConsts.h>

typedef struct SDccAesaFormat
{
    u8         octet[AESA_SIZE];
} SDccAesaFormat;

#endif /* _SDCCAESAFORMAT_H */

/**
*******************************************************************************
* @struct SDccAesaFormat
*
* Description :
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
* @param octet :
*
*  (AFI == 0x39, value of the first octet is the "Authority and Format Identifier")
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



