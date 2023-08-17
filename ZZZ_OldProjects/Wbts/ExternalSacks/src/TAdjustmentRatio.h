/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/TAdjustmentRatio.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _TADJUSTMENTRATIO_H
#define _TADJUSTMENTRATIO_H

#include <glo_def.h>
         
typedef u32 TAdjustmentRatio;

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description : 9.2.2.C	Adjustment . 
*               Adjustment Ratio IE (Radj) defines the convergence rate used for 
*               the associated Adjustment Period.
*
* Reference   : 3GPP TS 25.433 v4.3.0
*
*  IE Type and Reference:  INTEGER(0 .. 100)
*  Semantics description:  The adjustment Ratio is given with a granularity
*			   of 0.01
*				0 -> 0.00
*				1 -> 0.01
*				:
*				100 -> 1.00
*
* Provider : Telecom / Jesse Pasuri / Mika Hautala
*
************************************************************************/


#endif

