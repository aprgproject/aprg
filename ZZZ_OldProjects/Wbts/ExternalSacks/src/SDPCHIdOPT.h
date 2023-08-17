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

#ifndef _SDPCHIDOPT_H
#define _SDPCHIDOPT_H


#include <EIEPresentType.h>
#include <TDPCHId.h>


typedef struct SDPCHIdOPT {
	
	EIEPresentType			iePresent;		
	TDPCHId		                dPCHId;
	
} SDPCHIdOPT;

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

#endif  /* _SDPCHIDOPT_H */

