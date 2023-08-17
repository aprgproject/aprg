/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/ETransportBearReqInd.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_TRANSPORT_BEAR_REQ_IND_H
#define _E_TRANSPORT_BEAR_REQ_IND_H

#include <DFromTc_dsp.h>

typedef enum ETransportBearReqInd
{
    ETransportBearReqInd_BearerRequested         = 0,
    ETransportBearReqInd_BearerNotRequested      = 1,
    ETransportBearReqInd_NoValue                 = NO_VALUE_FOR_ENUMS
}ETransportBearReqInd;

#endif /* _E_TRANSPORT_BEAR_REQ_IND_H */

/***********************************************************************
* @enum ETransportBearReqInd
* Description         : Indicates whether a new transport bearer needs
*                       to be established for carrying the concerned
*                       transport channel.
*
* Reference           : WCDMA BTS RELEASES BTS RELEASE PROGRAMS,
*                       DSP SW - MCU SW INTERFACE SPECIFICATION
*                       Location: Sharenet
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/


