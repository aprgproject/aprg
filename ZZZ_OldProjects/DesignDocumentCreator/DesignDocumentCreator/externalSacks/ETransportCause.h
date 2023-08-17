/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/ETransportCause.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_TRANSPORT_CAUSE_H
#define _E_TRANSPORT_CAUSE_H

#include <DFromTc_dsp.h>

typedef enum ETransportCause
{
    ETransportCause_NoCause                   = 0,
    ETransportCause_UndefinedCause            = 1,
    ETransportCause_UnknownFPid               = 2,
    ETransportCause_CannotOpenSocket          = 3,
    ETransportCause_NoSuchTransportConection  = 4,
    ETransportCause_CannotCloseSocket         = 5

} ETransportCause;

#endif /* _E_TRANSPORT_CAUSE_H */

/******************************************************************************
@enum ETransportCause
*
* Description         : Cause codes used in transport procedures.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: ShareNet
*
* Additional Information :
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/

