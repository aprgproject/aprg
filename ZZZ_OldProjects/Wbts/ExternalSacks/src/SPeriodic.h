/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SPeriodic.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _SPERIODIC_H
#define _SPERIODIC_H

#include <EReportPeriodicity.h>
#include <TmSec.h>
#include <TMin.h>

typedef struct SPeriodic {

        EReportPeriodicity              reportPeriodicityChoice;
        TmSec                           milSec;
        TMin                            min;

} SPeriodic;

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description :
*
* Reference   : 3GPP TS 25.433 v4.1.0
*
* Parameters  :
* 	typeOne		<explanation>
*
* 	structOne	<explanation>
*
* 	typeTwo		<explanation>
*
* Provider : Telecom / Jesse Pasuri / Mika Hautala
*
************************************************************************/

#endif  /* _SPERIODIC_H */

