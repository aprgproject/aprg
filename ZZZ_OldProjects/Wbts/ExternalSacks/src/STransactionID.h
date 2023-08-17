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

#ifndef _STRANSACTIONID_H
#define _STRANSACTIONID_H


#include <EShortLongChoice.h>
#include <TTransactionID.h>


typedef struct STransactionID {
	
	EShortLongChoice		shortlongchoice;	
	TTransactionID			transactionID;

} STransactionID;

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
*  <additional explanations>
*
* Provider : Telecom / Jesse Pasuri / Mika Hautala
*
************************************************************************/

#endif  /* _STRANSACTIONID_H */

