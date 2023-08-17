/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SDlTxRefPowerInfo.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _SDLTXREFPOWERINFO_H
#define _SDLTXREFPOWERINFO_H

#include <TDlTxPower.h>
#include <TRadioLinkId.h>

struct SDlTxRefPowerInfo
{
	TRadioLinkId            radioLinkId;
	TDlTxPower              dlRefPower;
} ;
typedef struct SDlTxRefPowerInfo SDlTxRefPowerInfo;

#endif /* _SDLTXREFPOWERINFO_H */

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description :         dlRefPower defines the DL target power to
*                       given radioLinkId.
*
* Reference :           3GPP TS 25.433 v4.3.0
*
*  IE Type and Reference:  INTEGER(-350..150)
*  Semantics description:
*               Value = DL Power /10
*               Unit: dB
*               Range: -35.0 .. +15.0 dB
*               Step: 0.1dB
*
* Provider : Telecom
*
************************************************************************/

