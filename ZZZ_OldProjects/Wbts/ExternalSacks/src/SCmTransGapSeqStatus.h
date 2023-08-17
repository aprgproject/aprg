/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SCmTransGapSeqStatus.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef SCMTRANSGAPSEQSTATUS_H
#define SCMTRANSGAPSEQSTATUS_H

#include <TTransGapPatternSeqId.h>
#include <TTransGapPatternRepeat.h>
#include <TSfn.h>

struct SCmTransGapSeqStatus
{
    TTransGapPatternSeqId   transGapPatternSeqId;
    TTransGapPatternRepeat  transGapPatternRepeat;
    TSfn                    transGapFrameNumber;
};

typedef struct SCmTransGapSeqStatus SCmTransGapSeqStatus;

#endif /* SCMTRANSGAPSEQSTATUS_H */

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
*   transGapPatternSeqId    ID of the transmission gap pattern sequence.
*
*   transGapPatternRepeat   Identifies the number of transmission gap patterns
*                           within the Transmission Gap Pattern Sequence.
*
*   transGapFrameNumber     System Frame Number of the first frame with gap of
*                           the first pattern 1 within the Transmission Gap
*                           Pattern Sequence.
*
* Provider : DSP/Saku Matasaho
*
* Remember to put an empty line in the end of each definition
* file. Otherwise the compiler will generate a warning.
************************************************************************/
