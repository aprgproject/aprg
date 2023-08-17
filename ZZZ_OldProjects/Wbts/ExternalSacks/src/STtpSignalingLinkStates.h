/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/STtpSignalingLinkStates.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef STTPSIGNALINGLINKSTATES_H
#define STTPSIGNALINGLINKSTATES_H

#include <CoreTypes.h>
#include <ELinkState.h>
#include <glo_def.h>

struct STtpSignalingLinkStates
{
    TBoard        wamUnitAddr;            /* address of WAM unit where this TTP is located*/
    u8            pad1;
    u8            pad2;
    u8            pad3;
    ELinkState    dnbapLinkState;         /* state of D-NBAP link*/
    ELinkState    aal2SignalingLinkState; /* state of AAL2 signaling link*/
};
typedef struct STtpSignalingLinkStates STtpSignalingLinkStates;

#endif /* STTPSIGNALINGLINKSTATES_H */

/**
*******************************************************************************
* @struct STtpSignalingLinkStates
*
* Description :
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* @param wamUnitAddr :
* @param pad1 :
* @param pad2 :
* @param pad3 :
* @param dnbapLinkState :
* @param aal2SignalingLinkState :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



