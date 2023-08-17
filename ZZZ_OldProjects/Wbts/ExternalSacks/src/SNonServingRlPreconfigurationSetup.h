/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SNonServingRlPreconfigurationSetup.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Wang Xiaojiang
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_NON_SERVING_RL_PRECONFIGURATION_SETUP_H
#define _S_NON_SERVING_RL_PRECONFIGURATION_SETUP_H

#include <ENewServingRl.h>
#include <TNumberOfItems.h>

struct SNonServingRlPreconfigurationSetup 
{
    ENewServingRl        newServingRl;
    TNumberOfItems       addiEdchNonServingRlPreconfigSetup;
};
typedef struct SNonServingRlPreconfigurationSetup SNonServingRlPreconfigurationSetup;

#endif /* _S_NON_SERVING_RL_PRECONFIGURATION_SETUP_H */

/******************************************************************
* @struct SNonServingRlPreconfigurationSetup
* Description         : Non-Serving RL Preconfiguration Setup.
*                       This IE indicates that the Node B may preconfigure 
*                       E-DCH DL Code Information configured for new non-serving 
*                       RL for Enhanced Service Cell Change and contains the information 
*                       for the location of new serving RL after the Enhanced Serving Cell Change.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* @param newServingRl :
*                       Indicate Master HSUPA L2 preconfigures E-DCH for non-serving RL 
*                       in Intra or Inter BTS 
*
* @param addiEDCHNonServingRLPreconfigSetup : 
*                       Master HSUPA L2 preconfigures E-DCH for non-serving RL of Secondary Carriers
*                       for Enhanced Service Cell Change.
*                       If this IE is not present value 0 is used.
*
* Additional Information : -
*
* Definition Provided by : DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/

