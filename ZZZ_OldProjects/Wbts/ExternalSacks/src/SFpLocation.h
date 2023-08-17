/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Definitions/SFpLocation.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Olgierd Sobinski
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/
#ifndef _SFP_LOCATION_H
#define _SFP_LOCATION_H

#include <TFpId.h>
#include <TAaSysComSicad.h>


struct SFpLocation
{
    TFpId                  fpId;
    TAaSysComSicad         fpAddress;
    TAaSysComSicad         messagingAddress;
};

typedef struct SFpLocation SFpLocation;

#endif /*_SFP_LOCATION_H */

/******************************************************************
* @struct SFpLocation
* SW Block            : Ppc_Env
*
* Description         : A helper structure for STransportBearerRegisterMsg and STransportBearerReallocationPrepareReq. 
*                       Describes a single transport bearer parameters.
*
* Reference           : ATM_CTRL_MCUS_IF_spec.doc, 35.0, sharenet-IMS
*
* Parameters  :
*  @param   fpId            : Frame protocol instance identifier.
*  @param   fpAddress       : The address on which the FP instance is located. 
*  @param   messagingAddress: Address on which TUP CONMAN will sent fp realated messages:
*                             TUP_TRANSPORT_CONNECTION_SETUP_REQ_MSG TUP_TRANSPORT_CONNECTION_RELEASE_REQ_MSG TUP_TRANSPORT_CONNECTION_TRANSFER_REQ. 
*                             See ATM_CTRL_MCUS_IF_spec.doc for more details.
*
* Additional Information    :
* Definition Provided by    : TUP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
**********************************************************************/


