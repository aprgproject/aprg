/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/TMaxAdjustmentStep.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _TMAXADJUSTMENTSTEP_H
#define _TMAXADJUSTMENTSTEP_H

#include <glo_def.h>
         
typedef u32 TMaxAdjustmentStep;

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description : 9.2.2.20  Max Adjustment Step. 
*               Defines the maximum allowed value for the change of DL power
*               level during a certain number of slots that can be utilised
*               by the downlink power balancing algorithm. Max Adjustment Step
*               IE defines a time period, in terms of number of slots, in which
*               the accumulated power adjustment shall be maximum 1dB. This
*               value does not include the DL inner loop PC adjustment.
*
* Reference   : 3GPP TS 25.433 v4.1.0
*
*  IE Type and Reference:  INTEGER(1 .. 10)
*  Semantics description:  Slots
*
* Provider : Telecom / Jesse Pasuri / Mika Hautala
*
************************************************************************/

#endif

