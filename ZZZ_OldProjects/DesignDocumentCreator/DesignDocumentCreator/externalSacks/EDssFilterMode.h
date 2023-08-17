/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EDssFilterMode.h $
* @version               $LastChangedRevision: 2882 $
* @date                  $LastChangedDate: 2019-06-10 18:05:39 +0800 (Mon, 10 Jun 2019) $
* @author                $Author: malba $
*
* Original author        Mark Alba
*
* Copyright 2019 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _EDSS_FILTER_MODE_H
#define _EDSS_FILTER_MODE_H

typedef enum EDssFilterMode
{
    EDssFilterMode_Static   = 0,
    EDssFilterMode_Dynamic  = 1
} EDssFilterMode;

#endif /* _EDSS_FILTER_MODE_H */

/**
*******************************************************************************
* @enum EDssFilterMode
*
* Description : Enumerated type to identify the shared spectrum filter mode
*
* Reference   : OAM CPlane Interface Specification
*
* Parameters :
*
* @param Static          :   Indicates that the shared spectrum filter mode is static
*
* @param Dynamic         :   Indicates that the shared spectrum filter mode is dynamic
*
* Additional Information :
*
* Definition Provided by : WCDMA OAM TCOM DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

