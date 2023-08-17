/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SIcdAesaFormat.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _SICDAESAFORMAT_H
#define _SICDAESAFORMAT_H

#include <glo_def.h>

#include <D_AtmConsts.h>

typedef struct SIcdAesaFormat
{
    u8         octet[AESA_SIZE];
} SIcdAesaFormat;

#endif /* _SICDAESAFORMAT_H */

/**
*******************************************************************************
* @struct SIcdAesaFormat
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
*             (AFI == 0x47)
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



