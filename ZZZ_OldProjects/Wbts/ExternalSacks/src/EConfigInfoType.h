/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EConfigInfoType.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _ECONFIGINFOTYPE_H
#define _ECONFIGINFOTYPE_H

typedef enum EConfigInfoType
{
    EConfigInfoType_WamUnit               = 0,
    EConfigInfoType_WspUnit               = 1,
    EConfigInfoType_TrxModule             = 2,
    EConfigInfoType_WpaUnit               = 3,
    EConfigInfoType_LocalCellResource     = 4,
    EConfigInfoType_CarrierResources      = 5
} EConfigInfoType;

#endif /* _ECONFIGINFOTYPE_H */

/**
*******************************************************************************
* @enum EConfigInfoType
*
* Description :  Enum definitions for config info type
*                Indicates which info struct union 'Config info element' contains
*
* Reference   :  BTSOM - TCOM Interface Specification, v 3.0, PI
*
* Parameters  :
*
* @param EConfigInfoType_WamUnit           : union 'Config info element'contains WAM info
*
* @param EConfigInfoType_WspUnit           : union 'Config info element'contains WSP info
*
* @param EConfigInfoType_TrxModule         : union 'Config info element'contains TRX info
*
* @param EConfigInfoType_WpaUnit           : union 'Config info element'contains WPA info
*
* @param EConfigInfoType_LocalCellResource : union 'Config info element'contains LCR info
*
* @param EConfigInfoType_CarrierResources  : union 'Config info element'contains carrier resource info
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Codesso / Metsanurm
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/


