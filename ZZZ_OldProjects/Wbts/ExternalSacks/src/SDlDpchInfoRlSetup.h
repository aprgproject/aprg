/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SDlDpchInfoRlSetup.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef SDLDPCHINFORLSETUP_H
#define SDLDPCHINFORLSETUP_H

#include <TDlDpchSlotFormat.h>
#include <ETfciUsedFlag.h>
#include <EDtxInsertionPosition.h>
#include <TPowerOffsetForTFCIbits.h>
#include <TPowerOffsetForTPCbits.h>
#include <TPowerOffsetForPilotbits.h>
#include <ETpcDlStepSize.h>
#include <ELimitedPowerIncrease.h>
#include <EInnerLoopDLPCStatus.h>

struct SDlDpchInfoRlSetup
{
    TDlDpchSlotFormat                   dlDpchSlotFormat;
    ETfciUsedFlag                       tfciUsedFlag;
    EDtxInsertionPosition               dtxInsertionPosition;
    TPowerOffsetForTFCIbits             powerOffsetForTFCIbits;
    TPowerOffsetForTPCbits              powerOffsetForTPCbits;
    TPowerOffsetForPilotbits            powerOffsetForPilotbits;
    ETpcDlStepSize                      tpcDlStepSize;
    ELimitedPowerIncrease               limitedPowerIncrease;
    EInnerLoopDLPCStatus                innerLoopDlPcStatus;
};
typedef struct SDlDpchInfoRlSetup SDlDpchInfoRlSetup;

#endif /* SDLDPCHINFORLSETUP_H */

/******************************************************************
*
* SW Block            : Nora BTS / BS Env
*
* Description : Includes DL DPCH Information parameters in Radio Link Setup.
*
* Reference   : WCDMA BTS RELEASES BTS RELEASE PROGRAMS
*               DSP SW - MCU SW INTERFACE SPECIFICATION
*
* Parameters  :
*
*   dlDpchSlotFormat                Indicates the slot format used in DPCH in
*                                   DL.
*
*   tfciUsedFlag                    Named as 'TFCI Presence' in IUB. This
*                                   parameter has conditional dependency to the
*                                   Dl DPCH Slotformat. See reference.
*
*   dtxInsertionPosition            Named as 'Multiplexing position' in IUB.
*                                   DTX Insertion Position specifies whether
*                                   fixed or flexible positions of transport
*                                   channels shall be used in the physical
*                                   channel.
*
*   powerOffsetForTFCIbits          Defines a TFCI power offset relative to the
*                                   Downlink transmission power of a data field.
*
*   powerOffsetForTPCbits           Defines a TPC power offset relative to the
*                                   Downlink transmission power of a data field.
*
*   powerOffsetForPilotbits         Defines a Pilot power offset relative to the
*                                   Downlink transmission power of a data field.
*
*   tpcDlStepSize                   This parameter indicates step size for the
*                                   DL power adjustment.
*
*   limitedPowerIncrease            The parameter is used for a more efficient
*                                   use of the inner loop DL power control for
*                                   non real time data.
*
*   innerLoopDlPcStatus             Indicates whether inner loop downlink
*                                   control shall be active or not for all radio
*                                   links associated with this user.
*
* Provider : DSP/Saku Matasaho
*
* Remember to put an empty line in the end of each definition
* file. Otherwise the compiler will generate a warning.
************************************************************************/
