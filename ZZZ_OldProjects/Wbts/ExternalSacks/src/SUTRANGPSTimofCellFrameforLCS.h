/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SUTRANGPSTimofCellFrameforLCS.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _SUTRANGPSTIMOFCELLFRAMEFORLCS_H
#define _SUTRANGPSTIMOFCELLFRAMEFORLCS_H

#include <STUTRANGPSChangeLimitOPT.h>
#include <SPredictTUTRANGPSDeviatLimOPT.h>

typedef struct SUTRANGPSTimofCellFrameforLCS {
 	
	STUTRANGPSChangeLimitOPT                   tUTRANGPSChangeLimit;/* Optional */
        SPredictTUTRANGPSDeviatLimOPT              predictTUTRANGPSDeviatLim;/* Optional */

} SUTRANGPSTimofCellFrameforLCS;

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description : 9.2.1.64B TUTRAN-GPS Measurement Threshold Information. 
*               "The TUTRAN-GPS Measurement Threshold Information defines
*                the related thresholds for  UTRAN GPS Timing of Cell
*                Frame for LCS measurments shall shall trigger the event
*                On Modification."
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

#endif  /* _SUTRANGPSTIMOFCELLFRAMEFORLCS_H */

