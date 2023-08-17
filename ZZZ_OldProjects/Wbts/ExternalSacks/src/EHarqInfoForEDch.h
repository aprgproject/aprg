/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EHarqInfoForEDch.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        Kari Korvela
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _E_HARQ_INFO_FOR_EDCH_H
#define _E_HARQ_INFO_FOR_EDCH_H

#include <DFromTc_dsp.h>

typedef enum EHarqInfoForEDch
{
    EHarqInfoForEDch_Rv0        = 0,
    EHarqInfoForEDch_RvTable    = 1,
    EHarqInfoForEDch_NoValue    = NO_VALUE_FOR_ENUMS
} EHarqInfoForEDch;

#endif /* _E_HARQ_INFO_FOR_EDCH_H */

/**
*******************************************************************************
* @enum EHarqInfoForEDch
*
* Description         : HARQ information indicator.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: PI
*
* Parameters :
*
* @param EHarqInfoForEDch_Rv0 :
* @param EHarqInfoForEDch_RvTable :
* @param EHarqInfoForEDch_NoValue :
*
* Additional Information : 
*
* Definition Provided by : DSP, L2
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

