/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/TRncIdentifier.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _TRNC_IDENTIFIER_H
#define _TRNC_IDENTIFIER_H

#include <glo_def.h>

typedef u32        TRncIdentifier;

#endif /* _TRNC_IDENTIFIER_H */

/******************************************************************
*
* Description :  This IE identifies to the BTS is the resource to Iub only
*                or does the resource have also Iur component. The absence
*                of an RNC Identifier IE as well as the RNC Identifier
*                value 0 indicates that the radio bearer originates in the
*                CRNC and is over the Iub only. This information is used by
*                Node B to determine in case of congestion whether the Iub
*                or an Iur is congested.In case of Iur congestion, the rate
*                of flows originating in the CRNC shall not be reduced.
*
* Reference   :  WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                DSP SW - MCU SW INTERFACE SPECIFICATION
*                Location: Sharenet
*
* Parameters  :
*
*  <additional explanations>
*
* Provider :
*
* Remember to put an empty line in the end of each definition 
* file. Otherwise the compiler will generate a warning.
************************************************************************/

