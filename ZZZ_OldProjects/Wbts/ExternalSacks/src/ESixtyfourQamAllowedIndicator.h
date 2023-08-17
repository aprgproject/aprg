/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/ESixtyfourQamAllowedIndicator.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Krzysztof Michalak
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_SIXTY_FOUR_QAM_USAGE_ALLOWED_INDICATOR_H
#define _E_SIXTY_FOUR_QAM_USAGE_ALLOWED_INDICATOR_H

#include <DFromTc_dsp.h>

typedef enum ESixtyfourQamAllowedIndicator 
{
  ESixtyfourQamAllowedIndicator_Allowed     = 0,
  ESixtyfourQamAllowedIndicator_NotAllowed  = 1,
  ESixtyfourQamAllowedIndicator_NoValue     = NO_VALUE_FOR_ENUMS

} ESixtyfourQamAllowedIndicator;

#endif  /* _E_SIXTY_FOUR_QAM_USAGE_ALLOWED_INDICATOR_H */

/******************************************************************************
* @enum ESixtyfourQamAllowedIndicator
* Description         : Sixtyfour QAM Usage Allowed Indicator
*
* Reference           : WCDMA BTS SW DSP SW - MCU SW INTERFACE SPECIFICATION
**
* Additional Information : <type additional information if needed>
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/

