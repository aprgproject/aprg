/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EHarqPreambleMode.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Krzysztof Michalak
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_HARQ_PREAMBLE_MODE_H
#define _E_HARQ_PREAMBLE_MODE_H

#include <DFromTc_dsp.h>

typedef enum EHarqPreambleMode
{
    EHarqPreambleMode_0       = 0,
    EHarqPreambleMode_1       = 1,
    EHarqPreambleMode_NoValue = NO_VALUE_FOR_ENUMS

} EHarqPreambleMode;

#endif /* _E_HARQ_PREAMBLE_MODE_H */

/******************************************************************************
* @enum EHarqPreambleMode
* Description         : If this IE is not present NO_VALUE_FOR_ENUMS is used.
*                       The HARQ Preamble Mode IE is used as described in 
*                       3GPP TS 25.214 'Physical layer procedures'
*                       If this IE is not present NO_VALUE_FOR_ENUMS is used.
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

