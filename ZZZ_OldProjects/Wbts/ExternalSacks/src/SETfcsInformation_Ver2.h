/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SETfcsInformation_Ver2.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Krzysztof Michalak
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_E_TFCS_INFORMATION_VER2_H
#define _S_E_TFCS_INFORMATION_VER2_H


#include <TIndex.h>
#include <TETfci.h>
#include <TNumberOfItems.h>
#include <SReferenceETfciInformation.h>
#include <TPowerOffset.h>
#include <TEDpchPower.h>
#include <DOpenIUBCommonDefs.h>

struct SETfcsInformation_Ver2
{
    TIndex                      eTfciTableIndex;
    TETfci                      eDchMinSetETfci;
    TNumberOfItems              numOfRefETfci;
    SReferenceETfciInformation  refETfci[MAX_NR_OF_REF_ETFCIS];
    TETfci                      eTfciBetaECBoost;
    TPowerOffset                ulDeltaT2TP;
    TEDpchPower                 eDpdchPowInterpolation;
};

typedef struct SETfcsInformation_Ver2 SETfcsInformation_Ver2;

#endif /* _S_E_TFCS_INFORMATION_VER2_H */

/******************************************************************************
* @struct SETfcsInformation_Ver2
* Description         : E-TFCS Information for ver2
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: PI
*
* @param eTfciTableIndex :
*   E-DCH Decoder, E-DCH RM, Scheduler Indicates which standardised E-TFCS 
*   Transport Block Size Table shall be used. 
* 
* @param eDchMinSetETfci :
*   Scheduler. If this IE is not present NO_VALUE is used.
* 
* @param numOfRefETfci :
*   Number of Reference E-TFCI.
*
* @param refETfci[MAX_NR_OF_REF_ETFCIS] :
*   Reference E-TFCI Information.
*
* @param eTfciBetaECBoost :
*   E-TFCI threshold beyond which boosting of E-DPCCH is enabled.
*   If this IE is not present NO_VALUE is used.
* 
* @param ulDeltaT2TP :
*   Total E-DPDCH power across all codes to the combined power of DPCCH and E-DPCCH.
*   This IE is present if the E-TFCI BetaEC Boost IE value is not set to 127. Else NO_VALUE is used.
* 
* @param eDpdchPowInterpolation :
*   True ('1') means that the E-DPDCH power interpolation formula shall be applied.
*   False ('0') means that the E-DPDCH power extrapolation formula shall be applied for the computation of the gain factor [B]ed
*   If this IE is not present NO_VALUE is used.
*
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

