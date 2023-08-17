/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EHsDschMacdPduSizeFormat.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Krzysztof Michalak
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_HSDSCH_MACD_PDU_SIZE_FORMAT_H
#define _E_HSDSCH_MACD_PDU_SIZE_FORMAT_H

#include <DFromTc_dsp.h>

typedef enum EHsDschMacdPduSizeFormat 
{
  EHsDschMacdPduSizeFormat_Indexed    = 0,
  EHsDschMacdPduSizeFormat_Flexible   = 1,
  EHsDschMacdPduSizeFormat_NoValue    = NO_VALUE_FOR_ENUMS

} EHsDschMacdPduSizeFormat;
  

#endif  /* _E_HSDSCH_MACD_PDU_SIZE_FORMAT_H */

/******************************************************************************
* @enum EHsDschMacdPduSizeFormat
* Description         : HS-DSCH MAC-d PDU Size Format IE
*
* Reference           : WCDMA BTS SW DSP SW - MCU SW INTERFACE SPECIFICATION
**
* Additional Information : <type additional information if needed>
*
* Definition Provided by : DSP
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/

