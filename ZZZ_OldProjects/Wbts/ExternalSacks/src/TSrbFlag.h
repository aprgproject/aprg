/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/TSrbFlag.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _TSRB_FLAG_H
#define _TSRB_FLAG_H

#include <glo_def.h>

typedef u32        TSrbFlag;

#endif /* _TSRB_FLAG_H */

/******************************************************************
*
* Description :  Determined by TCOM from MAC-d flow Id = 7, when
*                F-DPCH is in use. Otherwise MAC-d flow Id = 7 
*                does not indicate SRBs and the flag shall not be set.
*
* Reference   :  WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                DSP SW - MCU SW INTERFACE SPECIFICATION
*                Location: Sharenet
*
* Parameters  :
*
*  <additional explanations>
*
* Provider :
*
* Remember to put an empty line in the end of each definition 
* file. Otherwise the compiler will generate a warning.
************************************************************************/

