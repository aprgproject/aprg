/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SDchSpecificInfo.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef SDCHSPECIFICINFO_H
#define SDCHSPECIFICINFO_H

#include <TDchId.h>
#include <TFrameHandlingPriority.h>
#include <EQESelector.h>
#include <SStaticTfInfo.h>
#include <TNumberOfItems.h>
#include <SDynamicTfInfo.h>

struct SDchSpecificInfo
{
    TDchId                        dchId;
    TFrameHandlingPriority        frameHandlingPriority;
    EQESelector                   qESelector;
    SStaticTfInfo                 staticTfInfoUl;
    SStaticTfInfo                 staticTfInfoDl;
    TNumberOfItems                numberOfTfUl;
    TNumberOfItems                numberOfTfDl;
    SDynamicTfInfo                dynamicTfInfo[1];
};
typedef struct SDchSpecificInfo SDchSpecificInfo;

#endif /* SDCHSPECIFICINFO_H */

/******************************************************************
*
* SW Block            : Nora BTS / BS Env
*
* Description : Provides DCH specific information included in DCH information IE
*
* Reference   : WCDMA BTS RELEASES BTS RELEASE PROGRAMS
*               DSP SW - MCU SW INTERFACE SPECIFICATION
*
* Parameters  :
*******************************************
*    Static part
*******************************************
*
*   dchId                           Dedicated Transport Channel ID is the unique
*                                   identifier for one dedicated transport
*                                   channel allocated for a user.
*
*   frameHandlingPriority           Indicates the priority level to be used
*                                   during the lifetime of the DCH for temporary
*                                   restriction of the allocated resources due
*                                   overload reason.
*
*   qESelector                      Indicates from which source the value for
*                                   the quality estimate (QE) shall be taken.
*
*   staticTfInfoUl and
*   staticTfInfoDl                  Includes transport channel encoding
*                                   parameters as txTimeInterval, channelCoding,
*                                   codingRate, rateMatchingAttrib and crcSize.
*
*   numberOfTfUl                    Number of dynamic STransportFormatSet
*                                   structures in the uplink.
*
*   numberOfTfDl                    Number of dynamic STransportFormatSet
*                                   structures in the downlink.
*
*******************************************
*    Dynamic part
*******************************************
*
*   dynamicTfInfo                   Includes numberOfTfUl times
*                                   STransportFormatSets for uplink and after
*                                   they numberOfTfDl times STransportFormatSets
*                                   for downlink.
*
* Provider : DSP/Saku Matasaho
*
* Remember to put an empty line in the end of each definition
* file. Otherwise the compiler will generate a warning.
************************************************************************/
