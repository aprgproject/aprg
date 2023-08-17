/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EMulticellEdchTpBearMode.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_MULTICELL_EDCH_TP_BEAR_MODE_H
#define _E_MULTICELL_EDCH_TP_BEAR_MODE_H

#include <DFromTc_dsp.h>

typedef enum EMulticellEdchTpBearMode
{
    EMulticellEdchTpBearMode_SeparateIubTpBearMode       = 0,
    EMulticellEdchTpBearMode_UlFlowMultiMode             = 1,
    EMulticellEdchTpBearMode_NoValue                     = NO_VALUE_FOR_ENUMS
}EMulticellEdchTpBearMode;

#endif /* _E_MULTICELL_EDCH_TP_BEAR_MODE_H */


/***********************************************************************
* @enum EMulticellEdchTpBearMode
* Description         : This IE indicates the Multicell E-DCH Transport Bearer Mode.
*                       For Multicell E-DCH Transport Bearer Mode  = "Separate Iub
*                       Transport Bearer Mode" the Mac-d flows from each carrier
*                       uses different Iub transport bearers, for Multicell E-DCH
*                       Transport Bearer Mode  = "UL Flow Multiplexing Mode" the
*                       Mac-d flows received on the different carriers in the Node B
*                       is multiplexed on one Iub transport bearer (per Mac-d flow).
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

