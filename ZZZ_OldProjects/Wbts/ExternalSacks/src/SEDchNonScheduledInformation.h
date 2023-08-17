/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SEDchNonScheduledInformation.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Kari Korvela
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_EDCH_NON_SCHEDULED_INFORMATION_H
#define _S_EDCH_NON_SCHEDULED_INFORMATION_H

#include <TNumberOfItems.h>
#include <THarqProcessAllocation.h>

struct SEDchNonScheduledInformation
{
    TNumberOfItems          maxNumOfBitsPerMacEPdu;
    THarqProcessAllocation  harqProcAllocFor2msTxGrant;
};

typedef struct SEDchNonScheduledInformation SEDchNonScheduledInformation;

#endif /* _S_EDCH_NON_SCHEDULED_INFORMATION_H */

/***********************************************************************
* @struct SEDchNonScheduledInformation
* Description         : Information of E-DCH Non-Scheduled.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION,
*                       version 13.6, location: PI
*
* @param maxNumOfBitsPerMacEPdu     : Maximum Number of Bits per MAC-e PDU for Non-scheduled Transmission
* @param harqProcAllocFor2msTxGrant : HARQ Process Allocation For 2ms Non-Scheduled Transmission Grant
*
* Additional Information :
*
* Definition Provided by : DSP, Kari Korvela
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/
