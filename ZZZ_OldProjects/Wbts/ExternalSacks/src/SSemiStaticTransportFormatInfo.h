/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SSemiStaticTransportFormatInfo.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _SSEMISTATICTRANSPORTFORMATINFO_H
#define _SSEMISTATICTRANSPORTFORMATINFO_H

#include <ETransmissionTimeInterval1.h>
#include <ETypeOfChannelCoding.h>
#include <SCodingRateCOND.h>
#include <TRateMatchingAttrib.h>
#include <ECrcSize.h>

typedef struct SSemiStaticTransportFormatInfo
{
    ETransmissionTimeInterval1 transmissionTimeInterval;
    ETypeOfChannelCoding       typeOfChannelCoding;
    SCodingRateCOND            codingRate;
    TRateMatchingAttrib        rateMatchingAttrib;
    ECrcSize                   crcSize;
} SSemiStaticTransportFormatInfo;

#endif /* _SSEMISTATICTRANSPORTFORMATINFO_H */

/**
*******************************************************************************
* @struct SSemiStaticTransportFormatInfo
*
* Description :
*
* Reference   : 3GPP TS 25.433 v4.1.0
*
* Parameters  :
*
* @param transmissionTimeInterval : Time Interval for Transmission
*
* @param typeOfChannelCoding      : Choice for codingRate
*
* @param codingRate               : This IE is only present if IE "Type of channel coding"
*                                   is "Convolutional" or "Turbo"
*
* @param rateMatchingAttrib       : Rate Matching Attributes
*
* @param crcSize                  : CRC Size
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom / Jesse Pasuri / Mika Hautala
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



