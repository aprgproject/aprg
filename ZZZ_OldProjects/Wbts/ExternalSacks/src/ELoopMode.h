/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/ELoopMode.h $
* @version               $LastChangedRevision: 2260 $
* @date                  $LastChangedDate: 2015-01-20 11:11:44 +0800 (Tue, 20 Jan 2015) $
* @author                $Author: yuson $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _ELOOPMODE_H
#define _ELOOPMODE_H

#include <DFromTc_dsp.h>

typedef enum ELoopMode
{
     ELoopMode_Normal   = 0,
     ELoopMode_Wcdma    = 1,
     ELoopMode_Baseband = 2,
     ELoopMode_IradAsic = 3,
     ELoopMode_Transparent  = 4,
     ELoopMode_TestModel1   = 5,
     ELoopMode_TestModel2   = 6,
     ELoopMode_TestModel3   = 7,
     ELoopMode_TestModel4   = 8,
     ELoopMode_TestModel5   = 9,
     ELoopMode_TestModel6   = 10,
     ELoopMode_TestModelN6  = 11,
     ELoopMode_TestModelN7  = 12,
     ELoopMode_TestModelN8  = 13,
     ELoopMode_TestModelN9  = 14,
     ELoopMode_TestModelN10 = 15,
     ELoopMode_TestModelN11 = 16,
     ELoopMode_TestModelN12 = 17,
     ELoopMode_TestModelN13 = 18,
     ELoopMode_BerTest      = 19,
     ELoopMode_PimTest      = 20,
     ELoopMode_NoValue      = NO_VALUE_FOR_ENUMS
} ELoopMode;

#endif /* _ELOOPMODE_H */

/**
*******************************************************************************
* @enum ELoopMode
*
* Description         : Possible loop mode values.
*
* Reference           : <type interface spec., version, location here>
*
* Parameters :
*
* @param ELoopMode_Normal           : No loop mode in use.
* @param ELoopMode_Wcdma            : There was not enough memory available for PM
* @param ELoopMode_Baseband         : Baseband loop mode
* @param ELoopMode_IradAsic         : IRAD ASIC loop mode
* @param ELoopMode_Transparent      : Transparent loop mode
* @param ELoopMode_TestModel1-N13   : testmodel 1/2/3/4/5/6/N6/N7/N8/N9/N10/N11/N12/N13
* @param ELoopMode_BerTest          : value for BerMeas for Internal TCOM use
* @param ELoopMode_NoValue          : No value
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : <type definition provider here> e.g System Component
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/
