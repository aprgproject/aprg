/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SUeCapabilitiesInformation.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _SUECAPABILITIESINFORMATION_H
#define _SUECAPABILITIESINFORMATION_H

#include <TPhysicalLayerCategory.h>
#include <TReorderingBufferSize.h>

typedef struct SUeCapabilitiesInformation
{
    TPhysicalLayerCategory  physicalLayerCategory;
    TReorderingBufferSize   reorderingBufSize;
}SUeCapabilitiesInformation;

#endif /* _SUECAPABILITIESINFORMATION_H */

/***********************************************************************
*
* SW Block            : Nora BTS / BS Env
*
* Description : UE Capabilities Information
*
* Reference   : WCDMA BTS RELEASES BTS RELEASE PROGRAMS
*               DSP SW - MCU SW INTERFACE SPECIFICATION
*
* Parameters  :
*
* Provider : DSP, MAC-hs / K.Korvela
*
* Remember to put an empty line in the end of each definition
* file. Otherwise the compiler will generate a warning.
***********************************************************************/


