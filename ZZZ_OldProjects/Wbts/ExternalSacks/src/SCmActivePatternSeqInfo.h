/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SCmActivePatternSeqInfo.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef SCMACTIVEPATTERNSEQINFO_H
#define SCMACTIVEPATTERNSEQINFO_H

#include <TSfn.h>
#include <TNumberOfItems.h>
#include <SCmTransGapSeqStatus.h>

struct SCmActivePatternSeqInfo
{
    TSfn                        cmConfigurationChangeSfn;
    TNumberOfItems              numOfCmTransGapSeqStatus;
    SCmTransGapSeqStatus        dynamicCmTransGapSeqStatus[1];
};

typedef struct SCmActivePatternSeqInfo SCmActivePatternSeqInfo;

#endif /*SCMACTIVEPATTERNSEQINFO_H*/

/******************************************************************
*
* SW Block            : Nora BTS / BS Env
*
* Description : Structure including the parameters for the
*               Compressed Mode gap pattern sequence activation
*
* Reference   : WCDMA BTS RELEASES BTS RELEASE PROGRAMS
*               DSP SW - MCU SW INTERFACE SPECIFICATION
*
* Parameters  :
*
*   cmConfigurationChangeSfn        Defines in which SFN compressed mode active
*                                   patterns are activated. Activation
*                                   completes in next approppriate SFN.
*
*   numOfCmTransGapSeqStatus        Defines Number of SCmTransGapSeqStatus
*                                   struct(s) included in dynamicData.
*
*   SCmTransGapSeqStatus            OPTIONAL. Defines transmission gap pattern
*                                   sequences belonging to Active Pattern
*                                   Sequence Information.
*
* Provider : DSP/Saku Matasaho
*
* Remember to put an empty line in the end of each definition
* file. Otherwise the compiler will generate a warning.
************************************************************************/
