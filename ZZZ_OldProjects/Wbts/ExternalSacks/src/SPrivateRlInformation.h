/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SPrivateRlInformation.h $
* @version               $LastChangedRevision: 5072 $
* @date                  $LastChangedDate: 2017-10-11 16:36:51 +0800 (Wed, 11 Oct 2017) $
* @author                $Author: zogeng $
*
* Original author        Wang Xiaojiang
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_PRIVATE_RL_INFORMATION
#define _S_PRIVATE_RL_INFORMATION

#include <TRncIdentifier.h>
#include <TOperatorId.h>
#include <SUeTracing.h>
#include <EHappyBitDelayConditionPeriod.h>

struct SPrivateRlInformation
{
    TRncIdentifier                rncIdentifier;
    TOperatorId                   operatorId;
    SUeTracing                    ueTracing;
    EHappyBitDelayConditionPeriod happyBitDelayConditionPeriod;
};
typedef struct SPrivateRlInformation SPrivateRlInformation;

#endif /* _S_PRIVATE_RL_INFORMATION */

/******************************************************************
* @struct SPrivateRlInformation
* Description         : The Private RL Information contains collection of private
*                       information that is wanted to be signalled towards BTS in
*                       RL procedure level 
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* Parameters           :
* @param rncIdentifier :
*                       This IE identifies to the BTS is the resource to Iub only
*                       or does the resource have also Iur component. The absence
*                       of an RNC Identifier IE as well as the RNC Identifier
*                       value 0 indicates that the radio bearer originates in the
*                       CRNC and is over the Iub only. This information is used by
*                       Node B to determine in case of congestion whether the Iub
*                       or an Iur is congested.In case of Iur congestion, the rate
*                       of flows originating in the CRNC shall not be reduced.
*                       If this IE is not present NO_VALUE is used.
*
* @param operatorId :   The associated home operator of the UE.
*
* @param ueTracing :    This structure contains the needed information for RAN2861 UE tracing.
*
* @param happyBitDelayConditionPeriod : This is the happy bit delay condition period of the UE.
*
* Additional Information : -
*
* Definition Provided by : DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/

