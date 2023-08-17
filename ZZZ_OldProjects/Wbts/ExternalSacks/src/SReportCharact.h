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

#ifndef _SREPORTCHARACT_H
#define _SREPORTCHARACT_H

#include <EReportCharactChoice.h>
#include <SPeriodic.h>
#include <SEvent.h>
#include <SEvent2.h>
#include <SEvent3.h>
#include <SOnModification.h>

typedef struct SReportCharact {
 	
	EReportCharactChoice                    choiceReportCharact;
        SPeriodic                               periodicChoice;
	SEvent                                  eventAChoice;
	SEvent                                  eventBChoice;
	SEvent2                                 eventCChoice;
	SEvent2                                 eventDChoice;
	SEvent3                                 eventEChoice;
	SEvent3                                 eventFChoice;
	SOnModification                         onModificationChoice;

} SReportCharact;

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description : 9.2.1.51 Report Characteristics. 
*               "The report characteristics, defines how the reporting
*                shall be performed.
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

#endif  /* _SREPORTCHARACT_H */

