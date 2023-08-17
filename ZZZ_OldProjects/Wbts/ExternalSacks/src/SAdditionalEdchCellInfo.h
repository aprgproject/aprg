/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SAdditionalEdchCellInfo.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_ADDITIONAL_EDCH_CELL_INFO_H
#define _S_ADDITIONAL_EDCH_CELL_INFO_H

#include <EMulticellEdchTpBearMode.h>
#include <TNumberOfItems.h>
#include <SAdditionalEdchCellInfoSetup.h>
#include <DOpenIUBCommonDefs.h>

struct SAdditionalEdchCellInfo
{
    EMulticellEdchTpBearMode            multicellEdchTpBearMode;
    TNumberOfItems                      numOfAdditionalEdchCellInfoSetup;
    SAdditionalEdchCellInfoSetup        additionalEdchCellInfoSetup[MAX_NR_OF_EDCH-1];
};
typedef struct SAdditionalEdchCellInfo SAdditionalEdchCellInfo;

#endif /* _S_ADDITIONAL_EDCH_CELL_INFO_H */

/**
****************************************************************************
* @struct SAdditionalEdchCellInfo
* Description         : This IE is not present if # of Additional E-DCH Cell Information IE has been set to '0'.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param multicellEdchTpBearMode :
*   Indicates the Multicell E-DCH Transport Bearer Mode. For Multicell E-DCH Transport Bearer Mode
*   = "Separate Iub Transport Bearer Mode" the Mac-d flows from each carrier uses different Iub transport bearers,
*   for Multicell E-DCH Transport Bearer Mode  = "UL Flow Multiplexing Mode" the Mac-d flows received on the
*   different carriers in the Node B is multiplexed on one Iub transport bearer (per Mac-d flow).
*
* @param numOfAdditionalEdchCellInfoSetup :
*   Defines Number of SAdditionalEdchCellInfoSetup struct(s).
*
* @param additionalEdchCellInfoSetup : 
*   E-DCH on Secondary uplink frequency.
*
*
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

