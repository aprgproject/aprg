/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EUarfcnBand.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Bartosz Ciesla
*
* Copyright 2012 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_UARFCN_BAND_H
#define _E_UARFCN_BAND_H

typedef enum EUarfcnBand
{
  EUarfcnBand_I       = 0,
  EUarfcnBand_II      = 1,
  EUarfcnBand_III     = 2,
  EUarfcnBand_IV      = 3,
  EUarfcnBand_V       = 4,
  EUarfcnBand_VI      = 5,
  EUarfcnBand_VII     = 6,
  EUarfcnBand_VIII    = 7,
  EUarfcnBand_IX      = 8,
  EUarfcnBand_X       = 9,
  EUarfcnBand_XI      = 10,
  EUarfcnBand_XII     = 11,
  EUarfcnBand_XIII    = 12,
  EUarfcnBand_XIV     = 13,
  EUarfcnBand_XV      = 14,
  EUarfcnBand_XVI     = 15,
  EUarfcnBand_XVII    = 16,
  EUarfcnBand_XVIII   = 17,
  EUarfcnBand_XIX     = 18,
  EUarfcnBand_XX      = 19,
  EUarfcnBand_NSN2000 = 20,
  EUarfcnBand_Last    = 21
} EUarfcnBand;

#endif /* _E_UARFCN_BAND_H */

/**
*******************************************************************************
* @enum EUarfcnBand
*
* Description         : Enumerated values indicating UARFCN Band
*
* Reference           : BTSOM TCOM IFS, 49.0, ShareNet-IMS
*
* Parameters :
*
* @param EUarfcnBand_I       : Band I
* @param EUarfcnBand_II      : Band II
* @param EUarfcnBand_III     : Band III
* @param EUarfcnBand_IV      : Band IV
* @param EUarfcnBand_V       : Band V
* @param EUarfcnBand_VI      : Band VI
* @param EUarfcnBand_VII     : Band VII
* @param EUarfcnBand_VIII    : Band VIII
* @param EUarfcnBand_IX      : Band IX
* @param EUarfcnBand_X       : Band X
* @param EUarfcnBand_XI      : Band XI
* @param EUarfcnBand_XII     : Band XII
* @param EUarfcnBand_XIII    : Band XIII
* @param EUarfcnBand_XIV     : Band XIV
* @param EUarfcnBand_XV      : Band XV
* @param EUarfcnBand_XVI     : Band XVI
* @param EUarfcnBand_XVII    : Band XVII
* @param EUarfcnBand_XVIII   : Band XVIII
* @param EUarfcnBand_XIX     : Band XIX
* @param EUarfcnBand_XX      : Band XX
* @param EUarfcnBand_NSN2000 : NSN 2000 band
* @param EUarfcnBand_Last    : Last enum value
*
* Additional Information :
*
* Definition Provided by : Telecom
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/

