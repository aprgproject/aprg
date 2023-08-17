/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/ETransmitDiversityIndicator.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        Jesse Pasuri
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _E_TRANSMIT_DIVERSITY_INDICATOR_H
#define _E_TRANSMIT_DIVERSITY_INDICATOR_H

#include <DFromTc_dsp.h>

typedef enum ETransmitDiversityIndicator
{
    ETransmitDiversityIndicator_Active      = 0,
    ETransmitDiversityIndicator_Inactive    = 1,
    ETransmitDiversityIndicator_NoValue     = NO_VALUE_FOR_ENUMS
} ETransmitDiversityIndicator;

#endif /* _E_TRANSMIT_DIVERSITY_INDICATOR_H */

/**
*******************************************************************************
* @enum ETransmitDiversityIndicator
*
* Description         : 9.2.2.53 Transmit Diversity Indicator.
*                       The Transmit Diversity Indicator indicates whether
*                       transmit diversity shall be active or not.
*
* Reference           : 3GPP TS 25.433,
*                       WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location : PI
*
* Parameters:
*
* @param ETransmitDiversityIndicator_Active :
* @param ETransmitDiversityIndicator_Inactive :
* @param ETransmitDiversityIndicator_NoValue :
*
* Additional Information  : -
*
* Definition Provided by  : Telecom
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

