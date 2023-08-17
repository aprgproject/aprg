/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/TEDchProcessingOverloadLevel.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _TEDCH_PROCESSING_OVERLOAD_LEVEL_H
#define _TEDCH_PROCESSING_OVERLOAD_LEVEL_H

#include <glo_def.h>

typedef u32      TEDchProcessingOverloadLevel;

#endif /* _TEDCH_PROCESSING_OVERLOAD_LEVEL_H */

/******************************************************************
* @typedef TEDchProcessingOverloadLevel
* Description :  Number of consecutive TTIs.
*                The value '0' is a special value that means infinity, 
*                i.e. when this value is used, the Node B shall never 
*                indicate processing issue to the RNC.
*
* Reference   :  WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                DSP SW - MCU SW INTERFACE SPECIFICATION
*                Location: Sharenet
*
* Additional Information : -
*
* Definition Provided by : DSP
*
* Remember to put an empty line in the end of each definition 
* file. Otherwise the compiler will generate a warning.
************************************************************************/

