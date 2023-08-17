/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SAal2Tp.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _S_AAL2_TP_H
#define _S_AAL2_TP_H

#include <TAal2TpIdentification.h>
#include <CoreTypes.h>
#include <TPathId.h>
#include <TAal2DataRate.h>
#include <TTransportLayerAddress.h>
#include <EAal2UpUsage.h>
#include <glo_def.h>

struct SAal2Tp
{
    TAal2TpIdentification   aal2TpId;
    TCpu                    atmMcuAddress;
    u8                      pad1;
    u8                      pad2;
    u8                      pad3;
    TPathId                 aal2PathId;
    TAal2DataRate           aal2DataRate;
    TTransportLayerAddress  transportLayerAddress;
    EAal2UpUsage            aal2UserPlaneUsage;
};
typedef struct SAal2Tp SAal2Tp;

#endif /* _S_AAL2_TP_H */

/**
*******************************************************************************
* @struct SAal2Tp
*
* Description :
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* @param aal2TpId              : AAL2 TP identifier
* @param atmMcuAddress         : cpu address this AAL2TP is mapped to
* @param pad1                  :
* @param pad2                  :
* @param pad3                  :
* @param aal2PathId            : AAL2 Path Id
* @param aal2DataRate          : cell rates for AAL2 user plane
*                                connections in cells/second(1 cell/sec = 53 bytes/sec)
* @param transportLayerAddress : Transportlayer address
* @param aal2UserPlaneUsage    : AAL2 user plane usage
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



