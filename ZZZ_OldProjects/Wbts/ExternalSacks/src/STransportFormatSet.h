/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/STransportFormatSet.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _STRANSPORTFORMATSET_H
#define _STRANSPORTFORMATSET_H

#include <TNumberOfItems.h>
#include <DOpenIUBCommonDefs.h>
#include <SDynamicTransportFormatInfoLST.h>
#include <SSemiStaticTransportFormatInfo.h>

typedef struct STransportFormatSet {
    TNumberOfItems                      numberOfdynamicTransportFormat;
    SDynamicTransportFormatInfoLST      dynamicTransportFormatInfo[MAX_TF_COUNT];
    SSemiStaticTransportFormatInfo      semiStaticTransportFormatInfo;
} STransportFormatSet;

#endif /* _STRANSPORTFORMATSET_H */

/**
*******************************************************************************
* @struct STransportFormatSet
*
* Description : 9.2.1.59  Transport Format Set
*               "The Transport Format Set is defined as the set of
*                Transport Formats associated to a Transport Channel,
*                e.g. DCH."
*
* Reference   : 3GPP TS 25.433 v4.1.0
*
* Parameters  :
*
* @param numberOfdynamicTransportFormat :
* @param dynamicTransportFormatInfo :
* @param semiStaticTransportFormatInfo :
*    MAX_TF_COUNT = Maximum number of different transport formats that
*                 can be included in the Transport format set for
*                 one transport channel
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom / Jesse Pasuri / Mika Hautala
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



