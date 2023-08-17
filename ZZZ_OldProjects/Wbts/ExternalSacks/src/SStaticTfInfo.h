/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SStaticTfInfo.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef SSTATICTFINFO_H
#define SSTATICTFINFO_H

#include <ETxTimeInterval.h>
#include <EChannelCoding.h>
#include <ECodingRate.h>
#include <TRateMatchingAttrib.h>
#include <ECrcSize.h>


struct SStaticTfInfo
{
    /********************************************************
    * Static part											*
    ********************************************************/
    /* Semi-static part */
    ETxTimeInterval         txTimeInterval;
    EChannelCoding          channelCoding;
    ECodingRate             codingRate;
    TRateMatchingAttrib     rateMatchingAttrib;
    ECrcSize                crcSize;
};
typedef struct SStaticTfInfo SStaticTfInfo;


/******************************************************************
*
* SW Block            : Nora BTS / BS Env
*
* Description :
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*  Definition is based on Iub Interface Specification version 3.2.0
*
*  <additional explanations>
*
* Provider :
*
* Remember to put an empty line in the end of each definition 
* file. Otherwise the compiler will generate a warning.
************************************************************************/
 
#endif

