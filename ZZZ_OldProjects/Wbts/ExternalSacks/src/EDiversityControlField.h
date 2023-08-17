/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EDiversityControlField.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        Jukka Sakkinen
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _EDIVERSITYCONTROLFIELD_H
#define _EDIVERSITYCONTROLFIELD_H

#include <DFromTc_dsp.h>

typedef enum EDiversityControlField
{
    ECombineSplitAtBTS        = 1,
    ECombineSplitAtBTSorRNC   = 2,
    ECombineSplitAtRNC        = 3,
    ECombineSplit_NoValue     = NO_VALUE_FOR_ENUMS
} EDiversityControlField;

#endif /* _EDIVERSITYCONTROLFIELD_H */

/**
*******************************************************************************
* @enum EDiversityControlField
*
* Description :
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* @param ECombineSplitAtBTS :
* @param ECombineSplitAtBTSorRNC :
* @param ECombineSplitAtRNC :
* @param ECombineSplit_NoValue :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/




