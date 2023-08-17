/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/ECqiFeedbackCycleK_Ver2.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Tarmo Auvinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_CQI_FEEDBACK_CYCLE_K_VER2_H
#define _E_CQI_FEEDBACK_CYCLE_K_VER2_H

#include <DFromTc_dsp.h>

typedef enum ECqiFeedbackCycleK_Ver2
{
    ECqiFeedbackCycleK_Ver2_0   = 0,
    ECqiFeedbackCycleK_Ver2_2   = 1,
    ECqiFeedbackCycleK_Ver2_4   = 2,
    ECqiFeedbackCycleK_Ver2_8   = 3,
    ECqiFeedbackCycleK_Ver2_10  = 4,
    ECqiFeedbackCycleK_Ver2_20  = 5,
    ECqiFeedbackCycleK_Ver2_40  = 6,
    ECqiFeedbackCycleK_Ver2_80  = 7,
    ECqiFeedbackCycleK_Ver2_160 = 8,
    ECqiFeedbackCycleK_Ver2_16  = 9, 
    ECqiFeedbackCycleK_Ver2_32  = 10,
    ECqiFeedbackCycleK_Ver2_64  = 11,
    ECqiFeedbackCycleK_Ver2_NoValue = NO_VALUE_FOR_ENUMS

} ECqiFeedbackCycleK_Ver2;

#endif /* _E_CQI_FEEDBACK_CYCLE_K_VER2_H */

/***********************************************************************
*
* SW Block            : Nora BTS / BS Env
*
* Description : CQI Feedback Cycle K
*
* Reference   : WCDMA BTS RELEASES BTS RELEASE PROGRAMS
*               DSP SW - MCU SW INTERFACE SPECIFICATION
*
* Parameters  :
*
* Provider : DSP
*
* Remember to put an empty line in the end of each definition
* file. Otherwise the compiler will generate a warning.
***********************************************************************/


