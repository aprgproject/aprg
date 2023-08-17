/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EETti.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        Kristian Ruotsalainen
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _E_ETTI_H
#define _E_ETTI_H

#include <DFromTc_dsp.h>

typedef enum EETti
{
    EETti_2ms     = 0,
    EETti_10ms    = 1,
    EETti_slot    = 2,/*Add for DCM product, Guibing, Gu. Jan, 2012*/
    EETti_NoValue = NO_VALUE_FOR_ENUMS
} EETti;

#endif /* _E_ETTI_H */

/**
*******************************************************************************
* @enum EETti
*
* Description         : 9.2.2.13Di E-TTI
*
* Reference           : 3GPP TS 25.433 v6.6.0
*
* Parameters :
*
* @param EETti_2ms  : 2ms
* @param EETti_10ms : 10ms
* @param EETti_slot :
* @param EETti_NoValue : "This IE is not present."
*
* Additional Information :  N/A
*
* Definition Provided by : Telecom, Kristian Ruotsalainen
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/


