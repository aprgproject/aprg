/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SFNSFNObservedTimeDifference.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _SFNSFNOBSERVEDTIMEDIFFERENCE_H
#define _SFNSFNOBSERVEDTIMEDIFFERENCE_H


#include <SSFNSFNChangeLimitOPT.h>
#include <SPredictSFNSFNDeviatLimOPT.h>


typedef struct SFNSFNObservedTimeDifference {
 	
	SSFNSFNChangeLimitOPT                   sFNSFNChangeLimit;/* Optional */
        SPredictSFNSFNDeviatLimOPT              predictSFNSFNDeviatLim;/* Optional */

} SFNSFNObservedTimeDifference;

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description : 9.2.1.53C SFN-SFN Measurement Threshold Information. 
*               "The SFN-SFN Measurement Threshold Information defines the
*                related thresholds SFN-SFN Observed Time Difference
*                measurments which shall trigger the Event On Modification."
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
*  <additional explanations>
*
* Provider : Telecom / Jesse Pasuri / Mika Hautala
*
************************************************************************/

#endif  /* _SFNSFNOBSERVEDTIMEDIFFERENCE_H */

