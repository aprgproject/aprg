/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EEagchTableChoice.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_EAGCH_TABLE_CHOICE_H
#define _E_EAGCH_TABLE_CHOICE_H

#include <DFromTc_dsp.h>

typedef enum EEagchTableChoice
{
    EEagchTableChoice_Table16B                  = 0,
    EEagchTableChoice_Table16B12                = 1,
    EEagchTableChoice_NoValue                   = NO_VALUE_FOR_ENUMS
}EEagchTableChoice;

#endif /* _E_EAGCH_TABLE_CHOICE_H */


/***********************************************************************
* @enum EEagchTableChoice
* Description         : The E-AGCH Table Choice IE indicates the choice of the E-AGCH table 
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/

