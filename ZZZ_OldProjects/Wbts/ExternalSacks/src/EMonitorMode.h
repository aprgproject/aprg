/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_GLOBAL/tags/GLOBAL_ENV_13_168/I_Interface/Global_Env/Definitions/EMonitorMode.h $
* @version               $LastChangedRevision: 3080 $
* @date                  $LastChangedDate: 2014-05-23 20:32:51 +0800 (Fri, 23 May 2014) $
* @author                $Author: plaskonk $
*
* Original author        <nn>
*
* Copyright 2010 Nokia. All rights reserved.
*******************************************************************************/

#ifndef EMONITORMODE_H
#define EMONITORMODE_H


typedef enum EMonitorMode
{
    EMonitorMode_None               = 0,
    EMonitorMode_All                = 1,    /* Both directions  */
    EMonitorMode_TxOnly             = 2,    /* Only sent        */
    EMonitorMode_RxOnly             = 3     /* Only received    */
} EMonitorMode;

#endif /* EMONITORMODE_H */

/**
*******************************************************************************
* @enum EMonitorMode
*
* Description  : Enumeration to define mode of monitoring
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
* @param EMonitorMode_None :
* @param EMonitorMode_All :
* @param EMonitorMode_TxOnly :
* @param EMonitorMode_RxOnly :
*
* Additional Information : <type additional information if needed>
*
* Title        : Definition of EMonitorMode
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



