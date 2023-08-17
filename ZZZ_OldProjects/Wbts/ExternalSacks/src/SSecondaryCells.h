/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SSecondaryCells.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Wang Xiaojiang
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_SECONDARY_CELLS
#define _S_SECONDARY_CELLS

#include <TCellId.h>
#include <TNumHsScchCodes.h>
#include <ESixtyfourQamAllowedIndicator.h>
#include <TMimoActivationInd.h>
#include <TEDchInd.h>

struct SSecondaryCells 
{
    TCellId                             cellId;
    TNumHsScchCodes                     numSecondaryHsScchCodes;
    ESixtyfourQamAllowedIndicator       sixtyFourQamUsageAllowedInd;
    TMimoActivationInd                  mimoActivationInd;
    TEDchInd                            eDchInd;
};
typedef struct SSecondaryCells SSecondaryCells;

#endif /* _S_SECONDARY_CELLS */

/******************************************************************
* @struct SSecondaryCells
* Description         : Preconfigured secondary serving HS-DSCH cell.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param cellId :
*                       Cell ID of the preconfigured secondary serving HS-DSCH cell.
*
* @param numSecondaryHsScchCodes : 
*                       For the secondary serving HS-DSCH cell.
*                       If this IE is not present NO_VALUE is used.
*
* @param sixtyFourQAMUsageAllowedInd :
*                       For the secondary serving HS-DSCH cell.
*                       This IE indicates whether the BTS is allowed to use 64 QAM modulation
*                       for HS-DSCH transmission or not.
*                       If this IE is not present NO_VALUE_FOR_ENUMS is used.
*
* @param mimoActivationInd :
*                       0 = not present, 1 = present. If this IE is not present value 0
*
* @param eDchInd :
*                       The secondary serving HS-DSCH cell shall be pre-configured with E-DCH.
*                       0 = not present,1 = present
*                       If this IE is not present value 0 is used.
*
* Additional Information : -
*
* Definition Provided by : DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/

