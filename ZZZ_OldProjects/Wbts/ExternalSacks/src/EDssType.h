/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EDssType.h $
* @version               $LastChangedRevision: 2882 $
* @date                  $LastChangedDate: 2019-06-10 18:05:39 +0800 (Mon, 10 Jun 2019) $
* @author                $Author: malba $
*
* Original author        Mark Alba
*
* Copyright 2019 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _EDSS_TYPE_H
#define _EDSS_TYPE_H

typedef enum EDssType
{
    EDssType_None         = 0,
    EDssType_GsmAndWcdma  = 1,
    EDssType_WcdmaAndLte  = 2
} EDssType;

#endif /* _EDSS_TYPE_H */

/**
*******************************************************************************
* @enum EDssType
*
* Description : Enumerated type to identify the type of DSS
*
* Reference   : OAM CPlane Interface Specification
*
* Parameters :
*
* @param None            :   Indicates that there is no DSS
*
* @param GsmAndWcdma     :   Indicates that the DSS type is GSM and WCDMA
*                            GSM is the Master RAT that decides the usage of shared frequencies
*                            WCDMA is the Slave RAT that reacts based on the usage of shared frequencies of the Master RAT
*
* @param WcdmaAndLte     :   Indicates that the DSS type is WCDMA and LTE
*                            WCDMA is the Master RAT that decides the usage of shared frequencies
*                            LTE is the Slave RAT that reacts based on the usage of shared frequencies of the Master RAT
*
* Additional Information :
*
* Definition Provided by : WCDMA OAM TCOM DSP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

