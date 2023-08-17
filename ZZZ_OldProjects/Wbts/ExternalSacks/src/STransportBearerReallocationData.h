/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Definitions/STransportBearerReallocationData.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Olgierd Sobinski
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/
#ifndef _STRANSPORT_BEARER_REALLOCATION_DATA_H
#define _STRANSPORT_BEARER_REALLOCATION_DATA_H

#include <TTransportBearerId.h>
#include <SFpLocation.h>
#include <EBoolean.h>


struct STransportBearerReallocationData
{
	TTransportBearerId     transportBearerId;
	SFpLocation            newFpLocation;
	EBoolean               dataDuplication;
};

typedef struct STransportBearerReallocationData STransportBearerReallocationData;

#endif /* _STRANSPORT_BEARER_REALLOCATION_DATA_H */

/******************************************************************
* @struct STransportBearerReallocationData
* SW Block            : Ppc_Env
*
* Description         : A helper structure for the STransportBearerReallocationPrepareReq.
*
* Reference           : ATM_CTRL_MCUS_IF_spec.doc, ver. 26.0, sharenet-IMS
*
* Parameters  :
*  @param transportBearerId  : Transport bearer identifier.
*  @param newFpLocation      : New (target) FP instance location.
*  @param                    : Indication whether the data duplication should occur during reallocation procedure. 
*                              In some cases i.e. WN7.0 Rel1<=>Rel2 user transfer the data duplication is not performed. See WBTS_CP 12092, WBTS_CP 12102. 
*                              The  information will be transferred to the relevant FP instances within TUP_TRANSPORT_CONNECTION_TRANSFER_REQ message.
*
* Additional Information	:
* Definition Provided by	: TUP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
**********************************************************************/




