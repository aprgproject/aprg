/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
*
* Copyright (c) Nokia 2007. All rights reserved.
*******************************************************************************/

#ifndef _E_WSP_TYPE_H
#define _E_WSP_TYPE_H


typedef enum EWspType
{
    EWspType_WspA      = 0,
    EWspType_WspC      = 1,
    EWspType_WspD      = 2,
    EWspType_WspE      = 3,
    EWspType_Faraday   = 4,
    EWspType_FspA      = 5,
    EWspType_FspB      = 6,
    EWspType_Nyquist   = 7,
    EWspType_TurboNyquist  = 8,
    EWspType_Kepler2   = 9

}EWspType;

#endif  /* _E_WSP_TYPE_H */

/******************************************************************
* @enum EWspType
* Development Workset : WCDMA:BS_ENV_WS
*
* Design Part         : WCDMA:BS_ENV.A;1
*
* Description         : Enumeration for type of WSP unit.
*
* Reference           : DSP SW - MCU SW Interface Specification
*                       
*
* @param EWspType_WspA     : Type of unit: WSPA
* @param EWspType_WspC     : Type of unit: WSPC
* @param EWspType_WspD     : Type of unit: WSPD
* @param EWspType_WspE     : Type of unit: WSPE
* @param EWspType_Faraday  : Type of unit: Faraday
* @param EWspType_FspA     : Type of unit: FSPA
* @param EWspType_FspB     : Type of unit: FSPB
* @param EWspType_Nyquist  : Type of unit: Nyquist
* @param EWspType_TurboNyquist    : Type of unit: TurboNyquist
*
* Additional Information : -
*
* Definition Provided by : DSP 
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
***********************************************************************/


