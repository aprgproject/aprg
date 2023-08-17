/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/ESixteenQamInd.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Krzysztof Michalak
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_SIXTEEN_QAM_IND_H
#define _E_SIXTEEN_QAM_IND_H

#include <DFromTc_dsp.h>

typedef enum ESixteenQamInd
{
    ESixteenQamInd_Activate     = 0,
    ESixteenQamInd_Deactivate   = 1,
    ESixteenQamInd_NoValue      = NO_VALUE_FOR_ENUMS

} ESixteenQamInd;

#endif /* _E_SIXTEEN_QAM_IND_H */

/******************************************************************************
* @enum ESixteenQamInd
* Description         : SixteenQAM UL Operation Indicator
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

