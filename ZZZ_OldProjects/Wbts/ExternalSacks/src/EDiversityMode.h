/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EDiversityMode.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jesse Pasuri
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_DIVERSITY_MODE_H
#define _E_DIVERSITY_MODE_H

#include <DFromTc_dsp.h>

typedef enum EDiversityMode
{
    EDiversityMode_None             = 0,
    EDiversityMode_STTD             = 1,
    EDiversityMode_ClosedLoopMode1  = 2,
    EDiversityMode_ClosedLoopMode2  = 3,
    EDiversityMode_NotUsed          = 4,
    EDiversityMode_NoValue          = NO_VALUE_FOR_ENUMS
}EDiversityMode;

#endif /* _E_DIVERSITY_MODE_H */

/**
*******************************************************************************
* @enum ETransmitDiversityIndicator
* Description         : 9.2.2.9 Diversity mode (3G).
*                       Define the diversity mode to be applied.
*
* Reference           : 3GPP TS 25.433,
*                       WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location : PI
*
* Additional Information  : -
*
* Definition Provided by  : Telecom
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

