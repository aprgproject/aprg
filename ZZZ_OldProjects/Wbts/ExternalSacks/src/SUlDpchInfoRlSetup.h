/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SUlDpchInfoRlSetup.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Saku Matasaho
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_UL_DPCH_INFO_RL_SETUP_H
#define _S_UL_DPCH_INFO_RL_SETUP_H

#include <SUlScramblingCode.h>
#include <EMinUlChannelisationCodeLength.h>
#include <TPunctureLimit.h>
#include <EUlDpcchSlotFormat.h>
#include <TUlSirTarget.h>
#include <EDiversityMode.h>
#include <EDpcMode.h>
#include <EUlDpdchIndEDch.h>

struct SUlDpchInfoRlSetup
{
    SUlScramblingCode                   ulScramblingCode;
    EMinUlChannelisationCodeLength      minUlChannelisationCodeLength;
    TPunctureLimit                      punctureLimit;
    EUlDpcchSlotFormat                  ulDpcchSlotFormat;
    TUlSirTarget                        ulSirTarget;
    EDiversityMode                      diversityMode;
    EDpcMode                            dpcMode;
    EUlDpdchIndEDch                     ulDpdchIndicatorForEDchOperation;
};

typedef struct SUlDpchInfoRlSetup SUlDpchInfoRlSetup;

#endif /* _S_UL_DPCH_INFO_RL_SETUP_H */

/******************************************************************************
* @struct SRadioLinkSetup
* Description         : Includes UL DPCH Information parameters in Radio Link
*                       Setup.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: PI
*
* @param ulScramblingCode :
*       Uplink scrambling code is unique to each MS and it is used continuously
*       even if the frequency is changed.
*
* @param minUlChannelisationCodeLength :
*       Minimum UL Channelisation code length (=spreading factor) of a DPDCH or
*       a PRACH message part, which is supported by UE or restricted by the 
*       network.
*
* @param punctureLimit :
*       The maximum amount of puncturing for a transport channel.
*
* @param ulDpcchSlotFormat :
*       Indicates the slot format used in DPCCH in UL.
*
* @param ulSirTarget :
*       UL SIR Target indicates a received UL SIR.
*
* @param diversityMode:
*       Indicates diversity mode to be used.
*
* @param dpcMode :
*       Indicates which Downlink Power Control mode (DPC mode) is applied.
*
* @param ulDpdchIndicatorForEDchOperation :
*       Indicates the presence of UL DPDCH for E-DCH.
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

