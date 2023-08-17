/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EChannelCoding.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _ECHANNELCODING_H
#define _ECHANNELCODING_H

typedef enum EChannelCoding
{
    EChannelCoding_Empty         = 0,
    EChannelCoding_No            = 1,
    EChannelCoding_Convolutional = 2,
    EChannelCoding_Turbo         = 3,
    EChannelCoding_NumOfItems
} EChannelCoding;

#endif /* _ECHANNELCODING_H */

/**
*******************************************************************************
* @enum EChannelCoding
*
* Description :
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* @param EChannelCoding_Empty :
* @param EChannelCoding_No :
* @param EChannelCoding_Convolutional :
* @param EChannelCoding_Turbo :
* @param EChannelCoding_NumOfItems :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/




