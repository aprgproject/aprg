/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EUlDpdchIndEDch.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Kristian Ruotsalainen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_UL_DPDCH_IND_EDCH_H
#define _E_UL_DPDCH_IND_EDCH_H

#include <DFromTc_dsp.h>

typedef enum EUlDpdchIndEDch
{
    EUlDpdchIndEDch_Present    = 0,
    EUlDpdchIndEDch_NotPresent = 1,
    EUlDpdchIndEDch_NoValue    = NO_VALUE_FOR_ENUMS
    
} EUlDpdchIndEDch;

#endif  /* _E_UL_DPDCH_IND_EDCH_H */

/***********************************************************************
* @enum EUlDpdchIndEDch
* Description         : 9.2.2.61 UL DPDCH Indicator For E-DCH Operation (3G). 
*                       "This parameter indicates whether some UL DPCH parameters
*                       should be ignored or not in the message in which the UL DPDCH
*                       Indicator For E-DCH Operation IE was included."
*
* Reference           : 3GPP TS 25.433 v6.6.0
*
* @param EUlDpdchIndEDch_Present     : UL-DPDCH present.
* @param EUlDpdchIndEDch_NotPresent  : UL-DPDCH not present
* @param EUlDpdchIndEDch_NoValue     : "This IE is not present."
*
*
* Additional Information : N/A
*
* Definition Provided by : Telecom, Kristian Ruotsalainen
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/


