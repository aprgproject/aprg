/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/ETypeOfChannelCoding.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _ETYPEOFCHANNELCODING_H
#define _ETYPEOFCHANNELCODING_H

typedef enum ETypeOfChannelCoding
{
    ETypeOfChannelCoding_NoCodingTDD    = 0,
    ETypeOfChannelCoding_Convolutional  = 1,
    ETypeOfChannelCoding_Turbo          = 2
} ETypeOfChannelCoding;

#endif /* _ETYPEOFCHANNELCODING_H */

/**
*******************************************************************************
* @enum ETypeOfChannelCoding
*
* Description : Type of channel coding .
*
* Reference   : 3GPP TS 25.433 v4.4.0
*
* Parameters:
*
* @param ETypeOfChannelCoding_NoCodingTDD :
* @param ETypeOfChannelCoding_Convolutional :
* @param ETypeOfChannelCoding_Turbo :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom / Jesse Pasuri / Mika Hautala
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



