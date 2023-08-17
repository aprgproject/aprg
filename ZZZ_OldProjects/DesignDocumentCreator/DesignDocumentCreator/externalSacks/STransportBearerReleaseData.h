/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Definitions/STransportBearerReleaseData.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Olgierd Sobinski
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/
#ifndef _STRANSPORT_BEARER_RELEASE_DATA_H
#define _STRANSPORT_BEARER_RELEASE_DATA_H

#include <TTransportBearerId.h>
#include <TTransactionID.h>


struct STransportBearerReleaseData
{
	TTransportBearerId     transportBearerId;
	TTransactionID         transactionId;
};

typedef struct STransportBearerReleaseData STransportBearerReleaseData;

#endif /* _STRANSPORT_BEARER_RELEASE_DATA_H */

/******************************************************************
* @struct STransportBearerReleaseData
* SW Block            : Ppc_Env
*
* Description         : A helper structure for STransportBearerRegisterMsg and STransportBearerReallocationPrepareReq. 
*				        Describes a single transport bearer parameters.
*
* Reference           : ATM_CTRL_MCUS_IF_spec.doc, ver.26.0, sharenet-IMS
*
* Parameters  :
*  @param transportBearerId : Transport bearer identifier.
*  @param transactionId     : Transaction ID passed by TELECOM for transport bearer in TC_TRANSPORT_BEARER_REGISTER_MSG 
*
* Additional Information	:
* Definition Provided by	: TUP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
**********************************************************************/




