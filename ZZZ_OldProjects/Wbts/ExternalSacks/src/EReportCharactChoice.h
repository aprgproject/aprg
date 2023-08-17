/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EReportCharactChoice.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Asko Rauhala
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_REPORT_CHARACT_CHOICE_H
#define _E_REPORT_CHARACT_CHOICE_H

typedef enum EReportCharactChoice
{
    EReportCharactChoice_OnDemand       = 0,
    EReportCharactChoice_Periodic       = 1,
    EReportCharactChoice_EventA         = 2,
    EReportCharactChoice_EventB         = 3,
    EReportCharactChoice_EventC         = 4,
    EReportCharactChoice_EventD         = 5,
    EReportCharactChoice_EventE         = 6,
    EReportCharactChoice_EventF         = 7,
    EReportCharactChoice_OnModification = 8,
    EReportCharactChoice_EventZ         = 0xF,
        
    EReportCharactChoice_Any            = 0xFF
    
} EReportCharactChoice;

#endif /* _E_REPORT_CHARACT_CHOICE_H */

/******************************************************************
* @enum EReportCharactChoice
* Description : Measurement Characteristics Choice.
*
* Reference   : DSP_SW_MCU_SW_INTERFACE_SPEC.DOC version 12.1
*               3GPP TS 25.433 v4.1.0
*
* @param EMyEnumeration_TheParameterName1  :
* @param EReportCharactChoice_OnDemand  : On Demand measurement
* @param EReportCharactChoice_Periodic  : Periodic measurement
* @param EReportCharactChoice_EventA    : Event A measurement type
* @param EReportCharactChoice_EventB    : Event B measurement type
* @param EReportCharactChoice_EventC    : Event C measurement type
* @param EReportCharactChoice_EventD    : Event D measurement type
* @param EReportCharactChoice_EventE    : Event E measurement type
* @param EReportCharactChoice_EventF    : Event F measurement type
* @param EReportCharactChoice_OnModification : -
* @param EReportCharactChoice_EventZ    : Nokia specific event Z measurement type
* @param EReportCharactChoice_Any       : Used when Measurement Characteristics Choice 
*                                         not known or with ECommonMeasurType_TerminateAll
*                                         to terminate all common measurements of sender.
*
* Additional Information : -
*
* Definition Provided by : Telecom/Jesse Pasuri/Mika Hautala; DSP/Timo Ronkko
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/


