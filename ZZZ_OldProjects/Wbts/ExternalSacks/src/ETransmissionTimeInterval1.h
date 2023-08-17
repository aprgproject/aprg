/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/ETransmissionTimeInterval1.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _ETRANSMISSIONTIMEINTERVAL1_H
#define _ETRANSMISSIONTIMEINTERVAL1_H

typedef enum ETransmissionTimeInterval1
{
    ETransmissionTimeInterval1_10       = 0,
    ETransmissionTimeInterval1_20       = 1,
    ETransmissionTimeInterval1_40       = 2,
    ETransmissionTimeInterval1_80       = 3,
    ETransmissionTimeInterval1_dynamic  = 4,
    ETransmissionTimeInterval1_5        = 5
} ETransmissionTimeInterval1;

#endif /* _ETRANSMISSIONTIMEINTERVAL1_H */

/**
*******************************************************************************
* @enum ETransmissionTimeInterval1
*
* Description : Transmission time interval.
*
* Reference   : 3GPP TS 25.433 v4.1.0
*
* IE type and reference:ENUMERATED(10, 20, 40, 80, dynamic,...,5)
*
* Semantics description: ms Value "dynamic" for TDD only Value "5" for LCR TDD only
*
* Parameters :
*
* @param ETransmissionTimeInterval1_10 :
* @param ETransmissionTimeInterval1_20 :
* @param ETransmissionTimeInterval1_40 :
* @param ETransmissionTimeInterval1_80 :
* @param ETransmissionTimeInterval1_dynamic :
* @param ETransmissionTimeInterval1_5 :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom / Jesse Pasuri / Mika Hautala
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



