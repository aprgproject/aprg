/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SCmTransGapPatternSeqInfo.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef SCMTRANSGAPPATTERNSEQINFO_H
#define SCMTRANSGAPPATTERNSEQINFO_H

#include <TTransGapPatternSeqId.h>
#include <TSlot.h>
#include <TTransGapLength.h>
#include <TTransGapDistance.h>
#include <TTransGapPatternLength.h>
#include <ECmModeSelect.h>
#include <ECmDlMethod.h>
#include <ECmUlMethod.h>
#include <ECmDlFrameType.h>
#include <TDeltaSir.h>

struct SCmTransGapPatternSeqInfo
{
    TTransGapPatternSeqId   transGapPatternSeqId;
    TSlot                   transGapStartSlotNum;
    TTransGapLength         transGapLength1;
    TTransGapLength         transGapLength2;
    TTransGapDistance       transGapDistance;
    TTransGapPatternLength  transGapPatternLength1;
    TTransGapPatternLength  transGapPatternLength2;
    ECmModeSelect           cmModeSelection;
    ECmDlMethod             cmDlMethod;
    ECmUlMethod             cmUlMethod;
    ECmDlFrameType          cmDlFrameType;
    TDeltaSir               deltaSIR1;
    TDeltaSir               deltaSIRafter1;
    TDeltaSir               deltaSIR2;
    TDeltaSir               deltaSIRafter2;
};

typedef struct SCmTransGapPatternSeqInfo SCmTransGapPatternSeqInfo;

#endif /*SCMTRANSGAPPATTERNSEQINFO_H*/

/******************************************************************
*
* SW Block            : Nora BTS / BS Env
*
* Description : Structure including CM pattern sequence information
*               parameters
*
* Reference   : WCDMA BTS RELEASES BTS RELEASE PROGRAMS
*               DSP SW - MCU SW INTERFACE SPECIFICATION
*
* Parameters  :
*
*   transGapPatternSeqId    ID of the transmission gap pattern sequence.
*
*   transGapStartSlotNum    Slot number of the 1st transmission gap slot.
*
*   transGapLength1         Length of the 1st transmission gap in number of
*                           slots.
*
*   transGapLength2         Length of the 2nd transmission gap in number of
*                           slots.
*
*   transGapDistance        Indicates the number of slots between the starting
*                           slots of two consecutive transmission gaps within a
*                           transmission gap pattern..
*
*   transGapPatternLength1  Duration of transmission gap pattern 1 in frames.
*
*   transGapPatternLength2  Duration of transmission gap pattern 2 in frames.
*
*   cmModeSelection         Defines whether only DL, only UL or combined UL/DL
*                           compressed mode is used.
*
*   cmDlMethod              Used CM method in DL.
*
*   cmUlMethod              Used CM method in UL.
*
*   cmDlFrameType           Defines which frame structure type shall be
*                           used in downlink compressed mode.
*
*   deltaSIR1;              Delta in SIR target value to be set in the Node B
*                           during the frame containing the start of the first
*                           transmission gap in the transmission gap pattern
*                           (without including the effect of the bit-rate
*                           increase).
*
*   deltaSIRafter1          Delta in SIR target value to be set in the Node B
*                           one frame after the frame containing the start of
*                           the first transmission gap in the transmission gap
*                           pattern.
*
*   deltaSIR2;              Delta in SIR target value to be set in the Node B
*                           during the frame containing the start of the second
*                           transmission gap in the transmission gap pattern
*                           (without including the effect of the bit-rate
*                           increase).
*
*   deltaSIRafter2          Delta in SIR target value to be set in the Node B
*                           one frame after the frame containing the start of
*                           the second transmission gap in the transmission gap
*                           pattern.
*
* Provider : DSP/Saku Matasaho
*
* Remember to put an empty line in the end of each definition
* file. Otherwise the compiler will generate a warning.
************************************************************************/
