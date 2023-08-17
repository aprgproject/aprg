/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Original author        <nn>
*
* Copyright 2012 Nokia Siemens Networks. All rights reserved.
*******************************************************************************/

#ifndef _SDEDMEASINITREQ3G_H
#define _SDEDMEASINITREQ3G_H


#include <SMessageHeader.h>
#include <TNbccId.h>
#include <STransactionID.h>
#include <TMeasurementID.h>
#include <EDedMeasurObjType.h>
#include <SDMIRRL.h>
#include <SDMIRRLS.h>
#include <EDedMeasurType.h>
#include <SMeasurFilterCoefOPT.h>
#include <SReportCharact.h>
#include <ECFNReportInd.h>
#include <SCFNOPT.h>
#include <EAlternativeFormatReportInd.h>


typedef struct SDedMeasInitReq3G {
 	
	MESSAGEHEADER(msgHeader)
	TNbccId            	        nodeBCommunicationContextId;	
	STransactionID				transactionID;
	TMeasurementID				measurementID;
	EDedMeasurObjType           choiceMeasurementObjType;
    SDMIRRL                     rlchoice;
    SDMIRRLS                    rlSetchoice;
	EDedMeasurType              dedMeasurementType;
	SMeasurFilterCoefOPT        measurFilterCoef;/* Optional */
	SReportCharact              reportCharact;
	ECFNReportInd               cFNReportInd;
	SCFNOPT                     cFN;/* Optional */
  EAlternativeFormatReportInd             alternativeFormat;/* Optional */
  
} SDedMeasInitReq3G;

#endif  /* _SDEDMEASINITREQ3G_H */

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Ppc Env / Telecom / Messages
*
* Description : 9.1.52	DEDICATED MEASUREMENT INITIATION REQUEST.
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


