/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EUlDpcchSlotFormat.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _E_UL_DPCCH_SLOT_FORMAT_H
#define _E_UL_DPCCH_SLOT_FORMAT_H

typedef enum EUlDpcchSlotFormat
{
    EUlDpcchSlotFormat_0  =  0,
    EUlDpcchSlotFormat_1  =  1,
    EUlDpcchSlotFormat_2  =  2,
    EUlDpcchSlotFormat_3  =  3,
    EUlDpcchSlotFormat_4  =  4,
    EUlDpcchSlotFormat_5  =  5,
    EUlDpcchSlotFormat_0A =  6,
    EUlDpcchSlotFormat_0B =  7,
    EUlDpcchSlotFormat_2A =  8,
    EUlDpcchSlotFormat_2B =  9,
    EUlDpcchSlotFormat_5A = 10,
    EUlDpcchSlotFormat_5B = 11
} EUlDpcchSlotFormat;

#endif /* _E_UL_DPCCH_SLOT_FORMAT_H */

/**
*******************************************************************************
* @enum EUlDpcchSlotFormat
*
* Possible uplink DPCCH slot formats.
*
* Description : DPCCH uplink slot formats
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* @param EUlDpcchSlotFormat_0 :  This slot format contains 6 pilot bits,
*                                2 TPC bits, 2 TFCI bits, and 0 FBI bits.
* @param EUlDpcchSlotFormat_1 :  This slot format contains 8 pilot bits,
*                                2 TPC bits, 0 TFCI bits, and 0 FBI bits.
* @param EUlDpcchSlotFormat_2 :  This slot format contains 5 pilot bits,
*                                2 TPC bits, 2 TFCI bits, and 1 FBI bit.
* @param EUlDpcchSlotFormat_3 :  This slot format contains 7 pilot bits,
*                                2 TPC bits, 0 TFCI bits, and 1 FBI bit.
* @param EUlDpcchSlotFormat_4 :  This slot format contains 6 pilot bits,
*                                2 TPC bits, 0 TFCI bits, and 2 FBI bits.
* @param EUlDpcchSlotFormat_5 :  This slot format contains 5 pilot bits,
*                                1 TPC bit, 2 TFCI bits, and 2 FBI bits.
* @param EUlDpcchSlotFormat_0A : This compressed mode slot format contains
*                                5 pilot bits, 2 TPC bits, 3 TFCI bits, and 0 FBI bits.
* @param EUlDpcchSlotFormat_0B : This compressed mode slot format contains
*                                4 pilot bits, 2 TPC bits, 4 TFCI bits, and 0 FBI bits.
* @param EUlDpcchSlotFormat_2A : This compressed mode slot format contains
*                                4 pilot bits, 2 TPC bits, 3 TFCI bits, and 1 FBI bit.
* @param EUlDpcchSlotFormat_2B : This compressed mode slot format contains
*                                3 pilot bits, 2 TPC bits, 4 TFCI bits, and 1 FBI bit.
* @param EUlDpcchSlotFormat_5A : This compressed mode slot format contains
*                                4 pilot bits, 1 TPC bit, 3 TFCI bits, and 2 FBI bits.
* @param EUlDpcchSlotFormat_5B : This compressed mode slot format contains
*                                3 pilot bits, 1 TPC bit, 4 TFCI bits, and 2 FBI bits.
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



