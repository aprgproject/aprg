/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EEdchMacdPduSizeFormat.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_EDCH_MACD_PDU_SIZE_FORMAT_H
#define _E_EDCH_MACD_PDU_SIZE_FORMAT_H

#include <DFromTc_dsp.h>

typedef enum EEdchMacdPduSizeFormat
{
    EEdchMacdPduSizeFormat_Fixed                   = 0,
    EEdchMacdPduSizeFormat_Flexible                = 1,
    EEdchMacdPduSizeFormat_NoValue                 = NO_VALUE_FOR_ENUMS
}EEdchMacdPduSizeFormat;

#endif /* _E_EDCH_MACD_PDU_SIZE_FORMAT_H */


/***********************************************************************
* @enum EEdchMacdPduSizeFormat
* Description         : The E-DCH MAC-d PDU Size Format IE provides
*                       information about the type of MAC-d PDU Size Format
*                       that shall be used for the E-DCH in the new configuration.
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

