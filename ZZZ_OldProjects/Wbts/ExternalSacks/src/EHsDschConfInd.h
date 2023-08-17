/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EHsDschConfInd.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Kari Korvela
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_HS_DSCH_CONF_IND_H
#define _E_HS_DSCH_CONF_IND_H

#include <DFromTc_dsp.h>

typedef enum EHsDschConfInd
{
    EHsDschConfInd_Configured       = 0,
    EHsDschConfInd_NotConfigured    = 1,
    EHsDschConfInd_NoValue          = NO_VALUE_FOR_ENUMS
}EHsDschConfInd;

#endif /* _E_HS_DSCH_CONF_IND_H */

/******************************************************************************
* @enum EHsDschConfInd
* Description         : HS-DSCH configured indicator.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: PI
*
* @param Configured     : HS-DSCH is configured for the user
* @param NotConfigured  : HS-DSCH is not configured for the user
* @param NoValue        : Not present
* Additional Information : 
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

