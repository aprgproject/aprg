/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EPresence.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _EPRESENCE_H
#define _EPRESENCE_H

typedef enum EPresence
{
    EPresence_NotPresent           = 0,
    EPresence_Present              = 1
} EPresence;

#endif /* _EPRESENCE_H */

/**
*******************************************************************************
* @enum EPresence
*
* Description  : Presence indicator of parameters in various messages
*                Defined in MCU SW - DSP SW I/F Spec 0.2.18
*                ch 8.1.30
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* @param EPresence_NotPresent :
* @param EPresence_Present :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



