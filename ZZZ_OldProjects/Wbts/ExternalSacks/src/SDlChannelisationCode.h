/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SDlChannelisationCode.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef SDLCHANNELISATIONCODE_H
#define SDLCHANNELISATIONCODE_H

#include <TDlScramblingCode.h>
#include <TDlChannelisationCodeNumber.h>
#include <EPresence.h>
#include <ECmScramblingCodeChange.h>

struct SDlChannelisationCode
{
        TDlScramblingCode               dlScramblingCode;
        TDlChannelisationCodeNumber     dlChannelisationCodeNumber;
        EPresence                       dlScramblingCodeChangePresent;
        ECmScramblingCodeChange         dlScramblingCodeChange;
};
typedef struct SDlChannelisationCode SDlChannelisationCode;

#endif /* SDLCHANNELISATIONCODE_H */

/**
*******************************************************************************
* @struct SDlChannelisationCode
*
* Description : Provides FDD DL code information for the RL.
*
* Reference   : WCDMA BTS RELEASES BTS RELEASE PROGRAMS
*               DSP SW - MCU SW INTERFACE SPECIFICATION
*
* Parameters  :
*
* @param dlScramblingCode              : DL scrambling code to be used by the RL. One
*                                        cell may have multiple DL scrambling codes
*                                        available.
*
* @param dlChannelisationCodeNumber    : The DL Channelisation Code Number indicates
*                                        the DL Channelisation Code number for a
*                                        specific DL physical channel.
*
* @param dlScramblingCodeChangePresent : Indicates whether the dlScramblingCodeChange
*                                        below is valid or not.
*
* @param dlScramblingCodeChange        : Indicates whether the alternative scrambling
*                                        code is used for compressed mode method
*                                        "SF/2".
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : DSP/Saku Matasaho
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/
