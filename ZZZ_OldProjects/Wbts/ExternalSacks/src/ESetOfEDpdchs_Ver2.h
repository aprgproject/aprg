/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/ESetOfEDpdchs_Ver2.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_SETOFEDPDCHS_VER2_H
#define _E_SETOFEDPDCHS_VER2_H

#include <DFromTc_dsp.h>
 
typedef enum ESetOfEDpdchs_Ver2 
{
    ESetOfEDpdchs_Ver2_None        = 0,
    ESetOfEDpdchs_Ver2_Idle        = 1,
    ESetOfEDpdchs_Ver2_SF256       = 2,
    ESetOfEDpdchs_Ver2_SF128       = 3,
    ESetOfEDpdchs_Ver2_SF64        = 4,
    ESetOfEDpdchs_Ver2_SF32        = 5,
    ESetOfEDpdchs_Ver2_SF16        = 6,
    ESetOfEDpdchs_Ver2_SF8         = 7,
    ESetOfEDpdchs_Ver2_SF4         = 8,
    ESetOfEDpdchs_Ver2_2SF4        = 9,
    ESetOfEDpdchs_Ver2_2SF2        = 10,
    ESetOfEDpdchs_Ver2_2SF4_2SF2   = 11,
    ESetOfEDpdchs_Ver2_2SF4M_2SF2M = 12,
    ESetOfEDpdchs_Ver2_NoValue     = NO_VALUE_FOR_ENUMS
} ESetOfEDpdchs_Ver2;

#endif /* _E_SETOFEDPDCHS_VER2_H */

/***********************************************************************
* @enum ESetOfEDpdchs_Ver2
* Description         : Defines the set of E-DPDCHs.
*                       The number of available bits per TTI of one E-DPDCH for all 
*                       possible spreading factors and modulation schemes is denoted 
*                       by N256(SF256), N128(SF128), N64,(SF64), N32(SF32), N16(SF16),
*                       N8(SF8), N4(SF4), N2(SF2), M4(SF4M) and M2(SF2M) where the 
*                       index refers to the spreading factor. N refers to BPSK 
*                       modulation and M to 4PAM modulation.
*
* Reference           : 
*
* @param ESetOfEDpdchs_None:      No E-DPDCH code channel.
* @param ESetOfEDpdchs_Idle:      No E-DPDCH code channel.
* @param ESetOfEDpdchs_SF256      Single E-DPDCH code channel, spreading factor 256.
* @param ESetOfEDpdchs_SF128:     Single E-DPDCH code channel, spreading factor 128.
* @param ESetOfEDpdchs_SF64:      Single E-DPDCH code channel, spreading factor 64.
* @param ESetOfEDpdchs_SF32:      Single E-DPDCH code channel, spreading factor 32.
* @param ESetOfEDpdchs_SF16:      Single E-DPDCH code channel, spreading factor 16.
* @param ESetOfEDpdchs_SF8:       Single E-DPDCH code channel, spreading factor 8.
* @param ESetOfEDpdchs_SF4:       Single E-DPDCH code channel, spreading factor 4.
* @param ESetOfEDpdchs_2SF4:      Multiple E-DPDCH code channels, two code channels with
*                                 spreading factor 4. 
* @param ESetOfEDpdchs_2SF2:      Multiple E-DPDCH code channels, two code channels with
*                                 spreading factor 2. 
* @param ESetOfEDpdchs_2SF4_2SF2: Multiple E-DPDCH code channels (BPSK modulation), two channels
*                                 with spreading factor 4 and two channels with spreading factor 2.
* @param ESetOfEDpdchs_2SF4M_2SF2M: Multiple E-DPDCH code channels (4PAM modulation), two channels
*                                   with spreading factor 4 and two channels with spreading factor 2.
* @param ESetOfEDpdchs_NoValue:   None / not present.
*
* Additional Information : 
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/



