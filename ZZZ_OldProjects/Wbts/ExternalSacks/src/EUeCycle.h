/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EUeCycle.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Krzysztof Michalak
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_UE_CYCLE_H
#define _E_UE_CYCLE_H

#include <DFromTc_dsp.h>

typedef enum EUeCycle
{
    EUeCycle_1       = 0, 
    EUeCycle_4       = 1,
    EUeCycle_5       = 2,
    EUeCycle_8       = 3,
    EUeCycle_10      = 4,
    EUeCycle_16      = 5,
    EUeCycle_20      = 6,
    EUeCycle_32      = 7,
    EUeCycle_40      = 8,
    EUeCycle_64      = 9,
    EUeCycle_80      = 10,
    EUeCycle_128     = 11,
    EUeCycle_160     = 12,
    EUeCycle_NoValue = NO_VALUE_FOR_ENUMS

} EUeCycle;

#endif /* _E_UE_CYCLE_H */

/******************************************************************************
* @enum EUeCycle
* Description         : UE Cycle
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

