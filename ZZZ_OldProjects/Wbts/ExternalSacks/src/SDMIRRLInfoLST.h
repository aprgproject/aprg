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

#ifndef _SDMIRRLINFOLST_H
#define _SDMIRRLINFOLST_H


#include <TRadioLinkId.h>
#include <SDPCHIdOPT.h>
#include <SPUSCHIDOPTLST.h>


typedef struct SDMIRRLInfoLST {
    
	TRadioLinkId				radioLinkId;
	SDPCHIdOPT                              dPCHId;/* Optional */
	SPUSCHIDOPTLST			        pUSCHID;/* Optional */
	
} SDMIRRLInfoLST;

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description : Radio Link Information.
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

#endif  /* _SDMIRRLINFOLST_H */

